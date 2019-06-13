#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
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

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

class MatchActionImpl : public MatchFinder::MatchCallback {
public:
  void run(const MatchFinder::MatchResult& result) override {
    auto node = result.Nodes.getNodeAs<NamedDecl>("decl");
    std::cout << node->getNameAsString() << std::endl;
  }
};

class ASTConsumerImpl : public ASTConsumer {
  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    MatchActionImpl callback;
    MatchFinder finder;
    finder.addMatcher(
        namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
        &callback);
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
