let { readFileSync } = require("fs");
require("util").inspect.defaultOptions.depth = null;
Error.stackTraceLimit = Infinity;

function main() {
  let ast_dump = readFileSync("o3", "utf8");
  let parser = new Parser(ast_dump);
  let result = parser.expect(p => new TranslationUnit(p));
  //parser.skip(/^$/);
  console.log(parser.ratify(result));
}

class ParseError extends Error {
  constructor(input, pattern) {
    const q = JSON.stringify;
    input = input.slice(0, 80);
    super(
      `Parse error\n` + `  pattern: ${q(pattern)}\n` + `  input:   ${q(input)}`
    );
  }
}

function assert(condition) {
  if (!condition) throw new Error("Assertion failed");
}

class Parser {
  constructor(str) {
    this.str = str === undefined ? "" : `${str}`;
    this.error = null;
  }

  _fork() {
    let fork = new Parser(this.str);
    return fork;
  }

  _unfork(fork) {
    assert(fork.error === null);
    this.str = fork.str;
  }

  _fail(pattern) {
    if (!this.error) {
      this.error = new ParseError(this.str, pattern);
    }
    return Parser.FAILED;
  }

  _match(matcher) {
    assert(this.error === null);

    switch (typeof matcher) {
      case "string": {
        const len = matcher.length;
        const comparand = this.str.slice(0, len);
        if (comparand !== matcher) {
          return this._fail(matcher);
        }
        this.str = this.str.slice(len);
        return comparand;
      }

      case "function":
        return matcher(this);

      case "object":
        if (matcher instanceof RegExp) {
          const m = this.str.match(matcher);
          if (m == null) {
            return this._fail(matcher);
          } else if (m.index !== 0) {
            console.warn(
              `Warning: regular expression ${matcher} matched after``the beginning of the string. This match is ignored.`
            );
            return this._fail(matcher);
          }
          this.str = this.str.slice(m[0].length);
          return m.groups != null ? m.groups : m.length > 1 ? [...m] : m[0];
        }
      // Fall through.

      default:
        throw new Error(
          "First argument should be a function, string, or regular expression."
        );
    }
  }

  _expect(matcher) {
    if (this.error) return Parser.FAILED;
    return this._match(matcher);
  }

  expect(matcher) {
    let r = this._expect(matcher);
    const now = Date.now();
    if (!global.last || now - global.last > 1000) {
      global.last = now;
      console.log(this.str.length);
    }
    return r;
  }

  try(matcher, or_else) {
    if (this.error) return Parser.FAILED;
    const fork = this._fork();
    const result = fork.expect(matcher);
    if (fork.error !== null) return or_else;
    this._unfork(fork);
    return result;
  }

  skip(matcher) {
    this.expect(matcher);
    return this;
  }

  try_skip(matcher) {
    this.try(matcher);
    return this;
  }

  peek(matcher) {
    if (this.error) return Parser.FAILED;
    const fork = this._fork();
    const result = fork.expect(matcher);
    if (fork.error !== null) {
      this.error = fork.error;
    }
    return result;
  }

  try_peek(matcher, or_else) {
    if (this.error) return Parser.FAILED;
    const fork = this._fork();
    const result = fork.expect(matcher);
    if (fork.error !== null) return or_else;
    return result;
  }

  repeat(matcher) {
    if (this.error) return Parser.FAILED;
    let results = [];
    for (;;) {
      const fork = this._fork();
      const result = fork.expect(matcher);
      if (fork.error) {
        return results;
      } else {
        this._unfork(fork);
        results.push(result);
      }
    }
  }

  ok() {
    return this.error === null;
  }

  ratify(value) {
    if (this.error !== null) {
      throw this.error;
    } else {
      return value;
    }
  }
}
Parser.FAILED = Symbol("Parser.FAILED");

class Node {
  constructor(parser, parent) {
    this.parent = parent;
    this.children = [];
    this.parse_prefix(parser);
    this.parse(parser);
    parser.skip(/^\r?\n/);
    this.parse_children(parser);
  }

  parse(parser) {}

  parse_prefix(parser) {
    this.prefix = this.parent.parse_child_prefix(parser);
  }

  parse_child_prefix(parser) {
    const base = parser.expect(this.prefix);
    if (!parser.ok()) return;
    const extension = parser.expect(/^[|`]-/);
    if (!parser.ok()) return;
    return base + extension.replace(/[`\-]/g, " ");
  }

  parse_child(parser) {
    let kind = parser.peek(p => {
      this.parse_child_prefix(p);
      return p.expect(/^\w+/);
    });
    if (!parser.ok()) return;
    let ctor = node_type_map.get(kind);
    return parser.ratify(new ctor(parser, this));
  }

  parse_children(parser) {
    let children = parser.repeat(p => {
      p.peek(p => this.parse_child_prefix(p));
      if (!parser.ok()) return;
      return this.parse_child(p);
    });
    this.children = this.children.concat(children);
  }

  parse_address(parser) {
    return parser.skip(" ").expect(/^0x[\da-f]+/);
  }

  parse_name(parser) {
    this.name = parser.skip(" ").expect(/^[:\w]+/);
  }

  parse_type(parser) {
    return parser.skip(" ").expect(p => new Type(p));
  }

  parse_attributes(parser, attrs) {
    outer: while (attrs.length) {
      for (let i = 0; i < attrs.length; i++) {
        const attr = attrs[i];
        if (parser.try(p => p.skip(" ").expect(attr))) {
          this[attr] = true;
          attrs.splice(i, 1);
          continue outer;
        }
      }
      break;
    }
  }
}

class KindedNode extends Node {
  parse(parser) {
    super.parse(parser);
    this.kind = parser.expect(/^\w+/);
  }
}

class AddressableNode extends KindedNode {
  parse(parser) {
    super.parse(parser);
    this.address = this.parse_address(parser);
    this.prev = parser.try(p =>
      p.skip(" prev").expect(p => this.parse_address(p))
    );
  }
}

class SrcRangeNode extends AddressableNode {
  parse(parser) {
    super.parse(parser);
    this.source_range = parser.skip(" ").expect(p => new SourceRange(p));
  }
}

class SrcRangeLocNode extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
    this.source_location = parser.skip(" ").expect(p => new SourceLocation(p));
  }
}

class DeclNodeBase extends SrcRangeLocNode {
  parse(parser) {
    super.parse(parser);
    this.parse_attributes(parser, ["implicit"]);
  }
}

class NamedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.parse_name(parser);
  }
}

class TypedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.type = this.parse_type(parser);
  }
}

class NamedAndTypedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.parse_name(parser);
    this.type = this.parse_type(parser);
  }
}

class RecordNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.record_kind = parser
      .skip(" ")
      .expect(/^class|struct|union|interface|enum/);
    this.parse_name(parser);
    
    if (parser.try(p => p.skip(" ").expect("definition"))) {
      this.is_definition = true;
      this.definition = parser.expect(p => new RecordDefinition(p, this));
    } else {
      this.is_definition = false;
    }    
  }
}

class TypedNode extends AddressableNode {
  parse(parser) {
    super.parse(parser);
    this.type = parser.skip(" ").expect(p => new Type(p));
    this.parse_attributes(parser, [
      "sugar",
      "dependent",
      "instantiation_dependent",
      "variably_modified",
      "contains_unexpanded_pack",
      "imported"
    ]);
  }
}

class AttrNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
    this.parse_attributes(parser, ["Inherited", "Implicit"]);
  }
}

class TypeNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class ExprNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
    this.result_type = this.parse_type(parser);
  }
}

class StmtNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class OperatorNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class CommentNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class SpecializationNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class EnumNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class CleanupsNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class FieldNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class LiteralNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class FunctionNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class KindNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class ParmNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class AliasNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class TypedefNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class TranslationUnit extends DeclNodeBase {
  constructor(parser) {
    super(parser, null);
  }
  parse_prefix(parser) {
    this.prefix = "";
  }
}

const node_types = [
  class AccessSpecDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class AlwaysInlineAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ArraySubscriptExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class AttributedType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BinaryOperator extends OperatorNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BlockCommandComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BreakStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BuiltinTemplateDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BuiltinType extends TypedNode {},
  class PointerType extends TypedNode {},
  class CStyleCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXX11NoReturnAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXBindTemporaryExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXBoolLiteralExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXCatchStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXConstCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXConstructExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXConstructorDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXConversionDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDefaultArgExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDefaultInitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDeleteExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDependentScopeMemberExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDestructorDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXDynamicCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXForRangeStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXFunctionalCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXMemberCallExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXMethodDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXNewExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXNoexceptExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXNullPtrLiteralExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXOperatorCallExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXPseudoDestructorExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXRecord extends TypedNode {},
  class CXXRecordDecl extends RecordNodeBase {},
  class CXXReinterpretCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXScalarValueInitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXStaticCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXTemporaryObjectExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXThisExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXThrowExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXTryStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXTypeidExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXUnresolvedConstructExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CallExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ClassTemplateDecl extends NamedDeclNodeBase {},
  class ClassTemplatePartialSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ClassTemplateSpecialization extends SpecializationNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ClassTemplateSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CompoundAssignOperator extends OperatorNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CompoundStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConditionalOperator extends OperatorNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConstAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConstantArrayType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConstantExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DeclRefExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DeclStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DecltypeType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DependentNameType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DependentScopeDeclRefExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DependentTemplateSpecializationType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DeprecatedAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ElaboratedType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class EmptyDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Enum extends EnumNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class EnumConstantDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class EnumDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class EnumType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ExprWithCleanups extends CleanupsNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Field extends FieldNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FieldDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FinalAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FloatingLiteral extends LiteralNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ForStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FormatAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FriendDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FullComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Function extends FunctionNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FunctionDecl extends NamedAndTypedDeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.storage_class = parser.try(p =>
        p.skip(" ").expect(/^extern|^static/)
      );
    }
  },
  class FunctionProtoType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FunctionTemplateDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class IfStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ImplicitCastExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class IndirectFieldDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class InitListExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class InjectedClassNameType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class InlineCommandComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class IntegerLiteral extends LiteralNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Kind extends KindNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class LValueReferenceType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class LambdaExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class LinkageSpecDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.linkage = parser.skip(" ").expect(/^C\+\+|^C/);
    }
  },
  class MSNoVTableAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class MaterializeTemporaryExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class MaxFieldAlignmentAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class MemberExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NamespaceDecl extends NamedDeclNodeBase {},
  class NoAliasAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NoInlineAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NoThrowAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NonTypeTemplateParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NullStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class OverrideAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class PackExpansionExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParagraphComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParamCommandComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParenExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParenListExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParenType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParmVarDecl extends TypedDeclNodeBase {},
  class PragmaCommentDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class PragmaDetectMismatchDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class PureAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class QualType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class RValueReferenceType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class RecordType extends TypedNode {},
  class RestrictAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ReturnStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class SizeOfPackExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class StaticAssertDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class StringLiteral extends LiteralNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class SubstNonTypeTemplateParmExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class SubstTemplateTypeParmType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateSpecializationType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateTemplateParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateTypeParm extends ParmNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateTypeParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.type_kind = parser.skip(" ").expect(/^(class|typename)/);
      this.depth = parser.skip(" depth ").expect(/^\d+/);
      this.index = parser.skip(" index ").expect(/^\d+/);
      this.parse_name(parser);
    }
  },
  class TemplateTypeParmType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TextComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TranslationUnitDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeAlias extends AliasNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeAliasDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeAliasTemplateDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeTraitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeVisibilityAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
      this.visibility = parser.skip(" ").expect(/^Default|Hidden|Protected/);
    }
  },
  class Typedef extends TypedNode {},
  class TypedefDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.parse_attributes(parser, ["referenced", "used"]);
      this.parse_name(parser);
      this.type = parser.skip(" ").expect(p => new Type(p));
      parser.ratify(this);
    }
  },
  class TypedefType extends TypedNode {},
  class UnaryExprOrTypeTraitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnaryOperator extends OperatorNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnaryTransformType extends TypeNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnresolvedLookupExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnresolvedMemberExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnresolvedUsingTypenameDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnresolvedUsingValueDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UsingDecl extends NamedDeclNodeBase {},
  class UsingShadowDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.target_kind = parser.skip(" ").expect(/Typedef|Function/);
      this.target_address = this.parse_address(parser);
      // The rest is redundant.
      parser.skip(" ").skip(/.*/);
    }
  },
  class VarDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VarTemplateDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VarTemplatePartialSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VarTemplateSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VerbatimBlockComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VerbatimBlockLineComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VisibilityAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class WarnUnusedResultAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class WhileStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  }
];

var node_type_map = new Map(node_types.map(cl => [cl.name, cl]));

class Type {
  constructor(parser) {
    Object.assign(this, this.parse(parser));
  }

  parse(parser) {
    const name = parser.skip("'").expect(/^[^']+/);
    parser.skip("'");
    const desugared = parser.try(p => {
      const r = p.skip(":").expect(p => new Type(p));
    });
    return { name, desugared };
  }
}

class SourceRange {
  constructor(parser) {
    Object.assign(this, this.parse(parser));
  }

  parse(parser) {
    const start = parser.skip("<").expect(p => new SourceLocation(p));
    const end = parser.try(
      p => p.skip(", ").expect(p => new SourceLocation(p)),
      start
    );
    parser.skip(">");
    return { start, end };
  }
}

class SourceLocation {
  constructor(parser) {
    Object.assign(this, this.parse(parser));
  }

  parse(parser) {
    if (parser.try("<invalid sloc>")) {
      return { valid: false };
    }
    let valid_fields =
      parser.try(/^col:(?<col>\d+)/) ||
      parser.try(/^line:(?<line>\d+):(?<col>\d+)/) ||
      parser.try(/^(?<file>.+?):(?<line>\d+):(?<col>\d+)/);
    if (valid_fields) {
      return { valid: true, ...valid_fields };
    }
  }
}

class RecordDefinition {
  constructor(parser, parent) {
    this._parent = parent;
    this.parse(parser);
    console.log(this);
  }

  parse(parser) {
    const top_level_flags = parser.expect(p => this.parse_top_level_flags(p));
    console.log("ok=",parser.str.slice(0,100));
    Object.assign(this, parser.ratify(top_level_flags));

    const subset_parser_fns = [
      this.parse_default_constructor_flags,
      this.parse_copy_constructor_flags,
      this.parse_copy_assignment_flags,
      this.parse_move_assignment_flags,
      this.parse_move_constructor_flags,
      this.parse_destructor_flags
    ];
    this.parse_unordered(
      parser,
      subset_parser_fns.map(parse_fn => {
        parse_fn = parse_fn.bind(this);
        return {
          match: parse_fn,
          on_match: r => Object.assign(this, r),
          on_unmatch: () => parser.expect(parse_fn)
        };
      })
    );
  }

  parse_top_level_flags(parser) {
    parser
      .skip(/^\r?\n/)
      .skip(this._parent.prefix)
      .skip(/^[`|]-/)
      .skip("DefinitionData");
    return this.parse_flags(parser, [
      "parsing_base_specifiers", // isParsingBaseSpecifiers

      "generic", // isGenericLambda
      "lambda", // isLambda

      "pass_in_registers", // canPassInRegisters
      "empty", // isEmpty
      "aggregate", // isAggregate
      "standard_layout", // isStandardLayout
      "trivially_copyable", // isTriviallyCopyable
      "pod", // isPOD
      "trivial", // isTrivial
      "polymorphic", // isPolymorphic
      "abstract", // isAbstract
      "literal", // isLiteral

      "has_user_declared_ctor", // hasUserDeclaredConstructor
      "has_constexpr_non_copy_move_ctor", // hasConstexprNonCopyMoveConstructor
      "has_mutable_fields", // hasMutableFields
      "has_variant_members", // hasVariantMembers
      "can_const_default_init" // allowConstDefaultInit
    ]);
  }

  parse_nested_flag_sets(parser, subset_parsers) {
    const results = {};

    return results;
  }

  parse_nested_flags(parser, identifier, flags) {
    const field_name = identifier
      .replace(/^[A-Z]/, l => l.toLowerCase())
      .replace(/[A-Z]/g, l => "_" + l.toLowerCase());
    parser
      .skip(/^\r?\n/)
      .skip(this._parent.prefix)
      .skip(/^[| ] /)
      .skip(/^[`|]-/)
      .skip(identifier);
    return { [field_name]: this.parse_flags(parser, flags) };
  }

  parse_default_constructor_flags(parser) {
    return this.parse_nested_flags(parser, "DefaultConstructor", [
      "exists", // hasDefaultConstructor
      "trivial", // hasTrivialDefaultConstructor
      "non_trivial", // hasNonTrivialDefaultConstructor
      "user_provided", // hasUserProvidedDefaultConstructor
      "constexpr", // hasConstexprDefaultConstructor
      "needs_implicit", // needsImplicitDefaultConstructor
      "defaulted_is_constexpr" // defaultedDefaultConstructorIsConstexpr
    ]);
  }

  parse_copy_constructor_flags(parser) {
    return this.parse_nested_flags(parser, "CopyConstructor", [
      "simple", // hasSimpleCopyConstructor
      "trivial", // hasTrivialCopyConstructor
      "non_trivial", // hasNonTrivialCopyConstructor
      "user_declared", // hasUserDeclaredCopyConstructor
      "has_const_param", // hasCopyConstructorWithConstParam
      "needs_implicit", // needsImplicitCopyConstructor
      "needs_overload_resolution", // needsOverloadResolutionForCopyConstructor
      "defaulted_is_deleted", // defaultedCopyConstructorIsDeleted
      "implicit_has_const_param" // implicitCopyConstructorHasConstParam
    ]);
  }

  parse_move_constructor_flags(parser) {
    return this.parse_nested_flags(parser, "MoveConstructor", [
      "exists", // hasMoveConstructor
      "simple", // hasSimpleMoveConstructor
      "trivial", // hasTrivialMoveConstructor
      "non_trivial", // hasNonTrivialMoveConstructor
      "user_declared", // hasUserDeclaredMoveConstructor
      "needs_implicit", // needsImplicitMoveConstructor
      "needs_overload_resolution", // needsOverloadResolutionForMoveConstructor
      "defaulted_is_deleted" // defaultedMoveConstructorIsDeleted
    ]);
  }

  parse_copy_assignment_flags(parser) {
    return this.parse_nested_flags(parser, "CopyAssignment", [
      "trivial", // hasTrivialCopyAssignment
      "non_trivial", // hasNonTrivialCopyAssignment
      "has_const_param", // hasCopyAssignmentWithConstParam
      "user_declared", // hasUserDeclaredCopyAssignment
      "needs_implicit", // needsImplicitCopyAssignment
      "needs_overload_resolution", // needsOverloadResolutionForCopyAssignment
      "implicit_has_const_param" // implicitCopyAssignmentHasConstParam
    ]);
  }

  parse_move_assignment_flags(parser) {
    return this.parse_nested_flags(parser, "MoveAssignment", [
      "exists", // hasMoveAssignment
      "simple", // hasSimpleMoveAssignment
      "trivial", // hasTrivialMoveAssignment
      "non_trivial", // hasNonTrivialMoveAssignment
      "user_declared", // hasUserDeclaredMoveAssignment
      "needs_implicit", // needsImplicitMoveAssignment
      "needs_overload_resolution" // needsOverloadResolutionForMoveAssignment
    ]);
  }

  parse_destructor_flags(parser) {
    return this.parse_nested_flags(parser, "Destructor", [
      "simple", // hasSimpleDestructor
      "irrelevant", // hasIrrelevantDestructor
      "trivial", // hasTrivialDestructor
      "non_trivial", // hasNonTrivialDestructor
      "user_declared", // hasUserDeclaredDestructor
      "needs_implicit", // needsImplicitDestructor
      "needs_overload_resolution", // needsOverloadResolutionForDestructor
      "defaulted_is_deleted" // defaultedDestructorIsDeleted
    ]);
  }

  parse_unordered(parser, items) {
    outer: while (items.length > 0) {
      for (let i = 0; i < items.length; i++) {
        const item = items[i];
        const result = parser.try(p => item.match(p));
        if (result != null) {
          item.on_match(result);
          items.splice(i, 1);
          continue outer;
        }
      }
      break;
    }
    for (const item of items) {
      item.on_unmatch();
    }
  }

  parse_flags(parser, flags) {
    const result = {};
    this.parse_unordered(
      parser,
      flags.map(flag => ({
        match: parser => parser.skip(" ").expect(flag) === flag,
        on_match: _ => (result[flag] = true),
        on_unmatch: () => (result[flag] = false)
      }))
    );
    return result;
  }
}

main();
