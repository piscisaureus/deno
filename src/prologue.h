#include <cstddef>

struct None {};
template <class... Ts>
struct Pack {};

// === Types

struct Type {
  static constexpr const bool IsConst = false;
};
template <class T>
struct UnqualifiedType : Type {
  using InnerType = T;
};
template <class T>
struct ConstQualifiedType : Type {
  static constexpr const bool IsConst = true;
  using InnerType = T;
};
struct VoidType : Type {};
struct BoolType : Type {};
struct NumericType : Type {};
struct IntegerType : NumericType {};
struct UnsignedIntegerType : IntegerType {};
struct SignedIntegerType : IntegerType {};
struct FloatingPointType : NumericType {};
template <class T, size_t s>
struct ABIIndependentSizeType : T {
  static constexpr const size_t size = s;
};
template <class T>
struct PointerSizeType : T {};
template <class T>
struct PointerType : Type {
  using PointeeType = T;
};
template <class CT, class MT>
struct MemberPointerType : Type {
  using ClassType = CT;
  using MemberType = MT;
};
template <class T>
struct ReferenceType : Type {
  using PointeeType = T;
};
template <class RT>
struct LValueReferenceType : RT {};
template <class RT>
struct RValueReferenceType : RT {};
template <class RT, class PTs, template <class> class MQ>
struct FunctionProtoType : Type {
  using ReturnType = RT;
  using ParamTypes = PTs;
  template <typename T>
  using AddMethodQualifiers = MQ<T>;
};
template <typename D>
struct TagType : Type {
  using Decl = D;
};
template <typename D, typename IT>
struct EnumType : TagType<D> {
  using IntegerType = IT;
};
template <typename D>
struct RecordType : TagType<D> {};
template <typename RT>
struct UnionRecordType : RT {};
template <typename RT>
struct StructOrClassRecordType : RT {};
template <class D>
struct TypedefType : Type {
  using Decl = D;
};

// === Decl misc.

template <class Ds>
struct DeclContext {
  using Decls = Ds;
};

template <class T>
struct CXXBaseSpecifier {
  using Type = T;
};

// === Decls
template <class Ctx>
struct Decl {
  using DeclContext = Ctx;
};

template <class Base>
struct TranslationUnitDecl: Base {};
template <class Base>
struct NamespaceDecl: Base {};

template <class Base, class S>
struct NamedDecl: Base {
  constexpr static const char* DeclName = S::value;
};
template <class Base, class S>
struct NamedDeclName : NamedDecl<Base, S> {};
template <class Base, class S>
struct NamedDeclAnon : NamedDecl<Base, S> {};

template <class Base, class T>
struct ValueDecl: Base { using Type = T; };

template <class Base>
struct DeclaratorDecl: Base {};

template <class Base>
struct VarDecl: Base {};
template <class Base>
struct ParmVarDecl: Base {};
template <class Base>
struct FieldDecl: Base {};

template <class TD, class Ps>
struct FunctionDecl : TD {
  using Params = Ps;
};
template <class FD>
struct CXXMethodDecl : FD {};
template <class MD, class TT>
struct CXXInstanceMethodDecl : MD {
  using ThisType = TT;
};
template <class MD>
struct CXXVirtualMethodDecl : MD {};
template <class MD>
struct CXXConstructorDecl : MD {};
template <class MD>
struct CXXDestructorDecl : MD {};
template <class MD>
struct CXXConversionDecl : MD {};

template <class Base, class T>
struct TypeDecl: Base { using Type = T; };

template <class Base>
struct TagDecl: Base {};
template <class Base, class Fs>
struct RecordDecl: Base { using Fields = Fs; };
template <class Base, class Bs>
struct CXXRecordDecl: Base { using Bases = Bs; };


template <class Base>
struct TypedefNameDecl : Base {};
template <class Base>
struct TypedefDecl : Base {};
template <class Base>
struct TypeAliasDecl : Base {};
