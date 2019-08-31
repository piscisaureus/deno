// clang -cc1 -E -P -I../llvm -I../build/llvm/llvm/tools -E ast_class_gen.js.pp | prettier --parser babel > ast_class_gen.js

class Node {}
exports.Node = Node;
  
#define NODE(Name, Base) \
  class Name extends Base {}; \
  exports.Name = Name;

NODE(Attr, Node)
#define ATTR(Name) NODE(Name##Attr, Attr)
#include "clang/include/clang/Basic/AttrList.inc"

NODE(Comment, Node)
#define COMMENT(Name, Base) NODE(Name, Base)
#include "clang/include/clang/AST/CommentNodes.inc"

NODE(Decl, Node)
#define DECL(Name, Base) NODE(Name##Decl, Base)
#include "clang/include/clang/AST/DeclNodes.inc"

NODE(Stmt, Node)
#define STMT(Name, Base) NODE(Name, Base)
#include "clang/include/clang/AST/StmtNodes.inc"

NODE(Type, Node)
NODE(QualType, Type)
#define TYPE(Name, Base) NODE(Name##Type, Base)
#include "clang/include/clang/AST/TypeNodes.def"
