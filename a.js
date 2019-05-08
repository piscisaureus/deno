let { readFileSync } = require("fs");
require("util").inspect.defaultOptions.depth = null;
require("util").inspect.defaultOptions.maxArrayLength = null;
//Error.stackTraceLimit = Infinity;

function main() {
  let ast_dump = readFileSync("o3", "utf8");
  let parser = new Parser(ast_dump);
  let result = parser.expect(p => new TranslationUnitDecl(p));
  parser.skip(/^$/);
  console.log(parser.ratify(result));
}

class ParseError extends Error {
  constructor(input, pattern) {
    input = JSON.stringify(input.slice(0, 200));
    pattern =
      typeof pattern === "string" ? JSON.stringify(pattern) : `${pattern}`;
    super(`Parse error\n` + `  pattern: ${pattern}\n` + `  input:   ${input}`);
    //super("Parse error");
  }
}

class DebugHistory {
  static log(...args) {
    const { history, max_entries } = DebugHistory;
    history.push(args);
    if (history.length >= max_entries * 2) {
      history.splice(0, history.length - max_entries);
    }
  }

  static dump() {
    const { history, max_entries } = DebugHistory;
    for (const args of history.slice(-max_entries)) {
      console.error(...args);
    }
  }
}
DebugHistory.history = [];
DebugHistory.max_entries = 25;
process.on("exit", () => DebugHistory.dump());

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
    let rest = parser.expect(/^.*/);
    if (rest.length) {
      console.error(this.constructor.name, " == ", rest);
    }
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
    const ctor = parser.peek(p => {
      if (this.parse_child_prefix(p) == null) {
        return;
      }
      const kind = p.try(p => this.parse_kind(p));
      if (kind != null) {
        const ctor = node_type_map.get(kind);
        if (!ctor) {
          throw new Error(`No constructor for node kind '${kind}'`);
        }
        return ctor;
      }
      const null_node = p.try(p => this.parse_null_node(p));
      if (null_node != null) {
        return NullNode;
      }
    });
    DebugHistory.log(ctor, parser.try_peek(/^.*/));
    if (!parser.ok()) return;
    //if (ctor == null) return;
    return new ctor(parser, this);
  }

  parse_children(parser) {
    let children = parser.repeat(p => {
      p.peek(p => this.parse_child_prefix(p));
      if (!parser.ok()) return;
      return this.parse_child(p);
    });
    this.children = this.children.concat(children);
  }

  parse_kind(parser) {
    return parser.try_skip(" ").expect(/^[A-Z]\w*/);
  }

  parse_null_node(parser) {
    return parser.expect("<<<NULL>>>");
  }

  parse_address(parser) {
    return parser.try_skip(" ").expect(/^0x[\da-f]+/);
  }

  parse_name(parser) {
    let name = parser.skip(" ").expect(/^(?:operator\s*.[^\s\(]*|::|~|\w)+<?/);
    if (!parser.ok()) return;
    if (!/</.test(name) || /operator/.test(name)) return name;

    const count = re => {
      let matches = name.match(re);
      return (matches && matches.length) || 0;
    };
    while (count(/</g) > count(/>/g)) {
      name += parser.expect(/^.*?>/);
    }
    return name;
  }

  parse_type(parser) {
    return parser.try_skip(" ").expect(p => new Type(p));
  }

  parse_node_ref(parser) {
    return parser.skip(" ").expect(p => new NodeRef(p));
  }

  parse_position(parser) {
    return parser.skip(" ").expect(p => new TemplateParameterPosition(p));
  }

  parse_parameter_pack_indicator(parser) {
    return Boolean(parser.try(" ..."));
  }

  parse_type_qualifiers(parser) {
    return this.parse_flags(parser, ["const", "resrict", "volatile"]);
  }

  parse_storage_class(parser) {
    return parser.try(
      p => p.skip(" ").expect(/^(?:auto|extern|static|register)/),
      "none"
    );
  }

  parse_tls_kind(parser) {
    return parser.try(
      p => p.skip(" ").expect(/^(?:tls|tls_dynamic)\b/),
      "none"
    );
  }

  parse_init_style(parser) {
    return parser.try(
      p => p.skip(" ").expect(/^(?:cinit|callinit|listinit)\b/),
      "none"
    );
  }

  parse_access_specifier(parser) {
    return parser.try(
      p => p.try_skip(" ").expect(/^(?:private|protected|public)/),
      "none"
    );
  }

  parse_operator(parser) {
    let operator = parser.skip(" '").expect(/^[^'\w]+/);
    parser.skip("'");
    return operator;
  }

  parse_flags(parser, flags) {
    outer: while (flags.length) {
      for (let i = 0; i < flags.length; i++) {
        const flag = flags[i];
        if (
          parser.try(p => {
            p.skip(" ");
            p.expect(flag);
            p.peek(/^\s/);
            return true;
          })
        ) {
          this[flag] = true;
          flags.splice(i, 1);
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
    this.kind = parser.expect(this.constructor.name);
  }
}

class NullNode extends Node {
  parse(parser) {
    super.parse(parser);
    this.parse_null_node(parser);
  }
}

class AddressableNode extends KindedNode {
  parse(parser) {
    super.parse(parser);
    this.address = this.parse_address(parser);
    this.semantic_parent = parser.try(p =>
      p.skip(" parent").expect(p => this.parse_node_ref(p))
    );
    this.prev = parser.try(p =>
      p.skip(" prev").expect(p => this.parse_node_ref(p))
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
    this.parse_flags(parser, ["implicit", "referenced", "used", "constexpr"]);
  }
}

class NamedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.name = this.parse_name(parser);
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
    this.name = this.parse_name(parser);
    this.type = this.parse_type(parser);
  }
}

class CallableDeclBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.name = this.parse_name(parser);
    this.type = this.parse_type(parser);
    this.storage_class = this.parse_storage_class(parser);
    this.parse_flags(parser, [
      "default",
      "delete",
      "inline",
      "pure",
      "trivial",
      "virtual"
    ]);

    const noexcept = parser.try(
      p => {
        p.skip(" ").expect("noexcept-");
        return {
          noexcept_spec: p.expect(/^\w+/),
          noexcept_source: this.parse_node_ref(p)
        };
      },
      { noexcept_spec: undefined, noexcept_source: undefined }
    );
    Object.assign(this, noexcept);

    this.overrides = [];
    parser.try(p => {
      p.expect(/^\r?\n/);
      this.parse_child_prefix(p);
      p.expect("Overrides: [");
      if (!p.ok()) return;

      do {
        this.overrides.push(this.parse_node_ref(p));
        this.parse_name(p); // Redundant.
        this.parse_type(p); // Redundant.
        assert(p.ok());
      } while (p.try(","));
      p.expect(" ]");
    });
  }
}

class RecordNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.record_kind = parser
      .skip(" ")
      .expect(/^(?:class|struct|union|interface|enum)/);

    // Umbiguity is unavoidable here - just never call your class 'definition'.
    // TODO: disambiguate using color output?
    if (!parser.try_peek(/^ definition\r?\n/)) {
      this.name = this.parse_name(parser);
    }

    if (parser.try(p => p.skip(" ").expect("definition"))) {
      this.is_definition = true;
      this.definition = parser.expect(p => new RecordDefinition(p, this));
      this.bases = parser.repeat(p => new CXXBaseSpecifier(p, this));
    } else {
      this.is_definition = false;
    }
  }
}

class TypedNode extends AddressableNode {
  parse(parser) {
    super.parse(parser);
    this.type = parser.skip(" ").expect(p => new Type(p));
    this.parse_flags(parser, [
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
    this.parse_flags(parser, ["Inherited", "Implicit"]);
  }
}

class SimpleAttr extends AttrNodeBase {
  parse(parser) {
    super.parse(parser);
    this.attr = parser.skip(" ").expect(/^[\w]+/);
  }
}

class ExprNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
    this.type = this.parse_type(parser);
    this.value_kind = parser.try(
      p => p.skip(" ").expect(/^(?:lvalue|xvalue)/),
      "rvalue"
    );
  }
}

class CastExprBase extends ExprNodeBase {
  parse_cast(parser, is_implicit_cast = false) {
    // This function SETS the cast_kind and base_path fields.
    // It also SETS the `part_of_explicit_cast` if `is_implicit_cast` is set.
    // It RETURNS the cast description which may need further processing by the caller.
    parser.try_skip(" ");
    let line = parser.expect(/^.*/);

    if (is_implicit_cast) {
      const m0 = line.match(/^(?<line>.*) (?<flag>part_of_explicit_cast)$/);
      this.part_of_explicit_cast = !!m0;
      line = m0 ? m0.groups.line : line;
    }

    const m1 = line.match(
      /^((?<description>.*) )?<(?<cast_kind>(Unchecked)?(BaseToDerived|DerivedToBase)) \((?<base_path>.+)\)>$/
    );
    if (m1) {
      const { description, cast_kind, base_path } = m1.groups;
      this.cast_kind = cast_kind;
      this.base_path = base_path.split(" -> ");
      return description || "";
    }

    const m2 = line.match(/^((?<description>.*) )?<(?<cast_kind>[a-zA-Z]+)>$/);
    if (m2) {
      const { description, cast_kind } = m2.groups;
      this.cast_kind = cast_kind;
      this.base_path = undefined;
      return description || "";
    }

    throw new Error(`Could not parse cast. ${line}`);
  }
}

class ImplicitCastExprBase extends CastExprBase {
  parse(parser) {
    super.parse(parser);
    const description = this.parse_cast(parser, true);
    assert(description === "");
  }
}

class CXXNamedCastExprBase extends CastExprBase {
  parse(parser) {
    super.parse(parser);
    const description = this.parse_cast(parser);
    // The type inside the angle brackets (static_cast<this_type>) is redundant.
    // It's the same as the result type of this expression (which is parsed by
    // our base class).
    this.cast_name = /^[a-z_]+_cast(?=<.+>$)/.exec(description)[0];
  }
}

class StmtNodeBase extends SrcRangeNode {
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

class CleanupsNodeBase extends SrcRangeNode {
  parse(parser) {
    super.parse(parser);
  }
}

class LiteralNodeBase extends ExprNodeBase {
  parse(parser) {
    super.parse(parser);
    this.source = parser.skip(" ").expect(/^.*\S/);
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

class TranslationUnitDecl extends DeclNodeBase {
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
      this.access = this.parse_access_specifier(parser);
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
  class AttributedType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class BinaryOperator extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.operator = this.parse_operator(parser);
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
  class BuiltinTemplateDecl extends NamedDeclNodeBase {},
  class BuiltinType extends TypedNode {},
  class PointerType extends TypedNode {},
  class CStyleCastExpr extends ImplicitCastExprBase {},
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
  class CXXBoolLiteralExpr extends LiteralNodeBase {
    parse(parser) {
      super.parse(parser);
      this.value = JSON.parse(this.source);
    }
  },
  class CXXCatchStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXConstCastExpr extends CXXNamedCastExprBase {},
  class CXXConstructExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.constructor_type = this.parse_type(parser);
      this.parse_flags(parser, [
        "elidable",
        "list",
        "std::initializer_list",
        "zeroing"
      ]);
    }
  },
  class CXXConstructorDecl extends CallableDeclBase {},
  class CXXCtorInitializer extends KindedNode {
    parse(parser) {
      super.parse(parser);
      const field = parser.try(p => {
        this.parse_kind(p); // Redundant
        const ref = this.parse_node_ref(p);
        p.skip(/^.*/); // Skip redundant info which replicated from the referenced field.
        return ref;
      });
      if (field) {
        // Initializer initializes a class member.
        this.field = field;
      } else {
        // Initializer intializes a base class or delegates to another constructor.
        // TODO: can we distinguish between those?
        this.base = this.parse_type(parser);
      }
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
  class CXXDestructorDecl extends CallableDeclBase {},
  class CXXDynamicCastExpr extends CXXNamedCastExprBase {},
  class CXXForRangeStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXFunctionalCastExpr extends CastExprBase {
    parse(parser) {
      super.parse(parser);
      const description = this.parse_cast(parser);
      // Further information in the description is redundant.
      assert(/^functional cast to .*\S$/.test(description));
    }
  },
  class CXXMemberCallExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXMethodDecl extends CallableDeclBase {},
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
  class CXXReinterpretCastExpr extends CXXNamedCastExprBase {},
  class CXXScalarValueInitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CXXStaticCastExpr extends CXXNamedCastExprBase {},
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
  class ClassTemplatePartialSpecializationDecl extends RecordNodeBase {},
  class ClassTemplateSpecialization extends TypedNode {},
  class ClassTemplateSpecializationDecl extends RecordNodeBase {},
  class CompoundAssignOperator extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class CompoundStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConditionalOperator extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConstAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ConstantArrayType extends TypedNode {
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
      this.parse_kind(parser); // Redundant info.
      this.decl = this.parse_node_ref(parser);
      parser.skip(/^.*/); // The rest of the line is also redundant.
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
  class DependentNameType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DependentScopeDeclRefExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DependentTemplateSpecializationType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class DeprecatedAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
      // There seems to be an always-empty string after the message.
      // Unclear what this is for.
      this.message = parser.expect(/^ "(?<message>.*)" ""/).message;
    }
  },
  class ElaboratedType extends TypedNode {},
  class EmptyDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Enum extends TypedNode {},
  class EnumConstantDecl extends NamedAndTypedDeclNodeBase {},
  class EnumDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.scope = parser.try(
        p => p.skip(" ").expect(/^(?:class|struct)/),
        "unscoped"
      );
      this.name = parser.try(p => this.parse_name(p));
      this.type = parser.try(p => this.parse_type(p));
    }
  },
  class EnumType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ExprWithCleanups extends CleanupsNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class Field extends AddressableNode {
    parse(parser) {
      super.parse(parser);
      parser.expect(" '");
      this.name = parser.expect(/^[^']*/);
      parser.expect("'");
      this.type = this.parse_type(parser);
    }
  },
  class FieldDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.name = parser.try(p => this.parse_name(p));
      this.type = this.parse_type(parser);
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
  class Function extends AddressableNode {
    parse(parser) {
      super.parse(parser);
      parser.expect(" '");
      this.name = parser.expect(/^[^']+/);
      parser.expect("'");
      this.type = this.parse_type(parser);
    }
  },
  class FunctionDecl extends CallableDeclBase {},
  class FunctionProtoType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class FunctionTemplateDecl extends NamedDeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class IfStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ImplicitCastExpr extends ImplicitCastExprBase {},
  class IndirectFieldDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class InitListExpr extends ExprNodeBase {
    parse_children(parser) {
      // Todo: don't auto-consume newlines in parse().
      let child = parser.try(p => new ImplicitValueInitExpr(p, this));
      if (child && child.label === "array_filler") {
        this.array_filler = child;
      } else if (child) {
        this.children.push(child);
      }
      super.parse_children(parser);
    }
  },
  class InjectedClassNameType extends TypedNode {
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
  class LValueReferenceType extends TypedNode {
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
      this.alignment = Number(parser.skip(" ").expect(/^\d+/));
    }
  },
  class MemberExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class NamespaceDecl extends NamedDeclNodeBase {
    parse(parser) {
      super.parse(parser);

      this.original = parser.try(p => {
        p.expect(/^\r?\n/);
        this.parse_child_prefix(p);
        p.expect("original");
        this.parse_kind(p); // Redundant.
        const original = this.parse_node_ref(p);
        parser.expect(/^.*/); // Redundant.
        return original;
      });
    }
  },
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
      this.type = this.parse_type(parser);
      this.position = this.parse_position(parser);
      this.is_parameter_pack = this.parse_parameter_pack_indicator(parser);
      this.name = parser.try(p => this.parse_name(p));
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
  class ParenType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ParmVarDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.name = parser.try(p => this.parse_name(p));
      this.type = this.parse_type(parser);
    }
  },
  class PragmaCommentDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class PragmaDetectMismatchDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      Object.assign(
        this,
        parser.skip(" ").expect(/"(?<name>.+)" "(?<value>.*)"/)
      );
    }
  },
  class PureAttr extends AttrNodeBase {},
  class QualType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      this.parse_type_qualifiers(parser);
    }
  },
  class RValueReferenceType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class RecordType extends TypedNode {},
  class RestrictAttr extends SimpleAttr {},
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
  class SubstTemplateTypeParmType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateSpecializationType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TemplateTemplateParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.position = this.parse_position(parser);
      this.is_parameter_pack = this.parse_parameter_pack_indicator(parser);
      this.name = parser.try(p => this.parse_name(p));
    }
  },
  class TemplateTypeParm extends TypedNode {},
  class TemplateTypeParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.type_kind = parser.skip(" ").expect(/^(?:class|typename)/);
      this.position = this.parse_position(parser);
      this.is_parameter_pack = this.parse_parameter_pack_indicator(parser);
      this.name = parser.try(p => this.parse_name(p));
    }
  },
  class TemplateTypeParmType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      this.position = this.parse_position(parser);
    }
  },
  class TemplateArgument extends KindedNode {
    parse(parser) {
      super.parse(parser);
      this.kind = parser
        .skip(" ")
        .expect(
          /^(?:decl|expr|integral|null|nullptr|pack|template|expansion|template|type)/
        );

      switch (this.kind) {
        case "type":
          this.type = this.parse_type(parser);
          break;
        case "integral":
          this.integral = parser.skip(" ").expect(/^\d+/);
          break;
      }

      this.inherited_default = new TemplateArgumentInheritedDefault(
        parser,
        this
      );
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
  class TypeAlias extends TypedNode {},
  class TypeAliasDecl extends NamedAndTypedDeclNodeBase {},
  class TypeAliasTemplateDecl extends NamedDeclNodeBase {},
  class TypeTraitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class TypeVisibilityAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
      this.type_visibility = parser
        .skip(" ")
        .expect(/^Default|Hidden|Protected/);
    }
  },
  class Typedef extends TypedNode {},
  class TypedefDecl extends NamedAndTypedDeclNodeBase {},
  class TypedefType extends TypedNode {},
  class UnaryExprOrTypeTraitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.operator = parser.skip(" ").expect(/^[\w]+/);
      this.argument_type = this.parse_type(parser);
    }
  },
  class UnaryOperator extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.attachment = parser.skip(" ").expect(/^(?:prefix|postfix)/);
      this.operator = this.parse_operator(parser);
      this.can_overflow = !parser.try(p =>
        p.skip(" ").expect("cannot overflow")
      );
    }
  },
  class UnaryTransformType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class UnresolvedLookupExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.unknown = parser.skip(" ").expect(/^.*/);
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
      this.parse_kind(parser); // Redundant.
      this.target = this.parse_node_ref(parser);
      parser.skip(" ").skip(/^.*/); // Redundant.
    }
  },
  class VarDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.name = this.parse_name(parser);
      this.type = this.parse_type(parser);
      this.storage_class = this.parse_storage_class(parser);
      this.tls_kind = this.parse_tls_kind(parser);
      this.parse_flags(parser, ["nrvo", "inline", "constexpr"]);
      this.init_style = this.parse_init_style(parser);
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
  class WarnUnusedResultAttr extends SimpleAttr {},
  class WhileStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  }
];

var node_type_map = new Map(node_types.map(cl => [cl.name, cl]));

class ImplicitValueInitExpr extends ExprNodeBase {
  // This type may be have the 'array_filler:' label.
  parse_prefix(parser) {
    super.parse_prefix(parser);
    this.label = parser.try(p => {
      const label = p.expect(/^[a-z_]+/);
      p.expect(": ");
      return label;
    });
  }
}

class Type {
  constructor(parser) {
    Object.assign(this, this.parse(parser));
  }

  static construct(props = {}) {
    // TODO: clean this up.
    return Object.assign(Object.create(Type.prototype), props);
  }

  parse(parser) {
    const name = parser.skip("'").expect(/^[^']*/);
    parser.skip("'");
    const desugared = parser.try(p => {
      return p.skip(":").expect(p => new Type(p));
    });
    return { name, desugared };
  }
}

class NodeRef {
  constructor(parser) {
    this.parse(parser);
  }

  parse(parser) {
    this.address = Node.prototype.parse_address(parser);
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

class TemplateParameterPosition {
  constructor(parser) {
    this.parse(parser);
  }

  parse(parser) {
    parser.skip("depth ");
    this.depth = Number(parser.expect(/^\d+/));
    parser.skip(" index ");
    this.index = Number(parser.expect(/^\d+/));
  }
}

class RecordDefinition {
  constructor(parser, parent) {
    this._parent = parent;
    this.parse(parser);
  }

  parse(parser) {
    const top_level_flags = parser.expect(p => this.parse_top_level_flags(p));
    Object.assign(this, top_level_flags);

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

class CXXBaseSpecifier {
  constructor(parser, parent) {
    this._parent = parent;
    this.parse(parser);
  }

  parse(parser) {
    parser
      .skip(/^\r?\n/)
      .skip(this._parent.prefix)
      .skip(/^[`|]-/);

    this.virtual = Boolean(parser.try("virtual"));
    this.access = Node.prototype.parse_access_specifier(parser);
    this.type = Node.prototype.parse_type(parser);
    this.is_pack_expansion = Node.prototype.parse_parameter_pack_indicator(
      parser
    );
  }
}

class TemplateArgumentInheritedDefault {
  constructor(parser, parent) {
    this._parent = parent;
    this.parse(parser);
  }

  parse(parser) {
    Object.assign(
      this,
      parser.try(p => this.parse_reference(p), {
        status: "none",
        origin: undefined
      })
    );
  }

  parse_reference(parser) {
    parser.expect(/^\r?\n/);
    parser.expect(this._parent.prefix);
    parser.expect(/^[`|]-/);

    let status;
    switch (parser.expect(/^(?:inherited from|previous)/)) {
      case "inherited from":
        status = "active";
        break;
      case "previous":
        status = "overridden";
        break;
      default:
        assert(!parser.ok());
        return;
    }

    parser.skip(" ");
    Node.prototype.parse_kind(parser); // Redundant.
    const origin = Node.prototype.parse_node_ref(parser);
    parser.skip(/^.*/); // Redundant.

    return { status, origin };
  }
}

main();
