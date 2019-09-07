#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING

#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/PrettyPrinter.h"
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

#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <variant>

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

class Matchers {
public:
  template <typename M>
  static auto inDeclContext(M m) {
    return anyOf(m, hasDeclContext(m), hasDeclContext(hasAncestor(m)));
  }

  template <typename M>
  static auto isOrHasAncestor(M m) {
    return anyOf(m, hasAncestor(m));
  }

  template <typename M>
  static auto unlessUnder(M m) {
    return unless(anyOf(m, hasAncestor(m)));
  }

  static auto inV8Namespace() {
    return decl(
        inDeclContext(namespaceDecl(hasName("::v8"))),
        unless(inDeclContext(namespaceDecl(hasName("::v8::internal")))));
  }

  static auto pubApi() {
    return decl(unless(hasAncestor(stmt())),
                unlessUnder(namespaceDecl(isAnonymous())),
                unlessUnder(isPrivate()),
                // unlessUnder(decl(
                //   isProtected(),
                //   unless(hasParent(cxxRecordDecl(hasMethod(isVirtual())))))),
                // unlessUnder(parmVarDecl()),
                // unlessUnder(indirectFieldDecl()),
                // unlessUnder(templateTypeParmDecl()),
                unlessUnder(friendDecl()),
                unlessUnder(accessSpecDecl()));
  }

  static auto anyV8Api() {
    return decl(inV8Namespace(), pubApi());
  }
};

class InvokableDeclAction : public MatchFinder::MatchCallback {
  ASTContext& ast_;
  PrintingPolicy pp_;

public:
  explicit InvokableDeclAction(ASTContext& ast)
      : ast_(ast), pp_(ast_.getLangOpts()) {
    // Ensure that printing types yields valid C++. This ensures:
    //   - tags ('class' etc) are not printed in type specifiers.
    //   - 'bool' is used rather than '_Bool'.
    pp_.adjustForCPlusPlus();
  }

private:
  std::unordered_set<const Decl*> seen;

  void printDecl(const Decl* decl) {
    auto named_decl = dyn_cast<NamedDecl>(decl);

    clang::QualType signature;
    std::string value;
    static const char* wrapper_template;

    do {
      auto ctor_decl = dyn_cast<CXXConstructorDecl>(decl);
      if (ctor_decl) {
        if (ctor_decl->isDeleted())
          return;
        auto mem_qty = ctor_decl->getType();
        auto cls_ty = ctor_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        wrapper_template = "pick_constructor_v";
        break;
      }

      auto dtor_decl = dyn_cast<CXXDestructorDecl>(decl);
      if (dtor_decl) {
        if (dtor_decl->isDeleted())
          return;
        auto mem_qty = dtor_decl->getType();
        auto cls_ty = dtor_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        wrapper_template = "pick_destructor_v";
        break;
      }

      auto method_decl = dyn_cast<CXXMethodDecl>(decl);
      if (method_decl && method_decl->isInstance()) {
        if (method_decl->isDeleted())
          return;
        auto mem_qty = method_decl->getType();
        auto cls_ty = method_decl->getParent()->getTypeForDecl();
        signature = ast_.getMemberPointerType(mem_qty, cls_ty);
        value = std::string("&") + named_decl->getQualifiedNameAsString();
        wrapper_template = "pick_overload_v";
        break;
      }

      auto fn_decl = dyn_cast<FunctionDecl>(decl);
      if (fn_decl) {
        if (fn_decl->isDeleted())
          return;
        auto fn_ty = decl->getFunctionType();
        auto fn_qty = QualType(fn_ty, 0);
        signature = ast_.getPointerType(fn_qty);
        value = std::string("&") + named_decl->getQualifiedNameAsString();
        wrapper_template = "pick_overload_v";
        break;
      }

      // Otherwise, we're not interested.
      return;
    } while (false);

    // Canonicalize the type name.
    signature = signature.getCanonicalType();

    // Do not write out instantiation-dependent types.
    if (signature->isInstantiationDependentType())
      return;

    std::ostringstream os;
    os << "  X_" << decl->getDeclKindName() << "(( " << wrapper_template << "<"
       << signature.getAsString(pp_);
    if (!value.empty()) {
      os << ", " << value;
    }
    os << "> ))\n";
    auto s = os.str();

    // if (s.find("unique_ptr") != string::npos ||
    //    s.find("Uncompilable") != string::npos ||
    //    decl->getAccess() == clang::AccessSpecifier::AS_protected) {
    s = std::string("// ") + s;
    //}

    std::cout << s;
  }

  void addDecl(const Decl* decl) {
    decl = decl->getCanonicalDecl();
    if (seen.count(decl) > 0)
      return;
    printDecl(decl);
  }

public:
  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<NamedDecl>("decl");
    addDecl(decl);
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

// Define a hasher for clang::QualType.
template <>
struct hash<clang::QualType> {
  size_t operator()(clang::QualType qty) const {
    auto ty = qty.getTypePtr();
    auto quals = qty.getLocalQualifiers().getAsOpaqueValue();
    return hash<decltype(ty)>()(ty) | hash<decltype(quals)>()(quals);
  }
};

class AstToTemplates : public MatchFinder::MatchCallback {
  using ASTEntity = std::variant<const clang::Decl*,
                                 const clang::CXXBaseSpecifier*,
                                 const clang::QualType>;

  ASTContext& ast_;
  PrintingPolicy pp_;

  std::unordered_map<std::string, size_t> string_ids;
  std::unordered_map<ASTEntity, size_t> ast_ids;
  std::unordered_map<ASTEntity, std::set<std::string>> ast_traits;
  std::unordered_map<const clang::Decl*, std::set<const clang::Decl*>>
      decl_contexts_;
  const clang::TranslationUnitDecl* tu_decl_ = nullptr;

public:
  explicit AstToTemplates(ASTContext& ast)
      : ast_(ast), pp_(ast_.getLangOpts()) {
    // Ensure that printing types yields valid C++. This ensures:
    //   - tags ('class' etc) are not printed in type specifiers.
    //   - 'bool' is used rather than '_Bool'.
    pp_.adjustForCPlusPlus();
  }

private:
  std::string make_string_tag(size_t id_num) {
    std::ostringstream buf;
    buf << "_str" << id_num;
    return buf.str();
  }

  std::string make_ast_tag(size_t id_num) {
    std::ostringstream buf;
    buf << "_ast" << id_num;
    return buf.str();
  }

  std::string none() {
    return "None";
  }

  template <class Iterator,
            class Item = decltype(*(std::declval<const Iterator>().begin())),
            class TransformFn = std::function<std::string(const Item&)>>
  std::string pack_it(const Iterator& args,
                      TransformFn transform = [](const auto& s) -> std::string {
                        return s;
                      }) {
    std::ostringstream buf;
    size_t count = 0;
    buf << "Pack<";
    for (const Item& arg : args) {
      buf << (count++ ? ", " : "") << transform(arg);
    }
    buf << ">";
    return buf.str();
  }

  template <class A0>
  void _print_template_args(std::ostringstream& out, A0 arg) {
    out << arg;
  }

  template <class A0, class... Args>
  void _print_template_args(std::ostringstream& out, A0 arg0, Args... args) {
    out << arg0 << ", ";
    _print_template_args(out, args...);
  }

  template <class... Args>
  std::string pack(Args... args) {
    std::ostringstream buf;
    buf << "Pack<";
    _print_template_args(buf, args...);
    buf << ">";
    return buf.str();
  }

  template <class... Args>
  std::string make_trait(const char* name, Args... args) {
    std::ostringstream buf;
    buf << name << "<";
    _print_template_args(buf, args...);
    buf << ">";
    return buf.str();
  }

  std::string make_trait(const char* name) {
    return name;
  }

  template <class... Args>
  void add_trait(ASTEntity e, Args... args) {
    ast_traits[e].emplace(make_trait(args...));
  }

  void add_trait(ASTEntity e, std::string trait) {
    ast_traits[e].emplace(trait);
  }

  std::string add_string(std::string s) {
    auto& string_id = string_ids[s];
    if (string_id == 0) {
      string_id = string_ids.size();
      assert(string_id > 0);
    }
    return make_string_tag(string_id);
  }

  std::string add_qty(QualType qty) {
    // Assign id.
    auto& qty_id = ast_ids[qty];
    if (qty_id > 0)
      goto done;
    qty_id = ast_ids.size();
    assert(qty_id > 0);

    auto ty = qty.getTypePtr();
    auto quals = qty.getLocalQualifiers();

    assert((quals.empty() || quals.hasOnlyConst()) &&
           "Only 'const' qualified and unqualified are supported");

    // Mutable is the default; if const, add ConstQualifiedType wrapper.
    if (quals.hasConst()) {
      add_trait(qty, "ConstQualifiedType", add_type(ty));
      goto done;
    }
    assert(quals.empty());

    using TC = clang::Type::TypeClass;
    switch (ty->getTypeClass()) {
    case TC::Pointer: { // extends Type
      add_trait(qty,
                "PointerType",
                add_qty(dyn_cast<clang::PointerType>(ty)->getPointeeType()));
      break;
    }

    case TC::MemberPointer: { // extends Type
      auto mem_ptr_ty = dyn_cast<clang::MemberPointerType>(ty);
      add_trait(qty,
                "MemberPointerType",
                add_type(mem_ptr_ty->getClass()),
                add_qty(mem_ptr_ty->getPointeeType()));
      break;
    }

    case TC::LValueReference:   // extends ReferenceType
    case TC::RValueReference: { // extends ReferenceType
      auto ref_ty = dyn_cast<clang::ReferenceType>(ty);
      add_trait(qty,
                ref_ty->isSpelledAsLValue() ? "LValueReferenceType"
                                            : "RValueReferenceType",
                make_trait("ReferenceType",
                           add_qty(ref_ty->getPointeeTypeAsWritten())));
      break;
    }

    case TC::FunctionProto: {
      auto fn_proto_ty = dyn_cast<FunctionProtoType>(ty);
      auto method_quals = fn_proto_ty->getMethodQuals();
      auto ref_qual = fn_proto_ty->getRefQualifier();
      // TODO: add ref-qualifiers.
      assert(!fn_proto_ty->isVariadic() &&
             "Variadic functions are not supported");
      assert((method_quals.empty() || method_quals.hasOnlyConst()) &&
             "Only 'const' qualified and unqualified are supported");
      assert(ref_qual == RefQualifierKind::RQ_None &&
             "Ref-qualifiers are not supported");
      add_trait(qty,
                "FunctionProtoType",
                add_qty(fn_proto_ty->getReturnType()),
                pack_it(fn_proto_ty->getParamTypes(),
                        [&](QualType param_qty) -> auto {
                          return add_qty(param_qty);
                        }),
                method_quals.hasConst() ? "ConstQualifiedType"
                                        : "UnqualifiedType");
      break;
    }

    case TC::Builtin: { // extends Type
      auto builtin_ty = dyn_cast<BuiltinType>(ty);

      using K = BuiltinType::Kind;
      switch (builtin_ty->getKind()) {
      case K::Void:
        add_trait(qty, "VoidType");
        break;
      case K::Bool:
        add_trait(qty, "BoolType");
        break;
      case K::Long:
      case K::ULong:
      case K::WChar_S:
      case K::WChar_U:
        // Not supported: these types do not have a dependable size.
        assert(false && "Encountered built-in type with ABI-dependent size");
        break;
      default:
        // Numeric type with ABI-independent size (hopefully).
        auto ty_size = static_cast<size_t>(
            ast_.getTypeSizeInChars(builtin_ty).getQuantity());
        if (builtin_ty->isSignedInteger()) {
          add_trait(
              qty, "ABIIndependentSizeType", "SignedIntegerType", ty_size);
        } else if (builtin_ty->isUnsignedInteger()) {
          add_trait(
              qty, "ABIIndependentSizeType", "UnsignedIntegerType", ty_size);
        } else if (builtin_ty->isFloatingPoint()) {
          add_trait(
              qty, "ABIIndependentSizeType", "FloatingPointType", ty_size);
        } else {
          assert(false && "Unsupported built-in type");
        }
        break;
      }
      break;
    }

    case TC::Typedef: { // extends Type
      auto typedef_type = dyn_cast<TypedefType>(ty);
      auto typedef_name_decl = typedef_type->getDecl();

      do {
        auto can_ty = qty.getCanonicalType();
        if (!can_ty.getQualifiers().empty())
          break; // stdint type should not have qualifiers.
        if (can_ty->isInstantiationDependentType())
          break; // Should not be instantiation-dependent.

        auto builtin_ty = dyn_cast<BuiltinType>(can_ty);
        if (!builtin_ty)
          break; // Does not refer to a built-in type.
        if (!builtin_ty->isInteger())
          break; // Does not refer to an integral type.

        auto redecl_ctx =
            typedef_name_decl->getDeclContext()->getRedeclContext();
        auto ns_ctx = dyn_cast<NamespaceDecl>(redecl_ctx);
        if (ns_ctx && ns_ctx->getName() == "std")
          redecl_ctx = ns_ctx->getDeclContext()->getRedeclContext();
        if (!redecl_ctx->isTranslationUnit())
          break; // Not in top-level or 'std' namespace.

        do {
          if (ast_.getTypeSize(builtin_ty) !=
              ast_.getTypeSize(ast_.getUIntPtrType()))
            break; // Size does not match the size of intptr_t.
          if (ast_.getTypeAlign(builtin_ty) !=
              ast_.getTypeAlign(ast_.getUIntPtrType()))
            break; // Alignment does not match the size of intptr_t.

          auto name = typedef_name_decl->getName();
          if (!(name == "intptr_t" || name == "uintptr_t" ||
                name == "ssize_t" || name == "size_t" || name == "ptrdiff_t" ||
                name == "unsigned ptrdiff_t"))
            break; // Name does not match a known pointer-sized type.

          add_trait(qty,
                    "PointerSizeType",
                    builtin_ty->isSignedInteger() ? "SignedIntegerType"
                                                  : "UnsignedIntegerType");
          goto typedef_done;
        } while (0);

        do {
          auto name = typedef_name_decl->getName();
          if (!(name == "int8_t" || name == "uint8_t" || name == "int16_t" ||
                name == "uint16_t" || name == "int32_t" || name == "uint32_t" ||
                name == "int64_t" || name == "uint64_t"))
            break; // Name does not match a known fixed-sized type.

          add_trait(qty,
                    "ABIIndependentSizeType",
                    builtin_ty->isSignedInteger() ? "SignedIntegerType"
                                                  : "UnsignedIntegerType",
                    static_cast<size_t>(
                        ast_.getTypeSizeInChars(builtin_ty).getQuantity()));
          goto typedef_done;
        } while (0);
      } while (0);

      // Just a regular typedef.
      add_trait(qty, "TypedefType", add_decl(typedef_name_decl));

    typedef_done:
      break;
    }

    case TC::Paren: // extends Type
      // This is sugar for a FunctionType or an alias thereof. We
      // just step over it.
      add_trait(qty,
                "UnqualifiedType",
                add_qty(dyn_cast<ParenType>(ty)->getInnerType()));
      break;

    case TC::Enum: { // extends TagType
      auto enum_ty = dyn_cast<EnumType>(ty);
      auto enum_decl = enum_ty->getDecl();
      auto enum_int_qty = enum_decl->getIntegerType();
      add_trait(qty,
                "EnumType",
                add_decl(enum_decl),
                enum_int_qty.getTypePtrOrNull() ? add_qty(enum_int_qty)
                                                : "None");
      break;
    }

    case TC::Record: { // extends TagType
      auto record_ty = dyn_cast<RecordType>(ty);
      auto record_decl = record_ty->getDecl();

      std::string base = make_trait("RecordType", add_decl(record_decl));

      std::string record_subtype;
      if (ty->isUnionType())
        add_trait(qty, "UnionRecordType", base);
      else if (ty->isStructureOrClassType())
        add_trait(qty, "StructOrClassRecordType", base);
      else
        assert(false && "Unexpected record type");

      break;
    }

    // Unsupported types.
    case TC::Complex:                         // extends Type
    case TC::BlockPointer:                    // extends Type
    case TC::ConstantArray:                   // extends ArrayType
    case TC::IncompleteArray:                 // extends ArrayType
    case TC::VariableArray:                   // extends ArrayType
    case TC::DependentSizedArray:             // extends ArrayType
    case TC::DependentSizedExtVector:         // extends Type
    case TC::DependentAddressSpace:           // extends Type
    case TC::Vector:                          // extends Type
    case TC::DependentVector:                 // extends Type
    case TC::ExtVector:                       // extends VectorType
    case TC::FunctionNoProto:                 // extends FunctionType
    case TC::UnresolvedUsing:                 // extends Type
    case TC::MacroQualified:                  // extends Type
    case TC::Adjusted:                        // extends Type
    case TC::Decayed:                         // extends AdjustedType
    case TC::TypeOfExpr:                      // extends Type
    case TC::TypeOf:                          // extends Type
    case TC::Decltype:                        // extends Type
    case TC::UnaryTransform:                  // extends Type
    case TC::Elaborated:                      // extends Type
    case TC::Attributed:                      // extends Type
    case TC::TemplateTypeParm:                // extends Type
    case TC::SubstTemplateTypeParm:           // extends Type
    case TC::SubstTemplateTypeParmPack:       // extends Type
    case TC::TemplateSpecialization:          // extends Type
    case TC::Auto:                            // extends DeducedType
    case TC::DeducedTemplateSpecialization:   // extends DeducedType
    case TC::InjectedClassName:               // extends Type
    case TC::DependentName:                   // extends Type
    case TC::DependentTemplateSpecialization: // extends Type
    case TC::PackExpansion:                   // extends Type
    case TC::ObjCTypeParam:                   // extends Type
    case TC::ObjCObject:                      // extends Type
    case TC::ObjCInterface:                   // extends ObjCObjectType
    case TC::ObjCObjectPointer:               // extends Type
    case TC::Pipe:                            // extends Type
    case TC::Atomic:                          // extends Type
      break;

    default:
      assert(false && "Unknown type class");
    }

  done:
    return make_ast_tag(qty_id);
  }

  std::string add_type(const clang::Type* ty) {
    return add_qty(QualType(ty, 0));
  }

  std::string get_decl_base(const Decl* decl) {
    auto tu_decl = dyn_cast<TranslationUnitDecl>(decl);
    if (tu_decl) {
      assert(!tu_decl_ && "Root TranslationUnit should only be set once");
      tu_decl_ = tu_decl;
      return make_trait("Decl", none());
    }

    auto decl_context = decl->getDeclContext();
    auto decl_context_decl = dyn_cast<Decl>(decl_context)->getCanonicalDecl();
    auto parent_decl = add_decl(decl_context_decl);
    if (decl_contexts_[decl_context_decl].count(decl) > 0)
      abort();
    decl_contexts_[decl_context_decl].emplace(decl);
    return make_trait("Decl", parent_decl);
  }

  void merge_decl_contexts() {
    for (const auto& it : decl_contexts_) {
      add_trait(dyn_cast<Decl>(it.first),
                "DeclContext",
                pack_it(it.second, [&](const clang::Decl* child_decl) -> auto {
                  auto ast_id = ast_ids[child_decl];
                  assert(ast_id > 0);
                  return make_ast_tag(ast_id);
                }));
    }
  }

  std::string get_named_decl_base(const NamedDecl* named_decl) {
    // The trait `NamedDecl` is always added.
    auto name = named_decl->getNameAsString();
    if (name.empty()) {
      // Anonymous namespace or union. Generate a name, but use
      // NamedDeclAnon.
      static size_t anon_counter = 0;
      auto anon_name = std::ostringstream() << "anonymous_" << ++anon_counter;
      return make_trait(
          "NamedDeclAnon", get_decl_base(named_decl), add_string(name));
    } else {
      // NameDecl has a name.
      return make_trait(
          "NamedDeclName", get_decl_base(named_decl), add_string(name));
    }
  }

  std::string get_value_decl_base(const ValueDecl* value_decl) {
    return make_trait("ValueDecl",
                      get_named_decl_base(value_decl),
                      add_qty(value_decl->getType()));
  }

  std::string get_declarator_decl_base(const DeclaratorDecl* decl_decl) {
    return make_trait("DeclaratorDecl", get_value_decl_base(decl_decl));
  }

  std::string get_function_decl_base(const FunctionDecl* fn_decl) {
    auto fn_ty = fn_decl->getFunctionType();
    auto fn_proto_ty = fn_ty->getAs<FunctionProtoType>();
    assert(fn_proto_ty && "All functions must have a prototype.");

    return make_trait("FunctionDecl",
                      get_declarator_decl_base(fn_decl),
                      pack_it(fn_decl->parameters(),
                              [&](const ParmVarDecl* parm_var_decl) -> auto {
                                return add_decl(parm_var_decl);
                              }));
  }

  std::string get_cxx_method_decl_base(const CXXMethodDecl* method_decl) {
    auto base =
        make_trait("CXXMethodDecl", get_function_decl_base(method_decl));

    if (method_decl->isInstance()) {
      base = make_trait(
          "CXXInstanceMethodDecl", base, add_qty(method_decl->getThisType()));

      if (method_decl->isVirtual())
        base = make_trait("CXXVirtualMethodDecl", base);
    }
    return base;
  }

  std::string get_tag_decl_base(const clang::TagDecl* tag_decl) {
    return make_trait("TagDecl", get_type_decl_base(tag_decl));
  }

  std::string get_record_decl_base(const clang::RecordDecl* record_decl) {
    auto tag_decl_base = get_tag_decl_base(record_decl);
    std::string fields;
    if (record_decl->isCompleteDefinition()) {
      assert(!record_decl->hasFlexibleArrayMember() && "Not supported");
      assert(!record_decl->isLambda() && "Not supported");
      fields = pack_it(
          record_decl->fields(), [&](const FieldDecl* field_decl) -> auto {
            return add_decl(field_decl);
          });
    } else {
      fields = none();
    }
    return make_trait("RecordDecl", tag_decl_base, fields);
  }

  std::string
      get_cxx_record_decl_base(const clang::CXXRecordDecl* cxx_record_decl) {
    auto record_decl_base = get_record_decl_base(cxx_record_decl);
    std::string bases;
    if (cxx_record_decl->isCompleteDefinition()) {
      assert(cxx_record_decl->getNumVBases() == 0 && "Not supported");
      assert(!cxx_record_decl->isGenericLambda() && "Not supported");
      bases = pack_it(cxx_record_decl->bases(),
                      [&](const CXXBaseSpecifier& cxx_base_spec) -> auto {
                        return add_cxx_base_specifier(&cxx_base_spec);
                      });
    } else {
      bases = none();
    }
    return make_trait("CXXRecordDecl", record_decl_base, bases);
  }

  std::string get_var_decl_base(const clang::VarDecl* var_decl) {
    return make_trait("VarDecl", get_declarator_decl_base(var_decl));
  }

  std::string get_type_decl_base(const TypeDecl* type_decl) {
    return make_trait("TypeDecl",
                      get_named_decl_base(type_decl),
                      add_qty(ast_.getTypeDeclType(type_decl)));
  }

  std::string
      get_typedef_name_decl_base(const TypedefNameDecl* typedef_name_decl) {
    return make_trait("TypedefNameDecl", get_type_decl_base(typedef_name_decl));
  }

  std::string add_cxx_base_specifier(const CXXBaseSpecifier* spec) {
    // Assign id.
    auto& ast_id = ast_ids[spec];
    if (ast_id > 0)
      return make_ast_tag(ast_id);
    ast_id = ast_ids.size();
    assert(ast_id > 0);

    assert(!spec->isVirtual() && "Not supported");
    add_trait(spec, "CXXBaseSpecifier", add_qty(spec->getType()));

    return make_ast_tag(ast_id);
  }

  std::string add_decl(const Decl* decl) {
    // Only process canonical decls.
    decl = decl->getCanonicalDecl();

    // Assign id.
    auto& decl_id = ast_ids[decl];
    if (decl_id > 0)
      return make_ast_tag(decl_id);
    decl_id = ast_ids.size();
    assert(decl_id > 0);

    using K = clang::Decl::Kind;
    switch (decl->getKind()) {
      {
      case K::TranslationUnit: // extends Decl
        add_trait(decl, "TranslationUnitDecl", get_decl_base(decl));
        break;

      case K::Namespace: // extends NamedDecl
        add_trait(decl,
                  "NamespaceDecl",
                  get_named_decl_base(dyn_cast<NamedDecl>(decl)));
        break;

      case K::Function: // extends DeclaratorDecl
        add_trait(decl, get_function_decl_base(dyn_cast<FunctionDecl>(decl)));
        break;
      case K::CXXMethod: // extends FunctionDecl
        add_trait(decl,
                  get_cxx_method_decl_base(dyn_cast<CXXMethodDecl>(decl)));
        break;
      case K::CXXConstructor: // extends CXXMethodDecl
        add_trait(decl,
                  make_trait(
                      "CXXConstructorDecl",
                      get_cxx_method_decl_base(dyn_cast<CXXMethodDecl>(decl))));
        break;
      case K::CXXConversion: // extends CXXMethodDecl
        add_trait(decl,
                  make_trait(
                      "CXXConversionDecl",
                      get_cxx_method_decl_base(dyn_cast<CXXMethodDecl>(decl))));
        break;
      case K::CXXDestructor: // extends CXXMethodDecl
        add_trait(decl,
                  make_trait(
                      "CXXDestructorDecl",
                      get_cxx_method_decl_base(dyn_cast<CXXMethodDecl>(decl))));
        break;

      case K::Enum: // extends TagDecl
        break;
      case K::Record: // extends TagDecl
        add_trait(decl, get_record_decl_base(dyn_cast<RecordDecl>(decl)));
        break;
      case K::CXXRecord: // extends RecordDecl
        add_trait(decl,
                  get_cxx_record_decl_base(dyn_cast<CXXRecordDecl>(decl)));
        break;
      case K::Var: // extends DeclaratorDecl
        add_trait(decl, get_var_decl_base(dyn_cast<VarDecl>(decl)));
        break;
      case K::ParmVar: // extends VarDecl
        add_trait(
            decl, "ParmVarDecl", get_var_decl_base(dyn_cast<VarDecl>(decl)));
        break;
      case K::EnumConstant: // extends ValueDecl
        break;              // TODO;
      case K::Field:        // extends DeclaratorDecl
        // TODO: bitfields etc.
        add_trait(decl,
                  "FieldDecl",
                  get_declarator_decl_base(dyn_cast<FieldDecl>(decl)));
        break;

      case K::TypeAlias: // extends TypedefNameDecl
        add_trait(decl,
                  "TypeAliasDecl",
                  get_typedef_name_decl_base(dyn_cast<TypedefNameDecl>(decl)));
        break;
      case K::Typedef: // extends TypedefNameDecl
        add_trait(decl,
                  "TypedefDecl",
                  get_typedef_name_decl_base(dyn_cast<TypedefNameDecl>(decl)));
        break;

      // Ignored nodes
      case K::AccessSpec:           // extends Decl
      case K::Captured:             // extends Decl
      case K::Binding:              // extends ValueDecl
      case K::Empty:                // extends Decl
      case K::FileScopeAsm:         // extends Decl
      case K::Friend:               // extends Decl
      case K::FriendTemplate:       // extends Decl
      case K::Label:                // extends NamedDecl
      case K::LinkageSpec:          // extends Decl
      case K::StaticAssert:         // extends Decl
      case K::UnresolvedUsingValue: // extends ValueDecl
        break;

      // Unsupported nodes
      case K::ClassScopeFunctionSpecialization: // extends Decl
      case K::ExternCContext:                   // extends Decl
      case K::NamespaceAlias:                   // extends NamedDecl
      case K::BuiltinTemplate:                  // extends TemplateDecl
      case K::ClassTemplate:               // extends RedeclarableTemplateDecl
      case K::FunctionTemplate:            // extends RedeclarableTemplateDecl
      case K::TypeAliasTemplate:           // extends RedeclarableTemplateDecl
      case K::VarTemplate:                 // extends RedeclarableTemplateDecl
      case K::TemplateTemplateParm:        // extends TemplateDecl
      case K::ClassTemplateSpecialization: // extends CXXRecordDecl
      case K::
          ClassTemplatePartialSpecialization: // extends
                                              // ClassTemplateSpecializationDecl
      case K::TemplateTypeParm:               // extends TypeDecl
      case K::Using:                          // extends NamedDecl
      case K::UsingDirective:                 // extends NamedDecl
      case K::UsingPack:                      // extends NamedDecl
      case K::UsingShadow:                    // extends NamedDecl
      case K::ConstructorUsingShadow:         // extends UsingShadowDecl
      case K::CXXDeductionGuide:              // extends FunctionDecl
      case K::NonTypeTemplateParm:            // extends DeclaratorDecl
      case K::Decomposition:                  // extends VarDecl
      case K::ImplicitParam:                  // extends VarDecl
      case K::VarTemplateSpecialization:      // extends VarDecl
      case K::VarTemplatePartialSpecialization: // extends
                                                // VarTemplateSpecializationDecl
      case K::IndirectField:                    // extends ValueDecl
      default:
        break;
      }
    }

    /*
    // Add name if named.
    std::string named_decl_base;
    do {
      auto named_decl = dyn_cast<NamedDecl>(decl);
      if (!named_decl)
        break;

      // Do not attempt for constructors and destructors.
      // if (isa<CXXConstructorDecl>(decl) || isa<CXXDestructorDecl>(decl) ||
      //    isa<CXXConversionDecl>(decl))
      //  break;

    } while (0);

    // Add function(-like) traits.
    auto fn_decl = dyn_cast<FunctionDecl>(decl);
    if (fn_decl) {
      std::string fn_trait;

      auto fn_ty = fn_decl->getFunctionType();
      auto fn_proto_ty = fn_ty->getAs<FunctionProtoType>();
      assert(fn_proto_ty && "All functions must have a prototype.");

      // Add function parameters.
      std::vector<std::string> params;
      for (auto& parm_var_decl : fn_decl->parameters()) {
        params.push_back(add_decl(parm_var_decl));
      }
      fn_trait = make_trait(
          "FunctionDecl",
          make_trait("TypeDecl", named_decl_base, add_type(fn_proto_ty)),
          pack_it(params));

      // Add Method information.
      auto method_decl = dyn_cast<CXXMethodDecl>(fn_decl);
      if (method_decl) {
        fn_trait = make_trait("MethodDecl", fn_trait);

        if (method_decl->isInstance()) {
          fn_trait = make_trait("InstanceMethodDecl",
                                fn_trait,
                                add_qty(method_decl->getThisType()));

          if (method_decl->isVirtual())
            fn_trait = make_trait("VirtualMethodDecl", fn_trait);

          if (isa<CXXConstructorDecl>(fn_decl))
            fn_trait = make_trait("ConstructorDecl", fn_trait);
          else if (isa<CXXDestructorDecl>(fn_decl))
            fn_trait = make_trait("DestructorDecl", fn_trait);
          else if (isa<CXXConversionDecl>(fn_decl))
            fn_trait = make_trait("ConversionDecl", fn_trait);
        }
      }

      add_trait(decl, fn_trait);
    }

    auto typedef_name_decl = dyn_cast<TypedefNameDecl>(decl);
    if (typedef_name_decl) {
      add_trait(decl,
                "TypedefNameDecl",
                make_trait("TypeDecl",
                           named_decl_base,
                           add_qty(typedef_name_decl->getUnderlyingType())));
    }

    // auto value_decl = dyn_cast<ValueDecl>(decl);
    // if (value_decl) {
    //  auto qty = value_decl->getType();
    //
    //  auto parm_var_decl = dyn_cast<ParmVarDecl>(decl);
    //  if (parm_var_decl) {
    //    add_trait(decl, "ParmVarDecl", add_qty(qty));
    //  }
    //}*/

    return make_ast_tag(decl_id);
  }

  template <class K, class V>
  auto sort_by_id(const std::unordered_map<K, V>& map) {
    std::map<V, K> ordered_map;
    for (auto& it : map) {
      ordered_map.emplace(std::make_pair(it.second, it.first));
    }
    return ordered_map;
  }

  void print_prologue(llvm::raw_ostream& out) {
    out << "#include \"src/prologue.h\"\n"
        << "\n";
  }

  void print_const_strings(llvm::raw_ostream& out) {
    for (auto& it : sort_by_id(string_ids)) {
      out << "struct " << make_string_tag(it.first)
          << " { constexpr static const char* value = \"" << it.second
          << "\"; };\n";
    }
    out << "\n";
  }

  void print_comment(llvm::raw_ostream& out, const clang::QualType qty) {
    out << qty->getTypeClassName() << "Type ";
    qty.print(out, pp_);
  }

  void print_comment(llvm::raw_ostream& out, const clang::Decl* decl) {
    out << decl->getDeclKindName() << "Decl";
    auto named_decl = dyn_cast<NamedDecl>(decl);
    if (named_decl)
      out << " " << named_decl->getNameAsString();
  }

  void print_comment(llvm::raw_ostream& out,
                     const clang::CXXBaseSpecifier* spec) {
    auto qty = spec->getType();
    out << "CXXBaseSpecifier " << qty->getTypeClassName() << " ";
    qty.print(out, pp_);
  }

  void print_comment(llvm::raw_ostream& out, const ASTEntity& e) {
    std::visit([&](const auto& v) { print_comment(out, v); }, e);
  }

  void print_forward_decls(llvm::raw_ostream& out) {
    for (auto& it : sort_by_id(ast_ids)) {
      out << "struct " << make_ast_tag(it.first) << "; // ";
      print_comment(out, it.second);
      out << "\n";
    }
    out << "\n";
  }

  void print_ast_traits(llvm::raw_ostream& out) {
    for (auto& it : sort_by_id(ast_ids)) {
      auto trait_set = ast_traits[it.second];
      if (trait_set.empty())
        continue;

      out << "struct " << make_ast_tag(it.first);
      size_t count = 0;
      for (auto& trait_str : trait_set) {
        out << (count++ ? ", " : ": ") << trait_str;
      }
      out << " {}; // ";
      print_comment(out, it.second);
      out << "\n";
    }
    out << "\n";
  }

  void print_run_call(llvm::raw_ostream& out) {
    out << "#include \"emit.h\"\n";
    out << "int main() {\n";
    out << "  run<" << make_ast_tag(ast_ids[tu_decl_]) << ">();\n";
    out << "}\n";
  }

public:
  void write(llvm::raw_ostream& out) {
    merge_decl_contexts();
    print_prologue(out);
    print_const_strings(out);
    print_forward_decls(out);
    print_ast_traits(out);
    print_run_call(out);
  }

  void run(const MatchFinder::MatchResult& result) override {
    auto decl = result.Nodes.getNodeAs<Decl>("decl");
    add_decl(decl);
  }
};

namespace name {
class Context;
class Name;
class GlobalContext;
class GlobalName;

class Context {
private:
  std::unordered_set<const Name&> children;
  size_t detail = 0;

public:
  void Add(const Name& child) {
    children.emplace(child);

  // Scan for collisions and increase detail level if necessary.
  restart:
    for (;;) {
      std::unordered_set<std::string> names;
      for (const auto& c : children) {
        auto name = GetNameOf(c);
        if (names.count(name) > 0) {
          // Collision found: increase detail level and restart scan.
          detail++;
          goto restart;
        }
        names.emplace(name);
      }

      // No collisions found.
      break;
    }
  }

private:
  friend Name;
  std::string GetNameOf(const Name& child) const {
    return child.GetNameAlternative(detail);
  }
};

class Name {
  Context* ctx_;

public:
  explicit Name(Context* ctx) : ctx_(ctx) {
    ctx->Add(*this);
  }

  std::string name() const {
    return ctx_->GetNameOf(*this);
  }

private:
  friend Context;
  virtual std::string GetNameAlternative(size_t detail) const = 0;
};

class GlobalContext : public Context {
private:
  friend class GlobalName;
  friend class GlobalNamedContext;

  virtual std::string separator() const = 0;
  virtual std::string prefix() const {
    return "";
  }
};

class GlobalName : public Name {
  GlobalContext* ctx_;

public:
  GlobalName(GlobalContext* ctx) : Name(ctx), ctx_(ctx) {}

  std::string qualifiedName() const {
    return ctx_->prefix() + name();
  }

protected:
  GlobalContext* context() const {
    return ctx_;
  }
};

class GlobalNamedContext : public GlobalName, public GlobalContext {
public:
  std::string separator() const override {
    return context()->separator();
  }

  std::string prefix() const override {
    return qualifiedName() + separator();
  }
};

} // namespace name

class ASTConsumerImpl : public ASTConsumer {

  void HandleTranslationUnit(ASTContext& ast) override {
    // Run the matchers when we have the whole TU parsed.
    InvokableDeclAction invokable_action(ast);
    RecordAction record_action;
    MatchFinder finder;
    AstToTemplates ast_to_templates(ast);
    // finder.addMatcher(
    //    namedDecl(hasAncestor(namespaceDecl(hasName("::v8")))).bind("decl"),
    //    &named_decl_action);

    finder.addMatcher(decl(Matchers::anyV8Api()).bind("decl"),
                      &ast_to_templates);
    finder.matchAST(ast);
    ast_to_templates.write(llvm::outs());
    // finder.addMatcher(
    //     decl(varDecl(hasAncestor(namespaceDecl(hasName("::v8_wrap")))))
    //         .bind("decl"),
    //     &var_type_action);
    // finder.addMatcher(recordDecl(v8api).bind("record",
    // &record_action);
    // finder.addMatcher(functionDecl(v8api).bind("fn"),
    // &function_action);
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
  auto result = tool.run(newFrontendActionFactory<FrontendActionImpl>().get());
  llvm::outs() << "// Done: " << result << "\n";
  return result;
}
