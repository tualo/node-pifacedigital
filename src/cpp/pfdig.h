
#include "pifacedigital.h"
#include <napi.h>
#include <uv.h>

/*
struct ASyncInfo
{
    // required
    uv_work_t request; // libuv
    v8::Isolate* isolate;
    v8::Local<v8::Function> callback; // javascript callback
    // optional : data goes here.
    // data that doesn't go back to javascript can be any typedef
    // data that goes back to javascript needs to be a supported type
    int hw_addr;
    int timeout;
    uint8_t inputs;
    int success;
};


// called by libuv worker in separate thread
static void WaitForAsync(uv_work_t *req)
{
	ASyncInfo *info = static_cast<ASyncInfo *>(req->data);
	pifacedigital_enable_interrupts();
    uint8_t inputs;
    int success;
	while ( 0==(success = pifacedigital_wait_for_input(&inputs, info->timeout, info->hw_addr))){
		if (success==0){
			printf("Interrupt detected. Inputs: 0x%x\n", inputs);
		}else {
			printf("pifacedigital_wait_for_input error or timeout\n");
		}
	}
	pifacedigital_disable_interrupts();
}



static void AsyncAfter(uv_work_t *req, int status)
{
	ASyncInfo *info = static_cast<ASyncInfo *>(req->data);
	v8::Local<v8::Value> argv[] = {
		//Handle<Value>(Int32::New(info->success)),
		//Handle<Value>(Int32::New(info->input))
	};
	const unsigned argc = 0;
    v8::Local<v8::Context> context = info->isolate->GetCurrentContext();
    info->callback->Call(context, Null(info->isolate), argc, NULL).ToLocalChecked();
	delete info;
}

*/

/*
class PIFaceDigital : public Napi::ObjectWrap<PIFaceDigital> {
  public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    PIFaceDigital(const Napi::CallbackInfo& info);
    Napi::Value Get(const Napi::CallbackInfo& info);

  private:
    static Napi::FunctionReference constructor;

    Napi::Value Set(const Napi::CallbackInfo& info);
    Napi::Value Open(const Napi::CallbackInfo& info);
    Napi::Value Close(const Napi::CallbackInfo& info);
    Napi::Value GetInput(const Napi::CallbackInfo& info);
    Napi::Value GetOutput(const Napi::CallbackInfo& info);
    //Napi::Boolean Watch(const Napi::CallbackInfo& info);
    
    int hw_addr;
};
*/

namespace PIFaceDigital{
    Napi::Object Init(Napi::Env env, Napi::Object exports);
    Napi::Value Get(const Napi::CallbackInfo& info);
    Napi::Value Set(const Napi::CallbackInfo& info);
    Napi::Value Open(const Napi::CallbackInfo& info);
    Napi::Value Close(const Napi::CallbackInfo& info);
    Napi::Value GetInput(const Napi::CallbackInfo& info);
    Napi::Value GetOutput(const Napi::CallbackInfo& info);
}

