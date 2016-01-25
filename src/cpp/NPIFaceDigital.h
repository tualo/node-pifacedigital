#ifndef __NODE_PIFACEDIGITAL_H__
#define __NODE_PIFACEDIGITAL_H__

#include <string.h>
#include <node.h>
#include <node_object_wrap.h>
#include <nan.h>

#include <pifacedigital.h>
//#include "AsyncWorker.h"


using namespace v8;
using namespace node;

class PIFaceDigital : public Nan::ObjectWrap {
  public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;
    static void Init(Handle<Object> target);

    PIFaceDigital();
    PIFaceDigital(int addr);

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  private:
    ~PIFaceDigital();
    static void Get(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void Set(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void Open(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void Close(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void GetInput(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void GetOutput(const Nan::FunctionCallbackInfo<v8::Value>& info);
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
