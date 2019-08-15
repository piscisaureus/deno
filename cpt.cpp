
#include <iostream>
#include <typeinfo>
#include <string>
#include <functional>

struct DeclContext {};

struct OpenContext: DeclContext {};
struct ClosedContext: DeclContext {};

struct RootContext: OpenContext {};
struct Namespace {};

template <class P, class T>
struct HasParent: T { using Parent = P; };

template <class T>
struct MetaType { using Type = T; };

template <class T> 
struct Class: OpenContext, MetaType<T> {};

template <class T>
struct PointerType: MetaType<T> { using Target = std::remove_pointer<T>; };

template <class T>
struct OpaquePointerType: MetaType<T> {};

template <class T>
struct FnArg: MetaType<T> {};

template <class... Args>
using FnArgPack = void(&)(Args... args);

template <class R, class A> 
struct Function: ClosedContext { 
  using Ret = R;
  using Args = A;
};

template <class R, class A> 
struct StaticMethod: Function<R, A> {};

template <class R, class T, class A> 
struct InstanceMethod: Function<R, A> {
  using This = T;
};

using root = RootContext;
using ns_v8 = HasParent<root, Namespace>;
using ns_std = HasParent<ns_v8, Namespace>;

using fn_bar_arg_0 = FnArg<const void*>;
using fn_bar_arg_1 = FnArg<int>;
using fn_bar_arg_2 = FnArg<double>;
using fn_bar = HasParent<ns_v8, Function<void, FnArgPack<fn_bar_arg_0, fn_bar_arg_1, fn_bar_arg_2>>>;

class Klass {};
using cl_klass = HasParent<ns_std, Class<Klass>>;
using fn_kfn_arg_0 = FnArg<const void*>;
using fn_kfn_arg_1 = FnArg<double>;
using fn_kfn = HasParent<ns_v8, InstanceMethod<int, cl_klass::Type, FnArgPack<fn_kfn_arg_0, fn_bar_arg_1>>>;

template <class R, class... Args>
auto fn_ptr(Function<R, FnArgPack<FnArg<Args>...>> fn) { return PointerType<R (*)(Args...)>(); }

template <class R, class T, class... Args>
auto fn_ptr(InstanceMethod<R, T, FnArgPack<FnArg<Args>...>> fn) { return OpaquePointerType<R (T::*)(Args...)>(); }

template <typename T>
using fn_ptr_t = typename decltype(fn_ptr(T()))::Type;

using bar_ptr = fn_ptr_t<fn_bar>;
using kfn_ptr = fn_ptr_t<fn_kfn>;

int main() {
  std::cout << typeid(bar_ptr).name() << std::endl;
  std::cout << typeid(kfn_ptr).name() << std::endl;
  return 0;
}


