#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include <cassert>
#include <iostream>
#include <unordered_set>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

class Matchers {
public:
  template <typename M>
  static auto inDeclContext(M m) {
    return anyOf(m, hasDeclContext(m), hasDeclContext(hasAncestor(m)));
  }

  template <typename M>
  static auto isOrHasAncestor(M m) {
    return anyOf(m, hasAncestor(m));
  }

  template <typename M>
  static auto unlessUnder(M m) {
    return unless(anyOf(m, hasAncestor(m)));
  }

  static auto inV8Namespace() {
    return decl(
        inDeclContext(namespaceDecl(hasName("::v8"))),
        unless(inDeclContext(namespaceDecl(hasName("::v8::internal")))));
  }

  static auto pubApi() {
    return decl(unless(hasAncestor(stmt())),
                unlessUnder(namespaceDecl(isAnonymous())),
                unlessUnder(isPrivate()),
                unlessUnder(decl(
                    isProtected(),
                    unless(hasParent(cxxRecordDecl(hasMethod(isVirtual())))))),
                unlessUnder(parmVarDecl()),
                unlessUnder(indirectFieldDecl()),
                unlessUnder(templateTypeParmDecl()),
                unlessUnder(friendDecl()),
                unlessUnder(accessSpecDecl()));
  }

  static auto anyV8Api() {
    return decl(inV8Namespace(), pubApi());
  }
};

class NamedDeclAction : public MatchFinder::MatchCallback {
  ASTContext& ast_;

public:
  explicit NamedDeclAction(ASTContext& ast) : ast_(ast) {}

private:
  std::unordered_set<const Decl*> seen;
  std::unordered_set<const Decl*> todo;
  bool is_running = false;

  void handleIdentifier(const clang::IdentifierInfo* identifier) {
    auto name = identifier->getName().str();
    std::cout << name;
  }

  void handleQualifiers(const clang::Qualifiers quals) {
    if (quals.empty()) {
      std::cout << "mut";
    } else if (quals.hasOnlyConst()) {
      std::cout << "const";
    } else {
      std::cout << "[[unsupported_qualifier]]";
    }
  }

  void handleTypeQualifiers(const clang::Qualifiers quals) {
    handleQualifiers(quals);
    std::cout << "_";
  }

  void addTemplateArgs(ArrayRef<TemplateArgument> args) {
    for (auto arg = args.begin(); arg != args.end(); ++arg) {
      switch (arg->getKind()) {
      case TemplateArgument::ArgKind::Declaration:
        addDeclContext(arg->getAsDecl());
        break;
      case TemplateArgument::ArgKind::Type:
        addType(arg->getAsType());
        break;
      case TemplateArgument::ArgKind::Expression:
        addType(arg->getAsExpr()->getType());
        break;
      case TemplateArgument::ArgKind::Pack:
        addTemplateArgs(arg->getPackAsArray());
        break;
      case TemplateArgument::ArgKind::TemplateExpansion:
      case TemplateArgument::ArgKind::Template: {
        auto d = arg->getAsTemplateOrTemplatePattern().getAsTemplateDecl();
        if (d) {
          addDeclContext(d);
        }
        break;
      }
      case TemplateArgument::ArgKind::Integral:
      case TemplateArgument::ArgKind::Null:
      case TemplateArgument::ArgKind::NullPtr:
        // Do nothing.
        break;
      default:
        llvm_unreachable("No such template argument kind");
      }
    }
  }

  void addTypes(ArrayRef<QualType> types) {
    for (auto qt = types.begin(); qt != types.end(); ++qt) {
      addType(*qt);
    }
  }

  void addType(const clang::QualType qual_type) {
    auto qt = qual_type;
    for (;;) {
      auto desugared = qt.getSingleStepDesugaredType(ast_);
      if (desugared == qt)
        break;
      qt = desugared;
      auto type = qt.getTypePtr();
      auto tag_type = dyn_cast<TagType>(type);
      if (tag_type) {
        addDeclContext(tag_type->getAsTagDecl());
      }
      auto typedef_type = dyn_cast<TypedefType>(type);
      if (typedef_type) {
        addDeclContext(typedef_type->getDecl());
      }
      auto spec_type = dyn_cast<TemplateSpecializationType>(type);
      if (spec_type) {
        addTemplateArgs(spec_type->template_arguments());
      }
      auto fn_type = dyn_cast<clang::FunctionType>(type);
      if (fn_type) {
        addType(fn_type->getReturnType());
      }
      auto fn_proto_type = dyn_cast<clang::FunctionProtoType>(type);
      if (fn_type) {
        addTypes(fn_proto_type->getParamTypes());
        addTypes(fn_proto_type->exceptions());
      }
    }
  }

  void handleQualType(
      const clang::QualType qual_type,
      const clang::Qualifiers extra_quals = clang::Qualifiers()) {
    addType(qual_type);

    auto type = qual_type.getTypePtr();
    auto quals = qual_type.getQualifiers();
    quals.addQualifiers(extra_quals);

    if (type->isDependentType()) {
      std::cout << "^";
    }

    switch (type->getTypeClass()) {
    case clang::Type::Builtin: {
      handleTypeQualifiers(quals);
      PrintingPolicy pp(ast_.getLangOpts());
      std::cout << dyn_cast<BuiltinType>(type)->getNameAsCString(pp);
      break;
    }
    case clang::Type::TypeClass::Record:
    case clang::Type::TypeClass::Enum:
      handleTypeQualifiers(quals);
      handleDeclPathComponent(type->getAsTagDecl());
      break;
    case clang::Type::TypeClass::Pointer:
      handleTypeQualifiers(quals);
      std::cout << "ptr_";
      handleQualType(type->getPointeeType());
      break;
    case clang::Type::TypeClass::LValueReference:
      handleTypeQualifiers(quals);
      std::cout << "ref_";
      handleQualType(type->getPointeeType());
      break;
    case clang::Type::TypeClass::RValueReference:
      handleTypeQualifiers(quals);
      std::cout << "move_";
      handleQualType(type->getPointeeType());
      break;
    case clang::Type::TypeClass::ConstantArray:
    case clang::Type::TypeClass::IncompleteArray:
    case clang::Type::TypeClass::VariableArray:
    case clang::Type::TypeClass::DependentSizedArray:
      handleTypeQualifiers(quals);
      std::cout << "array_of_";
      handleQualType(dyn_cast<clang::ArrayType>(type)->getElementType());
      break;
    case clang::Type::TypeClass::Decayed:
      handleQualType(dyn_cast<DecayedType>(type)->getDecayedType(), quals);
      break;
    case clang::Type::TypeClass::Elaborated:
      handleQualType(dyn_cast<ElaboratedType>(type)->getNamedType(), quals);
      break;
    case clang::Type::TypeClass::Typedef:
      handleTypeQualifiers(quals);
      handleDeclPathComponent(dyn_cast<TypedefType>(type)->getDecl());
      break;
    case clang::Type::InjectedClassName:
      handleQualType(dyn_cast<InjectedClassNameType>(type)
                         ->getInjectedSpecializationType(),
                     quals);
      break;
    case clang::Type::TemplateSpecialization: {
      handleTypeQualifiers(quals);
      auto spec_type = dyn_cast<TemplateSpecializationType>(type);
      auto decl = spec_type->getTemplateName().getAsTemplateDecl();
      if (decl) {
        handleDeclPathComponent(decl);
      } else {
        std::cout << "[[no-template-decl]]";
      }
      handleTemplateArguments(spec_type->template_arguments());
      break;
    }
    case clang::Type::TemplateTypeParm:
      handleTypeQualifiers(quals);
      handleIdentifier(dyn_cast<TemplateTypeParmType>(type)->getIdentifier());
      break;
    case clang::Type::DependentName:
      handleTypeQualifiers(quals);
      handleIdentifier(dyn_cast<DependentNameType>(type)->getIdentifier());
      break;
    case clang::Type::SubstTemplateTypeParm:
      handleQualType(
          dyn_cast<SubstTemplateTypeParmType>(type)->getReplacementType(),
          quals);
      break;
    default:
      std::cout << "[[??" << type->getTypeClassName() << "]]";
      break;
    }
  }

  void handleTemplateArguments(const ArrayRef<TemplateArgument> args) {
    std::cout << "<";
    for (size_t i = 0; i < args.size(); i++) {
      if (i > 0) {
        std::cout << ", ";
      }
      auto& arg = args[i];
      switch (arg.getKind()) {
      case TemplateArgument::ArgKind::Type: {
        auto arg_type = arg.getAsType();
        handleQualType(arg_type);
        break;
      }
      default:
        std::cout << "[[??NonTypeArg]]";
        break;
      }
    }
    std::cout << ">";
  }

  void handleFunctionParameters(const FunctionDecl* fn_decl) {
    std::cout << "(";
    auto params = fn_decl->parameters();
    for (size_t i = 0; i < params.size(); i++) {
      if (i > 0) {
        std::cout << ", ";
      }
      auto param_decl = params[i];
      handleQualType(param_decl->getType());

      // Try to find a name for this parameter by looking at all
      // redeclarations of this function. When different declarations for
      // the same function use different names, try to to use the name from
      // a non-definition declaration, since it is more likely to be
      // meaningful from an external viewpoint.
      auto name_parm_decl = param_decl;
      auto name_parent_fn_decl = fn_decl;
      auto name_info = param_decl->getDeclName();

      auto fn_redecls = fn_decl->redecls();
      for (auto f = fn_redecls.begin();
           f != fn_redecls.end() &&
           (name_info.isEmpty() ||
            name_parent_fn_decl->isThisDeclarationADefinition());
           ++f) {
        auto p = f->getParamDecl(i);
        auto n = p->getDeclName();
        if (n.isEmpty())
          continue;
        name_parm_decl = p;
        name_parent_fn_decl = f->getAsFunction();
        name_info = n;
      }

      std::cout << "_";
      handleName(name_parm_decl);
    }
    std::cout << ")";
  }

  void handleName(const clang::NamedDecl* named_decl) {
    auto name_info = named_decl->getDeclName();
    std::string name;
    switch (name_info.getNameKind()) {
    case DeclarationName::NameKind::Identifier:
      name = !name_info.isEmpty() ? name_info.getAsString() : "[[anon]]";
      break;
    case DeclarationName::NameKind::CXXConstructorName: {
      auto ctor_decl = dyn_cast<CXXConstructorDecl>(named_decl);
      if (ctor_decl && ctor_decl->isConvertingConstructor(false)) {
        name = "convert_from";
      } else {
        name = "constructor";
      }
      break;
    }
    case DeclarationName::NameKind::CXXDestructorName:
      name = "destructor";
      break;
    case DeclarationName::NameKind::CXXConversionFunctionName:
      name = "convert_to";
      break;
    case DeclarationName::NameKind::CXXOperatorName:
      switch (name_info.getCXXOverloadedOperator()) {
      case OverloadedOperatorKind::OO_New:
        name = "op_new";
        break;
      case OverloadedOperatorKind::OO_Delete:
        name = "op_delete";
        break;
      case OverloadedOperatorKind::OO_Array_New:
        name = "op_new_array";
        break;
      case OverloadedOperatorKind::OO_Array_Delete:
        name = "op_delete_array";
        break;
      case OverloadedOperatorKind::OO_Subscript:
        name = "op_subscript";
        break;
      case OverloadedOperatorKind::OO_Equal:
        name = "op_assign";
        break;
      case OverloadedOperatorKind::OO_EqualEqual:
        name = "op_equal";
        break;
      case OverloadedOperatorKind::OO_ExclaimEqual:
        name = "op_not_equal";
        break;
      case OverloadedOperatorKind::OO_Star:
        name = "op_deref";
        break;
      case OverloadedOperatorKind::OO_Arrow:
        name = "op_deref_recursive";
        break;
      default:
        name = "[[unsupported operator]]";
        break;
      }
      break;
    default:
      name = "[[unsupported]]";
      break;
    }
    std::cout << name;
  }

  void handleDeclPathComponent(const clang::Decl* decl) {
    addDecl(decl);

    if (isa<TranslationUnitDecl>(decl)) {
      std::cout << "{TU}";
      return;
    }

    auto linkage_spec_decl = dyn_cast<LinkageSpecDecl>(decl);
    if (linkage_spec_decl) {
      // `extern "C"` declarations have no name and are always global.
      assert(linkage_spec_decl->getLanguage() == LinkageSpecDecl::lang_c);
      return handleDeclPathComponent(decl->getTranslationUnitDecl());
    }

    auto ctx = decl->getDeclContext();
    auto ctx_decl = dyn_cast<Decl>(ctx);
    handleDeclPathComponent(ctx_decl);

    std::cout << "::{";
    if (ctx->isDependentContext()) {
      std::cout << "^";
    }
    std::cout << decl->getDeclKindName() << "}";

    auto named_decl = dyn_cast<NamedDecl>(decl);
    if (!named_decl) {
      std::cout << "[[??unnamed]]";
      return;
    } else {
      handleName(named_decl);
    }

    auto method_decl = dyn_cast<CXXMethodDecl>(decl);
    if (method_decl && method_decl->isInstance()) {
      auto ref_qual = method_decl->getRefQualifier();
      switch (ref_qual) {
      case RefQualifierKind::RQ_LValue:
        std::cout << "_ref";
        break;
      case RefQualifierKind::RQ_RValue:
        std::cout << "_move";
        break;
      case RefQualifierKind::RQ_None:
        // Nothing.
        break;
      default:
        llvm_unreachable("Unexpected RefQualifierKind");
      }

      std::cout << "_";
      handleQualifiers(method_decl->getMethodQualifiers());
    }

    auto spec_decl = dyn_cast<ClassTemplateSpecializationDecl>(decl);
    if (spec_decl) {
      handleTemplateArguments(spec_decl->getTemplateArgs().asArray());
    }

    auto fn_decl = dyn_cast<FunctionDecl>(decl);
    if (fn_decl) {
      addType(fn_decl->getType());
      auto template_args = fn_decl->getTemplateSpecializationArgs();
      if (template_args) {
        handleTemplateArguments(template_args->asArray());
      }
      handleFunctionParameters(fn_decl);
    }
  }

  void handleDecl(const Decl* decl) {
    seen.insert(decl);
    handleDeclPathComponent(decl);
    auto& sm = decl->getASTContext().getSourceManager();
    auto loc = decl->getBeginLoc().printToString(sm);
    std::cout << "  " << loc << std::endl;
  }

  void addDeclContext(const Decl* decl) {
    addDecl(decl);

    MatchFinder finder;
    finder.addMatcher(clang::ast_matchers::decl(
                          forEachDescendant(Matchers::pubApi().bind("decl"))),
                      this);
    finder.match(*decl, ast_);
  }

  void addDecl(const Decl* decl) {
    decl = decl->getCanonicalDecl();
    if (seen.count(decl) > 0 || todo.count(decl) > 0)
      return;
    todo.insert(decl);

    if (is_running)
      return;
    is_running = true;
    while (todo.size() > 0) {
      auto decl = todo.begin();
      handleDecl(*decl);
      todo.erase(decl);
    }
    is_running = false;
  }

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<Decl>("decl");
    addDecl(decl);
  }
};

class SimpleNamedDeclAction : public MatchFinder::MatchCallback {
  ASTContext& ast_;
  PrintingPolicy pp_;

public:
  explicit SimpleNamedDeclAction(ASTContext& ast)
      : ast_(ast), pp_(ast_.getLangOpts()) {}

private:
  std::unordered_set<const Decl*> seen;

  void printDecl(const NamedDecl* decl) {
    clang::QualType ptr_qty;
    do {
      auto method_decl = dyn_cast<CXXMethodDecl>(decl);
      if (method_decl && method_decl->isInstance()) {
        if (method_decl->isDeleted())
          return;
        auto mem_qty = method_decl->getType();
        auto cls_ty = method_decl->getParent()->getTypeForDecl();
        ptr_qty = ast_.getMemberPointerType(mem_qty, cls_ty);
        break;
      }

      auto fn_decl = dyn_cast<FunctionDecl>(decl);
      if (fn_decl) {
        if (fn_decl->isDeleted())
          return;
        auto fn_ty = decl->getFunctionType();
        auto fn_qty = QualType(fn_ty, 0);
        ptr_qty = ast_.getPointerType(fn_qty);
        break;
      }

      // Otherwise, we're not interested.
      return;
    } while (false);

    // Canonicalize the type name.
    ptr_qty = ptr_qty.getCanonicalType();

    // Do not write out instantiation-dependent types.
    if (ptr_qty.getTypePtr()->isInstantiationDependentType())
        return;

    // Do not print tags ('class' etc).
    // Use 'bool' and not '_Bool'.
    PrintingPolicy pp(ast_.getLangOpts());
    pp.adjustForCPlusPlus();

     std::cout << "  X(" << decl->getDeclKindName() << ", "
                  << decl->getQualifiedNameAsString() << ", "
              << ptr_qty.getAsString(pp) << ") \\\n";
    }

  void addDecl(const NamedDecl* decl) {
    decl = dyn_cast<NamedDecl>(decl->getCanonicalDecl());
    if (seen.count(decl) > 0)
      return;
    printDecl(decl);
  }

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<NamedDecl>("decl");
    addDecl(decl);
  }
};

class FunctionAction : public MatchFinder::MatchCallback {
  std::unordered_set<const FunctionDecl*> seen;

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto node = result.Nodes.getNodeAs<FunctionDecl>("fn")->getCanonicalDecl();
    if (seen.count(node) > 0) {
      return;
    }
    seen.insert(node);
    std::cout << node->getNameAsString() << std::endl;

    auto ret = node->getReturnType();
    std::cout << "  " << ret.getAsString();

    auto ret2 = ret.split();
    for (;;) {
      std::cout << "=> ";
      ret2.Ty->dump();
      auto ret3 = ret2.getSingleStepDesugaredType();
      if (ret2 == ret3)
        break;
      ret2 = ret3;
    }
    std::cout << std::endl;
  }
};

class VarTypeAction : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult& result) override {
    auto node = result.Nodes.getNodeAs<VarDecl>("decl")->getCanonicalDecl();
    std::cout << node->getNameAsString() << " => "
              << node->getType().getAsString() << " => "
              << node->getType().getCanonicalType().getAsString() << std::endl;
  }
};

class RecordAction : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult& result) override {
    auto node = result.Nodes.getNodeAs<RecordDecl>("record");
    if (!node->isCompleteDefinition()) {
      return;
    }
    std::cout << node->getNameAsString();
    if (node->isDependentType()) {
      std::cout << " <dependent>" << std::endl;
      return;
    }
    auto& layout = result.Context->getASTRecordLayout(node);
    if (layout.hasVBPtr() || layout.hasOwnVBPtr() || layout.hasOwnVFPtr()) {
      std::cout << " <virtual>";
    }
    std::cout << " size:" << layout.getSize().getQuantity();
    std::cout << " align:" << layout.getAlignment().getQuantity();
    std::cout << " fields:" << layout.getFieldCount();
    std::cout << std::endl;
    int n = 0;
    for (const auto& field : node->fields()) {
      auto offset = layout.getFieldOffset(n++);
      auto acc = field->getAccess();
      std::cout << "  " << n << " " << field->getNameAsString() << " +"
                << offset;
      switch (acc) {
      case AS_public:
        std::cout << " PUBLIC <===";
        break;
      case AS_private:
        std::cout << " private";
        break;
      case AS_protected:
        std::cout << " PROTECTED <===";
        break;
      case AS_none:
        std::cout << " NONE <===";
        break;
      }
      std::cout << std::endl;
    }
  }
};

class ASTConsumerImpl : public ASTConsumer {

  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    NamedDeclAction named_decl_action(ast);
    SimpleNamedDeclAction simple_named_decl_action(ast);
    RecordAction record_action;
    FunctionAction function_action;
    VarTypeAction var_type_action;
    MatchFinder finder;
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    finder.addMatcher(namedDecl(Matchers::anyV8Api()).bind("decl"),
                      &simple_named_decl_action);
    // finder.addMatcher(
    //     decl(varDecl(hasAncestor(namespaceDecl(hasName("::v8_wrap")))))
    //         .bind("decl"),
    //     &var_type_action);
    // finder.addMatcher(recordDecl(v8api).bind("record",
    // &record_action);
    // finder.addMatcher(functionDecl(v8api).bind("fn"),
    // &function_action);
    finder.matchAST(ast);
  }
};

class FrontendActionImpl : public ASTFrontendAction {
public:
  std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& CI,
                                                 StringRef file) override {
    return llvm::make_unique<ASTConsumerImpl>();
  }
};

int main(int argc, const char** argv) {
  cl::OptionCategory opt_category("gen8");
  tooling::CommonOptionsParser opt_parser(argc, argv, opt_category);

  tooling::ClangTool tool(opt_parser.getCompilations(),
                          opt_parser.getSourcePathList());
  std::cout << "#define DECLARATIONS(X) \\\n";
  auto result = tool.run(newFrontendActionFactory<FrontendActionImpl>().get());
  std::cout << "// Done: " << result << std::endl;
  return result;
}
