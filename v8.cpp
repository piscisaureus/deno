
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
struct UNKNOWN {};

template <class T, typename = void>
struct wrap_qual_type;

template <class T, typename = void>
struct wrap_type;

template <int align, typename = void>
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
  using element_t = typename element::type;
  static constexpr size_t element_count = size / sizeof(element_t);

  static_assert(size == sizeof(element_t) * element_count, "size mismatch");
  static_assert(align == alignof(element_t), "alignment mismatch");

public:
  using type = element_t[element_count];

  static std::string rust_type() {
    std::ostringstream s;
    s << "[" << element::rust_type() << "; " << element_count << "]";
    return s.str();
  }
};

template <class T, class>
struct wrap_type {
  using type = UNKNOWN;
  static std::string rust_type() {
    return std::string("??");
  }
};

template <auto fn>
struct fn_wrapper {
private:
  template <class R, class... A>
  struct invoker {
    static R invoke_fn(A... args) {
      return fn(args...);
    }
  };

  template <class R, class... A>
  static constexpr auto wrap_fn(R (*f)(A...)) {
    return invoker<R, A...>::invoke_fn;
  }

public:
  static constexpr auto ptr = fn_wrapper<fn>::wrap_fn(fn);
  using type = decltype(*ptr);
};

template <class T>
struct wrap_type<T, std::enable_if_t<std::is_same<T, void>::value>> {
  using type = void;
  static std::string rust_type() {
    return std::string("std::ffi::c_void");
  }
};

template <class T>
struct wrap_type<
    T,
    std::enable_if_t<std::is_integral<T>::value && std::is_signed<T>::value>> {
  using type = T;
  static std::string rust_type() {
    return std::string("i") + std::to_string(8 * sizeof(T));
  }
};

template <class T>
struct wrap_type<T,
                 std::enable_if_t<std::is_integral<T>::value &&
                                  std::is_unsigned<T>::value>> {
  using type = T;
  static std::string rust_type() {
    return std::string("u") + std::to_string(8 * sizeof(T));
  }
};

template <class T>
struct wrap_type<T, std::enable_if_t<std::is_array<T>::value>> {
  using type = typename filler<T>::type;

  static std::string rust_type() {
    return filler<T>::rust_type();
  }
};

template <class T>
struct wrap_type<
    T,
    std::enable_if_t<std::is_class<T>::value || std::is_union<T>::value>> {
public:
  using type = struct { typename filler<T>::type _; };

  static std::string rust_type() {
    std::ostringstream s;
    s << "struct(" << filler<T>::rust_type() << ")";
    return s.str();
  }
};

template <class F>
struct wrap_type<F, std::enable_if_t<std::is_function<F>::value>> {
private:
  template <template <class, class...> class Functor, class R, class... A>
  static auto apply(R (*f)(A...)) {
    return Functor<R, A...>::apply(f);
  };

  template <class R, class... A>
  struct cast_types {
    static auto apply(F* f) {
      return reinterpret_cast<typename wrap_type<R>::type (*)(
          typename wrap_type<A>::type...)>(f);
    };
  };

  template <class R, class... A>
  struct map_rust_types {
    template <class T>
    static auto rust_type() {
      return wrap_type<T>::rust_type();
    }

    static auto apply(F* f) {
      std::string ret_type = rust_type<R>();
      std::string arg_type[] = {rust_type<A>()..., std::string()};
      size_t arg_count = sizeof(arg_type) / sizeof(arg_type[0]) - 1;

      std::ostringstream s;
      s << "fn(";
      for (size_t i = 0; i < arg_count; i++) {
        if (i > 0)
          s << ", ";
        s << arg_type[i];
      }
      s << ") -> " << ret_type;
      return s.str();
    };
  };

  static constexpr F* f = nullptr;

public:
  using type = decltype(*apply<cast_types>(f));

  static std::string rust_type() {
    return apply<map_rust_types>(f);
  }
};

template <class T>
struct wrap_type<T, std::enable_if_t<std::is_pointer<T>::value>> {
private:
  using target = wrap_qual_type<std::remove_pointer_t<T>>;

public:
  using type = typename target::type*;
  static std::string rust_type() {
    return std::string("*") + target::rust_raw_type();
  }
};

template <class T>
struct wrap_qual_type<
    T,
    std::enable_if_t<std::is_const<T>::value && !std::is_volatile<T>::value>> {
  using unqualified = wrap_type<T>;

public:
  using type = const typename unqualified::type*;

  static std::string rust_type() {
    return unqualified::rust_type();
  }
  static std::string rust_raw_type() {
    return std::string("const ") + unqualified::rust_type();
  }
};

template <class T>
struct wrap_qual_type<
    T,
    std::enable_if_t<!std::is_const<T>::value && !std::is_volatile<T>::value>> {
  using unqualified = wrap_type<T>;

public:
  using type = typename unqualified::type*;

  static std::string rust_type() {
    return std::string("mut ") + unqualified::rust_type();
  }
  static std::string rust_raw_type() {
    return rust_type();
  }
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

template <class T>
void test_type() {
  std::cout << typeid(T).name() << "\n  => "
            << typeid(typename wrap_type<T>::type).name() << "\n  => "
            << wrap_type<T>::rust_type() << std::endl;
}

struct aap {
  double d[22];
};

int funfunfun(const char* const* a, aap b, v8::Local<v8::Int32>* d) {
  return 1;
}

int main() {
  test_type<int>();
  test_type<size_t>();
  test_type<int*>();
  test_type<void*>();
  test_type<v8::Local<v8::Int32>>();
  test_type<v8::Local<v8::Int32>*>();
  test_type<decltype(test_type<void>)>();
  test_type<decltype(funfunfun)>();
  int a[3];
  test_type<decltype(a)>();
  test_type<aap>();
}
