#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
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

public:
  static auto inV8Namespace() {
    return decl(
        inDeclContext(namespaceDecl(hasName("::v8"))),
        unless(inDeclContext(namespaceDecl(hasName("::v8::internal")))));
  }

  static auto anyV8Api() {
    return decl(inV8Namespace(),
                unless(hasAncestor(stmt())),
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
};

class NamedDeclAction : public MatchFinder::MatchCallback {
  const ASTContext& ast_;

public:
  explicit NamedDeclAction(const ASTContext& ast) : ast_(ast) {}

private:
  std::unordered_set<const Decl*> seen;

  void handleIdentifier(const clang::IdentifierInfo* identifier) {
    auto name = identifier->getName().str();
    std::cout << name;
  }

  void handleTypeQualifiers(const clang::Qualifiers quals) {
    if (quals.empty()) {
      std::cout << "mut_";
    } else if (quals.hasOnlyConst()) {
      std::cout << "const_";
    } else {
      std::cout << "[[unsupported_qualifier]]";
    }
  }

  void handleQualType(
      const clang::QualType& qual_type,
      const clang::Qualifiers extra_quals = clang::Qualifiers()) {
    auto type = qual_type.getTypePtr();
    auto quals = qual_type.getQualifiers();
    quals.addQualifiers(extra_quals);

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

  void handleDeclPathComponent(const clang::Decl* decl) {
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
      std::cout << "*";
    }
    std::cout << decl->getDeclKindName() << "}";

    auto named_decl = dyn_cast<NamedDecl>(decl);
    if (!named_decl) {
      std::cout << "[[??unnamed]]";
      return;
    } else {
      auto name_info = named_decl->getDeclName();
      std::string name;
      switch (name_info.getNameKind()) {
      case DeclarationName::NameKind::Identifier:
        name = !name_info.isEmpty() ? name_info.getAsString() : "[[anon]]";
        break;
      case DeclarationName::NameKind::CXXConstructorName:
        name = "constructor";
        break;
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
    }

    auto spec_decl = dyn_cast<ClassTemplateSpecializationDecl>(decl);
    if (spec_decl) {
      handleTemplateArguments(spec_decl->getTemplateArgs().asArray());
    }

    auto fn_decl = dyn_cast<FunctionDecl>(decl);
    if (fn_decl) {
      auto template_args = fn_decl->getTemplateSpecializationArgs();
      if (template_args) {
        handleTemplateArguments(template_args->asArray());
      }

      std::cout << "(";
      for (size_t i = 0; i < fn_decl->getNumParams(); i++) {
        if (i > 0) {
          std::cout << ", ";
        }
        auto param_decl = fn_decl->getParamDecl(i);
        auto param_Type = param_decl->getType();
        handleQualType(param_Type);
      }
      std::cout << ")";
    }
  }

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<Decl>("decl")->getCanonicalDecl();
    // if (isa<TagDecl>(decl) && dyn_cast<TagDecl>(decl)->getDefinition()) {
    //  decl = dyn_cast<TagDecl>(decl)->getDefinition();
    //}
    if (seen.count(decl) > 0)
      return;
    seen.insert(decl);
    handleDeclPathComponent(decl);
    auto& sm = decl->getASTContext().getSourceManager();
    auto loc = decl->getBeginLoc().printToString(sm);
    std::cout << "  " << loc << std::endl;
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
    RecordAction record_action;
    FunctionAction function_action;
    MatchFinder finder;
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    finder.addMatcher(Matchers::anyV8Api().bind("decl"), &named_decl_action);
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
  auto result = tool.run(newFrontendActionFactory<FrontendActionImpl>().get());
  std::cout << "Done: " << result << std::endl;
  return result;
}
