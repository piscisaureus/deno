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
    const node_data = {
      kind,
      children: [],
      ...this.parse_node_specific(kind)
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

  parse_template_parameter_position() {
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

  parse_var_type_and_properties() {
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
      ...this.parse_var_type_and_properties()
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

  parse_comment_text() {
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

  ////////////////////////////////////////////////////////////////////////////

  parse_node_specific(kind) {
    this.is_root = true;
    switch (kind) {
      case "<<<NULL>>>":
        return {};
      case "Field":
        return this.parse_field();
      case "Function":
        return this.parse_function();
      case "CXX11NoReturnAttr":
      case "ConstAttr":
        return this.parse_attr_node_base();
      case "DeprecatedAttr":
        return this.parse_deprecated_attr();
      case "FormatAttr":
        return this.parse_format_attr();
      case "MSAllocatorAttr":
      case "MSNoVTableAttr":
        return this.parse_attr_node_base();
      case "MaxFieldAlignmentAttr":
        return this.parse_max_field_alignment_attr();
      case "NoAliasAttr":
      case "NoInlineAttr":
      case "NoThrowAttr":
      case "OverrideAttr":
      case "PureAttr":
        return this.parse_attr_node_base();
      case "AlwaysInlineAttr":
      case "FinalAttr":
      case "RestrictAttr":
      case "WarnUnusedResultAttr":
        return this.parse_simple_attr();
      case "TypeVisibilityAttr":
        return this.parse_type_visibility_attr();
      case "VisibilityAttr":
        return this.parse_visibility_attr();
      case "BlockCommandComment":
        return this.parse_block_command_comment();
      case "BreakStmt":
      case "CXXCatchStmt":
      case "CXXForRangeStmt":
      case "CXXTryStmt":
      case "CompoundStmt":
      case "DeclStmt":
        return this.parse_src_range_node();
      case "ArraySubscriptExpr":
        return this.parse_expr_node_base();
      case "BinaryOperator":
        return this.parse_binary_operator();
      case "CXXBindTemporaryExpr":
        return this.parse_cxx_bind_temporary_expr();
      case "CXXDefaultArgExpr":
      case "CXXDefaultInitExpr":
        return this.parse_expr_node_base();
      case "CXXDeleteExpr":
        return this.parse_cxx_delete_expr();
      case "CXXDependentScopeMemberExpr":
        return this.parse_cxx_dependent_scope_member_expr();
      case "CXXMemberCallExpr":
        return this.parse_expr_node_base();
      case "CXXNewExpr":
        return this.parse_cxx_new_expr();
      case "CXXNoexceptExpr":
      case "CXXNullPtrLiteralExpr":
      case "CXXOperatorCallExpr":
      case "CXXPseudoDestructorExpr":
      case "CXXScalarValueInitExpr":
        return this.parse_expr_node_base();
      case "CXXThisExpr":
        return this.parse_cxx_this_expr();
      case "CXXThrowExpr":
      case "CXXTypeidExpr":
        return this.parse_expr_node_base();
      case "CXXUnresolvedConstructExpr":
        return this.parse_cxx_unresolved_construct_expr();
      case "CallExpr":
        return this.parse_expr_node_base();
      case "CompoundAssignOperator":
        return this.parse_compound_assign_operator();
      case "ConditionalOperator":
      case "ConstantExpr":
        return this.parse_expr_node_base();
      case "CXXConstructExpr":
      case "CXXTemporaryObjectExpr":
        return this.parse_construct_expr_base();
      case "DeclRefExpr":
        return this.parse_decl_ref_expr();
      case "DependentScopeDeclRefExpr":
      case "ExprWithCleanups":
        return this.parse_expr_node_base();
      case "ImplicitCastExpr":
        return this.parse_implicit_cast_expr();
      case "CStyleCastExpr":
        return this.parse_c_style_cast_expr();
      case "CXXFunctionalCastExpr":
        return this.parse_cxx_functional_cast_expr();
      case "CXXConstCastExpr":
      case "CXXDynamicCastExpr":
      case "CXXReinterpretCastExpr":
      case "CXXStaticCastExpr":
        return this.parse_cxx_named_cast_expr_base();
      case "ImplicitValueInitExpr":
        return this.parse_expr_node_base();
      case "InitListExpr":
        return this.parse_init_list_expr();
      case "LambdaExpr":
        return this.parse_expr_node_base();
      case "CXXBoolLiteralExpr":
        return this.parse_cxx_bool_literal_expr();
      case "FloatingLiteral":
      case "IntegerLiteral":
      case "StringLiteral":
        return this.parse_literal_node_base();
      case "MaterializeTemporaryExpr":
        return this.parse_expr_node_base();
      case "MemberExpr":
        return this.parse_member_expr();
      case "PackExpansionExpr":
      case "ParenExpr":
      case "ParenListExpr":
        return this.parse_expr_node_base();
      case "SizeOfPackExpr":
        return this.parse_size_of_pack_expr();
      case "SubstNonTypeTemplateParmExpr":
      case "TypeTraitExpr":
        return this.parse_expr_node_base();
      case "UnaryExprOrTypeTraitExpr":
        return this.parse_unary_expr_or_type_trait_expr();
      case "UnaryOperator":
        return this.parse_unary_operator();
      case "UnresolvedLookupExpr":
        return this.parse_unresolved_lookup_expr();
      case "UnresolvedMemberExpr":
        return this.parse_expr_node_base();
      case "ForStmt":
      case "FullComment":
        return this.parse_src_range_node();
      case "IfStmt":
        return this.parse_if_stmt();
      case "InlineCommandComment":
        return this.parse_inline_command_comment();
      case "Kind":
      case "NullStmt":
      case "ParagraphComment":
        return this.parse_src_range_node();
      case "ParamCommandComment":
        return this.parse_param_command_comment();
      case "ReturnStmt":
        return this.parse_src_range_node();
      case "AccessSpecDecl":
        return this.parse_access_spec_decl();
      case "CXXConstructorDecl":
      case "CXXConversionDecl":
      case "CXXDestructorDecl":
      case "CXXMethodDecl":
      case "FunctionDecl":
        return this.parse_callable_decl_base();
      case "EmptyDecl":
        return this.parse_decl_node_base();
      case "EnumDecl":
        return this.parse_enum_decl();
      case "FieldDecl":
        return this.parse_field_decl();
      case "FriendDecl":
        return this.parse_friend_decl();
      case "LinkageSpecDecl":
        return this.parse_linkage_spec_decl();
      case "EnumConstantDecl":
        return this.parse_named_and_typed_decl_node_base();
      case "IndirectFieldDecl":
        return this.parse_indirect_field_decl();
      case "TypeAliasDecl":
      case "TypedefDecl":
      case "UnresolvedUsingValueDecl":
        return this.parse_named_and_typed_decl_node_base();
      case "BuiltinTemplateDecl":
      case "ClassTemplateDecl":
      case "FunctionTemplateDecl":
        return this.parse_named_decl_node_base();
      case "NamespaceDecl":
        return this.parse_namespace_decl();
      case "TypeAliasTemplateDecl":
      case "UnresolvedUsingTypenameDecl":
      case "UsingDecl":
      case "VarTemplateDecl":
        return this.parse_named_decl_node_base();
      case "NonTypeTemplateParmDecl":
        return this.parse_non_type_template_parm_decl();
      case "ParmVarDecl":
        return this.parse_parm_var_decl();
      case "PragmaCommentDecl":
        return this.parse_pragma_comment_decl();
      case "PragmaDetectMismatchDecl":
        return this.parse_pragma_detect_mismatch_decl();
      case "CXXRecordDecl":
      case "ClassTemplatePartialSpecializationDecl":
      case "ClassTemplateSpecializationDecl":
        return this.parse_record_node_base();
      case "StaticAssertDecl":
        return this.parse_decl_node_base();
      case "TemplateTemplateParmDecl":
        return this.parse_template_template_parm_decl();
      case "TemplateTypeParmDecl":
        return this.parse_template_type_parm_decl();
      case "TranslationUnitDecl":
      case "TranslationUnitDecl":
        return this.parse_decl_node_base();
      case "UsingShadowDecl":
        return this.parse_using_shadow_decl();
      case "VarDecl":
        return this.parse_var_decl();
      case "VarTemplatePartialSpecializationDecl":
        return this.parse_var_template_partial_specialization_decl();
      case "VarTemplateSpecializationDecl":
        return this.parse_var_template_specialization_decl();
      case "TextComment":
        return this.parse_text_comment();
      case "VerbatimBlockComment":
        return this.parse_verbatim_block_comment();
      case "VerbatimBlockLineComment":
        return this.parse_verbatim_block_line_comment();
      case "WhileStmt":
        return this.parse_src_range_node();
      case "AttributedType":
      case "BuiltinType":
      case "CXXRecord":
      case "ClassTemplateSpecialization":
        return this.parse_typed_node();
      case "ConstantArrayType":
        return this.parse_constant_array_type();
      case "DecltypeType":
      case "DependentNameType":
      case "DependentTemplateSpecializationType":
      case "ElaboratedType":
      case "Enum":
      case "EnumType":
        return this.parse_typed_node();
      case "FunctionProtoType":
        return this.parse_function_proto_type();
      case "InjectedClassNameType":
      case "LValueReferenceType":
      case "ParenType":
      case "PointerType":
        return this.parse_typed_node();
      case "QualType":
        return this.parse_qual_type();
      case "RValueReferenceType":
      case "RecordType":
      case "SubstTemplateTypeParmType":
        return this.parse_typed_node();
      case "TemplateSpecializationType":
        return this.parse_template_specialization_type();
      case "TemplateTypeParm":
        return this.parse_typed_node();
      case "TemplateTypeParmType":
        return this.parse_template_type_parm_type();
      case "TypeAlias":
      case "Typedef":
      case "TypedefType":
        return this.parse_typed_node();
      case "UnaryTransformType":
        return this.parse_unary_transform_type();
      case "CXXCtorInitializer":
        return this.parse_cxx_ctor_initializer();
      case "TemplateArgument":
        return this.parse_template_argument();
      default:
        fatal(`Unsupported AST node kind: ${kind}`);
    }
  }

  parse_addressable_node() {
    return {
      address: this.parse_address(),
      semantic_parent: this.try(p =>
        p.skip(" parent").expect(p => p.parse_node_ref())
      ),
      prev: this.try(p => p.skip(" prev").expect(p => p.parse_node_ref()))
    };
  }

  parse_field() {
    const result = this.parse_addressable_node();
    this.expect(" '");
    result.name = this.expect(/^[^']*/);
    this.expect("'");
    result.type = this.parse_type();
    return result;
  }

  parse_function() {
    const result = this.parse_addressable_node();
    this.expect(" '");
    result.name = this.expect(/^[^']+/);
    this.expect("'");
    result.type = this.parse_type();
    return result;
  }

  parse_src_range_node() {
    return {
      ...this.parse_addressable_node(),
      source_range: this.skip(" ").expect(p => new SourceRange(p))
    };
  }

  parse_attr_node_base() {
    return {
      ...this.parse_src_range_node(),
      ...this.parse_flags(["Inherited", "Implicit"])
    };
  }

  parse_deprecated_attr() {
    const result = this.parse_attr_node_base();
    // There seems to be an always-empty string after the message.
    // Unclear what result is for.
    result.message = this.expect(/^ "(?<message>.*)" ""/).message;
    return result;
  }

  parse_format_attr() {
    return {
      ...this.parse_attr_node_base(),
      format_attr_kind: this.skip(" ").expect(/^\w+/),
      format_idx: Number(this.skip(" ").expect(/^\d+/)),
      first_arg_idx: Number(this.skip(" ").expect(/^\d+/))
    };
  }

  parse_max_field_alignment_attr() {
    return {
      ...this.parse_attr_node_base(),
      alignment: Number(this.skip(" ").expect(/^\d+/))
    };
  }

  parse_simple_attr() {
    return {
      ...this.parse_attr_node_base(),
      attr: this.skip(" ").expect(/^[\w]+/)
    };
  }

  parse_type_visibility_attr() {
    return {
      ...this.parse_attr_node_base(),
      type_visibility: this.parse_visibility()
    };
  }

  parse_visibility_attr() {
    return {
      ...this.parse_attr_node_base(),
      visibility: this.parse_visibility()
    };
  }

  parse_block_command_comment() {
    return {
      ...this.parse_src_range_node(),
      ...this.skip(" ").expect(/^Name="(?<command_name>.*)"/)
    };
  }

  parse_expr_node_base() {
    return {
      ...this.parse_src_range_node(),
      type: this.parse_type(),
      value_kind: this.try(
        p => p.skip(" ").expect(/^(?:lvalue|xvalue)/),
        "rvalue"
      )
    };
  }

  parse_binary_operator() {
    return { ...this.parse_expr_node_base(), operator: this.parse_operator() };
  }

  parse_cxx_bind_temporary_expr() {
    const result = this.parse_expr_node_base();
    this.skip(" (");
    result.temporary = {
      kind: this.parse_kind(),
      address: this.parse_address()
    };
    this.skip(")");
    return result;
  }

  parse_cxx_delete_expr() {
    const result = this.parse_expr_node_base();
    assign(result, this.parse_flags(["array", "global"]));
    this.try(p => {
      p.skip(" ").expect("Function");
      result.function_decl = p.parse_node_ref();
      p.skip(" ").expect(/^.*/); // Redundant info.
    });
    return result;
  }

  parse_cxx_dependent_scope_member_expr() {
    return {
      ...this.parse_expr_node_base(),
      operator: this.try_skip(" ").expect(/^(\.|->)/),
      member_name: this.parse_name()
    };
  }

  parse_cast_kind(line = this.expect(/^.*/)) {
    let {
      groups: { rest, cast_kind, base_path }
    } =
      line.match(
        /^(\s*(?<rest>.*) )?<(?<cast_kind>(Unchecked)?(BaseToDerived|DerivedToBase)) \((?<base_path>.+)\)>$/
      ) || line.match(/^(\s*(?<rest>.*) )?<(?<cast_kind>[a-zA-Z]+)>$/);
    if (rest === undefined) {
      rest = "";
    }
    if (base_path !== undefined) {
      base_path = base_path.split(" -> ");
    }
    return { rest, cast_kind, base_path };
  }

  parse_implicit_cast_expr() {
    const expr = this.parse_expr_node_base();
    let { kind_part, flag_part } =
      this.try(
        /^(?<kind_part>.*) (?<flag_part>part_of_explicit_cast)(?=[\n\r])/
      ) || this.expect(/^(?<kind_part>.*)/);
    const { rest, ...cast_kind } = this.parse_cast_kind(kind_part);
    assert(rest === "");
    return { ...expr, ...cast_kind, part_of_explicit_cast: !!flag_part };
  }

  parse_c_style_cast_expr() {
    const expr = this.parse_expr_node_base();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assert(rest === "");
    return { ...expr, ...cast_kind };
  }

  parse_cxx_named_cast_expr_base() {
    const result = this.parse_expr_node_base();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assign(result, cast_kind);
    // The type inside the angle brackets (static_cast<this_type>) is redundant.
    // It's the same as the result type of result expression (which is parsed by
    // our base class).
    result.cast_name = /^[a-z_]+_cast(?=<.+>$)/.exec(rest)[0];
    return result;
  }

  parse_cxx_functional_cast_expr() {
    const result = this.parse_expr_node_base();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assign(result, cast_kind);
    // Further information in the rest is redundant.
    assert(/^functional cast to .*\S$/.test(rest));
    return result;
  }

  parse_cxx_new_expr() {
    const result = this.parse_expr_node_base();
    assign(result, this.parse_flags(["array", "global"]));
    // Todo: parse reference to `operator new` if it exists.
    return result;
  }

  parse_cxx_this_expr() {
    return {
      ...this.parse_expr_node_base(),
      implicit: Boolean(this.try(" implicit")),
      name: this.skip(" ").expect("this")
    };
  }

  parse_cxx_unresolved_construct_expr() {
    const result = this.parse_expr_node_base();

    // This type is redundant.
    const type = this.parse_type();
    assert(type.name === result.type.name);

    assign(result, this.parse_flags(["list"]));
    return result;
  }

  parse_compound_assign_operator() {
    const result = this.parse_expr_node_base();
    this.skip(" ");
    this.expect("'");
    result.operator = this.expect(/^[^']+/);
    this.expect("'");
    this.skip(" ").expect("ComputeLHSTy=");
    result.computation_lhs_type = this.parse_type();
    this.skip(" ").expect("ComputeResultTy=");
    result.computation_result_type = this.parse_type();
    return result;
  }

  parse_construct_expr_base() {
    const result = this.parse_expr_node_base();
    result.constructor_type = this.parse_type();
    this.parse_flags(["elidable", "list", "std::initializer_list", "zeroing"]);
    return result;
  }

  parse_decl_ref_expr() {
    const result = this.parse_expr_node_base();
    this.parse_kind(); // Redundant info.
    result.decl = this.parse_node_ref();
    this.skip(/^.*/); // The rest of the line is also redundant.
    return result;
  }

  parse_init_list_expr() {
    const result = this.parse_expr_node_base();
    result.array_filler = this.try_parse_leaf(p => {
      p.expect("array_filler: ");
      p.parse_node();
    });
    return result;
  }

  parse_literal_node_base() {
    return {
      ...this.parse_expr_node_base(),
      source: this.skip(" ").expect(/^.*\S/)
    };
  }

  parse_cxx_bool_literal_expr() {
    const result = this.parse_literal_node_base();
    result.value = JSON.parse(result.source);
    return result;
  }

  parse_member_expr() {
    return {
      ...this.parse_expr_node_base(),
      operator: this.try_skip(" ").expect(/^(\.|->)/),
      member_name: this.parse_name(),
      member_decl: this.parse_node_ref()
    };
  }

  parse_size_of_pack_expr() {
    const result = this.parse_expr_node_base();
    result.pack = this.parse_node_ref();
    this.parse_name(); // Name of pack; redundant.
    return result;
  }

  parse_unary_expr_or_type_trait_expr() {
    return {
      ...this.parse_expr_node_base(),
      operator: this.skip(" ").expect(/^[\w]+/),
      argument_type: this.parse_type()
    };
  }

  parse_unary_operator() {
    return {
      ...this.parse_expr_node_base(),
      attachment: this.skip(" ").expect(/^(?:prefix|postfix)/),
      operator: this.parse_operator(),
      can_overflow: !this.try(p => p.skip(" ").expect("cannot overflow"))
    };
  }

  parse_unresolved_lookup_expr() {
    return {
      ...this.parse_expr_node_base(),
      unknown: this.skip(" ").expect(/^.*/)
    };
  }

  parse_if_stmt() {
    return {
      ...this.parse_src_range_node(),
      ...this.parse_flags(["has_init", "has_var", "has_else"])
    };
  }

  parse_inline_command_comment() {
    return {
      ...this.parse_src_range_node(),
      command_name: this.expect(/^ Name="(.*?)"/),
      render_kind: this.expect(/^ Render(\w+)/),
      args: this.repeat(p => p.expect(/^ Arg\[\d+\]="(.*?)"/))
    };
  }

  parse_param_command_comment() {
    const result = this.parse_src_range_node();
    this.skip(" ");
    result.direction = {
      in: "In",
      out: "Out",
      "in,out": "InOut"
    }[this.expect(/^\[(in|out|in,out)\]/)];
    this.skip(" ");
    result.direction_is_explicit =
      this.try("explicitly") || !this.expect("implicitly");
    result.param_name = this.try(p => {
      p.skip(" ");
      p.expect('Param="');
      const param_name = p.expect(/^\w+/);
      p.expect('"');
      return param_name;
    });
    result.param_index = this.try(p => {
      p.skip(" ");
      p.expect("ParamIndex=");
      return Number(p.expect(/^\d+/));
    });
    return result;
  }

  parse_src_range_loc_node() {
    return {
      ...this.parse_src_range_node(),
      source_location: this.skip(" ").expect(p => new SourceLocation(p))
    };
  }

  parse_decl_node_base() {
    return {
      ...this.parse_src_range_loc_node(),
      ...this.parse_flags(["implicit", "referenced", "used", "constexpr"])
    };
  }

  parse_access_spec_decl() {
    return {
      ...this.parse_decl_node_base(),
      access: this.parse_access_specifier()
    };
  }

  parse_callable_decl_base() {
    const result = this.parse_decl_node_base();
    result.name = this.try_skip(" ").expect(/^~?\w[^']*?(?=\s+')/);
    result.type = this.parse_type();
    result.storage_class = this.parse_storage_class();
    this.parse_flags([
      "default",
      "default_delete",
      "delete",
      "inline",
      "pure",
      "trivial",
      "virtual"
    ]);

    const noexcept = this.try(
      p => {
        p.skip(" ").expect("noexcept-");
        return {
          noexcept_spec: p.expect(/^\w+/),
          noexcept_source: p.parse_node_ref()
        };
      },
      { noexcept_spec: undefined, noexcept_source: undefined }
    );
    Object.assign(result, noexcept);

    result.overrides = this.try_parse_leaf(p => {
      const overrides = [];
      p.expect("Overrides: [");
      do {
        overrides.push(p.parse_node_ref());
        p.parse_name(); // Redundant.
        p.parse_type(); // Redundant.
      } while (p.try(","));
      p.expect(" ]");
    });
    return result;
  }

  parse_enum_decl() {
    return {
      ...this.parse_decl_node_base(),
      scope: this.try(p => p.skip(" ").expect(/^(?:class|struct)/), "unscoped"),
      name: this.try(p => p.parse_name()),
      type: this.try(p => p.parse_type())
    };
  }

  parse_field_decl() {
    return {
      ...this.parse_decl_node_base(),
      name: this.try(p => p.parse_name()),
      type: this.parse_type(),
      ...this.parse_flags(["mutable"])
    };
  }

  parse_friend_decl() {
    return {
      ...this.parse_decl_node_base(),
      friend_type: this.try(p => p.parse_type())
    };
  }

  parse_linkage_spec_decl() {
    return {
      ...this.parse_decl_node_base(),
      linkage: this.skip(" ").expect(/^C\+\+|^C/)
    };
  }

  parse_named_and_typed_decl_node_base() {
    return {
      ...this.parse_decl_node_base(),
      name: this.parse_name(),
      type: this.parse_type()
    };
  }

  parse_indirect_field_decl() {
    const result = this.parse_named_and_typed_decl_node_base();
    // Todo: parse chain (list of inline DeclRefs).
    return result;
  }

  parse_named_decl_node_base() {
    return { ...this.parse_decl_node_base(), name: this.parse_name() };
  }

  parse_namespace_decl() {
    const result = this.parse_named_decl_node_base();
    result.original = this.try_parse_leaf(p => {
      p.expect("original ");
      p.parse_kind(); // Redundant.
      const original = p.parse_node_ref();
      p.expect(/^.*/); // Redundant.
      return original;
    });
    return result;
  }

  parse_non_type_template_parm_decl() {
    return {
      ...this.parse_decl_node_base(),
      type: this.parse_type(),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_parm_var_decl() {
    return {
      ...this.parse_decl_node_base(),
      name: this.try(p => p.parse_name()),
      ...this.parse_var_type_and_properties()
    };
  }

  parse_pragma_comment_decl() {
    const result = this.parse_decl_node_base();
    Object.assign(
      result,
      this.skip(" ").expect(/(?<comment_kind>\w+) "(?<arg>.*)"/)
    );
    return result;
  }

  parse_pragma_detect_mismatch_decl() {
    const result = this.parse_decl_node_base();
    Object.assign(
      result,
      this.skip(" ").expect(/"(?<name>.+)" "(?<value>.*)"/)
    );
    return result;
  }

  parse_record_node_base() {
    const result = this.parse_decl_node_base();
    result.record_kind = this.skip(" ").expect(
      /^(?:class|struct|union|interface|enum)/
    );

    // Umbiguity is unavoidable here - just never call your class 'definition'.
    // TODO: disambiguate using color output?
    if (!this.try_peek(/^ definition(?=\r?\n)/)) {
      result.name = this.parse_name();
    }

    if (this.try(p => p.skip(" ").expect("definition"))) {
      result.is_definition = true;
      result.definition = this.parse_leaf(p => new RecordDefinition(p, result));
      result.bases = this.repeat(p =>
        p.parse_leaf(p => new CXXBaseSpecifier(p))
      );
    } else {
      result.is_definition = false;
    }
    return result;
  }

  parse_template_template_parm_decl() {
    return {
      ...this.parse_decl_node_base(),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_template_type_parm_decl() {
    return {
      ...this.parse_decl_node_base(),
      type_kind: this.skip(" ").expect(/^(?:class|typename)/),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_using_shadow_decl() {
    const result = this.parse_decl_node_base();
    this.parse_kind(); // Redundant.
    result.target = this.parse_node_ref();
    this.skip(" ").skip(/^.*/); // Redundant.
    return result;
  }

  parse_var_decl() {
    return { ...this.parse_decl_node_base(), ...this.parse_named_var_decl() };
  }

  parse_var_template_partial_specialization_decl() {
    const result = this.parse_decl_node_base();
    // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
    // appended to the first template argument.
    result.var = this.try(p => p.parse_named_var_decl());
    return result;
  }

  parse_var_template_specialization_decl() {
    const result = this.parse_decl_node_base();
    // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
    // appended to the first template argument.
    result.var = this.try(p => p.parse_named_var_decl());
    return result;
  }

  parse_text_comment() {
    return { ...this.parse_src_range_node(), text: this.parse_comment_text() };
  }

  parse_verbatim_block_comment() {
    const result = this.parse_src_range_node();
    Object.assign(
      this.skip(" ").expect(
        /^Name="(?<command_name>.*)" CloseName="(?<close_command_name>.*)"/
      )
    );
    return result;
  }

  parse_verbatim_block_line_comment() {
    return { ...this.parse_src_range_node(), text: this.parse_comment_text() };
  }

  parse_typed_node() {
    return {
      ...this.parse_addressable_node(),
      type: this.skip(" ").expect(p => new Type(p)),
      ...this.parse_flags([
        "sugar",
        "dependent",
        "instantiation_dependent",
        "variably_modified",
        "contains_unexpanded_pack",
        "imported"
      ])
    };
  }

  parse_constant_array_type() {
    const result = this.parse_typed_node();
    result.size = Number(this.skip(" ").expect(/^\d+/));
    result.array_type = this.parse_array_type();
    this.try(/^[ ]+(?= )/); // Skip extra spaces.
    assign(result, this.parse_type_qualifiers());
    this.try(" ");
    return result;
  }

  parse_function_proto_type() {
    return {
      ...this.parse_typed_node(),
      ...this.parse_flags(["trailing_return"]),
      ...this.parse_type_qualifiers(),
      ...this.parse_flags(["variadic"]),
      ref_qualifier: { "": "none", "&": "lvalue", "&&": "rvalue" }[
        this.try(p => p.skip(" ").expect(/^&+/), "")
      ],
      ...this.parse_flags(["noreturn", "produces_result", "regparm"]),
      calling_convention: this.skip(" ").expect(
        /^(?:cdecl|stdcall|fastcall|thiscall|pascal|vectorcall|ms_abi|sysv_abi|regcall|aapcs|aapcs-vfp|aarch64_vector_pcs|intel_ocl_bicc|spir_function|opencl_kernel|swiftcall|preserve_most|preserve_all)\b/
      )
    };
  }

  parse_qual_type() {
    return { ...this.parse_typed_node(), ...this.parse_type_qualifiers() };
  }

  parse_template_specialization_type() {
    return {
      ...this.parse_typed_node(),
      ...this.parse_flags(["alias"]),
      template_name: this.parse_name()
    };
  }

  parse_template_type_parm_type() {
    return {
      ...this.parse_typed_node(),
      position: this.parse_template_parameter_position()
    };
  }

  parse_unary_transform_type() {
    return {
      ...this.parse_typed_node(),
      unary_transform_type_kind: this.skip(" ").expect("underlying_type")
    };
  }

  parse_cxx_ctor_initializer() {
    const result = {};
    const field = this.try(p => {
      p.parse_kind(); // Redundant
      const ref = p.parse_node_ref();
      p.skip(/^.*/); // Skip redundant info which replicated from the referenced field.
      return ref;
    });
    if (field) {
      // Initializer initializes a class member.
      result.field = field;
    } else {
      // Initializer intializes a base class or delegates to another constructor.
      // TODO: can we distinguish between those?
      result.base = this.parse_type();
    }
    return result;
  }

  parse_template_argument() {
    const result = {};
    result.template_argument_kind = this.skip(" ")
      .expect(
        /^(?:decl|expr|integral|null|nullptr|pack|template(?: expansion)?|type)/
      )
      .replace(" ", "_");

    switch (result.template_argument_kind) {
      case "decl":
        // Expct decl ref here.
        fatal("Not implemented");
        break;

      case "integral":
        result.integral = this.skip(" ").expect(/^\d+/);
        break;

      case "template":
      case "template_expansion":
        result.template_name = this.parse_name();
        break;

      case "type": {
        result.type = this.parse_type();
        // This info is sometimes present up to clang 8.x, starting with
        // clang 9 it's moved to the VarTemplateSpecializationDecl node.
        // So we'll eventually move the 'var' field to the parent node.
        result.var = this.try(p => p.parse_named_var_decl());
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

    result.inherited_default = new TemplateArgumentInheritedDefault(
      this,
      result
    );
    return result;
  }
}

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
