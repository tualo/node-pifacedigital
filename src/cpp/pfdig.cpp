#include "pfdig.h"
#include <napi.h>


Napi::Object PIFaceDigital::Init(Napi::Env env, Napi::Object exports) {
    // This method is used to hook the accessor and method callbacks
    /*
    Napi::Function func = DefineClass(env, "PIFaceDigital", {

        //StaticMethod<&PIFaceDigital::CreateNewItem>("CreateNewItem"),
        InstanceMethod("Get", &PIFaceDigital::Get),
        InstanceMethod("Set", &PIFaceDigital::Set),
        InstanceMethod("Open", &PIFaceDigital::Open),
        InstanceMethod("Close", &PIFaceDigital::Close),
        InstanceMethod("GetInput", &PIFaceDigital::GetInput),
        InstanceMethod("GetOutput", &PIFaceDigital::GetOutput),

    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("PIFaceDigital", func);
    */

    exports.Set("Get", Napi::Function::New(env, PIFaceDigital::Get));
    exports.Set("Set", Napi::Function::New(env, PIFaceDigital::Set));
    exports.Set("Open", Napi::Function::New(env, PIFaceDigital::Open));
    exports.Set("Close", Napi::Function::New(env, PIFaceDigital::Close));
    exports.Set("GetInput", Napi::Function::New(env, PIFaceDigital::GetInput));
    exports.Set("GetOutput", Napi::Function::New(env, PIFaceDigital::GetOutput));

    exports.Set("get", Napi::Function::New(env, PIFaceDigital::Get));
    exports.Set("set", Napi::Function::New(env, PIFaceDigital::Set));
    exports.Set("open", Napi::Function::New(env, PIFaceDigital::Open));
    exports.Set("close", Napi::Function::New(env, PIFaceDigital::Close));
    exports.Set("getInput", Napi::Function::New(env, PIFaceDigital::GetInput));
    exports.Set("getOutput", Napi::Function::New(env, PIFaceDigital::GetOutput));

    return exports;
}





Napi::Value PIFaceDigital::Open(const Napi::CallbackInfo& info) {
    uint32_t hw_addr = info[0].As<Napi::Number>();
	pifacedigital_open(hw_addr);
    return Napi::Boolean::New(info.Env(), true);
}

Napi::Value PIFaceDigital::Close(const Napi::CallbackInfo& info) {
    uint32_t hw_addr = info[0].As<Napi::Number>();
	pifacedigital_close(hw_addr);
    return Napi::Boolean::New(info.Env(), true);
}


Napi::Value PIFaceDigital::Set(const Napi::CallbackInfo& info) {
	if(info.Length() == 3) {
        uint32_t hw_addr = info[0].As<Napi::Number>();
        Napi::Number _i = info[1].As<Napi::Number>();
        Napi::Number _j = info[2].As<Napi::Number>();
        int i = (int)_i;
        int j = (int) _j;
        pifacedigital_write_bit(i, j, OUTPUT, hw_addr);
    }
    return Napi::Boolean::New(info.Env(), true);
}

Napi::Value PIFaceDigital::Get(const Napi::CallbackInfo& info) {
	uint8_t res = 0;
    uint32_t hw_addr = info[0].As<Napi::Number>();
	if(info.Length() == 2) {
        Napi::Number _i = info[1].As<Napi::Number>();
        int i = (int)_i;
        res = pifacedigital_read_bit(i, INPUT, hw_addr);
	}else if(info.Length() == 3) {
        Napi::Number _i = info[1].As<Napi::Number>();
        Napi::Number _j = info[2].As<Napi::Number>();
        int i = (int)_i;
        int t = (int) _j;

        if (t==0){
			res = pifacedigital_read_bit(i, INPUT, hw_addr);
		}else if (t==1){
			res = pifacedigital_read_bit(i, OUTPUT, hw_addr);
		}

    }
    return Napi::Number::New(info.Env(), res);
}

Napi::Value PIFaceDigital::GetInput(const Napi::CallbackInfo& info) {
    uint32_t hw_addr = info[0].As<Napi::Number>();
	uint8_t inputs = pifacedigital_read_reg(INPUT, hw_addr);
    return Napi::Number::New(info.Env(), inputs);
}


Napi::Value PIFaceDigital::GetOutput(const Napi::CallbackInfo& info) {
    uint32_t hw_addr = info[0].As<Napi::Number>();
	uint8_t outputs = pifacedigital_read_reg(OUTPUT, hw_addr);
    return Napi::Number::New(info.Env(), outputs);
}
