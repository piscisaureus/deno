let { readFileSync } = require("fs");
require("util").inspect.defaultOptions.depth = null;
require("util").inspect.defaultOptions.maxArrayLength = null;
Error.stackTraceLimit = Infinity;

const assign = Object.assign;

function main() {
  let ast_dump = readFileSync(process.argv[2] || "o3", "utf8");
  let parser = new ClangAstDumpParser(ast_dump);
  let result = parser.parse_node();
  parser.skip(/^\s*$/);
  console.log(JSON.stringify(result, null, 2));
  //Type.dumpIndex();
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
    DebugHistory.dump();
    throw new ParseError(this.get_message());
  }
}

class Parser {
  constructor(str) {
    this.str = str === undefined ? "" : `${str}`;
    this.orig = str;
    this.is_root = true;
    this.fail_fast_ = false;
  }

  fail_fast(enable = true) {
    this.fail_fast_ = enable;
  }

  _fork() {
    const fork = Object.create(this.constructor.prototype);
    Object.assign(fork, {
      str: this.str,
      orig: this.orig,
      is_root: false,
      fail_fast_: false
    });
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
      if (this.is_root || this.fail_fast_) {
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
              `Warning: regular expression ${matcher} matched after the beginning of the string. This match is ignored.`
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

  parse_single_quoted() {
    let value = this.skip(" '").expect(/^[^']*/);
    this.skip("'");
    return value;
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
    this.expect(/^\r?\n/);
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
      ...this.parse_node_kind_specific(kind)
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
    return this.skip(" ").expect(/^0x[\da-f]+/);
  }

  parse_name() {
    let name = this.try_skip(" ").expect(
      /^(?:operator(?:[ \t]*[^\s\d][^\s]*)+|::|~|[a-zA-Z_](?:\w*))+<?/
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

  parse_value_kind() {
    return this.try(p => p.skip(" ").expect(/^(?:lvalue|xvalue)\b/), "rvalue");
  }

  parse_object_kind() {
    return this.try(
      p =>
        p
          .skip(" ")
          .expect(/^(?:bitfield|objcproperty|objcsubscript|vectorcomponent)\b/),
      "ordinary"
    );
  }

  parse_bare_ref() {
    return { address: this.parse_address() };
  }

  parse_template_parameter_position() {
    return {
      depth: Number(this.skip(" depth ").expect(/^\d+/)),
      index: Number(this.skip(" index ").expect(/^\d+/))
    };
  }

  parse_parameter_pack_indicator() {
    // Three dots (...) are used by older versions of clang.
    return Boolean(this.try(/^( ?[\.]{3}| pack\b)/));
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

  parse_node_kind_specific(kind) {
    this.fail_fast();
    //console.log(kind, this.try_peek(/^.*/));
    switch (kind) {
      case "<<<NULL>>>":
        return {};
      case "Field":
        return this.parse_field();
      case "Function":
        return this.parse_function();
      case "CXX11NoReturnAttr":
      case "ConstAttr":
      case "ExcludeFromExplicitInstantiationAttr":
      case "FallThroughAttr":
      case "GNUInlineAttr":
      case "MSAllocatorAttr":
      case "MSNoVTableAttr":
      case "NoAliasAttr":
      case "NoInlineAttr":
      case "NoThrowAttr":
      case "OverrideAttr":
      case "PureAttr":
      case "ReturnsTwiceAttr":
      case "WeakAttr":
        return this.parse_attr_node();
      case "AlignedAttr":
      case "AlwaysInlineAttr":
      case "FinalAttr":
      case "RestrictAttr":
      case "WarnUnusedResultAttr":
        return this.parse_singleton_attr();
      case "AsmLabelAttr":
        return this.parse_asm_label_attr();
      case "DeprecatedAttr":
        return this.parse_deprecated_attr();
      case "DiagnoseIfAttr":
        return this.parse_diagnose_if_attr();
      case "EnableIfAttr":
        return this.parse_enable_if_attr();
      case "FormatAttr":
        return this.parse_format_attr();
      case "ModeAttr":
        return this.parse_mode_attr();
      case "MSVtorDispAttr":
        return this.parse_ms_vtor_disp_attr();
      case "MaxFieldAlignmentAttr":
        return this.parse_max_field_alignment_attr();
      case "NonNullAttr":
        return this.parse_non_null_attr();
      case "NoSanitizeAttr":
        return this.parse_no_sanitize_attr();
      case "TypeVisibilityAttr":
        return this.parse_type_visibility_attr();
      case "VisibilityAttr":
        return this.parse_visibility_attr();
      case "BlockCommandComment":
        return this.parse_block_command_comment();
      case "AttributedStmt":
      case "BreakStmt":
      case "CXXCatchStmt":
      case "CXXForRangeStmt":
      case "CXXTryStmt":
      case "CaseStmt":
      case "CompoundStmt":
      case "ContinueStmt":
      case "DeclStmt":
      case "DefaultStmt":
      case "DoStmt":
      case "ForStmt":
      case "WhileStmt":
        return this.parse_stmt_node();
      case "ArrayInitIndexExpr":
      case "ArrayInitLoopExpr":
      case "ArraySubscriptExpr":
      case "AtomicExpr":
        return this.parse_expr_node();
      case "BinaryOperator":
        return this.parse_binary_operator();
      case "CXXBindTemporaryExpr":
        return this.parse_cxx_bind_temporary_expr();
      case "CXXDefaultArgExpr":
      case "CXXDefaultInitExpr":
        return this.parse_expr_node();
      case "CXXNewExpr":
        return this.parse_cxx_new_expr();
      case "CXXDeleteExpr":
        return this.parse_cxx_delete_expr();
      case "CXXThisExpr":
        return this.parse_cxx_this_expr();
      case "CXXDependentScopeMemberExpr":
        return this.parse_cxx_dependent_scope_member_expr();
      case "CXXNoexceptExpr":
      case "CXXNullPtrLiteralExpr":
      case "CXXPseudoDestructorExpr":
      case "CXXScalarValueInitExpr":
      case "GNUNullExpr":
        return this.parse_expr_node();
      case "CXXThrowExpr":
      case "CXXTypeidExpr":
        return this.parse_expr_node();
      case "CXXUnresolvedConstructExpr":
        return this.parse_cxx_unresolved_construct_expr();
      case "CallExpr":
      case "CXXMemberCallExpr":
      case "CXXOperatorCallExpr":
        return this.parse_call_expr();
      case "CompoundAssignOperator":
        return this.parse_compound_assign_operator();
      case "ConditionalOperator":
      case "ConstantExpr":
        return this.parse_expr_node();
      case "CXXConstructExpr":
      case "CXXTemporaryObjectExpr":
        return this.parse_construct_expr_base();
      case "DeclRefExpr":
        return this.parse_decl_ref_expr();
      case "DependentScopeDeclRefExpr":
      case "ExprWithCleanups":
        return this.parse_expr_node();
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
        return this.parse_expr_node();
      case "InitListExpr":
        return this.parse_init_list_expr();
      case "LambdaExpr":
        return this.parse_expr_node();
      case "CXXBoolLiteralExpr":
        return this.parse_cxx_bool_literal_expr();
      case "CharacterLiteral":
      case "FloatingLiteral":
      case "IntegerLiteral":
      case "StringLiteral":
        return this.parse_literal_node_base();
      case "MaterializeTemporaryExpr":
        return this.parse_expr_node();
      case "MemberExpr":
        return this.parse_member_expr();
      case "OpaqueValueExpr":
      case "PackExpansionExpr":
      case "ParenExpr":
      case "ParenListExpr":
        return this.parse_expr_node();
      case "SizeOfPackExpr":
        return this.parse_size_of_pack_expr();
      case "SubstNonTypeTemplateParmExpr":
      case "TypeTraitExpr":
        return this.parse_expr_node();
      case "UnaryExprOrTypeTraitExpr":
        return this.parse_unary_expr_or_type_trait_expr();
      case "UnaryOperator":
        return this.parse_unary_operator();
      case "UnresolvedLookupExpr":
        return this.parse_unresolved_lookup_expr();
      case "UnresolvedMemberExpr":
        return this.parse_expr_node();
      case "FullComment":
        return this.parse_stmt_node();
      case "GotoStmt":
        return this.parse_goto_stmt();
      case "IfStmt":
        return this.parse_if_stmt();
      case "LabelStmt":
        return this.parse_label_stmt();
      case "Kind":
      case "NullStmt":
      case "ParagraphComment":
        return this.parse_stmt_node();
      case "InlineCommandComment":
        return this.parse_inline_command_comment();
      case "ParamCommandComment":
        return this.parse_param_command_comment();
      case "ReturnStmt":
      case "SwitchStmt":
        return this.parse_stmt_node();
      case "FileScopeAsmDecl":
      case "EmptyDecl":
        return this.parse_decl_node();
      case "AccessSpecDecl":
        return this.parse_access_spec_decl();
      case "CXXConstructorDecl":
      case "CXXConversionDecl":
      case "CXXDestructorDecl":
      case "CXXMethodDecl":
      case "FunctionDecl":
      case "MethodDecl":
        return this.parse_callable_decl();
      case "EnumDecl":
        return this.parse_enum_decl();
      case "FieldDecl":
        return this.parse_field_decl();
      case "FriendDecl":
        return this.parse_friend_decl();
      case "LinkageSpecDecl":
        return this.parse_linkage_spec_decl();
      case "EnumConstantDecl":
        return this.parse_decl_node_with_name_and_type();
      case "IndirectFieldDecl":
        return this.parse_indirect_field_decl();
      case "TypeAliasDecl":
      case "TypedefDecl":
      case "UnresolvedUsingValueDecl":
        return this.parse_decl_node_with_name_and_type();
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
        return this.parse_record_decl();
      case "StaticAssertDecl":
        return this.parse_decl_node();
      case "TemplateTemplateParmDecl":
        return this.parse_template_template_parm_decl();
      case "TemplateTypeParmDecl":
        return this.parse_template_type_parm_decl();
      case "TranslationUnitDecl":
        return this.parse_decl_node();
      case "UsingDirectiveDecl":
      case "UsingShadowDecl":
        return this.parse_using_decl();
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
      case "AttributedType":
      case "BuiltinType":
      case "CXXRecord":
      case "ClassTemplateSpecialization":
      case "ClassTemplatePartialSpecialization":
      case "DecltypeType":
      case "DependentNameType":
      case "DependentTemplateSpecializationType":
      case "ElaboratedType":
      case "Enum":
      case "EnumType":
      case "InjectedClassNameType":
      case "LValueReferenceType":
      case "ParenType":
      case "PointerType":
      case "RValueReferenceType":
      case "RecordType":
      case "SubstTemplateTypeParmType":
        return this.parse_type_node();
      case "ConstantArrayType":
        return this.parse_constant_array_type();
      case "FunctionProtoType":
        return this.parse_function_proto_type();
      case "PackExpansionType":
        return this.parse_pack_expansion_type();
      case "QualType":
        return this.parse_qual_type();
      case "TemplateSpecializationType":
        return this.parse_template_specialization_type();
      case "TemplateTypeParm":
        return this.parse_type_node();
      case "TemplateTypeParmType":
        return this.parse_template_type_parm_type();
      case "TypeAlias":
      case "Typedef":
      case "TypedefType":
        return this.parse_type_node();
      case "UnaryTransformType":
        return this.parse_unary_transform_type();
      case "CXXCtorInitializer":
        return this.parse_cxx_ctor_initializer();
      case "TemplateArgument":
        return this.parse_template_argument();
      default:
        console.error(
          `Warning: unsupported AST node: ${kind}${this.try_peek(/.*/)}`
        );
        return this.parse_unsupported_node();
    }
  }

  parse_unsupported_node() {
    return {
      raw: this.peek(/^.*/),
      ...(this.try(p => p.parse_decl_node()) ||
        this.try(p => p.parse_type_node()) ||
        this.try(p => p.parse_stmt_node()) ||
        this.try(p => p.parse_addressable_node()) ||
        {}),
      extra: this.try(/^.+/)
    };
  }

  parse_addressable_node() {
    return {
      address: this.parse_address(),
      semantic_parent: this.try(p =>
        p.skip(" parent").expect(p => p.parse_bare_ref())
      ),
      prev: this.try(p => p.skip(" prev").expect(p => p.parse_bare_ref()))
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

  parse_stmt_node() {
    return {
      ...this.parse_addressable_node(),
      source_range: this.skip(" ").expect(p => new SourceRange(p))
    };
  }

  parse_attr_node() {
    return {
      ...this.parse_stmt_node(),
      ...this.parse_flags(["Inherited", "Implicit"])
    };
  }

  parse_singleton_attr() {
    return {
      ...this.parse_attr_node(),
      attr: this.skip(" ").expect(/^[\w]+/)
    };
  }

  parse_arg_ref() {
    return { index: Number(this.skip(" ").expect(/^\d+/)) };
  }

  parse_asm_label_attr() {
    return { ...this.parse_attr_node(), label: this.expect(/^ "(.*)"/) };
  }

  parse_deprecated_attr() {
    const result = this.parse_attr_node();
    // There seems to be an always-empty string after the message.
    // Unclear what result is for.
    result.message = this.expect(/^ "(?<message>.*)" ""/).message;
    return result;
  }

  parse_diagnose_if_attr() {
    return {
      ...this.parse_attr_node(),
      message: this.expect(/^ "(.*)"/),
      diagnostic_type: this.expect(/^ DT_(Error|Warning)/),
      ...this.parse_flags(["ArgDependent"]),
      attr_parent: this.parse_decl_ref() // Probably redundant.
    };
  }

  parse_enable_if_attr() {
    return {
      ...this.parse_attr_node(),
      message: this.try(/^ "(?:(?:<no message provided>)|(.*))"/, null)
    };
  }

  parse_format_attr() {
    return {
      ...this.parse_attr_node(),
      format_kind: this.skip(" ").expect(/^\w+/),
      format: this.parse_arg_ref(),
      first_arg: this.parse_arg_ref()
    };
  }

  parse_max_field_alignment_attr() {
    return {
      ...this.parse_attr_node(),
      alignment: Number(this.skip(" ").expect(/^\d+/))
    };
  }

  parse_mode_attr() {
    return {
      ...this.parse_attr_node(),
      mode: this.expect(/^ __([QHSDT][IF]|word)__/)
    };
  }

  parse_ms_vtor_disp_attr() {
    return {
      ...this.parse_attr_node(),
      mode: ["Never", "ForVBaseOverride", "ForVFTable"][
        this.skip(" ").expect(/^\d+/)
      ]
    };
  }

  parse_non_null_attr() {
    return {
      ...this.parse_attr_node(),
      args: this.repeat(p => p.parse_arg_ref())
    };
  }

  parse_no_sanitize_attr() {
    return {
      ...this.parse_attr_node(),
      sanitizers: this.repeat(p => p.expect(/^ (\S+)/))
    };
  }

  parse_type_visibility_attr() {
    return {
      ...this.parse_attr_node(),
      type_visibility: this.parse_visibility()
    };
  }

  parse_visibility_attr() {
    return {
      ...this.parse_attr_node(),
      visibility: this.parse_visibility()
    };
  }

  parse_block_command_comment() {
    return {
      ...this.parse_stmt_node(),
      ...this.skip(" ").expect(/^Name="(?<command_name>.*)"/)
    };
  }

  parse_expr_node() {
    return {
      ...this.parse_stmt_node(),
      type: this.parse_type(),
      value_kind: this.parse_value_kind(),
      object_kind: this.parse_object_kind()
    };
  }

  parse_call_expr() {
    return {
      ...this.parse_expr_node(),
      ...this.parse_flags(["adl"]) // Argument-dependent lookup.
    };
  }

  parse_binary_operator() {
    return {
      ...this.parse_expr_node(),
      operator: this.parse_single_quoted()
    };
  }

  parse_cxx_bind_temporary_expr() {
    const result = this.parse_expr_node();
    this.skip(" (");
    result.temporary = {
      kind: this.parse_kind(),
      address: this.parse_address()
    };
    this.skip(")");
    return result;
  }

  parse_cxx_dependent_scope_member_expr() {
    return {
      ...this.parse_expr_node(),
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
    const expr = this.parse_expr_node();
    let { kind_part, flag_part } =
      this.try(
        /^(?<kind_part>.*) (?<flag_part>part_of_explicit_cast)(?=[\n\r])/
      ) || this.expect(/^(?<kind_part>.*)/);
    const { rest, ...cast_kind } = this.parse_cast_kind(kind_part);
    assert(rest === "");
    return { ...expr, ...cast_kind, part_of_explicit_cast: !!flag_part };
  }

  parse_c_style_cast_expr() {
    const expr = this.parse_expr_node();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assert(rest === "");
    return { ...expr, ...cast_kind };
  }

  parse_cxx_named_cast_expr_base() {
    const result = this.parse_expr_node();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assign(result, cast_kind);
    // The type inside the angle brackets (static_cast<this_type>) is redundant.
    // It's the same as the result type of result expression (which is parsed by
    // our base class).
    result.cast_name = /^[a-z_]+_cast(?=<.+>$)/.exec(rest)[0];
    return result;
  }

  parse_cxx_functional_cast_expr() {
    const result = this.parse_expr_node();
    const { rest, ...cast_kind } = this.parse_cast_kind();
    assign(result, cast_kind);
    // Further information in the rest is redundant.
    assert(/^functional cast to .*\S$/.test(rest));
    return result;
  }

  parse_cxx_new_expr() {
    return {
      ...this.parse_expr_node(),
      ...this.parse_flags(["array", "global"]),
      operator_new: this.try(p => p.parse_decl_ref())
    };
  }

  parse_cxx_delete_expr() {
    return {
      ...this.parse_expr_node(),
      ...this.parse_flags(["array", "global"]),
      operator_delete: this.try(p => p.parse_decl_ref())
    };
  }

  parse_cxx_this_expr() {
    return {
      ...this.parse_expr_node(),
      implicit: Boolean(this.try(" implicit")),
      name: this.skip(" ").expect("this")
    };
  }

  parse_cxx_unresolved_construct_expr() {
    const result = this.parse_expr_node();

    // This type is redundant.
    const type = this.parse_type();
    assert(type.name === result.type.name);

    assign(result, this.parse_flags(["list"]));
    return result;
  }

  parse_compound_assign_operator() {
    const result = this.parse_expr_node();
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
    return {
      ...this.parse_expr_node(),
      constructor_type: this.parse_type(),
      ...this.parse_flags([
        "elidable",
        "list",
        "std::initializer_list",
        "zeroing"
      ])
    };
  }

  parse_decl_ref_with_name() {
    return {
      ...this.parse_addressable_node(),
      name: this.parse_single_quoted()
    };
  }

  parse_decl_ref_with_name_and_type() {
    return {
      ...this.parse_decl_ref_with_name(),
      type: this.parse_type()
    };
  }

  parse_decl_ref_template() {
    return this.try(p => {
      p.expect(" (");
      const template = {
        kind: p.parse_kind(),
        ...p.parse_addressable_node(),
        name: p.parse_single_quoted()
      };
      p.expect(")");
      return template;
    });
  }

  parse_decl_ref_kind_specific(kind) {
    switch (kind) {
      case "Namespace":
      case "TemplateTypeParm":
        return { decl: this.parse_decl_ref_with_name() };

      case "CXXMethod":
      case "EnumConstant":
      case "Field":
      case "Function":
      case "Var":
        return {
          decl: this.parse_decl_ref_with_name_and_type(),
          template: this.parse_decl_ref_template()
        };

      case "NonTypeTemplateParm":
      case "ParmVar":
      case "VarTemplateSpecialization":
        return { decl: this.parse_decl_ref_with_name_and_type() };

      default:
        throw new Error(`Unsupported DeclRef kind: ${kind}`);
    }
  }

  parse_decl_ref() {
    const kind = this.parse_kind();
    const { decl, template } = this.parse_decl_ref_kind_specific(kind);
    return { decl: { kind, ...decl }, template };
  }

  parse_decl_ref_expr() {
    return {
      ...this.parse_expr_node(),
      ...this.parse_decl_ref()
    };
  }

  parse_init_list_expr() {
    return {
      ...this.parse_expr_node(),
      field: this.try(p => {
        p.expect(" field");
        return p.parse_decl_ref();
      }),
      array_filler: this.try_parse_leaf(p => {
        p.expect("array_filler: ");
        return p.parse_node();
      })
    };
  }

  parse_literal_node_base() {
    return {
      ...this.parse_expr_node(),
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
      ...this.parse_expr_node(),
      operator: this.try_skip(" ").expect(/^(\.|->)/),
      member_name: this.try(p => p.parse_name()),
      member_decl: this.parse_bare_ref()
    };
  }

  parse_size_of_pack_expr() {
    const result = this.parse_expr_node();
    result.pack = this.parse_bare_ref();
    this.parse_name(); // Name of pack; redundant.
    return result;
  }

  parse_unary_expr_or_type_trait_expr() {
    return {
      ...this.parse_expr_node(),
      operator: this.skip(" ").expect(/^[\w]+/),
      argument_type: this.try(p => p.parse_type())
    };
  }

  parse_unary_operator() {
    return {
      ...this.parse_expr_node(),
      attachment: this.skip(" ").expect(/^(?:prefix|postfix)/),
      operator: this.parse_single_quoted(),
      can_overflow: !this.try(p => p.skip(" ").expect("cannot overflow"))
    };
  }

  parse_unresolved_lookup_expr() {
    return {
      ...this.parse_expr_node(),
      unknown: this.skip(" ").expect(/^.*/)
    };
  }

  parse_goto_stmt() {
    return {
      ...this.parse_stmt_node(),
      label_name: this.parse_single_quoted(),
      label: this.parse_bare_ref()
    };
  }

  parse_if_stmt() {
    return {
      ...this.parse_stmt_node(),
      ...this.parse_flags(["has_init", "has_var", "has_else"])
    };
  }

  parse_label_stmt() {
    return {
      ...this.parse_stmt_node(),
      label_name: this.parse_single_quoted()
    };
  }

  parse_inline_command_comment() {
    return {
      ...this.parse_stmt_node(),
      command_name: this.expect(/^ Name="(.*?)"/),
      render_kind: this.expect(/^ Render(\w+)/),
      args: this.repeat(p => p.expect(/^ Arg\[\d+\]="(.*?)"/))
    };
  }

  parse_param_command_comment() {
    const result = this.parse_stmt_node();
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

  parse_decl_node() {
    return {
      ...this.parse_stmt_node(),
      source_location: this.skip(" ").expect(p => new SourceLocation(p)),
      ...this.parse_flags(["implicit", "referenced", "used", "constexpr"])
    };
  }

  parse_access_spec_decl() {
    return {
      ...this.parse_decl_node(),
      access: this.parse_access_specifier()
    };
  }

  parse_callable_decl_info() {
    return {
      // TODO: constructors have no name.
      name: this.try_skip(" ").expect(/^[^']*?(?=\s+')/),
      type: this.parse_type(),
      storage_class: this.parse_storage_class(),
      ...this.parse_flags([
        "default",
        "default_delete",
        "delete",
        "inline",
        "pure",
        "trivial",
        "virtual"
      ]),
      ...this.try(
        p => {
          p.skip(" ").expect("noexcept-");
          return {
            noexcept_spec: p.expect(/^\w+/),
            noexcept_source: p.parse_bare_ref()
          };
        },
        { noexcept_spec: undefined, noexcept_source: undefined }
      )
    };
  }

  parse_callable_decl() {
    return {
      ...this.parse_decl_node(),
      ...this.parse_callable_decl_info(),
      overrides: this.try_parse_leaf(p => {
        const overrides = [];
        p.expect("Overrides: [");
        do {
          overrides.push({
            decl: {
              ...p.parse_addressable_node(),
              ...p.parse_callable_decl_info()
            }
          });
        } while (p.try(","));
        p.expect(" ]");
      })
    };
  }

  parse_enum_decl() {
    return {
      ...this.parse_decl_node(),
      scope: this.try(p => p.skip(" ").expect(/^(?:class|struct)/), "unscoped"),
      name: this.try(p => p.parse_name()),
      type: this.try(p => p.parse_type())
    };
  }

  parse_field_decl() {
    return {
      ...this.parse_decl_node(),
      name: this.try(p => p.parse_name()),
      type: this.parse_type(),
      ...this.parse_flags(["mutable"])
    };
  }

  parse_friend_decl() {
    return {
      ...this.parse_decl_node(),
      friend_type: this.try(p => p.parse_type())
    };
  }

  parse_linkage_spec_decl() {
    return {
      ...this.parse_decl_node(),
      linkage: this.skip(" ").expect(/^C\+\+|^C/)
    };
  }

  parse_decl_node_with_name_and_type() {
    return {
      ...this.parse_decl_node(),
      name: this.parse_name(),
      type: this.parse_type()
    };
  }

  parse_indirect_field_decl() {
    const result = this.parse_decl_node_with_name_and_type();
    // Todo: parse chain (list of inline DeclRefs).
    return result;
  }

  parse_named_decl_node_base() {
    return { ...this.parse_decl_node(), name: this.parse_name() };
  }

  parse_namespace_decl() {
    return {
      ...this.parse_decl_node(),
      name: this.try(p => p.parse_name()),
      ...this.parse_flags(["inline"]),
      original: this.try_parse_leaf(p => {
        p.expect("original ");
        return p.parse_decl_ref();
      })
    };
  }

  parse_non_type_template_parm_decl() {
    return {
      ...this.parse_decl_node(),
      type: this.parse_type(),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_parm_var_decl() {
    return {
      ...this.parse_decl_node(),
      name: this.try(p => p.parse_name()),
      ...this.parse_var_type_and_properties()
    };
  }

  parse_pragma_comment_decl() {
    const result = this.parse_decl_node();
    Object.assign(
      result,
      this.skip(" ").expect(/(?<comment_kind>\w+) "(?<arg>.*)"/)
    );
    return result;
  }

  parse_pragma_detect_mismatch_decl() {
    const result = this.parse_decl_node();
    Object.assign(
      result,
      this.skip(" ").expect(/"(?<name>.+)" "(?<value>.*)"/)
    );
    return result;
  }

  parse_record_decl() {
    const result = this.parse_decl_node();
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
      ...this.parse_decl_node(),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_template_type_parm_decl() {
    return {
      ...this.parse_decl_node(),
      type_kind: this.skip(" ").expect(/^(?:class|typename)/),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator(),
      name: this.try(p => p.parse_name())
    };
  }

  parse_template_type_parm_type() {
    return {
      ...this.parse_type_node(),
      position: this.parse_template_parameter_position(),
      is_parameter_pack: this.parse_parameter_pack_indicator()
    };
  }

  parse_using_decl() {
    const result = this.parse_decl_node();
    this.parse_kind(); // Redundant.
    result.target = this.parse_bare_ref();
    this.skip(" ").skip(/^.*/); // Redundant.
    return result;
  }

  parse_var_base() {
    return {
      name: this.parse_name(),
      ...this.parse_var_type_and_properties()
    };
  }

  parse_var_decl() {
    return { ...this.parse_decl_node(), ...this.parse_var_base() };
  }

  parse_var_template_partial_specialization_decl() {
    const result = this.parse_decl_node();
    // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
    // appended to the first template argument.
    result.var = this.try(p => p.parse_var_base());
    return result;
  }

  parse_var_template_specialization_decl() {
    const result = this.parse_decl_node();
    // This info is present here from clang 9.0.0-pre. Up to v0.8 it's usually
    // appended to the first template argument.
    result.var = this.try(p => p.parse_var_base());
    return result;
  }

  parse_text_comment() {
    return { ...this.parse_stmt_node(), text: this.parse_comment_text() };
  }

  parse_verbatim_block_comment() {
    const result = this.parse_stmt_node();
    Object.assign(
      this.skip(" ").expect(
        /^Name="(?<command_name>.*)" CloseName="(?<close_command_name>.*)"/
      )
    );
    return result;
  }

  parse_verbatim_block_line_comment() {
    return { ...this.parse_stmt_node(), text: this.parse_comment_text() };
  }

  parse_type_node() {
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
    const result = this.parse_type_node();
    result.size = Number(this.skip(" ").expect(/^\d+/));
    result.array_type = this.parse_array_type();
    this.try(/^[ ]+(?= )/); // Skip extra spaces.
    assign(result, this.parse_type_qualifiers());
    this.try(" ");
    return result;
  }

  parse_function_proto_type() {
    return {
      ...this.parse_type_node(),
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

  parse_pack_expansion_type() {
    return {
      ...this.parse_type_node(),
      num_expansions: this.try(p => Number(p.expect(/^ (\d+)/)), 0)
    };
  }

  parse_qual_type() {
    return { ...this.parse_type_node(), ...this.parse_type_qualifiers() };
  }

  parse_template_specialization_type() {
    return {
      ...this.parse_type_node(),
      ...this.parse_flags(["alias"]),
      template_name: this.parse_name()
    };
  }

  parse_unary_transform_type() {
    return {
      ...this.parse_type_node(),
      unary_transform_type_kind: this.skip(" ").expect("underlying_type")
    };
  }

  parse_cxx_ctor_initializer() {
    return (
      this.try(p => ({
        // Initializer initializes a class member.
        ctor_initializer_kind: "field",
        field: p.parse_decl_ref()
      })) ||
      this.expect(p => ({
        // Initializer intializes a base class or delegates to another
        // constructor.
        ctor_initializer_kind: "record",
        type: p.parse_type()
      }))
    );
  }

  parse_template_argument_kind() {
    return this.expect(
      /^ (decl|expr|integral|null|nullptr|pack|template(?: expansion)?|type)/
    ).replace(" ", "_");
  }

  parse_template_argument_kind_specific(template_argument_kind) {
    this.fail_fast();
    switch (template_argument_kind) {
      case "decl":
        return { decl: this.parse_decl_ref() };
      case "integral":
        return { integral: this.skip(" ").expect(/^[+-]?\d+/) };
      case "template":
      case "template_expansion":
        return { template_name: this.parse_name() };
      case "type":
        // Variable info is sometimes present up to clang 8.x, starting with
        // clang 9 it's moved to the VarTemplateSpecializationDecl node.
        // So we'll eventually move the 'var' field to the parent node.
        return {
          type: this.parse_type(),
          var: this.try(p => p.parse_var_base())
        };
      case "expr":
      case "null":
      case "nullptr":
      case "pack":
        return {};
      default:
        fatal("Unexpected template argument kind.");
    }
  }

  parse_template_argument_inherited_default() {
    return (
      this.try_parse_leaf(p => ({
        status: "inherited",
        template: p.skip("inherited from").parse_decl_ref()
      })) ||
      this.try_parse_leaf(p => ({
        status: "overridden",
        template: p.skip("previous").parse_decl_ref()
      })) || { status: "none" }
    );
  }

  parse_template_argument() {
    const template_argument_kind = this.parse_template_argument_kind();
    return {
      template_argument_kind,
      ...this.parse_template_argument_kind_specific(template_argument_kind),
      inherited_default: this.parse_template_argument_inherited_default()
    };
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
    let invalid_fields = parser.try(
      /^\<(?<error>invalid sloc|scratch space|built-in)\>(:(?<line>\d+):(?<col>\d+))?/
    );
    if (invalid_fields) {
      return { valid: false, ...invalid_fields };
    }
    let valid_fields =
      parser.try(/^col:(?<col>\d+)/) ||
      parser.try(/^line:(?<line>\d+):(?<col>\d+)/) ||
      parser.try(/^line:(?<line>\d+):(?<col>\d+)/) ||
      parser.try(/^(?<file>[^>'\n]+?):(?<line>\d+):(?<col>\d+)/);
    if (valid_fields) {
      return { valid: true, ...valid_fields };
    }
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

main();
