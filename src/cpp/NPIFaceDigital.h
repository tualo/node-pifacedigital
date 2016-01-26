#ifndef __NODE_PIFACEDIGITAL_H__
#define __NODE_PIFACEDIGITAL_H__

#include <string.h>
#include <node.h>
#include <node_object_wrap.h>
#include <uv.h>
//#include <nan.h>

#include <pifacedigital.h>
// #include "AsyncWorker.h"


using namespace v8;


struct ASyncInfo
{
// required
	uv_work_t request; // libuv
	Isolate* isolate;
	Local<Function> callback; // javascript callback
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
	//printf("Interrupt detected. Inputs: 0x%x\n", info->hw_addr);	
	while ( 0==(success = pifacedigital_wait_for_input(&inputs, info->timeout, info->hw_addr))){
		if (success==0){
			printf("Interrupt detected. Inputs: 0x%x\n", inputs);
			
//	const unsigned argc = 2;
//	Local<v8::Integer> argv[argc] = {};
	
	// execute the callback
//	info->callback->Call(Null(info->isolate),argc,argv);

	
		}else {
			printf("pifacedigital_wait_for_input error or timeout\n");
		}
	}
	pifacedigital_disable_interrupts();
}



static void AsyncAfter(uv_work_t *req, int status)
{
	// get the reference to the baton from the request
	ASyncInfo *info = static_cast<ASyncInfo *>(req->data);
	// set up return arguments
	Local<Value> argv[] =
	{
		//Handle<Value>(Int32::New(info->success)),
		//Handle<Value>(Int32::New(info->input))
	};
	
	// execute the callback
	const unsigned argc = 0;
	info->callback->Call(Null(info->isolate),argc,argv);
	// dispose the callback object from the info
	//info->callback.Dispose();
	// delete the baton object
	delete info;
}



using namespace v8;
using namespace node;

class PIFaceDigital : public node::ObjectWrap {
  public:
	  static v8::Persistent<v8::Function> constructor;
  
    //static Persistent<Function> constructor;
    //static Nan::Persistent<v8::FunctionTemplate> constructor;
    //static void Init(Handle<Object> target);
    static void Init(v8::Local<v8::Object> exports);

    PIFaceDigital();
    PIFaceDigital(int addr);

    static void New(const v8::FunctionCallbackInfo<v8::Value>& info);

  private:
    ~PIFaceDigital();
    static void Get(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Set(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Open(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Close(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void GetInput(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void GetOutput(const v8::FunctionCallbackInfo<v8::Value>& info);
    static void Watch(const v8::FunctionCallbackInfo<v8::Value>& info);
    int hw_addr;
};

/*
class PIFaceDigital: public node::ObjectWrap {
  public:


    static Persistent<FunctionTemplate> constructor;

    static void Init(Handle<Object> target);
    static NAN_METHOD(New);

    PIFaceDigital();
    PIFaceDigital(int addr);
    ~PIFaceDigital();

    JSFUNC(Get)
    JSFUNC(Set)
    JSFUNC(Open)
    JSFUNC(Close)
    JSFUNC(GetInput)
    JSFUNC(GetOutput)
    JSFUNC(Watch)


  private:
    int hw_addr;
};
*/
#endif
