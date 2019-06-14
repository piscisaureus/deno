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
public:
  void run(const MatchFinder::MatchResult& result) override {
    auto node = result.Nodes.getNodeAs<NamedDecl>("decl");
    std::cout << node->getNameAsString() << std::endl;
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
    FunctionProtoType
    std::cout << node->getNameAsString() << std::endl;

    auto ret = node->getReturnType();
    std::cout << "  " << ret.getAsString();

    auto ret2 = ret.split();
    for (;;) {
      std::cout << "=> ";
      ret2.Ty->dump();
      auto ret3 = ret2.getSingleStepDesugaredType();
      if (ret2 == ret3) break;
      ret2 = ret3;
    }
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
    NamedDeclAction named_decl_action;
    RecordAction record_action;
    FunctionAction function_action;
    MatchFinder finder;
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);
    auto v8api = decl(hasAncestor(namespaceDecl(hasName("::v8"))),
      unless(hasAncestor(namespaceDecl(hasName("internal")))));
    //finder.addMatcher(namedDecl(v8api).bind("decl"), &named_decl_action);
    //finder.addMatcher(recordDecl(v8api).bind("record", &record_action);
    finder.addMatcher(functionDecl(v8api).bind("fn"), &function_action);
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
