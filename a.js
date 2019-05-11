let { readFileSync } = require("fs");
require("util").inspect.defaultOptions.depth = null;
require("util").inspect.defaultOptions.maxArrayLength = null;
//Error.stackTraceLimit = Infinity;

const assign = Object.assign;

function main() {
  let ast_dump = readFileSync(process.argv[2] || "o3", "utf8");
  let parser = new ClangAstDumpParser(ast_dump);
  let result = parser.parse_node();
  parser.skip(/^\r?\n?$/);
  console.log(result);
  Type.dumpIndex();
}

class DebugHistory {
  static log(non_match) {
    const { history, max_entries } = DebugHistory;
    history.push(non_match);
    if (history.length >= max_entries * 2) {
      history.splice(0, history.length - max_entries);
    }
  }

  static dump() {
    const { history, max_entries } = DebugHistory;
    for (const non_match of history.slice(-max_entries)) {
      console.error(non_match.get_message());
    }
  }
}
DebugHistory.history = [];
DebugHistory.max_entries = 25;
process.on("exit", () => DebugHistory.dump());

function assert(condition, message) {
  if (!condition)
    throw new Error(
      "Assertion failed" + (message !== undefined ? `: ${message}` : "")
    );
}

function fatal(message) {
  throw new Error(
    "Fatal error" + (message !== undefined ? `: ${message}` : "")
  );
}

class ParseError extends Error {}

class NoMatch {
  constructor(pattern, str, orig) {
    this.pattern = pattern;
    this.str = str;
    this.orig = orig;
    DebugHistory.log(this);
  }

  get_message() {
    const offset = this.orig.length - this.str.length;
    const $ = val =>
      val instanceof RegExp ? val.toString() : JSON.stringify(val);
    return (
      "Parse error\n" +
      `  pattern: ${$(this.pattern)}\n` +
      `    found: ... ${$(this.orig.slice(0, offset).slice(-80))}\n` +
      `           ==> ${$(this.str.slice(0, 80))} ...`
    );
  }

  throw() {
    throw new ParseError(this.get_message());
  }
}

class Parser {
  constructor(str) {
    this.str = str === undefined ? "" : `${str}`;
    this.orig = str;
    this.is_root = true;
  }

  _fork() {
    const fork = Object.create(this.constructor.prototype);
    Object.assign(fork, { str: this.str, orig: this.orig, is_root: false });
    return fork;
  }

  _unfork(fork) {
    this.str = fork.str;
  }

  _fail(pattern) {
    throw new NoMatch(pattern, this.str, this.orig);
  }

  _catch_try(err, is_try) {
    if (err instanceof NoMatch) {
      if (is_try) return;
      if (this.is_root) {
        err.throw();
      }
    }
    throw err;
  }

  _match(matcher, is_try) {
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
          if (m.groups != null) {
            return m.groups;
          } else if (m.length === 1) {
            return m[0];
          } else if (m.length === 2) {
            return m[1];
          } else {
            throw new Error("Please use named capture groups");
          }
        }
      // Fall through.

      default:
        throw new Error(
          `First argument should be a function, string, or regular expression. ` +
            `It is a ${typeof matcher} (${matcher}) instead.`
        );
    }
  }

  _expect(matcher) {
    try {
      return this._match(matcher);
    } catch (err) {
      this._catch_try(err, false);
    }
  }

  expect(matcher) {
    let r = this._expect(matcher);
    const now = Date.now();
    if (!global.last || now - global.last > 1000) {
      global.last = now;
      console.error(this.str.length);
    }
    return r;
  }

  try(matcher, or_else) {
    const fork = this._fork(true);
    try {
      const result = fork.expect(matcher);
      this._unfork(fork);
      return result;
    } catch (err) {
      this._catch_try(err, true);
      return or_else;
    }
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
    return this._fork().expect(matcher);
  }

  try_peek(matcher, or_else) {
    return this._fork().try(matcher);
  }

  repeat(matcher) {
    let results = [];
    for (;;) {
      const fork = this._fork(true);
      try {
        const result = fork.expect(matcher);
        this._unfork(fork);
        results.push(result);
      } catch (err) {
        this._catch_try(err, true);
        return results;
      }
    }
  }
}

class ClangAstDumpParser extends Parser {
  constructor(str) {
    super(str);
    this.prefix = "";
  }

  _fork() {
    const fork = super._fork();
    fork.prefix = this.prefix;
    return fork;
  }

  parse_leaf(matcher) {
    const fork = this._fork();
    fork.prefix = fork.parse_prefix(this.prefix);
    const result = fork.expect(matcher);
    this._unfork(fork);
    return result;
  }

  try_parse_leaf(matcher) {
    return this.try(p => p.parse_leaf(matcher));
  }

  parse_prefix(parent_prefix) {
    this.expect(/\r?\n/);
    return (
      this.expect(parent_prefix) + this.expect(/^[|`]-/).replace(/[`\-]/g, " ")
    );
  }

  parse_kind() {
    return this.try_skip(" ").expect(/^(?:[A-Z]\w*\b|<<<NULL>>>)/);
  }

  parse_node() {
    const kind = this.parse_kind();
    const ctor = node_type_map.get(kind);
    assert(ctor != null, `No constructor for '${kind}'`);
    const node_data = {
      kind,
      children: [],
      ...new ctor(this)
    };
    let child;
    while ((child = this.try(p => p.parse_child_node()))) {
      node_data.children.push(child);
    }
    return node_data;
  }

  parse_child_node() {
    return this.parse_leaf(p => p.parse_node());
  }

  parse_address() {
    return this.try_skip(" ").expect(/^0x[\da-f]+/);
  }

  parse_name() {
    let name = this.try_skip(" ").expect(
      /^(?:operator\s*.[^\s\(]*|::|~|\w)+<?/
    );
    if (!/</.test(name) || /operator/.test(name)) return name;

    const count = re => {
      let matches = name.match(re);
      return (matches && matches.length) || 0;
    };
    while (count(/</g) > count(/>/g)) {
      name += this.expect(/^.*?>/);
    }
    return name;
  }

  parse_type() {
    return this.try_skip(" ").expect(p => new Type(p));
  }

  parse_node_ref() {
    return this.skip(" ").expect(p => new NodeRef(p));
  }

  parse_position() {
    return this.skip(" ").expect(p => new TemplateParameterPosition(p));
  }

  parse_parameter_pack_indicator() {
    return Boolean(this.try(" ..."));
  }

  parse_type_qualifiers() {
    return this.parse_flags(["const", "restrict", "volatile"]);
  }

  parse_array_type() {
    if (this.try(" static")) return "static";
    if (this.try(" *")) return "star";
    return "normal";
  }

  parse_visibility() {
    return this.skip(" ").expect(/^Default|Hidden|Protected/);
  }

  parse_storage_class() {
    return this.try(
      p => p.skip(" ").expect(/^(?:auto|extern|static|register)/),
      "none"
    );
  }

  parse_tls_kind() {
    return this.try(p => p.skip(" ").expect(/^(?:tls|tls_dynamic)\b/), "none");
  }

  parse_var_decl() {
    return {
      type: this.parse_type(),
      storage_class: this.parse_storage_class(),
      tls_kind: this.parse_tls_kind(),
      ...this.parse_flags(["nrvo", "inline", "constexpr"]),
      init_style: this.parse_init_style()
    };
  }

  parse_named_var_decl() {
    return {
      name: this.parse_name(),
      ...this.parse_var_decl()
    };
  }

  parse_init_style() {
    return this.try(
      p => p.skip(" ").expect(/^(?:cinit|callinit|listinit)\b/),
      "none"
    );
  }

  parse_access_specifier() {
    return this.try(
      p => p.try_skip(" ").expect(/^(?:private|protected|public)/),
      "none"
    );
  }

  parse_operator() {
    let operator = this.skip(" '").expect(/^[^'\w]+/);
    this.skip("'");
    return operator;
  }

  parse_text_comment() {
    return this.skip(" ").expect(/^Text="(?<text>.*)"/).text;
  }

  parse_flags(flags) {
    const result = {};
    outer: while (flags.length) {
      for (let i = 0; i < flags.length; i++) {
        const flag = flags[i];
        if (
          this.try(p => {
            p.skip(" ");
            p.expect(flag);
            p.peek(/^\s/);
            return true;
          })
        ) {
          result[flag] = true;
          flags.splice(i, 1);
          continue outer;
        }
      }
      break;
    }
    return result;
  }
}

class Node {
  constructor(parser) {
    this.parse(parser);
    let rest = parser.expect(/^.*/);
    if (rest.length) {
      console.error(this.constructor.name, " == ", rest);
    }
  }

  parse(parser) {}
}

class KindedNode extends Node {
  parse(parser) {
    super.parse(parser);
  }
}

class NullNode extends Node {
  parse(parser) {
    super.parse(parser);
  }
}

class AddressableNode extends KindedNode {
  parse(parser) {
    super.parse(parser);
    this.address = parser.parse_address();
    this.semantic_parent = parser.try(p =>
      p.skip(" parent").expect(p => p.parse_node_ref())
    );
    this.prev = parser.try(p =>
      p.skip(" prev").expect(p => p.parse_node_ref())
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
    assign(
      this,
      parser.parse_flags(["implicit", "referenced", "used", "constexpr"])
    );
  }
}

class NamedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.name = parser.parse_name();
  }
}

class TypedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.type = parser.parse_type();
  }
}

class NamedAndTypedDeclNodeBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.name = parser.parse_name();
    this.type = parser.parse_type();
  }
}

class CallableDeclBase extends DeclNodeBase {
  parse(parser) {
    super.parse(parser);
    this.name = parser.try_skip(" ").expect(/^~?\w[^']*?(?=\s+')/);
    this.type = parser.parse_type();
    this.storage_class = parser.parse_storage_class();
    parser.parse_flags([
      "default",
      "default_delete",
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
          noexcept_source: p.parse_node_ref()
        };
      },
      { noexcept_spec: undefined, noexcept_source: undefined }
    );
    Object.assign(this, noexcept);

    this.overrides = parser.try_parse_leaf(p => {
      const overrides = [];
      p.expect("Overrides: [");
      do {
        overrides.push(p.parse_node_ref());
        p.parse_name(); // Redundant.
        p.parse_type(); // Redundant.
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
    if (!parser.try_peek(/^ definition(?=\r?\n)/)) {
      this.name = parser.parse_name();
    }

    if (parser.try(p => p.skip(" ").expect("definition"))) {
      this.is_definition = true;
      this.definition = parser.parse_leaf(p => new RecordDefinition(p, this));
      this.bases = parser.repeat(p =>
        p.parse_leaf(p => new CXXBaseSpecifier(p))
      );
    } else {
      this.is_definition = false;
    }
  }
}

class TypedNode extends AddressableNode {
  parse(parser) {
    super.parse(parser);
    this.type = parser.skip(" ").expect(p => new Type(p));
    parser.parse_flags([
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
    assign(this, parser.parse_flags(["Inherited", "Implicit"]));
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
    this.type = parser.parse_type();
    this.value_kind = parser.try(
      p => p.skip(" ").expect(/^(?:lvalue|xvalue)/),
      "rvalue"
    );
  }
}

class ConstructExprBase extends ExprNodeBase {
  parse(parser) {
    super.parse(parser);
    this.constructor_type = parser.parse_type();
    parser.parse_flags([
      "elidable",
      "list",
      "std::initializer_list",
      "zeroing"
    ]);
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

class CXXTemporary {
  constructor(parser, parent) {
    this.parent = parent;
    this.parse(parser);
  }

  parse(parser) {
    this.kind = parser.expect(this.constructor.name);
    parser.skip(" ");
    this.address = parser.parse_address();
  }
}

const node_types = [
  class TranslationUnitDecl extends DeclNodeBase {
    constructor(parser) {
      super(parser, null);
    }
  },
  class AccessSpecDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.access = parser.parse_access_specifier();
    }
  },
  class AlwaysInlineAttr extends SimpleAttr {},
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
      this.operator = parser.parse_operator();
    }
  },
  class BlockCommandComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
      Object.assign(parser.skip(" ").expect(/^Name="(?<command_name>.*)"/));
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
      parser.skip(" (");
      this.temporary = new CXXTemporary(parser, this);
      parser.skip(")");
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
  class CXXConstructExpr extends ConstructExprBase {},
  class CXXConstructorDecl extends CallableDeclBase {},
  class CXXCtorInitializer extends KindedNode {
    parse(parser) {
      super.parse(parser);
      const field = parser.try(p => {
        p.parse_kind(); // Redundant
        const ref = p.parse_node_ref();
        p.skip(/^.*/); // Skip redundant info which replicated from the referenced field.
        return ref;
      });
      if (field) {
        // Initializer initializes a class member.
        this.field = field;
      } else {
        // Initializer intializes a base class or delegates to another constructor.
        // TODO: can we distinguish between those?
        this.base = parser.parse_type();
      }
    }
  },
  class CXXConversionDecl extends CallableDeclBase {
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
      assign(this, parser.parse_flags(["array", "global"]));
      parser.try(p => {
        p.skip(" ").expect("Function");
        this.function_decl = p.parse_node_ref();
        p.skip(" ").expect(/^.*/); // Redundant info.
      });
    }
  },
  class CXXDependentScopeMemberExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.operator = parser.try_skip(" ").expect(/^(\.|->)/);
      this.member_name = parser.parse_name();
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
      assign(this, parser.parse_flags(["array", "global"]));
      // Todo: parse reference to `operator new` if it exists.
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
  class CXXTemporaryObjectExpr extends ConstructExprBase {},
  class CXXThisExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.implicit = Boolean(parser.try(" implicit"));
      this.name = parser.skip(" ").expect("this");
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

      // This type is redundant.
      const type = parser.parse_type();
      assert(type.name === this.type.name);

      assign(this, parser.parse_flags(["list"]));
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
      parser.skip(" ");
      parser.expect("'");
      this.operator = parser.expect(/^[^']+/);
      parser.expect("'");
      parser.skip(" ").expect("ComputeLHSTy=");
      this.computation_lhs_type = parser.parse_type();
      parser.skip(" ").expect("ComputeResultTy=");
      this.computation_result_type = parser.parse_type();
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
      this.size = Number(parser.skip(" ").expect(/^\d+/));
      this.array_type = parser.parse_array_type();
      parser.try(/^[ ]+(?= )/); // Skip extra spaces.
      assign(this, parser.parse_type_qualifiers());
      parser.try(" ");
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
      parser.parse_kind(); // Redundant info.
      this.decl = parser.parse_node_ref();
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
      this.name = parser.try(p => p.parse_name());
      this.type = parser.try(p => p.parse_type());
    }
  },
  class EnumType extends TypedNode {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ExprWithCleanups extends ExprNodeBase {
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
      this.type = parser.parse_type();
    }
  },
  class FieldDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.name = parser.try(p => p.parse_name());
      this.type = parser.parse_type();
      assign(this, parser.parse_flags(["mutable"]));
    }
  },
  class FinalAttr extends SimpleAttr {},
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
      this.format_attr_kind = parser.skip(" ").expect(/^\w+/);
      this.format_idx = Number(parser.skip(" ").expect(/^\d+/));
      this.first_arg_idx = Number(parser.skip(" ").expect(/^\d+/));
    }
  },
  class FriendDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.friend_type = parser.try(p => p.parse_type());
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
      this.type = parser.parse_type();
    }
  },
  class FunctionDecl extends CallableDeclBase {},
  class FunctionProtoType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      assign(this, parser.parse_flags(["trailing_return"])),
        assign(this, parser.parse_type_qualifiers());
      assign(this, parser.parse_flags(["variadic"])),
        (this.ref_qualifier = {
          "": "none",
          "&": "lvalue",
          "&&": "rvalue"
        }[parser.try(p => p.skip(" ").expect(/^&+/), "")]);
      assign(
        this,
        parser.parse_flags(["noreturn", "produces_result", "regparm"])
      );
      this.calling_convention = parser
        .skip(" ")
        .expect(
          /^(?:cdecl|stdcall|fastcall|thiscall|pascal|vectorcall|ms_abi|sysv_abi|regcall|aapcs|aapcs-vfp|aarch64_vector_pcs|intel_ocl_bicc|spir_function|opencl_kernel|swiftcall|preserve_most|preserve_all)\b/
        );
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
      assign(this, parser.parse_flags(["has_init", "has_var", "has_else"]));
    }
  },
  class ImplicitCastExpr extends ImplicitCastExprBase {},
  class IndirectFieldDecl extends NamedAndTypedDeclNodeBase {
    parse(parser) {
      super.parse(parser);
      // Todo: parse chain (list of inline DeclRefs).
    }
  },
  class InitListExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.array_filler = parser.try_parse_leaf(p => {
        p.expect("array_filler: ");
        p.parse_node();
      });
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
      this.command_name = parser.expect(/^ Name="(.*?)"/);
      this.render_kind = parser.expect(/^ Render(\w+)/);
      this.args = parser.repeat(p => p.expect(/^ Arg\[\d+\]="(.*?)"/));
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
      this.operator = parser.try_skip(" ").expect(/^(\.|->)/);
      this.member_name = parser.parse_name();
      this.member_decl = parser.parse_node_ref();
    }
  },
  class NamespaceDecl extends NamedDeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.original = parser.try_parse_leaf(p => {
        p.expect("original ");
        p.parse_kind(); // Redundant.
        const original = p.parse_node_ref();
        p.expect(/^.*/); // Redundant.
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
      this.type = parser.parse_type();
      this.position = parser.parse_position();
      this.is_parameter_pack = parser.parse_parameter_pack_indicator();
      this.name = parser.try(p => p.parse_name());
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
      parser.skip(" ");
      this.direction = {
        in: "In",
        out: "Out",
        "in,out": "InOut"
      }[parser.expect(/^\[(in|out|in,out)\]/)];
      parser.skip(" ");
      this.direction_is_explicit =
        parser.try("explicitly") || !parser.expect("implicitly");
      this.param_name = parser.try(p => {
        p.skip(" ");
        p.expect('Param="');
        const param_name = p.expect(/^\w+/);
        p.expect('"');
        return param_name;
      });
      this.param_index = parser.try(p => {
        p.skip(" ");
        p.expect("ParamIndex=");
        return Number(p.expect(/^\d+/));
      });
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
  class VarDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      assign(this, parser.parse_named_var_decl());
    }
  },
  class ParmVarDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.name = parser.try(p => p.parse_name());
      assign(this, parser.parse_var_decl());
    }
  },
  class PragmaCommentDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      Object.assign(
        this,
        parser.skip(" ").expect(/(?<comment_kind>\w+) "(?<arg>.*)"/)
      );
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
  class MSAllocatorAttr extends AttrNodeBase {},
  class QualType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      assign(this, parser.parse_type_qualifiers());
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
      this.pack = parser.parse_node_ref();
      parser.parse_name(); // Name of pack; redundant.
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
      assign(this, parser.parse_flags(["alias"]));
      this.template_name = parser.parse_name();
    }
  },
  class TemplateTemplateParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.position = parser.parse_position();
      this.is_parameter_pack = parser.parse_parameter_pack_indicator();
      this.name = parser.try(p => p.parse_name());
    }
  },
  class TemplateTypeParm extends TypedNode {},
  class TemplateTypeParmDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      this.type_kind = parser.skip(" ").expect(/^(?:class|typename)/);
      this.position = parser.parse_position();
      this.is_parameter_pack = parser.parse_parameter_pack_indicator();
      this.name = parser.try(p => p.parse_name());
    }
  },
  class TemplateTypeParmType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      this.position = parser.parse_position();
    }
  },
  class TemplateArgument extends KindedNode {
    parse(parser) {
      super.parse(parser);
      this.template_argument_kind = parser
        .skip(" ")
        .expect(
          /^(?:decl|expr|integral|null|nullptr|pack|template(?: expansion)?|type)/
        )
        .replace(" ", "_");

      switch (this.template_argument_kind) {
        case "decl":
          // Expct decl ref here.
          fatal("Not implemented");
          break;

        case "integral":
          this.integral = parser.skip(" ").expect(/^\d+/);
          break;

        case "template":
        case "template_expansion":
          this.template_name = parser.parse_name();
          break;

        case "type": {
          this.type = parser.parse_type();
          // This info is sometimes present up to clang 8.x, starting with
          // clang 9 it's moved to the VarTemplateSpecializationDecl node.
          // So we'll eventually move the 'var' field to the parent node.
          this.var = parser.try(p => p.parse_named_var_decl());
          break;
        }

        case "expr":
        case "null":
        case "nullptr":
        case "pack":
          // No further info expected.
          break;

        default:
          fatal("Unexpected template argument kind.");
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
      this.text = parser.parse_text_comment();
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
      this.type_visibility = parser.parse_visibility();
    }
  },
  class Typedef extends TypedNode {},
  class TypedefDecl extends NamedAndTypedDeclNodeBase {},
  class TypedefType extends TypedNode {},
  class UnaryExprOrTypeTraitExpr extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.operator = parser.skip(" ").expect(/^[\w]+/);
      this.argument_type = parser.parse_type();
    }
  },
  class UnaryOperator extends ExprNodeBase {
    parse(parser) {
      super.parse(parser);
      this.attachment = parser.skip(" ").expect(/^(?:prefix|postfix)/);
      this.operator = parser.parse_operator();
      this.can_overflow = !parser.try(p =>
        p.skip(" ").expect("cannot overflow")
      );
    }
  },
  class UnaryTransformType extends TypedNode {
    parse(parser) {
      super.parse(parser);
      this.unary_transform_type_kind = parser
        .skip(" ")
        .expect("underlying_type");
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
  class UnresolvedUsingTypenameDecl extends NamedDeclNodeBase {},
  class UnresolvedUsingValueDecl extends NamedAndTypedDeclNodeBase {},
  class UsingDecl extends NamedDeclNodeBase {},
  class UsingShadowDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      parser.parse_kind(); // Redundant.
      this.target = parser.parse_node_ref();
      parser.skip(" ").skip(/^.*/); // Redundant.
    }
  },
  class VarTemplateDecl extends NamedDeclNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class VarTemplatePartialSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
      // appended to the first template argument.
      this.var = parser.try(p => p.parse_named_var_decl());
    }
  },
  class VarTemplateSpecializationDecl extends DeclNodeBase {
    parse(parser) {
      super.parse(parser);
      // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
      // appended to the first template argument.
      this.var = parser.try(p => p.parse_named_var_decl());
    }
  },
  class VerbatimBlockComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
      Object.assign(
        parser
          .skip(" ")
          .expect(
            /^Name="(?<command_name>.*)" CloseName="(?<close_command_name>.*)"/
          )
      );
    }
  },
  class VerbatimBlockLineComment extends CommentNodeBase {
    parse(parser) {
      super.parse(parser);
      this.text = parser.parse_text_comment();
    }
  },
  class VisibilityAttr extends AttrNodeBase {
    parse(parser) {
      super.parse(parser);
      this.visibility = parser.parse_visibility();
    }
  },
  class WarnUnusedResultAttr extends SimpleAttr {},
  class WhileStmt extends StmtNodeBase {
    parse(parser) {
      super.parse(parser);
    }
  },
  class ImplicitValueInitExpr extends ExprNodeBase {}
];

var node_type_map = new Map(node_types.map(cl => [cl.name, cl]));
node_type_map.set("<<<NULL>>>", NullNode);

class Type {
  constructor(parser) {
    Object.assign(this, this.parse(parser));
    Type.add(this);
  }

  static construct(props = {}) {
    // TODO: clean this up.
    const type = Object.assign(Object.create(Type.prototype), props);
    Type.add(type);
    return type;
  }

  parse(parser) {
    const name = parser.skip("'").expect(/^[^']*/);
    parser.skip("'");
    const desugared = parser.try(p => {
      return p.skip(":").expect(p => new Type(p));
    });
    return { name, desugared };
  }

  static add(type) {
    Type.index.push(type);
  }

  static dumpIndex() {
    let s = Type.index
      .map(({ name, desugared }) => `${name} ${desugared ? "@" : " "}\n`)
      .join("");
    process.stdout.write(s);
  }
}
Type.index = [];

class NodeRef {
  constructor(parser) {
    this.parse(parser);
  }

  parse(parser) {
    this.address = parser.parse_address();
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
  constructor(parser) {
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
        const match_fn = p => p.parse_leaf(parse_fn);
        return {
          match: match_fn,
          on_match: r => Object.assign(this, r),
          on_unmatch: match_fn
        };
      })
    );
  }

  parse_top_level_flags(parser) {
    parser.expect("DefinitionData");
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
    parser.expect(identifier);
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
      item.on_unmatch(parser);
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
  constructor(parser) {
    this.parse(parser);
  }

  parse(parser) {
    this.virtual = Boolean(parser.try("virtual"));
    this.access = parser.parse_access_specifier();
    this.type = parser.parse_type();
    this.pack_expansion = parser.parse_parameter_pack_indicator();
  }
}

class TemplateArgumentInheritedDefault {
  constructor(parser) {
    this.parse(parser);
  }

  parse(parser) {
    assign(
      this,
      parser.try_parse_leaf(p => this.parse_reference(p)) || {
        status: "none",
        origin: undefined
      }
    );
  }

  parse_reference(parser) {
    let status;
    switch (parser.expect(/^(?:inherited from|previous)/)) {
      case "inherited from":
        status = "active";
        break;
      case "previous":
        status = "overridden";
        break;
      default:
        return;
    }

    parser.skip(" ");
    parser.parse_kind(); // Redundant.
    const origin = parser.parse_node_ref();
    parser.skip(/^.*/); // Redundant.

    return { status, origin };
  }
}

main();
