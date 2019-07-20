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

#include <iostream>
#include <unordered_set>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

class NamedDeclAction : public MatchFinder::MatchCallback {
private:
  std::unordered_set<const Decl*> seen;

  void handleDeclPathComponent(const clang::Decl* decl) {
    if (isa<TranslationUnitDecl>(decl)) {
      std::cout << "<TU>";
      return;
    }

    auto ctx = decl->getDeclContext();
    auto ctx_decl = dyn_cast<Decl>(ctx);

    handleDeclPathComponent(ctx_decl);
    std::cout << "::<";
    if (ctx->isDependentContext()) {
      std::cout << "*";
    }
    std::cout << decl->getDeclKindName() << ">";

    auto named_decl = dyn_cast<NamedDecl>(decl);
    if (!named_decl) {
      std::cout << "[[unnamed]]";
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

    auto spec_decl = dyn_cast<ClassTemplateSpecializationDecl>(decl);
    if (spec_decl) {
      std::cout << "(";
      auto& args = spec_decl->getTemplateArgs();
      for (size_t i = 0; i < args.size(); i++) {
        if (i > 0) {
          std::cout << ", ";
        }
        auto arg = args[i];
        switch (arg.getKind()) {
        case TemplateArgument::ArgKind::Type:
          auto type = arg.getAsType();
          std::cout << type.getAsString();
        }
      }
      std::cout << ")";
    }

    auto fn_decl = dyn_cast<FunctionDecl>(decl);
    if (fn_decl) {
      std::cout << "(";
      for (size_t i = 0; i < fn_decl->getNumParams(); i++) {
        if (i > 0) {
          std::cout << ", ";
        }
        auto param_decl = fn_decl->getParamDecl(i);
        std::cout << param_decl->getType().getAsString();
      }
      std::cout << ")";
    }
  }

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<Decl>("decl");
    if (isa<TagDecl>(decl) &&
        dyn_cast<RecordDecl>(decl)->isCompleteDefinition()) {
      // Leave it.
    } else {
      decl = decl->getCanonicalDecl();
    }
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
  template <typename M>
  auto inContext(M m) {
    return anyOf(m, hasDeclContext(m), hasDeclContext(hasAncestor(m)));
  }

  template <typename M>
  auto isOrHasAncestor(M m) {
    return anyOf(m, hasAncestor(m));
  }

  template <typename M>
  auto unlessUnder(M m) {
    return unless(anyOf(m, hasAncestor(m)));
  }

  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    NamedDeclAction named_decl_action;
    RecordAction record_action;
    FunctionAction function_action;
    MatchFinder finder;
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    auto v8_ns = namespaceDecl(hasName("::v8"));
    auto v8_internal_ns = namespaceDecl(hasName("::v8::internal"));
    finder.addMatcher(decl(inContext(v8_ns),
                           unless(inContext(v8_internal_ns)),
                           unless(inContext(namespaceDecl(isAnonymous()))),
                           unless(hasAncestor(stmt())),
                           // unlessUnder(isPrivate()),
                           // unlessUnder(decl(isProtected(),
                           //            unless(hasParent(cxxRecordDecl(
                           //                hasMethod(isVirtual())))))),
                           unlessUnder(parmVarDecl()),
                           unlessUnder(indirectFieldDecl()),
                           unlessUnder(templateTypeParmDecl()),
                           unlessUnder(friendDecl()),
                           unlessUnder(accessSpecDecl()))
                          .bind("decl"),
                      &named_decl_action);
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
  return tool.run(newFrontendActionFactory<FrontendActionImpl>().get());
}
