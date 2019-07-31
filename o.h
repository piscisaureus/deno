#define DECLARATIONS(X) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, void (v8::Local<v8::Primitive>::*)()) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, void (v8::Local<v8::Primitive>::*)(v8::Local<v8::Primitive>)) \
  X(CXXMethod, v8::Local<v8::Primitive>::IsEmpty, bool (v8::Local<v8::Primitive>::*)() const) \
  X(CXXMethod, v8::Local<v8::Primitive>::Clear, void (v8::Local<v8::Primitive>::*)()) \
  X(CXXMethod, v8::Local<v8::Primitive>::operator->, v8::Primitive *(v8::Local<v8::Primitive>::*)() const) \
  X(CXXMethod, v8::Local<v8::Primitive>::operator*, v8::Primitive *(v8::Local<v8::Primitive>::*)() const) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, v8::Local<v8::Primitive> (*)(v8::Isolate *, v8::Local<v8::Primitive>)) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, v8::Local<v8::Primitive> (*)(v8::Isolate *, const v8::PersistentBase<v8::Primitive> &)) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, v8::Local<v8::Primitive> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Primitive> &)) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, void (v8::Local<v8::Primitive>::*)(const v8::Local<v8::Primitive> &)) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, void (v8::Local<v8::Primitive>::*)(v8::Local<v8::Primitive> &&)) \
  X(CXXDestructor, v8::Local<v8::Primitive>::~Local, void (v8::Local<v8::Primitive>::*)()) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, void (v8::Local<v8::Boolean>::*)()) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, void (v8::Local<v8::Boolean>::*)(v8::Local<v8::Boolean>)) \
  X(CXXMethod, v8::Local<v8::Boolean>::IsEmpty, bool (v8::Local<v8::Boolean>::*)() const) \
  X(CXXMethod, v8::Local<v8::Boolean>::Clear, void (v8::Local<v8::Boolean>::*)()) \
  X(CXXMethod, v8::Local<v8::Boolean>::operator->, v8::Boolean *(v8::Local<v8::Boolean>::*)() const) \
  X(CXXMethod, v8::Local<v8::Boolean>::operator*, v8::Boolean *(v8::Local<v8::Boolean>::*)() const) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, v8::Local<v8::Boolean> (*)(v8::Isolate *, v8::Local<v8::Boolean>)) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, v8::Local<v8::Boolean> (*)(v8::Isolate *, const v8::PersistentBase<v8::Boolean> &)) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, v8::Local<v8::Boolean> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Boolean> &)) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, void (v8::Local<v8::Boolean>::*)(const v8::Local<v8::Boolean> &)) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, void (v8::Local<v8::Boolean>::*)(v8::Local<v8::Boolean> &&)) \
  X(CXXDestructor, v8::Local<v8::Boolean>::~Local, void (v8::Local<v8::Boolean>::*)()) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, void (v8::Local<v8::Value>::*)()) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, void (v8::Local<v8::Value>::*)(v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Local<v8::Value>::IsEmpty, bool (v8::Local<v8::Value>::*)() const) \
  X(CXXMethod, v8::Local<v8::Value>::Clear, void (v8::Local<v8::Value>::*)()) \
  X(CXXMethod, v8::Local<v8::Value>::operator->, v8::Value *(v8::Local<v8::Value>::*)() const) \
  X(CXXMethod, v8::Local<v8::Value>::operator*, v8::Value *(v8::Local<v8::Value>::*)() const) \
  X(CXXMethod, v8::Local<v8::Value>::New, v8::Local<v8::Value> (*)(v8::Isolate *, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Local<v8::Value>::New, v8::Local<v8::Value> (*)(v8::Isolate *, const v8::PersistentBase<v8::Value> &)) \
  X(CXXMethod, v8::Local<v8::Value>::New, v8::Local<v8::Value> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Value> &)) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, void (v8::Local<v8::Value>::*)(const v8::Local<v8::Value> &)) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, void (v8::Local<v8::Value>::*)(v8::Local<v8::Value> &&)) \
  X(CXXDestructor, v8::Local<v8::Value>::~Local, void (v8::Local<v8::Value>::*)()) \
  X(CXXMethod, v8::Local<v8::Value>::operator=, v8::Local<v8::Value> &(v8::Local<v8::Value>::*)(const v8::Local<v8::Value> &)) \
  X(CXXMethod, v8::Local<v8::Value>::operator=, v8::Local<v8::Value> &(v8::Local<v8::Value>::*)(v8::Local<v8::Value> &&)) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, void (v8::Local<v8::PrimitiveArray>::*)()) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, void (v8::Local<v8::PrimitiveArray>::*)(v8::Local<v8::PrimitiveArray>)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::IsEmpty, bool (v8::Local<v8::PrimitiveArray>::*)() const) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::Clear, void (v8::Local<v8::PrimitiveArray>::*)()) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator->, v8::PrimitiveArray *(v8::Local<v8::PrimitiveArray>::*)() const) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator*, v8::PrimitiveArray *(v8::Local<v8::PrimitiveArray>::*)() const) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, v8::Local<v8::PrimitiveArray> (*)(v8::Isolate *, v8::Local<v8::PrimitiveArray>)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, v8::Local<v8::PrimitiveArray> (*)(v8::Isolate *, const v8::PersistentBase<v8::PrimitiveArray> &)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, v8::Local<v8::PrimitiveArray> (*)(v8::Isolate *, const v8::TracedGlobal<v8::PrimitiveArray> &)) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, void (v8::Local<v8::PrimitiveArray>::*)(const v8::Local<v8::PrimitiveArray> &)) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, void (v8::Local<v8::PrimitiveArray>::*)(v8::Local<v8::PrimitiveArray> &&)) \
  X(CXXDestructor, v8::Local<v8::PrimitiveArray>::~Local, void (v8::Local<v8::PrimitiveArray>::*)()) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator=, v8::Local<v8::PrimitiveArray> &(v8::Local<v8::PrimitiveArray>::*)(const v8::Local<v8::PrimitiveArray> &)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator=, v8::Local<v8::PrimitiveArray> &(v8::Local<v8::PrimitiveArray>::*)(v8::Local<v8::PrimitiveArray> &&)) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, void (v8::Local<v8::Integer>::*)()) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, void (v8::Local<v8::Integer>::*)(v8::Local<v8::Integer>)) \
  X(CXXMethod, v8::Local<v8::Integer>::IsEmpty, bool (v8::Local<v8::Integer>::*)() const) \
  X(CXXMethod, v8::Local<v8::Integer>::Clear, void (v8::Local<v8::Integer>::*)()) \
  X(CXXMethod, v8::Local<v8::Integer>::operator->, v8::Integer *(v8::Local<v8::Integer>::*)() const) \
  X(CXXMethod, v8::Local<v8::Integer>::operator*, v8::Integer *(v8::Local<v8::Integer>::*)() const) \
  X(CXXMethod, v8::Local<v8::Integer>::New, v8::Local<v8::Integer> (*)(v8::Isolate *, v8::Local<v8::Integer>)) \
  X(CXXMethod, v8::Local<v8::Integer>::New, v8::Local<v8::Integer> (*)(v8::Isolate *, const v8::PersistentBase<v8::Integer> &)) \
  X(CXXMethod, v8::Local<v8::Integer>::New, v8::Local<v8::Integer> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Integer> &)) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, void (v8::Local<v8::Integer>::*)(const v8::Local<v8::Integer> &)) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, void (v8::Local<v8::Integer>::*)(v8::Local<v8::Integer> &&)) \
  X(CXXDestructor, v8::Local<v8::Integer>::~Local, void (v8::Local<v8::Integer>::*)()) \
  X(CXXMethod, v8::Local<v8::Integer>::operator=, v8::Local<v8::Integer> &(v8::Local<v8::Integer>::*)(const v8::Local<v8::Integer> &)) \
  X(CXXMethod, v8::Local<v8::Integer>::operator=, v8::Local<v8::Integer> &(v8::Local<v8::Integer>::*)(v8::Local<v8::Integer> &&)) \
  X(CXXConstructor, v8::Local<v8::String>::Local, void (v8::Local<v8::String>::*)()) \
  X(CXXConstructor, v8::Local<v8::String>::Local, void (v8::Local<v8::String>::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Local<v8::String>::IsEmpty, bool (v8::Local<v8::String>::*)() const) \
  X(CXXMethod, v8::Local<v8::String>::Clear, void (v8::Local<v8::String>::*)()) \
  X(CXXMethod, v8::Local<v8::String>::operator->, v8::String *(v8::Local<v8::String>::*)() const) \
  X(CXXMethod, v8::Local<v8::String>::operator*, v8::String *(v8::Local<v8::String>::*)() const) \
  X(CXXMethod, v8::Local<v8::String>::New, v8::Local<v8::String> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Local<v8::String>::New, v8::Local<v8::String> (*)(v8::Isolate *, const v8::PersistentBase<v8::String> &)) \
  X(CXXMethod, v8::Local<v8::String>::New, v8::Local<v8::String> (*)(v8::Isolate *, const v8::TracedGlobal<v8::String> &)) \
  X(CXXConstructor, v8::Local<v8::String>::Local, void (v8::Local<v8::String>::*)(const v8::Local<v8::String> &)) \
  X(CXXConstructor, v8::Local<v8::String>::Local, void (v8::Local<v8::String>::*)(v8::Local<v8::String> &&)) \
  X(CXXMethod, v8::Local<v8::String>::operator=, v8::Local<v8::String> &(v8::Local<v8::String>::*)(const v8::Local<v8::String> &)) \
  X(CXXMethod, v8::Local<v8::String>::operator=, v8::Local<v8::String> &(v8::Local<v8::String>::*)(v8::Local<v8::String> &&)) \
  X(CXXDestructor, v8::Local<v8::String>::~Local, void (v8::Local<v8::String>::*)()) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, void (v8::Local<v8::Context>::*)()) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, void (v8::Local<v8::Context>::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Local<v8::Context>::IsEmpty, bool (v8::Local<v8::Context>::*)() const) \
  X(CXXMethod, v8::Local<v8::Context>::Clear, void (v8::Local<v8::Context>::*)()) \
  X(CXXMethod, v8::Local<v8::Context>::operator->, v8::Context *(v8::Local<v8::Context>::*)() const) \
  X(CXXMethod, v8::Local<v8::Context>::operator*, v8::Context *(v8::Local<v8::Context>::*)() const) \
  X(CXXMethod, v8::Local<v8::Context>::New, v8::Local<v8::Context> (*)(v8::Isolate *, v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Local<v8::Context>::New, v8::Local<v8::Context> (*)(v8::Isolate *, const v8::PersistentBase<v8::Context> &)) \
  X(CXXMethod, v8::Local<v8::Context>::New, v8::Local<v8::Context> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Context> &)) \
  X(CXXDestructor, v8::Local<v8::Context>::~Local, void (v8::Local<v8::Context>::*)()) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, void (v8::Local<v8::Context>::*)(const v8::Local<v8::Context> &)) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, void (v8::Local<v8::Context>::*)(v8::Local<v8::Context> &&)) \
  X(CXXConstructor, v8::Local<v8::UnboundScript>::Local, void (v8::Local<v8::UnboundScript>::*)()) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::IsEmpty, bool (v8::Local<v8::UnboundScript>::*)() const) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::Clear, void (v8::Local<v8::UnboundScript>::*)()) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::operator->, v8::UnboundScript *(v8::Local<v8::UnboundScript>::*)() const) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::operator*, v8::UnboundScript *(v8::Local<v8::UnboundScript>::*)() const) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, v8::Local<v8::UnboundScript> (*)(v8::Isolate *, v8::Local<v8::UnboundScript>)) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, v8::Local<v8::UnboundScript> (*)(v8::Isolate *, const v8::PersistentBase<v8::UnboundScript> &)) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, v8::Local<v8::UnboundScript> (*)(v8::Isolate *, const v8::TracedGlobal<v8::UnboundScript> &)) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, void (v8::Local<v8::Function>::*)()) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, void (v8::Local<v8::Function>::*)(v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Local<v8::Function>::IsEmpty, bool (v8::Local<v8::Function>::*)() const) \
  X(CXXMethod, v8::Local<v8::Function>::Clear, void (v8::Local<v8::Function>::*)()) \
  X(CXXMethod, v8::Local<v8::Function>::operator->, v8::Function *(v8::Local<v8::Function>::*)() const) \
  X(CXXMethod, v8::Local<v8::Function>::operator*, v8::Function *(v8::Local<v8::Function>::*)() const) \
  X(CXXMethod, v8::Local<v8::Function>::New, v8::Local<v8::Function> (*)(v8::Isolate *, v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Local<v8::Function>::New, v8::Local<v8::Function> (*)(v8::Isolate *, const v8::PersistentBase<v8::Function> &)) \
  X(CXXMethod, v8::Local<v8::Function>::New, v8::Local<v8::Function> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Function> &)) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, void (v8::Local<v8::Function>::*)(const v8::Local<v8::Function> &)) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, void (v8::Local<v8::Function>::*)(v8::Local<v8::Function> &&)) \
  X(CXXDestructor, v8::Local<v8::Function>::~Local, void (v8::Local<v8::Function>::*)()) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, void (v8::Local<v8::Name>::*)()) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, void (v8::Local<v8::Name>::*)(v8::Local<v8::String>)) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, void (v8::Local<v8::Name>::*)(v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Local<v8::Name>::IsEmpty, bool (v8::Local<v8::Name>::*)() const) \
  X(CXXMethod, v8::Local<v8::Name>::Clear, void (v8::Local<v8::Name>::*)()) \
  X(CXXMethod, v8::Local<v8::Name>::operator->, v8::Name *(v8::Local<v8::Name>::*)() const) \
  X(CXXMethod, v8::Local<v8::Name>::operator*, v8::Name *(v8::Local<v8::Name>::*)() const) \
  X(CXXMethod, v8::Local<v8::Name>::New, v8::Local<v8::Name> (*)(v8::Isolate *, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Local<v8::Name>::New, v8::Local<v8::Name> (*)(v8::Isolate *, const v8::PersistentBase<v8::Name> &)) \
  X(CXXMethod, v8::Local<v8::Name>::New, v8::Local<v8::Name> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Name> &)) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, void (v8::Local<v8::Name>::*)(const v8::Local<v8::Name> &)) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, void (v8::Local<v8::Name>::*)(v8::Local<v8::Name> &&)) \
  X(CXXDestructor, v8::Local<v8::Name>::~Local, void (v8::Local<v8::Name>::*)()) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, void (v8::Local<v8::FunctionTemplate>::*)()) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, void (v8::Local<v8::FunctionTemplate>::*)(v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::IsEmpty, bool (v8::Local<v8::FunctionTemplate>::*)() const) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::Clear, void (v8::Local<v8::FunctionTemplate>::*)()) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::operator->, v8::FunctionTemplate *(v8::Local<v8::FunctionTemplate>::*)() const) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::operator*, v8::FunctionTemplate *(v8::Local<v8::FunctionTemplate>::*)() const) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, v8::Local<v8::FunctionTemplate> (*)(v8::Isolate *, v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, v8::Local<v8::FunctionTemplate> (*)(v8::Isolate *, const v8::PersistentBase<v8::FunctionTemplate> &)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, v8::Local<v8::FunctionTemplate> (*)(v8::Isolate *, const v8::TracedGlobal<v8::FunctionTemplate> &)) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, void (v8::Local<v8::FunctionTemplate>::*)(const v8::Local<v8::FunctionTemplate> &)) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, void (v8::Local<v8::FunctionTemplate>::*)(v8::Local<v8::FunctionTemplate> &&)) \
  X(CXXDestructor, v8::Local<v8::FunctionTemplate>::~Local, void (v8::Local<v8::FunctionTemplate>::*)()) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, void (v8::Local<v8::Promise>::*)()) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, void (v8::Local<v8::Promise>::*)(v8::Local<v8::Promise>)) \
  X(CXXMethod, v8::Local<v8::Promise>::IsEmpty, bool (v8::Local<v8::Promise>::*)() const) \
  X(CXXMethod, v8::Local<v8::Promise>::Clear, void (v8::Local<v8::Promise>::*)()) \
  X(CXXMethod, v8::Local<v8::Promise>::operator->, v8::Promise *(v8::Local<v8::Promise>::*)() const) \
  X(CXXMethod, v8::Local<v8::Promise>::operator*, v8::Promise *(v8::Local<v8::Promise>::*)() const) \
  X(CXXMethod, v8::Local<v8::Promise>::New, v8::Local<v8::Promise> (*)(v8::Isolate *, v8::Local<v8::Promise>)) \
  X(CXXMethod, v8::Local<v8::Promise>::New, v8::Local<v8::Promise> (*)(v8::Isolate *, const v8::PersistentBase<v8::Promise> &)) \
  X(CXXMethod, v8::Local<v8::Promise>::New, v8::Local<v8::Promise> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Promise> &)) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, void (v8::Local<v8::Promise>::*)(const v8::Local<v8::Promise> &)) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, void (v8::Local<v8::Promise>::*)(v8::Local<v8::Promise> &&)) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, void (v8::Local<v8::Data>::*)()) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, void (v8::Local<v8::Data>::*)(v8::Local<v8::Data>)) \
  X(CXXMethod, v8::Local<v8::Data>::IsEmpty, bool (v8::Local<v8::Data>::*)() const) \
  X(CXXMethod, v8::Local<v8::Data>::Clear, void (v8::Local<v8::Data>::*)()) \
  X(CXXMethod, v8::Local<v8::Data>::operator->, v8::Data *(v8::Local<v8::Data>::*)() const) \
  X(CXXMethod, v8::Local<v8::Data>::operator*, v8::Data *(v8::Local<v8::Data>::*)() const) \
  X(CXXMethod, v8::Local<v8::Data>::New, v8::Local<v8::Data> (*)(v8::Isolate *, v8::Local<v8::Data>)) \
  X(CXXMethod, v8::Local<v8::Data>::New, v8::Local<v8::Data> (*)(v8::Isolate *, const v8::PersistentBase<v8::Data> &)) \
  X(CXXMethod, v8::Local<v8::Data>::New, v8::Local<v8::Data> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Data> &)) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, void (v8::Local<v8::Data>::*)(const v8::Local<v8::Data> &)) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, void (v8::Local<v8::Data>::*)(v8::Local<v8::Data> &&)) \
  X(CXXDestructor, v8::Local<v8::Data>::~Local, void (v8::Local<v8::Data>::*)()) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, void (v8::Local<v8::AccessorSignature>::*)()) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, void (v8::Local<v8::AccessorSignature>::*)(v8::Local<v8::AccessorSignature>)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::IsEmpty, bool (v8::Local<v8::AccessorSignature>::*)() const) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::Clear, void (v8::Local<v8::AccessorSignature>::*)()) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::operator->, v8::AccessorSignature *(v8::Local<v8::AccessorSignature>::*)() const) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::operator*, v8::AccessorSignature *(v8::Local<v8::AccessorSignature>::*)() const) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, v8::Local<v8::AccessorSignature> (*)(v8::Isolate *, v8::Local<v8::AccessorSignature>)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, v8::Local<v8::AccessorSignature> (*)(v8::Isolate *, const v8::PersistentBase<v8::AccessorSignature> &)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, v8::Local<v8::AccessorSignature> (*)(v8::Isolate *, const v8::TracedGlobal<v8::AccessorSignature> &)) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, void (v8::Local<v8::AccessorSignature>::*)(const v8::Local<v8::AccessorSignature> &)) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, void (v8::Local<v8::AccessorSignature>::*)(v8::Local<v8::AccessorSignature> &&)) \
  X(CXXDestructor, v8::Local<v8::AccessorSignature>::~Local, void (v8::Local<v8::AccessorSignature>::*)()) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, void (v8::Local<v8::Signature>::*)()) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, void (v8::Local<v8::Signature>::*)(v8::Local<v8::Signature>)) \
  X(CXXMethod, v8::Local<v8::Signature>::IsEmpty, bool (v8::Local<v8::Signature>::*)() const) \
  X(CXXMethod, v8::Local<v8::Signature>::Clear, void (v8::Local<v8::Signature>::*)()) \
  X(CXXMethod, v8::Local<v8::Signature>::operator->, v8::Signature *(v8::Local<v8::Signature>::*)() const) \
  X(CXXMethod, v8::Local<v8::Signature>::operator*, v8::Signature *(v8::Local<v8::Signature>::*)() const) \
  X(CXXMethod, v8::Local<v8::Signature>::New, v8::Local<v8::Signature> (*)(v8::Isolate *, v8::Local<v8::Signature>)) \
  X(CXXMethod, v8::Local<v8::Signature>::New, v8::Local<v8::Signature> (*)(v8::Isolate *, const v8::PersistentBase<v8::Signature> &)) \
  X(CXXMethod, v8::Local<v8::Signature>::New, v8::Local<v8::Signature> (*)(v8::Isolate *, const v8::TracedGlobal<v8::Signature> &)) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, void (v8::Local<v8::Signature>::*)(const v8::Local<v8::Signature> &)) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, void (v8::Local<v8::Signature>::*)(v8::Local<v8::Signature> &&)) \
  X(CXXDestructor, v8::Local<v8::Signature>::~Local, void (v8::Local<v8::Signature>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, void (v8::MaybeLocal<v8::Value>::*)()) \
  X(CXXMethod, v8::MaybeLocal<v8::Value>::IsEmpty, bool (v8::MaybeLocal<v8::Value>::*)() const) \
  X(CXXMethod, v8::MaybeLocal<v8::Value>::ToLocalChecked, v8::Local<v8::Value> (v8::MaybeLocal<v8::Value>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, void (v8::MaybeLocal<v8::Value>::*)(const v8::MaybeLocal<v8::Value> &)) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, void (v8::MaybeLocal<v8::Value>::*)(v8::MaybeLocal<v8::Value> &&)) \
  X(CXXDestructor, v8::MaybeLocal<v8::Value>::~MaybeLocal, void (v8::MaybeLocal<v8::Value>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::String>::MaybeLocal, void (v8::MaybeLocal<v8::String>::*)()) \
  X(CXXMethod, v8::MaybeLocal<v8::String>::IsEmpty, bool (v8::MaybeLocal<v8::String>::*)() const) \
  X(CXXMethod, v8::MaybeLocal<v8::String>::ToLocalChecked, v8::Local<v8::String> (v8::MaybeLocal<v8::String>::*)()) \
  X(CXXDestructor, v8::MaybeLocal<v8::String>::~MaybeLocal, void (v8::MaybeLocal<v8::String>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, void (v8::MaybeLocal<v8::Object>::*)()) \
  X(CXXMethod, v8::MaybeLocal<v8::Object>::IsEmpty, bool (v8::MaybeLocal<v8::Object>::*)() const) \
  X(CXXMethod, v8::MaybeLocal<v8::Object>::ToLocalChecked, v8::Local<v8::Object> (v8::MaybeLocal<v8::Object>::*)()) \
  X(CXXDestructor, v8::MaybeLocal<v8::Object>::~MaybeLocal, void (v8::MaybeLocal<v8::Object>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, void (v8::MaybeLocal<v8::Object>::*)(const v8::MaybeLocal<v8::Object> &)) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, void (v8::MaybeLocal<v8::Object>::*)(v8::MaybeLocal<v8::Object> &&)) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, void (v8::MaybeLocal<v8::ObjectTemplate>::*)()) \
  X(CXXMethod, v8::MaybeLocal<v8::ObjectTemplate>::IsEmpty, bool (v8::MaybeLocal<v8::ObjectTemplate>::*)() const) \
  X(CXXMethod, v8::MaybeLocal<v8::ObjectTemplate>::ToLocalChecked, v8::Local<v8::ObjectTemplate> (v8::MaybeLocal<v8::ObjectTemplate>::*)()) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, void (v8::MaybeLocal<v8::ObjectTemplate>::*)(const v8::MaybeLocal<v8::ObjectTemplate> &)) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, void (v8::MaybeLocal<v8::ObjectTemplate>::*)(v8::MaybeLocal<v8::ObjectTemplate> &&)) \
  X(CXXDestructor, v8::MaybeLocal<v8::ObjectTemplate>::~MaybeLocal, void (v8::MaybeLocal<v8::ObjectTemplate>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Reset, void (v8::PersistentBase<v8::Object>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::IsEmpty, bool (v8::PersistentBase<v8::Object>::*)() const) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Empty, void (v8::PersistentBase<v8::Object>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Get, v8::Local<v8::Object> (v8::PersistentBase<v8::Object>::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::SetWeak, void (v8::PersistentBase<v8::Object>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::ClearWeak, void (v8::PersistentBase<v8::Object>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::AnnotateStrongRetainer, void (v8::PersistentBase<v8::Object>::*)(const char *)) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::IsWeak, bool (v8::PersistentBase<v8::Object>::*)() const) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::SetWrapperClassId, void (v8::PersistentBase<v8::Object>::*)(unsigned short)) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::WrapperClassId, unsigned short (v8::PersistentBase<v8::Object>::*)() const) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Reset, void (v8::PersistentBase<v8::Promise>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::IsEmpty, bool (v8::PersistentBase<v8::Promise>::*)() const) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Empty, void (v8::PersistentBase<v8::Promise>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Get, v8::Local<v8::Promise> (v8::PersistentBase<v8::Promise>::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::SetWeak, void (v8::PersistentBase<v8::Promise>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::ClearWeak, void (v8::PersistentBase<v8::Promise>::*)()) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::AnnotateStrongRetainer, void (v8::PersistentBase<v8::Promise>::*)(const char *)) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::IsWeak, bool (v8::PersistentBase<v8::Promise>::*)() const) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::SetWrapperClassId, void (v8::PersistentBase<v8::Promise>::*)(unsigned short)) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::WrapperClassId, unsigned short (v8::PersistentBase<v8::Promise>::*)() const) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, void (v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)()) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, void (v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)(const v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &)) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, void (v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)(const v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &)) \
  X(CXXMethod, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::operator=, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &(v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)(const v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &)) \
  X(CXXMethod, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::operator=, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &(v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)(const v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> > &)) \
  X(CXXDestructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::~Persistent, void (v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::*)()) \
  X(CXXConstructor, v8::TracedGlobal<v8::Object>::TracedGlobal, void (v8::TracedGlobal<v8::Object>::*)()) \
  X(CXXDestructor, v8::TracedGlobal<v8::Object>::~TracedGlobal, void (v8::TracedGlobal<v8::Object>::*)()) \
  X(CXXConstructor, v8::TracedGlobal<v8::Object>::TracedGlobal, void (v8::TracedGlobal<v8::Object>::*)(v8::TracedGlobal<v8::Object> &&)) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::IsEmpty, bool (v8::TracedGlobal<v8::Object>::*)() const) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::Reset, void (v8::TracedGlobal<v8::Object>::*)()) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::Get, v8::Local<v8::Object> (v8::TracedGlobal<v8::Object>::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::SetWrapperClassId, void (v8::TracedGlobal<v8::Object>::*)(unsigned short)) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::WrapperClassId, unsigned short (v8::TracedGlobal<v8::Object>::*)() const) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::SetFinalizationCallback, void (v8::TracedGlobal<v8::Object>::*)(void *, void (*)(const v8::WeakCallbackInfo<void> &))) \
  X(CXXConstructor, v8::WeakCallbackInfo<void>::WeakCallbackInfo, void (v8::WeakCallbackInfo<void>::*)(v8::Isolate *, void *, void **, void (**)(const v8::WeakCallbackInfo<void> &))) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetIsolate, v8::Isolate *(v8::WeakCallbackInfo<void>::*)() const) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetParameter, void *(v8::WeakCallbackInfo<void>::*)() const) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetInternalField, void *(v8::WeakCallbackInfo<void>::*)(int) const) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::SetSecondPassCallback, void (v8::WeakCallbackInfo<void>::*)(void (*)(const v8::WeakCallbackInfo<void> &)) const) \
  X(CXXMethod, v8::NonCopyablePersistentTraits::Uncompilable, void (*)()) \
  X(CXXConstructor, v8::HandleScope::HandleScope, void (v8::HandleScope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::HandleScope::~HandleScope, void (v8::HandleScope::*)()) \
  X(CXXMethod, v8::HandleScope::NumberOfHandles, int (*)(v8::Isolate *)) \
  X(CXXMethod, v8::HandleScope::GetIsolate, v8::Isolate *(v8::HandleScope::*)() const) \
  X(CXXConstructor, v8::EscapableHandleScope::EscapableHandleScope, void (v8::EscapableHandleScope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::EscapableHandleScope::~EscapableHandleScope, void (v8::EscapableHandleScope::*)()) \
  X(CXXConstructor, v8::SealHandleScope::SealHandleScope, void (v8::SealHandleScope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::SealHandleScope::~SealHandleScope, void (v8::SealHandleScope::*)()) \
  X(CXXMethod, v8::ScriptOrModule::GetResourceName, v8::Local<v8::Value> (v8::ScriptOrModule::*)()) \
  X(CXXMethod, v8::ScriptOrModule::GetHostDefinedOptions, v8::Local<v8::PrimitiveArray> (v8::ScriptOrModule::*)()) \
  X(CXXMethod, v8::PrimitiveArray::New, v8::Local<v8::PrimitiveArray> (*)(v8::Isolate *, int)) \
  X(CXXMethod, v8::PrimitiveArray::Length, int (v8::PrimitiveArray::*)() const) \
  X(CXXMethod, v8::PrimitiveArray::Set, void (v8::PrimitiveArray::*)(v8::Isolate *, int, v8::Local<v8::Primitive>)) \
  X(CXXMethod, v8::PrimitiveArray::Get, v8::Local<v8::Primitive> (v8::PrimitiveArray::*)(v8::Isolate *, int)) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, void (v8::ScriptOriginOptions::*)(bool, bool, bool, bool)) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, void (v8::ScriptOriginOptions::*)(int)) \
  X(CXXMethod, v8::ScriptOriginOptions::IsSharedCrossOrigin, bool (v8::ScriptOriginOptions::*)() const) \
  X(CXXMethod, v8::ScriptOriginOptions::IsOpaque, bool (v8::ScriptOriginOptions::*)() const) \
  X(CXXMethod, v8::ScriptOriginOptions::IsWasm, bool (v8::ScriptOriginOptions::*)() const) \
  X(CXXMethod, v8::ScriptOriginOptions::IsModule, bool (v8::ScriptOriginOptions::*)() const) \
  X(CXXMethod, v8::ScriptOriginOptions::Flags, int (v8::ScriptOriginOptions::*)() const) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, void (v8::ScriptOriginOptions::*)(const v8::ScriptOriginOptions &)) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, void (v8::ScriptOriginOptions::*)(v8::ScriptOriginOptions &&)) \
  X(CXXDestructor, v8::ScriptOriginOptions::~ScriptOriginOptions, void (v8::ScriptOriginOptions::*)()) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, void (v8::ScriptOrigin::*)(v8::Local<v8::Value>, v8::Local<v8::Integer>, v8::Local<v8::Integer>, v8::Local<v8::Boolean>, v8::Local<v8::Integer>, v8::Local<v8::Value>, v8::Local<v8::Boolean>, v8::Local<v8::Boolean>, v8::Local<v8::Boolean>, v8::Local<v8::PrimitiveArray>)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceName, v8::Local<v8::Value> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ResourceLineOffset, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ResourceColumnOffset, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ScriptID, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::SourceMapUrl, v8::Local<v8::Value> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::HostDefinedOptions, v8::Local<v8::PrimitiveArray> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::Options, v8::ScriptOriginOptions (v8::ScriptOrigin::*)() const) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, void (v8::ScriptOrigin::*)(const v8::ScriptOrigin &)) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, void (v8::ScriptOrigin::*)(v8::ScriptOrigin &&)) \
  X(CXXMethod, v8::UnboundScript::BindToCurrentContext, v8::Local<v8::Script> (v8::UnboundScript::*)()) \
  X(CXXMethod, v8::UnboundScript::GetId, int (v8::UnboundScript::*)()) \
  X(CXXMethod, v8::UnboundScript::GetScriptName, v8::Local<v8::Value> (v8::UnboundScript::*)()) \
  X(CXXMethod, v8::UnboundScript::GetSourceURL, v8::Local<v8::Value> (v8::UnboundScript::*)()) \
  X(CXXMethod, v8::UnboundScript::GetSourceMappingURL, v8::Local<v8::Value> (v8::UnboundScript::*)()) \
  X(CXXMethod, v8::UnboundScript::GetLineNumber, int (v8::UnboundScript::*)(int)) \
  X(CXXMethod, v8::Location::GetLineNumber, int (v8::Location::*)()) \
  X(CXXMethod, v8::Location::GetColumnNumber, int (v8::Location::*)()) \
  X(CXXConstructor, v8::Location::Location, void (v8::Location::*)(int, int)) \
  X(CXXMethod, v8::Module::GetStatus, v8::Module::Status (v8::Module::*)() const) \
  X(CXXMethod, v8::Module::GetException, v8::Local<v8::Value> (v8::Module::*)() const) \
  X(CXXMethod, v8::Module::GetModuleRequestsLength, int (v8::Module::*)() const) \
  X(CXXMethod, v8::Module::GetModuleRequest, v8::Local<v8::String> (v8::Module::*)(int) const) \
  X(CXXMethod, v8::Module::GetModuleRequestLocation, v8::Location (v8::Module::*)(int) const) \
  X(CXXMethod, v8::Module::GetIdentityHash, int (v8::Module::*)() const) \
  X(CXXMethod, v8::Module::InstantiateModule, v8::Maybe<bool> (v8::Module::*)(v8::Local<v8::Context>, v8::MaybeLocal<v8::Module> (*)(v8::Local<v8::Context>, v8::Local<v8::String>, v8::Local<v8::Module>))) \
  X(CXXMethod, v8::Module::Evaluate, v8::MaybeLocal<v8::Value> (v8::Module::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Module::GetModuleNamespace, v8::Local<v8::Value> (v8::Module::*)()) \
  X(CXXMethod, v8::Module::GetUnboundModuleScript, v8::Local<v8::UnboundModuleScript> (v8::Module::*)()) \
  X(CXXMethod, v8::Script::Compile, v8::MaybeLocal<v8::Script> (*)(v8::Local<v8::Context>, v8::Local<v8::String>, v8::ScriptOrigin *)) \
  X(CXXMethod, v8::Script::Run, v8::MaybeLocal<v8::Value> (v8::Script::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Script::GetUnboundScript, v8::Local<v8::UnboundScript> (v8::Script::*)()) \
  X(CXXConstructor, v8::ScriptCompiler::CachedData::CachedData, void (v8::ScriptCompiler::CachedData::*)()) \
  X(CXXConstructor, v8::ScriptCompiler::CachedData::CachedData, void (v8::ScriptCompiler::CachedData::*)(const unsigned char *, int, v8::ScriptCompiler::CachedData::BufferPolicy)) \
  X(CXXDestructor, v8::ScriptCompiler::CachedData::~CachedData, void (v8::ScriptCompiler::CachedData::*)()) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, void (v8::ScriptCompiler::Source::*)(v8::Local<v8::String>, const v8::ScriptOrigin &, v8::ScriptCompiler::CachedData *)) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, void (v8::ScriptCompiler::Source::*)(v8::Local<v8::String>, v8::ScriptCompiler::CachedData *)) \
  X(CXXDestructor, v8::ScriptCompiler::Source::~Source, void (v8::ScriptCompiler::Source::*)()) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetCachedData, const v8::ScriptCompiler::CachedData *(v8::ScriptCompiler::Source::*)() const) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetResourceOptions, const v8::ScriptOriginOptions &(v8::ScriptCompiler::Source::*)() const) \
  X(CXXDestructor, v8::ScriptCompiler::ExternalSourceStream::~ExternalSourceStream, void (v8::ScriptCompiler::ExternalSourceStream::*)()) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::GetMoreData, unsigned long long (v8::ScriptCompiler::ExternalSourceStream::*)(const unsigned char **)) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::SetBookmark, bool (v8::ScriptCompiler::ExternalSourceStream::*)()) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::ResetToBookmark, void (v8::ScriptCompiler::ExternalSourceStream::*)()) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::operator=, v8::ScriptCompiler::ExternalSourceStream &(v8::ScriptCompiler::ExternalSourceStream::*)(const v8::ScriptCompiler::ExternalSourceStream &)) \
  X(CXXConstructor, v8::ScriptCompiler::StreamedSource::StreamedSource, void (v8::ScriptCompiler::StreamedSource::*)(v8::ScriptCompiler::ExternalSourceStream *, v8::ScriptCompiler::StreamedSource::Encoding)) \
  X(CXXDestructor, v8::ScriptCompiler::StreamedSource::~StreamedSource, void (v8::ScriptCompiler::StreamedSource::*)()) \
  X(CXXMethod, v8::ScriptCompiler::StreamedSource::impl, v8::internal::ScriptStreamingData *(v8::ScriptCompiler::StreamedSource::*)() const) \
  X(CXXMethod, v8::ScriptCompiler::ScriptStreamingTask::Run, void (v8::ScriptCompiler::ScriptStreamingTask::*)()) \
  X(CXXMethod, v8::ScriptCompiler::CompileUnboundScript, v8::MaybeLocal<v8::UnboundScript> (*)(v8::Isolate *, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)) \
  X(CXXMethod, v8::ScriptCompiler::Compile, v8::MaybeLocal<v8::Script> (*)(v8::Local<v8::Context>, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)) \
  X(CXXMethod, v8::ScriptCompiler::StartStreamingScript, v8::ScriptCompiler::ScriptStreamingTask *(*)(v8::Isolate *, v8::ScriptCompiler::StreamedSource *, v8::ScriptCompiler::CompileOptions)) \
  X(CXXMethod, v8::ScriptCompiler::Compile, v8::MaybeLocal<v8::Script> (*)(v8::Local<v8::Context>, v8::ScriptCompiler::StreamedSource *, v8::Local<v8::String>, const v8::ScriptOrigin &)) \
  X(CXXMethod, v8::ScriptCompiler::CachedDataVersionTag, unsigned int (*)()) \
  X(CXXMethod, v8::ScriptCompiler::CompileModule, v8::MaybeLocal<v8::Module> (*)(v8::Isolate *, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)) \
  X(CXXMethod, v8::ScriptCompiler::CompileFunctionInContext, v8::MaybeLocal<v8::Function> (*)(v8::Local<v8::Context>, v8::ScriptCompiler::Source *, unsigned long long, v8::Local<v8::String> *, unsigned long long, v8::Local<v8::Object> *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCache, v8::ScriptCompiler::CachedData *(*)(v8::Local<v8::UnboundScript>)) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCache, v8::ScriptCompiler::CachedData *(*)(v8::Local<v8::UnboundModuleScript>)) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCacheForFunction, v8::ScriptCompiler::CachedData *(*)(v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Message::Get, v8::Local<v8::String> (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetIsolate, v8::Isolate *(v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetSourceLine, v8::MaybeLocal<v8::String> (v8::Message::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Message::GetScriptOrigin, v8::ScriptOrigin (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetScriptResourceName, v8::Local<v8::Value> (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetStackTrace, v8::Local<v8::StackTrace> (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetLineNumber, v8::Maybe<int> (v8::Message::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Message::GetStartPosition, int (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetEndPosition, int (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::ErrorLevel, int (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetStartColumn, int (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetStartColumn, v8::Maybe<int> (v8::Message::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Message::GetEndColumn, int (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::GetEndColumn, v8::Maybe<int> (v8::Message::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Message::IsSharedCrossOrigin, bool (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::IsOpaque, bool (v8::Message::*)() const) \
  X(CXXMethod, v8::Message::PrintCurrentStackTrace, void (*)(v8::Isolate *, _iobuf *)) \
  X(CXXMethod, v8::StackTrace::GetFrame, v8::Local<v8::StackFrame> (v8::StackTrace::*)(v8::Isolate *, unsigned int) const) \
  X(CXXMethod, v8::StackTrace::GetFrameCount, int (v8::StackTrace::*)() const) \
  X(CXXMethod, v8::StackTrace::CurrentStackTrace, v8::Local<v8::StackTrace> (*)(v8::Isolate *, int, v8::StackTrace::StackTraceOptions)) \
  X(CXXMethod, v8::StackFrame::GetLineNumber, int (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::GetColumn, int (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::GetScriptId, int (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::GetScriptName, v8::Local<v8::String> (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::GetScriptNameOrSourceURL, v8::Local<v8::String> (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::GetFunctionName, v8::Local<v8::String> (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::IsEval, bool (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::IsConstructor, bool (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::IsWasm, bool (v8::StackFrame::*)() const) \
  X(CXXMethod, v8::StackFrame::IsUserJavaScript, bool (v8::StackFrame::*)() const) \
  X(CXXConstructor, v8::RegisterState::RegisterState, void (v8::RegisterState::*)()) \
  X(CXXMethod, v8::JSON::Parse, v8::MaybeLocal<v8::Value> (*)(v8::Local<v8::Context>, v8::Local<v8::String>)) \
  X(CXXMethod, v8::JSON::Stringify, v8::MaybeLocal<v8::String> (*)(v8::Local<v8::Context>, v8::Local<v8::Value>, v8::Local<v8::String>)) \
  X(CXXDestructor, v8::ValueSerializer::Delegate::~Delegate, void (v8::ValueSerializer::Delegate::*)()) \
  X(CXXMethod, v8::ValueSerializer::Delegate::ThrowDataCloneError, void (v8::ValueSerializer::Delegate::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::WriteHostObject, v8::Maybe<bool> (v8::ValueSerializer::Delegate::*)(v8::Isolate *, v8::Local<v8::Object>)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::GetSharedArrayBufferId, v8::Maybe<unsigned int> (v8::ValueSerializer::Delegate::*)(v8::Isolate *, v8::Local<v8::SharedArrayBuffer>)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::GetWasmModuleTransferId, v8::Maybe<unsigned int> (v8::ValueSerializer::Delegate::*)(v8::Isolate *, v8::Local<v8::WasmModuleObject>)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::ReallocateBufferMemory, void *(v8::ValueSerializer::Delegate::*)(void *, unsigned long long, unsigned long long *)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::FreeBufferMemory, void (v8::ValueSerializer::Delegate::*)(void *)) \
  X(CXXMethod, v8::ValueSerializer::Delegate::operator=, v8::ValueSerializer::Delegate &(v8::ValueSerializer::Delegate::*)(const v8::ValueSerializer::Delegate &)) \
  X(CXXConstructor, v8::ValueSerializer::ValueSerializer, void (v8::ValueSerializer::*)(v8::Isolate *)) \
  X(CXXConstructor, v8::ValueSerializer::ValueSerializer, void (v8::ValueSerializer::*)(v8::Isolate *, v8::ValueSerializer::Delegate *)) \
  X(CXXDestructor, v8::ValueSerializer::~ValueSerializer, void (v8::ValueSerializer::*)()) \
  X(CXXMethod, v8::ValueSerializer::WriteHeader, void (v8::ValueSerializer::*)()) \
  X(CXXMethod, v8::ValueSerializer::WriteValue, v8::Maybe<bool> (v8::ValueSerializer::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::ValueSerializer::Release, std::pair<unsigned char *, unsigned long long> (v8::ValueSerializer::*)()) \
  X(CXXMethod, v8::ValueSerializer::TransferArrayBuffer, void (v8::ValueSerializer::*)(unsigned int, v8::Local<v8::ArrayBuffer>)) \
  X(CXXMethod, v8::ValueSerializer::SetTreatArrayBufferViewsAsHostObjects, void (v8::ValueSerializer::*)(bool)) \
  X(CXXMethod, v8::ValueSerializer::WriteUint32, void (v8::ValueSerializer::*)(unsigned int)) \
  X(CXXMethod, v8::ValueSerializer::WriteUint64, void (v8::ValueSerializer::*)(unsigned long long)) \
  X(CXXMethod, v8::ValueSerializer::WriteDouble, void (v8::ValueSerializer::*)(double)) \
  X(CXXMethod, v8::ValueSerializer::WriteRawBytes, void (v8::ValueSerializer::*)(const void *, unsigned long long)) \
  X(CXXDestructor, v8::ValueDeserializer::Delegate::~Delegate, void (v8::ValueDeserializer::Delegate::*)()) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::ReadHostObject, v8::MaybeLocal<v8::Object> (v8::ValueDeserializer::Delegate::*)(v8::Isolate *)) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::GetWasmModuleFromId, v8::MaybeLocal<v8::WasmModuleObject> (v8::ValueDeserializer::Delegate::*)(v8::Isolate *, unsigned int)) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::GetSharedArrayBufferFromId, v8::MaybeLocal<v8::SharedArrayBuffer> (v8::ValueDeserializer::Delegate::*)(v8::Isolate *, unsigned int)) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::operator=, v8::ValueDeserializer::Delegate &(v8::ValueDeserializer::Delegate::*)(const v8::ValueDeserializer::Delegate &)) \
  X(CXXConstructor, v8::ValueDeserializer::ValueDeserializer, void (v8::ValueDeserializer::*)(v8::Isolate *, const unsigned char *, unsigned long long)) \
  X(CXXConstructor, v8::ValueDeserializer::ValueDeserializer, void (v8::ValueDeserializer::*)(v8::Isolate *, const unsigned char *, unsigned long long, v8::ValueDeserializer::Delegate *)) \
  X(CXXDestructor, v8::ValueDeserializer::~ValueDeserializer, void (v8::ValueDeserializer::*)()) \
  X(CXXMethod, v8::ValueDeserializer::ReadHeader, v8::Maybe<bool> (v8::ValueDeserializer::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::ValueDeserializer::ReadValue, v8::MaybeLocal<v8::Value> (v8::ValueDeserializer::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::ValueDeserializer::TransferArrayBuffer, void (v8::ValueDeserializer::*)(unsigned int, v8::Local<v8::ArrayBuffer>)) \
  X(CXXMethod, v8::ValueDeserializer::TransferSharedArrayBuffer, void (v8::ValueDeserializer::*)(unsigned int, v8::Local<v8::SharedArrayBuffer>)) \
  X(CXXMethod, v8::ValueDeserializer::SetSupportsLegacyWireFormat, void (v8::ValueDeserializer::*)(bool)) \
  X(CXXMethod, v8::ValueDeserializer::SetExpectInlineWasm, void (v8::ValueDeserializer::*)(bool)) \
  X(CXXMethod, v8::ValueDeserializer::GetWireFormatVersion, unsigned int (v8::ValueDeserializer::*)() const) \
  X(CXXMethod, v8::ValueDeserializer::ReadUint32, bool (v8::ValueDeserializer::*)(unsigned int *)) \
  X(CXXMethod, v8::ValueDeserializer::ReadUint64, bool (v8::ValueDeserializer::*)(unsigned long long *)) \
  X(CXXMethod, v8::ValueDeserializer::ReadDouble, bool (v8::ValueDeserializer::*)(double *)) \
  X(CXXMethod, v8::ValueDeserializer::ReadRawBytes, bool (v8::ValueDeserializer::*)(unsigned long long, const void **)) \
  X(CXXMethod, v8::Value::IsUndefined, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNull, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNullOrUndefined, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsTrue, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsFalse, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsName, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsString, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsSymbol, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsFunction, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsArray, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBigInt, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBoolean, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNumber, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsExternal, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsInt32, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsUint32, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsDate, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsArgumentsObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBigIntObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBooleanObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNumberObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsStringObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsSymbolObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNativeError, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsRegExp, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsAsyncFunction, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsGeneratorFunction, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsGeneratorObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsPromise, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsMap, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsSet, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsMapIterator, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsSetIterator, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsWeakMap, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsWeakSet, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsArrayBuffer, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsArrayBufferView, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsTypedArray, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsUint8Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsUint8ClampedArray, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsInt8Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsUint16Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsInt16Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsUint32Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsInt32Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsFloat32Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsFloat64Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBigInt64Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsBigUint64Array, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsDataView, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsSharedArrayBuffer, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsProxy, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsWebAssemblyCompiledModule, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsModuleNamespaceObject, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::ToBigInt, v8::MaybeLocal<v8::BigInt> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToNumber, v8::MaybeLocal<v8::Number> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToString, v8::MaybeLocal<v8::String> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToDetailString, v8::MaybeLocal<v8::String> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToObject, v8::MaybeLocal<v8::Object> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToInteger, v8::MaybeLocal<v8::Integer> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToUint32, v8::MaybeLocal<v8::Uint32> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToInt32, v8::MaybeLocal<v8::Int32> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::ToBoolean, v8::Local<v8::Boolean> (v8::Value::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::Value::ToArrayIndex, v8::MaybeLocal<v8::Uint32> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::BooleanValue, bool (v8::Value::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::Value::NumberValue, v8::Maybe<double> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::IntegerValue, v8::Maybe<long long> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::Uint32Value, v8::Maybe<unsigned int> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::Int32Value, v8::Maybe<int> (v8::Value::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Value::Equals, v8::Maybe<bool> (v8::Value::*)(v8::Local<v8::Context>, v8::Local<v8::Value>) const) \
  X(CXXMethod, v8::Value::StrictEquals, bool (v8::Value::*)(v8::Local<v8::Value>) const) \
  X(CXXMethod, v8::Value::SameValue, bool (v8::Value::*)(v8::Local<v8::Value>) const) \
  X(CXXMethod, v8::Value::TypeOf, v8::Local<v8::String> (v8::Value::*)(v8::Isolate *)) \
  X(CXXMethod, v8::Value::InstanceOf, v8::Maybe<bool> (v8::Value::*)(v8::Local<v8::Context>, v8::Local<v8::Object>)) \
  X(CXXMethod, v8::Boolean::Value, bool (v8::Boolean::*)() const) \
  X(CXXMethod, v8::Boolean::Cast, v8::Boolean *(*)(v8::Value *)) \
  X(CXXMethod, v8::Boolean::New, v8::Local<v8::Boolean> (*)(v8::Isolate *, bool)) \
  X(CXXMethod, v8::Name::GetIdentityHash, int (v8::Name::*)()) \
  X(CXXMethod, v8::Name::Cast, v8::Name *(*)(v8::Value *)) \
  X(CXXMethod, v8::String::Length, int (v8::String::*)() const) \
  X(CXXMethod, v8::String::Utf8Length, int (v8::String::*)(v8::Isolate *) const) \
  X(CXXMethod, v8::String::IsOneByte, bool (v8::String::*)() const) \
  X(CXXMethod, v8::String::ContainsOnlyOneByte, bool (v8::String::*)() const) \
  X(CXXMethod, v8::String::Write, int (v8::String::*)(v8::Isolate *, unsigned short *, int, int, int) const) \
  X(CXXMethod, v8::String::WriteOneByte, int (v8::String::*)(v8::Isolate *, unsigned char *, int, int, int) const) \
  X(CXXMethod, v8::String::WriteUtf8, int (v8::String::*)(v8::Isolate *, char *, int, int *, int) const) \
  X(CXXMethod, v8::String::Empty, v8::Local<v8::String> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::String::IsExternal, bool (v8::String::*)() const) \
  X(CXXMethod, v8::String::IsExternalOneByte, bool (v8::String::*)() const) \
  X(CXXDestructor, v8::String::ExternalStringResourceBase::~ExternalStringResourceBase, void (v8::String::ExternalStringResourceBase::*)()) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::IsCacheable, bool (v8::String::ExternalStringResourceBase::*)() const) \
  X(CXXConstructor, v8::String::ExternalStringResourceBase::ExternalStringResourceBase, void (v8::String::ExternalStringResourceBase::*)()) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Dispose, void (v8::String::ExternalStringResourceBase::*)()) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Lock, void (v8::String::ExternalStringResourceBase::*)() const) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Unlock, void (v8::String::ExternalStringResourceBase::*)() const) \
  X(CXXDestructor, v8::String::ExternalStringResource::~ExternalStringResource, void (v8::String::ExternalStringResource::*)()) \
  X(CXXMethod, v8::String::ExternalStringResource::data, const unsigned short *(v8::String::ExternalStringResource::*)() const) \
  X(CXXMethod, v8::String::ExternalStringResource::length, unsigned long long (v8::String::ExternalStringResource::*)() const) \
  X(CXXConstructor, v8::String::ExternalStringResource::ExternalStringResource, void (v8::String::ExternalStringResource::*)()) \
  X(CXXDestructor, v8::String::ExternalOneByteStringResource::~ExternalOneByteStringResource, void (v8::String::ExternalOneByteStringResource::*)()) \
  X(CXXMethod, v8::String::ExternalOneByteStringResource::data, const char *(v8::String::ExternalOneByteStringResource::*)() const) \
  X(CXXMethod, v8::String::ExternalOneByteStringResource::length, unsigned long long (v8::String::ExternalOneByteStringResource::*)() const) \
  X(CXXConstructor, v8::String::ExternalOneByteStringResource::ExternalOneByteStringResource, void (v8::String::ExternalOneByteStringResource::*)()) \
  X(CXXMethod, v8::String::GetExternalStringResourceBase, v8::String::ExternalStringResourceBase *(v8::String::*)(v8::String::Encoding *) const) \
  X(CXXMethod, v8::String::GetExternalStringResource, v8::String::ExternalStringResource *(v8::String::*)() const) \
  X(CXXMethod, v8::String::GetExternalOneByteStringResource, const v8::String::ExternalOneByteStringResource *(v8::String::*)() const) \
  X(CXXMethod, v8::String::Cast, v8::String *(*)(v8::Value *)) \
  X(CXXMethod, v8::String::NewFromUtf8, v8::MaybeLocal<v8::String> (*)(v8::Isolate *, const char *, v8::NewStringType, int)) \
  X(CXXMethod, v8::String::NewFromOneByte, v8::MaybeLocal<v8::String> (*)(v8::Isolate *, const unsigned char *, v8::NewStringType, int)) \
  X(CXXMethod, v8::String::NewFromTwoByte, v8::MaybeLocal<v8::String> (*)(v8::Isolate *, const unsigned short *, v8::NewStringType, int)) \
  X(CXXMethod, v8::String::Concat, v8::Local<v8::String> (*)(v8::Isolate *, v8::Local<v8::String>, v8::Local<v8::String>)) \
  X(CXXMethod, v8::String::NewExternalTwoByte, v8::MaybeLocal<v8::String> (*)(v8::Isolate *, v8::String::ExternalStringResource *)) \
  X(CXXMethod, v8::String::MakeExternal, bool (v8::String::*)(v8::String::ExternalStringResource *)) \
  X(CXXMethod, v8::String::NewExternalOneByte, v8::MaybeLocal<v8::String> (*)(v8::Isolate *, v8::String::ExternalOneByteStringResource *)) \
  X(CXXMethod, v8::String::MakeExternal, bool (v8::String::*)(v8::String::ExternalOneByteStringResource *)) \
  X(CXXMethod, v8::String::CanMakeExternal, bool (v8::String::*)()) \
  X(CXXMethod, v8::String::StringEquals, bool (v8::String::*)(v8::Local<v8::String>)) \
  X(CXXConstructor, v8::String::Utf8Value::Utf8Value, void (v8::String::Utf8Value::*)(v8::Isolate *, v8::Local<v8::Value>)) \
  X(CXXDestructor, v8::String::Utf8Value::~Utf8Value, void (v8::String::Utf8Value::*)()) \
  X(CXXMethod, v8::String::Utf8Value::operator*, char *(v8::String::Utf8Value::*)()) \
  X(CXXMethod, v8::String::Utf8Value::operator*, const char *(v8::String::Utf8Value::*)() const) \
  X(CXXMethod, v8::String::Utf8Value::length, int (v8::String::Utf8Value::*)() const) \
  X(CXXConstructor, v8::String::Value::Value, void (v8::String::Value::*)(v8::Isolate *, v8::Local<v8::Value>)) \
  X(CXXDestructor, v8::String::Value::~Value, void (v8::String::Value::*)()) \
  X(CXXMethod, v8::String::Value::operator*, unsigned short *(v8::String::Value::*)()) \
  X(CXXMethod, v8::String::Value::operator*, const unsigned short *(v8::String::Value::*)() const) \
  X(CXXMethod, v8::String::Value::length, int (v8::String::Value::*)() const) \
  X(CXXMethod, v8::Symbol::Name, v8::Local<v8::Value> (v8::Symbol::*)() const) \
  X(CXXMethod, v8::Symbol::New, v8::Local<v8::Symbol> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Symbol::For, v8::Local<v8::Symbol> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Symbol::ForApi, v8::Local<v8::Symbol> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Symbol::GetAsyncIterator, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetHasInstance, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetIsConcatSpreadable, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetIterator, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetMatch, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetReplace, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetSearch, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetSplit, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetToPrimitive, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetToStringTag, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::GetUnscopables, v8::Local<v8::Symbol> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Symbol::Cast, v8::Symbol *(*)(v8::Value *)) \
  X(CXXMethod, v8::Private::Name, v8::Local<v8::Value> (v8::Private::*)() const) \
  X(CXXMethod, v8::Private::New, v8::Local<v8::Private> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Private::ForApi, v8::Local<v8::Private> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Private::Cast, v8::Private *(*)(v8::Data *)) \
  X(CXXMethod, v8::Number::Value, double (v8::Number::*)() const) \
  X(CXXMethod, v8::Number::New, v8::Local<v8::Number> (*)(v8::Isolate *, double)) \
  X(CXXMethod, v8::Number::Cast, v8::Number *(*)(v8::Value *)) \
  X(CXXMethod, v8::Integer::New, v8::Local<v8::Integer> (*)(v8::Isolate *, int)) \
  X(CXXMethod, v8::Integer::NewFromUnsigned, v8::Local<v8::Integer> (*)(v8::Isolate *, unsigned int)) \
  X(CXXMethod, v8::Integer::Value, long long (v8::Integer::*)() const) \
  X(CXXMethod, v8::Integer::Cast, v8::Integer *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int32::Value, int (v8::Int32::*)() const) \
  X(CXXMethod, v8::Int32::Cast, v8::Int32 *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint32::Value, unsigned int (v8::Uint32::*)() const) \
  X(CXXMethod, v8::Uint32::Cast, v8::Uint32 *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigInt::New, v8::Local<v8::BigInt> (*)(v8::Isolate *, long long)) \
  X(CXXMethod, v8::BigInt::NewFromUnsigned, v8::Local<v8::BigInt> (*)(v8::Isolate *, unsigned long long)) \
  X(CXXMethod, v8::BigInt::NewFromWords, v8::MaybeLocal<v8::BigInt> (*)(v8::Local<v8::Context>, int, int, const unsigned long long *)) \
  X(CXXMethod, v8::BigInt::Uint64Value, unsigned long long (v8::BigInt::*)(bool *) const) \
  X(CXXMethod, v8::BigInt::Int64Value, long long (v8::BigInt::*)(bool *) const) \
  X(CXXMethod, v8::BigInt::WordCount, int (v8::BigInt::*)() const) \
  X(CXXMethod, v8::BigInt::ToWordsArray, void (v8::BigInt::*)(int *, int *, unsigned long long *) const) \
  X(CXXMethod, v8::BigInt::Cast, v8::BigInt *(*)(v8::Value *)) \
  X(CXXMethod, v8::Object::Set, bool (v8::Object::*)(v8::Local<v8::Value>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Set, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Set, bool (v8::Object::*)(unsigned int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Set, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::CreateDataProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::CreateDataProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::DefineOwnProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, v8::Local<v8::Value>, v8::PropertyAttribute)) \
  X(CXXMethod, v8::Object::DefineProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, v8::PropertyDescriptor &)) \
  X(CXXMethod, v8::Object::Get, v8::Local<v8::Value> (v8::Object::*)(v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Get, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Get, v8::Local<v8::Value> (v8::Object::*)(unsigned int)) \
  X(CXXMethod, v8::Object::Get, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, unsigned int)) \
  X(CXXMethod, v8::Object::GetPropertyAttributes, v8::Maybe<v8::PropertyAttribute> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::GetOwnPropertyDescriptor, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::Has, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Delete, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::Has, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int)) \
  X(CXXMethod, v8::Object::Delete, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int)) \
  X(CXXMethod, v8::Object::SetAccessor, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::MaybeLocal<v8::Value>, v8::AccessControl, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Object::SetAccessorProperty, void (v8::Object::*)(v8::Local<v8::Name>, v8::Local<v8::Function>, v8::Local<v8::Function>, v8::PropertyAttribute, v8::AccessControl)) \
  X(CXXMethod, v8::Object::SetNativeDataProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Object::SetLazyDataProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Object::HasPrivate, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Private>)) \
  X(CXXMethod, v8::Object::SetPrivate, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Private>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::DeletePrivate, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Private>)) \
  X(CXXMethod, v8::Object::GetPrivate, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Private>)) \
  X(CXXMethod, v8::Object::GetPropertyNames, v8::MaybeLocal<v8::Array> (v8::Object::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Object::GetPropertyNames, v8::MaybeLocal<v8::Array> (v8::Object::*)(v8::Local<v8::Context>, v8::KeyCollectionMode, v8::PropertyFilter, v8::IndexFilter, v8::KeyConversionMode)) \
  X(CXXMethod, v8::Object::GetOwnPropertyNames, v8::MaybeLocal<v8::Array> (v8::Object::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Object::GetOwnPropertyNames, v8::MaybeLocal<v8::Array> (v8::Object::*)(v8::Local<v8::Context>, v8::PropertyFilter, v8::KeyConversionMode)) \
  X(CXXMethod, v8::Object::GetPrototype, v8::Local<v8::Value> (v8::Object::*)()) \
  X(CXXMethod, v8::Object::SetPrototype, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::FindInstanceInPrototypeChain, v8::Local<v8::Object> (v8::Object::*)(v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::Object::ObjectProtoToString, v8::MaybeLocal<v8::String> (v8::Object::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Object::GetConstructorName, v8::Local<v8::String> (v8::Object::*)()) \
  X(CXXMethod, v8::Object::SetIntegrityLevel, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::IntegrityLevel)) \
  X(CXXMethod, v8::Object::InternalFieldCount, int (v8::Object::*)()) \
  X(CXXMethod, v8::Object::InternalFieldCount, int (*)(const v8::PersistentBase<v8::Object> &)) \
  X(CXXMethod, v8::Object::InternalFieldCount, int (*)(const v8::TracedGlobal<v8::Object> &)) \
  X(CXXMethod, v8::Object::GetInternalField, v8::Local<v8::Value> (v8::Object::*)(int)) \
  X(CXXMethod, v8::Object::SetInternalField, void (v8::Object::*)(int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, void *(v8::Object::*)(int)) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, void *(*)(const v8::PersistentBase<v8::Object> &, int)) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, void *(*)(const v8::TracedGlobal<v8::Object> &, int)) \
  X(CXXMethod, v8::Object::SetAlignedPointerInInternalField, void (v8::Object::*)(int, void *)) \
  X(CXXMethod, v8::Object::SetAlignedPointerInInternalFields, void (v8::Object::*)(int, int *, void **)) \
  X(CXXMethod, v8::Object::HasOwnProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::HasOwnProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int)) \
  X(CXXMethod, v8::Object::HasRealNamedProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::HasRealIndexedProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, unsigned int)) \
  X(CXXMethod, v8::Object::HasRealNamedCallbackProperty, v8::Maybe<bool> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyInPrototypeChain, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyAttributesInPrototypeChain, v8::Maybe<v8::PropertyAttribute> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::GetRealNamedProperty, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyAttributes, v8::Maybe<v8::PropertyAttribute> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Name>)) \
  X(CXXMethod, v8::Object::HasNamedLookupInterceptor, bool (v8::Object::*)()) \
  X(CXXMethod, v8::Object::HasIndexedLookupInterceptor, bool (v8::Object::*)()) \
  X(CXXMethod, v8::Object::GetIdentityHash, int (v8::Object::*)()) \
  X(CXXMethod, v8::Object::Clone, v8::Local<v8::Object> (v8::Object::*)()) \
  X(CXXMethod, v8::Object::CreationContext, v8::Local<v8::Context> (v8::Object::*)()) \
  X(CXXMethod, v8::Object::CreationContext, v8::Local<v8::Context> (*)(const v8::PersistentBase<v8::Object> &)) \
  X(CXXMethod, v8::Object::IsCallable, bool (v8::Object::*)()) \
  X(CXXMethod, v8::Object::IsConstructor, bool (v8::Object::*)()) \
  X(CXXMethod, v8::Object::CallAsFunction, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, v8::Local<v8::Value>, int, v8::Local<v8::Value> *)) \
  X(CXXMethod, v8::Object::CallAsConstructor, v8::MaybeLocal<v8::Value> (v8::Object::*)(v8::Local<v8::Context>, int, v8::Local<v8::Value> *)) \
  X(CXXMethod, v8::Object::GetIsolate, v8::Isolate *(v8::Object::*)()) \
  X(CXXMethod, v8::Object::PreviewEntries, v8::MaybeLocal<v8::Array> (v8::Object::*)(bool *)) \
  X(CXXMethod, v8::Object::New, v8::Local<v8::Object> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Object::New, v8::Local<v8::Object> (*)(v8::Isolate *, v8::Local<v8::Value>, v8::Local<v8::Name> *, v8::Local<v8::Value> *, unsigned long long)) \
  X(CXXMethod, v8::Object::Cast, v8::Object *(*)(v8::Value *)) \
  X(CXXMethod, v8::Array::Length, unsigned int (v8::Array::*)() const) \
  X(CXXMethod, v8::Array::New, v8::Local<v8::Array> (*)(v8::Isolate *, int)) \
  X(CXXMethod, v8::Array::New, v8::Local<v8::Array> (*)(v8::Isolate *, v8::Local<v8::Value> *, unsigned long long)) \
  X(CXXMethod, v8::Array::Cast, v8::Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Map::Size, unsigned long long (v8::Map::*)() const) \
  X(CXXMethod, v8::Map::Clear, void (v8::Map::*)()) \
  X(CXXMethod, v8::Map::Get, v8::MaybeLocal<v8::Value> (v8::Map::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Map::Set, v8::MaybeLocal<v8::Map> (v8::Map::*)(v8::Local<v8::Context>, v8::Local<v8::Value>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Map::Has, v8::Maybe<bool> (v8::Map::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Map::Delete, v8::Maybe<bool> (v8::Map::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Map::AsArray, v8::Local<v8::Array> (v8::Map::*)() const) \
  X(CXXMethod, v8::Map::New, v8::Local<v8::Map> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Map::Cast, v8::Map *(*)(v8::Value *)) \
  X(CXXMethod, v8::Set::Size, unsigned long long (v8::Set::*)() const) \
  X(CXXMethod, v8::Set::Clear, void (v8::Set::*)()) \
  X(CXXMethod, v8::Set::Add, v8::MaybeLocal<v8::Set> (v8::Set::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Set::Has, v8::Maybe<bool> (v8::Set::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Set::Delete, v8::Maybe<bool> (v8::Set::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Set::AsArray, v8::Local<v8::Array> (v8::Set::*)() const) \
  X(CXXMethod, v8::Set::New, v8::Local<v8::Set> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Set::Cast, v8::Set *(*)(v8::Value *)) \
  X(CXXMethod, v8::Function::New, v8::MaybeLocal<v8::Function> (*)(v8::Local<v8::Context>, void (*)(const v8::FunctionCallbackInfo<v8::Value> &), v8::Local<v8::Value>, int, v8::ConstructorBehavior, v8::SideEffectType)) \
  X(CXXMethod, v8::Function::NewInstance, v8::MaybeLocal<v8::Object> (v8::Function::*)(v8::Local<v8::Context>, int, v8::Local<v8::Value> *) const) \
  X(CXXMethod, v8::Function::NewInstance, v8::MaybeLocal<v8::Object> (v8::Function::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::Function::NewInstanceWithSideEffectType, v8::MaybeLocal<v8::Object> (v8::Function::*)(v8::Local<v8::Context>, int, v8::Local<v8::Value> *, v8::SideEffectType) const) \
  X(CXXMethod, v8::Function::Call, v8::MaybeLocal<v8::Value> (v8::Function::*)(v8::Local<v8::Context>, v8::Local<v8::Value>, int, v8::Local<v8::Value> *)) \
  X(CXXMethod, v8::Function::SetName, void (v8::Function::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Function::GetName, v8::Local<v8::Value> (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetInferredName, v8::Local<v8::Value> (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetDebugName, v8::Local<v8::Value> (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetDisplayName, v8::Local<v8::Value> (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetScriptLineNumber, int (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetScriptColumnNumber, int (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::ScriptId, int (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetBoundFunction, v8::Local<v8::Value> (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::GetScriptOrigin, v8::ScriptOrigin (v8::Function::*)() const) \
  X(CXXMethod, v8::Function::Cast, v8::Function *(*)(v8::Value *)) \
  X(CXXMethod, v8::Promise::Resolver::New, v8::MaybeLocal<v8::Promise::Resolver> (*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::Promise::Resolver::GetPromise, v8::Local<v8::Promise> (v8::Promise::Resolver::*)()) \
  X(CXXMethod, v8::Promise::Resolver::Resolve, v8::Maybe<bool> (v8::Promise::Resolver::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Promise::Resolver::Reject, v8::Maybe<bool> (v8::Promise::Resolver::*)(v8::Local<v8::Context>, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Promise::Resolver::Cast, v8::Promise::Resolver *(*)(v8::Value *)) \
  X(CXXMethod, v8::Promise::Catch, v8::MaybeLocal<v8::Promise> (v8::Promise::*)(v8::Local<v8::Context>, v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Promise::Then, v8::MaybeLocal<v8::Promise> (v8::Promise::*)(v8::Local<v8::Context>, v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Promise::Then, v8::MaybeLocal<v8::Promise> (v8::Promise::*)(v8::Local<v8::Context>, v8::Local<v8::Function>, v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Promise::HasHandler, bool (v8::Promise::*)()) \
  X(CXXMethod, v8::Promise::Result, v8::Local<v8::Value> (v8::Promise::*)()) \
  X(CXXMethod, v8::Promise::State, v8::Promise::PromiseState (v8::Promise::*)()) \
  X(CXXMethod, v8::Promise::MarkAsHandled, void (v8::Promise::*)()) \
  X(CXXMethod, v8::Promise::Cast, v8::Promise *(*)(v8::Value *)) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, void (v8::PropertyDescriptor::*)()) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, void (v8::PropertyDescriptor::*)(v8::Local<v8::Value>)) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, void (v8::PropertyDescriptor::*)(v8::Local<v8::Value>, bool)) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, void (v8::PropertyDescriptor::*)(v8::Local<v8::Value>, v8::Local<v8::Value>)) \
  X(CXXDestructor, v8::PropertyDescriptor::~PropertyDescriptor, void (v8::PropertyDescriptor::*)()) \
  X(CXXMethod, v8::PropertyDescriptor::value, v8::Local<v8::Value> (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_value, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::get, v8::Local<v8::Value> (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_get, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::set, v8::Local<v8::Value> (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_set, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::set_enumerable, void (v8::PropertyDescriptor::*)(bool)) \
  X(CXXMethod, v8::PropertyDescriptor::enumerable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_enumerable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::set_configurable, void (v8::PropertyDescriptor::*)(bool)) \
  X(CXXMethod, v8::PropertyDescriptor::configurable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_configurable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::writable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::has_writable, bool (v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::PropertyDescriptor::get_private, v8::PropertyDescriptor::PrivateData *(v8::PropertyDescriptor::*)() const) \
  X(CXXMethod, v8::Proxy::GetTarget, v8::Local<v8::Value> (v8::Proxy::*)()) \
  X(CXXMethod, v8::Proxy::GetHandler, v8::Local<v8::Value> (v8::Proxy::*)()) \
  X(CXXMethod, v8::Proxy::IsRevoked, bool (v8::Proxy::*)()) \
  X(CXXMethod, v8::Proxy::Revoke, void (v8::Proxy::*)()) \
  X(CXXMethod, v8::Proxy::New, v8::MaybeLocal<v8::Proxy> (*)(v8::Local<v8::Context>, v8::Local<v8::Object>, v8::Local<v8::Object>)) \
  X(CXXMethod, v8::Proxy::Cast, v8::Proxy *(*)(v8::Value *)) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, void (v8::MemorySpan<const unsigned char>::*)()) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, void (v8::MemorySpan<const unsigned char>::*)(const unsigned char *, unsigned long long)) \
  X(CXXMethod, v8::MemorySpan<const unsigned char>::data, const unsigned char *(v8::MemorySpan<const unsigned char>::*)() const) \
  X(CXXMethod, v8::MemorySpan<const unsigned char>::size, unsigned long long (v8::MemorySpan<const unsigned char>::*)() const) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, void (v8::MemorySpan<const unsigned char>::*)(const v8::MemorySpan<const unsigned char> &)) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, void (v8::MemorySpan<const unsigned char>::*)(v8::MemorySpan<const unsigned char> &&)) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, void (v8::OwnedBuffer::*)()) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, void (v8::OwnedBuffer::*)(v8::OwnedBuffer &&)) \
  X(CXXMethod, v8::OwnedBuffer::operator=, v8::OwnedBuffer &(v8::OwnedBuffer::*)(v8::OwnedBuffer &&)) \
  X(CXXDestructor, v8::OwnedBuffer::~OwnedBuffer, void (v8::OwnedBuffer::*)()) \
  X(CXXMethod, v8::CompiledWasmModule::Serialize, v8::OwnedBuffer (v8::CompiledWasmModule::*)()) \
  X(CXXMethod, v8::CompiledWasmModule::GetWireBytesRef, v8::MemorySpan<const unsigned char> (v8::CompiledWasmModule::*)()) \
  X(CXXConstructor, v8::CompiledWasmModule::CompiledWasmModule, void (v8::CompiledWasmModule::*)(const v8::CompiledWasmModule &)) \
  X(CXXConstructor, v8::CompiledWasmModule::CompiledWasmModule, void (v8::CompiledWasmModule::*)(v8::CompiledWasmModule &&)) \
  X(CXXDestructor, v8::CompiledWasmModule::~CompiledWasmModule, void (v8::CompiledWasmModule::*)()) \
  X(CXXConstructor, v8::WasmModuleObject::TransferrableModule::TransferrableModule, void (v8::WasmModuleObject::TransferrableModule::*)(v8::WasmModuleObject::TransferrableModule &&)) \
  X(CXXMethod, v8::WasmModuleObject::TransferrableModule::operator=, v8::WasmModuleObject::TransferrableModule &(v8::WasmModuleObject::TransferrableModule::*)(v8::WasmModuleObject::TransferrableModule &&)) \
  X(CXXDestructor, v8::WasmModuleObject::TransferrableModule::~TransferrableModule, void (v8::WasmModuleObject::TransferrableModule::*)()) \
  X(CXXMethod, v8::WasmModuleObject::GetTransferrableModule, v8::WasmModuleObject::TransferrableModule (v8::WasmModuleObject::*)()) \
  X(CXXMethod, v8::WasmModuleObject::FromTransferrableModule, v8::MaybeLocal<v8::WasmModuleObject> (*)(v8::Isolate *, const v8::WasmModuleObject::TransferrableModule &)) \
  X(CXXMethod, v8::WasmModuleObject::GetCompiledModule, v8::CompiledWasmModule (v8::WasmModuleObject::*)()) \
  X(CXXMethod, v8::WasmModuleObject::DeserializeOrCompile, v8::MaybeLocal<v8::WasmModuleObject> (*)(v8::Isolate *, v8::MemorySpan<const unsigned char>, v8::MemorySpan<const unsigned char>)) \
  X(CXXMethod, v8::WasmModuleObject::Cast, v8::WasmModuleObject *(*)(v8::Value *)) \
  X(CXXDestructor, v8::WasmStreaming::Client::~Client, void (v8::WasmStreaming::Client::*)()) \
  X(CXXMethod, v8::WasmStreaming::Client::OnModuleCompiled, void (v8::WasmStreaming::Client::*)(v8::CompiledWasmModule)) \
  X(CXXMethod, v8::WasmStreaming::Client::operator=, v8::WasmStreaming::Client &(v8::WasmStreaming::Client::*)(const v8::WasmStreaming::Client &)) \
  X(CXXDestructor, v8::WasmStreaming::~WasmStreaming, void (v8::WasmStreaming::*)()) \
  X(CXXMethod, v8::WasmStreaming::OnBytesReceived, void (v8::WasmStreaming::*)(const unsigned char *, unsigned long long)) \
  X(CXXMethod, v8::WasmStreaming::Finish, void (v8::WasmStreaming::*)()) \
  X(CXXMethod, v8::WasmStreaming::Abort, void (v8::WasmStreaming::*)(v8::MaybeLocal<v8::Value>)) \
  X(CXXMethod, v8::WasmStreaming::SetCompiledModuleBytes, bool (v8::WasmStreaming::*)(const unsigned char *, unsigned long long)) \
  X(CXXMethod, v8::WasmStreaming::SetClient, void (v8::WasmStreaming::*)(std::shared_ptr<v8::WasmStreaming::Client>)) \
  X(CXXMethod, v8::WasmStreaming::Unpack, std::shared_ptr<v8::WasmStreaming> (*)(v8::Isolate *, v8::Local<v8::Value>)) \
  X(CXXConstructor, v8::WasmModuleObjectBuilderStreaming::WasmModuleObjectBuilderStreaming, void (v8::WasmModuleObjectBuilderStreaming::*)(v8::Isolate *)) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::OnBytesReceived, void (v8::WasmModuleObjectBuilderStreaming::*)(const unsigned char *, unsigned long long)) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::Finish, void (v8::WasmModuleObjectBuilderStreaming::*)()) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::Abort, void (v8::WasmModuleObjectBuilderStreaming::*)(v8::MaybeLocal<v8::Value>)) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::GetPromise, v8::Local<v8::Promise> (v8::WasmModuleObjectBuilderStreaming::*)()) \
  X(CXXDestructor, v8::WasmModuleObjectBuilderStreaming::~WasmModuleObjectBuilderStreaming, void (v8::WasmModuleObjectBuilderStreaming::*)()) \
  X(CXXDestructor, v8::ArrayBuffer::Allocator::~Allocator, void (v8::ArrayBuffer::Allocator::*)()) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::Allocate, void *(v8::ArrayBuffer::Allocator::*)(unsigned long long)) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::AllocateUninitialized, void *(v8::ArrayBuffer::Allocator::*)(unsigned long long)) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::Free, void (v8::ArrayBuffer::Allocator::*)(void *, unsigned long long)) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::NewDefaultAllocator, v8::ArrayBuffer::Allocator *(*)()) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::operator=, v8::ArrayBuffer::Allocator &(v8::ArrayBuffer::Allocator::*)(const v8::ArrayBuffer::Allocator &)) \
  X(CXXConstructor, v8::ArrayBuffer::Contents::Contents, void (v8::ArrayBuffer::Contents::*)()) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationBase, void *(v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationLength, unsigned long long (v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationMode, v8::ArrayBuffer::Allocator::AllocationMode (v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Contents::Data, void *(v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Contents::ByteLength, unsigned long long (v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Contents::Deleter, void (*(v8::ArrayBuffer::Contents::*)() const)(void *, unsigned long long, void *)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::DeleterData, void *(v8::ArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::ByteLength, unsigned long long (v8::ArrayBuffer::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::New, v8::Local<v8::ArrayBuffer> (*)(v8::Isolate *, unsigned long long)) \
  X(CXXMethod, v8::ArrayBuffer::New, v8::Local<v8::ArrayBuffer> (*)(v8::Isolate *, void *, unsigned long long, v8::ArrayBufferCreationMode)) \
  X(CXXMethod, v8::ArrayBuffer::IsExternal, bool (v8::ArrayBuffer::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::IsDetachable, bool (v8::ArrayBuffer::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::IsNeuterable, bool (v8::ArrayBuffer::*)() const) \
  X(CXXMethod, v8::ArrayBuffer::Detach, void (v8::ArrayBuffer::*)()) \
  X(CXXMethod, v8::ArrayBuffer::Neuter, void (v8::ArrayBuffer::*)()) \
  X(CXXMethod, v8::ArrayBuffer::Externalize, v8::ArrayBuffer::Contents (v8::ArrayBuffer::*)()) \
  X(CXXMethod, v8::ArrayBuffer::GetContents, v8::ArrayBuffer::Contents (v8::ArrayBuffer::*)()) \
  X(CXXMethod, v8::ArrayBuffer::Cast, v8::ArrayBuffer *(*)(v8::Value *)) \
  X(CXXMethod, v8::ArrayBufferView::Buffer, v8::Local<v8::ArrayBuffer> (v8::ArrayBufferView::*)()) \
  X(CXXMethod, v8::ArrayBufferView::ByteOffset, unsigned long long (v8::ArrayBufferView::*)()) \
  X(CXXMethod, v8::ArrayBufferView::ByteLength, unsigned long long (v8::ArrayBufferView::*)()) \
  X(CXXMethod, v8::ArrayBufferView::CopyContents, unsigned long long (v8::ArrayBufferView::*)(void *, unsigned long long)) \
  X(CXXMethod, v8::ArrayBufferView::HasBuffer, bool (v8::ArrayBufferView::*)() const) \
  X(CXXMethod, v8::ArrayBufferView::Cast, v8::ArrayBufferView *(*)(v8::Value *)) \
  X(CXXMethod, v8::TypedArray::Length, unsigned long long (v8::TypedArray::*)()) \
  X(CXXMethod, v8::TypedArray::Cast, v8::TypedArray *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint8Array::New, v8::Local<v8::Uint8Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint8Array::New, v8::Local<v8::Uint8Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint8Array::Cast, v8::Uint8Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint8ClampedArray::New, v8::Local<v8::Uint8ClampedArray> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint8ClampedArray::New, v8::Local<v8::Uint8ClampedArray> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint8ClampedArray::Cast, v8::Uint8ClampedArray *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int8Array::New, v8::Local<v8::Int8Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int8Array::New, v8::Local<v8::Int8Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int8Array::Cast, v8::Int8Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint16Array::New, v8::Local<v8::Uint16Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint16Array::New, v8::Local<v8::Uint16Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint16Array::Cast, v8::Uint16Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int16Array::New, v8::Local<v8::Int16Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int16Array::New, v8::Local<v8::Int16Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int16Array::Cast, v8::Int16Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint32Array::New, v8::Local<v8::Uint32Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint32Array::New, v8::Local<v8::Uint32Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Uint32Array::Cast, v8::Uint32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int32Array::New, v8::Local<v8::Int32Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int32Array::New, v8::Local<v8::Int32Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Int32Array::Cast, v8::Int32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Float32Array::New, v8::Local<v8::Float32Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Float32Array::New, v8::Local<v8::Float32Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Float32Array::Cast, v8::Float32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Float64Array::New, v8::Local<v8::Float64Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Float64Array::New, v8::Local<v8::Float64Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::Float64Array::Cast, v8::Float64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigInt64Array::New, v8::Local<v8::BigInt64Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::BigInt64Array::New, v8::Local<v8::BigInt64Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::BigInt64Array::Cast, v8::BigInt64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigUint64Array::New, v8::Local<v8::BigUint64Array> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::BigUint64Array::New, v8::Local<v8::BigUint64Array> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::BigUint64Array::Cast, v8::BigUint64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::DataView::New, v8::Local<v8::DataView> (*)(v8::Local<v8::ArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::DataView::New, v8::Local<v8::DataView> (*)(v8::Local<v8::SharedArrayBuffer>, unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::DataView::Cast, v8::DataView *(*)(v8::Value *)) \
  X(CXXConstructor, v8::SharedArrayBuffer::Contents::Contents, void (v8::SharedArrayBuffer::Contents::*)()) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationBase, void *(v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationLength, unsigned long long (v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationMode, v8::ArrayBuffer::Allocator::AllocationMode (v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::Data, void *(v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::ByteLength, unsigned long long (v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::Deleter, void (*(v8::SharedArrayBuffer::Contents::*)() const)(void *, unsigned long long, void *)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::DeleterData, void *(v8::SharedArrayBuffer::Contents::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::ByteLength, unsigned long long (v8::SharedArrayBuffer::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::New, v8::Local<v8::SharedArrayBuffer> (*)(v8::Isolate *, unsigned long long)) \
  X(CXXMethod, v8::SharedArrayBuffer::New, v8::Local<v8::SharedArrayBuffer> (*)(v8::Isolate *, void *, unsigned long long, v8::ArrayBufferCreationMode)) \
  X(CXXMethod, v8::SharedArrayBuffer::New, v8::Local<v8::SharedArrayBuffer> (*)(v8::Isolate *, const v8::SharedArrayBuffer::Contents &, v8::ArrayBufferCreationMode)) \
  X(CXXMethod, v8::SharedArrayBuffer::IsExternal, bool (v8::SharedArrayBuffer::*)() const) \
  X(CXXMethod, v8::SharedArrayBuffer::Externalize, v8::SharedArrayBuffer::Contents (v8::SharedArrayBuffer::*)()) \
  X(CXXMethod, v8::SharedArrayBuffer::GetContents, v8::SharedArrayBuffer::Contents (v8::SharedArrayBuffer::*)()) \
  X(CXXMethod, v8::SharedArrayBuffer::Cast, v8::SharedArrayBuffer *(*)(v8::Value *)) \
  X(CXXMethod, v8::Date::New, v8::MaybeLocal<v8::Value> (*)(v8::Local<v8::Context>, double)) \
  X(CXXMethod, v8::Date::ValueOf, double (v8::Date::*)() const) \
  X(CXXMethod, v8::Date::Cast, v8::Date *(*)(v8::Value *)) \
  X(CXXMethod, v8::NumberObject::New, v8::Local<v8::Value> (*)(v8::Isolate *, double)) \
  X(CXXMethod, v8::NumberObject::ValueOf, double (v8::NumberObject::*)() const) \
  X(CXXMethod, v8::NumberObject::Cast, v8::NumberObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigIntObject::New, v8::Local<v8::Value> (*)(v8::Isolate *, long long)) \
  X(CXXMethod, v8::BigIntObject::ValueOf, v8::Local<v8::BigInt> (v8::BigIntObject::*)() const) \
  X(CXXMethod, v8::BigIntObject::Cast, v8::BigIntObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::BooleanObject::New, v8::Local<v8::Value> (*)(v8::Isolate *, bool)) \
  X(CXXMethod, v8::BooleanObject::ValueOf, bool (v8::BooleanObject::*)() const) \
  X(CXXMethod, v8::BooleanObject::Cast, v8::BooleanObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::StringObject::New, v8::Local<v8::Value> (*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::StringObject::ValueOf, v8::Local<v8::String> (v8::StringObject::*)() const) \
  X(CXXMethod, v8::StringObject::Cast, v8::StringObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::SymbolObject::New, v8::Local<v8::Value> (*)(v8::Isolate *, v8::Local<v8::Symbol>)) \
  X(CXXMethod, v8::SymbolObject::ValueOf, v8::Local<v8::Symbol> (v8::SymbolObject::*)() const) \
  X(CXXMethod, v8::SymbolObject::Cast, v8::SymbolObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::RegExp::New, v8::MaybeLocal<v8::RegExp> (*)(v8::Local<v8::Context>, v8::Local<v8::String>, v8::RegExp::Flags)) \
  X(CXXMethod, v8::RegExp::GetSource, v8::Local<v8::String> (v8::RegExp::*)() const) \
  X(CXXMethod, v8::RegExp::GetFlags, v8::RegExp::Flags (v8::RegExp::*)() const) \
  X(CXXMethod, v8::RegExp::Cast, v8::RegExp *(*)(v8::Value *)) \
  X(CXXMethod, v8::External::New, v8::Local<v8::External> (*)(v8::Isolate *, void *)) \
  X(CXXMethod, v8::External::Cast, v8::External *(*)(v8::Value *)) \
  X(CXXMethod, v8::External::Value, void *(v8::External::*)() const) \
  X(CXXMethod, v8::Template::Set, void (v8::Template::*)(v8::Local<v8::Name>, v8::Local<v8::Data>, v8::PropertyAttribute)) \
  X(CXXMethod, v8::Template::SetPrivate, void (v8::Template::*)(v8::Local<v8::Private>, v8::Local<v8::Data>, v8::PropertyAttribute)) \
  X(CXXMethod, v8::Template::Set, void (v8::Template::*)(v8::Isolate *, const char *, v8::Local<v8::Data>)) \
  X(CXXMethod, v8::Template::SetAccessorProperty, void (v8::Template::*)(v8::Local<v8::Name>, v8::Local<v8::FunctionTemplate>, v8::Local<v8::FunctionTemplate>, v8::PropertyAttribute, v8::AccessControl)) \
  X(CXXMethod, v8::Template::SetNativeDataProperty, void (v8::Template::*)(v8::Local<v8::String>, void (*)(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::String>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::Local<v8::Value>, v8::PropertyAttribute, v8::Local<v8::AccessorSignature>, v8::AccessControl, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Template::SetNativeDataProperty, void (v8::Template::*)(v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::Local<v8::Value>, v8::PropertyAttribute, v8::Local<v8::AccessorSignature>, v8::AccessControl, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Template::SetLazyDataProperty, void (v8::Template::*)(v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::Template::SetIntrinsicDataProperty, void (v8::Template::*)(v8::Local<v8::Name>, v8::Intrinsic, v8::PropertyAttribute)) \
  X(CXXMethod, v8::FunctionTemplate::New, v8::Local<v8::FunctionTemplate> (*)(v8::Isolate *, void (*)(const v8::FunctionCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::Local<v8::Signature>, int, v8::ConstructorBehavior, v8::SideEffectType)) \
  X(CXXMethod, v8::FunctionTemplate::FromSnapshot, v8::MaybeLocal<v8::FunctionTemplate> (*)(v8::Isolate *, unsigned long long)) \
  X(CXXMethod, v8::FunctionTemplate::NewWithCache, v8::Local<v8::FunctionTemplate> (*)(v8::Isolate *, void (*)(const v8::FunctionCallbackInfo<v8::Value> &), v8::Local<v8::Private>, v8::Local<v8::Value>, v8::Local<v8::Signature>, int, v8::SideEffectType)) \
  X(CXXMethod, v8::FunctionTemplate::GetFunction, v8::MaybeLocal<v8::Function> (v8::FunctionTemplate::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::FunctionTemplate::NewRemoteInstance, v8::MaybeLocal<v8::Object> (v8::FunctionTemplate::*)()) \
  X(CXXMethod, v8::FunctionTemplate::SetCallHandler, void (v8::FunctionTemplate::*)(void (*)(const v8::FunctionCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::SideEffectType)) \
  X(CXXMethod, v8::FunctionTemplate::SetLength, void (v8::FunctionTemplate::*)(int)) \
  X(CXXMethod, v8::FunctionTemplate::InstanceTemplate, v8::Local<v8::ObjectTemplate> (v8::FunctionTemplate::*)()) \
  X(CXXMethod, v8::FunctionTemplate::Inherit, void (v8::FunctionTemplate::*)(v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::FunctionTemplate::PrototypeTemplate, v8::Local<v8::ObjectTemplate> (v8::FunctionTemplate::*)()) \
  X(CXXMethod, v8::FunctionTemplate::SetPrototypeProviderTemplate, void (v8::FunctionTemplate::*)(v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::FunctionTemplate::SetClassName, void (v8::FunctionTemplate::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::FunctionTemplate::SetAcceptAnyReceiver, void (v8::FunctionTemplate::*)(bool)) \
  X(CXXMethod, v8::FunctionTemplate::ReadOnlyPrototype, void (v8::FunctionTemplate::*)()) \
  X(CXXMethod, v8::FunctionTemplate::RemovePrototype, void (v8::FunctionTemplate::*)()) \
  X(CXXMethod, v8::FunctionTemplate::HasInstance, bool (v8::FunctionTemplate::*)(v8::Local<v8::Value>)) \
  X(CXXMethod, v8::FunctionTemplate::Cast, v8::FunctionTemplate *(*)(v8::Data *)) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, void (v8::NamedPropertyHandlerConfiguration::*)(void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Integer> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), void (*)(v8::Local<v8::Name>, const v8::PropertyDescriptor &, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, void (v8::NamedPropertyHandlerConfiguration::*)(void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Integer> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, void (v8::NamedPropertyHandlerConfiguration::*)(void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), void (*)(v8::Local<v8::Name>, const v8::PropertyDescriptor &, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, void (v8::NamedPropertyHandlerConfiguration::*)(const v8::NamedPropertyHandlerConfiguration &)) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, void (v8::NamedPropertyHandlerConfiguration::*)(v8::NamedPropertyHandlerConfiguration &&)) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)(void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Integer> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), void (*)(unsigned int, const v8::PropertyDescriptor &, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)(void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Integer> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)(void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), void (*)(unsigned int, const v8::PropertyDescriptor &, const v8::PropertyCallbackInfo<v8::Value> &), v8::Local<v8::Value>, v8::PropertyHandlerFlags)) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)(const v8::IndexedPropertyHandlerConfiguration &)) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)(v8::IndexedPropertyHandlerConfiguration &&)) \
  X(CXXDestructor, v8::IndexedPropertyHandlerConfiguration::~IndexedPropertyHandlerConfiguration, void (v8::IndexedPropertyHandlerConfiguration::*)()) \
  X(CXXMethod, v8::ObjectTemplate::New, v8::Local<v8::ObjectTemplate> (*)(v8::Isolate *, v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::ObjectTemplate::FromSnapshot, v8::MaybeLocal<v8::ObjectTemplate> (*)(v8::Isolate *, unsigned long long)) \
  X(CXXMethod, v8::ObjectTemplate::NewInstance, v8::MaybeLocal<v8::Object> (v8::ObjectTemplate::*)(v8::Local<v8::Context>)) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessor, void (v8::ObjectTemplate::*)(v8::Local<v8::String>, void (*)(v8::Local<v8::String>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::String>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::Local<v8::Value>, v8::AccessControl, v8::PropertyAttribute, v8::Local<v8::AccessorSignature>, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessor, void (v8::ObjectTemplate::*)(v8::Local<v8::Name>, void (*)(v8::Local<v8::Name>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(v8::Local<v8::Name>, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<void> &), v8::Local<v8::Value>, v8::AccessControl, v8::PropertyAttribute, v8::Local<v8::AccessorSignature>, v8::SideEffectType, v8::SideEffectType)) \
  X(CXXMethod, v8::ObjectTemplate::SetHandler, void (v8::ObjectTemplate::*)(const v8::NamedPropertyHandlerConfiguration &)) \
  X(CXXMethod, v8::ObjectTemplate::SetIndexedPropertyHandler, void (v8::ObjectTemplate::*)(void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, v8::Local<v8::Value>, const v8::PropertyCallbackInfo<v8::Value> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Integer> &), void (*)(unsigned int, const v8::PropertyCallbackInfo<v8::Boolean> &), void (*)(const v8::PropertyCallbackInfo<v8::Array> &), v8::Local<v8::Value>)) \
  X(CXXMethod, v8::ObjectTemplate::SetHandler, void (v8::ObjectTemplate::*)(const v8::IndexedPropertyHandlerConfiguration &)) \
  X(CXXMethod, v8::ObjectTemplate::SetCallAsFunctionHandler, void (v8::ObjectTemplate::*)(void (*)(const v8::FunctionCallbackInfo<v8::Value> &), v8::Local<v8::Value>)) \
  X(CXXMethod, v8::ObjectTemplate::MarkAsUndetectable, void (v8::ObjectTemplate::*)()) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessCheckCallback, void (v8::ObjectTemplate::*)(bool (*)(v8::Local<v8::Context>, v8::Local<v8::Object>, v8::Local<v8::Value>), v8::Local<v8::Value>)) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessCheckCallbackAndHandler, void (v8::ObjectTemplate::*)(bool (*)(v8::Local<v8::Context>, v8::Local<v8::Object>, v8::Local<v8::Value>), const v8::NamedPropertyHandlerConfiguration &, const v8::IndexedPropertyHandlerConfiguration &, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::ObjectTemplate::InternalFieldCount, int (v8::ObjectTemplate::*)()) \
  X(CXXMethod, v8::ObjectTemplate::SetInternalFieldCount, void (v8::ObjectTemplate::*)(int)) \
  X(CXXMethod, v8::ObjectTemplate::IsImmutableProto, bool (v8::ObjectTemplate::*)()) \
  X(CXXMethod, v8::ObjectTemplate::SetImmutableProto, void (v8::ObjectTemplate::*)()) \
  X(CXXMethod, v8::ObjectTemplate::Cast, v8::ObjectTemplate *(*)(v8::Data *)) \
  X(CXXMethod, v8::Signature::New, v8::Local<v8::Signature> (*)(v8::Isolate *, v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::Signature::Cast, v8::Signature *(*)(v8::Data *)) \
  X(CXXMethod, v8::AccessorSignature::New, v8::Local<v8::AccessorSignature> (*)(v8::Isolate *, v8::Local<v8::FunctionTemplate>)) \
  X(CXXMethod, v8::AccessorSignature::Cast, v8::AccessorSignature *(*)(v8::Data *)) \
  X(CXXConstructor, v8::Extension::Extension, void (v8::Extension::*)(const char *, const char *, int, const char **, int)) \
  X(CXXDestructor, v8::Extension::~Extension, void (v8::Extension::*)()) \
  X(CXXMethod, v8::Extension::GetNativeFunctionTemplate, v8::Local<v8::FunctionTemplate> (v8::Extension::*)(v8::Isolate *, v8::Local<v8::String>)) \
  X(CXXMethod, v8::Extension::name, const char *(v8::Extension::*)() const) \
  X(CXXMethod, v8::Extension::source_length, unsigned long long (v8::Extension::*)() const) \
  X(CXXMethod, v8::Extension::source, const v8::String::ExternalOneByteStringResource *(v8::Extension::*)() const) \
  X(CXXMethod, v8::Extension::dependency_count, int (v8::Extension::*)() const) \
  X(CXXMethod, v8::Extension::dependencies, const char **(v8::Extension::*)() const) \
  X(CXXMethod, v8::Extension::set_auto_enable, void (v8::Extension::*)(bool)) \
  X(CXXMethod, v8::Extension::auto_enable, bool (v8::Extension::*)()) \
  X(Function, v8::Undefined, v8::Local<v8::Primitive> (*)(v8::Isolate *)) \
  X(Function, v8::Null, v8::Local<v8::Primitive> (*)(v8::Isolate *)) \
  X(Function, v8::True, v8::Local<v8::Boolean> (*)(v8::Isolate *)) \
  X(Function, v8::False, v8::Local<v8::Boolean> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::ResourceConstraints::ConfigureDefaultsFromHeapSize, void (v8::ResourceConstraints::*)(unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::ConfigureDefaults, void (v8::ResourceConstraints::*)(unsigned long long, unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::stack_limit, unsigned int *(v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_stack_limit, void (v8::ResourceConstraints::*)(unsigned int *)) \
  X(CXXMethod, v8::ResourceConstraints::code_range_size_in_bytes, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_code_range_size_in_bytes, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::max_old_generation_size_in_bytes, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_max_old_generation_size_in_bytes, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::max_young_generation_size_in_bytes, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_max_young_generation_size_in_bytes, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::initial_old_generation_size_in_bytes, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_initial_old_generation_size_in_bytes, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::initial_young_generation_size_in_bytes, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_initial_young_generation_size_in_bytes, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::code_range_size, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_code_range_size, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::max_semi_space_size_in_kb, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_max_semi_space_size_in_kb, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::max_old_space_size, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_max_old_space_size, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXMethod, v8::ResourceConstraints::max_zone_pool_size, unsigned long long (v8::ResourceConstraints::*)() const) \
  X(CXXMethod, v8::ResourceConstraints::set_max_zone_pool_size, void (v8::ResourceConstraints::*)(unsigned long long)) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, void (v8::ResourceConstraints::*)()) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, void (v8::ResourceConstraints::*)(const v8::ResourceConstraints &)) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, void (v8::ResourceConstraints::*)(v8::ResourceConstraints &&)) \
  X(CXXMethod, v8::Exception::RangeError, v8::Local<v8::Value> (*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Exception::ReferenceError, v8::Local<v8::Value> (*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Exception::SyntaxError, v8::Local<v8::Value> (*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Exception::TypeError, v8::Local<v8::Value> (*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Exception::Error, v8::Local<v8::Value> (*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Exception::CreateMessage, v8::Local<v8::Message> (*)(v8::Isolate *, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Exception::GetStackTrace, v8::Local<v8::StackTrace> (*)(v8::Local<v8::Value>)) \
  X(CXXConstructor, v8::PromiseRejectMessage::PromiseRejectMessage, void (v8::PromiseRejectMessage::*)(v8::Local<v8::Promise>, v8::PromiseRejectEvent, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::PromiseRejectMessage::GetPromise, v8::Local<v8::Promise> (v8::PromiseRejectMessage::*)() const) \
  X(CXXMethod, v8::PromiseRejectMessage::GetEvent, v8::PromiseRejectEvent (v8::PromiseRejectMessage::*)() const) \
  X(CXXMethod, v8::PromiseRejectMessage::GetValue, v8::Local<v8::Value> (v8::PromiseRejectMessage::*)() const) \
  X(CXXDestructor, v8::MicrotaskQueue::~MicrotaskQueue, void (v8::MicrotaskQueue::*)()) \
  X(CXXMethod, v8::MicrotaskQueue::EnqueueMicrotask, void (v8::MicrotaskQueue::*)(v8::Isolate *, v8::Local<v8::Function>)) \
  X(CXXMethod, v8::MicrotaskQueue::EnqueueMicrotask, void (v8::MicrotaskQueue::*)(v8::Isolate *, void (*)(void *), void *)) \
  X(CXXMethod, v8::MicrotaskQueue::AddMicrotasksCompletedCallback, void (v8::MicrotaskQueue::*)(void (*)(v8::Isolate *, void *), void *)) \
  X(CXXMethod, v8::MicrotaskQueue::RemoveMicrotasksCompletedCallback, void (v8::MicrotaskQueue::*)(void (*)(v8::Isolate *, void *), void *)) \
  X(CXXMethod, v8::MicrotaskQueue::PerformCheckpoint, void (v8::MicrotaskQueue::*)(v8::Isolate *)) \
  X(CXXMethod, v8::MicrotaskQueue::IsRunningMicrotasks, bool (v8::MicrotaskQueue::*)() const) \
  X(CXXMethod, v8::MicrotaskQueue::GetMicrotasksScopeDepth, int (v8::MicrotaskQueue::*)() const) \
  X(CXXConstructor, v8::MicrotasksScope::MicrotasksScope, void (v8::MicrotasksScope::*)(v8::Isolate *, v8::MicrotasksScope::Type)) \
  X(CXXConstructor, v8::MicrotasksScope::MicrotasksScope, void (v8::MicrotasksScope::*)(v8::Isolate *, v8::MicrotaskQueue *, v8::MicrotasksScope::Type)) \
  X(CXXDestructor, v8::MicrotasksScope::~MicrotasksScope, void (v8::MicrotasksScope::*)()) \
  X(CXXMethod, v8::MicrotasksScope::PerformCheckpoint, void (*)(v8::Isolate *)) \
  X(CXXMethod, v8::MicrotasksScope::GetCurrentDepth, int (*)(v8::Isolate *)) \
  X(CXXMethod, v8::MicrotasksScope::IsRunningMicrotasks, bool (*)(v8::Isolate *)) \
  X(CXXConstructor, v8::HeapStatistics::HeapStatistics, void (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::total_heap_size, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::total_heap_size_executable, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::total_physical_size, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::total_available_size, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::used_heap_size, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::heap_size_limit, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::malloced_memory, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::external_memory, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::peak_malloced_memory, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::number_of_native_contexts, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::number_of_detached_contexts, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXMethod, v8::HeapStatistics::does_zap_garbage, unsigned long long (v8::HeapStatistics::*)()) \
  X(CXXConstructor, v8::HeapSpaceStatistics::HeapSpaceStatistics, void (v8::HeapSpaceStatistics::*)()) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_name, const char *(v8::HeapSpaceStatistics::*)()) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_size, unsigned long long (v8::HeapSpaceStatistics::*)()) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_used_size, unsigned long long (v8::HeapSpaceStatistics::*)()) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_available_size, unsigned long long (v8::HeapSpaceStatistics::*)()) \
  X(CXXMethod, v8::HeapSpaceStatistics::physical_space_size, unsigned long long (v8::HeapSpaceStatistics::*)()) \
  X(CXXConstructor, v8::HeapObjectStatistics::HeapObjectStatistics, void (v8::HeapObjectStatistics::*)()) \
  X(CXXMethod, v8::HeapObjectStatistics::object_type, const char *(v8::HeapObjectStatistics::*)()) \
  X(CXXMethod, v8::HeapObjectStatistics::object_sub_type, const char *(v8::HeapObjectStatistics::*)()) \
  X(CXXMethod, v8::HeapObjectStatistics::object_count, unsigned long long (v8::HeapObjectStatistics::*)()) \
  X(CXXMethod, v8::HeapObjectStatistics::object_size, unsigned long long (v8::HeapObjectStatistics::*)()) \
  X(CXXConstructor, v8::HeapCodeStatistics::HeapCodeStatistics, void (v8::HeapCodeStatistics::*)()) \
  X(CXXMethod, v8::HeapCodeStatistics::code_and_metadata_size, unsigned long long (v8::HeapCodeStatistics::*)()) \
  X(CXXMethod, v8::HeapCodeStatistics::bytecode_and_metadata_size, unsigned long long (v8::HeapCodeStatistics::*)()) \
  X(CXXMethod, v8::HeapCodeStatistics::external_script_source_size, unsigned long long (v8::HeapCodeStatistics::*)()) \
  X(CXXDestructor, v8::ExternalResourceVisitor::~ExternalResourceVisitor, void (v8::ExternalResourceVisitor::*)()) \
  X(CXXMethod, v8::ExternalResourceVisitor::VisitExternalString, void (v8::ExternalResourceVisitor::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::ExternalResourceVisitor::operator=, v8::ExternalResourceVisitor &(v8::ExternalResourceVisitor::*)(const v8::ExternalResourceVisitor &)) \
  X(CXXDestructor, v8::PersistentHandleVisitor::~PersistentHandleVisitor, void (v8::PersistentHandleVisitor::*)()) \
  X(CXXMethod, v8::PersistentHandleVisitor::VisitPersistentHandle, void (v8::PersistentHandleVisitor::*)(v8::Persistent<v8::Value, v8::NonCopyablePersistentTraits<v8::Value> > *, unsigned short)) \
  X(CXXMethod, v8::PersistentHandleVisitor::operator=, v8::PersistentHandleVisitor &(v8::PersistentHandleVisitor::*)(const v8::PersistentHandleVisitor &)) \
  X(CXXDestructor, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::~TracedGlobalHandleVisitor, void (v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::VisitTracedGlobalHandle, void (v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::*)(const v8::TracedGlobal<v8::Value> &)) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::operator=, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor &(v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::*)(const v8::EmbedderHeapTracer::TracedGlobalHandleVisitor &)) \
  X(CXXDestructor, v8::EmbedderHeapTracer::~EmbedderHeapTracer, void (v8::EmbedderHeapTracer::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::IterateTracedGlobalHandles, void (v8::EmbedderHeapTracer::*)(v8::EmbedderHeapTracer::TracedGlobalHandleVisitor *)) \
  X(CXXMethod, v8::EmbedderHeapTracer::RegisterV8References, void (v8::EmbedderHeapTracer::*)(const std::vector<std::pair<void *, void *>, std::allocator<std::pair<void *, void *> > > &)) \
  X(CXXMethod, v8::EmbedderHeapTracer::RegisterEmbedderReference, void (v8::EmbedderHeapTracer::*)(const v8::TracedGlobal<v8::Value> &)) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracePrologue, void (v8::EmbedderHeapTracer::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracePrologue, void (v8::EmbedderHeapTracer::*)(v8::EmbedderHeapTracer::TraceFlags)) \
  X(CXXMethod, v8::EmbedderHeapTracer::AdvanceTracing, bool (v8::EmbedderHeapTracer::*)(double)) \
  X(CXXMethod, v8::EmbedderHeapTracer::IsTracingDone, bool (v8::EmbedderHeapTracer::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::TraceEpilogue, void (v8::EmbedderHeapTracer::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::TraceEpilogue, void (v8::EmbedderHeapTracer::*)(v8::EmbedderHeapTracer::TraceSummary *)) \
  X(CXXMethod, v8::EmbedderHeapTracer::EnterFinalPause, void (v8::EmbedderHeapTracer::*)(v8::EmbedderHeapTracer::EmbedderStackState)) \
  X(CXXMethod, v8::EmbedderHeapTracer::FinalizeTracing, void (v8::EmbedderHeapTracer::*)()) \
  X(CXXMethod, v8::EmbedderHeapTracer::IsRootForNonTracingGC, bool (v8::EmbedderHeapTracer::*)(const v8::TracedGlobal<v8::Value> &)) \
  X(CXXMethod, v8::EmbedderHeapTracer::GarbageCollectionForTesting, void (v8::EmbedderHeapTracer::*)(v8::EmbedderHeapTracer::EmbedderStackState)) \
  X(CXXMethod, v8::EmbedderHeapTracer::IncreaseAllocatedSize, void (v8::EmbedderHeapTracer::*)(unsigned long long)) \
  X(CXXMethod, v8::EmbedderHeapTracer::DecreaseAllocatedSize, void (v8::EmbedderHeapTracer::*)(unsigned long long)) \
  X(CXXMethod, v8::EmbedderHeapTracer::isolate, v8::Isolate *(v8::EmbedderHeapTracer::*)() const) \
  X(CXXMethod, v8::EmbedderHeapTracer::operator=, v8::EmbedderHeapTracer &(v8::EmbedderHeapTracer::*)(const v8::EmbedderHeapTracer &)) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, void (v8::SerializeInternalFieldsCallback::*)(v8::StartupData (*)(v8::Local<v8::Object>, int, void *), void *)) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, void (v8::SerializeInternalFieldsCallback::*)(const v8::SerializeInternalFieldsCallback &)) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, void (v8::SerializeInternalFieldsCallback::*)(v8::SerializeInternalFieldsCallback &&)) \
  X(CXXDestructor, v8::SerializeInternalFieldsCallback::~SerializeInternalFieldsCallback, void (v8::SerializeInternalFieldsCallback::*)()) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, void (v8::DeserializeInternalFieldsCallback::*)(void (*)(v8::Local<v8::Object>, int, v8::StartupData, void *), void *)) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, void (v8::DeserializeInternalFieldsCallback::*)(const v8::DeserializeInternalFieldsCallback &)) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, void (v8::DeserializeInternalFieldsCallback::*)(v8::DeserializeInternalFieldsCallback &&)) \
  X(CXXDestructor, v8::DeserializeInternalFieldsCallback::~DeserializeInternalFieldsCallback, void (v8::DeserializeInternalFieldsCallback::*)()) \
  X(CXXConstructor, v8::Isolate::CreateParams::CreateParams, void (v8::Isolate::CreateParams::*)()) \
  X(CXXConstructor, v8::Isolate::Scope::Scope, void (v8::Isolate::Scope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::Isolate::Scope::~Scope, void (v8::Isolate::Scope::*)()) \
  X(CXXConstructor, v8::Isolate::DisallowJavascriptExecutionScope::DisallowJavascriptExecutionScope, void (v8::Isolate::DisallowJavascriptExecutionScope::*)(v8::Isolate *, v8::Isolate::DisallowJavascriptExecutionScope::OnFailure)) \
  X(CXXDestructor, v8::Isolate::DisallowJavascriptExecutionScope::~DisallowJavascriptExecutionScope, void (v8::Isolate::DisallowJavascriptExecutionScope::*)()) \
  X(CXXConstructor, v8::Isolate::AllowJavascriptExecutionScope::AllowJavascriptExecutionScope, void (v8::Isolate::AllowJavascriptExecutionScope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::Isolate::AllowJavascriptExecutionScope::~AllowJavascriptExecutionScope, void (v8::Isolate::AllowJavascriptExecutionScope::*)()) \
  X(CXXConstructor, v8::Isolate::SuppressMicrotaskExecutionScope::SuppressMicrotaskExecutionScope, void (v8::Isolate::SuppressMicrotaskExecutionScope::*)(v8::Isolate *)) \
  X(CXXConstructor, v8::Isolate::SuppressMicrotaskExecutionScope::SuppressMicrotaskExecutionScope, void (v8::Isolate::SuppressMicrotaskExecutionScope::*)(v8::MicrotaskQueue *)) \
  X(CXXDestructor, v8::Isolate::SuppressMicrotaskExecutionScope::~SuppressMicrotaskExecutionScope, void (v8::Isolate::SuppressMicrotaskExecutionScope::*)()) \
  X(CXXConstructor, v8::Isolate::SafeForTerminationScope::SafeForTerminationScope, void (v8::Isolate::SafeForTerminationScope::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::Isolate::SafeForTerminationScope::~SafeForTerminationScope, void (v8::Isolate::SafeForTerminationScope::*)()) \
  X(CXXMethod, v8::Isolate::Allocate, v8::Isolate *(*)()) \
  X(CXXMethod, v8::Isolate::Initialize, void (*)(v8::Isolate *, const v8::Isolate::CreateParams &)) \
  X(CXXMethod, v8::Isolate::New, v8::Isolate *(*)(const v8::Isolate::CreateParams &)) \
  X(CXXMethod, v8::Isolate::GetCurrent, v8::Isolate *(*)()) \
  X(CXXMethod, v8::Isolate::SetAbortOnUncaughtExceptionCallback, void (v8::Isolate::*)(bool (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::SetHostImportModuleDynamicallyCallback, void (v8::Isolate::*)(v8::MaybeLocal<v8::Promise> (*)(v8::Local<v8::Context>, v8::Local<v8::ScriptOrModule>, v8::Local<v8::String>))) \
  X(CXXMethod, v8::Isolate::SetHostInitializeImportMetaObjectCallback, void (v8::Isolate::*)(void (*)(v8::Local<v8::Context>, v8::Local<v8::Module>, v8::Local<v8::Object>))) \
  X(CXXMethod, v8::Isolate::SetPrepareStackTraceCallback, void (v8::Isolate::*)(v8::MaybeLocal<v8::Value> (*)(v8::Local<v8::Context>, v8::Local<v8::Value>, v8::Local<v8::Array>))) \
  X(CXXMethod, v8::Isolate::MemoryPressureNotification, void (v8::Isolate::*)(v8::MemoryPressureLevel)) \
  X(CXXMethod, v8::Isolate::Enter, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::Exit, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::Dispose, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::DumpAndResetStats, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::DiscardThreadSpecificMetadata, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetData, void (v8::Isolate::*)(unsigned int, void *)) \
  X(CXXMethod, v8::Isolate::GetData, void *(v8::Isolate::*)(unsigned int)) \
  X(CXXMethod, v8::Isolate::GetNumberOfDataSlots, unsigned int (*)()) \
  X(CXXMethod, v8::Isolate::GetHeapStatistics, void (v8::Isolate::*)(v8::HeapStatistics *)) \
  X(CXXMethod, v8::Isolate::NumberOfHeapSpaces, unsigned long long (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetHeapSpaceStatistics, bool (v8::Isolate::*)(v8::HeapSpaceStatistics *, unsigned long long)) \
  X(CXXMethod, v8::Isolate::NumberOfTrackedHeapObjectTypes, unsigned long long (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetHeapObjectStatisticsAtLastGC, bool (v8::Isolate::*)(v8::HeapObjectStatistics *, unsigned long long)) \
  X(CXXMethod, v8::Isolate::GetHeapCodeAndMetadataStatistics, bool (v8::Isolate::*)(v8::HeapCodeStatistics *)) \
  X(CXXMethod, v8::Isolate::GetStackSample, void (v8::Isolate::*)(const v8::RegisterState &, void **, unsigned long long, v8::SampleInfo *)) \
  X(CXXMethod, v8::Isolate::AdjustAmountOfExternalAllocatedMemory, long long (v8::Isolate::*)(long long)) \
  X(CXXMethod, v8::Isolate::NumberOfPhantomHandleResetsSinceLastCall, unsigned long long (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetHeapProfiler, v8::HeapProfiler *(v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetIdle, void (v8::Isolate::*)(bool)) \
  X(CXXMethod, v8::Isolate::GetArrayBufferAllocator, v8::ArrayBuffer::Allocator *(v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::InContext, bool (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetCurrentContext, v8::Local<v8::Context> (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetEnteredContext, v8::Local<v8::Context> (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetEnteredOrMicrotaskContext, v8::Local<v8::Context> (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::GetIncumbentContext, v8::Local<v8::Context> (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::ThrowException, v8::Local<v8::Value> (v8::Isolate::*)(v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Isolate::AddGCPrologueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags, void *), void *, v8::GCType)) \
  X(CXXMethod, v8::Isolate::AddGCPrologueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags), v8::GCType)) \
  X(CXXMethod, v8::Isolate::RemoveGCPrologueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags, void *), void *)) \
  X(CXXMethod, v8::Isolate::RemoveGCPrologueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags))) \
  X(CXXMethod, v8::Isolate::SetEmbedderHeapTracer, void (v8::Isolate::*)(v8::EmbedderHeapTracer *)) \
  X(CXXMethod, v8::Isolate::GetEmbedderHeapTracer, v8::EmbedderHeapTracer *(v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::AtomicsWaitWakeHandle::Wake, void (v8::Isolate::AtomicsWaitWakeHandle::*)()) \
  X(CXXMethod, v8::Isolate::SetAtomicsWaitCallback, void (v8::Isolate::*)(void (*)(v8::Isolate::AtomicsWaitEvent, v8::Local<v8::SharedArrayBuffer>, unsigned long long, long long, double, v8::Isolate::AtomicsWaitWakeHandle *, void *), void *)) \
  X(CXXMethod, v8::Isolate::AddGCEpilogueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags, void *), void *, v8::GCType)) \
  X(CXXMethod, v8::Isolate::AddGCEpilogueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags), v8::GCType)) \
  X(CXXMethod, v8::Isolate::RemoveGCEpilogueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags, void *), void *)) \
  X(CXXMethod, v8::Isolate::RemoveGCEpilogueCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::GCType, v8::GCCallbackFlags))) \
  X(CXXMethod, v8::Isolate::SetGetExternallyAllocatedMemoryInBytesCallback, void (v8::Isolate::*)(unsigned long long (*)())) \
  X(CXXMethod, v8::Isolate::TerminateExecution, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::IsExecutionTerminating, bool (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::CancelTerminateExecution, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::RequestInterrupt, void (v8::Isolate::*)(void (*)(v8::Isolate *, void *), void *)) \
  X(CXXMethod, v8::Isolate::RequestGarbageCollectionForTesting, void (v8::Isolate::*)(v8::Isolate::GarbageCollectionType)) \
  X(CXXMethod, v8::Isolate::SetEventLogger, void (v8::Isolate::*)(void (*)(const char *, int))) \
  X(CXXMethod, v8::Isolate::AddBeforeCallEnteredCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::RemoveBeforeCallEnteredCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::AddCallCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::RemoveCallCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::SetPromiseHook, void (v8::Isolate::*)(void (*)(v8::PromiseHookType, v8::Local<v8::Promise>, v8::Local<v8::Value>))) \
  X(CXXMethod, v8::Isolate::SetPromiseRejectCallback, void (v8::Isolate::*)(void (*)(v8::PromiseRejectMessage))) \
  X(CXXMethod, v8::Isolate::RunMicrotasks, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::EnqueueMicrotask, void (v8::Isolate::*)(v8::Local<v8::Function>)) \
  X(CXXMethod, v8::Isolate::EnqueueMicrotask, void (v8::Isolate::*)(void (*)(void *), void *)) \
  X(CXXMethod, v8::Isolate::SetMicrotasksPolicy, void (v8::Isolate::*)(v8::MicrotasksPolicy)) \
  X(CXXMethod, v8::Isolate::GetMicrotasksPolicy, v8::MicrotasksPolicy (v8::Isolate::*)() const) \
  X(CXXMethod, v8::Isolate::AddMicrotasksCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::AddMicrotasksCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, void *), void *)) \
  X(CXXMethod, v8::Isolate::RemoveMicrotasksCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::RemoveMicrotasksCompletedCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, void *), void *)) \
  X(CXXMethod, v8::Isolate::SetUseCounterCallback, void (v8::Isolate::*)(void (*)(v8::Isolate *, v8::Isolate::UseCounterFeature))) \
  X(CXXMethod, v8::Isolate::SetCounterFunction, void (v8::Isolate::*)(int *(*)(const char *))) \
  X(CXXMethod, v8::Isolate::SetCreateHistogramFunction, void (v8::Isolate::*)(void *(*)(const char *, int, int, unsigned long long))) \
  X(CXXMethod, v8::Isolate::SetAddHistogramSampleFunction, void (v8::Isolate::*)(void (*)(void *, int))) \
  X(CXXMethod, v8::Isolate::IdleNotificationDeadline, bool (v8::Isolate::*)(double)) \
  X(CXXMethod, v8::Isolate::LowMemoryNotification, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::ContextDisposedNotification, int (v8::Isolate::*)(bool)) \
  X(CXXMethod, v8::Isolate::IsolateInForegroundNotification, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::IsolateInBackgroundNotification, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::EnableMemorySavingsMode, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::DisableMemorySavingsMode, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetRAILMode, void (v8::Isolate::*)(v8::RAILMode)) \
  X(CXXMethod, v8::Isolate::IncreaseHeapLimitForDebugging, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::RestoreOriginalHeapLimit, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::IsHeapLimitIncreasedForDebugging, bool (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetJitCodeEventHandler, void (v8::Isolate::*)(v8::JitCodeEventOptions, void (*)(const v8::JitCodeEvent *))) \
  X(CXXMethod, v8::Isolate::SetStackLimit, void (v8::Isolate::*)(unsigned long long)) \
  X(CXXMethod, v8::Isolate::GetCodeRange, void (v8::Isolate::*)(void **, unsigned long long *)) \
  X(CXXMethod, v8::Isolate::GetUnwindState, v8::UnwindState (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetFatalErrorHandler, void (v8::Isolate::*)(void (*)(const char *, const char *))) \
  X(CXXMethod, v8::Isolate::SetOOMErrorHandler, void (v8::Isolate::*)(void (*)(const char *, bool))) \
  X(CXXMethod, v8::Isolate::AddNearHeapLimitCallback, void (v8::Isolate::*)(unsigned long long (*)(void *, unsigned long long, unsigned long long), void *)) \
  X(CXXMethod, v8::Isolate::RemoveNearHeapLimitCallback, void (v8::Isolate::*)(unsigned long long (*)(void *, unsigned long long, unsigned long long), unsigned long long)) \
  X(CXXMethod, v8::Isolate::AutomaticallyRestoreInitialHeapLimit, void (v8::Isolate::*)(double)) \
  X(CXXMethod, v8::Isolate::SetAllowCodeGenerationFromStringsCallback, void (v8::Isolate::*)(bool (*)(v8::Local<v8::Context>, v8::Local<v8::String>))) \
  X(CXXMethod, v8::Isolate::SetAllowWasmCodeGenerationCallback, void (v8::Isolate::*)(bool (*)(v8::Local<v8::Context>, v8::Local<v8::String>))) \
  X(CXXMethod, v8::Isolate::SetWasmModuleCallback, void (v8::Isolate::*)(bool (*)(const v8::FunctionCallbackInfo<v8::Value> &))) \
  X(CXXMethod, v8::Isolate::SetWasmInstanceCallback, void (v8::Isolate::*)(bool (*)(const v8::FunctionCallbackInfo<v8::Value> &))) \
  X(CXXMethod, v8::Isolate::SetWasmStreamingCallback, void (v8::Isolate::*)(void (*)(const v8::FunctionCallbackInfo<v8::Value> &))) \
  X(CXXMethod, v8::Isolate::SetWasmThreadsEnabledCallback, void (v8::Isolate::*)(bool (*)(v8::Local<v8::Context>))) \
  X(CXXMethod, v8::Isolate::IsDead, bool (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::AddMessageListener, bool (v8::Isolate::*)(void (*)(v8::Local<v8::Message>, v8::Local<v8::Value>), v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Isolate::AddMessageListenerWithErrorLevel, bool (v8::Isolate::*)(void (*)(v8::Local<v8::Message>, v8::Local<v8::Value>), int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Isolate::RemoveMessageListeners, void (v8::Isolate::*)(void (*)(v8::Local<v8::Message>, v8::Local<v8::Value>))) \
  X(CXXMethod, v8::Isolate::SetFailedAccessCheckCallbackFunction, void (v8::Isolate::*)(void (*)(v8::Local<v8::Object>, v8::AccessType, v8::Local<v8::Value>))) \
  X(CXXMethod, v8::Isolate::SetCaptureStackTraceForUncaughtExceptions, void (v8::Isolate::*)(bool, int, v8::StackTrace::StackTraceOptions)) \
  X(CXXMethod, v8::Isolate::VisitExternalResources, void (v8::Isolate::*)(v8::ExternalResourceVisitor *)) \
  X(CXXMethod, v8::Isolate::VisitHandlesWithClassIds, void (v8::Isolate::*)(v8::PersistentHandleVisitor *)) \
  X(CXXMethod, v8::Isolate::VisitWeakHandles, void (v8::Isolate::*)(v8::PersistentHandleVisitor *)) \
  X(CXXMethod, v8::Isolate::IsInUse, bool (v8::Isolate::*)()) \
  X(CXXMethod, v8::Isolate::SetAllowAtomicsWait, void (v8::Isolate::*)(bool)) \
  X(CXXMethod, v8::Isolate::DateTimeConfigurationChangeNotification, void (v8::Isolate::*)(v8::Isolate::TimeZoneDetection)) \
  X(CXXMethod, v8::Isolate::LocaleConfigurationChangeNotification, void (v8::Isolate::*)()) \
  X(CXXMethod, v8::StartupData::CanBeRehashed, bool (v8::StartupData::*)() const) \
  X(CXXMethod, v8::V8::SetNativesDataBlob, void (*)(v8::StartupData *)) \
  X(CXXMethod, v8::V8::SetSnapshotDataBlob, void (*)(v8::StartupData *)) \
  X(CXXMethod, v8::V8::SetDcheckErrorHandler, void (*)(void (*)(const char *, int, const char *))) \
  X(CXXMethod, v8::V8::SetFlagsFromString, void (*)(const char *)) \
  X(CXXMethod, v8::V8::SetFlagsFromString, void (*)(const char *, unsigned long long)) \
  X(CXXMethod, v8::V8::SetFlagsFromString, void (*)(const char *, int)) \
  X(CXXMethod, v8::V8::SetFlagsFromCommandLine, void (*)(int *, char **, bool)) \
  X(CXXMethod, v8::V8::GetVersion, const char *(*)()) \
  X(CXXMethod, v8::V8::Initialize, bool (*)()) \
  X(CXXMethod, v8::V8::SetEntropySource, void (*)(bool (*)(unsigned char *, unsigned long long))) \
  X(CXXMethod, v8::V8::SetReturnAddressLocationResolver, void (*)(unsigned long long (*)(unsigned long long))) \
  X(CXXMethod, v8::V8::Dispose, bool (*)()) \
  X(CXXMethod, v8::V8::InitializeICU, bool (*)(const char *)) \
  X(CXXMethod, v8::V8::InitializeICUDefaultLocation, bool (*)(const char *, const char *)) \
  X(CXXMethod, v8::V8::InitializeExternalStartupData, void (*)(const char *)) \
  X(CXXMethod, v8::V8::InitializeExternalStartupData, void (*)(const char *, const char *)) \
  X(CXXMethod, v8::V8::InitializePlatform, void (*)(v8::Platform *)) \
  X(CXXMethod, v8::V8::ShutdownPlatform, void (*)()) \
  X(CXXMethod, v8::V8::EnableWebAssemblyTrapHandler, bool (*)(bool)) \
  X(CXXMethod, v8::V8::SetUnhandledExceptionCallback, void (*)(int (*)(_EXCEPTION_POINTERS *))) \
  X(CXXConstructor, v8::SnapshotCreator::SnapshotCreator, void (v8::SnapshotCreator::*)(v8::Isolate *, const long long *, v8::StartupData *)) \
  X(CXXConstructor, v8::SnapshotCreator::SnapshotCreator, void (v8::SnapshotCreator::*)(const long long *, v8::StartupData *)) \
  X(CXXDestructor, v8::SnapshotCreator::~SnapshotCreator, void (v8::SnapshotCreator::*)()) \
  X(CXXMethod, v8::SnapshotCreator::GetIsolate, v8::Isolate *(v8::SnapshotCreator::*)()) \
  X(CXXMethod, v8::SnapshotCreator::SetDefaultContext, void (v8::SnapshotCreator::*)(v8::Local<v8::Context>, v8::SerializeInternalFieldsCallback)) \
  X(CXXMethod, v8::SnapshotCreator::AddContext, unsigned long long (v8::SnapshotCreator::*)(v8::Local<v8::Context>, v8::SerializeInternalFieldsCallback)) \
  X(CXXMethod, v8::SnapshotCreator::AddTemplate, unsigned long long (v8::SnapshotCreator::*)(v8::Local<v8::Template>)) \
  X(CXXMethod, v8::SnapshotCreator::CreateBlob, v8::StartupData (v8::SnapshotCreator::*)(v8::SnapshotCreator::FunctionCodeHandling)) \
  X(CXXMethod, v8::Maybe<void>::IsNothing, bool (v8::Maybe<void>::*)() const) \
  X(CXXMethod, v8::Maybe<void>::IsJust, bool (v8::Maybe<void>::*)() const) \
  X(CXXMethod, v8::Maybe<void>::operator==, bool (v8::Maybe<void>::*)(const v8::Maybe<void> &) const) \
  X(CXXMethod, v8::Maybe<void>::operator!=, bool (v8::Maybe<void>::*)(const v8::Maybe<void> &) const) \
  X(CXXConstructor, v8::Maybe<void>::Maybe, void (v8::Maybe<void>::*)(const v8::Maybe<void> &)) \
  X(CXXConstructor, v8::Maybe<void>::Maybe, void (v8::Maybe<void>::*)(v8::Maybe<void> &&)) \
  X(CXXDestructor, v8::Maybe<void>::~Maybe, void (v8::Maybe<void>::*)()) \
  X(Function, v8::JustVoid, v8::Maybe<void> (*)()) \
  X(CXXConstructor, v8::TryCatch::TryCatch, void (v8::TryCatch::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::TryCatch::~TryCatch, void (v8::TryCatch::*)()) \
  X(CXXMethod, v8::TryCatch::HasCaught, bool (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::CanContinue, bool (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::HasTerminated, bool (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::ReThrow, v8::Local<v8::Value> (v8::TryCatch::*)()) \
  X(CXXMethod, v8::TryCatch::Exception, v8::Local<v8::Value> (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::StackTrace, v8::MaybeLocal<v8::Value> (v8::TryCatch::*)(v8::Local<v8::Context>) const) \
  X(CXXMethod, v8::TryCatch::Message, v8::Local<v8::Message> (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::Reset, void (v8::TryCatch::*)()) \
  X(CXXMethod, v8::TryCatch::SetVerbose, void (v8::TryCatch::*)(bool)) \
  X(CXXMethod, v8::TryCatch::IsVerbose, bool (v8::TryCatch::*)() const) \
  X(CXXMethod, v8::TryCatch::SetCaptureMessage, void (v8::TryCatch::*)(bool)) \
  X(CXXMethod, v8::TryCatch::JSStackComparableAddress, void *(*)(v8::TryCatch *)) \
  X(CXXConstructor, v8::ExtensionConfiguration::ExtensionConfiguration, void (v8::ExtensionConfiguration::*)()) \
  X(CXXConstructor, v8::ExtensionConfiguration::ExtensionConfiguration, void (v8::ExtensionConfiguration::*)(int, const char **)) \
  X(CXXMethod, v8::ExtensionConfiguration::begin, const char **(v8::ExtensionConfiguration::*)() const) \
  X(CXXMethod, v8::ExtensionConfiguration::end, const char **(v8::ExtensionConfiguration::*)() const) \
  X(CXXMethod, v8::Context::Global, v8::Local<v8::Object> (v8::Context::*)()) \
  X(CXXMethod, v8::Context::DetachGlobal, void (v8::Context::*)()) \
  X(CXXMethod, v8::Context::New, v8::Local<v8::Context> (*)(v8::Isolate *, v8::ExtensionConfiguration *, v8::MaybeLocal<v8::ObjectTemplate>, v8::MaybeLocal<v8::Value>, v8::DeserializeInternalFieldsCallback, v8::MicrotaskQueue *)) \
  X(CXXMethod, v8::Context::FromSnapshot, v8::MaybeLocal<v8::Context> (*)(v8::Isolate *, unsigned long long, v8::DeserializeInternalFieldsCallback, v8::ExtensionConfiguration *, v8::MaybeLocal<v8::Value>, v8::MicrotaskQueue *)) \
  X(CXXMethod, v8::Context::NewRemoteContext, v8::MaybeLocal<v8::Object> (*)(v8::Isolate *, v8::Local<v8::ObjectTemplate>, v8::MaybeLocal<v8::Value>)) \
  X(CXXMethod, v8::Context::SetSecurityToken, void (v8::Context::*)(v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Context::UseDefaultSecurityToken, void (v8::Context::*)()) \
  X(CXXMethod, v8::Context::GetSecurityToken, v8::Local<v8::Value> (v8::Context::*)()) \
  X(CXXMethod, v8::Context::Enter, void (v8::Context::*)()) \
  X(CXXMethod, v8::Context::Exit, void (v8::Context::*)()) \
  X(CXXMethod, v8::Context::GetIsolate, v8::Isolate *(v8::Context::*)()) \
  X(CXXMethod, v8::Context::GetNumberOfEmbedderDataFields, unsigned int (v8::Context::*)()) \
  X(CXXMethod, v8::Context::GetEmbedderData, v8::Local<v8::Value> (v8::Context::*)(int)) \
  X(CXXMethod, v8::Context::GetExtrasBindingObject, v8::Local<v8::Object> (v8::Context::*)()) \
  X(CXXMethod, v8::Context::SetEmbedderData, void (v8::Context::*)(int, v8::Local<v8::Value>)) \
  X(CXXMethod, v8::Context::GetAlignedPointerFromEmbedderData, void *(v8::Context::*)(int)) \
  X(CXXMethod, v8::Context::SetAlignedPointerInEmbedderData, void (v8::Context::*)(int, void *)) \
  X(CXXMethod, v8::Context::AllowCodeGenerationFromStrings, void (v8::Context::*)(bool)) \
  X(CXXMethod, v8::Context::IsCodeGenerationFromStringsAllowed, bool (v8::Context::*)()) \
  X(CXXMethod, v8::Context::SetErrorMessageForCodeGenerationFromStrings, void (v8::Context::*)(v8::Local<v8::String>)) \
  X(CXXMethod, v8::Context::SetAbortScriptExecution, void (v8::Context::*)(void (*)(v8::Isolate *, v8::Local<v8::Context>))) \
  X(CXXConstructor, v8::Context::Scope::Scope, void (v8::Context::Scope::*)(v8::Local<v8::Context>)) \
  X(CXXDestructor, v8::Context::Scope::~Scope, void (v8::Context::Scope::*)()) \
  X(CXXConstructor, v8::Context::BackupIncumbentScope::BackupIncumbentScope, void (v8::Context::BackupIncumbentScope::*)(v8::Local<v8::Context>)) \
  X(CXXDestructor, v8::Context::BackupIncumbentScope::~BackupIncumbentScope, void (v8::Context::BackupIncumbentScope::*)()) \
  X(CXXMethod, v8::Context::BackupIncumbentScope::JSStackComparableAddress, unsigned long long (v8::Context::BackupIncumbentScope::*)() const) \
  X(CXXConstructor, v8::Unlocker::Unlocker, void (v8::Unlocker::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::Unlocker::~Unlocker, void (v8::Unlocker::*)()) \
  X(CXXConstructor, v8::Locker::Locker, void (v8::Locker::*)(v8::Isolate *)) \
  X(CXXDestructor, v8::Locker::~Locker, void (v8::Locker::*)()) \
  X(CXXMethod, v8::Locker::IsLocked, bool (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Locker::IsActive, bool (*)()) \
  X(CXXMethod, v8::Unwinder::TryUnwindV8Frames, bool (*)(const v8::UnwindState &, v8::RegisterState *, const void *)) \
  X(CXXMethod, v8::Unwinder::PCIsInV8, bool (*)(const v8::UnwindState &, void *)) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, void (v8::ScriptOrigin::*)(v8::Local<v8::Value>, v8::Local<v8::Integer>, v8::Local<v8::Integer>, v8::Local<v8::Boolean>, v8::Local<v8::Integer>, v8::Local<v8::Value>, v8::Local<v8::Boolean>, v8::Local<v8::Boolean>, v8::Local<v8::Boolean>, v8::Local<v8::PrimitiveArray>)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceName, v8::Local<v8::Value> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::HostDefinedOptions, v8::Local<v8::PrimitiveArray> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ResourceLineOffset, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ResourceColumnOffset, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::ScriptID, v8::Local<v8::Integer> (v8::ScriptOrigin::*)() const) \
  X(CXXMethod, v8::ScriptOrigin::SourceMapUrl, v8::Local<v8::Value> (v8::ScriptOrigin::*)() const) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, void (v8::ScriptCompiler::Source::*)(v8::Local<v8::String>, const v8::ScriptOrigin &, v8::ScriptCompiler::CachedData *)) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, void (v8::ScriptCompiler::Source::*)(v8::Local<v8::String>, v8::ScriptCompiler::CachedData *)) \
  X(CXXDestructor, v8::ScriptCompiler::Source::~Source, void (v8::ScriptCompiler::Source::*)()) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetCachedData, const v8::ScriptCompiler::CachedData *(v8::ScriptCompiler::Source::*)() const) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetResourceOptions, const v8::ScriptOriginOptions &(v8::ScriptCompiler::Source::*)() const) \
  X(CXXMethod, v8::Boolean::New, v8::Local<v8::Boolean> (*)(v8::Isolate *, bool)) \
  X(CXXMethod, v8::Template::Set, void (v8::Template::*)(v8::Isolate *, const char *, v8::Local<v8::Data>)) \
  X(CXXMethod, v8::FunctionTemplate::Cast, v8::FunctionTemplate *(*)(v8::Data *)) \
  X(CXXMethod, v8::ObjectTemplate::Cast, v8::ObjectTemplate *(*)(v8::Data *)) \
  X(CXXMethod, v8::Signature::Cast, v8::Signature *(*)(v8::Data *)) \
  X(CXXMethod, v8::AccessorSignature::Cast, v8::AccessorSignature *(*)(v8::Data *)) \
  X(CXXMethod, v8::Object::GetInternalField, v8::Local<v8::Value> (v8::Object::*)(int)) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, void *(v8::Object::*)(int)) \
  X(CXXMethod, v8::String::Cast, v8::String *(*)(v8::Value *)) \
  X(CXXMethod, v8::String::Empty, v8::Local<v8::String> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::String::GetExternalStringResource, v8::String::ExternalStringResource *(v8::String::*)() const) \
  X(CXXMethod, v8::String::GetExternalStringResourceBase, v8::String::ExternalStringResourceBase *(v8::String::*)(v8::String::Encoding *) const) \
  X(CXXMethod, v8::Value::IsUndefined, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNull, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsNullOrUndefined, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Value::IsString, bool (v8::Value::*)() const) \
  X(CXXMethod, v8::Boolean::Cast, v8::Boolean *(*)(v8::Value *)) \
  X(CXXMethod, v8::Name::Cast, v8::Name *(*)(v8::Value *)) \
  X(CXXMethod, v8::Symbol::Cast, v8::Symbol *(*)(v8::Value *)) \
  X(CXXMethod, v8::Private::Cast, v8::Private *(*)(v8::Data *)) \
  X(CXXMethod, v8::Number::Cast, v8::Number *(*)(v8::Value *)) \
  X(CXXMethod, v8::Integer::Cast, v8::Integer *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int32::Cast, v8::Int32 *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint32::Cast, v8::Uint32 *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigInt::Cast, v8::BigInt *(*)(v8::Value *)) \
  X(CXXMethod, v8::Date::Cast, v8::Date *(*)(v8::Value *)) \
  X(CXXMethod, v8::StringObject::Cast, v8::StringObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::SymbolObject::Cast, v8::SymbolObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::NumberObject::Cast, v8::NumberObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigIntObject::Cast, v8::BigIntObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::BooleanObject::Cast, v8::BooleanObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::RegExp::Cast, v8::RegExp *(*)(v8::Value *)) \
  X(CXXMethod, v8::Object::Cast, v8::Object *(*)(v8::Value *)) \
  X(CXXMethod, v8::Array::Cast, v8::Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Map::Cast, v8::Map *(*)(v8::Value *)) \
  X(CXXMethod, v8::Set::Cast, v8::Set *(*)(v8::Value *)) \
  X(CXXMethod, v8::Promise::Cast, v8::Promise *(*)(v8::Value *)) \
  X(CXXMethod, v8::Proxy::Cast, v8::Proxy *(*)(v8::Value *)) \
  X(CXXMethod, v8::WasmModuleObject::Cast, v8::WasmModuleObject *(*)(v8::Value *)) \
  X(CXXMethod, v8::Promise::Resolver::Cast, v8::Promise::Resolver *(*)(v8::Value *)) \
  X(CXXMethod, v8::ArrayBuffer::Cast, v8::ArrayBuffer *(*)(v8::Value *)) \
  X(CXXMethod, v8::ArrayBufferView::Cast, v8::ArrayBufferView *(*)(v8::Value *)) \
  X(CXXMethod, v8::TypedArray::Cast, v8::TypedArray *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint8Array::Cast, v8::Uint8Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int8Array::Cast, v8::Int8Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint16Array::Cast, v8::Uint16Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int16Array::Cast, v8::Int16Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint32Array::Cast, v8::Uint32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Int32Array::Cast, v8::Int32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Float32Array::Cast, v8::Float32Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Float64Array::Cast, v8::Float64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigInt64Array::Cast, v8::BigInt64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::BigUint64Array::Cast, v8::BigUint64Array *(*)(v8::Value *)) \
  X(CXXMethod, v8::Uint8ClampedArray::Cast, v8::Uint8ClampedArray *(*)(v8::Value *)) \
  X(CXXMethod, v8::DataView::Cast, v8::DataView *(*)(v8::Value *)) \
  X(CXXMethod, v8::SharedArrayBuffer::Cast, v8::SharedArrayBuffer *(*)(v8::Value *)) \
  X(CXXMethod, v8::Function::Cast, v8::Function *(*)(v8::Value *)) \
  X(CXXMethod, v8::External::Cast, v8::External *(*)(v8::Value *)) \
  X(Function, v8::Undefined, v8::Local<v8::Primitive> (*)(v8::Isolate *)) \
  X(Function, v8::Null, v8::Local<v8::Primitive> (*)(v8::Isolate *)) \
  X(Function, v8::True, v8::Local<v8::Boolean> (*)(v8::Isolate *)) \
  X(Function, v8::False, v8::Local<v8::Boolean> (*)(v8::Isolate *)) \
  X(CXXMethod, v8::Isolate::SetData, void (v8::Isolate::*)(unsigned int, void *)) \
  X(CXXMethod, v8::Isolate::GetData, void *(v8::Isolate::*)(unsigned int)) \
  X(CXXMethod, v8::Isolate::GetNumberOfDataSlots, unsigned int (*)()) \
  X(CXXMethod, v8::Isolate::AdjustAmountOfExternalAllocatedMemory, long long (v8::Isolate::*)(long long)) \
  X(CXXMethod, v8::Context::GetEmbedderData, v8::Local<v8::Value> (v8::Context::*)(int)) \
  X(CXXMethod, v8::Context::GetAlignedPointerFromEmbedderData, void *(v8::Context::*)(int)) \
// Done: 0
