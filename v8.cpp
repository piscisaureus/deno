
#include "v8/include/v8config.h"
#undef V8_EXPORT
#define V8_EXPORT
#include "v8/include/v8.h"

/*
namespace v8_c {
  using namespace v8;

  template <class T>
  T& make() {
    static char data[sizeof(T)];
    return *reinterpret_cast<T*>(data);
  }

  void dummy() {
    auto parameter = make<void*>();
    auto callback = make<typename WeakCallbackInfo<void>::Callback>();
    auto type = make<WeakCallbackType>();
    auto& handle = make<Persistent<Object>>();
    handle.SetWeak(parameter, callback, type);
  }
}

namespace v8 {
  class Test {
    public:
      void Foo() const & {}
      void Foo() const && {}
      void Foo() && {}
      void Foo() & {}
  };

  void Poep(int);
  void Poep(int kaas);
  void Poep(int);
  void Poep(int boterham) {}
}
*/

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <typeinfo>

namespace type_wrapper {

#if defined(__GNUG__) // or Clang when it's emulating GCC.
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

#elif defined(_MSC_VER) // or Clang when it's emulating MSVC.
template <class T>
std::string cxx_typename() {
  return typeid(T).name();
}
#endif

template <class T, class = void>
class wrap_type;

template <class T, class W = wrap_type<std::remove_cv_t<T>>, class = void>
struct wrap_qual_type;

template <int align, class = void>
struct aligned_uint;
template <int align>
using aligned_uint_t = typename aligned_uint<align>::type;

template <>
struct aligned_uint<1, std::enable_if_t<1 == alignof(uint8_t)>> {
  using type = uint8_t;
};
template <>
struct aligned_uint<2, std::enable_if_t<2 == alignof(uint16_t)>> {
  using type = uint16_t;
};
template <>
struct aligned_uint<4, std::enable_if_t<4 == alignof(uint32_t)>> {
  using type = uint32_t;
};
template <>
struct aligned_uint<8, std::enable_if_t<8 == alignof(uint64_t)>> {
  using type = uint64_t;
};

template <class T>
struct filler {
private:
  static constexpr size_t size = sizeof(T);
  static constexpr size_t align = alignof(T);

  using element = wrap_type<aligned_uint_t<align>>;
  using element_t = typename element::opaque_type;
  static constexpr size_t element_count = size / sizeof(element_t);
  using element_rust_repr_t = typename element::rust_repr;

  static_assert(size == sizeof(element_t) * element_count, "size mismatch");
  static_assert(align == alignof(element_t), "alignment mismatch");

public:
  using type = element_t[element_count];

  static std::string rust_type() {
    std::ostringstream s;
    s << "[" << element_rust_repr_t().rust_type() << "; " << element_count
      << "]";
    return s.str();
  }
};

class rust_repr_base {
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

static size_t type_index_counter = 0;

template <class T>
class rust_non_primitive_type : public rust_repr_base {
  static size_t index() {
    static const auto v = ++type_index_counter;
    return v;
  }

public:
  std::string rust_name() override {
    std::ostringstream os;
    os << "@" << index() << "@"
       << " " << rust_type();
    return os.str();
  }
};

template <class T, class>
class wrap_type {
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
class wrap_type<T, std::enable_if_t<std::is_same_v<T, void>>> {
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

template <char letter, int byte_size>
class rust_numeric_type : public rust_primitive_type {
public:
  std::string rust_type() override {
    std::ostringstream os;
    os << letter << (byte_size << 3);
    return os.str();
  }
};

template <class T>
class wrap_type<
    T,
    std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value>> {
public:
  using opaque_type = T;
  using rust_repr = rust_numeric_type<'i', sizeof(T)>;
};

template <class T>
class wrap_type<T,
                std::enable_if_t<std::is_integral<T>::value &&
                                 std::is_unsigned<T>::value>> {
public:
  using opaque_type = T;
  using rust_repr = rust_numeric_type<'u', sizeof(T)>;
};

template <class T>
class wrap_type<T, std::enable_if_t<std::is_array<T>::value>> {
  template <class>
  struct array_element {};

  template <class E, size_t N>
  struct array_element<E[N]> {
    using type = E;
    static constexpr auto count = N;
  };

  using el = array_element<T>;
  using el_opaque_t = typename wrap_type<typename el::type>::opaque_type;
  using el_rust_repr = typename wrap_type<typename el::type>::rust_repr;

public:
  using opaque_type = el_opaque_t[el::count];
  static_assert(sizeof(T) == sizeof(opaque_type), "size mismatch");
  static_assert(alignof(T) == alignof(opaque_type), "alignment mismatch");

  class rust_repr : public rust_primitive_type {
  public:
    std::string rust_type() override {
      std::ostringstream os;
      os << "[" << el_rust_repr().rust_name() << "; " << el::count << "]";
      return os.str();
    }
  };
};

template <class T>
class wrap_type<
    T,
    std::enable_if_t<std::is_class<T>::value || std::is_union<T>::value>> {
public:
  using opaque_type = struct { typename filler<T>::type _; };

  class rust_repr : public rust_non_primitive_type<T> {
  public:
    std::string rust_type() override {
      std::ostringstream os;
      os << "struct(" << filler<T>::rust_type() << ")";
      return os.str();
    }
  };
};

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

template <auto fn>
class wrap_function {
  template <typename T>
  static auto& cast_arg(typename wrap_type<T>::opaque_type& arg) {
    return *reinterpret_cast<T*>(&arg);
  }

  template <typename T>
  static auto&& cast_return(T&& result) {
    return *reinterpret_cast<typename wrap_type<T>::opaque_type*>(&result);
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

template <class F>
struct wrap_type<F, std::enable_if_t<std::is_function_v<F>>> {
  template <bool is_void, class R, class... A>
  using make_opaque_type = typename wrap_type<R>::opaque_type (&)(
      typename wrap_type<A>::opaque_type... args);

  template <bool is_void, class R, class... A>
  class make_rust_repr : public rust_non_primitive_type<F> {
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

    static auto FunctorResult() {
      return map_rust_repr();
    }
  };

public:
  using opaque_type = transform_function_t<F, make_opaque_type>;
  using rust_repr = transform_function_t<F, make_rust_repr>;
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

template <class T>
class wrap_type<T, std::enable_if_t<std::is_pointer_v<T>>> {
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
class wrap_type<T, std::enable_if_t<std::is_reference<T>::value>> {
private:
  using target = std::remove_reference_t<T>;
  using wrapped_target = wrap_qual_type<target>;

public:
  using opaque_type = std::add_pointer_t<typename wrapped_target::opaque_type>;
  using rust_repr = rust_pointer_type<wrapped_target>;
};

template <class W>
class rust_qual_type : public rust_primitive_type {
  typename W::rust_repr target_repr;

protected:
  virtual std::string rust_qual() = 0;

public:
  std::string rust_type() override {
    std::ostringstream os;
    os << rust_qual() << " " << target_repr.rust_name();
    return os.str();
  }
};

template <class T, class W>
class wrap_qual_type<
    T,
    W,
    std::enable_if_t<std::is_const<T>::value && !std::is_volatile<T>::value>> {
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
    std::enable_if_t<!std::is_const<T>::value && !std::is_volatile<T>::value>> {
public:
  using opaque_type = typename W::opaque_type;

  class rust_repr : public rust_qual_type<W> {
    std::string rust_qual() override {
      return "mut";
    }
  };
};
} // namespace type_wrapper
using namespace type_wrapper;

namespace method_wrapper {
namespace {
template <auto method>
struct wrapper {
  template <class R, class T, class... A>
  struct invoker {
    static R invoke_method(T self, A... args) {
      return (self->*method)(args...);
    }
  };

  template <class R, class T, class... A>
  static constexpr auto wrap_method(R (T::*m)(A...)) {
    return invoker<R, T*, A...>::invoke_method;
  }

  template <class R, class T, class... A>
  static constexpr auto wrap_method(R (T::*m)(A...) const) {
    return invoker<R, const T*, A...>::invoke_method;
  }

  static constexpr auto wrap = wrapper<method>::wrap_method(method);
};
} // namespace

template <auto fn>
constexpr auto wrap_method = wrapper<fn>::wrap;
} // namespace method_wrapper
using namespace method_wrapper;

template <typename K>
struct test {
  int foo0() {
    return 1;
  }
  int foo1(void* arg) {
    return 1;
  }
  template <typename E>
  int foot1(E e, int a, double b) {
    return 2;
  }
};

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

void print_(const char* name, void (*printer)()) {
  std::cout << name << std::endl;
  printer();
  std::cout << std::endl;
}

#define test_type(a) print_(#a, print_type_<a>)
#define test_fn(a) print_(#a, print_fn_<a>)

struct aap {
  double d[22];
};

void void_fun0() {}
void void_fun1(void* v) {}
int int_fun1(int a) {
  return a;
}

v8::Persistent<v8::Value>&&
    funfunfun(const char* const* a, aap b, v8::Local<v8::Int32>* d) {
  static void* invalid = nullptr;
  return reinterpret_cast<v8::Persistent<v8::Value>&&>(invalid);
}

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
}
