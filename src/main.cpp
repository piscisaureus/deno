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

#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <unordered_map>
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
                // unlessUnder(decl(
                //   isProtected(),
                //   unless(hasParent(cxxRecordDecl(hasMethod(isVirtual())))))),
                // unlessUnder(parmVarDecl()),
                // unlessUnder(indirectFieldDecl()),
                // unlessUnder(templateTypeParmDecl()),
                unlessUnder(friendDecl()),
                unlessUnder(accessSpecDecl()));
  }

  static auto anyV8Api() {
    return decl(inV8Namespace(), pubApi());
  }
};

class InvokableDeclAction : public MatchFinder::MatchCallback {
  ASTContext& ast_;
  PrintingPolicy pp_;

public:
  explicit InvokableDeclAction(ASTContext& ast)
      : ast_(ast), pp_(ast_.getLangOpts()) {
    // Ensure that printing types yields valid C++. This ensures:
    //   - tags ('class' etc) are not printed in type specifiers.
    //   - 'bool' is used rather than '_Bool'.
    pp_.adjustForCPlusPlus();
  }

private:
  std::unordered_set<const Decl*> seen;

  void printDecl(const Decl* decl) {
    auto named_decl = dyn_cast<NamedDecl>(decl);

    clang::QualType signature;
    std::string value;
    static const char* wrapper_template;

    do {
      auto ctor_decl = dyn_cast<CXXConstructorDecl>(decl);
      if (ctor_decl) {
        if (ctor_decl->isDeleted())
          return;
        auto mem_qty = ctor_decl->getType();
        auto cls_ty = ctor_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        wrapper_template = "pick_constructor_v";
        break;
      }

      auto dtor_decl = dyn_cast<CXXDestructorDecl>(decl);
      if (dtor_decl) {
        if (dtor_decl->isDeleted())
          return;
        auto mem_qty = dtor_decl->getType();
        auto cls_ty = dtor_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        wrapper_template = "pick_destructor_v";
        break;
      }

      auto method_decl = dyn_cast<CXXMethodDecl>(decl);
      if (method_decl && method_decl->isInstance()) {
        if (method_decl->isDeleted())
          return;
        auto mem_qty = method_decl->getType();
        auto cls_ty = method_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        value = std::string("&") + named_decl->getQualifiedNameAsString();
        wrapper_template = "pick_overload_v";
        break;
      }

      auto fn_decl = dyn_cast<FunctionDecl>(decl);
      if (fn_decl) {
        if (fn_decl->isDeleted())
          return;
        auto fn_ty = decl->getFunctionType();
        auto fn_qty = QualType(fn_ty, 0);
        signature = ast_.getPointerType(fn_qty);
        value = std::string("&") + named_decl->getQualifiedNameAsString();
        wrapper_template = "pick_overload_v";
        break;
      }

      // Otherwise, we're not interested.
      return;
    } while (false);

    // Canonicalize the type name.
    signature = signature.getCanonicalType();

    // Do not write out instantiation-dependent types.
    if (signature.getTypePtr()->isInstantiationDependentType())
      return;

    std::ostringstream os;
    os << "  X_" << decl->getDeclKindName() << "(( " << wrapper_template << "<"
       << signature.getAsString(pp_);
    if (!value.empty()) {
      os << ", " << value;
    }
    os << "> ))\n";
    auto s = os.str();

    // if (s.find("unique_ptr") != string::npos ||
    //    s.find("Uncompilable") != string::npos ||
    //    decl->getAccess() == clang::AccessSpecifier::AS_protected) {
    s = std::string("// ") + s;
    //}

    std::cout << s;
  }

  void addDecl(const Decl* decl) {
    decl = decl->getCanonicalDecl();
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

// Define a hasher for clang::QualType.
template <>
struct hash<clang::QualType> {
  size_t operator()(clang::QualType qty) const {
    auto ty = qty.getTypePtr();
    auto quals = qty.getLocalQualifiers().getAsOpaqueValue();
    return hash<decltype(ty)>()(ty) | hash<decltype(quals)>()(quals);
  }
};

class AstToTemplates : public MatchFinder::MatchCallback {
  ASTContext& ast_;
  PrintingPolicy pp_;

  std::unordered_map<const clang::Decl*, size_t> decl_ids;
  std::unordered_map<const clang::Type*, size_t> type_ids;
  std::unordered_map<clang::QualType, size_t> qty_ids;
  std::unordered_map<std::string, size_t> name_ids;

public:
  explicit AstToTemplates(ASTContext& ast)
      : ast_(ast), pp_(ast_.getLangOpts()) {
    // Ensure that printing types yields valid C++. This ensures:
    //   - tags ('class' etc) are not printed in type specifiers.
    //   - 'bool' is used rather than '_Bool'.
    pp_.adjustForCPlusPlus();
  }

private:
  void add_type(const clang::Type* type) {
    if (type->isInstantiationDependentType())
      return;

    // Assign id.
    auto& type_id = type_ids[type];
    if (type_id > 0)
      return;
    type_id = type_ids.size();
    assert(type_id > 0);

    // Add dereferenced type.
    auto pointee_type = type->getPointeeOrArrayElementType();
    if (pointee_type != type)
      add_type(pointee_type);

    // Add function arguments and return qualified type.
    auto fn_proto_qty = type->getAs<FunctionProtoType>();
    if (fn_proto_qty) {
      add_qty(fn_proto_qty->getReturnType());
      // Adjusted return type.
      add_qty(fn_proto_qty->getCallResultType(ast_));

      for (auto& param_type : fn_proto_qty->param_types()) {
        add_qty(param_type);
        // Adjusted parameter type.
        add_qty(ast_.getAdjustedParameterType(param_type));
      }
    }

    // Add desugared qualified type.
    auto desugared_qty = type->getLocallyUnqualifiedSingleStepDesugaredType();
    add_qty(desugared_qty);

    // Add declarations.
    auto tag_decl = type->getAsTagDecl();
    if (tag_decl)
      add_decl(tag_decl);

    auto pointee_decl = type->getPointeeCXXRecordDecl();
    if (pointee_decl)
      add_decl(pointee_decl);
  }

  void add_qty(QualType qty) {
    auto type = qty.getTypePtr();
    auto quals = qty.getLocalQualifiers();

    if (type->isInstantiationDependentType())
      return;

    // Only 'const' qualified and mutable types are supported.
    assert(quals.empty() || quals.hasOnlyConst());

    // Assign id.
    auto& qty_id = qty_ids[qty];
    if (qty_id > 0)
      return;
    qty_id = qty_ids.size();
    assert(qty_id > 0);

    // Add unqualified type.
    add_type(type);
  }

  void add_decl(const Decl* decl) {
    // Only process canonical decls.
    decl = decl->getCanonicalDecl();

    // Skip deleted functions.
    if (isa<FunctionDecl>(decl) && dyn_cast<FunctionDecl>(decl)->isDeleted())
      return;

    // Assign id.
    auto& decl_id = decl_ids[decl];
    if (decl_id > 0)
      return;
    decl_id = decl_ids.size();
    assert(decl_id > 0);

    // Add name if named.
    auto named_decl = dyn_cast<NamedDecl>(decl);
    if (named_decl) {
      auto name = named_decl->getNameAsString();
      auto& name_id = name_ids[name];
      if (name_id == 0) {
        name_id = name_ids.size();
        assert(name_id > 0);
      }
    }

    // Add type.
    auto type_decl = dyn_cast<TypeDecl>(decl);
    if (type_decl) {
      auto qty = ast_.getTypeDeclType(type_decl);
      add_qty(qty);
    }

    auto value_decl = dyn_cast<ValueDecl>(decl);
    if (value_decl) {
      auto qty = value_decl->getType();
      add_qty(qty);
    }

    auto fn_decl = dyn_cast<FunctionDecl>(decl);
    if (fn_decl) {
      auto fn_ty = decl->getFunctionType();
      add_type(fn_ty);
    }

    auto method_decl = dyn_cast<CXXMethodDecl>(decl);
    if (method_decl && method_decl->isInstance()) {
      auto cls_ty = method_decl->getParent()->getTypeForDecl();
      // Todo: add const and ref-quals.
      add_type(cls_ty);
    }
  }

  template <class K, class V>
  auto sort_by_id(const std::unordered_map<K, V>& map) {
    std::vector<std::pair<K, V>> vec;
    for (auto& it : map) {
      vec.push_back(it);
    }
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) -> bool {
      return a.second < b.second;
    });
    return vec;
  }

  void print_meta_type_decls(llvm::raw_ostream& out) {
    for (auto& it : sort_by_id(type_ids)) {
      out << "struct ty" << it.second << ";  // "
          << it.first->getTypeClassName() << " ";
      QualType(it.first, 0).print(out, pp_);
      out << "\n";
    }

    for (auto& it : sort_by_id(qty_ids)) {
      auto ty = it.first.getTypePtr();
      auto quals = it.first.getLocalQualifiers();
      out << "struct qty" << it.second << ";  // " << ty->getTypeClassName()
          << " " << (quals.hasConst() ? "const" : "mut") << " ";
      QualType(ty, 0).print(out, pp_);
      out << "\n";
    }

    for (auto& it : sort_by_id(decl_ids)) {
      out << "struct def" << it.second << ";  // "
          << it.first->getDeclKindName();
      if (isa<NamedDecl>(it.first)) {
        out << " " << dyn_cast<NamedDecl>(it.first)->getNameAsString();
      }
      out << "\n";
    }

    for (auto& it : sort_by_id(name_ids)) {
      out << "struct nm" << it.second << " { "
          << "static const char* name() { "
          << "return \"" << it.first << "\"; "
          << "} "
          << "};\n";
    }
  }

  void print_meta_class(llvm::raw_ostream& out, clang::Type* type) {
    out << "ty" << type_ids[type];
  }

  void print_meta_class(llvm::raw_ostream& out, Decl* decl) {
    out << "def" << decl_ids[decl];
  }

public:
  void write(llvm::raw_ostream& out) {
    print_meta_type_decls(out);
  }

  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<Decl>("decl");
    add_decl(decl);
  }
};

class ASTConsumerImpl : public ASTConsumer {

  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    InvokableDeclAction invokable_action(ast);
    RecordAction record_action;
    MatchFinder finder;
    AstToTemplates ast_to_templates(ast);
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    finder.addMatcher(decl(Matchers::anyV8Api()).bind("decl"),
                      &ast_to_templates);
    finder.matchAST(ast);
    ast_to_templates.write(llvm::outs());
    // finder.addMatcher(
    //     decl(varDecl(hasAncestor(namespaceDecl(hasName("::v8_wrap")))))
    //         .bind("decl"),
    //     &var_type_action);
    // finder.addMatcher(recordDecl(v8api).bind("record",
    // &record_action);
    // finder.addMatcher(functionDecl(v8api).bind("fn"),
    // &function_action);
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
  llvm::outs() << "// Done: " << result << "\n";
  return result;
}
