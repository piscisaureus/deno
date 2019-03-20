 Namespace v8
   ClassDecl Context
   ClassDecl Data
   ClassDecl Isolate
 Namespace v8
   ClassDecl AccessorSignature
   ClassDecl Array
   ClassDecl ArrayBuffer
   ClassDecl BigInt
   ClassDecl BigIntObject
   ClassDecl Boolean
   ClassDecl BooleanObject
   ClassDecl Context
   ClassDecl Data
   ClassDecl Date
   ClassDecl External
   ClassDecl Function
   ClassDecl FunctionTemplate
   ClassDecl HeapProfiler
   ClassDecl ImplementationUtilities
   ClassDecl Int32
   ClassDecl Integer
   ClassDecl Isolate
   ClassTemplate Maybe<T>
     TemplateTypeParameter T
   ClassDecl Name
   ClassDecl Number
   ClassDecl NumberObject
   ClassDecl Object
   ClassDecl ObjectOperationDescriptor
   ClassDecl ObjectTemplate
   ClassDecl Platform
   ClassDecl Primitive
   ClassDecl Promise
   ClassDecl PropertyDescriptor
   ClassDecl Proxy
   ClassDecl RawOperationDescriptor
   ClassDecl Script
   ClassDecl SharedArrayBuffer
   ClassDecl Signature
   ClassDecl StartupData
   ClassDecl StackFrame
   ClassDecl StackTrace
   ClassDecl String
   ClassDecl StringObject
   ClassDecl Symbol
   ClassDecl SymbolObject
   ClassDecl PrimitiveArray
   ClassDecl Private
   ClassDecl Uint32
   ClassDecl Utils
   ClassDecl Value
   ClassDecl WasmModuleObject
   ClassTemplate Local<T>
     TemplateTypeParameter T
   ClassTemplate MaybeLocal<T>
     TemplateTypeParameter T
   ClassTemplate Eternal<T>
     TemplateTypeParameter T
   ClassTemplate NonCopyablePersistentTraits<T>
     TemplateTypeParameter T
   ClassTemplate PersistentBase<T>
     TemplateTypeParameter T
   ClassTemplate Persistent<T, M>
     TemplateTypeParameter T
     TemplateTypeParameter M
       TemplateRef NonCopyablePersistentTraits
       TypeRef T
   ClassTemplate Global<T>
     TemplateTypeParameter T
   ClassTemplate TracedGlobal<T>
     TemplateTypeParameter T
   ClassTemplate PersistentValueMap<K, V, T>
     TemplateTypeParameter K
     TemplateTypeParameter V
     TemplateTypeParameter T
   ClassTemplate PersistentValueMapBase<K, V, T>
     TemplateTypeParameter K
     TemplateTypeParameter V
     TemplateTypeParameter T
   ClassTemplate GlobalValueMap<K, V, T>
     TemplateTypeParameter K
     TemplateTypeParameter V
     TemplateTypeParameter T
   ClassTemplate PersistentValueVector<V, T>
     TemplateTypeParameter V
     TemplateTypeParameter T
   ClassTemplate WeakCallbackObject<T, P>
     TemplateTypeParameter T
     TemplateTypeParameter P
   ClassDecl FunctionTemplate
   ClassDecl ObjectTemplate
   ClassTemplate FunctionCallbackInfo<T>
     TemplateTypeParameter T
   ClassTemplate PropertyCallbackInfo<T>
     TemplateTypeParameter T
   ClassDecl StackTrace
   ClassDecl StackFrame
   ClassDecl Isolate
   ClassDecl CallHandlerHelper
   ClassDecl EscapableHandleScope
   ClassTemplate ReturnValue<T>
     TemplateTypeParameter T
   Namespace debug
     ClassDecl ConsoleCallArguments
   ClassTemplate Local<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Constructor Local<T>()
       UnexposedAttr ??
     FunctionTemplate Local<T>(Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     Method IsEmpty()
       UnexposedAttr ??
     Method Clear()
       UnexposedAttr ??
     Method operator->()
       UnexposedAttr ??
       TypeRef T
     Method operator*()
       UnexposedAttr ??
       TypeRef T
     FunctionTemplate operator==(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate operator==(const PersistentBase<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef PersistentBase
         TypeRef S
     FunctionTemplate operator!=(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate operator!=(const Persistent<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
     FunctionTemplate Cast(Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate As()
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef Local
       TypeRef S
     Method New(v8::Isolate *, Local<T>)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef Local
         TypeRef T
     Method New(v8::Isolate *, const PersistentBase<T> &)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef PersistentBase
         TypeRef T
     Method New(v8::Isolate *, const TracedGlobal<T> &)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef TracedGlobal
         TypeRef T
     AccessSpecifier ??
     FriendDecl ??
       TypeRef class v8::Utils
     FriendDecl ??
       ClassTemplate Eternal<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PersistentBase<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate Persistent<F, M>
         TemplateTypeParameter F
         TemplateTypeParameter M
     FriendDecl ??
       ClassTemplate Local<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate MaybeLocal<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate FunctionCallbackInfo<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PropertyCallbackInfo<F>
         TemplateTypeParameter F
     FriendDecl ??
       TypeRef class v8::String
     FriendDecl ??
       TypeRef class v8::Object
     FriendDecl ??
       TypeRef class v8::Context
     FriendDecl ??
       TypeRef class v8::Isolate
     FriendDecl ??
       TypeRef class v8::Private
     FriendDecl ??
       ClassTemplate CustomArguments<F>
         TemplateTypeParameter F
         NamespaceRef internal
     FriendDecl ??
       FunctionDecl Undefined(v8::Isolate *)
         TemplateRef Local
         TypeRef class v8::Primitive
         ParmDecl isolate
           TypeRef class v8::Isolate
     FriendDecl ??
       FunctionDecl Null(v8::Isolate *)
         TemplateRef Local
         TypeRef class v8::Primitive
         ParmDecl isolate
           TypeRef class v8::Isolate
     FriendDecl ??
       FunctionDecl True(v8::Isolate *)
         TemplateRef Local
         TypeRef class v8::Boolean
         ParmDecl isolate
           TypeRef class v8::Isolate
     FriendDecl ??
       FunctionDecl False(v8::Isolate *)
         TemplateRef Local
         TypeRef class v8::Boolean
         ParmDecl isolate
           TypeRef class v8::Isolate
     FriendDecl ??
       TypeRef class v8::HandleScope
     FriendDecl ??
       TypeRef class v8::EscapableHandleScope
     FriendDecl ??
       ClassTemplate PersistentValueMapBase<F1, F2, F3>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
         TemplateTypeParameter F3
     FriendDecl ??
       ClassTemplate PersistentValueVector<F1, F2>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate TracedGlobal<F>
         TemplateTypeParameter F
     Constructor Local<T>(T *)
       UnexposedAttr ??
       ParmDecl that
         TypeRef T
     Method New(v8::Isolate *, T *)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TypeRef T
     FieldDecl val_
       TypeRef T
   TypeAliasTemplateDecl Handle
     TemplateTypeParameter T
     TypeAliasDecl Handle
       TemplateRef Local
       TypeRef T
   ClassTemplate MaybeLocal<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Constructor MaybeLocal<T>()
       UnexposedAttr ??
     FunctionTemplate MaybeLocal<T>(Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     Method IsEmpty()
       UnexposedAttr ??
     FunctionTemplate ToLocal(Local<S> *)
       TemplateTypeParameter S
       UnexposedAttr ??
       UnexposedAttr ??
       ParmDecl out
         TemplateRef Local
         TypeRef S
     Method ToLocalChecked()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
     FunctionTemplate FromMaybe(Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef Local
       TypeRef S
       ParmDecl default_value
         TemplateRef Local
         TypeRef S
     AccessSpecifier ??
     FieldDecl val_
       TypeRef T
   ClassTemplate Eternal<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Constructor Eternal<T>()
       UnexposedAttr ??
     FunctionTemplate Eternal<T>(v8::Isolate *, Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl handle
         TemplateRef Local
         TypeRef S
     Method Get(v8::Isolate *)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method IsEmpty()
       UnexposedAttr ??
     FunctionTemplate Set(v8::Isolate *, Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl handle
         TemplateRef Local
         TypeRef S
     AccessSpecifier ??
     FieldDecl val_
       TypeRef T
   VarDecl kInternalFieldsInWeakCallback
     IntegerLiteral ??
   VarDecl kEmbedderFieldsInWeakCallback
     IntegerLiteral ??
   ClassTemplate WeakCallbackInfo<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     TypedefDecl Callback
       ParmDecl data
         TemplateRef WeakCallbackInfo
         TypeRef T
     Constructor WeakCallbackInfo<T>(v8::Isolate *, T *, void **, v8::WeakCallbackInfo::Callback *)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl parameter
         TypeRef T
       ParmDecl embedder_fields
         DeclRefExpr kEmbedderFieldsInWeakCallback
       ParmDecl callback
         TypeRef v8::WeakCallbackInfo::Callback
     Method GetIsolate()
       UnexposedAttr ??
       TypeRef class v8::Isolate
     Method GetParameter()
       UnexposedAttr ??
       TypeRef T
     Method GetInternalField(int)
       UnexposedAttr ??
       ParmDecl index
     Method SetSecondPassCallback(v8::WeakCallbackInfo::Callback)
       ParmDecl callback
         TypeRef v8::WeakCallbackInfo::Callback
     AccessSpecifier ??
     FieldDecl isolate_
       TypeRef class v8::Isolate
     FieldDecl parameter_
       TypeRef T
     FieldDecl callback_
       TypeRef v8::WeakCallbackInfo::Callback
     FieldDecl embedder_fields_
       DeclRefExpr kEmbedderFieldsInWeakCallback
   EnumDecl WeakCallbackType
     EnumConstantDecl kParameter
     EnumConstantDecl kInternalFields
     EnumConstantDecl kFinalizer
   ClassTemplate PersistentBase<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Method Reset()
       UnexposedAttr ??
     FunctionTemplate Reset(v8::Isolate *, const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl other
         TemplateRef Local
         TypeRef S
     FunctionTemplate Reset(v8::Isolate *, const PersistentBase<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl other
         TemplateRef PersistentBase
         TypeRef S
     Method IsEmpty()
       UnexposedAttr ??
     Method Empty()
       UnexposedAttr ??
     Method Get(v8::Isolate *)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
     FunctionTemplate operator==(const PersistentBase<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef PersistentBase
         TypeRef S
     FunctionTemplate operator==(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate operator!=(const PersistentBase<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef PersistentBase
         TypeRef S
     FunctionTemplate operator!=(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate SetWeak(P *, typename WeakCallbackInfo<P>::Callback, v8::WeakCallbackType)
       TemplateTypeParameter P
       UnexposedAttr ??
       ParmDecl parameter
         TypeRef P
       ParmDecl callback
         TemplateRef WeakCallbackInfo
         TypeRef P
       ParmDecl type
         TypeRef enum v8::WeakCallbackType
     Method SetWeak()
       UnexposedAttr ??
     FunctionTemplate ClearWeak()
       TemplateTypeParameter P
       UnexposedAttr ??
       TypeRef P
     Method ClearWeak()
       UnexposedAttr ??
     Method AnnotateStrongRetainer(const char *)
       UnexposedAttr ??
       ParmDecl label
     Method RegisterExternalReference(v8::Isolate *)
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method MarkIndependent()
       UnexposedAttr ??
     Method MarkActive()
       UnexposedAttr ??
     Method IsIndependent()
       UnexposedAttr ??
     Method IsNearDeath()
       UnexposedAttr ??
     Method IsWeak()
       UnexposedAttr ??
     Method SetWrapperClassId(uint16_t)
       UnexposedAttr ??
       ParmDecl class_id
         TypeRef uint16_t
     Method WrapperClassId()
       UnexposedAttr ??
       TypeRef uint16_t
     Constructor PersistentBase<T>(const PersistentBase<T> &)
       ParmDecl other
         TypeRef PersistentBase<T>
     Method operator=(const PersistentBase<T> &)
       ParmDecl ??
         TypeRef PersistentBase<T>
     AccessSpecifier ??
     FriendDecl ??
       TypeRef class v8::Isolate
     FriendDecl ??
       TypeRef class v8::Utils
     FriendDecl ??
       ClassTemplate Local<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate Persistent<F1, F2>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
     FriendDecl ??
       ClassTemplate Global<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PersistentBase<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PersistentValueMapBase<F1, F2, F3>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
         TemplateTypeParameter F3
     FriendDecl ??
       ClassTemplate PersistentValueVector<F1, F2>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
     FriendDecl ??
       TypeRef class v8::Object
     Constructor PersistentBase<T>(T *)
       UnexposedAttr ??
       ParmDecl val
         TypeRef T
     Method New(v8::Isolate *, T *)
       UnexposedAttr ??
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TypeRef T
     FieldDecl val_
       TypeRef T
   ClassTemplate NonCopyablePersistentTraits<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     TypedefDecl NonCopyablePersistent
       TemplateRef Persistent
       TypeRef T
       TemplateRef NonCopyablePersistentTraits
       TypeRef T
     VarDecl kResetInDestructor
       BoolLiteralExpr ??
     FunctionTemplate Copy(const Persistent<S, M> &, v8::NonCopyablePersistentTraits::NonCopyablePersistent *)
       TemplateTypeParameter S
       TemplateTypeParameter M
       UnexposedAttr ??
       ParmDecl source
         TemplateRef Persistent
         TypeRef S
         TypeRef M
       ParmDecl dest
         TypeRef v8::NonCopyablePersistentTraits::NonCopyablePersistent
     FunctionTemplate Uncompilable()
       TemplateTypeParameter O
       UnexposedAttr ??
   ClassTemplate CopyablePersistentTraits<T>
     TemplateTypeParameter T
     TypedefDecl CopyablePersistent
       TemplateRef Persistent
       TypeRef T
       TemplateRef CopyablePersistentTraits
       TypeRef T
     VarDecl kResetInDestructor
       BoolLiteralExpr ??
     FunctionTemplate Copy(const Persistent<S, M> &, v8::CopyablePersistentTraits::CopyablePersistent *)
       TemplateTypeParameter S
       TemplateTypeParameter M
       UnexposedAttr ??
       ParmDecl source
         TemplateRef Persistent
         TypeRef S
         TypeRef M
       ParmDecl dest
         TypeRef v8::CopyablePersistentTraits::CopyablePersistent
   ClassTemplate Persistent<T, M>
     TemplateTypeParameter T
     TemplateTypeParameter M
     BaseSpecifier PersistentBase<T>
       TemplateRef PersistentBase
       TypeRef T
     AccessSpecifier ??
     Constructor Persistent<T, M>()
       UnexposedAttr ??
     FunctionTemplate Persistent<T, M>(v8::Isolate *, Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate Persistent<T, M>(v8::Isolate *, const Persistent<S, M2> &)
       TemplateTypeParameter S
       TemplateTypeParameter M2
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
         TypeRef M2
     Constructor Persistent<T, M>(const Persistent<T, M> &)
       UnexposedAttr ??
       ParmDecl that
         TypeRef Persistent<T, M>
     FunctionTemplate Persistent<T, M>(const Persistent<S, M2> &)
       TemplateTypeParameter S
       TemplateTypeParameter M2
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
         TypeRef M2
     Method operator=(const Persistent<T, M> &)
       UnexposedAttr ??
       TypeRef Persistent<T, M>
       ParmDecl that
         TypeRef Persistent<T, M>
     FunctionTemplate operator=(const Persistent<S, M2> &)
       TemplateTypeParameter S
       TemplateTypeParameter M2
       UnexposedAttr ??
       TypeRef Persistent<T, M>
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
         TypeRef M2
     Destructor ~Persistent<T, M>()
       UnexposedAttr ??
     FunctionTemplate Cast(const Persistent<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef Persistent
       TypeRef T
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
     FunctionTemplate As()
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef Persistent
       TypeRef S
     AccessSpecifier ??
     FriendDecl ??
       TypeRef class v8::Isolate
     FriendDecl ??
       TypeRef class v8::Utils
     FriendDecl ??
       ClassTemplate Local<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate Persistent<F1, F2>
         TemplateTypeParameter F1
         TemplateTypeParameter F2
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
     Constructor Persistent<T, M>(T *)
       UnexposedAttr ??
       ParmDecl that
         TypeRef T
     Method operator*()
       UnexposedAttr ??
       TypeRef T
     FunctionTemplate Copy(const Persistent<S, M2> &)
       TemplateTypeParameter S
       TemplateTypeParameter M2
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Persistent
         TypeRef S
         TypeRef M2
   ClassTemplate Global<T>
     TemplateTypeParameter T
     BaseSpecifier PersistentBase<T>
       TemplateRef PersistentBase
       TypeRef T
     AccessSpecifier ??
     Constructor Global<T>()
       UnexposedAttr ??
     FunctionTemplate Global<T>(v8::Isolate *, Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate Global<T>(v8::Isolate *, const PersistentBase<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef PersistentBase
         TypeRef S
     Constructor Global<T>(Global<T> &&)
       UnexposedAttr ??
       ParmDecl other
         TypeRef Global<T>
     Destructor ~Global<T>()
       UnexposedAttr ??
     FunctionTemplate operator=(Global<S> &&)
       TemplateTypeParameter S
       UnexposedAttr ??
       TypeRef Global<T>
       ParmDecl rhs
         TemplateRef Global
         TypeRef S
     Method Pass()
       TypeRef Global<T>
     TypedefDecl MoveOnlyTypeForCPP03
     Constructor Global<T>(const Global<T> &)
       ParmDecl ??
         TypeRef Global<T>
     Method operator=(const Global<T> &)
       ParmDecl ??
         TypeRef Global<T>
     AccessSpecifier ??
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
     Method operator*()
       UnexposedAttr ??
       TypeRef T
   TypeAliasTemplateDecl UniquePersistent
     TemplateTypeParameter T
     TypeAliasDecl UniquePersistent
       TemplateRef Global
       TypeRef T
   ClassTemplate TracedGlobal<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Constructor TracedGlobal<T>()
     Destructor ~TracedGlobal<T>()
     FunctionTemplate TracedGlobal<T>(v8::Isolate *, Local<S>)
       TemplateTypeParameter S
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TemplateRef Local
         TypeRef S
     Constructor TracedGlobal<T>(TracedGlobal<T> &&)
       UnexposedAttr ??
       ParmDecl other
         TypeRef TracedGlobal<T>
     FunctionTemplate operator=(TracedGlobal<S> &&)
       TemplateTypeParameter S
       UnexposedAttr ??
       TypeRef TracedGlobal<T>
       ParmDecl rhs
         TemplateRef TracedGlobal
         TypeRef S
     Constructor TracedGlobal<T>(const TracedGlobal<T> &)
       ParmDecl ??
         TypeRef TracedGlobal<T>
     Method operator=(const TracedGlobal<T> &)
       ParmDecl ??
         TypeRef TracedGlobal<T>
     Method IsEmpty()
     Method Reset()
       UnexposedAttr ??
     FunctionTemplate Reset(v8::Isolate *, const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl other
         TemplateRef Local
         TypeRef S
     Method Get(v8::Isolate *)
       TemplateRef Local
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
     FunctionTemplate As()
       TemplateTypeParameter S
       UnexposedAttr ??
       TemplateRef TracedGlobal
       TypeRef S
     FunctionTemplate operator==(const TracedGlobal<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef TracedGlobal
         TypeRef S
     FunctionTemplate operator==(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     FunctionTemplate operator!=(const TracedGlobal<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef TracedGlobal
         TypeRef S
     FunctionTemplate operator!=(const Local<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef Local
         TypeRef S
     Method SetWrapperClassId(uint16_t)
       UnexposedAttr ??
       ParmDecl class_id
         TypeRef uint16_t
     Method WrapperClassId()
       UnexposedAttr ??
       TypeRef uint16_t
     Method SetFinalizationCallback(void *, WeakCallbackInfo<void>::Callback)
       UnexposedAttr ??
       ParmDecl parameter
       ParmDecl callback
         TemplateRef WeakCallbackInfo
         TypeRef v8::WeakCallbackInfo<void>::Callback
     AccessSpecifier ??
     Method New(v8::Isolate *, T *, T **)
       UnexposedAttr ??
       TypeRef T
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl that
         TypeRef T
       ParmDecl slot
         TypeRef T
     Method operator*()
       TypeRef T
     FieldDecl val_
       TypeRef T
       NullPtrLiteralExpr ??
     FriendDecl ??
       TypeRef class v8::EmbedderHeapTracer
     FriendDecl ??
       ClassTemplate Local<F>
         TemplateTypeParameter F
     FriendDecl ??
       TypeRef class v8::Object
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
   ClassDecl HandleScope
     AccessSpecifier ??
     Constructor HandleScope(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~HandleScope()
     Method NumberOfHandles(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetIsolate()
       UnexposedAttr ??
       TypeRef class v8::Isolate
     Constructor HandleScope(const v8::HandleScope &)
       ParmDecl ??
         TypeRef class v8::HandleScope
     Method operator=(const v8::HandleScope &)
       ParmDecl ??
         TypeRef class v8::HandleScope
     AccessSpecifier ??
     Constructor HandleScope()
       UnexposedAttr ??
     Method Initialize(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method CreateHandle(internal::Isolate *, internal::Address)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl isolate
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       ParmDecl value
         NamespaceRef internal
         TypeRef v8::internal::Address
     AccessSpecifier ??
     Method operator new(size_t)
       ParmDecl size
         TypeRef size_t
     Method operator new[](size_t)
       ParmDecl size
         TypeRef size_t
     Method operator delete(void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method operator delete[](void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
     FieldDecl prev_next_
       NamespaceRef internal
       TypeRef v8::internal::Address
     FieldDecl prev_limit_
       NamespaceRef internal
       TypeRef v8::internal::Address
     FriendDecl ??
       ClassTemplate Local<F>
         TemplateTypeParameter F
     FriendDecl ??
       TypeRef class v8::Object
     FriendDecl ??
       TypeRef class v8::Context
   ClassDecl EscapableHandleScope
     BaseSpecifier class v8::HandleScope
       TypeRef class v8::HandleScope
     AccessSpecifier ??
     Constructor EscapableHandleScope(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~EscapableHandleScope()
       UnexposedAttr ??
     FunctionTemplate Escape(Local<T>)
       TemplateTypeParameter T
       UnexposedAttr ??
       TemplateRef Local
       TypeRef T
       ParmDecl value
         TemplateRef Local
         TypeRef T
     FunctionTemplate EscapeMaybe(MaybeLocal<T>)
       TemplateTypeParameter T
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef T
       ParmDecl value
         TemplateRef MaybeLocal
         TypeRef T
     Constructor EscapableHandleScope(const v8::EscapableHandleScope &)
       ParmDecl ??
         TypeRef class v8::EscapableHandleScope
     Method operator=(const v8::EscapableHandleScope &)
       ParmDecl ??
         TypeRef class v8::EscapableHandleScope
     AccessSpecifier ??
     Method operator new(size_t)
       ParmDecl size
         TypeRef size_t
     Method operator new[](size_t)
       ParmDecl size
         TypeRef size_t
     Method operator delete(void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method operator delete[](void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method Escape(internal::Address *)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl escape_value
         NamespaceRef internal
         TypeRef v8::internal::Address
     FieldDecl escape_slot_
       NamespaceRef internal
       TypeRef v8::internal::Address
   ClassDecl SealHandleScope
     AccessSpecifier ??
     Constructor SealHandleScope(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~SealHandleScope()
     Constructor SealHandleScope(const v8::SealHandleScope &)
       ParmDecl ??
         TypeRef class v8::SealHandleScope
     Method operator=(const v8::SealHandleScope &)
       ParmDecl ??
         TypeRef class v8::SealHandleScope
     AccessSpecifier ??
     Method operator new(size_t)
       ParmDecl size
         TypeRef size_t
     Method operator new[](size_t)
       ParmDecl size
         TypeRef size_t
     Method operator delete(void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method operator delete[](void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
     FieldDecl prev_limit_
       NamespaceRef internal
       TypeRef v8::internal::Address
     FieldDecl prev_sealed_level_
   ClassDecl Data
     AccessSpecifier ??
     Constructor Data()
   ClassDecl ScriptOrModule
     AccessSpecifier ??
     Method GetResourceName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetHostDefinedOptions()
       TemplateRef Local
       TypeRef class v8::PrimitiveArray
   ClassDecl PrimitiveArray
     AccessSpecifier ??
     Method New(v8::Isolate *, int)
       TemplateRef Local
       TypeRef class v8::PrimitiveArray
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl length
     Method Length()
     Method Set(v8::Isolate *, int, Local<v8::Primitive>)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl index
       ParmDecl item
         TemplateRef Local
         TypeRef class v8::Primitive
     Method Get(v8::Isolate *, int)
       TemplateRef Local
       TypeRef class v8::Primitive
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl index
   ClassDecl ScriptOriginOptions
     AccessSpecifier ??
     Constructor ScriptOriginOptions(bool, bool, bool, bool)
       UnexposedAttr ??
       ParmDecl is_shared_cross_origin
         BoolLiteralExpr ??
       ParmDecl is_opaque
         BoolLiteralExpr ??
       ParmDecl is_wasm
         BoolLiteralExpr ??
       ParmDecl is_module
         BoolLiteralExpr ??
     Constructor ScriptOriginOptions(int)
       UnexposedAttr ??
       ParmDecl flags
     Method IsSharedCrossOrigin()
     Method IsOpaque()
     Method IsWasm()
     Method IsModule()
     Method Flags()
     AccessSpecifier ??
     EnumDecl ??
       EnumConstantDecl kIsSharedCrossOrigin
         IntegerLiteral ??
       EnumConstantDecl kIsOpaque
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kIsWasm
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kIsModule
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
     FieldDecl flags_
   ClassDecl ScriptOrigin
     AccessSpecifier ??
     Constructor ScriptOrigin(Local<v8::Value>, Local<v8::Integer>, Local<v8::Integer>, Local<v8::Boolean>, Local<v8::Integer>, Local<v8::Value>, Local<v8::Boolean>, Local<v8::Boolean>, Local<v8::Boolean>, Local<v8::PrimitiveArray>)
       UnexposedAttr ??
       ParmDecl resource_name
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl resource_line_offset
         TemplateRef Local
         TypeRef class v8::Integer
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Integer
       ParmDecl resource_column_offset
         TemplateRef Local
         TypeRef class v8::Integer
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Integer
       ParmDecl resource_is_shared_cross_origin
         TemplateRef Local
         TypeRef class v8::Boolean
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Boolean
       ParmDecl script_id
         TemplateRef Local
         TypeRef class v8::Integer
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Integer
       ParmDecl source_map_url
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl resource_is_opaque
         TemplateRef Local
         TypeRef class v8::Boolean
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Boolean
       ParmDecl is_wasm
         TemplateRef Local
         TypeRef class v8::Boolean
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Boolean
       ParmDecl is_module
         TemplateRef Local
         TypeRef class v8::Boolean
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Boolean
       ParmDecl host_defined_options
         TemplateRef Local
         TypeRef class v8::PrimitiveArray
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::PrimitiveArray
     Method ResourceName()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     Method ResourceLineOffset()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Integer
     Method ResourceColumnOffset()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Integer
     Method ScriptID()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Integer
     Method SourceMapUrl()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     Method HostDefinedOptions()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::PrimitiveArray
     Method Options()
       UnexposedAttr ??
       TypeRef class v8::ScriptOriginOptions
     AccessSpecifier ??
     FieldDecl resource_name_
       TemplateRef Local
       TypeRef class v8::Value
     FieldDecl resource_line_offset_
       TemplateRef Local
       TypeRef class v8::Integer
     FieldDecl resource_column_offset_
       TemplateRef Local
       TypeRef class v8::Integer
     FieldDecl options_
       TypeRef class v8::ScriptOriginOptions
     FieldDecl script_id_
       TemplateRef Local
       TypeRef class v8::Integer
     FieldDecl source_map_url_
       TemplateRef Local
       TypeRef class v8::Value
     FieldDecl host_defined_options_
       TemplateRef Local
       TypeRef class v8::PrimitiveArray
   ClassDecl UnboundScript
     AccessSpecifier ??
     Method BindToCurrentContext()
       TemplateRef Local
       TypeRef class v8::Script
     Method GetId()
     Method GetScriptName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetSourceURL()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetSourceMappingURL()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetLineNumber(int)
       ParmDecl code_pos
     VarDecl kNoScriptId
       IntegerLiteral ??
   ClassDecl UnboundModuleScript
   ClassDecl Location
     AccessSpecifier ??
     Method GetLineNumber()
     Method GetColumnNumber()
     Constructor Location(int, int)
       ParmDecl line_number
       ParmDecl column_number
     AccessSpecifier ??
     FieldDecl line_number_
     FieldDecl column_number_
   ClassDecl Module
     AccessSpecifier ??
     EnumDecl Status
       EnumConstantDecl kUninstantiated
       EnumConstantDecl kInstantiating
       EnumConstantDecl kInstantiated
       EnumConstantDecl kEvaluating
       EnumConstantDecl kEvaluated
       EnumConstantDecl kErrored
     Method GetStatus()
       TypeRef enum v8::Module::Status
     Method GetException()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetModuleRequestsLength()
     Method GetModuleRequest(int)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl i
     Method GetModuleRequestLocation(int)
       TypeRef class v8::Location
       ParmDecl i
     Method GetIdentityHash()
     TypedefDecl ResolveCallback
       TemplateRef MaybeLocal
       TypeRef class v8::Module
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl specifier
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl referrer
         TemplateRef Local
         TypeRef class v8::Module
     Method InstantiateModule(Local<v8::Context>, v8::Module::ResolveCallback)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl callback
         TypeRef v8::Module::ResolveCallback
     Method Evaluate(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetModuleNamespace()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetUnboundModuleScript()
       TemplateRef Local
       TypeRef class v8::UnboundModuleScript
   ClassDecl Script
     AccessSpecifier ??
     Method Compile(Local<v8::Context>, Local<v8::String>, v8::ScriptOrigin *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Script
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl source
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl origin
         TypeRef class v8::ScriptOrigin
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method Run(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetUnboundScript()
       TemplateRef Local
       TypeRef class v8::UnboundScript
   ClassDecl ScriptCompiler
     AccessSpecifier ??
     StructDecl CachedData
       EnumDecl BufferPolicy
         EnumConstantDecl BufferNotOwned
         EnumConstantDecl BufferOwned
       Constructor CachedData()
       Constructor CachedData(const uint8_t *, int, v8::ScriptCompiler::CachedData::BufferPolicy)
         ParmDecl data
           TypeRef uint8_t
         ParmDecl length
         ParmDecl buffer_policy
           TypeRef enum v8::ScriptCompiler::CachedData::BufferPolicy
           DeclRefExpr BufferNotOwned
       Destructor ~CachedData()
       FieldDecl data
         TypeRef uint8_t
       FieldDecl length
       FieldDecl rejected
       FieldDecl buffer_policy
         TypeRef enum v8::ScriptCompiler::CachedData::BufferPolicy
       Constructor CachedData(const v8::ScriptCompiler::CachedData &)
         ParmDecl ??
           TypeRef struct v8::ScriptCompiler::CachedData
       Method operator=(const v8::ScriptCompiler::CachedData &)
         TypeRef struct v8::ScriptCompiler::CachedData
         ParmDecl ??
           TypeRef struct v8::ScriptCompiler::CachedData
     ClassDecl Source
       AccessSpecifier ??
       Constructor Source(Local<v8::String>, const v8::ScriptOrigin &, v8::ScriptCompiler::CachedData *)
         UnexposedAttr ??
         ParmDecl source_string
           TemplateRef Local
           TypeRef class v8::String
         ParmDecl origin
           TypeRef class v8::ScriptOrigin
         ParmDecl cached_data
           TypeRef struct v8::ScriptCompiler::CachedData
           UnexposedExpr ??
             NullPtrLiteralExpr ??
       Constructor Source(Local<v8::String>, v8::ScriptCompiler::CachedData *)
         UnexposedAttr ??
         ParmDecl source_string
           TemplateRef Local
           TypeRef class v8::String
         ParmDecl cached_data
           TypeRef struct v8::ScriptCompiler::CachedData
           UnexposedExpr ??
             NullPtrLiteralExpr ??
       Destructor ~Source()
         UnexposedAttr ??
       Method GetCachedData()
         UnexposedAttr ??
         TypeRef struct v8::ScriptCompiler::CachedData
       Method GetResourceOptions()
         UnexposedAttr ??
         TypeRef class v8::ScriptOriginOptions
       Constructor Source(const v8::ScriptCompiler::Source &)
         ParmDecl ??
           TypeRef class v8::ScriptCompiler::Source
       Method operator=(const v8::ScriptCompiler::Source &)
         TypeRef class v8::ScriptCompiler::Source
         ParmDecl ??
           TypeRef class v8::ScriptCompiler::Source
       AccessSpecifier ??
       FriendDecl ??
         TypeRef class v8::ScriptCompiler
       FieldDecl source_string
         TemplateRef Local
         TypeRef class v8::String
       FieldDecl resource_name
         TemplateRef Local
         TypeRef class v8::Value
       FieldDecl resource_line_offset
         TemplateRef Local
         TypeRef class v8::Integer
       FieldDecl resource_column_offset
         TemplateRef Local
         TypeRef class v8::Integer
       FieldDecl resource_options
         TypeRef class v8::ScriptOriginOptions
       FieldDecl source_map_url
         TemplateRef Local
         TypeRef class v8::Value
       FieldDecl host_defined_options
         TemplateRef Local
         TypeRef class v8::PrimitiveArray
       FieldDecl cached_data
         TypeRef struct v8::ScriptCompiler::CachedData
     ClassDecl ExternalSourceStream
       AccessSpecifier ??
       Destructor ~ExternalSourceStream()
       Method GetMoreData(const uint8_t **)
         TypeRef size_t
         ParmDecl src
           TypeRef uint8_t
       Method SetBookmark()
       Method ResetToBookmark()
     ClassDecl StreamedSource
       AccessSpecifier ??
       EnumDecl Encoding
         EnumConstantDecl ONE_BYTE
         EnumConstantDecl TWO_BYTE
         EnumConstantDecl UTF8
       Constructor StreamedSource(v8::ScriptCompiler::ExternalSourceStream *, v8::ScriptCompiler::StreamedSource::Encoding)
         ParmDecl source_stream
           TypeRef class v8::ScriptCompiler::ExternalSourceStream
         ParmDecl encoding
           TypeRef enum v8::ScriptCompiler::StreamedSource::Encoding
       Destructor ~StreamedSource()
       Method impl()
         NamespaceRef internal
         TypeRef struct v8::internal::ScriptStreamingData
       Constructor StreamedSource(const v8::ScriptCompiler::StreamedSource &)
         ParmDecl ??
           TypeRef class v8::ScriptCompiler::StreamedSource
       Method operator=(const v8::ScriptCompiler::StreamedSource &)
         TypeRef class v8::ScriptCompiler::StreamedSource
         ParmDecl ??
           TypeRef class v8::ScriptCompiler::StreamedSource
       AccessSpecifier ??
       FieldDecl impl_
         NamespaceRef std
         TemplateRef unique_ptr
         NamespaceRef internal
         TypeRef struct v8::internal::ScriptStreamingData
     ClassDecl ScriptStreamingTask
       FinalAttr ??
       AccessSpecifier ??
       Method Run()
       AccessSpecifier ??
       FriendDecl ??
         TypeRef class v8::ScriptCompiler
       Constructor ScriptStreamingTask(internal::ScriptStreamingData *)
         ParmDecl data
           NamespaceRef internal
           TypeRef struct v8::internal::ScriptStreamingData
       FieldDecl data_
         NamespaceRef internal
         TypeRef struct v8::internal::ScriptStreamingData
     EnumDecl CompileOptions
       EnumConstantDecl kNoCompileOptions
         IntegerLiteral ??
       EnumConstantDecl kConsumeCodeCache
       EnumConstantDecl kEagerCompile
     EnumDecl NoCacheReason
       EnumConstantDecl kNoCacheNoReason
         IntegerLiteral ??
       EnumConstantDecl kNoCacheBecauseCachingDisabled
       EnumConstantDecl kNoCacheBecauseNoResource
       EnumConstantDecl kNoCacheBecauseInlineScript
       EnumConstantDecl kNoCacheBecauseModule
       EnumConstantDecl kNoCacheBecauseStreamingSource
       EnumConstantDecl kNoCacheBecauseInspector
       EnumConstantDecl kNoCacheBecauseScriptTooSmall
       EnumConstantDecl kNoCacheBecauseCacheTooCold
       EnumConstantDecl kNoCacheBecauseV8Extension
       EnumConstantDecl kNoCacheBecauseExtensionModule
       EnumConstantDecl kNoCacheBecausePacScript
       EnumConstantDecl kNoCacheBecauseInDocumentWrite
       EnumConstantDecl kNoCacheBecauseResourceWithNoCacheHandler
       EnumConstantDecl kNoCacheBecauseDeferredProduceCodeCache
     Method CompileUnboundScript(v8::Isolate *, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::UnboundScript
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl source
         TypeRef class v8::ScriptCompiler::Source
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
         DeclRefExpr kNoCompileOptions
       ParmDecl no_cache_reason
         TypeRef enum v8::ScriptCompiler::NoCacheReason
         DeclRefExpr kNoCacheNoReason
     Method Compile(Local<v8::Context>, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Script
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl source
         TypeRef class v8::ScriptCompiler::Source
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
         DeclRefExpr kNoCompileOptions
       ParmDecl no_cache_reason
         TypeRef enum v8::ScriptCompiler::NoCacheReason
         DeclRefExpr kNoCacheNoReason
     Method StartStreamingScript(v8::Isolate *, v8::ScriptCompiler::StreamedSource *, v8::ScriptCompiler::CompileOptions)
       TypeRef class v8::ScriptCompiler::ScriptStreamingTask
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl source
         TypeRef class v8::ScriptCompiler::StreamedSource
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
         DeclRefExpr kNoCompileOptions
     Method Compile(Local<v8::Context>, v8::ScriptCompiler::StreamedSource *, Local<v8::String>, const v8::ScriptOrigin &)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Script
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl source
         TypeRef class v8::ScriptCompiler::StreamedSource
       ParmDecl full_source_string
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl origin
         TypeRef class v8::ScriptOrigin
     Method CachedDataVersionTag()
       TypeRef uint32_t
     Method CompileModule(v8::Isolate *, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Module
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl source
         TypeRef class v8::ScriptCompiler::Source
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
         DeclRefExpr kNoCompileOptions
       ParmDecl no_cache_reason
         TypeRef enum v8::ScriptCompiler::NoCacheReason
         DeclRefExpr kNoCacheNoReason
     Method CompileFunctionInContext(Local<v8::Context>, v8::ScriptCompiler::Source *, size_t, Local<v8::String> *, size_t, Local<v8::Object> *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Function
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl source
         TypeRef class v8::ScriptCompiler::Source
       ParmDecl arguments_count
         TypeRef size_t
       ParmDecl arguments
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl context_extension_count
         TypeRef size_t
       ParmDecl context_extensions
         TemplateRef Local
         TypeRef class v8::Object
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
         DeclRefExpr kNoCompileOptions
       ParmDecl no_cache_reason
         TypeRef enum v8::ScriptCompiler::NoCacheReason
         DeclRefExpr kNoCacheNoReason
     Method CreateCodeCache(Local<v8::UnboundScript>)
       TypeRef struct v8::ScriptCompiler::CachedData
       ParmDecl unbound_script
         TemplateRef Local
         TypeRef class v8::UnboundScript
     Method CreateCodeCache(Local<v8::UnboundModuleScript>)
       TypeRef struct v8::ScriptCompiler::CachedData
       ParmDecl unbound_module_script
         TemplateRef Local
         TypeRef class v8::UnboundModuleScript
     Method CreateCodeCacheForFunction(Local<v8::Function>)
       TypeRef struct v8::ScriptCompiler::CachedData
       ParmDecl function
         TemplateRef Local
         TypeRef class v8::Function
     AccessSpecifier ??
     Method CompileUnboundInternal(v8::Isolate *, v8::ScriptCompiler::Source *, v8::ScriptCompiler::CompileOptions, v8::ScriptCompiler::NoCacheReason)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::UnboundScript
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl source
         TypeRef class v8::ScriptCompiler::Source
       ParmDecl options
         TypeRef enum v8::ScriptCompiler::CompileOptions
       ParmDecl no_cache_reason
         TypeRef enum v8::ScriptCompiler::NoCacheReason
   ClassDecl Message
     AccessSpecifier ??
     Method Get()
       TemplateRef Local
       TypeRef class v8::String
     Method GetIsolate()
       TypeRef class v8::Isolate
     Method GetSourceLine(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetScriptOrigin()
       TypeRef class v8::ScriptOrigin
     Method GetScriptResourceName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetStackTrace()
       TemplateRef Local
       TypeRef class v8::StackTrace
     Method GetLineNumber(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetStartPosition()
     Method GetEndPosition()
     Method ErrorLevel()
     Method GetStartColumn()
     Method GetStartColumn(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetEndColumn()
     Method GetEndColumn(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method IsSharedCrossOrigin()
     Method IsOpaque()
     Method PrintCurrentStackTrace(v8::Isolate *, FILE *)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl out
         TypeRef FILE
     VarDecl kNoLineNumberInfo
       IntegerLiteral ??
     VarDecl kNoColumnInfo
       IntegerLiteral ??
     VarDecl kNoScriptIdInfo
       IntegerLiteral ??
   ClassDecl StackTrace
     AccessSpecifier ??
     EnumDecl StackTraceOptions
       EnumConstantDecl kLineNumber
         IntegerLiteral ??
       EnumConstantDecl kColumnOffset
         BinaryOperator ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
           DeclRefExpr kLineNumber
       EnumConstantDecl kScriptName
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kFunctionName
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kIsEval
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kIsConstructor
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kScriptNameOrSourceURL
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kScriptId
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kExposeFramesAcrossSecurityOrigins
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kOverview
         BinaryOperator ??
           BinaryOperator ??
             BinaryOperator ??
               DeclRefExpr kLineNumber
               DeclRefExpr kColumnOffset
             DeclRefExpr kScriptName
           DeclRefExpr kFunctionName
       EnumConstantDecl kDetailed
         BinaryOperator ??
           BinaryOperator ??
             BinaryOperator ??
               DeclRefExpr kOverview
               DeclRefExpr kIsEval
             DeclRefExpr kIsConstructor
           DeclRefExpr kScriptNameOrSourceURL
     Method GetFrame(v8::Isolate *, uint32_t)
       TemplateRef Local
       TypeRef class v8::StackFrame
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl index
         TypeRef uint32_t
     Method GetFrameCount()
     Method CurrentStackTrace(v8::Isolate *, int, v8::StackTrace::StackTraceOptions)
       TemplateRef Local
       TypeRef class v8::StackTrace
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl frame_limit
       ParmDecl options
         TypeRef enum v8::StackTrace::StackTraceOptions
         DeclRefExpr kDetailed
   ClassDecl StackFrame
     AccessSpecifier ??
     Method GetLineNumber()
     Method GetColumn()
     Method GetScriptId()
     Method GetScriptName()
       TemplateRef Local
       TypeRef class v8::String
     Method GetScriptNameOrSourceURL()
       TemplateRef Local
       TypeRef class v8::String
     Method GetFunctionName()
       TemplateRef Local
       TypeRef class v8::String
     Method IsEval()
     Method IsConstructor()
     Method IsWasm()
   EnumDecl StateTag
     EnumConstantDecl JS
     EnumConstantDecl GC
     EnumConstantDecl PARSER
     EnumConstantDecl BYTECODE_COMPILER
     EnumConstantDecl COMPILER
     EnumConstantDecl OTHER
     EnumConstantDecl EXTERNAL
     EnumConstantDecl IDLE
   StructDecl RegisterState
     Constructor RegisterState()
     FieldDecl pc
     FieldDecl sp
     FieldDecl fp
   StructDecl SampleInfo
     FieldDecl frames_count
       TypeRef size_t
     FieldDecl vm_state
       TypeRef enum v8::StateTag
     FieldDecl external_callback_entry
   StructDecl MemoryRange
     FieldDecl start
       UnexposedExpr ??
         NullPtrLiteralExpr ??
     FieldDecl length_in_bytes
       TypeRef size_t
       UnexposedExpr ??
         IntegerLiteral ??
   StructDecl JSEntryStub
     FieldDecl code
       TypeRef struct v8::MemoryRange
   StructDecl UnwindState
     FieldDecl code_range
       TypeRef struct v8::MemoryRange
     FieldDecl embedded_code_range
       TypeRef struct v8::MemoryRange
     FieldDecl js_entry_stub
       TypeRef struct v8::JSEntryStub
   ClassDecl JSON
     AccessSpecifier ??
     Method Parse(Local<v8::Context>, Local<v8::String>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl json_string
         TemplateRef Local
         TypeRef class v8::String
     Method Stringify(Local<v8::Context>, Local<v8::Value>, Local<v8::String>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl json_object
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl gap
         TemplateRef Local
         TypeRef class v8::String
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::String
   ClassDecl ValueSerializer
     AccessSpecifier ??
     ClassDecl Delegate
       AccessSpecifier ??
       Destructor ~Delegate()
       Method ThrowDataCloneError(Local<v8::String>)
         ParmDecl message
           TemplateRef Local
           TypeRef class v8::String
       Method WriteHostObject(v8::Isolate *, Local<v8::Object>)
         TemplateRef Maybe
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl object
           TemplateRef Local
           TypeRef class v8::Object
       Method GetSharedArrayBufferId(v8::Isolate *, Local<v8::SharedArrayBuffer>)
         TemplateRef Maybe
         TypeRef uint32_t
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl shared_array_buffer
           TemplateRef Local
           TypeRef class v8::SharedArrayBuffer
       Method GetWasmModuleTransferId(v8::Isolate *, Local<v8::WasmModuleObject>)
         TemplateRef Maybe
         TypeRef uint32_t
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl module
           TemplateRef Local
           TypeRef class v8::WasmModuleObject
       Method ReallocateBufferMemory(void *, size_t, size_t *)
         ParmDecl old_buffer
         ParmDecl size
           TypeRef size_t
         ParmDecl actual_size
           TypeRef size_t
       Method FreeBufferMemory(void *)
         ParmDecl buffer
     Constructor ValueSerializer(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Constructor ValueSerializer(v8::Isolate *, v8::ValueSerializer::Delegate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl delegate
         TypeRef class v8::ValueSerializer::Delegate
     Destructor ~ValueSerializer()
     Method WriteHeader()
     Method WriteValue(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method Release()
       UnexposedAttr ??
       NamespaceRef std
       TemplateRef pair
       TypeRef uint8_t
       TypeRef size_t
     Method TransferArrayBuffer(uint32_t, Local<v8::ArrayBuffer>)
       ParmDecl transfer_id
         TypeRef uint32_t
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
     Method SetTreatArrayBufferViewsAsHostObjects(bool)
       ParmDecl mode
     Method WriteUint32(uint32_t)
       ParmDecl value
         TypeRef uint32_t
     Method WriteUint64(uint64_t)
       ParmDecl value
         TypeRef uint64_t
     Method WriteDouble(double)
       ParmDecl value
     Method WriteRawBytes(const void *, size_t)
       ParmDecl source
       ParmDecl length
         TypeRef size_t
     AccessSpecifier ??
     Constructor ValueSerializer(const v8::ValueSerializer &)
       ParmDecl ??
         TypeRef class v8::ValueSerializer
     Method operator=(const v8::ValueSerializer &)
       ParmDecl ??
         TypeRef class v8::ValueSerializer
     StructDecl PrivateData
     FieldDecl private_
       TypeRef struct v8::ValueSerializer::PrivateData
   ClassDecl ValueDeserializer
     AccessSpecifier ??
     ClassDecl Delegate
       AccessSpecifier ??
       Destructor ~Delegate()
       Method ReadHostObject(v8::Isolate *)
         TemplateRef MaybeLocal
         TypeRef class v8::Object
         ParmDecl isolate
           TypeRef class v8::Isolate
       Method GetWasmModuleFromId(v8::Isolate *, uint32_t)
         TemplateRef MaybeLocal
         TypeRef class v8::WasmModuleObject
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl transfer_id
           TypeRef uint32_t
       Method GetSharedArrayBufferFromId(v8::Isolate *, uint32_t)
         TemplateRef MaybeLocal
         TypeRef class v8::SharedArrayBuffer
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl clone_id
           TypeRef uint32_t
     Constructor ValueDeserializer(v8::Isolate *, const uint8_t *, size_t)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
     Constructor ValueDeserializer(v8::Isolate *, const uint8_t *, size_t, v8::ValueDeserializer::Delegate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
       ParmDecl delegate
         TypeRef class v8::ValueDeserializer::Delegate
     Destructor ~ValueDeserializer()
     Method ReadHeader(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ReadValue(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method TransferArrayBuffer(uint32_t, Local<v8::ArrayBuffer>)
       ParmDecl transfer_id
         TypeRef uint32_t
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
     Method TransferSharedArrayBuffer(uint32_t, Local<v8::SharedArrayBuffer>)
       ParmDecl id
         TypeRef uint32_t
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
     Method SetSupportsLegacyWireFormat(bool)
       ParmDecl supports_legacy_wire_format
     Method SetExpectInlineWasm(bool)
       ParmDecl allow_inline_wasm
     Method GetWireFormatVersion()
       TypeRef uint32_t
     Method ReadUint32(uint32_t *)
       UnexposedAttr ??
       ParmDecl value
         TypeRef uint32_t
     Method ReadUint64(uint64_t *)
       UnexposedAttr ??
       ParmDecl value
         TypeRef uint64_t
     Method ReadDouble(double *)
       UnexposedAttr ??
       ParmDecl value
     Method ReadRawBytes(size_t, const void **)
       UnexposedAttr ??
       ParmDecl length
         TypeRef size_t
       ParmDecl data
     AccessSpecifier ??
     Constructor ValueDeserializer(const v8::ValueDeserializer &)
       ParmDecl ??
         TypeRef class v8::ValueDeserializer
     Method operator=(const v8::ValueDeserializer &)
       ParmDecl ??
         TypeRef class v8::ValueDeserializer
     StructDecl PrivateData
     FieldDecl private_
       TypeRef struct v8::ValueDeserializer::PrivateData
   ClassDecl Value
     BaseSpecifier class v8::Data
       TypeRef class v8::Data
     AccessSpecifier ??
     Method IsUndefined()
       UnexposedAttr ??
     Method IsNull()
       UnexposedAttr ??
     Method IsNullOrUndefined()
       UnexposedAttr ??
     Method IsTrue()
     Method IsFalse()
     Method IsName()
     Method IsString()
       UnexposedAttr ??
     Method IsSymbol()
     Method IsFunction()
     Method IsArray()
     Method IsObject()
     Method IsBigInt()
     Method IsBoolean()
     Method IsNumber()
     Method IsExternal()
     Method IsInt32()
     Method IsUint32()
     Method IsDate()
     Method IsArgumentsObject()
     Method IsBigIntObject()
     Method IsBooleanObject()
     Method IsNumberObject()
     Method IsStringObject()
     Method IsSymbolObject()
     Method IsNativeError()
     Method IsRegExp()
     Method IsAsyncFunction()
     Method IsGeneratorFunction()
     Method IsGeneratorObject()
     Method IsPromise()
     Method IsMap()
     Method IsSet()
     Method IsMapIterator()
     Method IsSetIterator()
     Method IsWeakMap()
     Method IsWeakSet()
     Method IsArrayBuffer()
     Method IsArrayBufferView()
     Method IsTypedArray()
     Method IsUint8Array()
     Method IsUint8ClampedArray()
     Method IsInt8Array()
     Method IsUint16Array()
     Method IsInt16Array()
     Method IsUint32Array()
     Method IsInt32Array()
     Method IsFloat32Array()
     Method IsFloat64Array()
     Method IsBigInt64Array()
     Method IsBigUint64Array()
     Method IsDataView()
     Method IsSharedArrayBuffer()
     Method IsProxy()
     Method IsWebAssemblyCompiledModule()
     Method IsModuleNamespaceObject()
     Method ToBigInt(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::BigInt
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToBoolean(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Boolean
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToNumber(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Number
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToString(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToDetailString(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToObject(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToInteger(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Integer
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToUint32(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Uint32
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToInt32(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Int32
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method ToBoolean(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Boolean
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToNumber(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Number
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToString(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToObject(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Object
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToInteger(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Integer
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToInt32(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Int32
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method ToArrayIndex(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Uint32
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method BooleanValue(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method BooleanValue(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method NumberValue(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method IntegerValue(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef int64_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method Uint32Value(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef uint32_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method Int32Value(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef int32_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method Equals(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl that
         TemplateRef Local
         TypeRef class v8::Value
     Method StrictEquals(Local<v8::Value>)
       ParmDecl that
         TemplateRef Local
         TypeRef class v8::Value
     Method SameValue(Local<v8::Value>)
       ParmDecl that
         TemplateRef Local
         TypeRef class v8::Value
     FunctionTemplate Cast(T *)
       TemplateTypeParameter T
       UnexposedAttr ??
       TypeRef class v8::Value
       ParmDecl value
         TypeRef T
     Method TypeOf(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl ??
         TypeRef class v8::Isolate
     Method InstanceOf(Local<v8::Context>, Local<v8::Object>)
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl object
         TemplateRef Local
         TypeRef class v8::Object
     AccessSpecifier ??
     Method QuickIsUndefined()
       UnexposedAttr ??
     Method QuickIsNull()
       UnexposedAttr ??
     Method QuickIsNullOrUndefined()
       UnexposedAttr ??
     Method QuickIsString()
       UnexposedAttr ??
     Method FullIsUndefined()
     Method FullIsNull()
     Method FullIsString()
   ClassDecl Primitive
     BaseSpecifier class v8::Value
       TypeRef class v8::Value
   ClassDecl Boolean
     BaseSpecifier class v8::Primitive
       TypeRef class v8::Primitive
     AccessSpecifier ??
     Method Value()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Boolean
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     Method New(v8::Isolate *, bool)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Boolean
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl Name
     BaseSpecifier class v8::Primitive
       TypeRef class v8::Primitive
     AccessSpecifier ??
     Method GetIdentityHash()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Name
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   EnumDecl NewStringType
     EnumConstantDecl kNormal
     EnumConstantDecl kInternalized
   ClassDecl String
     BaseSpecifier class v8::Name
       TypeRef class v8::Name
     AccessSpecifier ??
     VarDecl kMaxLength
       ConditionalOperator ??
         BinaryOperator ??
           UnexposedExpr kApiTaggedSize
             DeclRefExpr kApiTaggedSize
               NamespaceRef internal
           IntegerLiteral ??
         BinaryOperator ??
           ParenExpr ??
             BinaryOperator ??
               IntegerLiteral ??
               IntegerLiteral ??
           IntegerLiteral ??
         BinaryOperator ??
           BinaryOperator ??
             UnexposedExpr kSmiMaxValue
               DeclRefExpr kSmiMaxValue
                 NamespaceRef internal
             IntegerLiteral ??
           IntegerLiteral ??
     EnumDecl Encoding
       EnumConstantDecl UNKNOWN_ENCODING
         IntegerLiteral ??
       EnumConstantDecl TWO_BYTE_ENCODING
         IntegerLiteral ??
       EnumConstantDecl ONE_BYTE_ENCODING
         IntegerLiteral ??
     Method Length()
     Method Utf8Length(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method IsOneByte()
     Method ContainsOnlyOneByte()
     EnumDecl WriteOptions
       EnumConstantDecl NO_OPTIONS
         IntegerLiteral ??
       EnumConstantDecl HINT_MANY_WRITES_EXPECTED
         IntegerLiteral ??
       EnumConstantDecl NO_NULL_TERMINATION
         IntegerLiteral ??
       EnumConstantDecl PRESERVE_ONE_BYTE_NULL
         IntegerLiteral ??
       EnumConstantDecl REPLACE_INVALID_UTF8
         IntegerLiteral ??
     Method Write(v8::Isolate *, uint16_t *, int, int, int)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl buffer
         TypeRef uint16_t
       ParmDecl start
         IntegerLiteral ??
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
       ParmDecl options
         UnexposedExpr NO_OPTIONS
           DeclRefExpr NO_OPTIONS
     Method WriteOneByte(v8::Isolate *, uint8_t *, int, int, int)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl buffer
         TypeRef uint8_t
       ParmDecl start
         IntegerLiteral ??
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
       ParmDecl options
         UnexposedExpr NO_OPTIONS
           DeclRefExpr NO_OPTIONS
     Method WriteUtf8(v8::Isolate *, char *, int, int *, int)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl buffer
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
       ParmDecl nchars_ref
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl options
         UnexposedExpr NO_OPTIONS
           DeclRefExpr NO_OPTIONS
     Method Empty(v8::Isolate *)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method IsExternal()
     Method IsExternalOneByte()
     ClassDecl ExternalStringResourceBase
       AccessSpecifier ??
       Destructor ~ExternalStringResourceBase()
       Method IsCacheable()
       AccessSpecifier ??
       Constructor ExternalStringResourceBase()
       Method Dispose()
       Method Lock()
       Method Unlock()
       Constructor ExternalStringResourceBase(const v8::String::ExternalStringResourceBase &)
         ParmDecl ??
           TypeRef class v8::String::ExternalStringResourceBase
       Method operator=(const v8::String::ExternalStringResourceBase &)
         ParmDecl ??
           TypeRef class v8::String::ExternalStringResourceBase
       AccessSpecifier ??
       FriendDecl ??
         NamespaceRef internal
         TypeRef class v8::internal::Heap
       FriendDecl ??
         NamespaceRef v8
         TypeRef class v8::String
       FriendDecl ??
         NamespaceRef internal
         TypeRef class v8::internal::ScopedExternalStringLock
     ClassDecl ExternalStringResource
       BaseSpecifier class v8::String::ExternalStringResourceBase
         TypeRef class v8::String::ExternalStringResourceBase
       AccessSpecifier ??
       Destructor ~ExternalStringResource()
         OverrideAttr ??
       Method data()
         TypeRef uint16_t
       Method length()
         TypeRef size_t
       AccessSpecifier ??
       Constructor ExternalStringResource()
     ClassDecl ExternalOneByteStringResource
       BaseSpecifier class v8::String::ExternalStringResourceBase
         TypeRef class v8::String::ExternalStringResourceBase
       AccessSpecifier ??
       Destructor ~ExternalOneByteStringResource()
         OverrideAttr ??
       Method data()
       Method length()
         TypeRef size_t
       AccessSpecifier ??
       Constructor ExternalOneByteStringResource()
     Method GetExternalStringResourceBase(v8::String::Encoding *)
       UnexposedAttr ??
       TypeRef class v8::String::ExternalStringResourceBase
       ParmDecl encoding_out
         TypeRef enum v8::String::Encoding
     Method GetExternalStringResource()
       UnexposedAttr ??
       TypeRef class v8::String::ExternalStringResource
     Method GetExternalOneByteStringResource()
       TypeRef class v8::String::ExternalOneByteStringResource
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::String
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     EnumDecl NewStringType
       EnumConstantDecl kNormalString
         StaticCastExpr ??
           DeclRefExpr kNormal
             NamespaceRef v8
             TypeRef enum v8::NewStringType
       EnumConstantDecl kInternalizedString
         StaticCastExpr ??
           DeclRefExpr kInternalized
             NamespaceRef v8
             TypeRef enum v8::NewStringType
     Method NewFromUtf8(v8::Isolate *, const char *, v8::String::NewStringType, int)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
       ParmDecl type
         TypeRef enum v8::String::NewStringType
         DeclRefExpr kNormalString
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
     Method NewFromUtf8(v8::Isolate *, const char *, v8::NewStringType, int)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
       ParmDecl type
         NamespaceRef v8
         TypeRef enum v8::NewStringType
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
     Method NewFromOneByte(v8::Isolate *, const uint8_t *, v8::NewStringType, int)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
         TypeRef uint8_t
       ParmDecl type
         NamespaceRef v8
         TypeRef enum v8::NewStringType
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
     Method NewFromTwoByte(v8::Isolate *, const uint16_t *, v8::String::NewStringType, int)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
         TypeRef uint16_t
       ParmDecl type
         TypeRef enum v8::String::NewStringType
         DeclRefExpr kNormalString
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
     Method NewFromTwoByte(v8::Isolate *, const uint16_t *, v8::NewStringType, int)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
         TypeRef uint16_t
       ParmDecl type
         NamespaceRef v8
         TypeRef enum v8::NewStringType
       ParmDecl length
         UnaryOperator ??
           IntegerLiteral ??
     Method Concat(v8::Isolate *, Local<v8::String>, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl left
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl right
         TemplateRef Local
         TypeRef class v8::String
     Method NewExternalTwoByte(v8::Isolate *, v8::String::ExternalStringResource *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl resource
         TypeRef class v8::String::ExternalStringResource
     Method MakeExternal(v8::String::ExternalStringResource *)
       ParmDecl resource
         TypeRef class v8::String::ExternalStringResource
     Method NewExternal(v8::Isolate *, v8::String::ExternalOneByteStringResource *)
       TemplateRef Local
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl resource
         TypeRef class v8::String::ExternalOneByteStringResource
     Method NewExternalOneByte(v8::Isolate *, v8::String::ExternalOneByteStringResource *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl resource
         TypeRef class v8::String::ExternalOneByteStringResource
     Method MakeExternal(v8::String::ExternalOneByteStringResource *)
       ParmDecl resource
         TypeRef class v8::String::ExternalOneByteStringResource
     Method CanMakeExternal()
     Method StringEquals(Local<v8::String>)
       ParmDecl str
         TemplateRef Local
         TypeRef class v8::String
     ClassDecl Utf8Value
       AccessSpecifier ??
       Constructor Utf8Value(v8::Isolate *, Local<v8::Value>)
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl obj
           TemplateRef Local
           NamespaceRef v8
           TypeRef class v8::Value
       Destructor ~Utf8Value()
       Method operator*()
       Method operator*()
       Method length()
       Constructor Utf8Value(const v8::String::Utf8Value &)
         ParmDecl ??
           TypeRef class v8::String::Utf8Value
       Method operator=(const v8::String::Utf8Value &)
         ParmDecl ??
           TypeRef class v8::String::Utf8Value
       AccessSpecifier ??
       FieldDecl str_
       FieldDecl length_
     ClassDecl Value
       AccessSpecifier ??
       Constructor Value(v8::Isolate *, Local<v8::Value>)
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl obj
           TemplateRef Local
           NamespaceRef v8
           TypeRef class v8::Value
       Destructor ~Value()
       Method operator*()
         TypeRef uint16_t
       Method operator*()
         TypeRef uint16_t
       Method length()
       Constructor Value(const v8::String::Value &)
         ParmDecl ??
           TypeRef class v8::String::Value
       Method operator=(const v8::String::Value &)
         ParmDecl ??
           TypeRef class v8::String::Value
       AccessSpecifier ??
       FieldDecl str_
         TypeRef uint16_t
       FieldDecl length_
     AccessSpecifier ??
     Method VerifyExternalStringResourceBase(v8::String::ExternalStringResourceBase *, v8::String::Encoding)
       ParmDecl v
         TypeRef class v8::String::ExternalStringResourceBase
       ParmDecl encoding
         TypeRef enum v8::String::Encoding
     Method VerifyExternalStringResource(v8::String::ExternalStringResource *)
       ParmDecl val
         TypeRef class v8::String::ExternalStringResource
     Method GetExternalStringResourceSlow()
       TypeRef class v8::String::ExternalStringResource
     Method GetExternalStringResourceBaseSlow(String::Encoding *)
       TypeRef class v8::String::ExternalStringResourceBase
       ParmDecl encoding_out
         TypeRef class v8::String
         TypeRef enum v8::String::Encoding
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl Symbol
     BaseSpecifier class v8::Name
       TypeRef class v8::Name
     AccessSpecifier ??
     Method Name()
       TemplateRef Local
       TypeRef class v8::Value
     Method New(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::String
     Method For(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method ForApi(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method GetAsyncIterator(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetHasInstance(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetIsConcatSpreadable(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetIterator(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetMatch(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetReplace(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetSearch(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetSplit(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetToPrimitive(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetToStringTag(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetUnscopables(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Symbol
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Symbol
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Symbol()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Private
     BaseSpecifier class v8::Data
       TypeRef class v8::Data
     AccessSpecifier ??
     Method Name()
       TemplateRef Local
       TypeRef class v8::Value
     Method New(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Private
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::String
     Method ForApi(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Private
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method Cast(v8::Data *)
       UnexposedAttr ??
       TypeRef class v8::Private
       ParmDecl data
         TypeRef class v8::Data
     AccessSpecifier ??
     Constructor Private()
     Method CheckCast(v8::Data *)
       ParmDecl that
         TypeRef class v8::Data
   ClassDecl Number
     BaseSpecifier class v8::Primitive
       TypeRef class v8::Primitive
     AccessSpecifier ??
     Method Value()
     Method New(v8::Isolate *, double)
       TemplateRef Local
       TypeRef class v8::Number
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Number
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Number()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl Integer
     BaseSpecifier class v8::Number
       TypeRef class v8::Number
     AccessSpecifier ??
     Method New(v8::Isolate *, int32_t)
       TemplateRef Local
       TypeRef class v8::Integer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TypeRef int32_t
     Method NewFromUnsigned(v8::Isolate *, uint32_t)
       TemplateRef Local
       TypeRef class v8::Integer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TypeRef uint32_t
     Method Value()
       TypeRef int64_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Integer
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Integer()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl Int32
     BaseSpecifier class v8::Integer
       TypeRef class v8::Integer
     AccessSpecifier ??
     Method Value()
       TypeRef int32_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Int32
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Int32()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl Uint32
     BaseSpecifier class v8::Integer
       TypeRef class v8::Integer
     AccessSpecifier ??
     Method Value()
       TypeRef uint32_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Uint32
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Uint32()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   ClassDecl BigInt
     BaseSpecifier class v8::Primitive
       TypeRef class v8::Primitive
     AccessSpecifier ??
     Method New(v8::Isolate *, int64_t)
       TemplateRef Local
       TypeRef class v8::BigInt
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TypeRef int64_t
     Method NewFromUnsigned(v8::Isolate *, uint64_t)
       TemplateRef Local
       TypeRef class v8::BigInt
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TypeRef uint64_t
     Method NewFromWords(Local<v8::Context>, int, int, const uint64_t *)
       TemplateRef MaybeLocal
       TypeRef class v8::BigInt
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl sign_bit
       ParmDecl word_count
       ParmDecl words
         TypeRef uint64_t
     Method Uint64Value(bool *)
       TypeRef uint64_t
       ParmDecl lossless
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method Int64Value(bool *)
       TypeRef int64_t
       ParmDecl lossless
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method WordCount()
     Method ToWordsArray(int *, int *, uint64_t *)
       ParmDecl sign_bit
       ParmDecl word_count
       ParmDecl words
         TypeRef uint64_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::BigInt
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor BigInt()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   EnumDecl PropertyAttribute
     EnumConstantDecl None
       IntegerLiteral ??
     EnumConstantDecl ReadOnly
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl DontEnum
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl DontDelete
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
   TypedefDecl AccessorGetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::String
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl AccessorNameGetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl AccessorSetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::String
     ParmDecl value
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl info
       TemplateRef PropertyCallbackInfo
   TypedefDecl AccessorNameSetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl value
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl info
       TemplateRef PropertyCallbackInfo
   EnumDecl AccessControl
     EnumConstantDecl DEFAULT
       IntegerLiteral ??
     EnumConstantDecl ALL_CAN_READ
       IntegerLiteral ??
     EnumConstantDecl ALL_CAN_WRITE
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl PROHIBITS_OVERWRITING
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
   EnumDecl PropertyFilter
     EnumConstantDecl ALL_PROPERTIES
       IntegerLiteral ??
     EnumConstantDecl ONLY_WRITABLE
       IntegerLiteral ??
     EnumConstantDecl ONLY_ENUMERABLE
       IntegerLiteral ??
     EnumConstantDecl ONLY_CONFIGURABLE
       IntegerLiteral ??
     EnumConstantDecl SKIP_STRINGS
       IntegerLiteral ??
     EnumConstantDecl SKIP_SYMBOLS
       IntegerLiteral ??
   EnumDecl SideEffectType
     EnumConstantDecl kHasSideEffect
     EnumConstantDecl kHasNoSideEffect
     EnumConstantDecl kHasSideEffectToReceiver
   EnumDecl KeyCollectionMode
     EnumConstantDecl kOwnOnly
     EnumConstantDecl kIncludePrototypes
   EnumDecl IndexFilter
     EnumConstantDecl kIncludeIndices
     EnumConstantDecl kSkipIndices
   EnumDecl KeyConversionMode
     EnumConstantDecl kConvertToString
     EnumConstantDecl kKeepNumbers
   EnumDecl IntegrityLevel
     EnumConstantDecl kFrozen
     EnumConstantDecl kSealed
   ClassDecl Object
     BaseSpecifier class v8::Value
       TypeRef class v8::Value
     AccessSpecifier ??
     Method Set(Local<v8::Value>, Local<v8::Value>)
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method Set(Local<v8::Context>, Local<v8::Value>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method Set(uint32_t, Local<v8::Value>)
       ParmDecl index
         TypeRef uint32_t
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method Set(Local<v8::Context>, uint32_t, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method CreateDataProperty(Local<v8::Context>, Local<v8::Name>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method CreateDataProperty(Local<v8::Context>, uint32_t, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method DefineOwnProperty(Local<v8::Context>, Local<v8::Name>, Local<v8::Value>, v8::PropertyAttribute)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl attributes
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
     Method DefineProperty(Local<v8::Context>, Local<v8::Name>, v8::PropertyDescriptor &)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl descriptor
         TypeRef class v8::PropertyDescriptor
     Method Get(Local<v8::Value>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Get(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Get(uint32_t)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl index
         TypeRef uint32_t
     Method Get(Local<v8::Context>, uint32_t)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
     Method GetPropertyAttributes(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef enum v8::PropertyAttribute
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method GetOwnPropertyDescriptor(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method Has(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Delete(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Has(Local<v8::Context>, uint32_t)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
     Method Delete(Local<v8::Context>, uint32_t)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
     Method SetAccessor(Local<v8::Context>, Local<v8::Name>, v8::AccessorNameGetterCallback, v8::AccessorNameSetterCallback, MaybeLocal<v8::Value>, v8::AccessControl, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorNameSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef MaybeLocal
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr MaybeLocal
                 TemplateRef MaybeLocal
                 TypeRef class v8::Value
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetAccessorProperty(Local<v8::Name>, Local<v8::Function>, Local<v8::Function>, v8::PropertyAttribute, v8::AccessControl)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TemplateRef Local
         TypeRef class v8::Function
       ParmDecl setter
         TemplateRef Local
         TypeRef class v8::Function
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Function
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
     Method SetNativeDataProperty(Local<v8::Context>, Local<v8::Name>, v8::AccessorNameGetterCallback, v8::AccessorNameSetterCallback, Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorNameSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl attributes
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetLazyDataProperty(Local<v8::Context>, Local<v8::Name>, v8::AccessorNameGetterCallback, Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl attributes
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method HasPrivate(Local<v8::Context>, Local<v8::Private>)
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Private
     Method SetPrivate(Local<v8::Context>, Local<v8::Private>, Local<v8::Value>)
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Private
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method DeletePrivate(Local<v8::Context>, Local<v8::Private>)
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Private
     Method GetPrivate(Local<v8::Context>, Local<v8::Private>)
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Private
     Method GetPropertyNames(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Array
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetPropertyNames(Local<v8::Context>, v8::KeyCollectionMode, v8::PropertyFilter, v8::IndexFilter, v8::KeyConversionMode)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Array
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl mode
         TypeRef enum v8::KeyCollectionMode
       ParmDecl property_filter
         TypeRef enum v8::PropertyFilter
       ParmDecl index_filter
         TypeRef enum v8::IndexFilter
       ParmDecl key_conversion
         TypeRef enum v8::KeyConversionMode
         DeclRefExpr kKeepNumbers
           TypeRef enum v8::KeyConversionMode
     Method GetOwnPropertyNames(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Array
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetOwnPropertyNames(Local<v8::Context>, v8::PropertyFilter, v8::KeyConversionMode)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Array
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl filter
         TypeRef enum v8::PropertyFilter
       ParmDecl key_conversion
         TypeRef enum v8::KeyConversionMode
         DeclRefExpr kKeepNumbers
           TypeRef enum v8::KeyConversionMode
     Method GetPrototype()
       TemplateRef Local
       TypeRef class v8::Value
     Method SetPrototype(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl prototype
         TemplateRef Local
         TypeRef class v8::Value
     Method FindInstanceInPrototypeChain(Local<v8::FunctionTemplate>)
       TemplateRef Local
       TypeRef class v8::Object
       ParmDecl tmpl
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
     Method ObjectProtoToString(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::String
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method GetConstructorName()
       TemplateRef Local
       TypeRef class v8::String
     Method SetIntegrityLevel(Local<v8::Context>, v8::IntegrityLevel)
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl level
         TypeRef enum v8::IntegrityLevel
     Method InternalFieldCount()
     Method InternalFieldCount(const PersistentBase<v8::Object> &)
       UnexposedAttr ??
       ParmDecl object
         TemplateRef PersistentBase
         TypeRef class v8::Object
     Method InternalFieldCount(const TracedGlobal<v8::Object> &)
       UnexposedAttr ??
       ParmDecl object
         TemplateRef TracedGlobal
         TypeRef class v8::Object
     Method GetInternalField(int)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl index
     Method SetInternalField(int, Local<v8::Value>)
       ParmDecl index
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method GetAlignedPointerFromInternalField(int)
       UnexposedAttr ??
       ParmDecl index
     Method GetAlignedPointerFromInternalField(const PersistentBase<v8::Object> &, int)
       UnexposedAttr ??
       ParmDecl object
         TemplateRef PersistentBase
         TypeRef class v8::Object
       ParmDecl index
     Method GetAlignedPointerFromInternalField(const TracedGlobal<v8::Object> &, int)
       UnexposedAttr ??
       ParmDecl object
         TemplateRef TracedGlobal
         TypeRef class v8::Object
       ParmDecl index
     Method SetAlignedPointerInInternalField(int, void *)
       ParmDecl index
       ParmDecl value
     Method SetAlignedPointerInInternalFields(int, int *, void **)
       ParmDecl argc
       ParmDecl indices
       ParmDecl values
     Method HasOwnProperty(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method HasOwnProperty(Local<v8::Context>, uint32_t)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
     Method HasRealNamedProperty(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method HasRealIndexedProperty(Local<v8::Context>, uint32_t)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl index
         TypeRef uint32_t
     Method HasRealNamedCallbackProperty(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method GetRealNamedPropertyInPrototypeChain(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method GetRealNamedPropertyAttributesInPrototypeChain(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef enum v8::PropertyAttribute
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method GetRealNamedProperty(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method GetRealNamedPropertyAttributes(Local<v8::Context>, Local<v8::Name>)
       UnexposedAttr ??
       TemplateRef Maybe
       TypeRef enum v8::PropertyAttribute
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Name
     Method HasNamedLookupInterceptor()
     Method HasIndexedLookupInterceptor()
     Method GetIdentityHash()
     Method Clone()
       TemplateRef Local
       TypeRef class v8::Object
     Method CreationContext()
       TemplateRef Local
       TypeRef class v8::Context
     Method CreationContext(const PersistentBase<v8::Object> &)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Context
       ParmDecl object
         TemplateRef PersistentBase
         TypeRef class v8::Object
     Method IsCallable()
     Method IsConstructor()
     Method CallAsFunction(Local<v8::Context>, Local<v8::Value>, int, Local<v8::Value> *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl recv
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl argc
       ParmDecl argv
         TemplateRef Local
         TypeRef class v8::Value
     Method CallAsConstructor(Local<v8::Context>, int, Local<v8::Value> *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl argc
       ParmDecl argv
         TemplateRef Local
         TypeRef class v8::Value
     Method GetIsolate()
       TypeRef class v8::Isolate
     Method PreviewEntries(bool *)
       TemplateRef MaybeLocal
       TypeRef class v8::Array
       ParmDecl is_key_value
     Method New(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Object
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method New(v8::Isolate *, Local<v8::Value>, Local<v8::Name> *, Local<v8::Value> *, size_t)
       TemplateRef Local
       TypeRef class v8::Object
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl prototype_or_null
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl names
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl values
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Object
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Object()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
     Method SlowGetInternalField(int)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl index
     Method SlowGetAlignedPointerFromInternalField(int)
       ParmDecl index
   ClassDecl Array
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method Length()
       TypeRef uint32_t
     Method New(v8::Isolate *, int)
       TemplateRef Local
       TypeRef class v8::Array
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl length
         IntegerLiteral ??
     Method New(v8::Isolate *, Local<v8::Value> *, size_t)
       TemplateRef Local
       TypeRef class v8::Array
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl elements
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Map
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method Size()
       TypeRef size_t
     Method Clear()
     Method Get(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Set(Local<v8::Context>, Local<v8::Value>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Map
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method Has(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Delete(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method AsArray()
       TemplateRef Local
       TypeRef class v8::Array
     Method New(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Map
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Map
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Map()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Set
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method Size()
       TypeRef size_t
     Method Clear()
     Method Add(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Set
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Has(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method Delete(Local<v8::Context>, Local<v8::Value>)
       UnexposedAttr ??
       TemplateRef Maybe
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl key
         TemplateRef Local
         TypeRef class v8::Value
     Method AsArray()
       TemplateRef Local
       TypeRef class v8::Array
     Method New(v8::Isolate *)
       TemplateRef Local
       TypeRef class v8::Set
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Set
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Set()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassTemplate ReturnValue<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     FunctionTemplate ReturnValue<T>(const ReturnValue<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl that
         TemplateRef ReturnValue
         TypeRef S
     FunctionTemplate Set(const Persistent<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl handle
         TemplateRef Persistent
         TypeRef S
     FunctionTemplate Set(const Global<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl handle
         TemplateRef Global
         TypeRef S
     FunctionTemplate Set(const TracedGlobal<S> &)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl handle
         TemplateRef TracedGlobal
         TypeRef S
     FunctionTemplate Set(const Local<S>)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl handle
         TemplateRef Local
         TypeRef S
     Method Set(bool)
       UnexposedAttr ??
       ParmDecl value
     Method Set(double)
       UnexposedAttr ??
       ParmDecl i
     Method Set(int32_t)
       UnexposedAttr ??
       ParmDecl i
         TypeRef int32_t
     Method Set(uint32_t)
       UnexposedAttr ??
       ParmDecl i
         TypeRef uint32_t
     Method SetNull()
       UnexposedAttr ??
     Method SetUndefined()
       UnexposedAttr ??
     Method SetEmptyString()
       UnexposedAttr ??
     Method GetIsolate()
       UnexposedAttr ??
       TypeRef class v8::Isolate
     FunctionTemplate Set(S *)
       TemplateTypeParameter S
       UnexposedAttr ??
       ParmDecl whatever
         TypeRef S
     Method Get()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     AccessSpecifier ??
     FriendDecl ??
       ClassTemplate ReturnValue<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate FunctionCallbackInfo<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PropertyCallbackInfo<F>
         TemplateTypeParameter F
     FriendDecl ??
       ClassTemplate PersistentValueMapBase<F, G, H>
         TemplateTypeParameter F
         TemplateTypeParameter G
         TemplateTypeParameter H
     Method SetInternal(internal::Address)
       UnexposedAttr ??
       ParmDecl value
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method GetDefaultValue()
       UnexposedAttr ??
       NamespaceRef internal
       TypeRef v8::internal::Address
     Constructor ReturnValue<T>(internal::Address *)
       UnexposedAttr ??
       ParmDecl slot
         NamespaceRef internal
         TypeRef v8::internal::Address
     FieldDecl value_
       NamespaceRef internal
       TypeRef v8::internal::Address
   ClassTemplate FunctionCallbackInfo<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Method Length()
       UnexposedAttr ??
     Method operator[](int)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl i
     Method This()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Object
     Method Holder()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Object
     Method NewTarget()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     Method IsConstructCall()
       UnexposedAttr ??
     Method Data()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     Method GetIsolate()
       UnexposedAttr ??
       TypeRef class v8::Isolate
     Method GetReturnValue()
       UnexposedAttr ??
       TemplateRef ReturnValue
       TypeRef T
     VarDecl kArgsLength
       IntegerLiteral ??
     AccessSpecifier ??
     FriendDecl ??
       NamespaceRef internal
       TypeRef class v8::internal::FunctionCallbackArguments
     FriendDecl ??
       NamespaceRef internal
       TemplateRef CustomArguments
       TypeRef FunctionCallbackInfo<T>
     FriendDecl ??
       NamespaceRef debug
       TypeRef class v8::debug::ConsoleCallArguments
     VarDecl kHolderIndex
       IntegerLiteral ??
     VarDecl kIsolateIndex
       IntegerLiteral ??
     VarDecl kReturnValueDefaultValueIndex
       IntegerLiteral ??
     VarDecl kReturnValueIndex
       IntegerLiteral ??
     VarDecl kDataIndex
       IntegerLiteral ??
     VarDecl kNewTargetIndex
       IntegerLiteral ??
     Constructor FunctionCallbackInfo<T>(internal::Address *, internal::Address *, int)
       UnexposedAttr ??
       ParmDecl implicit_args
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl values
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl length
     FieldDecl implicit_args_
       NamespaceRef internal
       TypeRef v8::internal::Address
     FieldDecl values_
       NamespaceRef internal
       TypeRef v8::internal::Address
     FieldDecl length_
   ClassTemplate PropertyCallbackInfo<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Method GetIsolate()
       UnexposedAttr ??
       TypeRef class v8::Isolate
     Method Data()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     Method This()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Object
     Method Holder()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Object
     Method GetReturnValue()
       UnexposedAttr ??
       TemplateRef ReturnValue
       TypeRef T
     Method ShouldThrowOnError()
       UnexposedAttr ??
     VarDecl kArgsLength
       IntegerLiteral ??
     AccessSpecifier ??
     FriendDecl ??
       TypeRef class v8::MacroAssembler
     FriendDecl ??
       NamespaceRef internal
       TypeRef class v8::internal::PropertyCallbackArguments
     FriendDecl ??
       NamespaceRef internal
       TemplateRef CustomArguments
       TypeRef PropertyCallbackInfo<T>
     VarDecl kShouldThrowOnErrorIndex
       IntegerLiteral ??
     VarDecl kHolderIndex
       IntegerLiteral ??
     VarDecl kIsolateIndex
       IntegerLiteral ??
     VarDecl kReturnValueDefaultValueIndex
       IntegerLiteral ??
     VarDecl kReturnValueIndex
       IntegerLiteral ??
     VarDecl kDataIndex
       IntegerLiteral ??
     VarDecl kThisIndex
       IntegerLiteral ??
     Constructor PropertyCallbackInfo<T>(internal::Address *)
       UnexposedAttr ??
       ParmDecl args
         NamespaceRef internal
         TypeRef v8::internal::Address
     FieldDecl args_
       NamespaceRef internal
       TypeRef v8::internal::Address
   TypedefDecl FunctionCallback
     ParmDecl info
       TemplateRef FunctionCallbackInfo
       TypeRef class v8::Value
   EnumDecl ConstructorBehavior
     EnumConstantDecl kThrow
     EnumConstantDecl kAllow
   ClassDecl Function
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(Local<v8::Context>, v8::FunctionCallback, Local<v8::Value>, int, v8::ConstructorBehavior, v8::SideEffectType)
       TemplateRef MaybeLocal
       TypeRef class v8::Function
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl callback
         TypeRef v8::FunctionCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl length
         IntegerLiteral ??
       ParmDecl behavior
         TypeRef enum v8::ConstructorBehavior
         DeclRefExpr kAllow
           TypeRef enum v8::ConstructorBehavior
       ParmDecl side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method NewInstance(Local<v8::Context>, int, Local<v8::Value> *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl argc
       ParmDecl argv
         TemplateRef Local
         TypeRef class v8::Value
     Method NewInstance(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method NewInstanceWithSideEffectType(Local<v8::Context>, int, Local<v8::Value> *, v8::SideEffectType)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl argc
       ParmDecl argv
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method Call(Local<v8::Context>, Local<v8::Value>, int, Local<v8::Value> *)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl recv
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl argc
       ParmDecl argv
         TemplateRef Local
         TypeRef class v8::Value
     Method SetName(Local<v8::String>)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method GetName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetInferredName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetDebugName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetDisplayName()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetScriptLineNumber()
     Method GetScriptColumnNumber()
     Method ScriptId()
     Method GetBoundFunction()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetScriptOrigin()
       TypeRef class v8::ScriptOrigin
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Function
       ParmDecl obj
         TypeRef class v8::Value
     VarDecl kLineOffsetNotFound
     AccessSpecifier ??
     Constructor Function()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Promise
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     EnumDecl PromiseState
       EnumConstantDecl kPending
       EnumConstantDecl kFulfilled
       EnumConstantDecl kRejected
     ClassDecl Resolver
       BaseSpecifier class v8::Object
         TypeRef class v8::Object
       AccessSpecifier ??
       Method New(Local<v8::Context>)
         UnexposedAttr ??
         TemplateRef MaybeLocal
         TypeRef class v8::Promise::Resolver
         ParmDecl context
           TemplateRef Local
           TypeRef class v8::Context
       Method GetPromise()
         TemplateRef Local
         TypeRef class v8::Promise
       Method Resolve(Local<v8::Context>, Local<v8::Value>)
         UnexposedAttr ??
         TemplateRef Maybe
         ParmDecl context
           TemplateRef Local
           TypeRef class v8::Context
         ParmDecl value
           TemplateRef Local
           TypeRef class v8::Value
       Method Reject(Local<v8::Context>, Local<v8::Value>)
         UnexposedAttr ??
         TemplateRef Maybe
         ParmDecl context
           TemplateRef Local
           TypeRef class v8::Context
         ParmDecl value
           TemplateRef Local
           TypeRef class v8::Value
       Method Cast(v8::Value *)
         UnexposedAttr ??
         TypeRef class v8::Promise::Resolver
         ParmDecl obj
           TypeRef class v8::Value
       AccessSpecifier ??
       Constructor Resolver()
       Method CheckCast(v8::Value *)
         ParmDecl obj
           TypeRef class v8::Value
     Method Catch(Local<v8::Context>, Local<v8::Function>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Promise
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl handler
         TemplateRef Local
         TypeRef class v8::Function
     Method Then(Local<v8::Context>, Local<v8::Function>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Promise
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl handler
         TemplateRef Local
         TypeRef class v8::Function
     Method Then(Local<v8::Context>, Local<v8::Function>, Local<v8::Function>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Promise
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl on_fulfilled
         TemplateRef Local
         TypeRef class v8::Function
       ParmDecl on_rejected
         TemplateRef Local
         TypeRef class v8::Function
     Method HasHandler()
     Method Result()
       TemplateRef Local
       TypeRef class v8::Value
     Method State()
       TypeRef enum v8::Promise::PromiseState
     Method MarkAsHandled()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Promise
       ParmDecl obj
         TypeRef class v8::Value
     VarDecl kEmbedderFieldCount
       IntegerLiteral ??
     AccessSpecifier ??
     Constructor Promise()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl PropertyDescriptor
     AccessSpecifier ??
     Constructor PropertyDescriptor()
     Constructor PropertyDescriptor(Local<v8::Value>)
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Constructor PropertyDescriptor(Local<v8::Value>, bool)
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl writable
     Constructor PropertyDescriptor(Local<v8::Value>, Local<v8::Value>)
       ParmDecl get
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl set
         TemplateRef Local
         TypeRef class v8::Value
     Destructor ~PropertyDescriptor()
     Method value()
       TemplateRef Local
       TypeRef class v8::Value
     Method has_value()
     Method get()
       TemplateRef Local
       TypeRef class v8::Value
     Method has_get()
     Method set()
       TemplateRef Local
       TypeRef class v8::Value
     Method has_set()
     Method set_enumerable(bool)
       ParmDecl enumerable
     Method enumerable()
     Method has_enumerable()
     Method set_configurable(bool)
       ParmDecl configurable
     Method configurable()
     Method has_configurable()
     Method writable()
     Method has_writable()
     StructDecl PrivateData
     Method get_private()
       TypeRef struct v8::PropertyDescriptor::PrivateData
     Constructor PropertyDescriptor(const v8::PropertyDescriptor &)
       ParmDecl ??
         TypeRef class v8::PropertyDescriptor
     Method operator=(const v8::PropertyDescriptor &)
       ParmDecl ??
         TypeRef class v8::PropertyDescriptor
     AccessSpecifier ??
     FieldDecl private_
       TypeRef struct v8::PropertyDescriptor::PrivateData
   ClassDecl Proxy
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method GetTarget()
       TemplateRef Local
       TypeRef class v8::Value
     Method GetHandler()
       TemplateRef Local
       TypeRef class v8::Value
     Method IsRevoked()
     Method Revoke()
     Method New(Local<v8::Context>, Local<v8::Object>, Local<v8::Object>)
       TemplateRef MaybeLocal
       TypeRef class v8::Proxy
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl local_target
         TemplateRef Local
         TypeRef class v8::Object
       ParmDecl local_handler
         TemplateRef Local
         TypeRef class v8::Object
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Proxy
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Proxy()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassTemplate MemorySpan<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Constructor MemorySpan<T>()
     Constructor MemorySpan<T>(T *, size_t)
       ParmDecl data
         TypeRef T
       ParmDecl size
         TypeRef size_t
       MemberRef data_
       UnexposedExpr ??
         DeclRefExpr data
       MemberRef size_
       UnexposedExpr size
         DeclRefExpr size
       CompoundStmt ??
     Method data()
       TypeRef T
       CompoundStmt ??
         ReturnStmt ??
           MemberRefExpr data_
     Method size()
       TypeRef size_t
       CompoundStmt ??
         ReturnStmt ??
           MemberRefExpr size_
     AccessSpecifier ??
     FieldDecl data_
       TypeRef T
       NullPtrLiteralExpr ??
     FieldDecl size_
       TypeRef size_t
       UnexposedExpr ??
         IntegerLiteral ??
   StructDecl OwnedBuffer
     FieldDecl buffer
       NamespaceRef std
       TemplateRef unique_ptr
       TypeRef uint8_t
     FieldDecl size
       TypeRef size_t
       UnexposedExpr ??
         IntegerLiteral ??
     Constructor OwnedBuffer(std::unique_ptr<const uint8_t []>, size_t)
       ParmDecl buffer
         NamespaceRef std
         TemplateRef unique_ptr
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
     Constructor OwnedBuffer()
   ClassDecl CompiledWasmModule
     AccessSpecifier ??
     Method Serialize()
       TypeRef struct v8::OwnedBuffer
     Method GetWireBytesRef()
       TemplateRef MemorySpan
       TypeRef uint8_t
     AccessSpecifier ??
     Constructor CompiledWasmModule(std::shared_ptr<internal::wasm::NativeModule>)
       ParmDecl ??
         NamespaceRef std
         TemplateRef shared_ptr
         NamespaceRef internal
         NamespaceRef wasm
         TypeRef class v8::internal::wasm::NativeModule
     FriendDecl ??
       TypeRef class v8::Utils
     FieldDecl native_module_
       NamespaceRef std
       TemplateRef shared_ptr
       NamespaceRef internal
       NamespaceRef wasm
       TypeRef class v8::internal::wasm::NativeModule
   ClassDecl WasmModuleObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     ClassDecl TransferrableModule
       FinalAttr ??
       AccessSpecifier ??
       Constructor TransferrableModule(v8::WasmModuleObject::TransferrableModule &&)
         ParmDecl src
           TypeRef class v8::WasmModuleObject::TransferrableModule
       Constructor TransferrableModule(const v8::WasmModuleObject::TransferrableModule &)
         ParmDecl src
           TypeRef class v8::WasmModuleObject::TransferrableModule
       Method operator=(v8::WasmModuleObject::TransferrableModule &&)
         TypeRef class v8::WasmModuleObject::TransferrableModule
         ParmDecl src
           TypeRef class v8::WasmModuleObject::TransferrableModule
       Method operator=(const v8::WasmModuleObject::TransferrableModule &)
         TypeRef class v8::WasmModuleObject::TransferrableModule
         ParmDecl src
           TypeRef class v8::WasmModuleObject::TransferrableModule
       AccessSpecifier ??
       TypedefDecl SharedModule
         NamespaceRef std
         TemplateRef shared_ptr
         NamespaceRef internal
         NamespaceRef wasm
         TypeRef class v8::internal::wasm::NativeModule
       FriendDecl ??
         TypeRef class v8::WasmModuleObject
       Constructor TransferrableModule(v8::WasmModuleObject::TransferrableModule::SharedModule)
         ParmDecl shared_module
           TypeRef v8::WasmModuleObject::TransferrableModule::SharedModule
       Constructor TransferrableModule(v8::OwnedBuffer, v8::OwnedBuffer)
         ParmDecl serialized
           TypeRef struct v8::OwnedBuffer
         ParmDecl bytes
           TypeRef struct v8::OwnedBuffer
       FieldDecl shared_module_
         TypeRef v8::WasmModuleObject::TransferrableModule::SharedModule
       FieldDecl serialized_
         TypeRef struct v8::OwnedBuffer
         UnexposedExpr ??
           CallExpr OwnedBuffer
             UnexposedExpr ??
               CallExpr ??
                 UnexposedExpr ??
                   UnexposedExpr ??
                     UnexposedExpr unique_ptr
                       CallExpr unique_ptr
                         NullPtrLiteralExpr ??
             UnexposedExpr ??
               IntegerLiteral ??
       FieldDecl wire_bytes_
         TypeRef struct v8::OwnedBuffer
         UnexposedExpr ??
           CallExpr OwnedBuffer
             UnexposedExpr ??
               CallExpr ??
                 UnexposedExpr ??
                   UnexposedExpr ??
                     UnexposedExpr unique_ptr
                       CallExpr unique_ptr
                         NullPtrLiteralExpr ??
             UnexposedExpr ??
               IntegerLiteral ??
     Method GetTransferrableModule()
       TypeRef class v8::WasmModuleObject::TransferrableModule
     Method FromTransferrableModule(v8::Isolate *, const v8::WasmModuleObject::TransferrableModule &)
       TemplateRef MaybeLocal
       TypeRef class v8::WasmModuleObject
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl ??
         TypeRef class v8::WasmModuleObject::TransferrableModule
     Method GetCompiledModule()
       TypeRef class v8::CompiledWasmModule
     Method DeserializeOrCompile(v8::Isolate *, MemorySpan<const uint8_t>, MemorySpan<const uint8_t>)
       TemplateRef MaybeLocal
       TypeRef class v8::WasmModuleObject
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl serialized_module
         TemplateRef MemorySpan
         TypeRef uint8_t
       ParmDecl wire_bytes
         TemplateRef MemorySpan
         TypeRef uint8_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::WasmModuleObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method Deserialize(v8::Isolate *, MemorySpan<const uint8_t>, MemorySpan<const uint8_t>)
       TemplateRef MaybeLocal
       TypeRef class v8::WasmModuleObject
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl serialized_module
         TemplateRef MemorySpan
         TypeRef uint8_t
       ParmDecl wire_bytes
         TemplateRef MemorySpan
         TypeRef uint8_t
     Method Compile(v8::Isolate *, const uint8_t *, size_t)
       TemplateRef MaybeLocal
       TypeRef class v8::WasmModuleObject
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl start
         TypeRef uint8_t
       ParmDecl length
         TypeRef size_t
     Method AsReference(const v8::OwnedBuffer &)
       TemplateRef MemorySpan
       TypeRef uint8_t
       ParmDecl buff
         TypeRef struct v8::OwnedBuffer
     Constructor WasmModuleObject()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   TypedefDecl WasmCompiledModule
     TypeRef class v8::WasmModuleObject
   ClassDecl WasmStreaming
     FinalAttr ??
     AccessSpecifier ??
     ClassDecl WasmStreamingImpl
     ClassDecl Client
       AccessSpecifier ??
       Destructor ~Client()
       Method OnModuleCompiled(v8::CompiledWasmModule)
         ParmDecl compiled_module
           TypeRef class v8::CompiledWasmModule
     Constructor WasmStreaming(std::unique_ptr<WasmStreamingImpl>)
       ParmDecl impl
         NamespaceRef std
         TemplateRef unique_ptr
         TypeRef class v8::WasmStreaming::WasmStreamingImpl
     Destructor ~WasmStreaming()
     Method OnBytesReceived(const uint8_t *, size_t)
       ParmDecl bytes
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
     Method Finish()
     Method Abort(MaybeLocal<v8::Value>)
       ParmDecl exception
         TemplateRef MaybeLocal
         TypeRef class v8::Value
     Method SetCompiledModuleBytes(const uint8_t *, size_t)
       ParmDecl bytes
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
     Method SetClient(std::shared_ptr<Client>)
       ParmDecl client
         NamespaceRef std
         TemplateRef shared_ptr
         TypeRef class v8::WasmStreaming::Client
     Method Unpack(v8::Isolate *, Local<v8::Value>)
       NamespaceRef std
       TemplateRef shared_ptr
       TypeRef class v8::WasmStreaming
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     AccessSpecifier ??
     FieldDecl impl_
       NamespaceRef std
       TemplateRef unique_ptr
       TypeRef class v8::WasmStreaming::WasmStreamingImpl
   ClassDecl WasmModuleObjectBuilderStreaming
     FinalAttr ??
     AccessSpecifier ??
     Constructor WasmModuleObjectBuilderStreaming(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method OnBytesReceived(const uint8_t *, size_t)
       ParmDecl ??
         TypeRef uint8_t
       ParmDecl size
         TypeRef size_t
     Method Finish()
     Method Abort(MaybeLocal<v8::Value>)
       ParmDecl exception
         TemplateRef MaybeLocal
         TypeRef class v8::Value
     Method GetPromise()
       TemplateRef Local
       TypeRef class v8::Promise
     Destructor ~WasmModuleObjectBuilderStreaming()
     AccessSpecifier ??
     Constructor WasmModuleObjectBuilderStreaming(const v8::WasmModuleObjectBuilderStreaming &)
       ParmDecl ??
         TypeRef class v8::WasmModuleObjectBuilderStreaming
     Constructor WasmModuleObjectBuilderStreaming(v8::WasmModuleObjectBuilderStreaming &&)
       ParmDecl ??
         TypeRef class v8::WasmModuleObjectBuilderStreaming
     Method operator=(const v8::WasmModuleObjectBuilderStreaming &)
       TypeRef class v8::WasmModuleObjectBuilderStreaming
       ParmDecl ??
         TypeRef class v8::WasmModuleObjectBuilderStreaming
     Method operator=(v8::WasmModuleObjectBuilderStreaming &&)
       TypeRef class v8::WasmModuleObjectBuilderStreaming
       ParmDecl ??
         TypeRef class v8::WasmModuleObjectBuilderStreaming
     FieldDecl isolate_
       TypeRef class v8::Isolate
       UnexposedExpr ??
         NullPtrLiteralExpr ??
     FieldDecl promise_
       TemplateRef Persistent
       TypeRef class v8::Promise
       TemplateRef CopyablePersistentTraits
       TypeRef class v8::Promise
     FieldDecl streaming_decoder_
       NamespaceRef std
       TemplateRef shared_ptr
       NamespaceRef internal
       NamespaceRef wasm
       TypeRef class v8::internal::wasm::StreamingDecoder
   EnumDecl ArrayBufferCreationMode
     EnumConstantDecl kInternalized
     EnumConstantDecl kExternalized
   ClassDecl ArrayBuffer
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     ClassDecl Allocator
       AccessSpecifier ??
       Destructor ~Allocator()
       Method Allocate(size_t)
         ParmDecl length
           TypeRef size_t
       Method AllocateUninitialized(size_t)
         ParmDecl length
           TypeRef size_t
       Method Free(void *, size_t)
         ParmDecl data
         ParmDecl length
           TypeRef size_t
       EnumDecl AllocationMode
         EnumConstantDecl kNormal
         EnumConstantDecl kReservation
       Method NewDefaultAllocator()
         TypeRef class v8::ArrayBuffer::Allocator
     ClassDecl Contents
       AccessSpecifier ??
       TypeAliasDecl DeleterCallback
         ParmDecl buffer
         ParmDecl length
           TypeRef size_t
         ParmDecl info
       Constructor Contents()
       Method AllocationBase()
       Method AllocationLength()
         TypeRef size_t
       Method AllocationMode()
         TypeRef class v8::ArrayBuffer::Allocator
         TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
       Method Data()
       Method ByteLength()
         TypeRef size_t
       Method Deleter()
         TypeRef v8::ArrayBuffer::Contents::DeleterCallback
       Method DeleterData()
       AccessSpecifier ??
       Constructor Contents(void *, size_t, void *, size_t, Allocator::AllocationMode, v8::ArrayBuffer::Contents::DeleterCallback, void *)
         ParmDecl data
         ParmDecl byte_length
           TypeRef size_t
         ParmDecl allocation_base
         ParmDecl allocation_length
           TypeRef size_t
         ParmDecl allocation_mode
           TypeRef class v8::ArrayBuffer::Allocator
           TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
         ParmDecl deleter
           TypeRef v8::ArrayBuffer::Contents::DeleterCallback
         ParmDecl deleter_data
       FieldDecl data_
       FieldDecl byte_length_
         TypeRef size_t
       FieldDecl allocation_base_
       FieldDecl allocation_length_
         TypeRef size_t
       FieldDecl allocation_mode_
         TypeRef class v8::ArrayBuffer::Allocator
         TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
       FieldDecl deleter_
         TypeRef v8::ArrayBuffer::Contents::DeleterCallback
       FieldDecl deleter_data_
       FriendDecl ??
         TypeRef class v8::ArrayBuffer
     Method ByteLength()
       TypeRef size_t
     Method New(v8::Isolate *, size_t)
       TemplateRef Local
       TypeRef class v8::ArrayBuffer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl byte_length
         TypeRef size_t
     Method New(v8::Isolate *, void *, size_t, v8::ArrayBufferCreationMode)
       TemplateRef Local
       TypeRef class v8::ArrayBuffer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
       ParmDecl byte_length
         TypeRef size_t
       ParmDecl mode
         TypeRef enum v8::ArrayBufferCreationMode
         DeclRefExpr kExternalized
           TypeRef enum v8::ArrayBufferCreationMode
     Method IsExternal()
     Method IsDetachable()
     Method IsNeuterable()
     Method Detach()
     Method Neuter()
     Method Externalize()
       TypeRef class v8::ArrayBuffer::Contents
     Method GetContents()
       TypeRef class v8::ArrayBuffer::Contents
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::ArrayBuffer
       ParmDecl obj
         TypeRef class v8::Value
     VarDecl kInternalFieldCount
       IntegerLiteral ??
     VarDecl kEmbedderFieldCount
       IntegerLiteral ??
     AccessSpecifier ??
     Constructor ArrayBuffer()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl ArrayBufferView
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method Buffer()
       TemplateRef Local
       TypeRef class v8::ArrayBuffer
     Method ByteOffset()
       TypeRef size_t
     Method ByteLength()
       TypeRef size_t
     Method CopyContents(void *, size_t)
       TypeRef size_t
       ParmDecl dest
       ParmDecl byte_length
         TypeRef size_t
     Method HasBuffer()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::ArrayBufferView
       ParmDecl obj
         TypeRef class v8::Value
     VarDecl kInternalFieldCount
       IntegerLiteral ??
     VarDecl kEmbedderFieldCount
       IntegerLiteral ??
     AccessSpecifier ??
     Constructor ArrayBufferView()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl TypedArray
     BaseSpecifier class v8::ArrayBufferView
       TypeRef class v8::ArrayBufferView
     AccessSpecifier ??
     VarDecl kMaxLength
       TypeRef size_t
       UnexposedExpr kSmiMaxValue
         UnexposedExpr kSmiMaxValue
           DeclRefExpr kSmiMaxValue
             NamespaceRef internal
     Method Length()
       TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::TypedArray
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor TypedArray()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Uint8Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint8Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint8Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Uint8Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Uint8Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Uint8ClampedArray
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint8ClampedArray
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint8ClampedArray
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Uint8ClampedArray
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Uint8ClampedArray()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Int8Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int8Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int8Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Int8Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Int8Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Uint16Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint16Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint16Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Uint16Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Uint16Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Int16Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int16Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int16Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Int16Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Int16Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Uint32Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint32Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Uint32Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Uint32Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Uint32Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Int32Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int32Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Int32Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Int32Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Int32Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Float32Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Float32Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Float32Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Float32Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Float32Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Float64Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Float64Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::Float64Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Float64Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor Float64Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl BigInt64Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::BigInt64Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::BigInt64Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::BigInt64Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor BigInt64Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl BigUint64Array
     BaseSpecifier class v8::TypedArray
       TypeRef class v8::TypedArray
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::BigUint64Array
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::BigUint64Array
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::BigUint64Array
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor BigUint64Array()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl DataView
     BaseSpecifier class v8::ArrayBufferView
       TypeRef class v8::ArrayBufferView
     AccessSpecifier ??
     Method New(Local<v8::ArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::DataView
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::ArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method New(Local<v8::SharedArrayBuffer>, size_t, size_t)
       TemplateRef Local
       TypeRef class v8::DataView
       ParmDecl shared_array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl byte_offset
         TypeRef size_t
       ParmDecl length
         TypeRef size_t
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::DataView
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Constructor DataView()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl SharedArrayBuffer
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     ClassDecl Contents
       AccessSpecifier ??
       TypeAliasDecl Allocator
         NamespaceRef v8
         TypeRef class v8::ArrayBuffer
         TypeRef class v8::ArrayBuffer::Allocator
       TypeAliasDecl DeleterCallback
         ParmDecl buffer
         ParmDecl length
           TypeRef size_t
         ParmDecl info
       Constructor Contents()
       Method AllocationBase()
       Method AllocationLength()
         TypeRef size_t
       Method AllocationMode()
         TypeRef v8::SharedArrayBuffer::Contents::Allocator
         TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
       Method Data()
       Method ByteLength()
         TypeRef size_t
       Method Deleter()
         TypeRef v8::SharedArrayBuffer::Contents::DeleterCallback
       Method DeleterData()
       Method IsGrowable()
       AccessSpecifier ??
       Constructor Contents(void *, size_t, void *, size_t, Allocator::AllocationMode, v8::SharedArrayBuffer::Contents::DeleterCallback, void *, bool)
         ParmDecl data
         ParmDecl byte_length
           TypeRef size_t
         ParmDecl allocation_base
         ParmDecl allocation_length
           TypeRef size_t
         ParmDecl allocation_mode
           TypeRef v8::SharedArrayBuffer::Contents::Allocator
           TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
         ParmDecl deleter
           TypeRef v8::SharedArrayBuffer::Contents::DeleterCallback
         ParmDecl deleter_data
         ParmDecl is_growable
       FieldDecl data_
       FieldDecl byte_length_
         TypeRef size_t
       FieldDecl allocation_base_
       FieldDecl allocation_length_
         TypeRef size_t
       FieldDecl allocation_mode_
         TypeRef v8::SharedArrayBuffer::Contents::Allocator
         TypeRef enum v8::ArrayBuffer::Allocator::AllocationMode
       FieldDecl deleter_
         TypeRef v8::SharedArrayBuffer::Contents::DeleterCallback
       FieldDecl deleter_data_
       FieldDecl is_growable_
       FriendDecl ??
         TypeRef class v8::SharedArrayBuffer
     Method ByteLength()
       TypeRef size_t
     Method New(v8::Isolate *, size_t)
       TemplateRef Local
       TypeRef class v8::SharedArrayBuffer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl byte_length
         TypeRef size_t
     Method New(v8::Isolate *, void *, size_t, v8::ArrayBufferCreationMode)
       TemplateRef Local
       TypeRef class v8::SharedArrayBuffer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl data
       ParmDecl byte_length
         TypeRef size_t
       ParmDecl mode
         TypeRef enum v8::ArrayBufferCreationMode
         DeclRefExpr kExternalized
           TypeRef enum v8::ArrayBufferCreationMode
     Method New(v8::Isolate *, const SharedArrayBuffer::Contents &, v8::ArrayBufferCreationMode)
       TemplateRef Local
       TypeRef class v8::SharedArrayBuffer
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl ??
         TypeRef class v8::SharedArrayBuffer
         TypeRef class v8::SharedArrayBuffer::Contents
       ParmDecl mode
         TypeRef enum v8::ArrayBufferCreationMode
         DeclRefExpr kExternalized
           TypeRef enum v8::ArrayBufferCreationMode
     Method IsExternal()
     Method Externalize()
       TypeRef class v8::SharedArrayBuffer::Contents
     Method GetContents()
       TypeRef class v8::SharedArrayBuffer::Contents
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::SharedArrayBuffer
       ParmDecl obj
         TypeRef class v8::Value
     VarDecl kInternalFieldCount
       IntegerLiteral ??
     AccessSpecifier ??
     Constructor SharedArrayBuffer()
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl Date
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(Local<v8::Context>, double)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl time
     Method ValueOf()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::Date
       ParmDecl obj
         TypeRef class v8::Value
     EnumDecl TimeZoneDetection
       EnumConstantDecl kSkip
       EnumConstantDecl kRedetect
     Method DateTimeConfigurationChangeNotification(v8::Isolate *, v8::Date::TimeZoneDetection)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl time_zone_detection
         TypeRef enum v8::Date::TimeZoneDetection
         DeclRefExpr kSkip
           TypeRef enum v8::Date::TimeZoneDetection
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl NumberObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(v8::Isolate *, double)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
     Method ValueOf()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::NumberObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl BigIntObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(v8::Isolate *, int64_t)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TypeRef int64_t
     Method ValueOf()
       TemplateRef Local
       TypeRef class v8::BigInt
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::BigIntObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl BooleanObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(v8::Isolate *, bool)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
     Method ValueOf()
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::BooleanObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl StringObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::String
     Method ValueOf()
       TemplateRef Local
       TypeRef class v8::String
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::StringObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl SymbolObject
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     Method New(v8::Isolate *, Local<v8::Symbol>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Symbol
     Method ValueOf()
       TemplateRef Local
       TypeRef class v8::Symbol
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::SymbolObject
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl RegExp
     BaseSpecifier class v8::Object
       TypeRef class v8::Object
     AccessSpecifier ??
     EnumDecl Flags
       EnumConstantDecl kNone
         IntegerLiteral ??
       EnumConstantDecl kGlobal
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kIgnoreCase
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kMultiline
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kSticky
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kUnicode
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
       EnumConstantDecl kDotAll
         BinaryOperator ??
           IntegerLiteral ??
           IntegerLiteral ??
     Method New(Local<v8::Context>, Local<v8::String>, v8::RegExp::Flags)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::RegExp
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl pattern
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl flags
         TypeRef enum v8::RegExp::Flags
     Method GetSource()
       TemplateRef Local
       TypeRef class v8::String
     Method GetFlags()
       TypeRef enum v8::RegExp::Flags
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::RegExp
       ParmDecl obj
         TypeRef class v8::Value
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         TypeRef class v8::Value
   ClassDecl External
     BaseSpecifier class v8::Value
       TypeRef class v8::Value
     AccessSpecifier ??
     Method New(v8::Isolate *, void *)
       TemplateRef Local
       TypeRef class v8::External
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl value
     Method Cast(v8::Value *)
       UnexposedAttr ??
       TypeRef class v8::External
       ParmDecl obj
         TypeRef class v8::Value
     Method Value()
     AccessSpecifier ??
     Method CheckCast(v8::Value *)
       ParmDecl obj
         NamespaceRef v8
         TypeRef class v8::Value
   EnumDecl Intrinsic
     EnumConstantDecl kArrayProto_entries
     EnumConstantDecl kArrayProto_forEach
     EnumConstantDecl kArrayProto_keys
     EnumConstantDecl kArrayProto_values
     EnumConstantDecl kErrorPrototype
     EnumConstantDecl kIteratorPrototype
   ClassDecl Template
     BaseSpecifier class v8::Data
       TypeRef class v8::Data
     AccessSpecifier ??
     Method Set(Local<v8::Name>, Local<v8::Data>, v8::PropertyAttribute)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Data
       ParmDecl attributes
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
     Method SetPrivate(Local<v8::Private>, Local<v8::Data>, v8::PropertyAttribute)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Private
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Data
       ParmDecl attributes
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
     Method Set(v8::Isolate *, const char *, Local<v8::Data>)
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Data
     Method SetAccessorProperty(Local<v8::Name>, Local<v8::FunctionTemplate>, Local<v8::FunctionTemplate>, v8::PropertyAttribute, v8::AccessControl)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::FunctionTemplate
       ParmDecl setter
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::FunctionTemplate
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
     Method SetNativeDataProperty(Local<v8::String>, v8::AccessorGetterCallback, v8::AccessorSetterCallback, Local<v8::Value>, v8::PropertyAttribute, Local<v8::AccessorSignature>, v8::AccessControl, v8::SideEffectType, v8::SideEffectType)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl getter
         TypeRef v8::AccessorGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::AccessorSignature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::AccessorSignature
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetNativeDataProperty(Local<v8::Name>, v8::AccessorNameGetterCallback, v8::AccessorNameSetterCallback, Local<v8::Value>, v8::PropertyAttribute, Local<v8::AccessorSignature>, v8::AccessControl, v8::SideEffectType, v8::SideEffectType)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorNameSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::AccessorSignature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::AccessorSignature
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetLazyDataProperty(Local<v8::Name>, v8::AccessorNameGetterCallback, Local<v8::Value>, v8::PropertyAttribute, v8::SideEffectType, v8::SideEffectType)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetIntrinsicDataProperty(Local<v8::Name>, v8::Intrinsic, v8::PropertyAttribute)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl intrinsic
         TypeRef enum v8::Intrinsic
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
     AccessSpecifier ??
     Constructor Template()
     FriendDecl ??
       TypeRef class v8::ObjectTemplate
     FriendDecl ??
       TypeRef class v8::FunctionTemplate
   TypedefDecl GenericNamedPropertyGetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl GenericNamedPropertySetterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl value
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl GenericNamedPropertyQueryCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Integer
   TypedefDecl GenericNamedPropertyDeleterCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Boolean
   TypedefDecl GenericNamedPropertyEnumeratorCallback
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Array
   TypedefDecl GenericNamedPropertyDefinerCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl desc
       TypeRef class v8::PropertyDescriptor
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl GenericNamedPropertyDescriptorCallback
     ParmDecl property
       TemplateRef Local
       TypeRef class v8::Name
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl IndexedPropertyGetterCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl IndexedPropertySetterCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl value
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl IndexedPropertyQueryCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Integer
   TypedefDecl IndexedPropertyDeleterCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Boolean
   TypedefDecl IndexedPropertyEnumeratorCallback
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Array
   TypedefDecl IndexedPropertyDefinerCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl desc
       TypeRef class v8::PropertyDescriptor
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   TypedefDecl IndexedPropertyDescriptorCallback
     ParmDecl index
       TypeRef uint32_t
     ParmDecl info
       TemplateRef PropertyCallbackInfo
       TypeRef class v8::Value
   EnumDecl AccessType
     EnumConstantDecl ACCESS_GET
     EnumConstantDecl ACCESS_SET
     EnumConstantDecl ACCESS_HAS
     EnumConstantDecl ACCESS_DELETE
     EnumConstantDecl ACCESS_KEYS
   TypedefDecl AccessCheckCallback
     ParmDecl accessing_context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl accessed_object
       TemplateRef Local
       TypeRef class v8::Object
     ParmDecl data
       TemplateRef Local
       TypeRef class v8::Value
   ClassDecl FunctionTemplate
     BaseSpecifier class v8::Template
       TypeRef class v8::Template
     AccessSpecifier ??
     Method New(v8::Isolate *, v8::FunctionCallback, Local<v8::Value>, Local<v8::Signature>, int, v8::ConstructorBehavior, v8::SideEffectType)
       TemplateRef Local
       TypeRef class v8::FunctionTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl callback
         TypeRef v8::FunctionCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::Signature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Signature
       ParmDecl length
         IntegerLiteral ??
       ParmDecl behavior
         TypeRef enum v8::ConstructorBehavior
         DeclRefExpr kAllow
           TypeRef enum v8::ConstructorBehavior
       ParmDecl side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method FromSnapshot(v8::Isolate *, size_t)
       TemplateRef MaybeLocal
       TypeRef class v8::FunctionTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl index
         TypeRef size_t
     Method NewWithCache(v8::Isolate *, v8::FunctionCallback, Local<v8::Private>, Local<v8::Value>, Local<v8::Signature>, int, v8::SideEffectType)
       TemplateRef Local
       TypeRef class v8::FunctionTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl callback
         TypeRef v8::FunctionCallback
       ParmDecl cache_property
         TemplateRef Local
         TypeRef class v8::Private
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::Signature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Signature
       ParmDecl length
         IntegerLiteral ??
       ParmDecl side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method GetFunction(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Function
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method NewRemoteInstance()
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
     Method SetCallHandler(v8::FunctionCallback, Local<v8::Value>, v8::SideEffectType)
       ParmDecl callback
         TypeRef v8::FunctionCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetLength(int)
       ParmDecl length
     Method InstanceTemplate()
       TemplateRef Local
       TypeRef class v8::ObjectTemplate
     Method Inherit(Local<v8::FunctionTemplate>)
       ParmDecl parent
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
     Method PrototypeTemplate()
       TemplateRef Local
       TypeRef class v8::ObjectTemplate
     Method SetPrototypeProviderTemplate(Local<v8::FunctionTemplate>)
       ParmDecl prototype_provider
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
     Method SetClassName(Local<v8::String>)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method SetAcceptAnyReceiver(bool)
       ParmDecl value
     Method SetHiddenPrototype(bool)
       ParmDecl value
     Method ReadOnlyPrototype()
     Method RemovePrototype()
     Method HasInstance(Local<v8::Value>)
       ParmDecl object
         TemplateRef Local
         TypeRef class v8::Value
     Method Cast(v8::Data *)
       UnexposedAttr ??
       TypeRef class v8::FunctionTemplate
       ParmDecl data
         TypeRef class v8::Data
     AccessSpecifier ??
     Constructor FunctionTemplate()
     Method CheckCast(v8::Data *)
       ParmDecl that
         TypeRef class v8::Data
     FriendDecl ??
       TypeRef class v8::Context
     FriendDecl ??
       TypeRef class v8::ObjectTemplate
   EnumDecl PropertyHandlerFlags
     EnumConstantDecl kNone
       IntegerLiteral ??
     EnumConstantDecl kAllCanRead
       IntegerLiteral ??
     EnumConstantDecl kNonMasking
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kOnlyInterceptStrings
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kHasNoSideEffect
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
   StructDecl NamedPropertyHandlerConfiguration
     Constructor NamedPropertyHandlerConfiguration(v8::GenericNamedPropertyGetterCallback, v8::GenericNamedPropertySetterCallback, v8::GenericNamedPropertyQueryCallback, v8::GenericNamedPropertyDeleterCallback, v8::GenericNamedPropertyEnumeratorCallback, v8::GenericNamedPropertyDefinerCallback, v8::GenericNamedPropertyDescriptorCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::GenericNamedPropertyGetterCallback
       ParmDecl setter
         TypeRef v8::GenericNamedPropertySetterCallback
       ParmDecl query
         TypeRef v8::GenericNamedPropertyQueryCallback
       ParmDecl deleter
         TypeRef v8::GenericNamedPropertyDeleterCallback
       ParmDecl enumerator
         TypeRef v8::GenericNamedPropertyEnumeratorCallback
       ParmDecl definer
         TypeRef v8::GenericNamedPropertyDefinerCallback
       ParmDecl descriptor
         TypeRef v8::GenericNamedPropertyDescriptorCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     Constructor NamedPropertyHandlerConfiguration(v8::GenericNamedPropertyGetterCallback, v8::GenericNamedPropertySetterCallback, v8::GenericNamedPropertyQueryCallback, v8::GenericNamedPropertyDeleterCallback, v8::GenericNamedPropertyEnumeratorCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::GenericNamedPropertyGetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl setter
         TypeRef v8::GenericNamedPropertySetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl query
         TypeRef v8::GenericNamedPropertyQueryCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl deleter
         TypeRef v8::GenericNamedPropertyDeleterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl enumerator
         TypeRef v8::GenericNamedPropertyEnumeratorCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     Constructor NamedPropertyHandlerConfiguration(v8::GenericNamedPropertyGetterCallback, v8::GenericNamedPropertySetterCallback, v8::GenericNamedPropertyDescriptorCallback, v8::GenericNamedPropertyDeleterCallback, v8::GenericNamedPropertyEnumeratorCallback, v8::GenericNamedPropertyDefinerCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::GenericNamedPropertyGetterCallback
       ParmDecl setter
         TypeRef v8::GenericNamedPropertySetterCallback
       ParmDecl descriptor
         TypeRef v8::GenericNamedPropertyDescriptorCallback
       ParmDecl deleter
         TypeRef v8::GenericNamedPropertyDeleterCallback
       ParmDecl enumerator
         TypeRef v8::GenericNamedPropertyEnumeratorCallback
       ParmDecl definer
         TypeRef v8::GenericNamedPropertyDefinerCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     FieldDecl getter
       TypeRef v8::GenericNamedPropertyGetterCallback
     FieldDecl setter
       TypeRef v8::GenericNamedPropertySetterCallback
     FieldDecl query
       TypeRef v8::GenericNamedPropertyQueryCallback
     FieldDecl deleter
       TypeRef v8::GenericNamedPropertyDeleterCallback
     FieldDecl enumerator
       TypeRef v8::GenericNamedPropertyEnumeratorCallback
     FieldDecl definer
       TypeRef v8::GenericNamedPropertyDefinerCallback
     FieldDecl descriptor
       TypeRef v8::GenericNamedPropertyDescriptorCallback
     FieldDecl data
       TemplateRef Local
       TypeRef class v8::Value
     FieldDecl flags
       TypeRef enum v8::PropertyHandlerFlags
   StructDecl IndexedPropertyHandlerConfiguration
     Constructor IndexedPropertyHandlerConfiguration(v8::IndexedPropertyGetterCallback, v8::IndexedPropertySetterCallback, v8::IndexedPropertyQueryCallback, v8::IndexedPropertyDeleterCallback, v8::IndexedPropertyEnumeratorCallback, v8::IndexedPropertyDefinerCallback, v8::IndexedPropertyDescriptorCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::IndexedPropertyGetterCallback
       ParmDecl setter
         TypeRef v8::IndexedPropertySetterCallback
       ParmDecl query
         TypeRef v8::IndexedPropertyQueryCallback
       ParmDecl deleter
         TypeRef v8::IndexedPropertyDeleterCallback
       ParmDecl enumerator
         TypeRef v8::IndexedPropertyEnumeratorCallback
       ParmDecl definer
         TypeRef v8::IndexedPropertyDefinerCallback
       ParmDecl descriptor
         TypeRef v8::IndexedPropertyDescriptorCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     Constructor IndexedPropertyHandlerConfiguration(v8::IndexedPropertyGetterCallback, v8::IndexedPropertySetterCallback, v8::IndexedPropertyQueryCallback, v8::IndexedPropertyDeleterCallback, v8::IndexedPropertyEnumeratorCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::IndexedPropertyGetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl setter
         TypeRef v8::IndexedPropertySetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl query
         TypeRef v8::IndexedPropertyQueryCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl deleter
         TypeRef v8::IndexedPropertyDeleterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl enumerator
         TypeRef v8::IndexedPropertyEnumeratorCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     Constructor IndexedPropertyHandlerConfiguration(v8::IndexedPropertyGetterCallback, v8::IndexedPropertySetterCallback, v8::IndexedPropertyDescriptorCallback, v8::IndexedPropertyDeleterCallback, v8::IndexedPropertyEnumeratorCallback, v8::IndexedPropertyDefinerCallback, Local<v8::Value>, v8::PropertyHandlerFlags)
       ParmDecl getter
         TypeRef v8::IndexedPropertyGetterCallback
       ParmDecl setter
         TypeRef v8::IndexedPropertySetterCallback
       ParmDecl descriptor
         TypeRef v8::IndexedPropertyDescriptorCallback
       ParmDecl deleter
         TypeRef v8::IndexedPropertyDeleterCallback
       ParmDecl enumerator
         TypeRef v8::IndexedPropertyEnumeratorCallback
       ParmDecl definer
         TypeRef v8::IndexedPropertyDefinerCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl flags
         TypeRef enum v8::PropertyHandlerFlags
         DeclRefExpr kNone
           TypeRef enum v8::PropertyHandlerFlags
     FieldDecl getter
       TypeRef v8::IndexedPropertyGetterCallback
     FieldDecl setter
       TypeRef v8::IndexedPropertySetterCallback
     FieldDecl query
       TypeRef v8::IndexedPropertyQueryCallback
     FieldDecl deleter
       TypeRef v8::IndexedPropertyDeleterCallback
     FieldDecl enumerator
       TypeRef v8::IndexedPropertyEnumeratorCallback
     FieldDecl definer
       TypeRef v8::IndexedPropertyDefinerCallback
     FieldDecl descriptor
       TypeRef v8::IndexedPropertyDescriptorCallback
     FieldDecl data
       TemplateRef Local
       TypeRef class v8::Value
     FieldDecl flags
       TypeRef enum v8::PropertyHandlerFlags
   ClassDecl ObjectTemplate
     BaseSpecifier class v8::Template
       TypeRef class v8::Template
     AccessSpecifier ??
     Method New(v8::Isolate *, Local<v8::FunctionTemplate>)
       TemplateRef Local
       TypeRef class v8::ObjectTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl constructor
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::FunctionTemplate
     Method FromSnapshot(v8::Isolate *, size_t)
       TemplateRef MaybeLocal
       TypeRef class v8::ObjectTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl index
         TypeRef size_t
     Method NewInstance(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method SetAccessor(Local<v8::String>, v8::AccessorGetterCallback, v8::AccessorSetterCallback, Local<v8::Value>, v8::AccessControl, v8::PropertyAttribute, Local<v8::AccessorSignature>, v8::SideEffectType, v8::SideEffectType)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
       ParmDecl getter
         TypeRef v8::AccessorGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::AccessorSignature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::AccessorSignature
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetAccessor(Local<v8::Name>, v8::AccessorNameGetterCallback, v8::AccessorNameSetterCallback, Local<v8::Value>, v8::AccessControl, v8::PropertyAttribute, Local<v8::AccessorSignature>, v8::SideEffectType, v8::SideEffectType)
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::Name
       ParmDecl getter
         TypeRef v8::AccessorNameGetterCallback
       ParmDecl setter
         TypeRef v8::AccessorNameSetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
       ParmDecl settings
         TypeRef enum v8::AccessControl
         DeclRefExpr DEFAULT
       ParmDecl attribute
         TypeRef enum v8::PropertyAttribute
         DeclRefExpr None
       ParmDecl signature
         TemplateRef Local
         TypeRef class v8::AccessorSignature
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::AccessorSignature
       ParmDecl getter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
       ParmDecl setter_side_effect_type
         TypeRef enum v8::SideEffectType
         DeclRefExpr kHasSideEffect
           TypeRef enum v8::SideEffectType
     Method SetHandler(const v8::NamedPropertyHandlerConfiguration &)
       ParmDecl configuration
         TypeRef struct v8::NamedPropertyHandlerConfiguration
     Method SetIndexedPropertyHandler(v8::IndexedPropertyGetterCallback, v8::IndexedPropertySetterCallback, v8::IndexedPropertyQueryCallback, v8::IndexedPropertyDeleterCallback, v8::IndexedPropertyEnumeratorCallback, Local<v8::Value>)
       ParmDecl getter
         TypeRef v8::IndexedPropertyGetterCallback
       ParmDecl setter
         TypeRef v8::IndexedPropertySetterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl query
         TypeRef v8::IndexedPropertyQueryCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl deleter
         TypeRef v8::IndexedPropertyDeleterCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl enumerator
         TypeRef v8::IndexedPropertyEnumeratorCallback
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method SetHandler(const v8::IndexedPropertyHandlerConfiguration &)
       ParmDecl configuration
         TypeRef struct v8::IndexedPropertyHandlerConfiguration
     Method SetCallAsFunctionHandler(v8::FunctionCallback, Local<v8::Value>)
       ParmDecl callback
         TypeRef v8::FunctionCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method MarkAsUndetectable()
     Method SetAccessCheckCallback(v8::AccessCheckCallback, Local<v8::Value>)
       ParmDecl callback
         TypeRef v8::AccessCheckCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method SetAccessCheckCallbackAndHandler(v8::AccessCheckCallback, const v8::NamedPropertyHandlerConfiguration &, const v8::IndexedPropertyHandlerConfiguration &, Local<v8::Value>)
       ParmDecl callback
         TypeRef v8::AccessCheckCallback
       ParmDecl named_handler
         TypeRef struct v8::NamedPropertyHandlerConfiguration
       ParmDecl indexed_handler
         TypeRef struct v8::IndexedPropertyHandlerConfiguration
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method InternalFieldCount()
     Method SetInternalFieldCount(int)
       ParmDecl value
     Method IsImmutableProto()
     Method SetImmutableProto()
     Method Cast(v8::Data *)
       UnexposedAttr ??
       TypeRef class v8::ObjectTemplate
       ParmDecl data
         TypeRef class v8::Data
     AccessSpecifier ??
     Constructor ObjectTemplate()
     Method New(internal::Isolate *, Local<v8::FunctionTemplate>)
       TemplateRef Local
       TypeRef class v8::ObjectTemplate
       ParmDecl isolate
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       ParmDecl constructor
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
     Method CheckCast(v8::Data *)
       ParmDecl that
         TypeRef class v8::Data
     FriendDecl ??
       TypeRef class v8::FunctionTemplate
   ClassDecl Signature
     BaseSpecifier class v8::Data
       TypeRef class v8::Data
     AccessSpecifier ??
     Method New(v8::Isolate *, Local<v8::FunctionTemplate>)
       TemplateRef Local
       TypeRef class v8::Signature
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl receiver
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::FunctionTemplate
     Method Cast(v8::Data *)
       UnexposedAttr ??
       TypeRef class v8::Signature
       ParmDecl data
         TypeRef class v8::Data
     AccessSpecifier ??
     Constructor Signature()
     Method CheckCast(v8::Data *)
       ParmDecl that
         TypeRef class v8::Data
   ClassDecl AccessorSignature
     BaseSpecifier class v8::Data
       TypeRef class v8::Data
     AccessSpecifier ??
     Method New(v8::Isolate *, Local<v8::FunctionTemplate>)
       TemplateRef Local
       TypeRef class v8::AccessorSignature
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl receiver
         TemplateRef Local
         TypeRef class v8::FunctionTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::FunctionTemplate
     Method Cast(v8::Data *)
       UnexposedAttr ??
       TypeRef class v8::AccessorSignature
       ParmDecl data
         TypeRef class v8::Data
     AccessSpecifier ??
     Constructor AccessorSignature()
     Method CheckCast(v8::Data *)
       ParmDecl that
         TypeRef class v8::Data
   ClassDecl Extension
     AccessSpecifier ??
     Constructor Extension(const char *, const char *, int, const char **, int)
       ParmDecl name
       ParmDecl source
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl dep_count
         IntegerLiteral ??
       ParmDecl deps
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl source_length
         UnaryOperator ??
           IntegerLiteral ??
     Destructor ~Extension()
     Method GetNativeFunctionTemplate(v8::Isolate *, Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::FunctionTemplate
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl name
         TemplateRef Local
         TypeRef class v8::String
     Method name()
     Method source_length()
       TypeRef size_t
     Method source()
       TypeRef class v8::String
       TypeRef class v8::String::ExternalOneByteStringResource
     Method dependency_count()
     Method dependencies()
     Method set_auto_enable(bool)
       ParmDecl value
     Method auto_enable()
     Constructor Extension(const v8::Extension &)
       ParmDecl ??
         TypeRef class v8::Extension
     Method operator=(const v8::Extension &)
       ParmDecl ??
         TypeRef class v8::Extension
     AccessSpecifier ??
     FieldDecl name_
     FieldDecl source_length_
       TypeRef size_t
     FieldDecl source_
       TypeRef class v8::String
       TypeRef class v8::String::ExternalOneByteStringResource
     FieldDecl dep_count_
     FieldDecl deps_
     FieldDecl auto_enable_
   FunctionDecl RegisterExtension(v8::Extension *)
     ParmDecl extension
       TypeRef class v8::Extension
   FunctionDecl RegisterExtension(std::unique_ptr<Extension>)
     ParmDecl ??
       NamespaceRef std
       TemplateRef unique_ptr
       TypeRef class v8::Extension
   FunctionDecl Undefined(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Primitive
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl Null(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Primitive
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl True(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Boolean
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl False(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Boolean
     ParmDecl isolate
       TypeRef class v8::Isolate
   ClassDecl ResourceConstraints
     AccessSpecifier ??
     Constructor ResourceConstraints()
     Method ConfigureDefaults(uint64_t, uint64_t)
       ParmDecl physical_memory
         TypeRef uint64_t
       ParmDecl virtual_memory_limit
         TypeRef uint64_t
     Method max_semi_space_size_in_kb()
       TypeRef size_t
     Method set_max_semi_space_size_in_kb(size_t)
       ParmDecl limit_in_kb
         TypeRef size_t
     Method max_old_space_size()
       TypeRef size_t
     Method set_max_old_space_size(size_t)
       ParmDecl limit_in_mb
         TypeRef size_t
     Method stack_limit()
       TypeRef uint32_t
     Method set_stack_limit(uint32_t *)
       ParmDecl value
         TypeRef uint32_t
     Method code_range_size()
       TypeRef size_t
     Method set_code_range_size(size_t)
       ParmDecl limit_in_mb
         TypeRef size_t
     Method max_zone_pool_size()
       TypeRef size_t
     Method set_max_zone_pool_size(size_t)
       ParmDecl bytes
         TypeRef size_t
     AccessSpecifier ??
     FieldDecl max_semi_space_size_in_kb_
       TypeRef size_t
     FieldDecl max_old_space_size_
       TypeRef size_t
     FieldDecl stack_limit_
       TypeRef uint32_t
     FieldDecl code_range_size_
       TypeRef size_t
     FieldDecl max_zone_pool_size_
       TypeRef size_t
   TypedefDecl FatalErrorCallback
     ParmDecl location
     ParmDecl message
   TypedefDecl OOMErrorCallback
     ParmDecl location
     ParmDecl is_heap_oom
   TypedefDecl DcheckErrorCallback
     ParmDecl file
     ParmDecl line
     ParmDecl message
   TypedefDecl MessageCallback
     ParmDecl message
       TemplateRef Local
       TypeRef class v8::Message
     ParmDecl data
       TemplateRef Local
       TypeRef class v8::Value
   TypedefDecl LogEventCallback
     ParmDecl name
     ParmDecl event
   ClassDecl Exception
     AccessSpecifier ??
     Method RangeError(Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     Method ReferenceError(Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     Method SyntaxError(Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     Method TypeError(Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     Method Error(Local<v8::String>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     Method CreateMessage(v8::Isolate *, Local<v8::Value>)
       TemplateRef Local
       TypeRef class v8::Message
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl exception
         TemplateRef Local
         TypeRef class v8::Value
     Method GetStackTrace(Local<v8::Value>)
       TemplateRef Local
       TypeRef class v8::StackTrace
       ParmDecl exception
         TemplateRef Local
         TypeRef class v8::Value
   TypedefDecl CounterLookupCallback
     ParmDecl name
   TypedefDecl CreateHistogramCallback
     ParmDecl name
     ParmDecl min
     ParmDecl max
     ParmDecl buckets
       TypeRef size_t
   TypedefDecl AddHistogramSampleCallback
     ParmDecl histogram
     ParmDecl sample
   TypedefDecl BeforeCallEnteredCallback
     ParmDecl ??
       TypeRef class v8::Isolate
   TypedefDecl CallCompletedCallback
     ParmDecl ??
       TypeRef class v8::Isolate
   TypedefDecl HostImportModuleDynamicallyCallback
     TemplateRef MaybeLocal
     TypeRef class v8::Promise
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl referrer
       TemplateRef Local
       TypeRef class v8::ScriptOrModule
     ParmDecl specifier
       TemplateRef Local
       TypeRef class v8::String
   TypedefDecl HostInitializeImportMetaObjectCallback
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl module
       TemplateRef Local
       TypeRef class v8::Module
     ParmDecl meta
       TemplateRef Local
       TypeRef class v8::Object
   TypedefDecl PrepareStackTraceCallback
     TemplateRef MaybeLocal
     TypeRef class v8::Value
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl error
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl sites
       TemplateRef Local
       TypeRef class v8::Array
   EnumDecl PromiseHookType
     EnumConstantDecl kInit
     EnumConstantDecl kResolve
     EnumConstantDecl kBefore
     EnumConstantDecl kAfter
   TypedefDecl PromiseHook
     ParmDecl type
       TypeRef enum v8::PromiseHookType
     ParmDecl promise
       TemplateRef Local
       TypeRef class v8::Promise
     ParmDecl parent
       TemplateRef Local
       TypeRef class v8::Value
   EnumDecl PromiseRejectEvent
     EnumConstantDecl kPromiseRejectWithNoHandler
       IntegerLiteral ??
     EnumConstantDecl kPromiseHandlerAddedAfterReject
       IntegerLiteral ??
     EnumConstantDecl kPromiseRejectAfterResolved
       IntegerLiteral ??
     EnumConstantDecl kPromiseResolveAfterResolved
       IntegerLiteral ??
   ClassDecl PromiseRejectMessage
     AccessSpecifier ??
     Constructor PromiseRejectMessage(Local<v8::Promise>, v8::PromiseRejectEvent, Local<v8::Value>, Local<v8::StackTrace>)
       ParmDecl promise
         TemplateRef Local
         TypeRef class v8::Promise
       ParmDecl event
         TypeRef enum v8::PromiseRejectEvent
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
       ParmDecl stack_trace
         TemplateRef Local
         TypeRef class v8::StackTrace
     Method GetPromise()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Promise
     Method GetEvent()
       UnexposedAttr ??
       TypeRef enum v8::PromiseRejectEvent
     Method GetValue()
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
     AccessSpecifier ??
     FieldDecl promise_
       TemplateRef Local
       TypeRef class v8::Promise
     FieldDecl event_
       TypeRef enum v8::PromiseRejectEvent
     FieldDecl value_
       TemplateRef Local
       TypeRef class v8::Value
     FieldDecl stack_trace_
       TemplateRef Local
       TypeRef class v8::StackTrace
   TypedefDecl PromiseRejectCallback
     ParmDecl message
       TypeRef class v8::PromiseRejectMessage
   TypedefDecl MicrotasksCompletedCallback
     ParmDecl ??
       TypeRef class v8::Isolate
   TypedefDecl MicrotaskCallback
     ParmDecl data
   EnumDecl MicrotasksPolicy
     EnumConstantDecl kExplicit
     EnumConstantDecl kScoped
     EnumConstantDecl kAuto
   ClassDecl MicrotasksScope
     AccessSpecifier ??
     EnumDecl Type
       EnumConstantDecl kRunMicrotasks
       EnumConstantDecl kDoNotRunMicrotasks
     Constructor MicrotasksScope(v8::Isolate *, v8::MicrotasksScope::Type)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl type
         TypeRef enum v8::MicrotasksScope::Type
     Destructor ~MicrotasksScope()
     Method PerformCheckpoint(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method GetCurrentDepth(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method IsRunningMicrotasks(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Constructor MicrotasksScope(const v8::MicrotasksScope &)
       ParmDecl ??
         TypeRef class v8::MicrotasksScope
     Method operator=(const v8::MicrotasksScope &)
       TypeRef class v8::MicrotasksScope
       ParmDecl ??
         TypeRef class v8::MicrotasksScope
     AccessSpecifier ??
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
     FieldDecl microtask_queue_
       NamespaceRef internal
       TypeRef class v8::internal::MicrotaskQueue
     FieldDecl run_
   TypedefDecl FailedAccessCheckCallback
     ParmDecl target
       TemplateRef Local
       TypeRef class v8::Object
     ParmDecl type
       TypeRef enum v8::AccessType
     ParmDecl data
       TemplateRef Local
       TypeRef class v8::Value
   TypedefDecl AllowCodeGenerationFromStringsCallback
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl source
       TemplateRef Local
       TypeRef class v8::String
   TypedefDecl ExtensionCallback
     ParmDecl ??
       TemplateRef FunctionCallbackInfo
       TypeRef class v8::Value
   TypedefDecl AllowWasmCodeGenerationCallback
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl source
       TemplateRef Local
       TypeRef class v8::String
   TypedefDecl ApiImplementationCallback
     ParmDecl ??
       TemplateRef FunctionCallbackInfo
       TypeRef class v8::Value
   TypedefDecl WasmStreamingCallback
     ParmDecl ??
       TemplateRef FunctionCallbackInfo
       TypeRef class v8::Value
   TypedefDecl WasmThreadsEnabledCallback
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
   EnumDecl GCType
     EnumConstantDecl kGCTypeScavenge
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCTypeMarkSweepCompact
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCTypeIncrementalMarking
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCTypeProcessWeakCallbacks
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCTypeAll
       BinaryOperator ??
         BinaryOperator ??
           BinaryOperator ??
             DeclRefExpr kGCTypeScavenge
             DeclRefExpr kGCTypeMarkSweepCompact
           DeclRefExpr kGCTypeIncrementalMarking
         DeclRefExpr kGCTypeProcessWeakCallbacks
   EnumDecl GCCallbackFlags
     EnumConstantDecl kNoGCCallbackFlags
       IntegerLiteral ??
     EnumConstantDecl kGCCallbackFlagConstructRetainedObjectInfos
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCCallbackFlagForced
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCCallbackFlagSynchronousPhantomCallbackProcessing
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCCallbackFlagCollectAllAvailableGarbage
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCCallbackFlagCollectAllExternalMemory
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
     EnumConstantDecl kGCCallbackScheduleIdleGarbageCollection
       BinaryOperator ??
         IntegerLiteral ??
         IntegerLiteral ??
   TypedefDecl GCCallback
     ParmDecl type
       TypeRef enum v8::GCType
     ParmDecl flags
       TypeRef enum v8::GCCallbackFlags
   TypedefDecl InterruptCallback
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl data
   TypedefDecl NearHeapLimitCallback
     TypeRef size_t
     ParmDecl data
     ParmDecl current_heap_limit
       TypeRef size_t
     ParmDecl initial_heap_limit
       TypeRef size_t
   ClassDecl HeapStatistics
     AccessSpecifier ??
     Constructor HeapStatistics()
     Method total_heap_size()
       TypeRef size_t
     Method total_heap_size_executable()
       TypeRef size_t
     Method total_physical_size()
       TypeRef size_t
     Method total_available_size()
       TypeRef size_t
     Method used_heap_size()
       TypeRef size_t
     Method heap_size_limit()
       TypeRef size_t
     Method malloced_memory()
       TypeRef size_t
     Method external_memory()
       TypeRef size_t
     Method peak_malloced_memory()
       TypeRef size_t
     Method number_of_native_contexts()
       TypeRef size_t
     Method number_of_detached_contexts()
       TypeRef size_t
     Method does_zap_garbage()
       TypeRef size_t
     AccessSpecifier ??
     FieldDecl total_heap_size_
       TypeRef size_t
     FieldDecl total_heap_size_executable_
       TypeRef size_t
     FieldDecl total_physical_size_
       TypeRef size_t
     FieldDecl total_available_size_
       TypeRef size_t
     FieldDecl used_heap_size_
       TypeRef size_t
     FieldDecl heap_size_limit_
       TypeRef size_t
     FieldDecl malloced_memory_
       TypeRef size_t
     FieldDecl external_memory_
       TypeRef size_t
     FieldDecl peak_malloced_memory_
       TypeRef size_t
     FieldDecl does_zap_garbage_
     FieldDecl number_of_native_contexts_
       TypeRef size_t
     FieldDecl number_of_detached_contexts_
       TypeRef size_t
     FriendDecl ??
       TypeRef class v8::V8
     FriendDecl ??
       TypeRef class v8::Isolate
   ClassDecl HeapSpaceStatistics
     AccessSpecifier ??
     Constructor HeapSpaceStatistics()
     Method space_name()
     Method space_size()
       TypeRef size_t
     Method space_used_size()
       TypeRef size_t
     Method space_available_size()
       TypeRef size_t
     Method physical_space_size()
       TypeRef size_t
     AccessSpecifier ??
     FieldDecl space_name_
     FieldDecl space_size_
       TypeRef size_t
     FieldDecl space_used_size_
       TypeRef size_t
     FieldDecl space_available_size_
       TypeRef size_t
     FieldDecl physical_space_size_
       TypeRef size_t
     FriendDecl ??
       TypeRef class v8::Isolate
   ClassDecl HeapObjectStatistics
     AccessSpecifier ??
     Constructor HeapObjectStatistics()
     Method object_type()
     Method object_sub_type()
     Method object_count()
       TypeRef size_t
     Method object_size()
       TypeRef size_t
     AccessSpecifier ??
     FieldDecl object_type_
     FieldDecl object_sub_type_
     FieldDecl object_count_
       TypeRef size_t
     FieldDecl object_size_
       TypeRef size_t
     FriendDecl ??
       TypeRef class v8::Isolate
   ClassDecl HeapCodeStatistics
     AccessSpecifier ??
     Constructor HeapCodeStatistics()
     Method code_and_metadata_size()
       TypeRef size_t
     Method bytecode_and_metadata_size()
       TypeRef size_t
     Method external_script_source_size()
       TypeRef size_t
     AccessSpecifier ??
     FieldDecl code_and_metadata_size_
       TypeRef size_t
     FieldDecl bytecode_and_metadata_size_
       TypeRef size_t
     FieldDecl external_script_source_size_
       TypeRef size_t
     FriendDecl ??
       TypeRef class v8::Isolate
   StructDecl JitCodeEvent
     EnumDecl EventType
       EnumConstantDecl CODE_ADDED
       EnumConstantDecl CODE_MOVED
       EnumConstantDecl CODE_REMOVED
       EnumConstantDecl CODE_ADD_LINE_POS_INFO
       EnumConstantDecl CODE_START_LINE_INFO_RECORDING
       EnumConstantDecl CODE_END_LINE_INFO_RECORDING
     EnumDecl PositionType
       EnumConstantDecl POSITION
       EnumConstantDecl STATEMENT_POSITION
     EnumDecl CodeType
       EnumConstantDecl BYTE_CODE
       EnumConstantDecl JIT_CODE
     FieldDecl type
       TypeRef enum v8::JitCodeEvent::EventType
     FieldDecl code_type
       TypeRef enum v8::JitCodeEvent::CodeType
     FieldDecl code_start
     FieldDecl code_len
       TypeRef size_t
     FieldDecl script
       TemplateRef Local
       TypeRef class v8::UnboundScript
     FieldDecl user_data
     StructDecl name_t
       FieldDecl str
       FieldDecl len
         TypeRef size_t
     StructDecl line_info_t
       FieldDecl offset
         TypeRef size_t
       FieldDecl pos
         TypeRef size_t
       FieldDecl position_type
         TypeRef enum v8::JitCodeEvent::PositionType
     UnionDecl ??
       FieldDecl name
         TypeRef struct v8::JitCodeEvent::name_t
       FieldDecl line_info
         TypeRef struct v8::JitCodeEvent::line_info_t
       FieldDecl new_code_start
     FieldDecl isolate
       TypeRef class v8::Isolate
   EnumDecl RAILMode
     EnumConstantDecl PERFORMANCE_RESPONSE
     EnumConstantDecl PERFORMANCE_ANIMATION
     EnumConstantDecl PERFORMANCE_IDLE
     EnumConstantDecl PERFORMANCE_LOAD
   EnumDecl JitCodeEventOptions
     EnumConstantDecl kJitCodeEventDefault
       IntegerLiteral ??
     EnumConstantDecl kJitCodeEventEnumExisting
       IntegerLiteral ??
   TypedefDecl JitCodeEventHandler
     ParmDecl event
       TypeRef struct v8::JitCodeEvent
   ClassDecl ExternalResourceVisitor
     AccessSpecifier ??
     Destructor ~ExternalResourceVisitor()
     Method VisitExternalString(Local<v8::String>)
       ParmDecl string
         TemplateRef Local
         TypeRef class v8::String
   ClassDecl PersistentHandleVisitor
     AccessSpecifier ??
     Destructor ~PersistentHandleVisitor()
     Method VisitPersistentHandle(Persistent<v8::Value> *, uint16_t)
       ParmDecl value
         TemplateRef Persistent
         TypeRef class v8::Value
       ParmDecl class_id
         TypeRef uint16_t
   EnumDecl MemoryPressureLevel
     EnumConstantDecl kNone
     EnumConstantDecl kModerate
     EnumConstantDecl kCritical
   ClassDecl EmbedderHeapTracer
     AccessSpecifier ??
     EnumDecl EmbedderStackState
       EnumConstantDecl kUnknown
       EnumConstantDecl kNonEmpty
       EnumConstantDecl kEmpty
     ClassDecl TracedGlobalHandleVisitor
       AccessSpecifier ??
       Destructor ~TracedGlobalHandleVisitor()
       Method VisitTracedGlobalHandle(const TracedGlobal<v8::Value> &)
         ParmDecl value
           TemplateRef TracedGlobal
           TypeRef class v8::Value
     Destructor ~EmbedderHeapTracer()
     Method IterateTracedGlobalHandles(v8::EmbedderHeapTracer::TracedGlobalHandleVisitor *)
       ParmDecl visitor
         TypeRef class v8::EmbedderHeapTracer::TracedGlobalHandleVisitor
     Method RegisterV8References(const std::vector<std::pair<void *, void *> > &)
       ParmDecl embedder_fields
         NamespaceRef std
         TemplateRef vector
         NamespaceRef std
         TemplateRef pair
     Method RegisterEmbedderReference(const TracedGlobal<v8::Value> &)
       ParmDecl ref
         TemplateRef TracedGlobal
         NamespaceRef v8
         TypeRef class v8::Value
     Method TracePrologue()
     Method AdvanceTracing(double)
       ParmDecl deadline_in_ms
     Method IsTracingDone()
     Method TraceEpilogue()
     Method EnterFinalPause(v8::EmbedderHeapTracer::EmbedderStackState)
       ParmDecl stack_state
         TypeRef enum v8::EmbedderHeapTracer::EmbedderStackState
     Method FinalizeTracing()
     Method IsRootForNonTracingGC(const v8::TracedGlobal<v8::Value> &)
       ParmDecl handle
         NamespaceRef v8
         TemplateRef TracedGlobal
         NamespaceRef v8
         TypeRef class v8::Value
     Method GarbageCollectionForTesting(v8::EmbedderHeapTracer::EmbedderStackState)
       ParmDecl stack_state
         TypeRef enum v8::EmbedderHeapTracer::EmbedderStackState
     Method isolate()
       NamespaceRef v8
       TypeRef class v8::Isolate
     AccessSpecifier ??
     FieldDecl isolate_
       NamespaceRef v8
       TypeRef class v8::Isolate
       UnexposedExpr ??
         NullPtrLiteralExpr ??
     FriendDecl ??
       NamespaceRef internal
       TypeRef class v8::internal::LocalEmbedderHeapTracer
   StructDecl SerializeInternalFieldsCallback
     TypedefDecl CallbackFunction
       TypeRef class v8::StartupData
       ParmDecl holder
         TemplateRef Local
         TypeRef class v8::Object
       ParmDecl index
       ParmDecl data
     Constructor SerializeInternalFieldsCallback(v8::SerializeInternalFieldsCallback::CallbackFunction, void *)
       ParmDecl function
         TypeRef v8::SerializeInternalFieldsCallback::CallbackFunction
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data_arg
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     FieldDecl callback
       TypeRef v8::SerializeInternalFieldsCallback::CallbackFunction
     FieldDecl data
   TypedefDecl SerializeEmbedderFieldsCallback
     TypeRef struct v8::SerializeInternalFieldsCallback
   StructDecl DeserializeInternalFieldsCallback
     TypedefDecl CallbackFunction
       ParmDecl holder
         TemplateRef Local
         TypeRef class v8::Object
       ParmDecl index
       ParmDecl payload
         TypeRef class v8::StartupData
       ParmDecl data
     Constructor DeserializeInternalFieldsCallback(v8::DeserializeInternalFieldsCallback::CallbackFunction, void *)
       ParmDecl function
         TypeRef v8::DeserializeInternalFieldsCallback::CallbackFunction
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl data_arg
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     FieldDecl callback
       ParmDecl holder
         TemplateRef Local
         TypeRef class v8::Object
       ParmDecl index
       ParmDecl payload
         TypeRef class v8::StartupData
       ParmDecl data
     FieldDecl data
   TypedefDecl DeserializeEmbedderFieldsCallback
     TypeRef struct v8::DeserializeInternalFieldsCallback
   ClassDecl Isolate
     AccessSpecifier ??
     StructDecl CreateParams
       Constructor CreateParams()
       FieldDecl code_event_handler
         TypeRef v8::JitCodeEventHandler
       FieldDecl constraints
         TypeRef class v8::ResourceConstraints
       FieldDecl snapshot_blob
         TypeRef class v8::StartupData
       FieldDecl counter_lookup_callback
         TypeRef v8::CounterLookupCallback
       FieldDecl create_histogram_callback
         TypeRef v8::CreateHistogramCallback
       FieldDecl add_histogram_sample_callback
         TypeRef v8::AddHistogramSampleCallback
       FieldDecl array_buffer_allocator
         TypeRef class v8::ArrayBuffer
         TypeRef class v8::ArrayBuffer::Allocator
       FieldDecl external_references
         TypeRef intptr_t
       FieldDecl allow_atomics_wait
       FieldDecl only_terminate_in_safe_scope
     ClassDecl Scope
       AccessSpecifier ??
       Constructor Scope(v8::Isolate *)
         ParmDecl isolate
           TypeRef class v8::Isolate
       Destructor ~Scope()
       Constructor Scope(const v8::Isolate::Scope &)
         ParmDecl ??
           TypeRef class v8::Isolate::Scope
       Method operator=(const v8::Isolate::Scope &)
         TypeRef class v8::Isolate::Scope
         ParmDecl ??
           TypeRef class v8::Isolate::Scope
       AccessSpecifier ??
       FieldDecl isolate_
         TypeRef class v8::Isolate
     ClassDecl DisallowJavascriptExecutionScope
       AccessSpecifier ??
       EnumDecl OnFailure
         EnumConstantDecl CRASH_ON_FAILURE
         EnumConstantDecl THROW_ON_FAILURE
         EnumConstantDecl DUMP_ON_FAILURE
       Constructor DisallowJavascriptExecutionScope(v8::Isolate *, v8::Isolate::DisallowJavascriptExecutionScope::OnFailure)
         ParmDecl isolate
           TypeRef class v8::Isolate
         ParmDecl on_failure
           TypeRef enum v8::Isolate::DisallowJavascriptExecutionScope::OnFailure
       Destructor ~DisallowJavascriptExecutionScope()
       Constructor DisallowJavascriptExecutionScope(const v8::Isolate::DisallowJavascriptExecutionScope &)
         ParmDecl ??
           TypeRef class v8::Isolate::DisallowJavascriptExecutionScope
       Method operator=(const v8::Isolate::DisallowJavascriptExecutionScope &)
         TypeRef class v8::Isolate::DisallowJavascriptExecutionScope
         ParmDecl ??
           TypeRef class v8::Isolate::DisallowJavascriptExecutionScope
       AccessSpecifier ??
       FieldDecl on_failure_
         TypeRef enum v8::Isolate::DisallowJavascriptExecutionScope::OnFailure
       FieldDecl internal_
     ClassDecl AllowJavascriptExecutionScope
       AccessSpecifier ??
       Constructor AllowJavascriptExecutionScope(v8::Isolate *)
         ParmDecl isolate
           TypeRef class v8::Isolate
       Destructor ~AllowJavascriptExecutionScope()
       Constructor AllowJavascriptExecutionScope(const v8::Isolate::AllowJavascriptExecutionScope &)
         ParmDecl ??
           TypeRef class v8::Isolate::AllowJavascriptExecutionScope
       Method operator=(const v8::Isolate::AllowJavascriptExecutionScope &)
         TypeRef class v8::Isolate::AllowJavascriptExecutionScope
         ParmDecl ??
           TypeRef class v8::Isolate::AllowJavascriptExecutionScope
       AccessSpecifier ??
       FieldDecl internal_throws_
       FieldDecl internal_assert_
       FieldDecl internal_dump_
     ClassDecl SuppressMicrotaskExecutionScope
       AccessSpecifier ??
       Constructor SuppressMicrotaskExecutionScope(v8::Isolate *)
         ParmDecl isolate
           TypeRef class v8::Isolate
       Destructor ~SuppressMicrotaskExecutionScope()
       Constructor SuppressMicrotaskExecutionScope(const v8::Isolate::SuppressMicrotaskExecutionScope &)
         ParmDecl ??
           TypeRef class v8::Isolate::SuppressMicrotaskExecutionScope
       Method operator=(const v8::Isolate::SuppressMicrotaskExecutionScope &)
         TypeRef class v8::Isolate::SuppressMicrotaskExecutionScope
         ParmDecl ??
           TypeRef class v8::Isolate::SuppressMicrotaskExecutionScope
       AccessSpecifier ??
       FieldDecl isolate_
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       FieldDecl microtask_queue_
         NamespaceRef internal
         TypeRef class v8::internal::MicrotaskQueue
     ClassDecl SafeForTerminationScope
       AccessSpecifier ??
       Constructor SafeForTerminationScope(v8::Isolate *)
         ParmDecl isolate
           NamespaceRef v8
           TypeRef class v8::Isolate
       Destructor ~SafeForTerminationScope()
       Constructor SafeForTerminationScope(const v8::Isolate::SafeForTerminationScope &)
         ParmDecl ??
           TypeRef class v8::Isolate::SafeForTerminationScope
       Method operator=(const v8::Isolate::SafeForTerminationScope &)
         TypeRef class v8::Isolate::SafeForTerminationScope
         ParmDecl ??
           TypeRef class v8::Isolate::SafeForTerminationScope
       AccessSpecifier ??
       FieldDecl isolate_
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       FieldDecl prev_value_
     EnumDecl GarbageCollectionType
       EnumConstantDecl kFullGarbageCollection
       EnumConstantDecl kMinorGarbageCollection
     EnumDecl UseCounterFeature
       EnumConstantDecl kUseAsm
         IntegerLiteral ??
       EnumConstantDecl kBreakIterator
         IntegerLiteral ??
       EnumConstantDecl kLegacyConst
         IntegerLiteral ??
       EnumConstantDecl kMarkDequeOverflow
         IntegerLiteral ??
       EnumConstantDecl kStoreBufferOverflow
         IntegerLiteral ??
       EnumConstantDecl kSlotsBufferOverflow
         IntegerLiteral ??
       EnumConstantDecl kObjectObserve
         IntegerLiteral ??
       EnumConstantDecl kForcedGC
         IntegerLiteral ??
       EnumConstantDecl kSloppyMode
         IntegerLiteral ??
       EnumConstantDecl kStrictMode
         IntegerLiteral ??
       EnumConstantDecl kStrongMode
         IntegerLiteral ??
       EnumConstantDecl kRegExpPrototypeStickyGetter
         IntegerLiteral ??
       EnumConstantDecl kRegExpPrototypeToString
         IntegerLiteral ??
       EnumConstantDecl kRegExpPrototypeUnicodeGetter
         IntegerLiteral ??
       EnumConstantDecl kIntlV8Parse
         IntegerLiteral ??
       EnumConstantDecl kIntlPattern
         IntegerLiteral ??
       EnumConstantDecl kIntlResolved
         IntegerLiteral ??
       EnumConstantDecl kPromiseChain
         IntegerLiteral ??
       EnumConstantDecl kPromiseAccept
         IntegerLiteral ??
       EnumConstantDecl kPromiseDefer
         IntegerLiteral ??
       EnumConstantDecl kHtmlCommentInExternalScript
         IntegerLiteral ??
       EnumConstantDecl kHtmlComment
         IntegerLiteral ??
       EnumConstantDecl kSloppyModeBlockScopedFunctionRedefinition
         IntegerLiteral ??
       EnumConstantDecl kForInInitializer
         IntegerLiteral ??
       EnumConstantDecl kArrayProtectorDirtied
         IntegerLiteral ??
       EnumConstantDecl kArraySpeciesModified
         IntegerLiteral ??
       EnumConstantDecl kArrayPrototypeConstructorModified
         IntegerLiteral ??
       EnumConstantDecl kArrayInstanceProtoModified
         IntegerLiteral ??
       EnumConstantDecl kArrayInstanceConstructorModified
         IntegerLiteral ??
       EnumConstantDecl kLegacyFunctionDeclaration
         IntegerLiteral ??
       EnumConstantDecl kRegExpPrototypeSourceGetter
         IntegerLiteral ??
       EnumConstantDecl kRegExpPrototypeOldFlagGetter
         IntegerLiteral ??
       EnumConstantDecl kDecimalWithLeadingZeroInStrictMode
         IntegerLiteral ??
       EnumConstantDecl kLegacyDateParser
         IntegerLiteral ??
       EnumConstantDecl kDefineGetterOrSetterWouldThrow
         IntegerLiteral ??
       EnumConstantDecl kFunctionConstructorReturnedUndefined
         IntegerLiteral ??
       EnumConstantDecl kAssigmentExpressionLHSIsCallInSloppy
         IntegerLiteral ??
       EnumConstantDecl kAssigmentExpressionLHSIsCallInStrict
         IntegerLiteral ??
       EnumConstantDecl kPromiseConstructorReturnedUndefined
         IntegerLiteral ??
       EnumConstantDecl kConstructorNonUndefinedPrimitiveReturn
         IntegerLiteral ??
       EnumConstantDecl kLabeledExpressionStatement
         IntegerLiteral ??
       EnumConstantDecl kLineOrParagraphSeparatorAsLineTerminator
         IntegerLiteral ??
       EnumConstantDecl kIndexAccessor
         IntegerLiteral ??
       EnumConstantDecl kErrorCaptureStackTrace
         IntegerLiteral ??
       EnumConstantDecl kErrorPrepareStackTrace
         IntegerLiteral ??
       EnumConstantDecl kErrorStackTraceLimit
         IntegerLiteral ??
       EnumConstantDecl kWebAssemblyInstantiation
         IntegerLiteral ??
       EnumConstantDecl kDeoptimizerDisableSpeculation
         IntegerLiteral ??
       EnumConstantDecl kArrayPrototypeSortJSArrayModifiedPrototype
         IntegerLiteral ??
       EnumConstantDecl kFunctionTokenOffsetTooLongForToString
         IntegerLiteral ??
       EnumConstantDecl kWasmSharedMemory
         IntegerLiteral ??
       EnumConstantDecl kWasmThreadOpcodes
         IntegerLiteral ??
       EnumConstantDecl kAtomicsNotify
         IntegerLiteral ??
       EnumConstantDecl kAtomicsWake
         IntegerLiteral ??
       EnumConstantDecl kCollator
         IntegerLiteral ??
       EnumConstantDecl kNumberFormat
         IntegerLiteral ??
       EnumConstantDecl kDateTimeFormat
         IntegerLiteral ??
       EnumConstantDecl kPluralRules
         IntegerLiteral ??
       EnumConstantDecl kRelativeTimeFormat
         IntegerLiteral ??
       EnumConstantDecl kLocale
         IntegerLiteral ??
       EnumConstantDecl kListFormat
         IntegerLiteral ??
       EnumConstantDecl kSegmenter
         IntegerLiteral ??
       EnumConstantDecl kStringLocaleCompare
         IntegerLiteral ??
       EnumConstantDecl kStringToLocaleUpperCase
         IntegerLiteral ??
       EnumConstantDecl kStringToLocaleLowerCase
         IntegerLiteral ??
       EnumConstantDecl kNumberToLocaleString
         IntegerLiteral ??
       EnumConstantDecl kDateToLocaleString
         IntegerLiteral ??
       EnumConstantDecl kDateToLocaleDateString
         IntegerLiteral ??
       EnumConstantDecl kDateToLocaleTimeString
         IntegerLiteral ??
       EnumConstantDecl kAttemptOverrideReadOnlyOnPrototypeSloppy
         IntegerLiteral ??
       EnumConstantDecl kAttemptOverrideReadOnlyOnPrototypeStrict
         IntegerLiteral ??
       EnumConstantDecl kOptimizedFunctionWithOneShotBytecode
         IntegerLiteral ??
       EnumConstantDecl kRegExpMatchIsTrueishOnNonJSRegExp
         IntegerLiteral ??
       EnumConstantDecl kRegExpMatchIsFalseishOnJSRegExp
         IntegerLiteral ??
       EnumConstantDecl kDateGetTimezoneOffset
         IntegerLiteral ??
       EnumConstantDecl kStringNormalize
         IntegerLiteral ??
       EnumConstantDecl kUseCounterFeatureCount
     EnumDecl MessageErrorLevel
       EnumConstantDecl kMessageLog
         ParenExpr ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
       EnumConstantDecl kMessageDebug
         ParenExpr ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
       EnumConstantDecl kMessageInfo
         ParenExpr ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
       EnumConstantDecl kMessageError
         ParenExpr ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
       EnumConstantDecl kMessageWarning
         ParenExpr ??
           BinaryOperator ??
             IntegerLiteral ??
             IntegerLiteral ??
       EnumConstantDecl kMessageAll
         BinaryOperator ??
           BinaryOperator ??
             BinaryOperator ??
               BinaryOperator ??
                 DeclRefExpr kMessageLog
                 DeclRefExpr kMessageDebug
               DeclRefExpr kMessageInfo
             DeclRefExpr kMessageError
           DeclRefExpr kMessageWarning
     TypedefDecl UseCounterCallback
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl feature
         TypeRef enum v8::Isolate::UseCounterFeature
     Method Allocate()
       TypeRef class v8::Isolate
     Method Initialize(v8::Isolate *, const v8::Isolate::CreateParams &)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl params
         TypeRef struct v8::Isolate::CreateParams
     Method New(const v8::Isolate::CreateParams &)
       TypeRef class v8::Isolate
       ParmDecl params
         TypeRef struct v8::Isolate::CreateParams
     Method GetCurrent()
       TypeRef class v8::Isolate
     TypedefDecl AbortOnUncaughtExceptionCallback
       ParmDecl ??
         TypeRef class v8::Isolate
     Method SetAbortOnUncaughtExceptionCallback(v8::Isolate::AbortOnUncaughtExceptionCallback)
       ParmDecl callback
         TypeRef v8::Isolate::AbortOnUncaughtExceptionCallback
     Method SetHostImportModuleDynamicallyCallback(v8::HostImportModuleDynamicallyCallback)
       ParmDecl callback
         TypeRef v8::HostImportModuleDynamicallyCallback
     Method SetHostInitializeImportMetaObjectCallback(v8::HostInitializeImportMetaObjectCallback)
       ParmDecl callback
         TypeRef v8::HostInitializeImportMetaObjectCallback
     Method SetPrepareStackTraceCallback(v8::PrepareStackTraceCallback)
       ParmDecl callback
         TypeRef v8::PrepareStackTraceCallback
     Method MemoryPressureNotification(v8::MemoryPressureLevel)
       ParmDecl level
         TypeRef enum v8::MemoryPressureLevel
     Method Enter()
     Method Exit()
     Method Dispose()
     Method DumpAndResetStats()
     Method DiscardThreadSpecificMetadata()
     Method SetData(uint32_t, void *)
       UnexposedAttr ??
       ParmDecl slot
         TypeRef uint32_t
       ParmDecl data
     Method GetData(uint32_t)
       UnexposedAttr ??
       ParmDecl slot
         TypeRef uint32_t
     Method GetNumberOfDataSlots()
       UnexposedAttr ??
       TypeRef uint32_t
     FunctionTemplate GetDataFromSnapshotOnce(size_t)
       TemplateTypeParameter T
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef T
       ParmDecl index
         TypeRef size_t
     Method GetHeapStatistics(v8::HeapStatistics *)
       ParmDecl heap_statistics
         TypeRef class v8::HeapStatistics
     Method NumberOfHeapSpaces()
       TypeRef size_t
     Method GetHeapSpaceStatistics(v8::HeapSpaceStatistics *, size_t)
       ParmDecl space_statistics
         TypeRef class v8::HeapSpaceStatistics
       ParmDecl index
         TypeRef size_t
     Method NumberOfTrackedHeapObjectTypes()
       TypeRef size_t
     Method GetHeapObjectStatisticsAtLastGC(v8::HeapObjectStatistics *, size_t)
       ParmDecl object_statistics
         TypeRef class v8::HeapObjectStatistics
       ParmDecl type_index
         TypeRef size_t
     Method GetHeapCodeAndMetadataStatistics(v8::HeapCodeStatistics *)
       ParmDecl object_statistics
         TypeRef class v8::HeapCodeStatistics
     Method GetStackSample(const v8::RegisterState &, void **, size_t, v8::SampleInfo *)
       ParmDecl state
         TypeRef struct v8::RegisterState
       ParmDecl frames
       ParmDecl frames_limit
         TypeRef size_t
       ParmDecl sample_info
         TypeRef struct v8::SampleInfo
     Method AdjustAmountOfExternalAllocatedMemory(int64_t)
       UnexposedAttr ??
       TypeRef int64_t
       ParmDecl change_in_bytes
         TypeRef int64_t
     Method NumberOfPhantomHandleResetsSinceLastCall()
       TypeRef size_t
     Method GetHeapProfiler()
       TypeRef class v8::HeapProfiler
     Method SetIdle(bool)
       ParmDecl is_idle
     Method GetArrayBufferAllocator()
       TypeRef class v8::ArrayBuffer
       TypeRef class v8::ArrayBuffer::Allocator
     Method InContext()
     Method GetCurrentContext()
       TemplateRef Local
       TypeRef class v8::Context
     Method GetEnteredContext()
       TemplateRef Local
       TypeRef class v8::Context
     Method GetEnteredOrMicrotaskContext()
       TemplateRef Local
       TypeRef class v8::Context
     Method GetIncumbentContext()
       TemplateRef Local
       TypeRef class v8::Context
     Method ThrowException(Local<v8::Value>)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl exception
         TemplateRef Local
         TypeRef class v8::Value
     TypedefDecl GCCallback
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl type
         TypeRef enum v8::GCType
       ParmDecl flags
         TypeRef enum v8::GCCallbackFlags
     TypedefDecl GCCallbackWithData
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl type
         TypeRef enum v8::GCType
       ParmDecl flags
         TypeRef enum v8::GCCallbackFlags
       ParmDecl data
     Method AddGCPrologueCallback(v8::Isolate::GCCallbackWithData, void *, v8::GCType)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallbackWithData
       ParmDecl data
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl gc_type_filter
         TypeRef enum v8::GCType
         DeclRefExpr kGCTypeAll
     Method AddGCPrologueCallback(v8::Isolate::GCCallback, v8::GCType)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallback
       ParmDecl gc_type_filter
         TypeRef enum v8::GCType
         DeclRefExpr kGCTypeAll
     Method RemoveGCPrologueCallback(v8::Isolate::GCCallbackWithData, void *)
       ParmDecl ??
         TypeRef v8::Isolate::GCCallbackWithData
       ParmDecl data
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method RemoveGCPrologueCallback(v8::Isolate::GCCallback)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallback
     Method SetEmbedderHeapTracer(v8::EmbedderHeapTracer *)
       ParmDecl tracer
         TypeRef class v8::EmbedderHeapTracer
     Method GetEmbedderHeapTracer()
       TypeRef class v8::EmbedderHeapTracer
     EnumDecl AtomicsWaitEvent
       EnumConstantDecl kStartWait
       EnumConstantDecl kWokenUp
       EnumConstantDecl kTimedOut
       EnumConstantDecl kTerminatedExecution
       EnumConstantDecl kAPIStopped
       EnumConstantDecl kNotEqual
     ClassDecl AtomicsWaitWakeHandle
       AccessSpecifier ??
       Method Wake()
     TypedefDecl AtomicsWaitCallback
       ParmDecl event
         TypeRef enum v8::Isolate::AtomicsWaitEvent
       ParmDecl array_buffer
         TemplateRef Local
         TypeRef class v8::SharedArrayBuffer
       ParmDecl offset_in_bytes
         TypeRef size_t
       ParmDecl value
         TypeRef int64_t
       ParmDecl timeout_in_ms
       ParmDecl stop_handle
         TypeRef class v8::Isolate::AtomicsWaitWakeHandle
       ParmDecl data
     Method SetAtomicsWaitCallback(v8::Isolate::AtomicsWaitCallback, void *)
       ParmDecl callback
         TypeRef v8::Isolate::AtomicsWaitCallback
       ParmDecl data
     Method AddGCEpilogueCallback(v8::Isolate::GCCallbackWithData, void *, v8::GCType)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallbackWithData
       ParmDecl data
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl gc_type_filter
         TypeRef enum v8::GCType
         DeclRefExpr kGCTypeAll
     Method AddGCEpilogueCallback(v8::Isolate::GCCallback, v8::GCType)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallback
       ParmDecl gc_type_filter
         TypeRef enum v8::GCType
         DeclRefExpr kGCTypeAll
     Method RemoveGCEpilogueCallback(v8::Isolate::GCCallbackWithData, void *)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallbackWithData
       ParmDecl data
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method RemoveGCEpilogueCallback(v8::Isolate::GCCallback)
       ParmDecl callback
         TypeRef v8::Isolate::GCCallback
     TypedefDecl GetExternallyAllocatedMemoryInBytesCallback
       TypeRef size_t
     Method SetGetExternallyAllocatedMemoryInBytesCallback(v8::Isolate::GetExternallyAllocatedMemoryInBytesCallback)
       ParmDecl callback
         TypeRef v8::Isolate::GetExternallyAllocatedMemoryInBytesCallback
     Method TerminateExecution()
     Method IsExecutionTerminating()
     Method CancelTerminateExecution()
     Method RequestInterrupt(v8::InterruptCallback, void *)
       ParmDecl callback
         TypeRef v8::InterruptCallback
       ParmDecl data
     Method RequestGarbageCollectionForTesting(v8::Isolate::GarbageCollectionType)
       ParmDecl type
         TypeRef enum v8::Isolate::GarbageCollectionType
     Method SetEventLogger(v8::LogEventCallback)
       ParmDecl that
         TypeRef v8::LogEventCallback
     Method AddBeforeCallEnteredCallback(v8::BeforeCallEnteredCallback)
       ParmDecl callback
         TypeRef v8::BeforeCallEnteredCallback
     Method RemoveBeforeCallEnteredCallback(v8::BeforeCallEnteredCallback)
       ParmDecl callback
         TypeRef v8::BeforeCallEnteredCallback
     Method AddCallCompletedCallback(v8::CallCompletedCallback)
       ParmDecl callback
         TypeRef v8::CallCompletedCallback
     Method RemoveCallCompletedCallback(v8::CallCompletedCallback)
       ParmDecl callback
         TypeRef v8::CallCompletedCallback
     Method SetPromiseHook(v8::PromiseHook)
       ParmDecl hook
         TypeRef v8::PromiseHook
     Method SetPromiseRejectCallback(v8::PromiseRejectCallback)
       ParmDecl callback
         TypeRef v8::PromiseRejectCallback
     Method RunMicrotasks()
     Method EnqueueMicrotask(Local<v8::Function>)
       ParmDecl microtask
         TemplateRef Local
         TypeRef class v8::Function
     Method EnqueueMicrotask(v8::MicrotaskCallback, void *)
       ParmDecl callback
         TypeRef v8::MicrotaskCallback
       ParmDecl data
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method SetMicrotasksPolicy(v8::MicrotasksPolicy)
       ParmDecl policy
         TypeRef enum v8::MicrotasksPolicy
     Method GetMicrotasksPolicy()
       TypeRef enum v8::MicrotasksPolicy
     Method AddMicrotasksCompletedCallback(v8::MicrotasksCompletedCallback)
       ParmDecl callback
         TypeRef v8::MicrotasksCompletedCallback
     Method RemoveMicrotasksCompletedCallback(v8::MicrotasksCompletedCallback)
       ParmDecl callback
         TypeRef v8::MicrotasksCompletedCallback
     Method SetUseCounterCallback(v8::Isolate::UseCounterCallback)
       ParmDecl callback
         TypeRef v8::Isolate::UseCounterCallback
     Method SetCounterFunction(v8::CounterLookupCallback)
       ParmDecl ??
         TypeRef v8::CounterLookupCallback
     Method SetCreateHistogramFunction(v8::CreateHistogramCallback)
       ParmDecl ??
         TypeRef v8::CreateHistogramCallback
     Method SetAddHistogramSampleFunction(v8::AddHistogramSampleCallback)
       ParmDecl ??
         TypeRef v8::AddHistogramSampleCallback
     Method IdleNotificationDeadline(double)
       ParmDecl deadline_in_seconds
     Method LowMemoryNotification()
     Method ContextDisposedNotification(bool)
       ParmDecl dependant_context
         BoolLiteralExpr ??
     Method IsolateInForegroundNotification()
     Method IsolateInBackgroundNotification()
     Method EnableMemorySavingsMode()
     Method DisableMemorySavingsMode()
     Method SetRAILMode(v8::RAILMode)
       ParmDecl rail_mode
         TypeRef enum v8::RAILMode
     Method IncreaseHeapLimitForDebugging()
     Method RestoreOriginalHeapLimit()
     Method IsHeapLimitIncreasedForDebugging()
     Method SetJitCodeEventHandler(v8::JitCodeEventOptions, v8::JitCodeEventHandler)
       ParmDecl options
         TypeRef enum v8::JitCodeEventOptions
       ParmDecl event_handler
         TypeRef v8::JitCodeEventHandler
     Method SetStackLimit(uintptr_t)
       ParmDecl stack_limit
         TypeRef uintptr_t
     Method GetCodeRange(void **, size_t *)
       ParmDecl start
       ParmDecl length_in_bytes
         TypeRef size_t
     Method GetUnwindState()
       TypeRef struct v8::UnwindState
     Method SetFatalErrorHandler(v8::FatalErrorCallback)
       ParmDecl that
         TypeRef v8::FatalErrorCallback
     Method SetOOMErrorHandler(v8::OOMErrorCallback)
       ParmDecl that
         TypeRef v8::OOMErrorCallback
     Method AddNearHeapLimitCallback(v8::NearHeapLimitCallback, void *)
       ParmDecl callback
         TypeRef v8::NearHeapLimitCallback
       ParmDecl data
     Method RemoveNearHeapLimitCallback(v8::NearHeapLimitCallback, size_t)
       ParmDecl callback
         TypeRef v8::NearHeapLimitCallback
       ParmDecl heap_limit
         TypeRef size_t
     Method AutomaticallyRestoreInitialHeapLimit(double)
       ParmDecl threshold_percent
         FloatingLiteral ??
     Method SetAllowCodeGenerationFromStringsCallback(v8::AllowCodeGenerationFromStringsCallback)
       ParmDecl callback
         TypeRef v8::AllowCodeGenerationFromStringsCallback
     Method SetAllowWasmCodeGenerationCallback(v8::AllowWasmCodeGenerationCallback)
       ParmDecl callback
         TypeRef v8::AllowWasmCodeGenerationCallback
     Method SetWasmModuleCallback(v8::ExtensionCallback)
       ParmDecl callback
         TypeRef v8::ExtensionCallback
     Method SetWasmInstanceCallback(v8::ExtensionCallback)
       ParmDecl callback
         TypeRef v8::ExtensionCallback
     Method SetWasmStreamingCallback(v8::WasmStreamingCallback)
       ParmDecl callback
         TypeRef v8::WasmStreamingCallback
     Method SetWasmThreadsEnabledCallback(v8::WasmThreadsEnabledCallback)
       ParmDecl callback
         TypeRef v8::WasmThreadsEnabledCallback
     Method IsDead()
     Method AddMessageListener(v8::MessageCallback, Local<v8::Value>)
       ParmDecl that
         TypeRef v8::MessageCallback
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method AddMessageListenerWithErrorLevel(v8::MessageCallback, int, Local<v8::Value>)
       ParmDecl that
         TypeRef v8::MessageCallback
       ParmDecl message_levels
       ParmDecl data
         TemplateRef Local
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr Local
                 TemplateRef Local
                 TypeRef class v8::Value
     Method RemoveMessageListeners(v8::MessageCallback)
       ParmDecl that
         TypeRef v8::MessageCallback
     Method SetFailedAccessCheckCallbackFunction(v8::FailedAccessCheckCallback)
       ParmDecl ??
         TypeRef v8::FailedAccessCheckCallback
     Method SetCaptureStackTraceForUncaughtExceptions(bool, int, StackTrace::StackTraceOptions)
       ParmDecl capture
       ParmDecl frame_limit
         IntegerLiteral ??
       ParmDecl options
         TypeRef class v8::StackTrace
         TypeRef enum v8::StackTrace::StackTraceOptions
         DeclRefExpr kOverview
           TypeRef class v8::StackTrace
     Method VisitExternalResources(v8::ExternalResourceVisitor *)
       ParmDecl visitor
         TypeRef class v8::ExternalResourceVisitor
     Method VisitHandlesWithClassIds(v8::PersistentHandleVisitor *)
       ParmDecl visitor
         TypeRef class v8::PersistentHandleVisitor
     Method VisitHandlesForPartialDependence(v8::PersistentHandleVisitor *)
       ParmDecl visitor
         TypeRef class v8::PersistentHandleVisitor
     Method VisitWeakHandles(v8::PersistentHandleVisitor *)
       ParmDecl visitor
         TypeRef class v8::PersistentHandleVisitor
     Method IsInUse()
     Method SetAllowAtomicsWait(bool)
       ParmDecl allow
     Constructor Isolate()
     Destructor ~Isolate()
     Constructor Isolate(const v8::Isolate &)
       ParmDecl ??
         TypeRef class v8::Isolate
     Method operator=(const v8::Isolate &)
       TypeRef class v8::Isolate
       ParmDecl ??
         TypeRef class v8::Isolate
     Method operator new(size_t)
       ParmDecl size
         TypeRef size_t
     Method operator new[](size_t)
       ParmDecl size
         TypeRef size_t
     Method operator delete(void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method operator delete[](void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     AccessSpecifier ??
     FriendDecl ??
       ClassTemplate PersistentValueMapBase<K, V, Traits>
         TemplateTypeParameter K
         TemplateTypeParameter V
         TemplateTypeParameter Traits
     Method GetDataFromSnapshotOnce(size_t)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl index
         TypeRef size_t
     Method ReportExternalAllocationLimitReached()
     Method CheckMemoryPressure()
   ClassDecl StartupData
     AccessSpecifier ??
     FieldDecl data
     FieldDecl raw_size
   TypedefDecl EntropySource
     ParmDecl buffer
     ParmDecl length
       TypeRef size_t
   TypedefDecl ReturnAddressLocationResolver
     TypeRef uintptr_t
     ParmDecl return_addr_location
       TypeRef uintptr_t
   ClassDecl V8
     AccessSpecifier ??
     Method SetNativesDataBlob(v8::StartupData *)
       ParmDecl startup_blob
         TypeRef class v8::StartupData
     Method SetSnapshotDataBlob(v8::StartupData *)
       ParmDecl startup_blob
         TypeRef class v8::StartupData
     Method SetDcheckErrorHandler(v8::DcheckErrorCallback)
       ParmDecl that
         TypeRef v8::DcheckErrorCallback
     Method SetFlagsFromString(const char *, int)
       ParmDecl str
       ParmDecl length
     Method SetFlagsFromCommandLine(int *, char **, bool)
       ParmDecl argc
       ParmDecl argv
       ParmDecl remove_flags
     Method GetVersion()
     Method Initialize()
     Method SetEntropySource(v8::EntropySource)
       ParmDecl source
         TypeRef v8::EntropySource
     Method SetReturnAddressLocationResolver(v8::ReturnAddressLocationResolver)
       ParmDecl return_address_resolver
         TypeRef v8::ReturnAddressLocationResolver
     Method Dispose()
     Method InitializeICU(const char *)
       ParmDecl icu_data_file
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method InitializeICUDefaultLocation(const char *, const char *)
       ParmDecl exec_path
       ParmDecl icu_data_file
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Method InitializeExternalStartupData(const char *)
       ParmDecl directory_path
     Method InitializeExternalStartupData(const char *, const char *)
       ParmDecl natives_blob
       ParmDecl snapshot_blob
     Method InitializePlatform(v8::Platform *)
       ParmDecl platform
         TypeRef class v8::Platform
     Method ShutdownPlatform()
     Method EnableWebAssemblyTrapHandler(bool)
       ParmDecl use_v8_signal_handler
     AccessSpecifier ??
     Constructor V8()
     Method GlobalizeReference(internal::Isolate *, internal::Address *)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl isolate
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       ParmDecl handle
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method GlobalizeTracedReference(internal::Isolate *, internal::Address *, internal::Address *)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl isolate
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       ParmDecl handle
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl slot
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method MoveGlobalReference(internal::Address **, internal::Address **)
       ParmDecl from
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl to
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method MoveTracedGlobalReference(internal::Address **, internal::Address **)
       ParmDecl from
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl to
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method CopyGlobalReference(internal::Address *)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl from
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method DisposeGlobal(internal::Address *)
       ParmDecl global_handle
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method DisposeTracedGlobal(internal::Address *)
       ParmDecl global_handle
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method MakeWeak(internal::Address *, void *, WeakCallbackInfo<void>::Callback, v8::WeakCallbackType)
       ParmDecl location
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl data
       ParmDecl weak_callback
         TemplateRef WeakCallbackInfo
         TypeRef v8::WeakCallbackInfo<void>::Callback
       ParmDecl type
         TypeRef enum v8::WeakCallbackType
     Method MakeWeak(internal::Address **)
       ParmDecl location_addr
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method ClearWeak(internal::Address *)
       ParmDecl location
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method SetFinalizationCallbackTraced(internal::Address *, void *, WeakCallbackInfo<void>::Callback)
       ParmDecl location
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl parameter
       ParmDecl callback
         TemplateRef WeakCallbackInfo
         TypeRef v8::WeakCallbackInfo<void>::Callback
     Method AnnotateStrongRetainer(internal::Address *, const char *)
       ParmDecl location
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl label
     Method Eternalize(v8::Isolate *, v8::Value *)
       TypeRef class v8::Value
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl handle
         TypeRef class v8::Value
     Method RegisterExternallyReferencedObject(internal::Address *, internal::Isolate *)
       ParmDecl location
         NamespaceRef internal
         TypeRef v8::internal::Address
       ParmDecl isolate
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
     FriendDecl ??
       ClassTemplate PersistentValueMapBase<K, V, T>
         TemplateTypeParameter K
         TemplateTypeParameter V
         TemplateTypeParameter T
     Method FromJustIsNothing()
     Method ToLocalEmpty()
     Method InternalFieldOutOfBounds(int)
       ParmDecl index
     FriendDecl ??
       ClassTemplate Global<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate Local<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate MaybeLocal<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate Maybe<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate TracedGlobal<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate WeakCallbackInfo<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate Eternal<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate PersistentBase<T>
         TemplateTypeParameter T
     FriendDecl ??
       ClassTemplate Persistent<T, M>
         TemplateTypeParameter T
         TemplateTypeParameter M
     FriendDecl ??
       TypeRef class v8::Context
   ClassDecl SnapshotCreator
     AccessSpecifier ??
     EnumDecl FunctionCodeHandling
       EnumConstantDecl kClear
       EnumConstantDecl kKeep
     Constructor SnapshotCreator(v8::Isolate *, const intptr_t *, v8::StartupData *)
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl external_references
         TypeRef intptr_t
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl existing_blob
         TypeRef class v8::StartupData
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Constructor SnapshotCreator(const intptr_t *, v8::StartupData *)
       ParmDecl external_references
         TypeRef intptr_t
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl existing_blob
         TypeRef class v8::StartupData
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     Destructor ~SnapshotCreator()
     Method GetIsolate()
       TypeRef class v8::Isolate
     Method SetDefaultContext(Local<v8::Context>, v8::SerializeInternalFieldsCallback)
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl callback
         TypeRef struct v8::SerializeInternalFieldsCallback
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr SerializeInternalFieldsCallback
                 TypeRef struct v8::SerializeInternalFieldsCallback
                 UnexposedExpr ??
                 UnexposedExpr ??
     Method AddContext(Local<v8::Context>, v8::SerializeInternalFieldsCallback)
       TypeRef size_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl callback
         TypeRef struct v8::SerializeInternalFieldsCallback
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr SerializeInternalFieldsCallback
                 TypeRef struct v8::SerializeInternalFieldsCallback
                 UnexposedExpr ??
                 UnexposedExpr ??
     Method AddTemplate(Local<v8::Template>)
       TypeRef size_t
       ParmDecl template_obj
         TemplateRef Local
         TypeRef class v8::Template
     FunctionTemplate AddData(Local<v8::Context>, Local<T>)
       TemplateTypeParameter T
       UnexposedAttr ??
       TypeRef size_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl object
         TemplateRef Local
         TypeRef T
     FunctionTemplate AddData(Local<T>)
       TemplateTypeParameter T
       UnexposedAttr ??
       TypeRef size_t
       ParmDecl object
         TemplateRef Local
         TypeRef T
     Method CreateBlob(v8::SnapshotCreator::FunctionCodeHandling)
       TypeRef class v8::StartupData
       ParmDecl function_code_handling
         TypeRef enum v8::SnapshotCreator::FunctionCodeHandling
     Constructor SnapshotCreator(const v8::SnapshotCreator &)
       ParmDecl ??
         TypeRef class v8::SnapshotCreator
     Method operator=(const v8::SnapshotCreator &)
       ParmDecl ??
         TypeRef class v8::SnapshotCreator
     AccessSpecifier ??
     Method AddData(Local<v8::Context>, internal::Address)
       TypeRef size_t
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
       ParmDecl object
         NamespaceRef internal
         TypeRef v8::internal::Address
     Method AddData(internal::Address)
       TypeRef size_t
       ParmDecl object
         NamespaceRef internal
         TypeRef v8::internal::Address
     FieldDecl data_
   ClassTemplate Maybe<T>
     TemplateTypeParameter T
     AccessSpecifier ??
     Method IsNothing()
       UnexposedAttr ??
     Method IsJust()
       UnexposedAttr ??
     Method ToChecked()
       UnexposedAttr ??
       TypeRef T
     Method Check()
       UnexposedAttr ??
     Method To(T *)
       UnexposedAttr ??
       UnexposedAttr ??
       ParmDecl out
         TypeRef T
     Method FromJust()
       UnexposedAttr ??
       TypeRef T
     Method FromMaybe(const T &)
       UnexposedAttr ??
       TypeRef T
       ParmDecl default_value
         TypeRef T
     Method operator==(const Maybe<T> &)
       UnexposedAttr ??
       ParmDecl other
         TypeRef Maybe<T>
     Method operator!=(const Maybe<T> &)
       UnexposedAttr ??
       ParmDecl other
         TypeRef Maybe<T>
     AccessSpecifier ??
     Constructor Maybe<T>()
     Constructor Maybe<T>(const T &)
       ParmDecl t
         TypeRef T
     FieldDecl has_value_
     FieldDecl value_
       TypeRef T
     FriendDecl ??
       FunctionTemplate Nothing()
         TemplateTypeParameter U
         TemplateRef Maybe
         TypeRef U
     FriendDecl ??
       FunctionTemplate Just(const U &)
         TemplateTypeParameter U
         TemplateRef Maybe
         TypeRef U
         ParmDecl u
           TypeRef U
   FunctionTemplate Nothing()
     TemplateTypeParameter T
     TemplateRef Maybe
     TypeRef T
   FunctionTemplate Just(const T &)
     TemplateTypeParameter T
     TemplateRef Maybe
     TypeRef T
     ParmDecl t
       TypeRef T
   ClassDecl Maybe<void>
     AccessSpecifier ??
     Method IsNothing()
       UnexposedAttr ??
     Method IsJust()
       UnexposedAttr ??
     Method operator==(const v8::Maybe<void> &)
       UnexposedAttr ??
       ParmDecl other
         TypeRef class v8::Maybe<void>
     Method operator!=(const v8::Maybe<void> &)
       UnexposedAttr ??
       ParmDecl other
         TypeRef class v8::Maybe<void>
     AccessSpecifier ??
     StructDecl JustTag
     Constructor Maybe()
     Constructor Maybe(v8::Maybe<void>::JustTag)
       ParmDecl ??
         TypeRef struct v8::Maybe<void>::JustTag
     FieldDecl is_valid_
     FriendDecl ??
       FunctionTemplate Nothing()
         TemplateTypeParameter U
         TemplateRef Maybe
         TypeRef U
     FriendDecl ??
       FunctionDecl JustVoid()
         TemplateRef Maybe
   FunctionDecl JustVoid()
     TemplateRef Maybe
   ClassDecl TryCatch
     AccessSpecifier ??
     Constructor TryCatch(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~TryCatch()
     Method HasCaught()
     Method CanContinue()
     Method HasTerminated()
     Method ReThrow()
       TemplateRef Local
       TypeRef class v8::Value
     Method Exception()
       TemplateRef Local
       TypeRef class v8::Value
     Method StackTrace(Local<v8::Context>)
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef class v8::Value
       ParmDecl context
         TemplateRef Local
         TypeRef class v8::Context
     Method Message()
       TemplateRef Local
       NamespaceRef v8
       TypeRef class v8::Message
     Method Reset()
     Method SetVerbose(bool)
       ParmDecl value
     Method IsVerbose()
     Method SetCaptureMessage(bool)
       ParmDecl value
     Method JSStackComparableAddress(v8::TryCatch *)
       ParmDecl handler
         TypeRef class v8::TryCatch
     Constructor TryCatch(const v8::TryCatch &)
       ParmDecl ??
         TypeRef class v8::TryCatch
     Method operator=(const v8::TryCatch &)
       ParmDecl ??
         TypeRef class v8::TryCatch
     AccessSpecifier ??
     Method operator new(size_t)
       ParmDecl size
         TypeRef size_t
     Method operator new[](size_t)
       ParmDecl size
         TypeRef size_t
     Method operator delete(void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method operator delete[](void *, size_t)
       ParmDecl ??
       ParmDecl ??
         TypeRef size_t
     Method ResetInternal()
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
     FieldDecl next_
       TypeRef class v8::TryCatch
     FieldDecl exception_
     FieldDecl message_obj_
     FieldDecl js_stack_comparable_address_
     FieldDecl is_verbose_
       IntegerLiteral ??
     FieldDecl can_continue_
       IntegerLiteral ??
     FieldDecl capture_message_
       IntegerLiteral ??
     FieldDecl rethrow_
       IntegerLiteral ??
     FieldDecl has_terminated_
       IntegerLiteral ??
     FriendDecl ??
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
   ClassDecl ExtensionConfiguration
     AccessSpecifier ??
     Constructor ExtensionConfiguration()
     Constructor ExtensionConfiguration(int, const char **)
       ParmDecl name_count
       ParmDecl names
     Method begin()
     Method end()
     AccessSpecifier ??
     FieldDecl name_count_
     FieldDecl names_
   ClassDecl Context
     AccessSpecifier ??
     Method Global()
       TemplateRef Local
       TypeRef class v8::Object
     Method DetachGlobal()
     Method New(v8::Isolate *, v8::ExtensionConfiguration *, MaybeLocal<v8::ObjectTemplate>, MaybeLocal<v8::Value>, v8::DeserializeInternalFieldsCallback)
       TemplateRef Local
       TypeRef class v8::Context
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl extensions
         TypeRef class v8::ExtensionConfiguration
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl global_template
         TemplateRef MaybeLocal
         TypeRef class v8::ObjectTemplate
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr MaybeLocal
                 TemplateRef MaybeLocal
                 TypeRef class v8::ObjectTemplate
       ParmDecl global_object
         TemplateRef MaybeLocal
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr MaybeLocal
                 TemplateRef MaybeLocal
                 TypeRef class v8::Value
       ParmDecl internal_fields_deserializer
         TypeRef struct v8::DeserializeInternalFieldsCallback
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr DeserializeInternalFieldsCallback
                 TypeRef struct v8::DeserializeInternalFieldsCallback
                 UnexposedExpr ??
                 UnexposedExpr ??
     Method FromSnapshot(v8::Isolate *, size_t, v8::DeserializeInternalFieldsCallback, v8::ExtensionConfiguration *, MaybeLocal<v8::Value>)
       TemplateRef MaybeLocal
       TypeRef class v8::Context
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl context_snapshot_index
         TypeRef size_t
       ParmDecl embedder_fields_deserializer
         TypeRef struct v8::DeserializeInternalFieldsCallback
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr DeserializeInternalFieldsCallback
                 TypeRef struct v8::DeserializeInternalFieldsCallback
                 UnexposedExpr ??
                 UnexposedExpr ??
       ParmDecl extensions
         TypeRef class v8::ExtensionConfiguration
         UnexposedExpr ??
           NullPtrLiteralExpr ??
       ParmDecl global_object
         TemplateRef MaybeLocal
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr MaybeLocal
                 TemplateRef MaybeLocal
                 TypeRef class v8::Value
     Method NewRemoteContext(v8::Isolate *, Local<v8::ObjectTemplate>, MaybeLocal<v8::Value>)
       TemplateRef MaybeLocal
       TypeRef class v8::Object
       ParmDecl isolate
         TypeRef class v8::Isolate
       ParmDecl global_template
         TemplateRef Local
         TypeRef class v8::ObjectTemplate
       ParmDecl global_object
         TemplateRef MaybeLocal
         TypeRef class v8::Value
         UnexposedExpr ??
           CallExpr ??
             UnexposedExpr ??
               CallExpr MaybeLocal
                 TemplateRef MaybeLocal
                 TypeRef class v8::Value
     Method SetSecurityToken(Local<v8::Value>)
       ParmDecl token
         TemplateRef Local
         TypeRef class v8::Value
     Method UseDefaultSecurityToken()
     Method GetSecurityToken()
       TemplateRef Local
       TypeRef class v8::Value
     Method Enter()
     Method Exit()
     Method GetIsolate()
       TypeRef class v8::Isolate
     EnumDecl EmbedderDataFields
       EnumConstantDecl kDebugIdIndex
         IntegerLiteral ??
     Method GetNumberOfEmbedderDataFields()
       TypeRef uint32_t
     Method GetEmbedderData(int)
       UnexposedAttr ??
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl index
     Method GetExtrasBindingObject()
       TemplateRef Local
       TypeRef class v8::Object
     Method SetEmbedderData(int, Local<v8::Value>)
       ParmDecl index
       ParmDecl value
         TemplateRef Local
         TypeRef class v8::Value
     Method GetAlignedPointerFromEmbedderData(int)
       UnexposedAttr ??
       ParmDecl index
     Method SetAlignedPointerInEmbedderData(int, void *)
       ParmDecl index
       ParmDecl value
     Method AllowCodeGenerationFromStrings(bool)
       ParmDecl allow
     Method IsCodeGenerationFromStringsAllowed()
     Method SetErrorMessageForCodeGenerationFromStrings(Local<v8::String>)
       ParmDecl message
         TemplateRef Local
         TypeRef class v8::String
     FunctionTemplate GetDataFromSnapshotOnce(size_t)
       TemplateTypeParameter T
       UnexposedAttr ??
       TemplateRef MaybeLocal
       TypeRef T
       ParmDecl index
         TypeRef size_t
     ClassDecl Scope
       AccessSpecifier ??
       Constructor Scope(Local<v8::Context>)
         UnexposedAttr ??
         ParmDecl context
           TemplateRef Local
           TypeRef class v8::Context
       Destructor ~Scope()
         UnexposedAttr ??
       AccessSpecifier ??
       FieldDecl context_
         TemplateRef Local
         TypeRef class v8::Context
     ClassDecl BackupIncumbentScope
       FinalAttr ??
       AccessSpecifier ??
       Constructor BackupIncumbentScope(Local<v8::Context>)
         ParmDecl backup_incumbent_context
           TemplateRef Local
           TypeRef class v8::Context
       Destructor ~BackupIncumbentScope()
       Method JSStackComparableAddress()
         TypeRef uintptr_t
       AccessSpecifier ??
       FriendDecl ??
         NamespaceRef internal
         TypeRef class v8::internal::Isolate
       FieldDecl backup_incumbent_context_
         TemplateRef Local
         TypeRef class v8::Context
       FieldDecl js_stack_comparable_address_
         TypeRef uintptr_t
         UnexposedExpr ??
           IntegerLiteral ??
       FieldDecl prev_
         TypeRef class v8::Context::BackupIncumbentScope
         UnexposedExpr ??
           NullPtrLiteralExpr ??
     AccessSpecifier ??
     FriendDecl ??
       TypeRef class v8::Value
     FriendDecl ??
       TypeRef class v8::Script
     FriendDecl ??
       TypeRef class v8::Object
     FriendDecl ??
       TypeRef class v8::Function
     Method GetDataFromSnapshotOnce(size_t)
       NamespaceRef internal
       TypeRef v8::internal::Address
       ParmDecl index
         TypeRef size_t
     Method SlowGetEmbedderData(int)
       TemplateRef Local
       TypeRef class v8::Value
       ParmDecl index
     Method SlowGetAlignedPointerFromEmbedderData(int)
       ParmDecl index
   ClassDecl Unlocker
     AccessSpecifier ??
     Constructor Unlocker(v8::Isolate *)
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~Unlocker()
     AccessSpecifier ??
     Method Initialize(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
   ClassDecl Locker
     AccessSpecifier ??
     Constructor Locker(v8::Isolate *)
       UnexposedAttr ??
       ParmDecl isolate
         TypeRef class v8::Isolate
     Destructor ~Locker()
     Method IsLocked(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     Method IsActive()
     Constructor Locker(const v8::Locker &)
       ParmDecl ??
         TypeRef class v8::Locker
     Method operator=(const v8::Locker &)
       ParmDecl ??
         TypeRef class v8::Locker
     AccessSpecifier ??
     Method Initialize(v8::Isolate *)
       ParmDecl isolate
         TypeRef class v8::Isolate
     FieldDecl has_lock_
     FieldDecl top_level_
     FieldDecl isolate_
       NamespaceRef internal
       TypeRef class v8::internal::Isolate
   ClassDecl Unwinder
     AccessSpecifier ??
     Method TryUnwindV8Frames(const v8::UnwindState &, v8::RegisterState *, const void *)
       ParmDecl unwind_state
         TypeRef struct v8::UnwindState
       ParmDecl register_state
         TypeRef struct v8::RegisterState
       ParmDecl stack_base
     Method PCIsInV8(const v8::UnwindState &, void *)
       ParmDecl unwind_state
         TypeRef struct v8::UnwindState
       ParmDecl pc
   Method New(v8::Isolate *, Local<T>)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef Local
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TemplateRef Local
       TypeRef T
   Method New(v8::Isolate *, const PersistentBase<T> &)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef Local
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TemplateRef PersistentBase
       TypeRef T
   Method New(v8::Isolate *, const TracedGlobal<T> &)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef Local
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TemplateRef TracedGlobal
       TypeRef T
   Method New(v8::Isolate *, T *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef Local
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TypeRef T
   FunctionTemplate Set(v8::Isolate *, Local<S>)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Eternal
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl handle
       TemplateRef Local
       TypeRef S
   Method Get(v8::Isolate *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef Eternal
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
   Method ToLocalChecked()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef T
     TemplateRef MaybeLocal
     TypeRef T
   Method GetInternalField(int)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef WeakCallbackInfo
     TypeRef T
     ParmDecl index
   Method New(v8::Isolate *, T *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TypeRef T
   FunctionTemplate Copy(const Persistent<S, M2> &)
     TemplateTypeParameter S
     TemplateTypeParameter M2
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateTypeParameter M
     TemplateRef Persistent
     TypeRef T
     TypeRef M
     ParmDecl that
       TemplateRef Persistent
       TypeRef S
       TypeRef M2
   Method IsIndependent()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   Method IsNearDeath()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   Method IsWeak()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   Method Reset()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   FunctionTemplate Reset(v8::Isolate *, const Local<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl other
       TemplateRef Local
       TypeRef S
   FunctionTemplate Reset(v8::Isolate *, const PersistentBase<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl other
       TemplateRef PersistentBase
       TypeRef S
   FunctionTemplate SetWeak(P *, typename WeakCallbackInfo<P>::Callback, v8::WeakCallbackType)
     TemplateTypeParameter P
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl parameter
       TypeRef P
     ParmDecl callback
       TemplateRef WeakCallbackInfo
       TypeRef P
     ParmDecl type
       TypeRef enum v8::WeakCallbackType
   Method SetWeak()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   FunctionTemplate ClearWeak()
     TemplateTypeParameter P
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef P
     TemplateRef PersistentBase
     TypeRef T
   Method AnnotateStrongRetainer(const char *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl label
   Method RegisterExternalReference(v8::Isolate *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
   Method MarkIndependent()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   Method MarkActive()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
   Method SetWrapperClassId(uint16_t)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PersistentBase
     TypeRef T
     ParmDecl class_id
       TypeRef uint16_t
   Method WrapperClassId()
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef uint16_t
     TemplateRef PersistentBase
     TypeRef T
   Constructor Global<T>(Global<T> &&)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Global
     TypeRef T
     ParmDecl other
       TypeRef Global<T>
   FunctionTemplate operator=(Global<S> &&)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Global
     TypeRef T
     TemplateRef Global
     TypeRef T
     ParmDecl rhs
       TemplateRef Global
       TypeRef S
   Method New(v8::Isolate *, T *, T **)
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl that
       TypeRef T
     ParmDecl slot
       TypeRef T
   Method Reset()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
   FunctionTemplate Reset(v8::Isolate *, const Local<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl other
       TemplateRef Local
       TypeRef S
   Constructor TracedGlobal<T>(TracedGlobal<T> &&)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl other
       TypeRef TracedGlobal<T>
   FunctionTemplate operator=(TracedGlobal<S> &&)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl rhs
       TemplateRef TracedGlobal
       TypeRef S
   Method SetWrapperClassId(uint16_t)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl class_id
       TypeRef uint16_t
   Method WrapperClassId()
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef uint16_t
     TemplateRef TracedGlobal
     TypeRef T
   Method SetFinalizationCallback(void *, typename WeakCallbackInfo<void>::Callback)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef TracedGlobal
     TypeRef T
     ParmDecl parameter
     ParmDecl callback
       TemplateRef WeakCallbackInfo
       TypeRef v8::WeakCallbackInfo<void>::Callback
   Constructor ReturnValue<T>(internal::Address *)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl slot
       NamespaceRef internal
       TypeRef v8::internal::Address
   FunctionTemplate Set(const Persistent<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl handle
       TemplateRef Persistent
       TypeRef S
   FunctionTemplate Set(const Global<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl handle
       TemplateRef Global
       TypeRef S
   FunctionTemplate Set(const TracedGlobal<S> &)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl handle
       TemplateRef TracedGlobal
       TypeRef S
   FunctionTemplate Set(const Local<S>)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl handle
       TemplateRef Local
       TypeRef S
   Method Set(double)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl i
   Method Set(int32_t)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl i
       TypeRef int32_t
   Method Set(uint32_t)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl i
       TypeRef uint32_t
   Method Set(bool)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl value
   Method SetNull()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
   Method SetUndefined()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
   Method SetEmptyString()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
   Method GetIsolate()
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef class v8::Isolate
     TemplateRef ReturnValue
     TypeRef T
   Method Get()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Value
     TemplateRef ReturnValue
     TypeRef T
   FunctionTemplate Set(S *)
     TemplateTypeParameter S
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     ParmDecl whatever
       TypeRef S
   Method GetDefaultValue()
     UnexposedAttr ??
     TemplateTypeParameter T
     NamespaceRef internal
     TypeRef v8::internal::Address
     TemplateRef ReturnValue
     TypeRef T
   Constructor FunctionCallbackInfo<T>(internal::Address *, internal::Address *, int)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef FunctionCallbackInfo
     TypeRef T
     ParmDecl implicit_args
       NamespaceRef internal
       TypeRef v8::internal::Address
     ParmDecl values
       NamespaceRef internal
       TypeRef v8::internal::Address
     ParmDecl length
   Method operator[](int)
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Value
     TemplateRef FunctionCallbackInfo
     TypeRef T
     ParmDecl i
   Method This()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Object
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method Holder()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Object
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method NewTarget()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Value
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method Data()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Value
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method GetIsolate()
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef class v8::Isolate
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method GetReturnValue()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method IsConstructCall()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Method Length()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef FunctionCallbackInfo
     TypeRef T
   Constructor ScriptOrigin(Local<v8::Value>, Local<v8::Integer>, Local<v8::Integer>, Local<v8::Boolean>, Local<v8::Integer>, Local<v8::Value>, Local<v8::Boolean>, Local<v8::Boolean>, Local<v8::Boolean>, Local<v8::PrimitiveArray>)
     UnexposedAttr ??
     TypeRef class v8::ScriptOrigin
     ParmDecl resource_name
       TemplateRef Local
       TypeRef class v8::Value
     ParmDecl resource_line_offset
       TemplateRef Local
       TypeRef class v8::Integer
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Integer
     ParmDecl resource_column_offset
       TemplateRef Local
       TypeRef class v8::Integer
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Integer
     ParmDecl resource_is_shared_cross_origin
       TemplateRef Local
       TypeRef class v8::Boolean
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Boolean
     ParmDecl script_id
       TemplateRef Local
       TypeRef class v8::Integer
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Integer
     ParmDecl source_map_url
       TemplateRef Local
       TypeRef class v8::Value
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Value
     ParmDecl resource_is_opaque
       TemplateRef Local
       TypeRef class v8::Boolean
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Boolean
     ParmDecl is_wasm
       TemplateRef Local
       TypeRef class v8::Boolean
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Boolean
     ParmDecl is_module
       TemplateRef Local
       TypeRef class v8::Boolean
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::Boolean
     ParmDecl host_defined_options
       TemplateRef Local
       TypeRef class v8::PrimitiveArray
       UnexposedExpr ??
         CallExpr ??
           UnexposedExpr ??
             CallExpr Local
               TemplateRef Local
               TypeRef class v8::PrimitiveArray
   Method ResourceName()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Value
     TypeRef class v8::ScriptOrigin
   Method HostDefinedOptions()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::PrimitiveArray
     TypeRef class v8::ScriptOrigin
   Method ResourceLineOffset()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Integer
     TypeRef class v8::ScriptOrigin
   Method ResourceColumnOffset()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Integer
     TypeRef class v8::ScriptOrigin
   Method ScriptID()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Integer
     TypeRef class v8::ScriptOrigin
   Method SourceMapUrl()
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Value
     TypeRef class v8::ScriptOrigin
   Constructor Source(Local<v8::String>, const v8::ScriptOrigin &, v8::ScriptCompiler::CachedData *)
     UnexposedAttr ??
     TypeRef class v8::ScriptCompiler
     TypeRef class v8::ScriptCompiler::Source
     ParmDecl string
       TemplateRef Local
       TypeRef class v8::String
     ParmDecl origin
       TypeRef class v8::ScriptOrigin
     ParmDecl data
       TypeRef struct v8::ScriptCompiler::CachedData
       UnexposedExpr ??
         NullPtrLiteralExpr ??
   Constructor Source(Local<v8::String>, v8::ScriptCompiler::CachedData *)
     UnexposedAttr ??
     TypeRef class v8::ScriptCompiler
     TypeRef class v8::ScriptCompiler::Source
     ParmDecl string
       TemplateRef Local
       TypeRef class v8::String
     ParmDecl data
       TypeRef struct v8::ScriptCompiler::CachedData
       UnexposedExpr ??
         NullPtrLiteralExpr ??
   Destructor ~Source()
     UnexposedAttr ??
     TypeRef class v8::ScriptCompiler
     TypeRef class v8::ScriptCompiler::Source
   Method GetCachedData()
     UnexposedAttr ??
     TypeRef class v8::ScriptCompiler
     TypeRef struct v8::ScriptCompiler::CachedData
     TypeRef class v8::ScriptCompiler
     TypeRef class v8::ScriptCompiler::Source
   Method GetResourceOptions()
     UnexposedAttr ??
     TypeRef class v8::ScriptOriginOptions
     TypeRef class v8::ScriptCompiler
     TypeRef class v8::ScriptCompiler::Source
   Method New(v8::Isolate *, bool)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Boolean
     TypeRef class v8::Boolean
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl value
   Method Set(v8::Isolate *, const char *, Local<v8::Data>)
     UnexposedAttr ??
     TypeRef class v8::Template
     ParmDecl isolate
       TypeRef class v8::Isolate
     ParmDecl name
     ParmDecl value
       TemplateRef Local
       TypeRef class v8::Data
   Method Cast(v8::Data *)
     UnexposedAttr ??
     TypeRef class v8::FunctionTemplate
     TypeRef class v8::FunctionTemplate
     ParmDecl data
       TypeRef class v8::Data
   Method Cast(v8::Data *)
     UnexposedAttr ??
     TypeRef class v8::ObjectTemplate
     TypeRef class v8::ObjectTemplate
     ParmDecl data
       TypeRef class v8::Data
   Method Cast(v8::Data *)
     UnexposedAttr ??
     TypeRef class v8::Signature
     TypeRef class v8::Signature
     ParmDecl data
       TypeRef class v8::Data
   Method Cast(v8::Data *)
     UnexposedAttr ??
     TypeRef class v8::AccessorSignature
     TypeRef class v8::AccessorSignature
     ParmDecl data
       TypeRef class v8::Data
   Method GetInternalField(int)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Value
     TypeRef class v8::Object
     ParmDecl index
   Method GetAlignedPointerFromInternalField(int)
     UnexposedAttr ??
     TypeRef class v8::Object
     ParmDecl index
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::String
     TypeRef class v8::String
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Empty(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::String
     TypeRef class v8::String
     ParmDecl isolate
       TypeRef class v8::Isolate
   Method GetExternalStringResource()
     UnexposedAttr ??
     TypeRef class v8::String
     TypeRef class v8::String::ExternalStringResource
     TypeRef class v8::String
   Method GetExternalStringResourceBase(String::Encoding *)
     UnexposedAttr ??
     TypeRef class v8::String
     TypeRef class v8::String::ExternalStringResourceBase
     TypeRef class v8::String
     ParmDecl encoding_out
       TypeRef class v8::String
       TypeRef enum v8::String::Encoding
   Method IsUndefined()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method QuickIsUndefined()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method IsNull()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method QuickIsNull()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method IsNullOrUndefined()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method QuickIsNullOrUndefined()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method IsString()
     UnexposedAttr ??
     TypeRef class v8::Value
   Method QuickIsString()
     UnexposedAttr ??
     TypeRef class v8::Value
   FunctionTemplate Cast(T *)
     TemplateTypeParameter T
     UnexposedAttr ??
     TypeRef class v8::Value
     TypeRef class v8::Value
     ParmDecl value
       TypeRef T
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Boolean
     TypeRef class v8::Boolean
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Name
     TypeRef class v8::Name
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Symbol
     TypeRef class v8::Symbol
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Data *)
     UnexposedAttr ??
     TypeRef class v8::Private
     TypeRef class v8::Private
     ParmDecl data
       TypeRef class v8::Data
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Number
     TypeRef class v8::Number
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Integer
     TypeRef class v8::Integer
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Int32
     TypeRef class v8::Int32
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Uint32
     TypeRef class v8::Uint32
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::BigInt
     TypeRef class v8::BigInt
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Date
     TypeRef class v8::Date
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::StringObject
     TypeRef class v8::StringObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::SymbolObject
     TypeRef class v8::SymbolObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::NumberObject
     TypeRef class v8::NumberObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::BigIntObject
     TypeRef class v8::BigIntObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::BooleanObject
     TypeRef class v8::BooleanObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::RegExp
     TypeRef class v8::RegExp
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Object
     TypeRef class v8::Object
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Array
     TypeRef class v8::Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Map
     TypeRef class v8::Map
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Set
     TypeRef class v8::Set
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Promise
     TypeRef class v8::Promise
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Proxy
     TypeRef class v8::Proxy
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::WasmModuleObject
     TypeRef class v8::WasmModuleObject
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Promise
     TypeRef class v8::Promise::Resolver
     TypeRef class v8::Promise
     TypeRef class v8::Promise::Resolver
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::ArrayBuffer
     TypeRef class v8::ArrayBuffer
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::ArrayBufferView
     TypeRef class v8::ArrayBufferView
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::TypedArray
     TypeRef class v8::TypedArray
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Uint8Array
     TypeRef class v8::Uint8Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Int8Array
     TypeRef class v8::Int8Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Uint16Array
     TypeRef class v8::Uint16Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Int16Array
     TypeRef class v8::Int16Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Uint32Array
     TypeRef class v8::Uint32Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Int32Array
     TypeRef class v8::Int32Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Float32Array
     TypeRef class v8::Float32Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Float64Array
     TypeRef class v8::Float64Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::BigInt64Array
     TypeRef class v8::BigInt64Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::BigUint64Array
     TypeRef class v8::BigUint64Array
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Uint8ClampedArray
     TypeRef class v8::Uint8ClampedArray
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::DataView
     TypeRef class v8::DataView
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::SharedArrayBuffer
     TypeRef class v8::SharedArrayBuffer
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::Function
     TypeRef class v8::Function
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method Cast(v8::Value *)
     UnexposedAttr ??
     TypeRef class v8::External
     TypeRef class v8::External
     ParmDecl value
       NamespaceRef v8
       TypeRef class v8::Value
   Method GetIsolate()
     UnexposedAttr ??
     TemplateTypeParameter T
     TypeRef class v8::Isolate
     TemplateRef PropertyCallbackInfo
     TypeRef T
   Method Data()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Value
     TemplateRef PropertyCallbackInfo
     TypeRef T
   Method This()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Object
     TemplateRef PropertyCallbackInfo
     TypeRef T
   Method Holder()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef Local
     TypeRef class v8::Object
     TemplateRef PropertyCallbackInfo
     TypeRef T
   Method GetReturnValue()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef ReturnValue
     TypeRef T
     TemplateRef PropertyCallbackInfo
     TypeRef T
   Method ShouldThrowOnError()
     UnexposedAttr ??
     TemplateTypeParameter T
     TemplateRef PropertyCallbackInfo
     TypeRef T
   FunctionDecl Undefined(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Primitive
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl Null(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Primitive
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl True(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Boolean
     ParmDecl isolate
       TypeRef class v8::Isolate
   FunctionDecl False(v8::Isolate *)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Boolean
     ParmDecl isolate
       TypeRef class v8::Isolate
   Method SetData(uint32_t, void *)
     UnexposedAttr ??
     TypeRef class v8::Isolate
     ParmDecl slot
       TypeRef uint32_t
     ParmDecl data
   Method GetData(uint32_t)
     UnexposedAttr ??
     TypeRef class v8::Isolate
     ParmDecl slot
       TypeRef uint32_t
   Method GetNumberOfDataSlots()
     UnexposedAttr ??
     TypeRef uint32_t
     TypeRef class v8::Isolate
   FunctionTemplate GetDataFromSnapshotOnce(size_t)
     TemplateTypeParameter T
     UnexposedAttr ??
     TemplateRef MaybeLocal
     TypeRef T
     TypeRef class v8::Isolate
     ParmDecl index
       TypeRef size_t
   Method AdjustAmountOfExternalAllocatedMemory(int64_t)
     UnexposedAttr ??
     TypeRef int64_t
     TypeRef class v8::Isolate
     ParmDecl change_in_bytes
       TypeRef int64_t
   Method GetEmbedderData(int)
     UnexposedAttr ??
     TemplateRef Local
     TypeRef class v8::Value
     TypeRef class v8::Context
     ParmDecl index
   Method GetAlignedPointerFromEmbedderData(int)
     UnexposedAttr ??
     TypeRef class v8::Context
     ParmDecl index
   FunctionTemplate GetDataFromSnapshotOnce(size_t)
     TemplateTypeParameter T
     UnexposedAttr ??
     TemplateRef MaybeLocal
     TypeRef T
     TypeRef class v8::Context
     ParmDecl index
       TypeRef size_t
   FunctionTemplate AddData(Local<v8::Context>, Local<T>)
     TemplateTypeParameter T
     UnexposedAttr ??
     TypeRef size_t
     TypeRef class v8::SnapshotCreator
     ParmDecl context
       TemplateRef Local
       TypeRef class v8::Context
     ParmDecl object
       TemplateRef Local
       TypeRef T
   FunctionTemplate AddData(Local<T>)
     TemplateTypeParameter T
     UnexposedAttr ??
     TypeRef size_t
     TypeRef class v8::SnapshotCreator
     ParmDecl object
       TemplateRef Local
       TypeRef T
 Namespace v8
   StructDecl Nada1
   StructDecl Nada2
     BaseSpecifier struct v8::Nada1
       TypeRef struct v8::Nada1
   StructDecl Nada3
     BaseSpecifier struct v8::Nada2
       TypeRef struct v8::Nada2
     FieldDecl a
     FieldDecl b
     FieldDecl c
   StructDecl Nada4
     BaseSpecifier struct v8::Nada3
       TypeRef struct v8::Nada3
     FieldDecl d
   ClassDecl Local<v8::Number>
     NamespaceRef v8
     TypeRef class v8::Number
   ClassDecl Local<v8::String>
     NamespaceRef v8
     TypeRef class v8::String
Context
  base: []
  deriv: []
  fields: []
Data
  base: []
  deriv: ["Template"]
  fields: []
Isolate
  base: []
  deriv: []
  fields: []
AccessorSignature
  base: []
  deriv: []
  fields: []
Array
  base: []
  deriv: []
  fields: []
ArrayBuffer
  base: []
  deriv: []
  fields: []
BigInt
  base: []
  deriv: []
  fields: []
BigIntObject
  base: []
  deriv: []
  fields: []
Boolean
  base: []
  deriv: []
  fields: []
BooleanObject
  base: []
  deriv: []
  fields: []
Date
  base: []
  deriv: []
  fields: []
External
  base: []
  deriv: []
  fields: []
Function
  base: []
  deriv: []
  fields: []
FunctionTemplate
  base: []
  deriv: []
  fields: []
HeapProfiler
  base: []
  deriv: []
  fields: []
Nada1
  base: []
  deriv: ["Nada2"]
  fields: []
ImplementationUtilities
  base: []
  deriv: []
  fields: []
Nada2
  base: ["Nada1"]
  deriv: ["Nada3"]
  fields: []
Int32
  base: []
  deriv: []
  fields: []
Nada3
  base: ["Nada2"]
  deriv: ["Nada4"]
  fields: ["a", "b", "c"]
Integer
  base: []
  deriv: []
  fields: []
Nada4
  base: ["Nada3"]
  deriv: []
  fields: ["a", "b", "c", "d"]
Name
  base: []
  deriv: []
  fields: []
Number
  base: []
  deriv: []
  fields: []
NumberObject
  base: []
  deriv: []
  fields: []
Local
  base: []
  deriv: []
  fields: []
Object
  base: []
  deriv: ["Set", "Map", "ArrayBufferView", "RegExp"]
  fields: []
ObjectOperationDescriptor
  base: []
  deriv: []
  fields: []
Local
  base: []
  deriv: []
  fields: []
ObjectTemplate
  base: []
  deriv: []
  fields: []
Platform
  base: []
  deriv: []
  fields: []
Primitive
  base: []
  deriv: []
  fields: []
Promise
  base: []
  deriv: []
  fields: []
PropertyDescriptor
  base: []
  deriv: []
  fields: []
Proxy
  base: []
  deriv: []
  fields: []
RawOperationDescriptor
  base: []
  deriv: []
  fields: []
Script
  base: []
  deriv: []
  fields: []
SharedArrayBuffer
  base: []
  deriv: []
  fields: []
Signature
  base: []
  deriv: []
  fields: []
StartupData
  base: []
  deriv: []
  fields: []
StackFrame
  base: []
  deriv: []
  fields: []
StackTrace
  base: []
  deriv: []
  fields: []
String
  base: []
  deriv: []
  fields: []
StringObject
  base: []
  deriv: []
  fields: []
Symbol
  base: []
  deriv: []
  fields: []
SymbolObject
  base: []
  deriv: []
  fields: []
PrimitiveArray
  base: []
  deriv: []
  fields: []
Private
  base: []
  deriv: []
  fields: []
Uint32
  base: []
  deriv: []
  fields: []
Utils
  base: []
  deriv: []
  fields: []
Value
  base: []
  deriv: []
  fields: []
WasmModuleObject
  base: []
  deriv: []
  fields: []
CallHandlerHelper
  base: []
  deriv: []
  fields: []
EscapableHandleScope
  base: []
  deriv: []
  fields: []
HandleScope
  base: []
  deriv: []
  fields: []
EmbedderHeapTracer
  base: []
  deriv: []
  fields: []
SealHandleScope
  base: []
  deriv: []
  fields: ["isolate_", "prev_limit_", "prev_sealed_level_"]
ScriptOrModule
  base: []
  deriv: []
  fields: []
ScriptOriginOptions
  base: []
  deriv: []
  fields: ["flags_"]
ScriptOrigin
  base: []
  deriv: []
  fields: ["resource_name_", "resource_line_offset_", "resource_column_offset_", "options_", "script_id_", "source_map_url_", "host_defined_options_"]
UnboundScript
  base: []
  deriv: []
  fields: []
UnboundModuleScript
  base: []
  deriv: []
  fields: []
Location
  base: []
  deriv: []
  fields: ["line_number_", "column_number_"]
Module
  base: []
  deriv: []
  fields: []
ScriptCompiler
  base: []
  deriv: []
  fields: []
Message
  base: []
  deriv: []
  fields: []
RegisterState
  base: []
  deriv: []
  fields: ["pc", "sp", "fp"]
SampleInfo
  base: []
  deriv: []
  fields: ["frames_count", "vm_state", "external_callback_entry"]
MemoryRange
  base: []
  deriv: []
  fields: ["start", "length_in_bytes"]
JSEntryStub
  base: []
  deriv: []
  fields: ["code"]
UnwindState
  base: []
  deriv: []
  fields: ["code_range", "embedded_code_range", "js_entry_stub"]
JSON
  base: []
  deriv: []
  fields: []
ValueSerializer
  base: []
  deriv: []
  fields: ["private_"]
ValueDeserializer
  base: []
  deriv: []
  fields: ["private_"]
Map
  base: ["Object"]
  deriv: []
  fields: []
Set
  base: ["Object"]
  deriv: []
  fields: []
OwnedBuffer
  base: []
  deriv: []
  fields: ["buffer", "size"]
CompiledWasmModule
  base: []
  deriv: []
  fields: ["native_module_"]
WasmStreaming
  base: []
  deriv: []
  fields: ["impl_"]
WasmModuleObjectBuilderStreaming
  base: []
  deriv: []
  fields: ["isolate_", "promise_", "streaming_decoder_"]
ArrayBufferView
  base: ["Object"]
  deriv: ["TypedArray", "DataView"]
  fields: []
TypedArray
  base: ["ArrayBufferView"]
  deriv: ["Int32Array", "Float32Array", "Int16Array", "BigInt64Array", "Uint8ClampedArray", "Uint8Array", "Int8Array", "Float64Array", "Uint32Array", "BigUint64Array", "Uint16Array"]
  fields: []
Uint8Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Uint8ClampedArray
  base: ["TypedArray"]
  deriv: []
  fields: []
Int8Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Uint16Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Int16Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Uint32Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Int32Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Float32Array
  base: ["TypedArray"]
  deriv: []
  fields: []
Float64Array
  base: ["TypedArray"]
  deriv: []
  fields: []
BigInt64Array
  base: ["TypedArray"]
  deriv: []
  fields: []
BigUint64Array
  base: ["TypedArray"]
  deriv: []
  fields: []
DataView
  base: ["ArrayBufferView"]
  deriv: []
  fields: []
RegExp
  base: ["Object"]
  deriv: []
  fields: []
Template
  base: ["Data"]
  deriv: []
  fields: []
NamedPropertyHandlerConfiguration
  base: []
  deriv: []
  fields: ["getter", "setter", "query", "deleter", "enumerator", "definer", "descriptor", "data", "flags"]
IndexedPropertyHandlerConfiguration
  base: []
  deriv: []
  fields: ["getter", "setter", "query", "deleter", "enumerator", "definer", "descriptor", "data", "flags"]
Extension
  base: []
  deriv: []
  fields: ["name_", "source_length_", "source_", "dep_count_", "deps_", "auto_enable_"]
ResourceConstraints
  base: []
  deriv: []
  fields: ["max_semi_space_size_in_kb_", "max_old_space_size_", "stack_limit_", "code_range_size_", "max_zone_pool_size_"]
Exception
  base: []
  deriv: []
  fields: []
PromiseRejectMessage
  base: []
  deriv: []
  fields: ["promise_", "event_", "value_", "stack_trace_"]
MicrotasksScope
  base: []
  deriv: []
  fields: ["isolate_", "microtask_queue_", "run_"]
HeapStatistics
  base: []
  deriv: []
  fields: ["total_heap_size_", "total_heap_size_executable_", "total_physical_size_", "total_available_size_", "used_heap_size_", "heap_size_limit_", "malloced_memory_", "external_memory_", "peak_malloced_memory_", "does_zap_garbage_", "number_of_native_contexts_", "number_of_detached_contexts_"]
V8
  base: []
  deriv: []
  fields: []
HeapSpaceStatistics
  base: []
  deriv: []
  fields: ["space_name_", "space_size_", "space_used_size_", "space_available_size_", "physical_space_size_"]
HeapObjectStatistics
  base: []
  deriv: []
  fields: ["object_type_", "object_sub_type_", "object_count_", "object_size_"]
HeapCodeStatistics
  base: []
  deriv: []
  fields: ["code_and_metadata_size_", "bytecode_and_metadata_size_", "external_script_source_size_"]
JitCodeEvent
  base: []
  deriv: []
  fields: ["type", "code_type", "code_start", "code_len", "script", "user_data", "isolate"]
ExternalResourceVisitor
  base: []
  deriv: []
  fields: []
PersistentHandleVisitor
  base: []
  deriv: []
  fields: []
SerializeInternalFieldsCallback
  base: []
  deriv: []
  fields: ["callback", "data"]
DeserializeInternalFieldsCallback
  base: []
  deriv: []
  fields: ["callback", "data"]
SnapshotCreator
  base: []
  deriv: []
  fields: ["data_"]
Maybe
  base: []
  deriv: []
  fields: ["is_valid_"]
TryCatch
  base: []
  deriv: []
  fields: ["isolate_", "next_", "exception_", "message_obj_", "js_stack_comparable_address_", "is_verbose_", "can_continue_", "capture_message_", "rethrow_", "has_terminated_"]
ExtensionConfiguration
  base: []
  deriv: []
  fields: ["name_count_", "names_"]
Unlocker
  base: []
  deriv: []
  fields: ["isolate_"]
Locker
  base: []
  deriv: []
  fields: ["has_lock_", "top_level_", "isolate_"]
Unwinder
  base: []
  deriv: []
  fields: []
