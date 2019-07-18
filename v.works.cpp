
#include "v8/include/v8.h"
#include <assert.h>
#include <iostream>
#include <typeinfo>

namespace v8 {

/*
class Int32 {};
class Value {};

template <typename T>
class Local {
public:
  T* ptr;

  template <typename S>
  static Local<T> Cast(Local<S> that) {
    Local r{.ptr = reinterpret_cast<T*>(that.ptr)};
    return r;
  }
};
*/

namespace c_wrapper {

struct v8__local_int32 {
  using cxx_type = v8::Local<v8::Int32>;
  void* ptr;
};

struct v8__local_value {
  using cxx_type = v8::Local<v8::Value>;
  void* ptr;
};

struct v8__value {
  using cxx_type = v8::Value;
};

class Pod {
  template <typename T, template <typename> class D>
  struct map_type {
  private:
    template <typename S>
    struct mapping;

    template <>
    struct mapping<typename D<v8__local_int32>::from_type>
        : D<v8__local_int32> {};
    template <>
    struct mapping<typename D<v8__local_value>::from_type>
        : D<v8__local_value> {};    
    template <>
    struct mapping<typename D<v8__value>::from_type> : D<v8__value> {};

    template <typename M>
    struct assert_valid : M {
      static_assert(sizeof(typename M::from_type) ==
                        sizeof(typename M::to_type),
                    "size mismatch");
      static_assert(alignof(typename M::from_type) ==
                        alignof(typename M::to_type),
                    "alignment mismatch");
    };

  public:
    using result_type = typename assert_valid<mapping<T>>::to_type;
  };

  template <template <typename> class M>
  struct cast {
  private:
    template <typename T>
    using result_type = typename M<T>::result_type;

  public:
    template <typename I>
    result_type<I>&& operator()(I&& value) const {
      return reinterpret_cast<result_type<I>&&>(value);
    };

    template <typename I>
    const result_type<I>&& operator()(const I&& value) const {
      return reinterpret_cast<const result_type<I>&&>(value);
    }    

    template <typename I>
    result_type<I>* operator()(I* value) const {
      return reinterpret_cast<result_type<I>*>(value);
    };

    template <typename I>
    const result_type<I>* operator()(const I* value) const {
      return reinterpret_cast<const result_type<I>*>(value);
    }
  };

  template <typename P>
  struct cxx_to_pod_mapping {
    using from_type = typename P::cxx_type;
    using to_type = P;
  };

  template <typename P>
  struct pod_to_cxx_mapping {
    using from_type = P;
    using to_type = typename P::cxx_type;
  };

  template <typename T>
  using cxx_to_pod_type = map_type<T, cxx_to_pod_mapping>;
  template <typename T>
  using pod_to_cxx_type = map_type<T, pod_to_cxx_mapping>;

public:
  template <typename T>
  using pod_type = typename cxx_to_pod_type<T>::result_type;
  template <typename T>
  using cxx_type = typename cxx_to_pod_type<T>::result_type;

  using pod_cast = cast<cxx_to_pod_type>;
  using cxx_cast = cast<pod_to_cxx_type>;

  static const pod_cast wrap;
  static const cxx_cast unwrap;
};

const Pod::pod_cast Pod::wrap;
const Pod::cxx_cast Pod::unwrap;

extern "C" {
//bool v8__value__is_null(const v8__value* self) {
//  return Pod::unwrap(self)->IsNull();
//}
//
v8__local_value v8__local_value__cast_int32(v8__local_int32 that) {
  return Pod::wrap(v8::Local<v8::Value>::Cast(Pod::unwrap(std::move(that))));
}
//
//v8__local_int32 v8__local_value__as_int32(const v8__local_value* self) {
//  return Pod::wrap(Pod::unwrap(self)->As<v8::Int32>());
//}
// 
//v8__local_value v8__local_int32__as_value(const v8__local_int32* self) {
//  return Pod::wrap(Pod::unwrap(self)->As<v8::Value>());
//}
//
//v8__value* v8__local_value__deref(const v8__local_value* self) {
// return Pod::wrap(Pod::unwrap(self)->operator->());
//}

}  // extern "C"
} // namespace c_wrapper
} // namespace v8

using namespace v8::c_wrapper;
int main() {
  v8::Local<v8::Int32> v;
  auto c1 = Pod::wrap(std::move(v));
  std::cout << typeid(c1).name() << std::endl;
  auto c2 = Pod::unwrap(std::move(c1));
  std::cout << typeid(c2).name() << std::endl;
}