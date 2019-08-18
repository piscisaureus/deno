
#include <iostream>
#include <ostream>
#include <type_traits>

// ====== Distinguishing between complete and incomplete classes ======

template <typename T>
class is_complete {
private:
  template <typename U>
  static auto test(U*) -> std::integral_constant<bool, sizeof(U) == sizeof(U)>;
  static auto test(...) -> std::false_type;

public:
  using type = decltype(test((std::add_pointer_t<T>) 0));
  static constexpr bool value = type();
};

template <typename T>
static constexpr bool is_complete_v = is_complete<T>::value;

template <typename T, typename U>
using complete_or_else_t = std::conditional_t<is_complete_v<T>, T, U>;

// ======

struct IncompleteType : Type {};

template <class T>
void emit3(std::ostream& out) {
  using U = complete_or_else_t<T, IncompleteType>;
  emit2(out, U(), U());
}

template <class D, class A>
void emit2(std::ostream& out, D, ParmVarDecl<A>) {}

template <class D, class N, class T>
void emit2(std::ostream& out, D, TypeDecl<N, T>) {}

template <class T>
void emit2(std::ostream& out, T, Type) {
  out << "[?" << typeid(T).name() << "]";
}

template <class T>
void emit2(std::ostream& out, T, IncompleteType) {
  out << "[?X]";
}

template <class T, class U>
void emit2(std::ostream& out, T, ConstQualifiedType<U>) {
  out << "const ";
  emit3<U>(out);
}

template <class T, class U>
void emit2(std::ostream& out, T, UnqualifiedType<U>) {
  emit3<U>(out);
}

template <class T>
void emit2(std::ostream& out, T, VoidType) {
  out << "void";
}

template <class T, size_t s>
void emit2(std::ostream& out, T, ABIIndependentSizeType<SignedIntegerType, s>) {
  out << "int" << s << "_t";
}

template <class T, size_t s>
void emit2(std::ostream& out,
           T,
           ABIIndependentSizeType<UnsignedIntegerType, s>) {
  out << "uint" << s << "_t";
}

template <class T>
void emit2(std::ostream& out, T, PointerSizeType<SignedIntegerType>) {
  out << "intptr_t";
}

template <class T>
void emit2(std::ostream& out, T, PointerSizeType<UnsignedIntegerType>) {
  out << "uintptr_t";
}

template <class T, size_t s>
void emit2(std::ostream& out, T, ABIIndependentSizeType<FloatingPointType, s>) {
  out << "float" << s << "_t";
}

template <class T, class PT>
void emit2(std::ostream& out, T, PointerType<PT>) {
  emit3<PT>(out);
  out << "*";
}

template <class T, class CT, class RT, class As, template <class> class MQ>
void emit2(std::ostream& out,
           T,
           MemberPointerType<CT, FunctionProtoType<RT, As, MQ>>) {
  emit3<RT>(out);
  out << " (";
  emit3(MQ<CT>);
  out << "::*)(...)";
}

template <class T, class PT>
void emit2(std::ostream& out, T, LValueReferenceType<ReferenceType<PT>>) {
  emit3<PT>(out);
  out << "&";
}

template <class T, class PT>
void emit2(std::ostream& out, T, RValueReferenceType<ReferenceType<PT>>) {
  emit3<PT>(out);
  out << "&&";
}

struct IncompleteNamedDecl {
  static constexpr const char* DeclName = "[?D]";
};

template <class T, class D>
void emit2(std::ostream& out, T, TagType<D>) {
  using D2 = complete_or_else_t<D, IncompleteNamedDecl>;
  out << "tag " << D2::DeclName;
}

template <class T, class TD, class TU>
void emit2(std::ostream& out, T, TypedefNameDecl<TypeDecl<TD, TU>>) {
  using TD2 = complete_or_else_t<TD, IncompleteNamedDecl>;
  out << "typedef " << TD2::DeclName << " (a.k.a ";
  emit3<TU>(out);
  out << ")";
}

/*
  struct Type {                                                                \
    static constexpr const bool IsConst = false;                               \
  };                                                                           \
  template <class T>                                                           \
  using SameType = T;                                                          \
                                                                               \
  template <class T>                                                           \
  struct ConstQualifiedType : Type {                                           \
    static constexpr const bool IsConst = true;                                \
    using InnerType = T;                                                       \
  };                                                                           \
                                                                               \
  struct VoidType : Type {};                                                   \
  struct BoolType : Type {};                                                   \
  struct NumericType : Type {};                                                \
                                                                               \
  struct IntegerType : NumericType {};                                         \
  struct UnsignedIntegerType : IntegerType {};                                 \
  struct SignedIntegerType : IntegerType {};                                   \
                                                                               \
  struct FloatingPointType : NumericType {};                                   \
                                                                               \
  template <class T, size_t s>                                                 \
  struct ABIIndependentSizeType : T {                                          \
    static constexpr const size_t size = s;                                    \
  };                                                                           \
  template <class T>                                                           \
  struct PointerSizeType : T {};                                               \
                                                                               \
  template <class T>                                                           \
  struct PointerType : Type {                                                  \
    using PointeeType = T;                                                     \
  };                                                                           \
                                                                               \
  template <class CT, class MT>                                                \
  struct MemberPointerType : Type {                                            \
    using ClassType = CT;                                                      \
    using MemberType = MT;                                                     \
  };                                                                           \
                                                                               \
  template <class T>                                                           \
  struct ReferenceType : Type {                                                \
    using PointeeType = T;                                                     \
  };                                                                           \
  template <class RT>                                                          \
  struct LValueReferenceType : RT {};                                          \
  template <class RT>                                                          \
  struct RValueReferenceType : RT {};                                          \
                                                                               \
  template <class RT, class PTs, template <class> class MQ>                    \
  struct FunctionProtoType : Type {                                            \
    using ReturnType = RT;                                                     \
    using ParamTypes = PTs;                                                    \
                                                                               \
    template <typename T>                                                      \
    using AddMethodQualifiers = MQ<T>;                                         \
  };                                                                           \
                                                                               \
  template <typename D>                                                        \
  struct TagType : Type {                                                      \
    using Decl = D;                                                            \
  };                                                                           \
                                                                               \
  template <typename D, typename IT>                                           \
  struct EnumType : TagType<D> {                                               \
    using IntegerType = IT;                                                    \
  };                                                                           \
                                                                               \
  template <typename D>                                                        \
  struct RecordType : TagType<D> {};                                           \
  template <typename RT>                                                       \
  struct UnionRecordType : RT {};                                              \
  template <typename RT>                                                       \
  struct StructOrClassRecordType : RT {};                                      \
                                                                               \
  template <class D>                                                           \
  struct TypedefType : Type {                                                  \
    using Decl = D;                                                            \
  };                                                                           \
*/

//--
template <class T>
T& fake() {
  static char dummy[256];
  return *reinterpret_cast<T*>(dummy);
}

template <class T>
static void emit() {
  std::cout << typeid(T).name() << " = ";
  emit3<T>(std::cout);
  std::cout << "\n";
}
