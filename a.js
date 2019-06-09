let { readFileSync, writeFileSync } = require("fs");
require("util").inspect.defaultOptions.depth = null;
require("util").inspect.defaultOptions.maxArrayLength = null;
Error.stackTraceLimit = Infinity;

const assign = Object.assign;
const hasOwnProperty = Object.prototype.hasOwnProperty.call.bind(
  Object.prototype.hasOwnProperty
);

function main() {
  let top_level_node;
  if (true) {
    let ast_dump = readFileSync(process.argv[2] || "o3", "utf8");
    let parser = new ClangAstDumpParser(ast_dump);
    top_level_node = parser.parse_node();
    let json = JSON.stringify(top_level_node, null, 2);
    writeFileSync("dump.json", json);
  } else {
    top_level_node = require("./dump.json");
  }

  const index = Object.create(null);
  walk(top_level_node, null, node => {
    if (!node.address) return;
    if (!node.kind) return;
    if (!hasOwnProperty(index, node.address)) {
      index[node.address] = Object.create(null);
      index[node.address]._first = node.kind;
      index[node.address]._cld = 0;
      index[node.address]._kc = 0;
    }
    if (node.children.length) index[node.address]._cld++;
    if (!hasOwnProperty(index[node.address], node.kind)) {
      index[node.address][node.kind] = 0;
      index[node.address]._kc++;
    }
    index[node.address][node.kind]++;
  });
  //console.log(index);

  for (const address in index) {
    const counts = index[address];
    let total = 0;
    const kinds = [];
    for (const kind in counts) {
      if (/^_/.test(kind)) continue;
      total += counts[kind];
      kinds.push(kind);
    }
    kinds.sort();
    if (kinds.length > 1) {
      //console.log(kinds.join('\t'));
    }
  }
  //parser.skip(/^\s*$/);
  //let result = filter_v8(top_level_node);
  //console.log(JSON.stringify(result, null, 2));
}

function walk(obj, parent, cb) {
  let recurse;
  let new_parent = parent;
  if (obj.children) {
    recurse = cb(obj, parent);
    new_parent = obj;
  }
  if (recurse === undefined) {
    recurse = true;
  }
  if (recurse) {
    for (const key in obj) {
      if (!hasOwnProperty(obj, key)) continue;
      const val = obj[key];
      if (val === null) continue;
      if (typeof val !== "object") continue;
      walk(val, new_parent, cb);
    }
  }
}

function filter_v8(node) {
  function visit_children(nodes, ns) {
    return nodes.map(node => visit(node, ns)).filter(Boolean);
  }

  function recurse(node, ns) {
    let r = { ...node, children: visit_children(node.children, ns) };
    delete r.source_range;
    delete r.source_location;
    return r;
  }

  function visit(node, ns = null) {
    switch (node.kind) {
      case "TranslationUnitDecl":
        return recurse(node, ns);

      case "NamespaceDecl":
        ns = (ns ? "::" : "") + node.name;
        return ns === "v8" ? recurse(node, ns) : null;

      default:
        if (/(Expr|Stmt|Comment|FriendDecl)$/.test(node.kind)) return null;
        return ns === "v8" ? recurse(node, ns) : null;
    }
  }

  return visit(node);
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
    this.try_depth = 0;
  }

  _fail(pattern) {
    throw new NoMatch(pattern, this.str, this.orig);
  }

  _handle_no_match(err, mode) {
    if (err instanceof NoMatch) {
      switch (mode) {
        case "try":
          return;
        case "expect":
          err.throw();
        default:
          assert(false, `Unexpected mode: ${mode}`);
      }
    }
    throw err;
  }

  _dump_progress() {
    const now = Date.now();
    if (!Parser.last_log_time) {
      Parser.last_log_time = now;
      Parser.last_log_size = this.str.length;
    } else if (now - Parser.last_log_time > 1000) {
      const size = this.str.length;
      if (size !== Parser.last_log_size) {
        console.error(this.str.length);
      } else {
        throw new Error("No progress");
      }
      Parser.last_log_time = now;
      Parser.last_log_size = size;
    }
  }

  _match(matcher) {
    this._dump_progress();

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

  expect(matcher) {
    try {
      return this._match(matcher);
    } catch (err) {
      this._handle_no_match(err, "expect");
    }
  }

  try(matcher, or_else) {
    const prev = this.str;
    this.try_depth++;
    try {
      return this.match(matcher);
    } catch (err) {
      this.str = prev;
      this._handle_no_match(err, "try");
      return or_else;
    } finally {
      this.try_depth--;
    }
  }

  match(matcher) {
    if (this.try_depth === 0) {
      return this.expect(matcher);
    } else {
      return this._match(matcher);
    }
  }

  skip(matcher) {
    this.match(matcher);
    return this;
  }

  try_skip(matcher) {
    this.try(matcher);
    return this;
  }

  peek(matcher) {
    const prev = this.str;
    try {
      return this.match(matcher);
    } finally {
      this.str = prev;
    }
  }

  try_peek(matcher, or_else) {
    return this.try(p => p.peek(matcher));
  }

  repeat(matcher) {
    const results = [];
    let r;
    while ((r = this.try(matcher))) {
      results.push(r);
    }
    return results;
  }
}

const as_is = Symbol("as_is");
const neither = Symbol("neither");

class ClangAstDumpParser extends Parser {
  constructor(str) {
    super(str);
    this.prefix = "";
  }

  parse_single_quoted() {
    let value = this.skip(" '").match(/^[^']*/);
    this.skip("'");
    return value;
  }

  parse_leaf(matcher) {
    const prev_prefix = this.prefix;
    this.prefix = this.parse_prefix(prev_prefix);
    try {
      return this.match(matcher);
    } finally {
      this.prefix = prev_prefix;
    }
  }

  try_parse_leaf(matcher) {
    return this.try(p => p.parse_leaf(matcher));
  }

  parse_prefix(parent_prefix) {
    this.match(/^\r?\n/);
    return (
      this.match(parent_prefix) + this.match(/^[|`]-/).replace(/[`\-]/g, " ")
    );
  }

  parse_kind() {
    return this.try_skip(" ").match(/^(?:[A-Z]\w*\b|<<<NULL>>>)/);
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
    return this.skip(" ").match(/^0x[\da-f]+/);
  }

  parse_name() {
    let name = this.try_skip(" ").match(
      /^(?:operator(?:[ \t]*[^\s\d'][^\s']*)+|::|~|[a-zA-Z_](?:\w*))+<?/
    );
    if (!/</.test(name) || /operator/.test(name)) return name;

    const count = re => {
      let matches = name.match(re);
      return (matches && matches.length) || 0;
    };
    while (count(/</g) > count(/>/g)) {
      name += this.match(/^.*?>/);
    }
    return name;
  }

  parse_type() {
    return this.try_skip(" ").match(
      /^'(?<name>[^']*)'(?::'(?<desugared>[^']*)')?/
    );
  }

  parse_value_kind() {
    return this.parse_simple_enum({
      lvalue: as_is,
      xvalue: as_is,
      rvalue: neither
    });
  }

  parse_object_kind() {
    return this.parse_simple_enum({
      bitfield: as_is,
      objcproperty: as_is,
      objcsubscript: as_is,
      vectorcomponent: as_is,
      ordinary: neither
    });
  }

  parse_bare_ref() {
    return { address: this.parse_address() };
  }

  parse_template_parameter_position() {
    return {
      depth: Number(this.skip(" depth ").match(/^\d+/)),
      index: Number(this.skip(" index ").match(/^\d+/))
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
    return this.parse_simple_enum({
      static: as_is,
      start: "*",
      normal: neither
    });
  }

  parse_visibility() {
    return this.parse_simple_enum({
      default: "Default",
      hidden: "Hidden",
      protected: "Protected"
    });
  }

  parse_storage_class() {
    return this.parse_simple_enum({
      auto: as_is,
      extern: as_is,
      static: as_is,
      register: as_is,
      none: neither
    });
  }

  parse_tls_kind() {
    return this.parse_simple_enum({
      static: "tls",
      dynamic: "tls_dynamic",
      none: neither
    });
  }

  parse_var_flags() {
    return this.parse_flags(["nrvo", "inline", "constexpr"]);
  }

  parse_var_type_and_properties() {
    return {
      type: this.parse_type(),
      storage_class: this.parse_storage_class(),
      tls_kind: this.parse_tls_kind(),
      ...this.parse_var_flags(),
      init_style: this.parse_init_style()
    };
  }

  parse_init_style() {
    return this.parse_simple_enum({
      c: "cinit",
      call: "callinit",
      list: "listinit",
      none: neither
    });
  }

  parse_access_specifier() {
    return this.parse_simple_enum({
      private: as_is,
      protected: as_is,
      public: as_is,
      none: neither
    });
  }

  parse_comment_text() {
    return this.skip(" ").match(/^Text="(?<text>.*)"/).text;
  }

  parse_flags(flags) {
    const result = {};
    outer: while (flags.length) {
      for (let i = 0; i < flags.length; i++) {
        const flag = flags[i];
        if (
          this.try(p => {
            p.skip(" ");
            p.match(flag);
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

  parse_simple_enum(mappings) {
    let default_mapping;
    for (const key in mappings) {
      if (!hasOwnProperty(mappings, key)) continue;
      let matcher = mappings[key];
      if (matcher === as_is) {
        matcher = key;
      } else if (matcher === neither) {
        assert(default_mapping === undefined);
        default_mapping = key;
        continue;
      }
      if (
        this.try(p => {
          p.try_skip(" ");
          p.match(matcher);
          p.peek(/^\s|$/);
          return true;
        })
      ) {
        return key;
      }
    }
    if (default_mapping !== undefined) {
      return default_mapping;
    }
    this._fail(mappings);
  }

  parse_node_kind_specific(kind) {
    return this.expect(p => {
      //console.log(kind, p.try_peek(/^.*/));
      switch (kind) {
        case "<<<NULL>>>":
          return {};

        // Comment
        case "FullComment":
        case "ParagraphComment":
          return p.parse_comment_node();
        case "BlockCommandComment":
          return p.parse_block_command_comment();
        case "InlineCommandComment":
          return p.parse_inline_command_comment();
        case "ParamCommandComment":
          return p.parse_param_command_comment();
        case "TextComment":
          return p.parse_text_comment();
        case "VerbatimBlockComment":
          return p.parse_verbatim_block_comment();
        case "VerbatimBlockLineComment":
          return p.parse_verbatim_block_line_comment();

        // Decl
        // Decl: basic (no properties)
        case "EmptyDecl":
        case "FileScopeAsmDecl":
        case "StaticAssertDecl":
        case "TranslationUnitDecl":
          return p.parse_decl_node();
        // Decl: named
        case "BuiltinTemplateDecl":
        case "ClassTemplateDecl":
        case "FunctionTemplateDecl":
        case "TypeAliasTemplateDecl":
        case "UnresolvedUsingTypenameDecl":
        case "UsingDecl":
        case "VarTemplateDecl":
          return p.parse_named_decl_node_base();
        // Decl: named and typed
        case "EnumConstantDecl":
        case "TypeAliasDecl":
        case "TypedefDecl":
        case "UnresolvedUsingValueDecl":
          return p.parse_decl_node_with_name_and_type();
        // Decl: records (struct, class, union).
        case "CXXRecordDecl":
        case "ClassTemplatePartialSpecializationDecl":
        case "ClassTemplateSpecializationDecl":
          return p.parse_record_decl();
        // Decl: functions, methods and other "callable" things.
        case "FunctionDecl":
        case "MethodDecl":
          return this.parse_function_decl();
        case "CXXConstructorDecl":
          return this.parse_cxx_constructor_decl();
        case "CXXConversionDecl":
        case "CXXDestructorDecl":
        case "CXXMethodDecl":
          return this.parse_cxx_method_decl();
        // Decl: other
        case "AccessSpecDecl":
          return p.parse_access_spec_decl();
        case "EnumDecl":
          return p.parse_enum_decl();
        case "FieldDecl":
          return p.parse_field_decl();
        case "FriendDecl":
          return p.parse_friend_decl();
        case "LinkageSpecDecl":
          return p.parse_linkage_spec_decl();
        case "IndirectFieldDecl":
          return p.parse_indirect_field_decl();
        case "NamespaceDecl":
          return p.parse_namespace_decl();
        case "NonTypeTemplateParmDecl":
          return p.parse_non_type_template_parm_decl();
        case "ParmVarDecl":
          return p.parse_parm_var_decl();
        case "PragmaCommentDecl":
          return p.parse_pragma_comment_decl();
        case "PragmaDetectMismatchDecl":
          return p.parse_pragma_detect_mismatch_decl();
        case "TemplateTemplateParmDecl":
          return p.parse_template_template_parm_decl();
        case "TemplateTypeParmDecl":
          return p.parse_template_type_parm_decl();
        case "UsingDirectiveDecl":
        case "UsingShadowDecl":
          return p.parse_using_decl();
        case "VarDecl":
          return p.parse_var_decl();
        case "VarTemplatePartialSpecializationDecl":
          return p.parse_var_template_partial_specialization_decl();
        case "VarTemplateSpecializationDecl":
          return p.parse_var_template_specialization_decl();

        // Template argument.
        case "TemplateArgument":
          return p.parse_template_argument();

        // Type
        case "AttributedType":
        case "BuiltinType":
        case "DecltypeType":
        case "DependentNameType":
        case "DependentTemplateSpecializationType":
        case "ElaboratedType":
        case "EnumType":
        case "InjectedClassNameType":
        case "LValueReferenceType":
        case "ParenType":
        case "PointerType":
        case "RValueReferenceType":
        case "RecordType":
        case "SubstTemplateTypeParmType":
        case "TypedefType":
          return p.parse_type_node();
        case "ConstantArrayType":
          return p.parse_constant_array_type();
        case "FunctionProtoType":
          return p.parse_function_proto_type();
        case "PackExpansionType":
          return p.parse_pack_expansion_type();
        case "QualType":
          return p.parse_qual_type();
        case "TemplateSpecializationType":
          return p.parse_template_specialization_type();
        case "TemplateTypeParmType":
          return p.parse_template_type_parm_type();
        case "UnaryTransformType":
          return p.parse_unary_transform_type();

        // Attr
        // Attr: basic (no properties)
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
          return p.parse_attr_node();
        // Attr: singleton (e.g. `AlignedAttr aligned`)
        case "AlignedAttr":
        case "AlwaysInlineAttr":
        case "FinalAttr":
        case "RestrictAttr":
        case "WarnUnusedResultAttr":
          return p.parse_singleton_attr();
        // Attr: visibility (private/public etc)
        case "TypeVisibilityAttr":
        case "VisibilityAttr":
          return p.parse_visibility_attr();
        // Attr: other
        case "AsmLabelAttr":
          return p.parse_asm_label_attr();
        case "DeprecatedAttr":
          return p.parse_deprecated_attr();
        case "DiagnoseIfAttr":
          return p.parse_diagnose_if_attr();
        case "EnableIfAttr":
          return p.parse_enable_if_attr();
        case "FormatAttr":
          return p.parse_format_attr();
        case "ModeAttr":
          return p.parse_mode_attr();
        case "MSVtorDispAttr":
          return p.parse_ms_vtor_disp_attr();
        case "MaxFieldAlignmentAttr":
          return p.parse_max_field_alignment_attr();
        case "NonNullAttr":
          return p.parse_non_null_attr();
        case "NoSanitizeAttr":
          return p.parse_no_sanitize_attr();

        // Ctor initializer.
        case "CXXCtorInitializer":
          return p.parse_cxx_ctor_initializer();

        // Stmt
        // Stmt: basic (no properties)
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
        case "NullStmt":
        case "ReturnStmt":
        case "SwitchStmt":
        case "WhileStmt":
          return p.parse_stmt_node();

        // Stmt: other non-expression statements.
        case "GotoStmt":
          return p.parse_goto_stmt();
        case "IfStmt":
          return p.parse_if_stmt();
        case "LabelStmt":
          return p.parse_label_stmt();

        // Stmt:Expr
        // Stmt:Expr: basic (no properties)
        case "ArrayInitIndexExpr":
        case "ArrayInitLoopExpr":
        case "ArraySubscriptExpr":
        case "AtomicExpr":
        case "CXXDefaultArgExpr":
        case "CXXDefaultInitExpr":
        case "CXXNoexceptExpr":
        case "CXXNullPtrLiteralExpr":
        case "CXXPseudoDestructorExpr":
        case "CXXScalarValueInitExpr":
        case "GNUNullExpr":
        case "CXXThrowExpr":
        case "CXXTypeidExpr":
        case "ConstantExpr":
        case "DependentScopeDeclRefExpr":
        case "ExprWithCleanups":
        case "ImplicitValueInitExpr":
        case "LambdaExpr":
        case "MaterializeTemporaryExpr":
        case "OpaqueValueExpr":
        case "PackExpansionExpr":
        case "ParenExpr":
        case "ParenListExpr":
        case "UnresolvedMemberExpr":
        case "SubstNonTypeTemplateParmExpr":
        case "TypeTraitExpr":
          return p.parse_expr_node();
        // Stmt:Expr: casts
        case "ImplicitCastExpr":
          return p.parse_implicit_cast_expr();
        case "CStyleCastExpr":
          return p.parse_c_style_cast_expr();
        case "CXXFunctionalCastExpr":
          return p.parse_cxx_functional_cast_expr();
        case "CXXConstCastExpr":
        case "CXXDynamicCastExpr":
        case "CXXReinterpretCastExpr":
        case "CXXStaticCastExpr":
          return p.parse_cxx_named_cast_expr_base();

        // Stmt:Expr: call and construct
        case "CallExpr":
        case "CXXMemberCallExpr":
        case "CXXOperatorCallExpr":
          return p.parse_call_expr();
        case "CXXConstructExpr":
        case "CXXTemporaryObjectExpr":
          return p.parse_construct_expr_base();
        // Stmt:Expr: other non-literal and non-operator
        case "CXXBindTemporaryExpr":
          return p.parse_cxx_bind_temporary_expr();
        case "CXXBoolLiteralExpr":
          return p.parse_cxx_bool_literal_expr();
        case "CXXDeleteExpr":
          return p.parse_cxx_delete_expr();
        case "CXXDependentScopeMemberExpr":
          return p.parse_cxx_dependent_scope_member_expr();
        case "CXXNewExpr":
          return p.parse_cxx_new_expr();
        case "CXXThisExpr":
          return p.parse_cxx_this_expr();
        case "CXXUnresolvedConstructExpr":
          return p.parse_cxx_unresolved_construct_expr();
        case "DeclRefExpr":
          return p.parse_decl_ref_expr();
        case "InitListExpr":
          return p.parse_init_list_expr();
        case "MemberExpr":
          return p.parse_member_expr();
        case "SizeOfPackExpr":
          return p.parse_size_of_pack_expr();
        case "UnaryExprOrTypeTraitExpr":
          return p.parse_unary_expr_or_type_trait_expr();
        case "UnresolvedLookupExpr":
          return p.parse_unresolved_lookup_expr();

        // Stmt:Expr:Literal
        case "CharacterLiteral":
        case "FloatingLiteral":
        case "IntegerLiteral":
        case "StringLiteral":
          return p.parse_literal_node_base();

        // Stmt:Expr:Operator
        case "BinaryOperator":
          return p.parse_binary_operator();
        case "CompoundAssignOperator":
          return p.parse_compound_assign_operator();
        case "ConditionalOperator":
          return p.parse_expr_node();
        case "UnaryOperator":
          return p.parse_unary_operator();

        default:
          // DeclRef
          const decl_ref = this.parse_decl_ref_kind_specific(kind);
          if (decl_ref) {
            return decl_ref;
          }

          console.error(
            `Warning: unsupported AST node: ${kind}${p.try_peek(/.*/)}`
          );
          return p.parse_unsupported_node();
      }
    });
  }

  parse_unsupported_node() {
    return {
      raw: this.peek(/^.*/),
      ...(this.try(p => p.parse_decl_node()) ||
        this.try(p => p.parse_stmt_node()) ||
        this.try(p => p.parse_type_node()) ||
        {}),
      extra: this.try(/^.+/)
    };
  }

  parse_stmt_node() {
    return {
      address: this.parse_address(),
      source_range: this.skip(" ").parse_source_range()
    };
  }

  parse_attr_node() {
    return {
      address: this.parse_address(),
      source_range: this.skip(" ").parse_source_range(),
      ...this.parse_flags(["Inherited", "Implicit"])
    };
  }

  parse_singleton_attr() {
    return {
      ...this.parse_attr_node(),
      attr: this.skip(" ").match(/^[\w]+/)
    };
  }

  parse_arg_ref() {
    return { index: Number(this.skip(" ").match(/^\d+/)) };
  }

  parse_asm_label_attr() {
    return { ...this.parse_attr_node(), label: this.match(/^ "(.*)"/) };
  }

  parse_deprecated_attr() {
    const result = this.parse_attr_node();
    // There seems to be an always-empty string after the message.
    // Unclear what result is for.
    result.message = this.match(/^ "(?<message>.*)" ""/).message;
    return result;
  }

  parse_diagnose_if_attr() {
    return {
      ...this.parse_attr_node(),
      message: this.match(/^ "(.*)"/),
      diagnostic_type: this.parse_simple_enum({
        error: "DT_Error",
        warning: "DT_Warning"
      }),
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
      format_kind: this.skip(" ").match(/^\w+/),
      format: this.parse_arg_ref(),
      first_arg: this.parse_arg_ref()
    };
  }

  parse_max_field_alignment_attr() {
    return {
      ...this.parse_attr_node(),
      alignment: Number(this.skip(" ").match(/^\d+/))
    };
  }

  parse_mode_attr() {
    return {
      ...this.parse_attr_node(),
      mode: this.match(/^ __([QHSDT][IF]|word)__/)
    };
  }

  parse_ms_vtor_disp_attr() {
    return {
      ...this.parse_attr_node(),
      mode: this.parse_simple_enum({
        never: "0",
        for_virtual_base_override: "1",
        for_virtual_function_table: "2"
      })
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
      sanitizers: this.repeat(p => p.match(/^ (\S+)/))
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
      ...this.parse_comment_node(),
      ...this.skip(" ").match(/^Name="(?<command_name>.*)"/)
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
      operator: this.try_skip(" ").match(/^(\.|->)/),
      member_name: this.parse_name()
    };
  }

  parse_cast_kind(line = this.match(/^.*/)) {
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
      ) || this.match(/^(?<kind_part>.*)/);
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
      name: this.skip(" ").match("this")
    };
  }

  parse_cxx_unresolved_construct_expr() {
    const expr = this.parse_expr_node();

    // This type is redundant.
    const type = this.parse_type();
    assert(type.name === expr.type.name);

    return {
      ...expr,
      ...this.parse_flags(["list"])
    };
  }

  parse_compound_assign_operator() {
    const result = this.parse_expr_node();
    result.operator = this.parse_single_quoted();
    this.skip(" ").match("ComputeLHSTy=");
    result.computation_lhs_type = this.parse_type();
    this.skip(" ").match("ComputeResultTy=");
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
      address: this.parse_address(),
      name: this.parse_single_quoted()
    };
  }

  parse_decl_ref_with_name_and_type() {
    return {
      ...this.parse_decl_ref_with_name(),
      type: this.parse_type()
    };
  }

  parse_decl_ref_kind_specific(kind) {
    switch (kind) {
      case "Namespace":
      case "TemplateTypeParm":
      case "ClassTemplatePartialSpecialization":
      case "ClassTemplateSpecialization":
      case "CXXRecord":
      case "Enum":
      case "TypeAlias":
      case "Typedef":
        return this.parse_decl_ref_with_name();

      case "CXXMethod":
      case "EnumConstant":
      case "Field":
      case "Function":
      case "Var":
      case "TemplateTypeParm":
      case "NonTypeTemplateParm":
      case "ParmVar":
      case "VarTemplateSpecialization":
        return this.parse_decl_ref_with_name_and_type();

      default:
        throw new Error(`Unsupported DeclRef kind: ${kind}`);
    }
  }

  parse_decl_ref() {
    const kind = this.parse_kind();
    const specific = this.parse_decl_ref_kind_specific(kind);
    if (!specific) {
      throw new Error(`Unsupported DeclRef kind: ${kind}`);
    }
    return { kind, ...specific };
  }

  parse_decl_ref_expr_template_ref() {
    this.match(" (");
    const template = this.expect(() => ({
      kind: this.parse_kind(),
      address: this.parse_address(),
      name: this.parse_single_quoted()
    }));
    this.expect(")");
    return template;
  }

  parse_decl_ref_expr() {
    return {
      ...this.parse_expr_node(),
      decl: this.parse_decl_ref(),
      template: this.try(() => this.parse_decl_ref_expr_template_ref())
    };
  }

  parse_init_list_expr() {
    return {
      ...this.parse_expr_node(),
      field: this.try(p => {
        p.match(" field");
        return p.parse_decl_ref();
      }),
      array_filler: this.try_parse_leaf(p => {
        p.match("array_filler: ");
        return p.parse_node();
      })
    };
  }

  parse_literal_node_base() {
    return {
      ...this.parse_expr_node(),
      source: this.skip(" ").match(/^.*\S/)
    };
  }

  parse_cxx_bool_literal_expr() {
    const result = this.parse_literal_node_base();
    result.bool_value = JSON.parse(result.source);
    return result;
  }

  parse_member_expr() {
    return {
      ...this.parse_expr_node(),
      operator: this.try_skip(" ").match(/^(\.|->)/),
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
      operator: this.skip(" ").match(/^[\w]+/),
      argument_type: this.try(p => p.parse_type())
    };
  }

  parse_unary_operator_attachment() {
    return this.parse_simple_enum({
      prefix: as_is,
      postfix: as_is
    });
  }

  parse_unary_operator() {
    return {
      ...this.parse_expr_node(),
      attachment: this.parse_unary_operator_attachment(),
      operator: this.parse_single_quoted(),
      can_overflow: !this.try(p => p.skip(" ").match("cannot overflow"))
    };
  }

  parse_unresolved_lookup_expr() {
    return {
      ...this.parse_expr_node(),
      unknown: this.skip(" ").match(/^.*/)
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
      ...this.parse_comment_node(),
      command_name: this.match(/^ Name="(.*?)"/),
      render_kind: this.match(/^ Render(\w+)/),
      args: this.repeat(p => p.match(/^ Arg\[\d+\]="(.*?)"/))
    };
  }

  parse_param_direction() {
    return this.parse_simple_enum({
      in: "[in]",
      out: "[out]",
      in_out: "[in,out]"
    });
  }

  parse_param_command_comment() {
    const result = this.parse_comment_node();
    result.direction = this.parse_param_direction();
    this.skip(" ");
    result.has_explicit_direction =
      this.try("explicitly") || !this.match("implicitly");
    result.param_name = this.try(p => {
      p.skip(" ");
      p.match('Param="');
      const param_name = p.match(/^\w+/);
      p.match('"');
      return param_name;
    });
    result.param_index = this.try(p => {
      p.skip(" ");
      p.match("ParamIndex=");
      return Number(p.match(/^\d+/));
    });
    return result;
  }

  parse_decl_node() {
    return {
      address: this.parse_address(),
      semantic_parent: this.try(() => {
        this.match(" parent");
        return this.parse_bare_ref();
      }),
      prev: this.try(() => {
        this.match(" prev");
        return this.parse_bare_ref();
      }),
      source_range: this.skip(" ").parse_source_range(),
      source_location: this.skip(" ").parse_source_location(),
      ...this.parse_flags(["implicit", "referenced", "used", "constexpr"])
    };
  }

  parse_access_spec_decl() {
    return {
      ...this.parse_decl_node(),
      access: this.parse_access_specifier()
    };
  }

  parse_function_flags() {
    return this.parse_flags([
      "default",
      "default_delete",
      "delete",
      "inline",
      "pure",
      "trivial",
      "virtual"
    ]);
  }

  parse_function_exception_spec_info() {
    if (this.try(" noexcept-unevaluated")) {
      return { noexcept: "unevaluated", source_decl: this.parse_bare_ref() };
    } else if (this.try(" noexcept-uninstantiated")) {
      return {
        noexcept: "uninstantiated",
        source_template: this.parse_bare_ref()
      };
    } else {
      return { noexcept: "other" };
    }
  }

  parse_function_qualifiers() {
    return {
      storage_class: this.parse_storage_class(),
      ...this.parse_function_flags(),
      exception_spec_info: this.parse_function_exception_spec_info()
    };
  }

  parse_function_decl() {
    return {
      ...this.parse_decl_node_with_name_and_type(),
      ...this.parse_function_qualifiers()
    };
  }

  parse_cxx_constructor_decl() {
    // Clang doesn't always output a name for constructors,
    // but sometimes it does. If there is no name we'll find
    // two spaces before the type.
    return {
      ...this.parse_decl_node(),
      name: this.try(/^ (?= )/) ? null : this.parse_name(),
      type: this.parse_type(),
      ...this.parse_function_qualifiers()
    };
  }

  parse_cxx_method_overridden_methods() {
    let overridden_methods = [];
    if (this.try_parse_leaf("Overrides: [")) {
      do {
        this.expect(() => {
          overridden_methods.push({
            address: this.parse_address(),
            name: this.parse_name(),
            type: this.parse_type()
          });
        });
      } while (this.try(","));
      this.expect(" ]");
    }
    return overridden_methods;
  }

  parse_cxx_method_decl() {
    return {
      ...this.parse_function_decl(),
      overridden_methods: this.parse_cxx_method_overridden_methods()
    };
  }
  /*
  parse_callable_decl_info() {
    return {
      // TODO: constructors have no name.
      name: this.try_skip(" ").match(/^[^']*?(?=\s+')/),
      type: this.parse_type(),
      storage_class: this.parse_storage_class(),
      ...this.parse_function_flags(),
      exception_spec_info: this.parse_function_exception_spec_info()
    };
  }

  parse_callable_decl() {
    return {
      ...this.parse_decl_node(),
      ...this.parse_callable_decl_info(),
      overrides: this.try_parse_leaf(() => {
        const overrides = [];
        this.match("Overrides: [");
        do {
          overrides.push(this.expect(() => ({
              address: this.parse_address(),
              ...this.parse_callable_decl_info()
          })));
        } while (this.try(","));
        this.expect(" ]");
      })
    };
  }*/

  parse_enum_decl() {
    return {
      ...this.parse_decl_node(),
      scope: this.parse_simple_enum({
        class: as_is,
        struct: as_is,
        union: as_is,
        unscoped: neither
      }),
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
      linkage: this.skip(" ").match(/^C\+\+|^C/)
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
        p.match("original ");
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
      this.skip(" ").match(/(?<comment_kind>\w+) "(?<arg>.*)"/)
    );
    return result;
  }

  parse_pragma_detect_mismatch_decl() {
    const result = this.parse_decl_node();
    Object.assign(result, this.skip(" ").match(/"(?<name>.+)" "(?<value>.*)"/));
    return result;
  }

  parse_cxx_base_specifier() {
    return {
      // CXXBaseSpecifier isn't really an AST node in clang, but it's often
      // treated as such, e.g. in libclang. So we mimick that and give it a
      // `kind` property.
      kind: "CXXBaseSpecifier",
      virtual: Boolean(this.try("virtual")),
      access: this.parse_access_specifier(),
      type: this.parse_type(),
      pack_expansion: this.parse_parameter_pack_indicator()
    };
  }

  parse_record_kind() {
    return this.parse_simple_enum({
      class: as_is,
      struct: as_is,
      union: as_is,
      interface: as_is,
      enum: as_is
    });
  }

  parse_record_decl() {
    const result = this.parse_decl_node();
    result.record_kind = this.parse_record_kind();
    // Ambiguity is unavoidable here - just never call your class 'definition'.
    // TODO: disambiguate using color output?
    if (!this.try_peek(/^ definition(?=\r?\n)/)) {
      result.name = this.parse_name();
    }
    if (this.try(p => p.skip(" ").match("definition"))) {
      result.is_definition = true;
      result.definition = this.parse_leaf(p => new RecordDefinition(p, result));
      result.bases = this.repeat(p =>
        p.parse_leaf(p => p.parse_cxx_base_specifier())
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

  parse_template_type_parm_type_kind() {
    return this.parse_simple_enum({
      class: as_is,
      typename: as_is
    });
  }

  parse_template_type_parm_decl() {
    return {
      ...this.parse_decl_node(),
      type_kind: this.parse_template_type_parm_type_kind(),
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

  parse_comment_node() {
    return {
      address: this.parse_address(),
      source_range: this.skip(" ").parse_source_range()
    };
  }

  parse_text_comment() {
    return { ...this.parse_comment_node(), text: this.parse_comment_text() };
  }

  parse_verbatim_block_comment() {
    const result = this.parse_comment_node();
    Object.assign(
      this.skip(" ").match(
        /^Name="(?<command_name>.*)" CloseName="(?<close_command_name>.*)"/
      )
    );
    return result;
  }

  parse_verbatim_block_line_comment() {
    return { ...this.parse_comment_node(), text: this.parse_comment_text() };
  }

  parse_type_node() {
    return {
      address: this.parse_address(),
      type: this.parse_type(),
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
    result.size = Number(this.skip(" ").match(/^\d+/));
    result.array_type = this.parse_array_type();
    this.try(/^[ ]+(?= )/); // Skip extra spaces.
    assign(result, this.parse_type_qualifiers());
    this.try(" ");
    return result;
  }

  parse_function_ref_qualifier() {
    return this.parse_simple_enum({
      lvalue: "&",
      rvalue: "&&",
      none: neither
    });
  }

  parse_function_calling_convention() {
    return this.parse_simple_enum({
      cdecl: as_is,
      stdcall: as_is,
      fastcall: as_is,
      thiscall: as_is,
      pascal: as_is,
      vectorcall: as_is,
      ms_abi: as_is,
      sysv_abi: as_is,
      regcall: as_is,
      aapcs: as_is,
      aapcs_vfp: "aapcs-vfp",
      aarch64_vector_pcs: as_is,
      intel_ocl_bicc: as_is,
      spir_function: as_is,
      opencl_kernel: as_is,
      swiftcall: as_is,
      preserve_most: as_is,
      preserve_all: as_is
    });
  }

  parse_function_proto_type() {
    return {
      ...this.parse_type_node(),
      ...this.parse_flags(["trailing_return"]),
      ...this.parse_type_qualifiers(),
      ...this.parse_flags(["variadic"]),
      ref_qualifier: this.parse_function_ref_qualifier(),
      ...this.parse_flags(["noreturn", "produces_result", "regparm"]),
      calling_convention: this.parse_function_calling_convention()
    };
  }

  parse_pack_expansion_type() {
    return {
      ...this.parse_type_node(),
      num_expansions: this.try(p => Number(p.match(/^ (\d+)/)), 0)
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

  parse_unary_transform_type_utt_kind() {
    return this.parse_simple_enum({
      enum_underlying_type: "underlying_type"
    });
  }

  parse_unary_transform_type() {
    return {
      ...this.parse_type_node(),
      utt_kind: this.parse_unary_transform_type_utt_kind()
    };
  }

  parse_cxx_ctor_initializer() {
    return (
      this.try(p => ({
        // Initializer initializes a class member.
        ctor_initializer_kind: "field",
        field: p.parse_decl_ref()
      })) ||
      this.match(p => ({
        // Initializer intializes a base class or delegates to another
        // constructor.
        ctor_initializer_kind: "record",
        type: p.parse_type()
      }))
    );
  }

  parse_template_argument_kind() {
    return this.parse_simple_enum({
      decl: as_is,
      expr: as_is,
      integral: as_is,
      null: as_is,
      nullptr: as_is,
      pack: as_is,
      template: /^template(?! expansion)/,
      template_expansion: "template expansion",
      type: as_is
    });
  }

  parse_template_argument_kind_specific(template_argument_kind) {
    return this.expect(p => {
      switch (template_argument_kind) {
        case "decl":
          return { decl: p.parse_decl_ref() };
        case "integral":
          return { integral: p.skip(" ").match(/^[+-]?\d+/) };
        case "template":
        case "template_expansion":
          return { template_name: p.parse_name() };
        case "type":
          // Variable info is sometimes present up to clang 8.x, starting with
          // clang 9 it's moved to the VarTemplateSpecializationDecl node.
          // So we'll eventually move the 'var' field to the parent node.
          return {
            type: p.parse_type(),
            var: p.try(p => p.parse_var_base())
          };
        case "expr":
        case "null":
        case "nullptr":
        case "pack":
          return {};
        default:
          fatal("Unmatched template argument kind.");
      }
    });
  }

  parse_template_argument_inherited_default() {
    return (
      this.try_parse_leaf(p => ({
        status: "inherited",
        template: p.skip("inherited from").expect(p => p.parse_decl_ref())
      })) ||
      this.try_parse_leaf(p => ({
        status: "overridden",
        template: p.skip("previous").expect(p => p.parse_decl_ref())
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

  parse_source_range() {
    this.match("<");
    const start = this.parse_source_location();
    const end = this.try(() => {
      this.match(", ");
      return this.parse_source_location();
    });
    this.match(">");
    return { start, end };
  }

  parse_source_location() {
    let invalid_fields = this.try(
      /^\<(?<error>invalid sloc|scratch space|built-in)\>(:(?<line>\d+):(?<col>\d+))?/
    );
    if (invalid_fields) {
      return { valid: false, ...invalid_fields };
    }
    let valid_fields =
      this.try(/^col:(?<col>\d+)/) ||
      this.try(/^line:(?<line>\d+):(?<col>\d+)/) ||
      this.try(/^line:(?<line>\d+):(?<col>\d+)/) ||
      this.try(/^(?<file>[^>'\n]+?):(?<line>\d+):(?<col>\d+)/);
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
    const top_level_flags = parser.match(p => this.parse_top_level_flags(p));
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
    parser.match("DefinitionData");
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
    parser.match(identifier);
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
        match: parser => parser.skip(" ").match(flag) === flag,
        on_match: _ => (result[flag] = true),
        on_unmatch: () => (result[flag] = false)
      }))
    );
    return result;
  }
}

main();
