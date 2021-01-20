#include <napi.h>

class Fibo : public Napi::ObjectWrap<Fibo> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    Fibo(const Napi::CallbackInfo& info);
    static Napi::Value CreateNewItem(const Napi::CallbackInfo& info);

  private:
    double _value;
    long int _prevFib = 0;
    long int _curFib = 1;
 
    Napi::Value get(const Napi::CallbackInfo& info);
    Napi::Value clear(const Napi::CallbackInfo& info);
};

Napi::Object Fibo::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "Fibo", {
        InstanceMethod<&Fibo::get>("get"),
        InstanceMethod<&Fibo::clear>("clear"),
        StaticMethod<&Fibo::CreateNewItem>("CreateNewItem"),
    });

    Napi::FunctionReference* constructor = new Napi::FunctionReference();

    *constructor = Napi::Persistent(func);
    exports.Set("Fibo", func);

   
    env.SetInstanceData<Napi::FunctionReference>(constructor);

    return exports;
}

Fibo::Fibo(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Fibo>(info) {}

Napi::Value Fibo::get(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();

    long int nextFib = this->_prevFib + this->_curFib;

    this->_prevFib = this->_curFib;
    this->_curFib = nextFib;


    return Napi::Number::New(env, nextFib);
}

Napi::Value Fibo::clear(const Napi::CallbackInfo& info){

    Napi::Env env = info.Env();

    this->_prevFib = 0;
    this->_curFib = 1;

    return Napi::Number::New(env,  this->_prevFib);
}


Napi::Object Init (Napi::Env env, Napi::Object exports) {
    Fibo::Init(env, exports);
    return exports;
}


Napi::Value Fibo::CreateNewItem(const Napi::CallbackInfo& info) {
  Napi::FunctionReference* constructor =
      info.Env().GetInstanceData<Napi::FunctionReference>();
  return constructor->New({});
}

NODE_API_MODULE(fibo, Init);