
#include "v8/include/v8config.h"
#undef V8_EXPORT
#define V8_EXPORT
#include "v8/include/v8.h"

/*
namespace v8_c {
  using namespace v8;

  template <typename T>
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

#include <cstdio>
#include <functional>
#include <typeinfo>

template <auto fn>
struct wrapper {
  template <class R, class T, class... A>
  struct caller {
    static R call_fn(T self, A... args) {
      return (self->*fn)(args...);
    }
  };

  template <class R, class T, class... A>
  static constexpr auto wrap_fn(R (T::*m)(A...)) { 
    return caller<R, T*, A...>::call_fn;
  }  
  
  template <class R, class T, class... A>
  static constexpr auto wrap_fn(R (T::*m)(A...) const) { 
    return caller<R, const T*, A...>::call_fn;
  }

  static constexpr auto wrap = wrapper<fn>::wrap_fn(fn);
};

template <auto fn>
constexpr auto wrap = wrapper<fn>::wrap;

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

namespace v8_wrap {
extern "C" {
__declspec(dllexport) extern const auto& v8__function__new = v8::Function::New;
__declspec(dllexport) extern const
    auto& v8__local_int32__cast_value = v8::Local<v8::Int32>::Cast<v8::Value>;
extern const auto v8__local_int32__as_value =
    wrap<&v8::Local<v8::Int32>::As<v8::Value>>;
extern const auto v8__local_int32__is_empty =
    wrap<&v8::Local<v8::Int32>::IsEmpty>;
}
} // namespace v8_wrap

int main() {
}
