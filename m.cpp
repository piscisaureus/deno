
#include "d:/deno/third_party/v8/include/v8.h"

#include <iostream>
#include <stdio.h>
#include <type_traits>

struct v8_Value;
struct v8_Number;

struct v8_Local_Value {
  v8_Value* val_;
};

struct v8_Local_Number {
  v8_Number* val_;
};

extern "C" v8_Local_Value v8_Local_Value_from_Local_Number(v8_Local_Number a_c) {
  v8::Local<v8::Number> a = *reinterpret_cast<v8::Local<v8::Number>*>(&a_c);
  printf("%p %p\n", &a, &a_c);
  v8::Local<v8::Value> b = a;
  v8_Local_Value& b_c = *reinterpret_cast<v8_Local_Value*>(&b);
  printf("%p %p\n", &b, &b_c);
  return b_c;
}

extern "C" void test() {
  v8_Local_Value vc = { reinterpret_cast<v8_Value*>(1) };
  v8::Local<v8::Value>& v = *reinterpret_cast<v8::Local<v8::Value>*>(&vc);
  printf("a %p\n", vc.val_);
  new (&v) v8::Local<v8::Value>();
  v.~Local();
  printf("b %p\n", vc.val_);
  printf("%p %p\n", &v, &vc);
}

int main() {
  struct v8_Local_Number a;
  v8_Local_Value_from_Local_Number(a);
  test();
  std::cout << std::is_convertible<v8::Local<v8::String>, v8::Local<v8::Number>>::value << std::endl;
  std::cout << std::is_convertible<v8::Number, v8::Symbol>::value << std::endl;
}

namespace v8 {
struct Nada1 { };
struct Nada2: public Nada1 {};
struct Nada3: public Nada2 { char a; char b; char c; };
struct Nada4: public Nada3 { char d; };

template class v8::Local<v8::Number>;
template class v8::Local<v8::String>;
template v8::Local<v8::Number>::Local(v8::Local<v8::Integer>);
template v8::Local<v8::Number>::Local(v8::Global<v8::Integer>);
}