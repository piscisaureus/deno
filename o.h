#define DECLARATIONS(X) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, (void (class v8::Local<class v8::Primitive>))) \
  X(CXXMethod, v8::Local<v8::Primitive>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Primitive>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Primitive>::operator->, (class v8::Primitive *(void) const)) \
  X(CXXMethod, v8::Local<v8::Primitive>::operator*, (class v8::Primitive *(void) const)) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, (class v8::Local<class v8::Primitive> (class v8::Isolate *, class v8::Local<class v8::Primitive>))) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, (class v8::Local<class v8::Primitive> (class v8::Isolate *, const class v8::PersistentBase<class v8::Primitive> &))) \
  X(CXXMethod, v8::Local<v8::Primitive>::New, (class v8::Local<class v8::Primitive> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Primitive> &))) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, (void (const class v8::Local<class v8::Primitive> &))) \
  X(CXXConstructor, v8::Local<v8::Primitive>::Local, (void (class v8::Local<class v8::Primitive> &&))) \
  X(CXXDestructor, v8::Local<v8::Primitive>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, (void (class v8::Local<class v8::Boolean>))) \
  X(CXXMethod, v8::Local<v8::Boolean>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Boolean>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Boolean>::operator->, (class v8::Boolean *(void) const)) \
  X(CXXMethod, v8::Local<v8::Boolean>::operator*, (class v8::Boolean *(void) const)) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, (class v8::Local<class v8::Boolean> (class v8::Isolate *, class v8::Local<class v8::Boolean>))) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, (class v8::Local<class v8::Boolean> (class v8::Isolate *, const class v8::PersistentBase<class v8::Boolean> &))) \
  X(CXXMethod, v8::Local<v8::Boolean>::New, (class v8::Local<class v8::Boolean> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Boolean> &))) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, (void (const class v8::Local<class v8::Boolean> &))) \
  X(CXXConstructor, v8::Local<v8::Boolean>::Local, (void (class v8::Local<class v8::Boolean> &&))) \
  X(CXXDestructor, v8::Local<v8::Boolean>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, (void (class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Local<v8::Value>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Value>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Value>::operator->, (class v8::Value *(void) const)) \
  X(CXXMethod, v8::Local<v8::Value>::operator*, (class v8::Value *(void) const)) \
  X(CXXMethod, v8::Local<v8::Value>::New, (class v8::Local<class v8::Value> (class v8::Isolate *, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Local<v8::Value>::New, (class v8::Local<class v8::Value> (class v8::Isolate *, const class v8::PersistentBase<class v8::Value> &))) \
  X(CXXMethod, v8::Local<v8::Value>::New, (class v8::Local<class v8::Value> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Value> &))) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, (void (const class v8::Local<class v8::Value> &))) \
  X(CXXConstructor, v8::Local<v8::Value>::Local, (void (class v8::Local<class v8::Value> &&))) \
  X(CXXDestructor, v8::Local<v8::Value>::~Local, (void (void))) \
  X(CXXMethod, v8::Local<v8::Value>::operator=, (class v8::Local<class v8::Value> &(const class v8::Local<class v8::Value> &))) \
  X(CXXMethod, v8::Local<v8::Value>::operator=, (class v8::Local<class v8::Value> &(class v8::Local<class v8::Value> &&))) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, (void (class v8::Local<class v8::PrimitiveArray>))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator->, (class v8::PrimitiveArray *(void) const)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator*, (class v8::PrimitiveArray *(void) const)) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, (class v8::Local<class v8::PrimitiveArray> (class v8::Isolate *, class v8::Local<class v8::PrimitiveArray>))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, (class v8::Local<class v8::PrimitiveArray> (class v8::Isolate *, const class v8::PersistentBase<class v8::PrimitiveArray> &))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::New, (class v8::Local<class v8::PrimitiveArray> (class v8::Isolate *, const class v8::TracedGlobal<class v8::PrimitiveArray> &))) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, (void (const class v8::Local<class v8::PrimitiveArray> &))) \
  X(CXXConstructor, v8::Local<v8::PrimitiveArray>::Local, (void (class v8::Local<class v8::PrimitiveArray> &&))) \
  X(CXXDestructor, v8::Local<v8::PrimitiveArray>::~Local, (void (void))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator=, (class v8::Local<class v8::PrimitiveArray> &(const class v8::Local<class v8::PrimitiveArray> &))) \
  X(CXXMethod, v8::Local<v8::PrimitiveArray>::operator=, (class v8::Local<class v8::PrimitiveArray> &(class v8::Local<class v8::PrimitiveArray> &&))) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, (void (class v8::Local<class v8::Integer>))) \
  X(CXXMethod, v8::Local<v8::Integer>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Integer>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Integer>::operator->, (class v8::Integer *(void) const)) \
  X(CXXMethod, v8::Local<v8::Integer>::operator*, (class v8::Integer *(void) const)) \
  X(CXXMethod, v8::Local<v8::Integer>::New, (class v8::Local<class v8::Integer> (class v8::Isolate *, class v8::Local<class v8::Integer>))) \
  X(CXXMethod, v8::Local<v8::Integer>::New, (class v8::Local<class v8::Integer> (class v8::Isolate *, const class v8::PersistentBase<class v8::Integer> &))) \
  X(CXXMethod, v8::Local<v8::Integer>::New, (class v8::Local<class v8::Integer> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Integer> &))) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, (void (const class v8::Local<class v8::Integer> &))) \
  X(CXXConstructor, v8::Local<v8::Integer>::Local, (void (class v8::Local<class v8::Integer> &&))) \
  X(CXXDestructor, v8::Local<v8::Integer>::~Local, (void (void))) \
  X(CXXMethod, v8::Local<v8::Integer>::operator=, (class v8::Local<class v8::Integer> &(const class v8::Local<class v8::Integer> &))) \
  X(CXXMethod, v8::Local<v8::Integer>::operator=, (class v8::Local<class v8::Integer> &(class v8::Local<class v8::Integer> &&))) \
  X(CXXConstructor, v8::Local<v8::String>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::String>::Local, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Local<v8::String>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::String>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::String>::operator->, (class v8::String *(void) const)) \
  X(CXXMethod, v8::Local<v8::String>::operator*, (class v8::String *(void) const)) \
  X(CXXMethod, v8::Local<v8::String>::New, (class v8::Local<class v8::String> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Local<v8::String>::New, (class v8::Local<class v8::String> (class v8::Isolate *, const class v8::PersistentBase<class v8::String> &))) \
  X(CXXMethod, v8::Local<v8::String>::New, (class v8::Local<class v8::String> (class v8::Isolate *, const class v8::TracedGlobal<class v8::String> &))) \
  X(CXXConstructor, v8::Local<v8::String>::Local, (void (const class v8::Local<class v8::String> &))) \
  X(CXXConstructor, v8::Local<v8::String>::Local, (void (class v8::Local<class v8::String> &&))) \
  X(CXXMethod, v8::Local<v8::String>::operator=, (class v8::Local<class v8::String> &(const class v8::Local<class v8::String> &))) \
  X(CXXMethod, v8::Local<v8::String>::operator=, (class v8::Local<class v8::String> &(class v8::Local<class v8::String> &&))) \
  X(CXXDestructor, v8::Local<v8::String>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, (void (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Local<v8::Context>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Context>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Context>::operator->, (class v8::Context *(void) const)) \
  X(CXXMethod, v8::Local<v8::Context>::operator*, (class v8::Context *(void) const)) \
  X(CXXMethod, v8::Local<v8::Context>::New, (class v8::Local<class v8::Context> (class v8::Isolate *, class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Local<v8::Context>::New, (class v8::Local<class v8::Context> (class v8::Isolate *, const class v8::PersistentBase<class v8::Context> &))) \
  X(CXXMethod, v8::Local<v8::Context>::New, (class v8::Local<class v8::Context> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Context> &))) \
  X(CXXDestructor, v8::Local<v8::Context>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, (void (const class v8::Local<class v8::Context> &))) \
  X(CXXConstructor, v8::Local<v8::Context>::Local, (void (class v8::Local<class v8::Context> &&))) \
  X(CXXConstructor, v8::Local<v8::UnboundScript>::Local, (void (void))) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::operator->, (class v8::UnboundScript *(void) const)) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::operator*, (class v8::UnboundScript *(void) const)) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, (class v8::Local<class v8::UnboundScript> (class v8::Isolate *, class v8::Local<class v8::UnboundScript>))) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, (class v8::Local<class v8::UnboundScript> (class v8::Isolate *, const class v8::PersistentBase<class v8::UnboundScript> &))) \
  X(CXXMethod, v8::Local<v8::UnboundScript>::New, (class v8::Local<class v8::UnboundScript> (class v8::Isolate *, const class v8::TracedGlobal<class v8::UnboundScript> &))) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, (void (class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Local<v8::Function>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Function>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Function>::operator->, (class v8::Function *(void) const)) \
  X(CXXMethod, v8::Local<v8::Function>::operator*, (class v8::Function *(void) const)) \
  X(CXXMethod, v8::Local<v8::Function>::New, (class v8::Local<class v8::Function> (class v8::Isolate *, class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Local<v8::Function>::New, (class v8::Local<class v8::Function> (class v8::Isolate *, const class v8::PersistentBase<class v8::Function> &))) \
  X(CXXMethod, v8::Local<v8::Function>::New, (class v8::Local<class v8::Function> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Function> &))) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, (void (const class v8::Local<class v8::Function> &))) \
  X(CXXConstructor, v8::Local<v8::Function>::Local, (void (class v8::Local<class v8::Function> &&))) \
  X(CXXDestructor, v8::Local<v8::Function>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, (void (class v8::Local<class v8::String>))) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, (void (class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Local<v8::Name>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Name>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Name>::operator->, (class v8::Name *(void) const)) \
  X(CXXMethod, v8::Local<v8::Name>::operator*, (class v8::Name *(void) const)) \
  X(CXXMethod, v8::Local<v8::Name>::New, (class v8::Local<class v8::Name> (class v8::Isolate *, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Local<v8::Name>::New, (class v8::Local<class v8::Name> (class v8::Isolate *, const class v8::PersistentBase<class v8::Name> &))) \
  X(CXXMethod, v8::Local<v8::Name>::New, (class v8::Local<class v8::Name> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Name> &))) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, (void (const class v8::Local<class v8::Name> &))) \
  X(CXXConstructor, v8::Local<v8::Name>::Local, (void (class v8::Local<class v8::Name> &&))) \
  X(CXXDestructor, v8::Local<v8::Name>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, (void (class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::operator->, (class v8::FunctionTemplate *(void) const)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::operator*, (class v8::FunctionTemplate *(void) const)) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, const class v8::PersistentBase<class v8::FunctionTemplate> &))) \
  X(CXXMethod, v8::Local<v8::FunctionTemplate>::New, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, const class v8::TracedGlobal<class v8::FunctionTemplate> &))) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, (void (const class v8::Local<class v8::FunctionTemplate> &))) \
  X(CXXConstructor, v8::Local<v8::FunctionTemplate>::Local, (void (class v8::Local<class v8::FunctionTemplate> &&))) \
  X(CXXDestructor, v8::Local<v8::FunctionTemplate>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, (void (class v8::Local<class v8::Promise>))) \
  X(CXXMethod, v8::Local<v8::Promise>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Promise>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Promise>::operator->, (class v8::Promise *(void) const)) \
  X(CXXMethod, v8::Local<v8::Promise>::operator*, (class v8::Promise *(void) const)) \
  X(CXXMethod, v8::Local<v8::Promise>::New, (class v8::Local<class v8::Promise> (class v8::Isolate *, class v8::Local<class v8::Promise>))) \
  X(CXXMethod, v8::Local<v8::Promise>::New, (class v8::Local<class v8::Promise> (class v8::Isolate *, const class v8::PersistentBase<class v8::Promise> &))) \
  X(CXXMethod, v8::Local<v8::Promise>::New, (class v8::Local<class v8::Promise> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Promise> &))) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, (void (const class v8::Local<class v8::Promise> &))) \
  X(CXXConstructor, v8::Local<v8::Promise>::Local, (void (class v8::Local<class v8::Promise> &&))) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, (void (class v8::Local<class v8::Data>))) \
  X(CXXMethod, v8::Local<v8::Data>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Data>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Data>::operator->, (class v8::Data *(void) const)) \
  X(CXXMethod, v8::Local<v8::Data>::operator*, (class v8::Data *(void) const)) \
  X(CXXMethod, v8::Local<v8::Data>::New, (class v8::Local<class v8::Data> (class v8::Isolate *, class v8::Local<class v8::Data>))) \
  X(CXXMethod, v8::Local<v8::Data>::New, (class v8::Local<class v8::Data> (class v8::Isolate *, const class v8::PersistentBase<class v8::Data> &))) \
  X(CXXMethod, v8::Local<v8::Data>::New, (class v8::Local<class v8::Data> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Data> &))) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, (void (const class v8::Local<class v8::Data> &))) \
  X(CXXConstructor, v8::Local<v8::Data>::Local, (void (class v8::Local<class v8::Data> &&))) \
  X(CXXDestructor, v8::Local<v8::Data>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, (void (class v8::Local<class v8::AccessorSignature>))) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::operator->, (class v8::AccessorSignature *(void) const)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::operator*, (class v8::AccessorSignature *(void) const)) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, (class v8::Local<class v8::AccessorSignature> (class v8::Isolate *, class v8::Local<class v8::AccessorSignature>))) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, (class v8::Local<class v8::AccessorSignature> (class v8::Isolate *, const class v8::PersistentBase<class v8::AccessorSignature> &))) \
  X(CXXMethod, v8::Local<v8::AccessorSignature>::New, (class v8::Local<class v8::AccessorSignature> (class v8::Isolate *, const class v8::TracedGlobal<class v8::AccessorSignature> &))) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, (void (const class v8::Local<class v8::AccessorSignature> &))) \
  X(CXXConstructor, v8::Local<v8::AccessorSignature>::Local, (void (class v8::Local<class v8::AccessorSignature> &&))) \
  X(CXXDestructor, v8::Local<v8::AccessorSignature>::~Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, (void (void))) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, (void (class v8::Local<class v8::Signature>))) \
  X(CXXMethod, v8::Local<v8::Signature>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local<v8::Signature>::Clear, (void (void))) \
  X(CXXMethod, v8::Local<v8::Signature>::operator->, (class v8::Signature *(void) const)) \
  X(CXXMethod, v8::Local<v8::Signature>::operator*, (class v8::Signature *(void) const)) \
  X(CXXMethod, v8::Local<v8::Signature>::New, (class v8::Local<class v8::Signature> (class v8::Isolate *, class v8::Local<class v8::Signature>))) \
  X(CXXMethod, v8::Local<v8::Signature>::New, (class v8::Local<class v8::Signature> (class v8::Isolate *, const class v8::PersistentBase<class v8::Signature> &))) \
  X(CXXMethod, v8::Local<v8::Signature>::New, (class v8::Local<class v8::Signature> (class v8::Isolate *, const class v8::TracedGlobal<class v8::Signature> &))) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, (void (const class v8::Local<class v8::Signature> &))) \
  X(CXXConstructor, v8::Local<v8::Signature>::Local, (void (class v8::Local<class v8::Signature> &&))) \
  X(CXXDestructor, v8::Local<v8::Signature>::~Local, (void (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, (void (void))) \
  X(CXXMethod, v8::MaybeLocal<v8::Value>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::MaybeLocal<v8::Value>::ToLocalChecked, (class v8::Local<class v8::Value> (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, (void (const class v8::MaybeLocal<class v8::Value> &))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Value>::MaybeLocal, (void (class v8::MaybeLocal<class v8::Value> &&))) \
  X(CXXDestructor, v8::MaybeLocal<v8::Value>::~MaybeLocal, (void (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::String>::MaybeLocal, (void (void))) \
  X(CXXMethod, v8::MaybeLocal<v8::String>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::MaybeLocal<v8::String>::ToLocalChecked, (class v8::Local<class v8::String> (void))) \
  X(CXXDestructor, v8::MaybeLocal<v8::String>::~MaybeLocal, (void (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, (void (void))) \
  X(CXXMethod, v8::MaybeLocal<v8::Object>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::MaybeLocal<v8::Object>::ToLocalChecked, (class v8::Local<class v8::Object> (void))) \
  X(CXXDestructor, v8::MaybeLocal<v8::Object>::~MaybeLocal, (void (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, (void (const class v8::MaybeLocal<class v8::Object> &))) \
  X(CXXConstructor, v8::MaybeLocal<v8::Object>::MaybeLocal, (void (class v8::MaybeLocal<class v8::Object> &&))) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, (void (void))) \
  X(CXXMethod, v8::MaybeLocal<v8::ObjectTemplate>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::MaybeLocal<v8::ObjectTemplate>::ToLocalChecked, (class v8::Local<class v8::ObjectTemplate> (void))) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, (void (const class v8::MaybeLocal<class v8::ObjectTemplate> &))) \
  X(CXXConstructor, v8::MaybeLocal<v8::ObjectTemplate>::MaybeLocal, (void (class v8::MaybeLocal<class v8::ObjectTemplate> &&))) \
  X(CXXDestructor, v8::MaybeLocal<v8::ObjectTemplate>::~MaybeLocal, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Reset, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Empty, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::Get, (class v8::Local<class v8::Object> (class v8::Isolate *) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::SetWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::ClearWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::AnnotateStrongRetainer, (void (const char *))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::IsWeak, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::WrapperClassId, (unsigned short (void) const)) \
  X(CXXConstructor, v8::PersistentBase<v8::Object>::PersistentBase, (void (const class v8::PersistentBase<class v8::Object> &))) \
  X(CXXMethod, v8::PersistentBase<v8::Object>::operator=, (void (const class v8::PersistentBase<class v8::Object> &))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Reset, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Empty, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::Get, (class v8::Local<class v8::Promise> (class v8::Isolate *) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::SetWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::ClearWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::AnnotateStrongRetainer, (void (const char *))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::IsWeak, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::WrapperClassId, (unsigned short (void) const)) \
  X(CXXConstructor, v8::PersistentBase<v8::Promise>::PersistentBase, (void (const class v8::PersistentBase<class v8::Promise> &))) \
  X(CXXMethod, v8::PersistentBase<v8::Promise>::operator=, (void (const class v8::PersistentBase<class v8::Promise> &))) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, (void (void))) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, (void (const class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &))) \
  X(CXXConstructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::Persistent, (void (const class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &))) \
  X(CXXMethod, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::operator=, (class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &(const class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &))) \
  X(CXXMethod, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::operator=, (class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &(const class v8::Persistent<class v8::Promise, struct v8::CopyablePersistentTraits<class v8::Promise> > &))) \
  X(CXXDestructor, v8::Persistent<v8::Promise, v8::CopyablePersistentTraits<v8::Promise> >::~Persistent, (void (void))) \
  X(CXXConstructor, v8::TracedGlobal<v8::Object>::TracedGlobal, (void (void))) \
  X(CXXDestructor, v8::TracedGlobal<v8::Object>::~TracedGlobal, (void (void))) \
  X(CXXConstructor, v8::TracedGlobal<v8::Object>::TracedGlobal, (void (class v8::TracedGlobal<class v8::Object> &&))) \
  X(CXXConstructor, v8::TracedGlobal<v8::Object>::TracedGlobal, (void (const class v8::TracedGlobal<class v8::Object> &))) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::operator=, (void (const class v8::TracedGlobal<class v8::Object> &))) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::Reset, (void (void))) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::Get, (class v8::Local<class v8::Object> (class v8::Isolate *) const)) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::WrapperClassId, (unsigned short (void) const)) \
  X(CXXMethod, v8::TracedGlobal<v8::Object>::SetFinalizationCallback, (void (void *, void (*)(const class v8::WeakCallbackInfo<void> &)))) \
  X(CXXConstructor, v8::Local::Local<T>, (void (void))) \
  X(CXXMethod, v8::Local::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::Local::Clear, (void (void))) \
  X(CXXConstructor, v8::MaybeLocal::MaybeLocal<T>, (void (void))) \
  X(CXXMethod, v8::MaybeLocal::IsEmpty, (_Bool (void) const)) \
  X(CXXConstructor, v8::Eternal::Eternal<T>, (void (void))) \
  X(CXXMethod, v8::Eternal::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::WeakCallbackInfo::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::WeakCallbackInfo::GetInternalField, (void *(int) const)) \
  X(CXXConstructor, v8::WeakCallbackInfo<void>::WeakCallbackInfo, (void (class v8::Isolate *, void *, void **, void (**)(const class v8::WeakCallbackInfo<void> &)))) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetParameter, (void *(void) const)) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::GetInternalField, (void *(int) const)) \
  X(CXXMethod, v8::WeakCallbackInfo<void>::SetSecondPassCallback, (void (void (*)(const class v8::WeakCallbackInfo<void> &)) const)) \
  X(CXXMethod, v8::PersistentBase::Reset, (void (void))) \
  X(CXXMethod, v8::PersistentBase::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase::Empty, (void (void))) \
  X(CXXMethod, v8::PersistentBase::SetWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase::ClearWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase::AnnotateStrongRetainer, (void (const char *))) \
  X(CXXMethod, v8::PersistentBase::IsWeak, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::PersistentBase::WrapperClassId, (unsigned short (void) const)) \
  X(CXXMethod, v8::NonCopyablePersistentTraits::Uncompilable, (void (void))) \
  X(CXXConstructor, v8::Persistent::Persistent<T, M>, (void (void))) \
  X(CXXDestructor, v8::Persistent::~Persistent<T, M>, (void (void))) \
  X(CXXConstructor, v8::Global::Global<T>, (void (void))) \
  X(CXXDestructor, v8::Global::~Global<T>, (void (void))) \
  X(CXXConstructor, v8::TracedGlobal::TracedGlobal<T>, (void (void))) \
  X(CXXDestructor, v8::TracedGlobal::~TracedGlobal<T>, (void (void))) \
  X(CXXMethod, v8::TracedGlobal::IsEmpty, (_Bool (void) const)) \
  X(CXXMethod, v8::TracedGlobal::Reset, (void (void))) \
  X(CXXMethod, v8::TracedGlobal::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::TracedGlobal::WrapperClassId, (unsigned short (void) const)) \
  X(CXXMethod, v8::TracedGlobal::SetFinalizationCallback, (void (void *, void (*)(const class v8::WeakCallbackInfo<void> &)))) \
  X(CXXConstructor, v8::HandleScope::HandleScope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::HandleScope::~HandleScope, (void (void))) \
  X(CXXMethod, v8::HandleScope::NumberOfHandles, (int (class v8::Isolate *))) \
  X(CXXMethod, v8::HandleScope::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXConstructor, v8::HandleScope::HandleScope, (void (const class v8::HandleScope &))) \
  X(CXXMethod, v8::HandleScope::operator=, (void (const class v8::HandleScope &))) \
  X(CXXConstructor, v8::EscapableHandleScope::EscapableHandleScope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::EscapableHandleScope::~EscapableHandleScope, (void (void))) \
  X(CXXConstructor, v8::EscapableHandleScope::EscapableHandleScope, (void (const class v8::EscapableHandleScope &))) \
  X(CXXMethod, v8::EscapableHandleScope::operator=, (void (const class v8::EscapableHandleScope &))) \
  X(CXXConstructor, v8::SealHandleScope::SealHandleScope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::SealHandleScope::~SealHandleScope, (void (void))) \
  X(CXXConstructor, v8::SealHandleScope::SealHandleScope, (void (const class v8::SealHandleScope &))) \
  X(CXXMethod, v8::SealHandleScope::operator=, (void (const class v8::SealHandleScope &))) \
  X(CXXMethod, v8::ScriptOrModule::GetResourceName, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::ScriptOrModule::GetHostDefinedOptions, (class v8::Local<class v8::PrimitiveArray> (void))) \
  X(CXXMethod, v8::PrimitiveArray::New, (class v8::Local<class v8::PrimitiveArray> (class v8::Isolate *, int))) \
  X(CXXMethod, v8::PrimitiveArray::Length, (int (void) const)) \
  X(CXXMethod, v8::PrimitiveArray::Set, (void (class v8::Isolate *, int, class v8::Local<class v8::Primitive>))) \
  X(CXXMethod, v8::PrimitiveArray::Get, (class v8::Local<class v8::Primitive> (class v8::Isolate *, int))) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, (void (_Bool, _Bool, _Bool, _Bool))) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, (void (int))) \
  X(CXXMethod, v8::ScriptOriginOptions::IsSharedCrossOrigin, (_Bool (void) const)) \
  X(CXXMethod, v8::ScriptOriginOptions::IsOpaque, (_Bool (void) const)) \
  X(CXXMethod, v8::ScriptOriginOptions::IsWasm, (_Bool (void) const)) \
  X(CXXMethod, v8::ScriptOriginOptions::IsModule, (_Bool (void) const)) \
  X(CXXMethod, v8::ScriptOriginOptions::Flags, (int (void) const)) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, (void (const class v8::ScriptOriginOptions &))) \
  X(CXXConstructor, v8::ScriptOriginOptions::ScriptOriginOptions, (void (class v8::ScriptOriginOptions &&))) \
  X(CXXDestructor, v8::ScriptOriginOptions::~ScriptOriginOptions, (void (void))) \
  X(CXXMethod, v8::ScriptOriginOptions::operator=, (class v8::ScriptOriginOptions &(const class v8::ScriptOriginOptions &))) \
  X(CXXMethod, v8::ScriptOriginOptions::operator=, (class v8::ScriptOriginOptions &(class v8::ScriptOriginOptions &&))) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, (void (class v8::Local<class v8::Value>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Value>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::PrimitiveArray>))) \
  X(CXXMethod, v8::ScriptOrigin::ResourceName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceLineOffset, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceColumnOffset, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ScriptID, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::SourceMapUrl, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::HostDefinedOptions, (class v8::Local<class v8::PrimitiveArray> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::Options, (class v8::ScriptOriginOptions (void) const)) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, (void (const class v8::ScriptOrigin &))) \
  X(CXXMethod, v8::ScriptOrigin::operator=, (class v8::ScriptOrigin &(class v8::ScriptOrigin &&))) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, (void (class v8::ScriptOrigin &&))) \
  X(CXXMethod, v8::UnboundScript::BindToCurrentContext, (class v8::Local<class v8::Script> (void))) \
  X(CXXMethod, v8::UnboundScript::GetId, (int (void))) \
  X(CXXMethod, v8::UnboundScript::GetScriptName, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::UnboundScript::GetSourceURL, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::UnboundScript::GetSourceMappingURL, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::UnboundScript::GetLineNumber, (int (int))) \
  X(CXXMethod, v8::Location::GetLineNumber, (int (void))) \
  X(CXXMethod, v8::Location::GetColumnNumber, (int (void))) \
  X(CXXConstructor, v8::Location::Location, (void (int, int))) \
  X(CXXMethod, v8::Module::GetStatus, (enum v8::Module::Status (void) const)) \
  X(CXXMethod, v8::Module::GetException, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Module::GetModuleRequestsLength, (int (void) const)) \
  X(CXXMethod, v8::Module::GetModuleRequest, (class v8::Local<class v8::String> (int) const)) \
  X(CXXMethod, v8::Module::GetModuleRequestLocation, (class v8::Location (int) const)) \
  X(CXXMethod, v8::Module::GetIdentityHash, (int (void) const)) \
  X(CXXMethod, v8::Module::InstantiateModule, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::MaybeLocal<class v8::Module> (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::String>, class v8::Local<class v8::Module>)))) \
  X(CXXMethod, v8::Module::Evaluate, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Module::GetModuleNamespace, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Module::GetUnboundModuleScript, (class v8::Local<class v8::UnboundModuleScript> (void))) \
  X(CXXMethod, v8::Script::Compile, (class v8::MaybeLocal<class v8::Script> (class v8::Local<class v8::Context>, class v8::Local<class v8::String>, class v8::ScriptOrigin *))) \
  X(CXXMethod, v8::Script::Run, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Script::GetUnboundScript, (class v8::Local<class v8::UnboundScript> (void))) \
  X(CXXConstructor, v8::ScriptCompiler::CachedData::CachedData, (void (void))) \
  X(CXXConstructor, v8::ScriptCompiler::CachedData::CachedData, (void (const unsigned char *, int, enum v8::ScriptCompiler::CachedData::BufferPolicy))) \
  X(CXXDestructor, v8::ScriptCompiler::CachedData::~CachedData, (void (void))) \
  X(CXXConstructor, v8::ScriptCompiler::CachedData::CachedData, (void (const struct v8::ScriptCompiler::CachedData &))) \
  X(CXXMethod, v8::ScriptCompiler::CachedData::operator=, (struct v8::ScriptCompiler::CachedData &(const struct v8::ScriptCompiler::CachedData &))) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, (void (class v8::Local<class v8::String>, const class v8::ScriptOrigin &, struct v8::ScriptCompiler::CachedData *))) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, (void (class v8::Local<class v8::String>, struct v8::ScriptCompiler::CachedData *))) \
  X(CXXDestructor, v8::ScriptCompiler::Source::~Source, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetCachedData, (const struct v8::ScriptCompiler::CachedData *(void) const)) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetResourceOptions, (const class v8::ScriptOriginOptions &(void) const)) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, (void (const class v8::ScriptCompiler::Source &))) \
  X(CXXMethod, v8::ScriptCompiler::Source::operator=, (class v8::ScriptCompiler::Source &(const class v8::ScriptCompiler::Source &))) \
  X(CXXDestructor, v8::ScriptCompiler::ExternalSourceStream::~ExternalSourceStream, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::GetMoreData, (unsigned long long (const unsigned char **))) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::SetBookmark, (_Bool (void))) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::ResetToBookmark, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::ExternalSourceStream::operator=, (class v8::ScriptCompiler::ExternalSourceStream &(const class v8::ScriptCompiler::ExternalSourceStream &))) \
  X(CXXConstructor, v8::ScriptCompiler::StreamedSource::StreamedSource, (void (class v8::ScriptCompiler::ExternalSourceStream *, enum v8::ScriptCompiler::StreamedSource::Encoding))) \
  X(CXXConstructor, v8::ScriptCompiler::StreamedSource::StreamedSource, (void (class std::unique_ptr<class v8::ScriptCompiler::ExternalSourceStream, struct std::default_delete<class v8::ScriptCompiler::ExternalSourceStream> >, enum v8::ScriptCompiler::StreamedSource::Encoding))) \
  X(CXXDestructor, v8::ScriptCompiler::StreamedSource::~StreamedSource, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::StreamedSource::impl, (struct v8::internal::ScriptStreamingData *(void) const)) \
  X(CXXConstructor, v8::ScriptCompiler::StreamedSource::StreamedSource, (void (const class v8::ScriptCompiler::StreamedSource &))) \
  X(CXXMethod, v8::ScriptCompiler::StreamedSource::operator=, (class v8::ScriptCompiler::StreamedSource &(const class v8::ScriptCompiler::StreamedSource &))) \
  X(CXXMethod, v8::ScriptCompiler::ScriptStreamingTask::Run, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::CompileUnboundScript, (class v8::MaybeLocal<class v8::UnboundScript> (class v8::Isolate *, class v8::ScriptCompiler::Source *, enum v8::ScriptCompiler::CompileOptions, enum v8::ScriptCompiler::NoCacheReason))) \
  X(CXXMethod, v8::ScriptCompiler::Compile, (class v8::MaybeLocal<class v8::Script> (class v8::Local<class v8::Context>, class v8::ScriptCompiler::Source *, enum v8::ScriptCompiler::CompileOptions, enum v8::ScriptCompiler::NoCacheReason))) \
  X(CXXMethod, v8::ScriptCompiler::StartStreamingScript, (class v8::ScriptCompiler::ScriptStreamingTask *(class v8::Isolate *, class v8::ScriptCompiler::StreamedSource *, enum v8::ScriptCompiler::CompileOptions))) \
  X(CXXMethod, v8::ScriptCompiler::Compile, (class v8::MaybeLocal<class v8::Script> (class v8::Local<class v8::Context>, class v8::ScriptCompiler::StreamedSource *, class v8::Local<class v8::String>, const class v8::ScriptOrigin &))) \
  X(CXXMethod, v8::ScriptCompiler::CachedDataVersionTag, (unsigned int (void))) \
  X(CXXMethod, v8::ScriptCompiler::CompileModule, (class v8::MaybeLocal<class v8::Module> (class v8::Isolate *, class v8::ScriptCompiler::Source *, enum v8::ScriptCompiler::CompileOptions, enum v8::ScriptCompiler::NoCacheReason))) \
  X(CXXMethod, v8::ScriptCompiler::CompileFunctionInContext, (class v8::MaybeLocal<class v8::Function> (class v8::Local<class v8::Context>, class v8::ScriptCompiler::Source *, unsigned long long, class v8::Local<class v8::String> *, unsigned long long, class v8::Local<class v8::Object> *, enum v8::ScriptCompiler::CompileOptions, enum v8::ScriptCompiler::NoCacheReason))) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCache, (struct v8::ScriptCompiler::CachedData *(class v8::Local<class v8::UnboundScript>))) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCache, (struct v8::ScriptCompiler::CachedData *(class v8::Local<class v8::UnboundModuleScript>))) \
  X(CXXMethod, v8::ScriptCompiler::CreateCodeCacheForFunction, (struct v8::ScriptCompiler::CachedData *(class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Message::Get, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::Message::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::Message::GetSourceLine, (class v8::MaybeLocal<class v8::String> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Message::GetScriptOrigin, (class v8::ScriptOrigin (void) const)) \
  X(CXXMethod, v8::Message::GetScriptResourceName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Message::GetStackTrace, (class v8::Local<class v8::StackTrace> (void) const)) \
  X(CXXMethod, v8::Message::GetLineNumber, (class v8::Maybe<int> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Message::GetStartPosition, (int (void) const)) \
  X(CXXMethod, v8::Message::GetEndPosition, (int (void) const)) \
  X(CXXMethod, v8::Message::ErrorLevel, (int (void) const)) \
  X(CXXMethod, v8::Message::GetStartColumn, (int (void) const)) \
  X(CXXMethod, v8::Message::GetStartColumn, (class v8::Maybe<int> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Message::GetEndColumn, (int (void) const)) \
  X(CXXMethod, v8::Message::GetEndColumn, (class v8::Maybe<int> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Message::IsSharedCrossOrigin, (_Bool (void) const)) \
  X(CXXMethod, v8::Message::IsOpaque, (_Bool (void) const)) \
  X(CXXMethod, v8::Message::PrintCurrentStackTrace, (void (class v8::Isolate *, struct _iobuf *))) \
  X(CXXMethod, v8::StackTrace::GetFrame, (class v8::Local<class v8::StackFrame> (class v8::Isolate *, unsigned int) const)) \
  X(CXXMethod, v8::StackTrace::GetFrameCount, (int (void) const)) \
  X(CXXMethod, v8::StackTrace::CurrentStackTrace, (class v8::Local<class v8::StackTrace> (class v8::Isolate *, int, enum v8::StackTrace::StackTraceOptions))) \
  X(CXXMethod, v8::StackFrame::GetLineNumber, (int (void) const)) \
  X(CXXMethod, v8::StackFrame::GetColumn, (int (void) const)) \
  X(CXXMethod, v8::StackFrame::GetScriptId, (int (void) const)) \
  X(CXXMethod, v8::StackFrame::GetScriptName, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::StackFrame::GetScriptNameOrSourceURL, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::StackFrame::GetFunctionName, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::StackFrame::IsEval, (_Bool (void) const)) \
  X(CXXMethod, v8::StackFrame::IsConstructor, (_Bool (void) const)) \
  X(CXXMethod, v8::StackFrame::IsWasm, (_Bool (void) const)) \
  X(CXXMethod, v8::StackFrame::IsUserJavaScript, (_Bool (void) const)) \
  X(CXXConstructor, v8::RegisterState::RegisterState, (void (void))) \
  X(CXXMethod, v8::JSON::Parse, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::JSON::Stringify, (class v8::MaybeLocal<class v8::String> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, class v8::Local<class v8::String>))) \
  X(CXXDestructor, v8::ValueSerializer::Delegate::~Delegate, (void (void))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::ThrowDataCloneError, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::WriteHostObject, (class v8::Maybe<_Bool> (class v8::Isolate *, class v8::Local<class v8::Object>))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::GetSharedArrayBufferId, (class v8::Maybe<unsigned int> (class v8::Isolate *, class v8::Local<class v8::SharedArrayBuffer>))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::GetWasmModuleTransferId, (class v8::Maybe<unsigned int> (class v8::Isolate *, class v8::Local<class v8::WasmModuleObject>))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::ReallocateBufferMemory, (void *(void *, unsigned long long, unsigned long long *))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::FreeBufferMemory, (void (void *))) \
  X(CXXMethod, v8::ValueSerializer::Delegate::operator=, (class v8::ValueSerializer::Delegate &(const class v8::ValueSerializer::Delegate &))) \
  X(CXXConstructor, v8::ValueSerializer::ValueSerializer, (void (class v8::Isolate *))) \
  X(CXXConstructor, v8::ValueSerializer::ValueSerializer, (void (class v8::Isolate *, class v8::ValueSerializer::Delegate *))) \
  X(CXXDestructor, v8::ValueSerializer::~ValueSerializer, (void (void))) \
  X(CXXMethod, v8::ValueSerializer::WriteHeader, (void (void))) \
  X(CXXMethod, v8::ValueSerializer::WriteValue, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::ValueSerializer::Release, (struct std::pair<unsigned char *, unsigned long long> (void))) \
  X(CXXMethod, v8::ValueSerializer::TransferArrayBuffer, (void (unsigned int, class v8::Local<class v8::ArrayBuffer>))) \
  X(CXXMethod, v8::ValueSerializer::SetTreatArrayBufferViewsAsHostObjects, (void (_Bool))) \
  X(CXXMethod, v8::ValueSerializer::WriteUint32, (void (unsigned int))) \
  X(CXXMethod, v8::ValueSerializer::WriteUint64, (void (unsigned long long))) \
  X(CXXMethod, v8::ValueSerializer::WriteDouble, (void (double))) \
  X(CXXMethod, v8::ValueSerializer::WriteRawBytes, (void (const void *, unsigned long long))) \
  X(CXXConstructor, v8::ValueSerializer::ValueSerializer, (void (const class v8::ValueSerializer &))) \
  X(CXXMethod, v8::ValueSerializer::operator=, (void (const class v8::ValueSerializer &))) \
  X(CXXDestructor, v8::ValueDeserializer::Delegate::~Delegate, (void (void))) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::ReadHostObject, (class v8::MaybeLocal<class v8::Object> (class v8::Isolate *))) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::GetWasmModuleFromId, (class v8::MaybeLocal<class v8::WasmModuleObject> (class v8::Isolate *, unsigned int))) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::GetSharedArrayBufferFromId, (class v8::MaybeLocal<class v8::SharedArrayBuffer> (class v8::Isolate *, unsigned int))) \
  X(CXXMethod, v8::ValueDeserializer::Delegate::operator=, (class v8::ValueDeserializer::Delegate &(const class v8::ValueDeserializer::Delegate &))) \
  X(CXXConstructor, v8::ValueDeserializer::ValueDeserializer, (void (class v8::Isolate *, const unsigned char *, unsigned long long))) \
  X(CXXConstructor, v8::ValueDeserializer::ValueDeserializer, (void (class v8::Isolate *, const unsigned char *, unsigned long long, class v8::ValueDeserializer::Delegate *))) \
  X(CXXDestructor, v8::ValueDeserializer::~ValueDeserializer, (void (void))) \
  X(CXXMethod, v8::ValueDeserializer::ReadHeader, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::ValueDeserializer::ReadValue, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::ValueDeserializer::TransferArrayBuffer, (void (unsigned int, class v8::Local<class v8::ArrayBuffer>))) \
  X(CXXMethod, v8::ValueDeserializer::TransferSharedArrayBuffer, (void (unsigned int, class v8::Local<class v8::SharedArrayBuffer>))) \
  X(CXXMethod, v8::ValueDeserializer::SetSupportsLegacyWireFormat, (void (_Bool))) \
  X(CXXMethod, v8::ValueDeserializer::SetExpectInlineWasm, (void (_Bool))) \
  X(CXXMethod, v8::ValueDeserializer::GetWireFormatVersion, (unsigned int (void) const)) \
  X(CXXMethod, v8::ValueDeserializer::ReadUint32, (_Bool (unsigned int *))) \
  X(CXXMethod, v8::ValueDeserializer::ReadUint64, (_Bool (unsigned long long *))) \
  X(CXXMethod, v8::ValueDeserializer::ReadDouble, (_Bool (double *))) \
  X(CXXMethod, v8::ValueDeserializer::ReadRawBytes, (_Bool (unsigned long long, const void **))) \
  X(CXXConstructor, v8::ValueDeserializer::ValueDeserializer, (void (const class v8::ValueDeserializer &))) \
  X(CXXMethod, v8::ValueDeserializer::operator=, (void (const class v8::ValueDeserializer &))) \
  X(CXXMethod, v8::Value::IsUndefined, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNull, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNullOrUndefined, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsTrue, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsFalse, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsName, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsString, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsSymbol, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsFunction, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsArray, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBigInt, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBoolean, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNumber, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsExternal, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsInt32, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsUint32, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsDate, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsArgumentsObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBigIntObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBooleanObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNumberObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsStringObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsSymbolObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNativeError, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsRegExp, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsAsyncFunction, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsGeneratorFunction, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsGeneratorObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsPromise, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsMap, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsSet, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsMapIterator, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsSetIterator, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsWeakMap, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsWeakSet, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsArrayBuffer, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsArrayBufferView, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsTypedArray, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsUint8Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsUint8ClampedArray, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsInt8Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsUint16Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsInt16Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsUint32Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsInt32Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsFloat32Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsFloat64Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBigInt64Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsBigUint64Array, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsDataView, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsSharedArrayBuffer, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsProxy, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsWebAssemblyCompiledModule, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsModuleNamespaceObject, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::ToBigInt, (class v8::MaybeLocal<class v8::BigInt> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToNumber, (class v8::MaybeLocal<class v8::Number> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToString, (class v8::MaybeLocal<class v8::String> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToDetailString, (class v8::MaybeLocal<class v8::String> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToObject, (class v8::MaybeLocal<class v8::Object> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToInteger, (class v8::MaybeLocal<class v8::Integer> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToUint32, (class v8::MaybeLocal<class v8::Uint32> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToInt32, (class v8::MaybeLocal<class v8::Int32> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::ToBoolean, (class v8::Local<class v8::Boolean> (class v8::Isolate *) const)) \
  X(CXXMethod, v8::Value::ToArrayIndex, (class v8::MaybeLocal<class v8::Uint32> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::BooleanValue, (_Bool (class v8::Isolate *) const)) \
  X(CXXMethod, v8::Value::NumberValue, (class v8::Maybe<double> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::IntegerValue, (class v8::Maybe<long long> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::Uint32Value, (class v8::Maybe<unsigned int> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::Int32Value, (class v8::Maybe<int> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Value::Equals, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>) const)) \
  X(CXXMethod, v8::Value::StrictEquals, (_Bool (class v8::Local<class v8::Value>) const)) \
  X(CXXMethod, v8::Value::SameValue, (_Bool (class v8::Local<class v8::Value>) const)) \
  X(CXXMethod, v8::Value::TypeOf, (class v8::Local<class v8::String> (class v8::Isolate *))) \
  X(CXXMethod, v8::Value::InstanceOf, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Object>))) \
  X(CXXMethod, v8::Boolean::Value, (_Bool (void) const)) \
  X(CXXMethod, v8::Boolean::Cast, (class v8::Boolean *(class v8::Value *))) \
  X(CXXMethod, v8::Boolean::New, (class v8::Local<class v8::Boolean> (class v8::Isolate *, _Bool))) \
  X(CXXMethod, v8::Name::GetIdentityHash, (int (void))) \
  X(CXXMethod, v8::Name::Cast, (class v8::Name *(class v8::Value *))) \
  X(CXXMethod, v8::String::Length, (int (void) const)) \
  X(CXXMethod, v8::String::Utf8Length, (int (class v8::Isolate *) const)) \
  X(CXXMethod, v8::String::IsOneByte, (_Bool (void) const)) \
  X(CXXMethod, v8::String::ContainsOnlyOneByte, (_Bool (void) const)) \
  X(CXXMethod, v8::String::Write, (int (class v8::Isolate *, unsigned short *, int, int, int) const)) \
  X(CXXMethod, v8::String::WriteOneByte, (int (class v8::Isolate *, unsigned char *, int, int, int) const)) \
  X(CXXMethod, v8::String::WriteUtf8, (int (class v8::Isolate *, char *, int, int *, int) const)) \
  X(CXXMethod, v8::String::Empty, (class v8::Local<class v8::String> (class v8::Isolate *))) \
  X(CXXMethod, v8::String::IsExternal, (_Bool (void) const)) \
  X(CXXMethod, v8::String::IsExternalOneByte, (_Bool (void) const)) \
  X(CXXDestructor, v8::String::ExternalStringResourceBase::~ExternalStringResourceBase, (void (void))) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::IsCacheable, (_Bool (void) const)) \
  X(CXXConstructor, v8::String::ExternalStringResourceBase::ExternalStringResourceBase, (void (const class v8::String::ExternalStringResourceBase &))) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::operator=, (void (const class v8::String::ExternalStringResourceBase &))) \
  X(CXXConstructor, v8::String::ExternalStringResourceBase::ExternalStringResourceBase, (void (void))) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Dispose, (void (void))) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Lock, (void (void) const)) \
  X(CXXMethod, v8::String::ExternalStringResourceBase::Unlock, (void (void) const)) \
  X(CXXDestructor, v8::String::ExternalStringResource::~ExternalStringResource, (void (void))) \
  X(CXXMethod, v8::String::ExternalStringResource::data, (const unsigned short *(void) const)) \
  X(CXXMethod, v8::String::ExternalStringResource::length, (unsigned long long (void) const)) \
  X(CXXConstructor, v8::String::ExternalStringResource::ExternalStringResource, (void (void))) \
  X(CXXConstructor, v8::String::ExternalStringResource::ExternalStringResource, (void (const class v8::String::ExternalStringResource &))) \
  X(CXXMethod, v8::String::ExternalStringResource::operator=, (class v8::String::ExternalStringResource &(const class v8::String::ExternalStringResource &))) \
  X(CXXDestructor, v8::String::ExternalOneByteStringResource::~ExternalOneByteStringResource, (void (void))) \
  X(CXXMethod, v8::String::ExternalOneByteStringResource::data, (const char *(void) const)) \
  X(CXXMethod, v8::String::ExternalOneByteStringResource::length, (unsigned long long (void) const)) \
  X(CXXConstructor, v8::String::ExternalOneByteStringResource::ExternalOneByteStringResource, (void (void))) \
  X(CXXConstructor, v8::String::ExternalOneByteStringResource::ExternalOneByteStringResource, (void (const class v8::String::ExternalOneByteStringResource &))) \
  X(CXXMethod, v8::String::ExternalOneByteStringResource::operator=, (class v8::String::ExternalOneByteStringResource &(const class v8::String::ExternalOneByteStringResource &))) \
  X(CXXMethod, v8::String::GetExternalStringResourceBase, (class v8::String::ExternalStringResourceBase *(enum v8::String::Encoding *) const)) \
  X(CXXMethod, v8::String::GetExternalStringResource, (class v8::String::ExternalStringResource *(void) const)) \
  X(CXXMethod, v8::String::GetExternalOneByteStringResource, (const class v8::String::ExternalOneByteStringResource *(void) const)) \
  X(CXXMethod, v8::String::Cast, (class v8::String *(class v8::Value *))) \
  X(CXXMethod, v8::String::NewFromUtf8, (class v8::MaybeLocal<class v8::String> (class v8::Isolate *, const char *, enum v8::NewStringType, int))) \
  X(CXXMethod, v8::String::NewFromOneByte, (class v8::MaybeLocal<class v8::String> (class v8::Isolate *, const unsigned char *, enum v8::NewStringType, int))) \
  X(CXXMethod, v8::String::NewFromTwoByte, (class v8::MaybeLocal<class v8::String> (class v8::Isolate *, const unsigned short *, enum v8::NewStringType, int))) \
  X(CXXMethod, v8::String::Concat, (class v8::Local<class v8::String> (class v8::Isolate *, class v8::Local<class v8::String>, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::String::NewExternalTwoByte, (class v8::MaybeLocal<class v8::String> (class v8::Isolate *, class v8::String::ExternalStringResource *))) \
  X(CXXMethod, v8::String::MakeExternal, (_Bool (class v8::String::ExternalStringResource *))) \
  X(CXXMethod, v8::String::NewExternalOneByte, (class v8::MaybeLocal<class v8::String> (class v8::Isolate *, class v8::String::ExternalOneByteStringResource *))) \
  X(CXXMethod, v8::String::MakeExternal, (_Bool (class v8::String::ExternalOneByteStringResource *))) \
  X(CXXMethod, v8::String::CanMakeExternal, (_Bool (void))) \
  X(CXXMethod, v8::String::StringEquals, (_Bool (class v8::Local<class v8::String>))) \
  X(CXXConstructor, v8::String::Utf8Value::Utf8Value, (void (class v8::Isolate *, class v8::Local<class v8::Value>))) \
  X(CXXDestructor, v8::String::Utf8Value::~Utf8Value, (void (void))) \
  X(CXXMethod, v8::String::Utf8Value::operator*, (char *(void))) \
  X(CXXMethod, v8::String::Utf8Value::operator*, (const char *(void) const)) \
  X(CXXMethod, v8::String::Utf8Value::length, (int (void) const)) \
  X(CXXConstructor, v8::String::Utf8Value::Utf8Value, (void (const class v8::String::Utf8Value &))) \
  X(CXXMethod, v8::String::Utf8Value::operator=, (void (const class v8::String::Utf8Value &))) \
  X(CXXConstructor, v8::String::Value::Value, (void (class v8::Isolate *, class v8::Local<class v8::Value>))) \
  X(CXXDestructor, v8::String::Value::~Value, (void (void))) \
  X(CXXMethod, v8::String::Value::operator*, (unsigned short *(void))) \
  X(CXXMethod, v8::String::Value::operator*, (const unsigned short *(void) const)) \
  X(CXXMethod, v8::String::Value::length, (int (void) const)) \
  X(CXXConstructor, v8::String::Value::Value, (void (const class v8::String::Value &))) \
  X(CXXMethod, v8::String::Value::operator=, (void (const class v8::String::Value &))) \
  X(CXXMethod, v8::Symbol::Name, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Symbol::New, (class v8::Local<class v8::Symbol> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Symbol::For, (class v8::Local<class v8::Symbol> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Symbol::ForApi, (class v8::Local<class v8::Symbol> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Symbol::GetAsyncIterator, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetHasInstance, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetIsConcatSpreadable, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetIterator, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetMatch, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetReplace, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetSearch, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetSplit, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetToPrimitive, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetToStringTag, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::GetUnscopables, (class v8::Local<class v8::Symbol> (class v8::Isolate *))) \
  X(CXXMethod, v8::Symbol::Cast, (class v8::Symbol *(class v8::Value *))) \
  X(CXXMethod, v8::Private::Name, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Private::New, (class v8::Local<class v8::Private> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Private::ForApi, (class v8::Local<class v8::Private> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Private::Cast, (class v8::Private *(class v8::Data *))) \
  X(CXXMethod, v8::Number::Value, (double (void) const)) \
  X(CXXMethod, v8::Number::New, (class v8::Local<class v8::Number> (class v8::Isolate *, double))) \
  X(CXXMethod, v8::Number::Cast, (class v8::Number *(class v8::Value *))) \
  X(CXXMethod, v8::Integer::New, (class v8::Local<class v8::Integer> (class v8::Isolate *, int))) \
  X(CXXMethod, v8::Integer::NewFromUnsigned, (class v8::Local<class v8::Integer> (class v8::Isolate *, unsigned int))) \
  X(CXXMethod, v8::Integer::Value, (long long (void) const)) \
  X(CXXMethod, v8::Integer::Cast, (class v8::Integer *(class v8::Value *))) \
  X(CXXMethod, v8::Int32::Value, (int (void) const)) \
  X(CXXMethod, v8::Int32::Cast, (class v8::Int32 *(class v8::Value *))) \
  X(CXXMethod, v8::Uint32::Value, (unsigned int (void) const)) \
  X(CXXMethod, v8::Uint32::Cast, (class v8::Uint32 *(class v8::Value *))) \
  X(CXXMethod, v8::BigInt::New, (class v8::Local<class v8::BigInt> (class v8::Isolate *, long long))) \
  X(CXXMethod, v8::BigInt::NewFromUnsigned, (class v8::Local<class v8::BigInt> (class v8::Isolate *, unsigned long long))) \
  X(CXXMethod, v8::BigInt::NewFromWords, (class v8::MaybeLocal<class v8::BigInt> (class v8::Local<class v8::Context>, int, int, const unsigned long long *))) \
  X(CXXMethod, v8::BigInt::Uint64Value, (unsigned long long (_Bool *) const)) \
  X(CXXMethod, v8::BigInt::Int64Value, (long long (_Bool *) const)) \
  X(CXXMethod, v8::BigInt::WordCount, (int (void) const)) \
  X(CXXMethod, v8::BigInt::ToWordsArray, (void (int *, int *, unsigned long long *) const)) \
  X(CXXMethod, v8::BigInt::Cast, (class v8::BigInt *(class v8::Value *))) \
  X(CXXMethod, v8::Object::Set, (_Bool (class v8::Local<class v8::Value>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Set, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Set, (_Bool (unsigned int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Set, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::CreateDataProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::CreateDataProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::DefineOwnProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, enum v8::PropertyAttribute))) \
  X(CXXMethod, v8::Object::DefineProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, class v8::PropertyDescriptor &))) \
  X(CXXMethod, v8::Object::Get, (class v8::Local<class v8::Value> (class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Get, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Get, (class v8::Local<class v8::Value> (unsigned int))) \
  X(CXXMethod, v8::Object::Get, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, unsigned int))) \
  X(CXXMethod, v8::Object::GetPropertyAttributes, (class v8::Maybe<enum v8::PropertyAttribute> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::GetOwnPropertyDescriptor, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::Has, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Delete, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::Has, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int))) \
  X(CXXMethod, v8::Object::Delete, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int))) \
  X(CXXMethod, v8::Object::SetAccessor, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::MaybeLocal<class v8::Value>, enum v8::AccessControl, enum v8::PropertyAttribute, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Object::SetAccessorProperty, (void (class v8::Local<class v8::Name>, class v8::Local<class v8::Function>, class v8::Local<class v8::Function>, enum v8::PropertyAttribute, enum v8::AccessControl))) \
  X(CXXMethod, v8::Object::SetNativeDataProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::Local<class v8::Value>, enum v8::PropertyAttribute, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Object::SetLazyDataProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyAttribute, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Object::HasPrivate, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Private>))) \
  X(CXXMethod, v8::Object::SetPrivate, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Private>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::DeletePrivate, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Private>))) \
  X(CXXMethod, v8::Object::GetPrivate, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Private>))) \
  X(CXXMethod, v8::Object::GetPropertyNames, (class v8::MaybeLocal<class v8::Array> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Object::GetPropertyNames, (class v8::MaybeLocal<class v8::Array> (class v8::Local<class v8::Context>, enum v8::KeyCollectionMode, enum v8::PropertyFilter, enum v8::IndexFilter, enum v8::KeyConversionMode))) \
  X(CXXMethod, v8::Object::GetOwnPropertyNames, (class v8::MaybeLocal<class v8::Array> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Object::GetOwnPropertyNames, (class v8::MaybeLocal<class v8::Array> (class v8::Local<class v8::Context>, enum v8::PropertyFilter, enum v8::KeyConversionMode))) \
  X(CXXMethod, v8::Object::GetPrototype, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Object::SetPrototype, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::FindInstanceInPrototypeChain, (class v8::Local<class v8::Object> (class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::Object::ObjectProtoToString, (class v8::MaybeLocal<class v8::String> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Object::GetConstructorName, (class v8::Local<class v8::String> (void))) \
  X(CXXMethod, v8::Object::SetIntegrityLevel, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, enum v8::IntegrityLevel))) \
  X(CXXMethod, v8::Object::InternalFieldCount, (int (void))) \
  X(CXXMethod, v8::Object::InternalFieldCount, (int (const class v8::PersistentBase<class v8::Object> &))) \
  X(CXXMethod, v8::Object::InternalFieldCount, (int (const class v8::TracedGlobal<class v8::Object> &))) \
  X(CXXMethod, v8::Object::GetInternalField, (class v8::Local<class v8::Value> (int))) \
  X(CXXMethod, v8::Object::SetInternalField, (void (int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, (void *(int))) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, (void *(const class v8::PersistentBase<class v8::Object> &, int))) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, (void *(const class v8::TracedGlobal<class v8::Object> &, int))) \
  X(CXXMethod, v8::Object::SetAlignedPointerInInternalField, (void (int, void *))) \
  X(CXXMethod, v8::Object::SetAlignedPointerInInternalFields, (void (int, int *, void **))) \
  X(CXXMethod, v8::Object::HasOwnProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::HasOwnProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int))) \
  X(CXXMethod, v8::Object::HasRealNamedProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::HasRealIndexedProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, unsigned int))) \
  X(CXXMethod, v8::Object::HasRealNamedCallbackProperty, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyInPrototypeChain, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyAttributesInPrototypeChain, (class v8::Maybe<enum v8::PropertyAttribute> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::GetRealNamedProperty, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::GetRealNamedPropertyAttributes, (class v8::Maybe<enum v8::PropertyAttribute> (class v8::Local<class v8::Context>, class v8::Local<class v8::Name>))) \
  X(CXXMethod, v8::Object::HasNamedLookupInterceptor, (_Bool (void))) \
  X(CXXMethod, v8::Object::HasIndexedLookupInterceptor, (_Bool (void))) \
  X(CXXMethod, v8::Object::GetIdentityHash, (int (void))) \
  X(CXXMethod, v8::Object::Clone, (class v8::Local<class v8::Object> (void))) \
  X(CXXMethod, v8::Object::CreationContext, (class v8::Local<class v8::Context> (void))) \
  X(CXXMethod, v8::Object::CreationContext, (class v8::Local<class v8::Context> (const class v8::PersistentBase<class v8::Object> &))) \
  X(CXXMethod, v8::Object::IsCallable, (_Bool (void))) \
  X(CXXMethod, v8::Object::IsConstructor, (_Bool (void))) \
  X(CXXMethod, v8::Object::CallAsFunction, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, int, class v8::Local<class v8::Value> *))) \
  X(CXXMethod, v8::Object::CallAsConstructor, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, int, class v8::Local<class v8::Value> *))) \
  X(CXXMethod, v8::Object::GetIsolate, (class v8::Isolate *(void))) \
  X(CXXMethod, v8::Object::PreviewEntries, (class v8::MaybeLocal<class v8::Array> (_Bool *))) \
  X(CXXMethod, v8::Object::New, (class v8::Local<class v8::Object> (class v8::Isolate *))) \
  X(CXXMethod, v8::Object::New, (class v8::Local<class v8::Object> (class v8::Isolate *, class v8::Local<class v8::Value>, class v8::Local<class v8::Name> *, class v8::Local<class v8::Value> *, unsigned long long))) \
  X(CXXMethod, v8::Object::Cast, (class v8::Object *(class v8::Value *))) \
  X(CXXMethod, v8::Array::Length, (unsigned int (void) const)) \
  X(CXXMethod, v8::Array::New, (class v8::Local<class v8::Array> (class v8::Isolate *, int))) \
  X(CXXMethod, v8::Array::New, (class v8::Local<class v8::Array> (class v8::Isolate *, class v8::Local<class v8::Value> *, unsigned long long))) \
  X(CXXMethod, v8::Array::Cast, (class v8::Array *(class v8::Value *))) \
  X(CXXMethod, v8::Map::Size, (unsigned long long (void) const)) \
  X(CXXMethod, v8::Map::Clear, (void (void))) \
  X(CXXMethod, v8::Map::Get, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Map::Set, (class v8::MaybeLocal<class v8::Map> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Map::Has, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Map::Delete, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Map::AsArray, (class v8::Local<class v8::Array> (void) const)) \
  X(CXXMethod, v8::Map::New, (class v8::Local<class v8::Map> (class v8::Isolate *))) \
  X(CXXMethod, v8::Map::Cast, (class v8::Map *(class v8::Value *))) \
  X(CXXMethod, v8::Set::Size, (unsigned long long (void) const)) \
  X(CXXMethod, v8::Set::Clear, (void (void))) \
  X(CXXMethod, v8::Set::Add, (class v8::MaybeLocal<class v8::Set> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Set::Has, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Set::Delete, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Set::AsArray, (class v8::Local<class v8::Array> (void) const)) \
  X(CXXMethod, v8::Set::New, (class v8::Local<class v8::Set> (class v8::Isolate *))) \
  X(CXXMethod, v8::Set::Cast, (class v8::Set *(class v8::Value *))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (_Bool))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (double))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (int))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (unsigned int))) \
  X(CXXMethod, v8::ReturnValue::SetNull, (void (void))) \
  X(CXXMethod, v8::ReturnValue::SetUndefined, (void (void))) \
  X(CXXMethod, v8::ReturnValue::SetEmptyString, (void (void))) \
  X(CXXMethod, v8::ReturnValue::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::ReturnValue::Get, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Length, (int (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::operator[], (class v8::Local<class v8::Value> (int) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::This, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Holder, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::NewTarget, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::IsConstructCall, (_Bool (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Data, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::Data, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::This, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::Holder, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::ShouldThrowOnError, (_Bool (void) const)) \
  X(CXXMethod, v8::Function::New, (class v8::MaybeLocal<class v8::Function> (class v8::Local<class v8::Context>, void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, int, enum v8::ConstructorBehavior, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Function::NewInstance, (class v8::MaybeLocal<class v8::Object> (class v8::Local<class v8::Context>, int, class v8::Local<class v8::Value> *) const)) \
  X(CXXMethod, v8::Function::NewInstance, (class v8::MaybeLocal<class v8::Object> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::Function::NewInstanceWithSideEffectType, (class v8::MaybeLocal<class v8::Object> (class v8::Local<class v8::Context>, int, class v8::Local<class v8::Value> *, enum v8::SideEffectType) const)) \
  X(CXXMethod, v8::Function::Call, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, int, class v8::Local<class v8::Value> *))) \
  X(CXXMethod, v8::Function::SetName, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Function::GetName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Function::GetInferredName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Function::GetDebugName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Function::GetDisplayName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Function::GetScriptLineNumber, (int (void) const)) \
  X(CXXMethod, v8::Function::GetScriptColumnNumber, (int (void) const)) \
  X(CXXMethod, v8::Function::ScriptId, (int (void) const)) \
  X(CXXMethod, v8::Function::GetBoundFunction, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::Function::GetScriptOrigin, (class v8::ScriptOrigin (void) const)) \
  X(CXXMethod, v8::Function::Cast, (class v8::Function *(class v8::Value *))) \
  X(CXXMethod, v8::Promise::Resolver::New, (class v8::MaybeLocal<class v8::Promise::Resolver> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::Promise::Resolver::GetPromise, (class v8::Local<class v8::Promise> (void))) \
  X(CXXMethod, v8::Promise::Resolver::Resolve, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Promise::Resolver::Reject, (class v8::Maybe<_Bool> (class v8::Local<class v8::Context>, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Promise::Resolver::Cast, (class v8::Promise::Resolver *(class v8::Value *))) \
  X(CXXMethod, v8::Promise::Catch, (class v8::MaybeLocal<class v8::Promise> (class v8::Local<class v8::Context>, class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Promise::Then, (class v8::MaybeLocal<class v8::Promise> (class v8::Local<class v8::Context>, class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Promise::Then, (class v8::MaybeLocal<class v8::Promise> (class v8::Local<class v8::Context>, class v8::Local<class v8::Function>, class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Promise::HasHandler, (_Bool (void))) \
  X(CXXMethod, v8::Promise::Result, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Promise::State, (enum v8::Promise::PromiseState (void))) \
  X(CXXMethod, v8::Promise::MarkAsHandled, (void (void))) \
  X(CXXMethod, v8::Promise::Cast, (class v8::Promise *(class v8::Value *))) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, (void (void))) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, (void (class v8::Local<class v8::Value>))) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, (void (class v8::Local<class v8::Value>, _Bool))) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, (void (class v8::Local<class v8::Value>, class v8::Local<class v8::Value>))) \
  X(CXXDestructor, v8::PropertyDescriptor::~PropertyDescriptor, (void (void))) \
  X(CXXMethod, v8::PropertyDescriptor::value, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_value, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::get, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_get, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::set, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_set, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::set_enumerable, (void (_Bool))) \
  X(CXXMethod, v8::PropertyDescriptor::enumerable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_enumerable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::set_configurable, (void (_Bool))) \
  X(CXXMethod, v8::PropertyDescriptor::configurable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_configurable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::writable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::has_writable, (_Bool (void) const)) \
  X(CXXMethod, v8::PropertyDescriptor::get_private, (struct v8::PropertyDescriptor::PrivateData *(void) const)) \
  X(CXXConstructor, v8::PropertyDescriptor::PropertyDescriptor, (void (const class v8::PropertyDescriptor &))) \
  X(CXXMethod, v8::PropertyDescriptor::operator=, (void (const class v8::PropertyDescriptor &))) \
  X(CXXMethod, v8::Proxy::GetTarget, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Proxy::GetHandler, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Proxy::IsRevoked, (_Bool (void))) \
  X(CXXMethod, v8::Proxy::Revoke, (void (void))) \
  X(CXXMethod, v8::Proxy::New, (class v8::MaybeLocal<class v8::Proxy> (class v8::Local<class v8::Context>, class v8::Local<class v8::Object>, class v8::Local<class v8::Object>))) \
  X(CXXMethod, v8::Proxy::Cast, (class v8::Proxy *(class v8::Value *))) \
  X(CXXConstructor, v8::MemorySpan::MemorySpan<T>, (void (void))) \
  X(CXXMethod, v8::MemorySpan::size, (unsigned long long (void) const)) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, (void (void))) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, (void (const unsigned char *, unsigned long long))) \
  X(CXXMethod, v8::MemorySpan<const unsigned char>::data, (const unsigned char *(void) const)) \
  X(CXXMethod, v8::MemorySpan<const unsigned char>::size, (unsigned long long (void) const)) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, (void (const class v8::MemorySpan<const unsigned char> &))) \
  X(CXXConstructor, v8::MemorySpan<const unsigned char>::MemorySpan, (void (class v8::MemorySpan<const unsigned char> &&))) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, (void (class std::unique_ptr<unsigned char const[], struct std::default_delete<unsigned char const[]> >, unsigned long long))) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, (void (void))) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, (void (const struct v8::OwnedBuffer &))) \
  X(CXXConstructor, v8::OwnedBuffer::OwnedBuffer, (void (struct v8::OwnedBuffer &&))) \
  X(CXXMethod, v8::OwnedBuffer::operator=, (struct v8::OwnedBuffer &(struct v8::OwnedBuffer &&))) \
  X(CXXDestructor, v8::OwnedBuffer::~OwnedBuffer, (void (void))) \
  X(CXXMethod, v8::OwnedBuffer::operator=, (struct v8::OwnedBuffer &(const struct v8::OwnedBuffer &))) \
  X(CXXMethod, v8::CompiledWasmModule::Serialize, (struct v8::OwnedBuffer (void))) \
  X(CXXMethod, v8::CompiledWasmModule::GetWireBytesRef, (class v8::MemorySpan<const unsigned char> (void))) \
  X(CXXConstructor, v8::CompiledWasmModule::CompiledWasmModule, (void (const class v8::CompiledWasmModule &))) \
  X(CXXConstructor, v8::CompiledWasmModule::CompiledWasmModule, (void (class v8::CompiledWasmModule &&))) \
  X(CXXMethod, v8::CompiledWasmModule::operator=, (class v8::CompiledWasmModule &(class v8::CompiledWasmModule &&))) \
  X(CXXDestructor, v8::CompiledWasmModule::~CompiledWasmModule, (void (void))) \
  X(CXXConstructor, v8::WasmModuleObject::TransferrableModule::TransferrableModule, (void (class v8::WasmModuleObject::TransferrableModule &&))) \
  X(CXXConstructor, v8::WasmModuleObject::TransferrableModule::TransferrableModule, (void (const class v8::WasmModuleObject::TransferrableModule &))) \
  X(CXXMethod, v8::WasmModuleObject::TransferrableModule::operator=, (class v8::WasmModuleObject::TransferrableModule &(class v8::WasmModuleObject::TransferrableModule &&))) \
  X(CXXMethod, v8::WasmModuleObject::TransferrableModule::operator=, (class v8::WasmModuleObject::TransferrableModule &(const class v8::WasmModuleObject::TransferrableModule &))) \
  X(CXXDestructor, v8::WasmModuleObject::TransferrableModule::~TransferrableModule, (void (void))) \
  X(CXXMethod, v8::WasmModuleObject::GetTransferrableModule, (class v8::WasmModuleObject::TransferrableModule (void))) \
  X(CXXMethod, v8::WasmModuleObject::FromTransferrableModule, (class v8::MaybeLocal<class v8::WasmModuleObject> (class v8::Isolate *, const class v8::WasmModuleObject::TransferrableModule &))) \
  X(CXXMethod, v8::WasmModuleObject::GetCompiledModule, (class v8::CompiledWasmModule (void))) \
  X(CXXMethod, v8::WasmModuleObject::DeserializeOrCompile, (class v8::MaybeLocal<class v8::WasmModuleObject> (class v8::Isolate *, class v8::MemorySpan<const unsigned char>, class v8::MemorySpan<const unsigned char>))) \
  X(CXXMethod, v8::WasmModuleObject::Cast, (class v8::WasmModuleObject *(class v8::Value *))) \
  X(CXXDestructor, v8::WasmStreaming::Client::~Client, (void (void))) \
  X(CXXMethod, v8::WasmStreaming::Client::OnModuleCompiled, (void (class v8::CompiledWasmModule))) \
  X(CXXMethod, v8::WasmStreaming::Client::operator=, (class v8::WasmStreaming::Client &(const class v8::WasmStreaming::Client &))) \
  X(CXXConstructor, v8::WasmStreaming::WasmStreaming, (void (class std::unique_ptr<class v8::WasmStreaming::WasmStreamingImpl, struct std::default_delete<class v8::WasmStreaming::WasmStreamingImpl> >))) \
  X(CXXDestructor, v8::WasmStreaming::~WasmStreaming, (void (void))) \
  X(CXXMethod, v8::WasmStreaming::OnBytesReceived, (void (const unsigned char *, unsigned long long))) \
  X(CXXMethod, v8::WasmStreaming::Finish, (void (void))) \
  X(CXXMethod, v8::WasmStreaming::Abort, (void (class v8::MaybeLocal<class v8::Value>))) \
  X(CXXMethod, v8::WasmStreaming::SetCompiledModuleBytes, (_Bool (const unsigned char *, unsigned long long))) \
  X(CXXMethod, v8::WasmStreaming::SetClient, (void (class std::shared_ptr<class v8::WasmStreaming::Client>))) \
  X(CXXMethod, v8::WasmStreaming::Unpack, (class std::shared_ptr<class v8::WasmStreaming> (class v8::Isolate *, class v8::Local<class v8::Value>))) \
  X(CXXConstructor, v8::WasmStreaming::WasmStreaming, (void (const class v8::WasmStreaming &))) \
  X(CXXConstructor, v8::WasmModuleObjectBuilderStreaming::WasmModuleObjectBuilderStreaming, (void (class v8::Isolate *))) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::OnBytesReceived, (void (const unsigned char *, unsigned long long))) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::Finish, (void (void))) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::Abort, (void (class v8::MaybeLocal<class v8::Value>))) \
  X(CXXMethod, v8::WasmModuleObjectBuilderStreaming::GetPromise, (class v8::Local<class v8::Promise> (void))) \
  X(CXXDestructor, v8::WasmModuleObjectBuilderStreaming::~WasmModuleObjectBuilderStreaming, (void (void))) \
  X(CXXDestructor, v8::ArrayBuffer::Allocator::~Allocator, (void (void))) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::Allocate, (void *(unsigned long long))) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::AllocateUninitialized, (void *(unsigned long long))) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::Free, (void (void *, unsigned long long))) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::NewDefaultAllocator, (class v8::ArrayBuffer::Allocator *(void))) \
  X(CXXMethod, v8::ArrayBuffer::Allocator::operator=, (class v8::ArrayBuffer::Allocator &(const class v8::ArrayBuffer::Allocator &))) \
  X(CXXConstructor, v8::ArrayBuffer::Contents::Contents, (void (void))) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationBase, (void *(void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::AllocationMode, (enum v8::ArrayBuffer::Allocator::AllocationMode (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::Data, (void *(void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::ByteLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Contents::Deleter, (void (*(void) const)(void *, unsigned long long, void *))) \
  X(CXXMethod, v8::ArrayBuffer::Contents::DeleterData, (void *(void) const)) \
  X(CXXMethod, v8::ArrayBuffer::ByteLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::New, (class v8::Local<class v8::ArrayBuffer> (class v8::Isolate *, unsigned long long))) \
  X(CXXMethod, v8::ArrayBuffer::New, (class v8::Local<class v8::ArrayBuffer> (class v8::Isolate *, void *, unsigned long long, enum v8::ArrayBufferCreationMode))) \
  X(CXXMethod, v8::ArrayBuffer::IsExternal, (_Bool (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::IsDetachable, (_Bool (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::IsNeuterable, (_Bool (void) const)) \
  X(CXXMethod, v8::ArrayBuffer::Detach, (void (void))) \
  X(CXXMethod, v8::ArrayBuffer::Neuter, (void (void))) \
  X(CXXMethod, v8::ArrayBuffer::Externalize, (class v8::ArrayBuffer::Contents (void))) \
  X(CXXMethod, v8::ArrayBuffer::GetContents, (class v8::ArrayBuffer::Contents (void))) \
  X(CXXMethod, v8::ArrayBuffer::Cast, (class v8::ArrayBuffer *(class v8::Value *))) \
  X(CXXMethod, v8::ArrayBufferView::Buffer, (class v8::Local<class v8::ArrayBuffer> (void))) \
  X(CXXMethod, v8::ArrayBufferView::ByteOffset, (unsigned long long (void))) \
  X(CXXMethod, v8::ArrayBufferView::ByteLength, (unsigned long long (void))) \
  X(CXXMethod, v8::ArrayBufferView::CopyContents, (unsigned long long (void *, unsigned long long))) \
  X(CXXMethod, v8::ArrayBufferView::HasBuffer, (_Bool (void) const)) \
  X(CXXMethod, v8::ArrayBufferView::Cast, (class v8::ArrayBufferView *(class v8::Value *))) \
  X(CXXMethod, v8::TypedArray::Length, (unsigned long long (void))) \
  X(CXXMethod, v8::TypedArray::Cast, (class v8::TypedArray *(class v8::Value *))) \
  X(CXXMethod, v8::Uint8Array::New, (class v8::Local<class v8::Uint8Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint8Array::New, (class v8::Local<class v8::Uint8Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint8Array::Cast, (class v8::Uint8Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint8ClampedArray::New, (class v8::Local<class v8::Uint8ClampedArray> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint8ClampedArray::New, (class v8::Local<class v8::Uint8ClampedArray> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint8ClampedArray::Cast, (class v8::Uint8ClampedArray *(class v8::Value *))) \
  X(CXXMethod, v8::Int8Array::New, (class v8::Local<class v8::Int8Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int8Array::New, (class v8::Local<class v8::Int8Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int8Array::Cast, (class v8::Int8Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint16Array::New, (class v8::Local<class v8::Uint16Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint16Array::New, (class v8::Local<class v8::Uint16Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint16Array::Cast, (class v8::Uint16Array *(class v8::Value *))) \
  X(CXXMethod, v8::Int16Array::New, (class v8::Local<class v8::Int16Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int16Array::New, (class v8::Local<class v8::Int16Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int16Array::Cast, (class v8::Int16Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint32Array::New, (class v8::Local<class v8::Uint32Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint32Array::New, (class v8::Local<class v8::Uint32Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Uint32Array::Cast, (class v8::Uint32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Int32Array::New, (class v8::Local<class v8::Int32Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int32Array::New, (class v8::Local<class v8::Int32Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Int32Array::Cast, (class v8::Int32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Float32Array::New, (class v8::Local<class v8::Float32Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Float32Array::New, (class v8::Local<class v8::Float32Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Float32Array::Cast, (class v8::Float32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Float64Array::New, (class v8::Local<class v8::Float64Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Float64Array::New, (class v8::Local<class v8::Float64Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::Float64Array::Cast, (class v8::Float64Array *(class v8::Value *))) \
  X(CXXMethod, v8::BigInt64Array::New, (class v8::Local<class v8::BigInt64Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::BigInt64Array::New, (class v8::Local<class v8::BigInt64Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::BigInt64Array::Cast, (class v8::BigInt64Array *(class v8::Value *))) \
  X(CXXMethod, v8::BigUint64Array::New, (class v8::Local<class v8::BigUint64Array> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::BigUint64Array::New, (class v8::Local<class v8::BigUint64Array> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::BigUint64Array::Cast, (class v8::BigUint64Array *(class v8::Value *))) \
  X(CXXMethod, v8::DataView::New, (class v8::Local<class v8::DataView> (class v8::Local<class v8::ArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::DataView::New, (class v8::Local<class v8::DataView> (class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::DataView::Cast, (class v8::DataView *(class v8::Value *))) \
  X(CXXConstructor, v8::SharedArrayBuffer::Contents::Contents, (void (void))) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationBase, (void *(void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::AllocationMode, (enum v8::ArrayBuffer::Allocator::AllocationMode (void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::Data, (void *(void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::ByteLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::Deleter, (void (*(void) const)(void *, unsigned long long, void *))) \
  X(CXXMethod, v8::SharedArrayBuffer::Contents::DeleterData, (void *(void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::ByteLength, (unsigned long long (void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::New, (class v8::Local<class v8::SharedArrayBuffer> (class v8::Isolate *, unsigned long long))) \
  X(CXXMethod, v8::SharedArrayBuffer::New, (class v8::Local<class v8::SharedArrayBuffer> (class v8::Isolate *, void *, unsigned long long, enum v8::ArrayBufferCreationMode))) \
  X(CXXMethod, v8::SharedArrayBuffer::New, (class v8::Local<class v8::SharedArrayBuffer> (class v8::Isolate *, const class v8::SharedArrayBuffer::Contents &, enum v8::ArrayBufferCreationMode))) \
  X(CXXMethod, v8::SharedArrayBuffer::IsExternal, (_Bool (void) const)) \
  X(CXXMethod, v8::SharedArrayBuffer::Externalize, (class v8::SharedArrayBuffer::Contents (void))) \
  X(CXXMethod, v8::SharedArrayBuffer::GetContents, (class v8::SharedArrayBuffer::Contents (void))) \
  X(CXXMethod, v8::SharedArrayBuffer::Cast, (class v8::SharedArrayBuffer *(class v8::Value *))) \
  X(CXXMethod, v8::Date::New, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>, double))) \
  X(CXXMethod, v8::Date::ValueOf, (double (void) const)) \
  X(CXXMethod, v8::Date::Cast, (class v8::Date *(class v8::Value *))) \
  X(CXXMethod, v8::NumberObject::New, (class v8::Local<class v8::Value> (class v8::Isolate *, double))) \
  X(CXXMethod, v8::NumberObject::ValueOf, (double (void) const)) \
  X(CXXMethod, v8::NumberObject::Cast, (class v8::NumberObject *(class v8::Value *))) \
  X(CXXMethod, v8::BigIntObject::New, (class v8::Local<class v8::Value> (class v8::Isolate *, long long))) \
  X(CXXMethod, v8::BigIntObject::ValueOf, (class v8::Local<class v8::BigInt> (void) const)) \
  X(CXXMethod, v8::BigIntObject::Cast, (class v8::BigIntObject *(class v8::Value *))) \
  X(CXXMethod, v8::BooleanObject::New, (class v8::Local<class v8::Value> (class v8::Isolate *, _Bool))) \
  X(CXXMethod, v8::BooleanObject::ValueOf, (_Bool (void) const)) \
  X(CXXMethod, v8::BooleanObject::Cast, (class v8::BooleanObject *(class v8::Value *))) \
  X(CXXMethod, v8::StringObject::New, (class v8::Local<class v8::Value> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::StringObject::ValueOf, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::StringObject::Cast, (class v8::StringObject *(class v8::Value *))) \
  X(CXXMethod, v8::SymbolObject::New, (class v8::Local<class v8::Value> (class v8::Isolate *, class v8::Local<class v8::Symbol>))) \
  X(CXXMethod, v8::SymbolObject::ValueOf, (class v8::Local<class v8::Symbol> (void) const)) \
  X(CXXMethod, v8::SymbolObject::Cast, (class v8::SymbolObject *(class v8::Value *))) \
  X(CXXMethod, v8::RegExp::New, (class v8::MaybeLocal<class v8::RegExp> (class v8::Local<class v8::Context>, class v8::Local<class v8::String>, enum v8::RegExp::Flags))) \
  X(CXXMethod, v8::RegExp::GetSource, (class v8::Local<class v8::String> (void) const)) \
  X(CXXMethod, v8::RegExp::GetFlags, (enum v8::RegExp::Flags (void) const)) \
  X(CXXMethod, v8::RegExp::Cast, (class v8::RegExp *(class v8::Value *))) \
  X(CXXMethod, v8::External::New, (class v8::Local<class v8::External> (class v8::Isolate *, void *))) \
  X(CXXMethod, v8::External::Cast, (class v8::External *(class v8::Value *))) \
  X(CXXMethod, v8::External::Value, (void *(void) const)) \
  X(CXXMethod, v8::Template::Set, (void (class v8::Local<class v8::Name>, class v8::Local<class v8::Data>, enum v8::PropertyAttribute))) \
  X(CXXMethod, v8::Template::SetPrivate, (void (class v8::Local<class v8::Private>, class v8::Local<class v8::Data>, enum v8::PropertyAttribute))) \
  X(CXXMethod, v8::Template::Set, (void (class v8::Isolate *, const char *, class v8::Local<class v8::Data>))) \
  X(CXXMethod, v8::Template::SetAccessorProperty, (void (class v8::Local<class v8::Name>, class v8::Local<class v8::FunctionTemplate>, class v8::Local<class v8::FunctionTemplate>, enum v8::PropertyAttribute, enum v8::AccessControl))) \
  X(CXXMethod, v8::Template::SetNativeDataProperty, (void (class v8::Local<class v8::String>, void (*)(class v8::Local<class v8::String>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::String>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::Local<class v8::Value>, enum v8::PropertyAttribute, class v8::Local<class v8::AccessorSignature>, enum v8::AccessControl, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Template::SetNativeDataProperty, (void (class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::Local<class v8::Value>, enum v8::PropertyAttribute, class v8::Local<class v8::AccessorSignature>, enum v8::AccessControl, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Template::SetLazyDataProperty, (void (class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyAttribute, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::Template::SetIntrinsicDataProperty, (void (class v8::Local<class v8::Name>, enum v8::Intrinsic, enum v8::PropertyAttribute))) \
  X(CXXMethod, v8::FunctionTemplate::New, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, class v8::Local<class v8::Signature>, int, enum v8::ConstructorBehavior, enum v8::SideEffectType))) \
  X(CXXMethod, v8::FunctionTemplate::FromSnapshot, (class v8::MaybeLocal<class v8::FunctionTemplate> (class v8::Isolate *, unsigned long long))) \
  X(CXXMethod, v8::FunctionTemplate::NewWithCache, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &), class v8::Local<class v8::Private>, class v8::Local<class v8::Value>, class v8::Local<class v8::Signature>, int, enum v8::SideEffectType))) \
  X(CXXMethod, v8::FunctionTemplate::GetFunction, (class v8::MaybeLocal<class v8::Function> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::FunctionTemplate::NewRemoteInstance, (class v8::MaybeLocal<class v8::Object> (void))) \
  X(CXXMethod, v8::FunctionTemplate::SetCallHandler, (void (void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::SideEffectType))) \
  X(CXXMethod, v8::FunctionTemplate::SetLength, (void (int))) \
  X(CXXMethod, v8::FunctionTemplate::InstanceTemplate, (class v8::Local<class v8::ObjectTemplate> (void))) \
  X(CXXMethod, v8::FunctionTemplate::Inherit, (void (class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::FunctionTemplate::PrototypeTemplate, (class v8::Local<class v8::ObjectTemplate> (void))) \
  X(CXXMethod, v8::FunctionTemplate::SetPrototypeProviderTemplate, (void (class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::FunctionTemplate::SetClassName, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::FunctionTemplate::SetAcceptAnyReceiver, (void (_Bool))) \
  X(CXXMethod, v8::FunctionTemplate::ReadOnlyPrototype, (void (void))) \
  X(CXXMethod, v8::FunctionTemplate::RemovePrototype, (void (void))) \
  X(CXXMethod, v8::FunctionTemplate::HasInstance, (_Bool (class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::FunctionTemplate::Cast, (class v8::FunctionTemplate *(class v8::Data *))) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, (void (void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Integer> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyDescriptor &, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, (void (void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Integer> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, (void (void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), void (*)(class v8::Local<class v8::Name>, const class v8::PropertyDescriptor &, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, (void (const struct v8::NamedPropertyHandlerConfiguration &))) \
  X(CXXConstructor, v8::NamedPropertyHandlerConfiguration::NamedPropertyHandlerConfiguration, (void (struct v8::NamedPropertyHandlerConfiguration &&))) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, (void (void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Integer> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), void (*)(unsigned int, const class v8::PropertyDescriptor &, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, (void (void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Integer> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, (void (void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), void (*)(unsigned int, const class v8::PropertyDescriptor &, const class v8::PropertyCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>, enum v8::PropertyHandlerFlags))) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, (void (const struct v8::IndexedPropertyHandlerConfiguration &))) \
  X(CXXConstructor, v8::IndexedPropertyHandlerConfiguration::IndexedPropertyHandlerConfiguration, (void (struct v8::IndexedPropertyHandlerConfiguration &&))) \
  X(CXXDestructor, v8::IndexedPropertyHandlerConfiguration::~IndexedPropertyHandlerConfiguration, (void (void))) \
  X(CXXMethod, v8::ObjectTemplate::New, (class v8::Local<class v8::ObjectTemplate> (class v8::Isolate *, class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::ObjectTemplate::FromSnapshot, (class v8::MaybeLocal<class v8::ObjectTemplate> (class v8::Isolate *, unsigned long long))) \
  X(CXXMethod, v8::ObjectTemplate::NewInstance, (class v8::MaybeLocal<class v8::Object> (class v8::Local<class v8::Context>))) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessor, (void (class v8::Local<class v8::String>, void (*)(class v8::Local<class v8::String>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::String>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::Local<class v8::Value>, enum v8::AccessControl, enum v8::PropertyAttribute, class v8::Local<class v8::AccessorSignature>, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessor, (void (class v8::Local<class v8::Name>, void (*)(class v8::Local<class v8::Name>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(class v8::Local<class v8::Name>, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<void> &), class v8::Local<class v8::Value>, enum v8::AccessControl, enum v8::PropertyAttribute, class v8::Local<class v8::AccessorSignature>, enum v8::SideEffectType, enum v8::SideEffectType))) \
  X(CXXMethod, v8::ObjectTemplate::SetHandler, (void (const struct v8::NamedPropertyHandlerConfiguration &))) \
  X(CXXMethod, v8::ObjectTemplate::SetIndexedPropertyHandler, (void (void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, class v8::Local<class v8::Value>, const class v8::PropertyCallbackInfo<class v8::Value> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Integer> &), void (*)(unsigned int, const class v8::PropertyCallbackInfo<class v8::Boolean> &), void (*)(const class v8::PropertyCallbackInfo<class v8::Array> &), class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::ObjectTemplate::SetHandler, (void (const struct v8::IndexedPropertyHandlerConfiguration &))) \
  X(CXXMethod, v8::ObjectTemplate::SetCallAsFunctionHandler, (void (void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &), class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::ObjectTemplate::MarkAsUndetectable, (void (void))) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessCheckCallback, (void (_Bool (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::Object>, class v8::Local<class v8::Value>), class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::ObjectTemplate::SetAccessCheckCallbackAndHandler, (void (_Bool (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::Object>, class v8::Local<class v8::Value>), const struct v8::NamedPropertyHandlerConfiguration &, const struct v8::IndexedPropertyHandlerConfiguration &, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::ObjectTemplate::InternalFieldCount, (int (void))) \
  X(CXXMethod, v8::ObjectTemplate::SetInternalFieldCount, (void (int))) \
  X(CXXMethod, v8::ObjectTemplate::IsImmutableProto, (_Bool (void))) \
  X(CXXMethod, v8::ObjectTemplate::SetImmutableProto, (void (void))) \
  X(CXXMethod, v8::ObjectTemplate::Cast, (class v8::ObjectTemplate *(class v8::Data *))) \
  X(CXXMethod, v8::Signature::New, (class v8::Local<class v8::Signature> (class v8::Isolate *, class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::Signature::Cast, (class v8::Signature *(class v8::Data *))) \
  X(CXXMethod, v8::AccessorSignature::New, (class v8::Local<class v8::AccessorSignature> (class v8::Isolate *, class v8::Local<class v8::FunctionTemplate>))) \
  X(CXXMethod, v8::AccessorSignature::Cast, (class v8::AccessorSignature *(class v8::Data *))) \
  X(CXXConstructor, v8::Extension::Extension, (void (const char *, const char *, int, const char **, int))) \
  X(CXXDestructor, v8::Extension::~Extension, (void (void))) \
  X(CXXMethod, v8::Extension::GetNativeFunctionTemplate, (class v8::Local<class v8::FunctionTemplate> (class v8::Isolate *, class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Extension::name, (const char *(void) const)) \
  X(CXXMethod, v8::Extension::source_length, (unsigned long long (void) const)) \
  X(CXXMethod, v8::Extension::source, (const class v8::String::ExternalOneByteStringResource *(void) const)) \
  X(CXXMethod, v8::Extension::dependency_count, (int (void) const)) \
  X(CXXMethod, v8::Extension::dependencies, (const char **(void) const)) \
  X(CXXMethod, v8::Extension::set_auto_enable, (void (_Bool))) \
  X(CXXMethod, v8::Extension::auto_enable, (_Bool (void))) \
  X(CXXConstructor, v8::Extension::Extension, (void (const class v8::Extension &))) \
  X(CXXMethod, v8::Extension::operator=, (void (const class v8::Extension &))) \
  X(Disabled, v8::RegisterExtension, (void (class std::unique_ptr<class v8::Extension, struct std::default_delete<class v8::Extension> >))) \
  X(Function, v8::Undefined, (class v8::Local<class v8::Primitive> (class v8::Isolate *))) \
  X(Function, v8::Null, (class v8::Local<class v8::Primitive> (class v8::Isolate *))) \
  X(Function, v8::True, (class v8::Local<class v8::Boolean> (class v8::Isolate *))) \
  X(Function, v8::False, (class v8::Local<class v8::Boolean> (class v8::Isolate *))) \
  X(CXXMethod, v8::ResourceConstraints::ConfigureDefaultsFromHeapSize, (void (unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::ConfigureDefaults, (void (unsigned long long, unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::stack_limit, (unsigned int *(void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_stack_limit, (void (unsigned int *))) \
  X(CXXMethod, v8::ResourceConstraints::code_range_size_in_bytes, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_code_range_size_in_bytes, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::max_old_generation_size_in_bytes, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_max_old_generation_size_in_bytes, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::max_young_generation_size_in_bytes, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_max_young_generation_size_in_bytes, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::initial_old_generation_size_in_bytes, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_initial_old_generation_size_in_bytes, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::initial_young_generation_size_in_bytes, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_initial_young_generation_size_in_bytes, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::code_range_size, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_code_range_size, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::max_semi_space_size_in_kb, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_max_semi_space_size_in_kb, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::max_old_space_size, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_max_old_space_size, (void (unsigned long long))) \
  X(CXXMethod, v8::ResourceConstraints::max_zone_pool_size, (unsigned long long (void) const)) \
  X(CXXMethod, v8::ResourceConstraints::set_max_zone_pool_size, (void (unsigned long long))) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, (void (void))) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, (void (const class v8::ResourceConstraints &))) \
  X(CXXConstructor, v8::ResourceConstraints::ResourceConstraints, (void (class v8::ResourceConstraints &&))) \
  X(CXXMethod, v8::Exception::RangeError, (class v8::Local<class v8::Value> (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Exception::ReferenceError, (class v8::Local<class v8::Value> (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Exception::SyntaxError, (class v8::Local<class v8::Value> (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Exception::TypeError, (class v8::Local<class v8::Value> (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Exception::Error, (class v8::Local<class v8::Value> (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Exception::CreateMessage, (class v8::Local<class v8::Message> (class v8::Isolate *, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Exception::GetStackTrace, (class v8::Local<class v8::StackTrace> (class v8::Local<class v8::Value>))) \
  X(CXXConstructor, v8::PromiseRejectMessage::PromiseRejectMessage, (void (class v8::Local<class v8::Promise>, enum v8::PromiseRejectEvent, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::PromiseRejectMessage::GetPromise, (class v8::Local<class v8::Promise> (void) const)) \
  X(CXXMethod, v8::PromiseRejectMessage::GetEvent, (enum v8::PromiseRejectEvent (void) const)) \
  X(CXXMethod, v8::PromiseRejectMessage::GetValue, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::MicrotaskQueue::New, (class std::unique_ptr<class v8::MicrotaskQueue, struct std::default_delete<class v8::MicrotaskQueue> > (class v8::Isolate *, enum v8::MicrotasksPolicy))) \
  X(CXXDestructor, v8::MicrotaskQueue::~MicrotaskQueue, (void (void))) \
  X(CXXMethod, v8::MicrotaskQueue::EnqueueMicrotask, (void (class v8::Isolate *, class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::MicrotaskQueue::EnqueueMicrotask, (void (class v8::Isolate *, void (*)(void *), void *))) \
  X(CXXMethod, v8::MicrotaskQueue::AddMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *, void *), void *))) \
  X(CXXMethod, v8::MicrotaskQueue::RemoveMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *, void *), void *))) \
  X(CXXMethod, v8::MicrotaskQueue::PerformCheckpoint, (void (class v8::Isolate *))) \
  X(CXXMethod, v8::MicrotaskQueue::IsRunningMicrotasks, (_Bool (void) const)) \
  X(CXXMethod, v8::MicrotaskQueue::GetMicrotasksScopeDepth, (int (void) const)) \
  X(CXXConstructor, v8::MicrotaskQueue::MicrotaskQueue, (void (const class v8::MicrotaskQueue &))) \
  X(CXXMethod, v8::MicrotaskQueue::operator=, (class v8::MicrotaskQueue &(const class v8::MicrotaskQueue &))) \
  X(CXXConstructor, v8::MicrotasksScope::MicrotasksScope, (void (class v8::Isolate *, enum v8::MicrotasksScope::Type))) \
  X(CXXConstructor, v8::MicrotasksScope::MicrotasksScope, (void (class v8::Isolate *, class v8::MicrotaskQueue *, enum v8::MicrotasksScope::Type))) \
  X(CXXDestructor, v8::MicrotasksScope::~MicrotasksScope, (void (void))) \
  X(CXXMethod, v8::MicrotasksScope::PerformCheckpoint, (void (class v8::Isolate *))) \
  X(CXXMethod, v8::MicrotasksScope::GetCurrentDepth, (int (class v8::Isolate *))) \
  X(CXXMethod, v8::MicrotasksScope::IsRunningMicrotasks, (_Bool (class v8::Isolate *))) \
  X(CXXConstructor, v8::MicrotasksScope::MicrotasksScope, (void (const class v8::MicrotasksScope &))) \
  X(CXXMethod, v8::MicrotasksScope::operator=, (class v8::MicrotasksScope &(const class v8::MicrotasksScope &))) \
  X(CXXConstructor, v8::HeapStatistics::HeapStatistics, (void (void))) \
  X(CXXMethod, v8::HeapStatistics::total_heap_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::total_heap_size_executable, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::total_physical_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::total_available_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::used_heap_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::heap_size_limit, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::malloced_memory, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::external_memory, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::peak_malloced_memory, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::number_of_native_contexts, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::number_of_detached_contexts, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapStatistics::does_zap_garbage, (unsigned long long (void))) \
  X(CXXConstructor, v8::HeapSpaceStatistics::HeapSpaceStatistics, (void (void))) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_name, (const char *(void))) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_used_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapSpaceStatistics::space_available_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapSpaceStatistics::physical_space_size, (unsigned long long (void))) \
  X(CXXConstructor, v8::HeapObjectStatistics::HeapObjectStatistics, (void (void))) \
  X(CXXMethod, v8::HeapObjectStatistics::object_type, (const char *(void))) \
  X(CXXMethod, v8::HeapObjectStatistics::object_sub_type, (const char *(void))) \
  X(CXXMethod, v8::HeapObjectStatistics::object_count, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapObjectStatistics::object_size, (unsigned long long (void))) \
  X(CXXConstructor, v8::HeapCodeStatistics::HeapCodeStatistics, (void (void))) \
  X(CXXMethod, v8::HeapCodeStatistics::code_and_metadata_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapCodeStatistics::bytecode_and_metadata_size, (unsigned long long (void))) \
  X(CXXMethod, v8::HeapCodeStatistics::external_script_source_size, (unsigned long long (void))) \
  X(CXXDestructor, v8::ExternalResourceVisitor::~ExternalResourceVisitor, (void (void))) \
  X(CXXMethod, v8::ExternalResourceVisitor::VisitExternalString, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::ExternalResourceVisitor::operator=, (class v8::ExternalResourceVisitor &(const class v8::ExternalResourceVisitor &))) \
  X(CXXDestructor, v8::PersistentHandleVisitor::~PersistentHandleVisitor, (void (void))) \
  X(CXXMethod, v8::PersistentHandleVisitor::VisitPersistentHandle, (void (class v8::Persistent<class v8::Value, class v8::NonCopyablePersistentTraits<class v8::Value> > *, unsigned short))) \
  X(CXXMethod, v8::PersistentHandleVisitor::operator=, (class v8::PersistentHandleVisitor &(const class v8::PersistentHandleVisitor &))) \
  X(CXXDestructor, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::~TracedGlobalHandleVisitor, (void (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::VisitTracedGlobalHandle, (void (const class v8::TracedGlobal<class v8::Value> &))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracedGlobalHandleVisitor::operator=, (class v8::EmbedderHeapTracer::TracedGlobalHandleVisitor &(const class v8::EmbedderHeapTracer::TracedGlobalHandleVisitor &))) \
  X(CXXDestructor, v8::EmbedderHeapTracer::~EmbedderHeapTracer, (void (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::IterateTracedGlobalHandles, (void (class v8::EmbedderHeapTracer::TracedGlobalHandleVisitor *))) \
  X(CXXMethod, v8::EmbedderHeapTracer::RegisterV8References, (void (const class std::vector<struct std::pair<void *, void *>, class std::allocator<struct std::pair<void *, void *> > > &))) \
  X(CXXMethod, v8::EmbedderHeapTracer::RegisterEmbedderReference, (void (const class v8::TracedGlobal<class v8::Value> &))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracePrologue, (void (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TracePrologue, (void (enum v8::EmbedderHeapTracer::TraceFlags))) \
  X(CXXMethod, v8::EmbedderHeapTracer::AdvanceTracing, (_Bool (double))) \
  X(CXXMethod, v8::EmbedderHeapTracer::IsTracingDone, (_Bool (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TraceEpilogue, (void (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::TraceEpilogue, (void (struct v8::EmbedderHeapTracer::TraceSummary *))) \
  X(CXXMethod, v8::EmbedderHeapTracer::EnterFinalPause, (void (enum v8::EmbedderHeapTracer::EmbedderStackState))) \
  X(CXXMethod, v8::EmbedderHeapTracer::FinalizeTracing, (void (void))) \
  X(CXXMethod, v8::EmbedderHeapTracer::IsRootForNonTracingGC, (_Bool (const class v8::TracedGlobal<class v8::Value> &))) \
  X(CXXMethod, v8::EmbedderHeapTracer::GarbageCollectionForTesting, (void (enum v8::EmbedderHeapTracer::EmbedderStackState))) \
  X(CXXMethod, v8::EmbedderHeapTracer::IncreaseAllocatedSize, (void (unsigned long long))) \
  X(CXXMethod, v8::EmbedderHeapTracer::DecreaseAllocatedSize, (void (unsigned long long))) \
  X(CXXMethod, v8::EmbedderHeapTracer::isolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::EmbedderHeapTracer::operator=, (class v8::EmbedderHeapTracer &(const class v8::EmbedderHeapTracer &))) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, (void (class v8::StartupData (*)(class v8::Local<class v8::Object>, int, void *), void *))) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, (void (const struct v8::SerializeInternalFieldsCallback &))) \
  X(CXXConstructor, v8::SerializeInternalFieldsCallback::SerializeInternalFieldsCallback, (void (struct v8::SerializeInternalFieldsCallback &&))) \
  X(CXXDestructor, v8::SerializeInternalFieldsCallback::~SerializeInternalFieldsCallback, (void (void))) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, (void (void (*)(class v8::Local<class v8::Object>, int, class v8::StartupData, void *), void *))) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, (void (const struct v8::DeserializeInternalFieldsCallback &))) \
  X(CXXConstructor, v8::DeserializeInternalFieldsCallback::DeserializeInternalFieldsCallback, (void (struct v8::DeserializeInternalFieldsCallback &&))) \
  X(CXXDestructor, v8::DeserializeInternalFieldsCallback::~DeserializeInternalFieldsCallback, (void (void))) \
  X(CXXConstructor, v8::Isolate::CreateParams::CreateParams, (void (void))) \
  X(CXXConstructor, v8::Isolate::Scope::Scope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::Isolate::Scope::~Scope, (void (void))) \
  X(CXXConstructor, v8::Isolate::Scope::Scope, (void (const class v8::Isolate::Scope &))) \
  X(CXXMethod, v8::Isolate::Scope::operator=, (class v8::Isolate::Scope &(const class v8::Isolate::Scope &))) \
  X(CXXConstructor, v8::Isolate::DisallowJavascriptExecutionScope::DisallowJavascriptExecutionScope, (void (class v8::Isolate *, enum v8::Isolate::DisallowJavascriptExecutionScope::OnFailure))) \
  X(CXXDestructor, v8::Isolate::DisallowJavascriptExecutionScope::~DisallowJavascriptExecutionScope, (void (void))) \
  X(CXXConstructor, v8::Isolate::DisallowJavascriptExecutionScope::DisallowJavascriptExecutionScope, (void (const class v8::Isolate::DisallowJavascriptExecutionScope &))) \
  X(CXXMethod, v8::Isolate::DisallowJavascriptExecutionScope::operator=, (class v8::Isolate::DisallowJavascriptExecutionScope &(const class v8::Isolate::DisallowJavascriptExecutionScope &))) \
  X(CXXConstructor, v8::Isolate::AllowJavascriptExecutionScope::AllowJavascriptExecutionScope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::Isolate::AllowJavascriptExecutionScope::~AllowJavascriptExecutionScope, (void (void))) \
  X(CXXConstructor, v8::Isolate::AllowJavascriptExecutionScope::AllowJavascriptExecutionScope, (void (const class v8::Isolate::AllowJavascriptExecutionScope &))) \
  X(CXXMethod, v8::Isolate::AllowJavascriptExecutionScope::operator=, (class v8::Isolate::AllowJavascriptExecutionScope &(const class v8::Isolate::AllowJavascriptExecutionScope &))) \
  X(CXXConstructor, v8::Isolate::SuppressMicrotaskExecutionScope::SuppressMicrotaskExecutionScope, (void (class v8::Isolate *))) \
  X(CXXConstructor, v8::Isolate::SuppressMicrotaskExecutionScope::SuppressMicrotaskExecutionScope, (void (class v8::MicrotaskQueue *))) \
  X(CXXDestructor, v8::Isolate::SuppressMicrotaskExecutionScope::~SuppressMicrotaskExecutionScope, (void (void))) \
  X(CXXConstructor, v8::Isolate::SuppressMicrotaskExecutionScope::SuppressMicrotaskExecutionScope, (void (const class v8::Isolate::SuppressMicrotaskExecutionScope &))) \
  X(CXXMethod, v8::Isolate::SuppressMicrotaskExecutionScope::operator=, (class v8::Isolate::SuppressMicrotaskExecutionScope &(const class v8::Isolate::SuppressMicrotaskExecutionScope &))) \
  X(CXXConstructor, v8::Isolate::SafeForTerminationScope::SafeForTerminationScope, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::Isolate::SafeForTerminationScope::~SafeForTerminationScope, (void (void))) \
  X(CXXConstructor, v8::Isolate::SafeForTerminationScope::SafeForTerminationScope, (void (const class v8::Isolate::SafeForTerminationScope &))) \
  X(CXXMethod, v8::Isolate::SafeForTerminationScope::operator=, (class v8::Isolate::SafeForTerminationScope &(const class v8::Isolate::SafeForTerminationScope &))) \
  X(CXXMethod, v8::Isolate::Allocate, (class v8::Isolate *(void))) \
  X(CXXMethod, v8::Isolate::Initialize, (void (class v8::Isolate *, const struct v8::Isolate::CreateParams &))) \
  X(CXXMethod, v8::Isolate::New, (class v8::Isolate *(const struct v8::Isolate::CreateParams &))) \
  X(CXXMethod, v8::Isolate::GetCurrent, (class v8::Isolate *(void))) \
  X(CXXMethod, v8::Isolate::SetAbortOnUncaughtExceptionCallback, (void (_Bool (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::SetHostImportModuleDynamicallyCallback, (void (class v8::MaybeLocal<class v8::Promise> (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::ScriptOrModule>, class v8::Local<class v8::String>)))) \
  X(CXXMethod, v8::Isolate::SetHostInitializeImportMetaObjectCallback, (void (void (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::Module>, class v8::Local<class v8::Object>)))) \
  X(CXXMethod, v8::Isolate::SetPrepareStackTraceCallback, (void (class v8::MaybeLocal<class v8::Value> (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::Value>, class v8::Local<class v8::Array>)))) \
  X(CXXMethod, v8::Isolate::MemoryPressureNotification, (void (enum v8::MemoryPressureLevel))) \
  X(CXXMethod, v8::Isolate::Enter, (void (void))) \
  X(CXXMethod, v8::Isolate::Exit, (void (void))) \
  X(CXXMethod, v8::Isolate::Dispose, (void (void))) \
  X(CXXMethod, v8::Isolate::DumpAndResetStats, (void (void))) \
  X(CXXMethod, v8::Isolate::DiscardThreadSpecificMetadata, (void (void))) \
  X(CXXMethod, v8::Isolate::SetData, (void (unsigned int, void *))) \
  X(CXXMethod, v8::Isolate::GetData, (void *(unsigned int))) \
  X(CXXMethod, v8::Isolate::GetNumberOfDataSlots, (unsigned int (void))) \
  X(CXXMethod, v8::Isolate::GetHeapStatistics, (void (class v8::HeapStatistics *))) \
  X(CXXMethod, v8::Isolate::NumberOfHeapSpaces, (unsigned long long (void))) \
  X(CXXMethod, v8::Isolate::GetHeapSpaceStatistics, (_Bool (class v8::HeapSpaceStatistics *, unsigned long long))) \
  X(CXXMethod, v8::Isolate::NumberOfTrackedHeapObjectTypes, (unsigned long long (void))) \
  X(CXXMethod, v8::Isolate::GetHeapObjectStatisticsAtLastGC, (_Bool (class v8::HeapObjectStatistics *, unsigned long long))) \
  X(CXXMethod, v8::Isolate::GetHeapCodeAndMetadataStatistics, (_Bool (class v8::HeapCodeStatistics *))) \
  X(CXXMethod, v8::Isolate::GetStackSample, (void (const struct v8::RegisterState &, void **, unsigned long long, struct v8::SampleInfo *))) \
  X(CXXMethod, v8::Isolate::AdjustAmountOfExternalAllocatedMemory, (long long (long long))) \
  X(CXXMethod, v8::Isolate::NumberOfPhantomHandleResetsSinceLastCall, (unsigned long long (void))) \
  X(CXXMethod, v8::Isolate::GetHeapProfiler, (class v8::HeapProfiler *(void))) \
  X(CXXMethod, v8::Isolate::SetIdle, (void (_Bool))) \
  X(CXXMethod, v8::Isolate::GetArrayBufferAllocator, (class v8::ArrayBuffer::Allocator *(void))) \
  X(CXXMethod, v8::Isolate::InContext, (_Bool (void))) \
  X(CXXMethod, v8::Isolate::GetCurrentContext, (class v8::Local<class v8::Context> (void))) \
  X(CXXMethod, v8::Isolate::GetEnteredContext, (class v8::Local<class v8::Context> (void))) \
  X(CXXMethod, v8::Isolate::GetEnteredOrMicrotaskContext, (class v8::Local<class v8::Context> (void))) \
  X(CXXMethod, v8::Isolate::GetIncumbentContext, (class v8::Local<class v8::Context> (void))) \
  X(CXXMethod, v8::Isolate::ThrowException, (class v8::Local<class v8::Value> (class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Isolate::AddGCPrologueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags, void *), void *, enum v8::GCType))) \
  X(CXXMethod, v8::Isolate::AddGCPrologueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags), enum v8::GCType))) \
  X(CXXMethod, v8::Isolate::RemoveGCPrologueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags, void *), void *))) \
  X(CXXMethod, v8::Isolate::RemoveGCPrologueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags)))) \
  X(CXXMethod, v8::Isolate::SetEmbedderHeapTracer, (void (class v8::EmbedderHeapTracer *))) \
  X(CXXMethod, v8::Isolate::GetEmbedderHeapTracer, (class v8::EmbedderHeapTracer *(void))) \
  X(CXXMethod, v8::Isolate::AtomicsWaitWakeHandle::Wake, (void (void))) \
  X(CXXMethod, v8::Isolate::SetAtomicsWaitCallback, (void (void (*)(enum v8::Isolate::AtomicsWaitEvent, class v8::Local<class v8::SharedArrayBuffer>, unsigned long long, long long, double, class v8::Isolate::AtomicsWaitWakeHandle *, void *), void *))) \
  X(CXXMethod, v8::Isolate::AddGCEpilogueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags, void *), void *, enum v8::GCType))) \
  X(CXXMethod, v8::Isolate::AddGCEpilogueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags), enum v8::GCType))) \
  X(CXXMethod, v8::Isolate::RemoveGCEpilogueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags, void *), void *))) \
  X(CXXMethod, v8::Isolate::RemoveGCEpilogueCallback, (void (void (*)(class v8::Isolate *, enum v8::GCType, enum v8::GCCallbackFlags)))) \
  X(CXXMethod, v8::Isolate::SetGetExternallyAllocatedMemoryInBytesCallback, (void (unsigned long long (*)(void)))) \
  X(CXXMethod, v8::Isolate::TerminateExecution, (void (void))) \
  X(CXXMethod, v8::Isolate::IsExecutionTerminating, (_Bool (void))) \
  X(CXXMethod, v8::Isolate::CancelTerminateExecution, (void (void))) \
  X(CXXMethod, v8::Isolate::RequestInterrupt, (void (void (*)(class v8::Isolate *, void *), void *))) \
  X(CXXMethod, v8::Isolate::RequestGarbageCollectionForTesting, (void (enum v8::Isolate::GarbageCollectionType))) \
  X(CXXMethod, v8::Isolate::SetEventLogger, (void (void (*)(const char *, int)))) \
  X(CXXMethod, v8::Isolate::AddBeforeCallEnteredCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::RemoveBeforeCallEnteredCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::AddCallCompletedCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::RemoveCallCompletedCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::SetPromiseHook, (void (void (*)(enum v8::PromiseHookType, class v8::Local<class v8::Promise>, class v8::Local<class v8::Value>)))) \
  X(CXXMethod, v8::Isolate::SetPromiseRejectCallback, (void (void (*)(class v8::PromiseRejectMessage)))) \
  X(CXXMethod, v8::Isolate::RunMicrotasks, (void (void))) \
  X(CXXMethod, v8::Isolate::EnqueueMicrotask, (void (class v8::Local<class v8::Function>))) \
  X(CXXMethod, v8::Isolate::EnqueueMicrotask, (void (void (*)(void *), void *))) \
  X(CXXMethod, v8::Isolate::SetMicrotasksPolicy, (void (enum v8::MicrotasksPolicy))) \
  X(CXXMethod, v8::Isolate::GetMicrotasksPolicy, (enum v8::MicrotasksPolicy (void) const)) \
  X(CXXMethod, v8::Isolate::AddMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::AddMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *, void *), void *))) \
  X(CXXMethod, v8::Isolate::RemoveMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *)))) \
  X(CXXMethod, v8::Isolate::RemoveMicrotasksCompletedCallback, (void (void (*)(class v8::Isolate *, void *), void *))) \
  X(CXXMethod, v8::Isolate::SetUseCounterCallback, (void (void (*)(class v8::Isolate *, enum v8::Isolate::UseCounterFeature)))) \
  X(CXXMethod, v8::Isolate::SetCounterFunction, (void (int *(*)(const char *)))) \
  X(CXXMethod, v8::Isolate::SetCreateHistogramFunction, (void (void *(*)(const char *, int, int, unsigned long long)))) \
  X(CXXMethod, v8::Isolate::SetAddHistogramSampleFunction, (void (void (*)(void *, int)))) \
  X(CXXMethod, v8::Isolate::IdleNotificationDeadline, (_Bool (double))) \
  X(CXXMethod, v8::Isolate::LowMemoryNotification, (void (void))) \
  X(CXXMethod, v8::Isolate::ContextDisposedNotification, (int (_Bool))) \
  X(CXXMethod, v8::Isolate::IsolateInForegroundNotification, (void (void))) \
  X(CXXMethod, v8::Isolate::IsolateInBackgroundNotification, (void (void))) \
  X(CXXMethod, v8::Isolate::EnableMemorySavingsMode, (void (void))) \
  X(CXXMethod, v8::Isolate::DisableMemorySavingsMode, (void (void))) \
  X(CXXMethod, v8::Isolate::SetRAILMode, (void (enum v8::RAILMode))) \
  X(CXXMethod, v8::Isolate::IncreaseHeapLimitForDebugging, (void (void))) \
  X(CXXMethod, v8::Isolate::RestoreOriginalHeapLimit, (void (void))) \
  X(CXXMethod, v8::Isolate::IsHeapLimitIncreasedForDebugging, (_Bool (void))) \
  X(CXXMethod, v8::Isolate::SetJitCodeEventHandler, (void (enum v8::JitCodeEventOptions, void (*)(const struct v8::JitCodeEvent *)))) \
  X(CXXMethod, v8::Isolate::SetStackLimit, (void (unsigned long long))) \
  X(CXXMethod, v8::Isolate::GetCodeRange, (void (void **, unsigned long long *))) \
  X(CXXMethod, v8::Isolate::GetUnwindState, (struct v8::UnwindState (void))) \
  X(CXXMethod, v8::Isolate::SetFatalErrorHandler, (void (void (*)(const char *, const char *)))) \
  X(CXXMethod, v8::Isolate::SetOOMErrorHandler, (void (void (*)(const char *, _Bool)))) \
  X(CXXMethod, v8::Isolate::AddNearHeapLimitCallback, (void (unsigned long long (*)(void *, unsigned long long, unsigned long long), void *))) \
  X(CXXMethod, v8::Isolate::RemoveNearHeapLimitCallback, (void (unsigned long long (*)(void *, unsigned long long, unsigned long long), unsigned long long))) \
  X(CXXMethod, v8::Isolate::AutomaticallyRestoreInitialHeapLimit, (void (double))) \
  X(CXXMethod, v8::Isolate::SetAllowCodeGenerationFromStringsCallback, (void (_Bool (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::String>)))) \
  X(CXXMethod, v8::Isolate::SetAllowWasmCodeGenerationCallback, (void (_Bool (*)(class v8::Local<class v8::Context>, class v8::Local<class v8::String>)))) \
  X(CXXMethod, v8::Isolate::SetWasmModuleCallback, (void (_Bool (*)(const class v8::FunctionCallbackInfo<class v8::Value> &)))) \
  X(CXXMethod, v8::Isolate::SetWasmInstanceCallback, (void (_Bool (*)(const class v8::FunctionCallbackInfo<class v8::Value> &)))) \
  X(CXXMethod, v8::Isolate::SetWasmStreamingCallback, (void (void (*)(const class v8::FunctionCallbackInfo<class v8::Value> &)))) \
  X(CXXMethod, v8::Isolate::SetWasmThreadsEnabledCallback, (void (_Bool (*)(class v8::Local<class v8::Context>)))) \
  X(CXXMethod, v8::Isolate::IsDead, (_Bool (void))) \
  X(CXXMethod, v8::Isolate::AddMessageListener, (_Bool (void (*)(class v8::Local<class v8::Message>, class v8::Local<class v8::Value>), class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Isolate::AddMessageListenerWithErrorLevel, (_Bool (void (*)(class v8::Local<class v8::Message>, class v8::Local<class v8::Value>), int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Isolate::RemoveMessageListeners, (void (void (*)(class v8::Local<class v8::Message>, class v8::Local<class v8::Value>)))) \
  X(CXXMethod, v8::Isolate::SetFailedAccessCheckCallbackFunction, (void (void (*)(class v8::Local<class v8::Object>, enum v8::AccessType, class v8::Local<class v8::Value>)))) \
  X(CXXMethod, v8::Isolate::SetCaptureStackTraceForUncaughtExceptions, (void (_Bool, int, enum v8::StackTrace::StackTraceOptions))) \
  X(CXXMethod, v8::Isolate::VisitExternalResources, (void (class v8::ExternalResourceVisitor *))) \
  X(CXXMethod, v8::Isolate::VisitHandlesWithClassIds, (void (class v8::PersistentHandleVisitor *))) \
  X(CXXMethod, v8::Isolate::VisitWeakHandles, (void (class v8::PersistentHandleVisitor *))) \
  X(CXXMethod, v8::Isolate::IsInUse, (_Bool (void))) \
  X(CXXMethod, v8::Isolate::SetAllowAtomicsWait, (void (_Bool))) \
  X(CXXMethod, v8::Isolate::DateTimeConfigurationChangeNotification, (void (enum v8::Isolate::TimeZoneDetection))) \
  X(CXXMethod, v8::Isolate::LocaleConfigurationChangeNotification, (void (void))) \
  X(CXXConstructor, v8::Isolate::Isolate, (void (void))) \
  X(CXXDestructor, v8::Isolate::~Isolate, (void (void))) \
  X(CXXConstructor, v8::Isolate::Isolate, (void (const class v8::Isolate &))) \
  X(CXXMethod, v8::Isolate::operator=, (class v8::Isolate &(const class v8::Isolate &))) \
  X(CXXMethod, v8::Isolate::operator new, (void *(unsigned long long))) \
  X(CXXMethod, v8::Isolate::operator new[], (void *(unsigned long long))) \
  X(CXXMethod, v8::Isolate::operator delete, (void (void *, unsigned long long))) \
  X(CXXMethod, v8::Isolate::operator delete[], (void (void *, unsigned long long))) \
  X(CXXMethod, v8::StartupData::CanBeRehashed, (_Bool (void) const)) \
  X(CXXMethod, v8::V8::SetNativesDataBlob, (void (class v8::StartupData *))) \
  X(CXXMethod, v8::V8::SetSnapshotDataBlob, (void (class v8::StartupData *))) \
  X(CXXMethod, v8::V8::SetDcheckErrorHandler, (void (void (*)(const char *, int, const char *)))) \
  X(CXXMethod, v8::V8::SetFlagsFromString, (void (const char *))) \
  X(CXXMethod, v8::V8::SetFlagsFromString, (void (const char *, unsigned long long))) \
  X(CXXMethod, v8::V8::SetFlagsFromString, (void (const char *, int))) \
  X(CXXMethod, v8::V8::SetFlagsFromCommandLine, (void (int *, char **, _Bool))) \
  X(CXXMethod, v8::V8::GetVersion, (const char *(void))) \
  X(CXXMethod, v8::V8::Initialize, (_Bool (void))) \
  X(CXXMethod, v8::V8::SetEntropySource, (void (_Bool (*)(unsigned char *, unsigned long long)))) \
  X(CXXMethod, v8::V8::SetReturnAddressLocationResolver, (void (unsigned long long (*)(unsigned long long)))) \
  X(CXXMethod, v8::V8::Dispose, (_Bool (void))) \
  X(CXXMethod, v8::V8::InitializeICU, (_Bool (const char *))) \
  X(CXXMethod, v8::V8::InitializeICUDefaultLocation, (_Bool (const char *, const char *))) \
  X(CXXMethod, v8::V8::InitializeExternalStartupData, (void (const char *))) \
  X(CXXMethod, v8::V8::InitializeExternalStartupData, (void (const char *, const char *))) \
  X(CXXMethod, v8::V8::InitializePlatform, (void (class v8::Platform *))) \
  X(CXXMethod, v8::V8::ShutdownPlatform, (void (void))) \
  X(CXXMethod, v8::V8::EnableWebAssemblyTrapHandler, (_Bool (_Bool))) \
  X(CXXMethod, v8::V8::SetUnhandledExceptionCallback, (void (int (*)(struct _EXCEPTION_POINTERS *)))) \
  X(CXXConstructor, v8::SnapshotCreator::SnapshotCreator, (void (class v8::Isolate *, const long long *, class v8::StartupData *))) \
  X(CXXConstructor, v8::SnapshotCreator::SnapshotCreator, (void (const long long *, class v8::StartupData *))) \
  X(CXXDestructor, v8::SnapshotCreator::~SnapshotCreator, (void (void))) \
  X(CXXMethod, v8::SnapshotCreator::GetIsolate, (class v8::Isolate *(void))) \
  X(CXXMethod, v8::SnapshotCreator::SetDefaultContext, (void (class v8::Local<class v8::Context>, struct v8::SerializeInternalFieldsCallback))) \
  X(CXXMethod, v8::SnapshotCreator::AddContext, (unsigned long long (class v8::Local<class v8::Context>, struct v8::SerializeInternalFieldsCallback))) \
  X(CXXMethod, v8::SnapshotCreator::AddTemplate, (unsigned long long (class v8::Local<class v8::Template>))) \
  X(CXXMethod, v8::SnapshotCreator::CreateBlob, (class v8::StartupData (enum v8::SnapshotCreator::FunctionCodeHandling))) \
  X(CXXConstructor, v8::SnapshotCreator::SnapshotCreator, (void (const class v8::SnapshotCreator &))) \
  X(CXXMethod, v8::SnapshotCreator::operator=, (void (const class v8::SnapshotCreator &))) \
  X(CXXMethod, v8::Maybe::IsNothing, (_Bool (void) const)) \
  X(CXXMethod, v8::Maybe::IsJust, (_Bool (void) const)) \
  X(CXXMethod, v8::Maybe::Check, (void (void) const)) \
  X(CXXMethod, v8::Maybe<void>::IsNothing, (_Bool (void) const)) \
  X(CXXMethod, v8::Maybe<void>::IsJust, (_Bool (void) const)) \
  X(CXXMethod, v8::Maybe<void>::operator==, (_Bool (const class v8::Maybe<void> &) const)) \
  X(CXXMethod, v8::Maybe<void>::operator!=, (_Bool (const class v8::Maybe<void> &) const)) \
  X(CXXConstructor, v8::Maybe<void>::Maybe, (void (const class v8::Maybe<void> &))) \
  X(CXXConstructor, v8::Maybe<void>::Maybe, (void (class v8::Maybe<void> &&))) \
  X(CXXDestructor, v8::Maybe<void>::~Maybe, (void (void))) \
  X(Function, v8::JustVoid, (class v8::Maybe<void> (void))) \
  X(CXXConstructor, v8::TryCatch::TryCatch, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::TryCatch::~TryCatch, (void (void))) \
  X(CXXMethod, v8::TryCatch::HasCaught, (_Bool (void) const)) \
  X(CXXMethod, v8::TryCatch::CanContinue, (_Bool (void) const)) \
  X(CXXMethod, v8::TryCatch::HasTerminated, (_Bool (void) const)) \
  X(CXXMethod, v8::TryCatch::ReThrow, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::TryCatch::Exception, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::TryCatch::StackTrace, (class v8::MaybeLocal<class v8::Value> (class v8::Local<class v8::Context>) const)) \
  X(CXXMethod, v8::TryCatch::Message, (class v8::Local<class v8::Message> (void) const)) \
  X(CXXMethod, v8::TryCatch::Reset, (void (void))) \
  X(CXXMethod, v8::TryCatch::SetVerbose, (void (_Bool))) \
  X(CXXMethod, v8::TryCatch::IsVerbose, (_Bool (void) const)) \
  X(CXXMethod, v8::TryCatch::SetCaptureMessage, (void (_Bool))) \
  X(CXXMethod, v8::TryCatch::JSStackComparableAddress, (void *(class v8::TryCatch *))) \
  X(CXXConstructor, v8::TryCatch::TryCatch, (void (const class v8::TryCatch &))) \
  X(CXXMethod, v8::TryCatch::operator=, (void (const class v8::TryCatch &))) \
  X(CXXConstructor, v8::ExtensionConfiguration::ExtensionConfiguration, (void (void))) \
  X(CXXConstructor, v8::ExtensionConfiguration::ExtensionConfiguration, (void (int, const char **))) \
  X(CXXMethod, v8::ExtensionConfiguration::begin, (const char **(void) const)) \
  X(CXXMethod, v8::ExtensionConfiguration::end, (const char **(void) const)) \
  X(CXXMethod, v8::Context::Global, (class v8::Local<class v8::Object> (void))) \
  X(CXXMethod, v8::Context::DetachGlobal, (void (void))) \
  X(CXXMethod, v8::Context::New, (class v8::Local<class v8::Context> (class v8::Isolate *, class v8::ExtensionConfiguration *, class v8::MaybeLocal<class v8::ObjectTemplate>, class v8::MaybeLocal<class v8::Value>, struct v8::DeserializeInternalFieldsCallback, class v8::MicrotaskQueue *))) \
  X(CXXMethod, v8::Context::FromSnapshot, (class v8::MaybeLocal<class v8::Context> (class v8::Isolate *, unsigned long long, struct v8::DeserializeInternalFieldsCallback, class v8::ExtensionConfiguration *, class v8::MaybeLocal<class v8::Value>, class v8::MicrotaskQueue *))) \
  X(CXXMethod, v8::Context::NewRemoteContext, (class v8::MaybeLocal<class v8::Object> (class v8::Isolate *, class v8::Local<class v8::ObjectTemplate>, class v8::MaybeLocal<class v8::Value>))) \
  X(CXXMethod, v8::Context::SetSecurityToken, (void (class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Context::UseDefaultSecurityToken, (void (void))) \
  X(CXXMethod, v8::Context::GetSecurityToken, (class v8::Local<class v8::Value> (void))) \
  X(CXXMethod, v8::Context::Enter, (void (void))) \
  X(CXXMethod, v8::Context::Exit, (void (void))) \
  X(CXXMethod, v8::Context::GetIsolate, (class v8::Isolate *(void))) \
  X(CXXMethod, v8::Context::GetNumberOfEmbedderDataFields, (unsigned int (void))) \
  X(CXXMethod, v8::Context::GetEmbedderData, (class v8::Local<class v8::Value> (int))) \
  X(CXXMethod, v8::Context::GetExtrasBindingObject, (class v8::Local<class v8::Object> (void))) \
  X(CXXMethod, v8::Context::SetEmbedderData, (void (int, class v8::Local<class v8::Value>))) \
  X(CXXMethod, v8::Context::GetAlignedPointerFromEmbedderData, (void *(int))) \
  X(CXXMethod, v8::Context::SetAlignedPointerInEmbedderData, (void (int, void *))) \
  X(CXXMethod, v8::Context::AllowCodeGenerationFromStrings, (void (_Bool))) \
  X(CXXMethod, v8::Context::IsCodeGenerationFromStringsAllowed, (_Bool (void))) \
  X(CXXMethod, v8::Context::SetErrorMessageForCodeGenerationFromStrings, (void (class v8::Local<class v8::String>))) \
  X(CXXMethod, v8::Context::SetAbortScriptExecution, (void (void (*)(class v8::Isolate *, class v8::Local<class v8::Context>)))) \
  X(CXXConstructor, v8::Context::Scope::Scope, (void (class v8::Local<class v8::Context>))) \
  X(CXXDestructor, v8::Context::Scope::~Scope, (void (void))) \
  X(CXXConstructor, v8::Context::BackupIncumbentScope::BackupIncumbentScope, (void (class v8::Local<class v8::Context>))) \
  X(CXXDestructor, v8::Context::BackupIncumbentScope::~BackupIncumbentScope, (void (void))) \
  X(CXXMethod, v8::Context::BackupIncumbentScope::JSStackComparableAddress, (unsigned long long (void) const)) \
  X(CXXConstructor, v8::Unlocker::Unlocker, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::Unlocker::~Unlocker, (void (void))) \
  X(CXXConstructor, v8::Locker::Locker, (void (class v8::Isolate *))) \
  X(CXXDestructor, v8::Locker::~Locker, (void (void))) \
  X(CXXMethod, v8::Locker::IsLocked, (_Bool (class v8::Isolate *))) \
  X(CXXMethod, v8::Locker::IsActive, (_Bool (void))) \
  X(CXXConstructor, v8::Locker::Locker, (void (const class v8::Locker &))) \
  X(CXXMethod, v8::Locker::operator=, (void (const class v8::Locker &))) \
  X(CXXMethod, v8::Unwinder::TryUnwindV8Frames, (_Bool (const struct v8::UnwindState &, struct v8::RegisterState *, const void *))) \
  X(CXXMethod, v8::Unwinder::PCIsInV8, (_Bool (const struct v8::UnwindState &, void *))) \
  X(CXXMethod, v8::WeakCallbackInfo::GetInternalField, (void *(int) const)) \
  X(CXXMethod, v8::PersistentBase::IsWeak, (_Bool (void) const)) \
  X(CXXMethod, v8::PersistentBase::Reset, (void (void))) \
  X(CXXMethod, v8::PersistentBase::SetWeak, (void (void))) \
  X(CXXMethod, v8::PersistentBase::AnnotateStrongRetainer, (void (const char *))) \
  X(CXXMethod, v8::PersistentBase::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::PersistentBase::WrapperClassId, (unsigned short (void) const)) \
  X(CXXMethod, v8::TracedGlobal::Reset, (void (void))) \
  X(CXXMethod, v8::TracedGlobal::SetWrapperClassId, (void (unsigned short))) \
  X(CXXMethod, v8::TracedGlobal::WrapperClassId, (unsigned short (void) const)) \
  X(CXXMethod, v8::TracedGlobal::SetFinalizationCallback, (void (void *, void (*)(const class v8::WeakCallbackInfo<void> &)))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (double))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (int))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (unsigned int))) \
  X(CXXMethod, v8::ReturnValue::Set, (void (_Bool))) \
  X(CXXMethod, v8::ReturnValue::SetNull, (void (void))) \
  X(CXXMethod, v8::ReturnValue::SetUndefined, (void (void))) \
  X(CXXMethod, v8::ReturnValue::SetEmptyString, (void (void))) \
  X(CXXMethod, v8::ReturnValue::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::ReturnValue::Get, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::operator[], (class v8::Local<class v8::Value> (int) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::This, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Holder, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::NewTarget, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Data, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::IsConstructCall, (_Bool (void) const)) \
  X(CXXMethod, v8::FunctionCallbackInfo::Length, (int (void) const)) \
  X(CXXConstructor, v8::ScriptOrigin::ScriptOrigin, (void (class v8::Local<class v8::Value>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Integer>, class v8::Local<class v8::Value>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::Boolean>, class v8::Local<class v8::PrimitiveArray>))) \
  X(CXXMethod, v8::ScriptOrigin::ResourceName, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::HostDefinedOptions, (class v8::Local<class v8::PrimitiveArray> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceLineOffset, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ResourceColumnOffset, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::ScriptID, (class v8::Local<class v8::Integer> (void) const)) \
  X(CXXMethod, v8::ScriptOrigin::SourceMapUrl, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, (void (class v8::Local<class v8::String>, const class v8::ScriptOrigin &, struct v8::ScriptCompiler::CachedData *))) \
  X(CXXConstructor, v8::ScriptCompiler::Source::Source, (void (class v8::Local<class v8::String>, struct v8::ScriptCompiler::CachedData *))) \
  X(CXXDestructor, v8::ScriptCompiler::Source::~Source, (void (void))) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetCachedData, (const struct v8::ScriptCompiler::CachedData *(void) const)) \
  X(CXXMethod, v8::ScriptCompiler::Source::GetResourceOptions, (const class v8::ScriptOriginOptions &(void) const)) \
  X(CXXMethod, v8::Boolean::New, (class v8::Local<class v8::Boolean> (class v8::Isolate *, _Bool))) \
  X(CXXMethod, v8::Template::Set, (void (class v8::Isolate *, const char *, class v8::Local<class v8::Data>))) \
  X(CXXMethod, v8::FunctionTemplate::Cast, (class v8::FunctionTemplate *(class v8::Data *))) \
  X(CXXMethod, v8::ObjectTemplate::Cast, (class v8::ObjectTemplate *(class v8::Data *))) \
  X(CXXMethod, v8::Signature::Cast, (class v8::Signature *(class v8::Data *))) \
  X(CXXMethod, v8::AccessorSignature::Cast, (class v8::AccessorSignature *(class v8::Data *))) \
  X(CXXMethod, v8::Object::GetInternalField, (class v8::Local<class v8::Value> (int))) \
  X(CXXMethod, v8::Object::GetAlignedPointerFromInternalField, (void *(int))) \
  X(CXXMethod, v8::String::Cast, (class v8::String *(class v8::Value *))) \
  X(CXXMethod, v8::String::Empty, (class v8::Local<class v8::String> (class v8::Isolate *))) \
  X(CXXMethod, v8::String::GetExternalStringResource, (class v8::String::ExternalStringResource *(void) const)) \
  X(CXXMethod, v8::String::GetExternalStringResourceBase, (class v8::String::ExternalStringResourceBase *(enum v8::String::Encoding *) const)) \
  X(CXXMethod, v8::Value::IsUndefined, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNull, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsNullOrUndefined, (_Bool (void) const)) \
  X(CXXMethod, v8::Value::IsString, (_Bool (void) const)) \
  X(CXXMethod, v8::Boolean::Cast, (class v8::Boolean *(class v8::Value *))) \
  X(CXXMethod, v8::Name::Cast, (class v8::Name *(class v8::Value *))) \
  X(CXXMethod, v8::Symbol::Cast, (class v8::Symbol *(class v8::Value *))) \
  X(CXXMethod, v8::Private::Cast, (class v8::Private *(class v8::Data *))) \
  X(CXXMethod, v8::Number::Cast, (class v8::Number *(class v8::Value *))) \
  X(CXXMethod, v8::Integer::Cast, (class v8::Integer *(class v8::Value *))) \
  X(CXXMethod, v8::Int32::Cast, (class v8::Int32 *(class v8::Value *))) \
  X(CXXMethod, v8::Uint32::Cast, (class v8::Uint32 *(class v8::Value *))) \
  X(CXXMethod, v8::BigInt::Cast, (class v8::BigInt *(class v8::Value *))) \
  X(CXXMethod, v8::Date::Cast, (class v8::Date *(class v8::Value *))) \
  X(CXXMethod, v8::StringObject::Cast, (class v8::StringObject *(class v8::Value *))) \
  X(CXXMethod, v8::SymbolObject::Cast, (class v8::SymbolObject *(class v8::Value *))) \
  X(CXXMethod, v8::NumberObject::Cast, (class v8::NumberObject *(class v8::Value *))) \
  X(CXXMethod, v8::BigIntObject::Cast, (class v8::BigIntObject *(class v8::Value *))) \
  X(CXXMethod, v8::BooleanObject::Cast, (class v8::BooleanObject *(class v8::Value *))) \
  X(CXXMethod, v8::RegExp::Cast, (class v8::RegExp *(class v8::Value *))) \
  X(CXXMethod, v8::Object::Cast, (class v8::Object *(class v8::Value *))) \
  X(CXXMethod, v8::Array::Cast, (class v8::Array *(class v8::Value *))) \
  X(CXXMethod, v8::Map::Cast, (class v8::Map *(class v8::Value *))) \
  X(CXXMethod, v8::Set::Cast, (class v8::Set *(class v8::Value *))) \
  X(CXXMethod, v8::Promise::Cast, (class v8::Promise *(class v8::Value *))) \
  X(CXXMethod, v8::Proxy::Cast, (class v8::Proxy *(class v8::Value *))) \
  X(CXXMethod, v8::WasmModuleObject::Cast, (class v8::WasmModuleObject *(class v8::Value *))) \
  X(CXXMethod, v8::Promise::Resolver::Cast, (class v8::Promise::Resolver *(class v8::Value *))) \
  X(CXXMethod, v8::ArrayBuffer::Cast, (class v8::ArrayBuffer *(class v8::Value *))) \
  X(CXXMethod, v8::ArrayBufferView::Cast, (class v8::ArrayBufferView *(class v8::Value *))) \
  X(CXXMethod, v8::TypedArray::Cast, (class v8::TypedArray *(class v8::Value *))) \
  X(CXXMethod, v8::Uint8Array::Cast, (class v8::Uint8Array *(class v8::Value *))) \
  X(CXXMethod, v8::Int8Array::Cast, (class v8::Int8Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint16Array::Cast, (class v8::Uint16Array *(class v8::Value *))) \
  X(CXXMethod, v8::Int16Array::Cast, (class v8::Int16Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint32Array::Cast, (class v8::Uint32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Int32Array::Cast, (class v8::Int32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Float32Array::Cast, (class v8::Float32Array *(class v8::Value *))) \
  X(CXXMethod, v8::Float64Array::Cast, (class v8::Float64Array *(class v8::Value *))) \
  X(CXXMethod, v8::BigInt64Array::Cast, (class v8::BigInt64Array *(class v8::Value *))) \
  X(CXXMethod, v8::BigUint64Array::Cast, (class v8::BigUint64Array *(class v8::Value *))) \
  X(CXXMethod, v8::Uint8ClampedArray::Cast, (class v8::Uint8ClampedArray *(class v8::Value *))) \
  X(CXXMethod, v8::DataView::Cast, (class v8::DataView *(class v8::Value *))) \
  X(CXXMethod, v8::SharedArrayBuffer::Cast, (class v8::SharedArrayBuffer *(class v8::Value *))) \
  X(CXXMethod, v8::Function::Cast, (class v8::Function *(class v8::Value *))) \
  X(CXXMethod, v8::External::Cast, (class v8::External *(class v8::Value *))) \
  X(CXXMethod, v8::PropertyCallbackInfo::GetIsolate, (class v8::Isolate *(void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::Data, (class v8::Local<class v8::Value> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::This, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::Holder, (class v8::Local<class v8::Object> (void) const)) \
  X(CXXMethod, v8::PropertyCallbackInfo::ShouldThrowOnError, (_Bool (void) const)) \
  X(Function, v8::Undefined, (class v8::Local<class v8::Primitive> (class v8::Isolate *))) \
  X(Function, v8::Null, (class v8::Local<class v8::Primitive> (class v8::Isolate *))) \
  X(Function, v8::True, (class v8::Local<class v8::Boolean> (class v8::Isolate *))) \
  X(Function, v8::False, (class v8::Local<class v8::Boolean> (class v8::Isolate *))) \
  X(CXXMethod, v8::Isolate::SetData, (void (unsigned int, void *))) \
  X(CXXMethod, v8::Isolate::GetData, (void *(unsigned int))) \
  X(CXXMethod, v8::Isolate::GetNumberOfDataSlots, (unsigned int (void))) \
  X(CXXMethod, v8::Isolate::AdjustAmountOfExternalAllocatedMemory, (long long (long long))) \
  X(CXXMethod, v8::Context::GetEmbedderData, (class v8::Local<class v8::Value> (int))) \
  X(CXXMethod, v8::Context::GetAlignedPointerFromEmbedderData, (void *(int))) \
// Done: 0
