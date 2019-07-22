
#include "v8/include/v8.h"

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
