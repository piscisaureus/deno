
#include "v8/include/v8config.h"
#undef V8_EXPORT
#define V8_EXPORT
#include "v8/include/v8.h"

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace type_wrapper {

// ====== Type name deduction utilities ======

// GCC, or Clang emulating it.
#if defined(__GNUG__)
#include <cxxabi.h>
#include <stdlib.h>
template <class T>
std::string cxx_typename() {
  std::string mangled = typeid(T).name();
  int status;
  char* str = abi::__cxa_demangle(mangled.c_str(), 0, 0, &status);
  if (status != 0) {
    std::cerr << "Demangling '" << mangled << "' failed (status " << status
              << ")" << std::endl;
    abort();
  }
  std::string demangled(str);
  free(str);
  return demangled;
}

// MSVC, or Clang emulating it.
#elif defined(_MSC_VER)
template <class T>
std::string cxx_typename() {
  return typeid(T).name();
}
#endif

// ====== Function and method argument deduction utilities ======

// Functions and static methods
template <class F, template <bool, class, class...> class Functor>
class transform_function {
  template <class R, class... A>
  static constexpr auto deduce(R (*)(A...))
      -> Functor<std::is_void_v<R>, R, A...>;

public:
  using type = decltype(deduce(std::declval<F>()));
};

template <class F, template <bool, class, class...> class Functor>
using transform_function_t = typename transform_function<F, Functor>::type;

// Instance methods
template <class M, template <bool, class, class, class...> class Functor>
class transform_method {
  template <class R, class T, class... A>
  static constexpr auto deduce(R (T::*)(A...))
      -> Functor<std::is_void_v<R>, R, T, A...>;

  template <class R, class T, class... A>
  static constexpr auto deduce(R (T::*)(A...) const)
      -> Functor<std::is_void_v<R>, R, const T, A...>;

public:
  using type = decltype(deduce(std::declval<M>()));
};

template <class M, template <bool, class, class, class...> class Functor>
using transform_method_t = typename transform_method<M, Functor>::type;

// ====== Array element type deduction ======
template <class>
struct array_element {};

template <class E, size_t N>
struct array_element<E[N]> {
  using type = E;
  static constexpr auto count = N;
};

// ====== Type picker for opaque type fillers ======

template <size_t align, class E, class = void>
struct filler_traits;

template <size_t align, class E>
struct filler_traits<
    align,
    E,
    std::enable_if_t<alignof(E) == align && sizeof(E) == align>> {
  using type = E;
};

template <size_t align>
struct filler;
template <>
struct filler<1> : public filler_traits<1, uint8_t> {};
template <>
struct filler<2> : public filler_traits<2, uint16_t> {};
template <>
struct filler<4> : public filler_traits<4, uint32_t> {};
template <>
struct filler<8> : public filler_traits<8, uint64_t> {};

template <size_t align>
using filler_t = typename filler<align>::type;

// ====== Type mapping ======

template <class T, class = void>
class wrap_type;

template <class T, class W = wrap_type<std::remove_cv_t<T>>, class = void>
struct wrap_qual_type;

// ====== Rust type representations ======

// Unqualified types.
class rust_repr_base {
protected:
  static size_t next_type_index() {
    static size_t type_index_counter = 0;
    return ++type_index_counter;
  }

public:
  virtual std::string rust_type() {
    return "???";
  };
  virtual std::string rust_name() {
    return "???";
  };
  virtual std::string rust_decl() {
    return "???";
  };
};

class rust_primitive_type : public rust_repr_base {
public:
  std::string rust_name() override {
    return rust_type();
  }
  std::string rust_decl() override {
    return "";
  }
};

template <char letter, int byte_size>
class rust_numeric_type : public rust_primitive_type {
public:
  std::string rust_type() override {
    std::ostringstream os;
    os << letter << (byte_size << 3);
    return os.str();
  }
};

template <class W>
class rust_pointer_type : public rust_primitive_type {
  typename W::rust_repr target_repr;

public:
  std::string rust_type() override {
    std::ostringstream os;
    os << "*" << target_repr.rust_name();
    return os.str();
  }
};

template <typename E, size_t N>
class rust_slice : public rust_primitive_type {
  typename wrap_type<E>::rust_repr el_repr;

public:
  std::string rust_type() override {
    std::ostringstream os;
    os << "[" << el_repr.rust_name() << "; " << N << "]";
    return os.str();
  }
};

template <class T>
class rust_named_type : public rust_repr_base {
  static size_t index() {
    static const auto idx = next_type_index();
    return idx;
  }

public:
  std::string rust_name() override {
    std::ostringstream os;
    os << "@" << index() << "@"
       << " " << rust_type();
    return os.str();
  }
};

// Qualified types.
template <class W>
class rust_qual_type : public rust_primitive_type {
  typename W::rust_repr target_repr;
  std::string quals;

protected:
  virtual std::string rust_qual() = 0;

public:
  std::string rust_type() override {
    std::ostringstream os;
    os << rust_qual() << " " << target_repr.rust_name();
    return os.str();
  }
};

// ====== Type mappings ======

// Unqualified types.

class wrap_type_base {};

template <class T, class>
class wrap_type : public wrap_type_base {
  struct UNKNOWN {
    T _;
  };

public:
  using opaque_type = UNKNOWN;
  class rust_repr : public rust_primitive_type {
  public:
    std::string rust_type() override {
      std::ostringstream os;
      os << "<<<UNKNOWN " << cxx_typename<T>() << ">>>";
      return os.str();
    }
  };
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_same_v<T, void>>>
    : public wrap_type_base {
public:
  using opaque_type = void;

  class rust_repr : public rust_primitive_type {
  public:
    std::string rust_type() override {
      return "()";
    }
  };
};

// The rust equivalent of `void` is `()`, but creating a reference/pointer
// to `()` isn't possible; we need to use `std::ffi::c_void` instead.
class wrap_void_non_unit : public wrap_type<void> {
public:
  class rust_repr : public rust_primitive_type {
  public:
    std::string rust_type() override {
      return "std::ffi::c_void";
    }
  };
};

template <class T>
class wrap_type<T,
                std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>>
    : public wrap_type_base {
public:
  using opaque_type = T;
  using rust_repr = rust_numeric_type<'i', sizeof(T)>;
};

template <class T>
class wrap_type<
    T,
    std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>>>
    : public wrap_type_base {
public:
  using opaque_type = T;
  using rust_repr = rust_numeric_type<'u', sizeof(T)>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_array_v<T>>>
    : public wrap_type_base {
  using el = array_element<T>;
  using el_opaque_t = typename wrap_type<typename el::type>::opaque_type;

public:
  using opaque_type = el_opaque_t[el::count];
  static_assert(sizeof(T) == sizeof(opaque_type), "size mismatch");
  static_assert(alignof(T) == alignof(opaque_type), "alignment mismatch");

  using rust_repr = rust_slice<typename el::type, el::count>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_class_v<T> || std::is_union_v<T>>>
    : public wrap_type_base {
private:
  using el_t = filler_t<alignof(T)>;
  static constexpr size_t el_count = sizeof(T) / sizeof(el_t);

public:
  struct opaque_type {
    el_t _filler[el_count];
  };
  static_assert(sizeof(T) == sizeof(opaque_type), "size mismatch");
  static_assert(alignof(T) == alignof(opaque_type), "alignment mismatch");

  class rust_repr : public rust_named_type<T> {
    rust_slice<el_t, el_count> filler_repr;

  public:
    std::string rust_type() override {
      std::ostringstream os;
      os << "struct(" << filler_repr.rust_type() << ")";
      return os.str();
    }
  };
};

template <class F>
struct wrap_type<F, std::enable_if_t<std::is_function_v<F>>>
    : public wrap_type_base {
  template <bool is_void, class R, class... A>
  using make_opaque_type = typename wrap_type<R>::opaque_type (&)(
      typename wrap_type<A>::opaque_type... args);

  template <bool is_void, class R, class... A>
  class make_rust_repr : public rust_named_type<F> {
    template <class T>
    static auto rust_type_name() {
      typename wrap_type<T>::rust_repr rust_repr;
      return rust_repr.rust_name();
    }

  public:
    std::string rust_type() override {
      std::string ret_type = rust_type_name<R>();
      // The last element of arg_type[] is always an empty string.
      // This avoids instantiating to an empty array (which is illegal) when the
      // function takes no arguments.
      std::string arg_type[] = {rust_type_name<A>()..., std::string()};
      size_t arg_count = sizeof(arg_type) / sizeof(arg_type[0]) - 1;

      std::ostringstream os;
      os << "extern \"C\" fn(";
      for (size_t i = 0; i < arg_count; i++) {
        if (i > 0)
          os << ", ";
        os << arg_type[i];
      }
      os << ") -> ";
      if (is_void) {
        os << "()";
      } else {
        os << ret_type;
      }
      return os.str();
    }
  };

public:
  using opaque_type = transform_function_t<F, make_opaque_type>;
  using rust_repr = transform_function_t<F, make_rust_repr>;
};

template <class M>
struct wrap_type<M, std::enable_if_t<std::is_member_function_pointer_v<M>>>
    : public wrap_type_base {
  template <bool is_void, class R, class T, class... A>
  using make_opaque_type = typename wrap_type<R>::opaque_type (T::*)(
      typename wrap_type<A>::opaque_type... args);

  template <bool is_void, class R, class T, class... A>
  class make_rust_repr : public rust_named_type<M> {
    template <class X>
    static auto rust_type_name() {
      typename wrap_type<X>::rust_repr rust_repr;
      return rust_repr.rust_name();
    }

  public:
    std::string rust_type() override {
      std::string ret_type = rust_type_name<R>();
      std::string arg_type[] = {rust_type_name<T>(), rust_type_name<A>()...};
      size_t arg_count = sizeof(arg_type) / sizeof(arg_type[0]);

      std::ostringstream os;
      os << "extern \"C\" fn(";
      for (size_t i = 0; i < arg_count; i++) {
        if (i > 0)
          os << ", ";
        os << arg_type[i];
      }
      os << ") -> ";
      if (is_void) {
        os << "()";
      } else {
        os << ret_type;
      }
      return os.str();
    }
  };

public:
  using opaque_type = transform_method_t<M, make_opaque_type>;
  using rust_repr = transform_method_t<M, make_rust_repr>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_pointer_v<T>>>
    : public wrap_type_base {
  using target = std::remove_pointer_t<T>;
  using wrapped_target =
      std::conditional_t<!std::is_void_v<target>,
                         wrap_qual_type<target>,
                         wrap_qual_type<target, wrap_void_non_unit>>;

public:
  using opaque_type = std::add_pointer_t<typename wrapped_target::opaque_type>;
  using rust_repr = rust_pointer_type<wrapped_target>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_lvalue_reference_v<T>>>
    : public wrap_type_base {
private:
  using target = std::remove_reference_t<T>;
  using wrapped_target = wrap_qual_type<target>;

public:
  using opaque_type =
      std::add_lvalue_reference_t<typename wrapped_target::opaque_type>;
  using rust_repr = rust_pointer_type<wrapped_target>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_rvalue_reference_v<T>>>
    : public wrap_type_base {
private:
  using target = std::remove_reference_t<T>;
  using wrapped_target = wrap_qual_type<target>;

public:
  using opaque_type =
      std::add_rvalue_reference_t<typename wrapped_target::opaque_type>;
  using rust_repr = rust_pointer_type<wrapped_target>;
};

// Qualified types

class wrap_qual_type_base : public wrap_type_base {};

template <class T, class W>
class wrap_qual_type<
    T,
    W,
    std::enable_if_t<std::is_const_v<T> && !std::is_volatile_v<T>>>
    : public wrap_qual_type_base {
public:
  using opaque_type = const typename W::opaque_type;

  class rust_repr : public rust_qual_type<W> {
    std::string rust_qual() override {
      return "const";
    }
  };
};

template <class T, class W>
class wrap_qual_type<
    T,
    W,
    std::enable_if_t<!std::is_const_v<T> && !std::is_volatile_v<T>>>
    : public wrap_qual_type_base {
public:
  using opaque_type = typename W::opaque_type;

  class rust_repr : public rust_qual_type<W> {
    std::string rust_qual() override {
      return "mut";
    }
  };
};

// ====== Function and method wrappers ======

// Functions and static methods.
template <auto fn>
class wrap_function {
  template <class T>
  static auto&& cast_return(std::remove_reference_t<T>&& result) {
    return reinterpret_cast<
        std::remove_reference_t<typename wrap_type<T>::opaque_type>&&>(result);
  }

  template <class T>
  static auto& cast_arg(typename wrap_type<T>::opaque_type& arg) {
    return *reinterpret_cast<T*>(&arg);
  }

  template <bool is_void, class R, class... A>
  struct make_wrapper;

  // Call function without return value.
  template <class R, class... A>
  struct make_wrapper<true, R, A...> {
    static void invoke(typename wrap_type<A>::opaque_type... args) {
      fn(cast_arg<A>(args)...);
    }
  };

  // Call function with return value.
  template <class R, class... A>
  struct make_wrapper<false, R, A...> {
    static typename wrap_type<R>::opaque_type
        invoke(typename wrap_type<A>::opaque_type... args) {
      return cast_return<R>(fn(cast_arg<A>(args)...));
    }
  };

public:
  static constexpr auto invoke =
      transform_function_t<decltype(fn), make_wrapper>::invoke;
};

// Class instance methods
template <auto method>
class wrap_method {
  template <typename T>
  static auto&& cast_return(std::remove_reference_t<T>&& result) {
    return reinterpret_cast<
        std::remove_reference_t<typename wrap_type<T>::opaque_type>&&>(result);
  }

  // template <typename T>
  // static auto& cast_this(typename wrap_type<T>::opaque_type& arg) {
  //  return *reinterpret_cast<T*>(&arg);
  //}

  template <typename T>
  static auto& cast_arg(typename wrap_type<T>::opaque_type& arg) {
    return *reinterpret_cast<T*>(&arg);
  }

  template <bool is_void, class R, class T, class... A>
  struct make_wrapper;

  // Call method without return value.
  template <class R, class T, class... A>
  struct make_wrapper<true, R, T, A...> {
    static void invoke(typename wrap_qual_type<T*>::opaque_type self,
                       typename wrap_type<A>::opaque_type... args) {
      (cast_arg<T*>(self)->*method)(cast_arg<A>(args)...);
    }
  };

  // Call method with return value.
  template <class R, class T, class... A>
  struct make_wrapper<false, R, T, A...> {
    static typename wrap_type<R>::opaque_type
        invoke(typename wrap_type<T>::opaque_type* self,
               typename wrap_type<A>::opaque_type... args) {
      return cast_return<R>(
          (cast_arg<T*>(self)->*method)(cast_arg<A>(args)...));
    }
  };

public:
  static constexpr auto invoke =
      transform_method_t<decltype(method), make_wrapper>::invoke;
};

} // namespace type_wrapper
using namespace type_wrapper;

// ====== Testing and debugging ======

#if 0
namespace v8_wrap {
extern "C" {
__declspec(dllexport) extern const auto& v8__function__new = v8::Function::New;
__declspec(dllexport) extern const
    auto& v8__local_int32__cast_value = v8::Local<v8::Int32>::Cast<v8::Value>;
extern const auto v8__local_int32__as_value =
    wrap_method<&v8::Local<v8::Int32>::As<v8::Value>>;
extern const auto v8__local_int32__is_empty =
    wrap_method<&v8::Local<v8::Int32>::IsEmpty>;
}
} // namespace v8_wrap
#endif

static void p(std::string s) {
  std::cout << "  => " << s << std::endl;
}

template <class T>
void print_type_() {
  p(cxx_typename<T>());
  p(cxx_typename<typename wrap_type<T>::opaque_type>());
  typename wrap_type<T>::rust_repr rust_repr;
  p(rust_repr.rust_name());
}

template <auto fn, class F = std::remove_pointer_t<decltype(fn)>>
void print_fn_() {
  print_type_<F>();
  static constexpr auto wrapped = wrap_function<fn>::invoke;
  p(cxx_typename<decltype(wrapped)>());
}

template <auto method>
void print_method_() {
  print_type_<decltype(method)>();
  static constexpr auto wrapped = wrap_method<method>::invoke;
  p(cxx_typename<decltype(wrapped)>());
}

void print_(const char* name, void (*printer)()) {
  std::cout << name << std::endl;
  printer();
  std::cout << std::endl;
}

#define test_type(a) print_(#a, print_type_<a>)
#define test_fn(a) print_(#a, print_fn_<a>)
#define test_method(a) print_(#a, print_method_<a>)

struct aap {
  double d[22];
};

void void_fun0() {}
void void_fun1(void* v) {}
int int_fun1(int a) {
  return a;
}

void ff_mut(aap a) {}
void ff_mut_lval(aap& a) {}
void ff_mut_rval(aap&& a) {}
void ff_const(const aap a) {}
void ff_const_lval(const aap& a) {}
void ff_const_rval(const aap&& a) {}

v8::Persistent<v8::Value>&&
    funfunfun(const char* const* a, aap b, v8::Local<v8::Int32>* d) {
  static void* invalid = nullptr;
  return reinterpret_cast<v8::Persistent<v8::Value>&&>(invalid);
}

struct klas {
  int foo0() {
    return 1;
  }
  int foo1(void* arg) {
    return 1;
  }
  void vood1(klas k) {}
  void mm_mut() {}
  void mm_mut_lval() & {}
  void mm_mut_rval() && {}
  void mm_const() const {}
  void mm_const_lval() const& {}
  void mm_const_rval() const&& {}
  template <typename E>
  int foot1(E e, int a, double b) {
    return 2;
  }
};

int main() {
  test_type(int);
  test_type(size_t);
  test_type(int*);
  test_type(void*);
  test_type(v8::Local<v8::Int32>);
  test_type(v8::Local<v8::Int32>*);
  test_type(decltype(funfunfun));
  test_fn(&funfunfun);
  test_fn(&int_fun1);
  test_fn(&void_fun0);
  test_fn(&void_fun1);
  int a[3];
  test_type(decltype(a));
  std::string strings[10];
  test_type(decltype(strings));
  test_type(aap);
  test_method(&klas::foo0);
  test_method(&klas::foo1);
  test_method(&klas::vood1);

  test_fn(&ff_mut);
  // test_fn(&ff_mut_lval);
  // test_fn(&ff_mut_rval);
  test_fn(&ff_const);
  // test_fn(&ff_const_lval);
  // test_fn(&ff_const_rval);

  test_method(&klas::mm_mut);
  // test_method(&klas::mm_mut_lval);
  // test_method(&klas::mm_mut_rval);
  test_method(&klas::mm_const);
  // test_method(&klas::mm_const_lval);
  // test_method(&klas::mm_const_rval);

  // test_method(&v8::Local<v8::Int32>::As<v8::Value>);
}
