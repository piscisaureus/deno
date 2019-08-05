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
#include <sstream>
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

class ASTConsumerImpl : public ASTConsumer {

  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    InvokableDeclAction invokable_action(ast);
    RecordAction record_action;
    MatchFinder finder;
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    finder.addMatcher(decl(Matchers::anyV8Api()).bind("decl"),
                      &invokable_action);
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
  auto result = tool.run(newFrontendActionFactory<FrontendActionImpl>().get());
  std::cout << "// Done: " << result << std::endl;
  return result;
}
