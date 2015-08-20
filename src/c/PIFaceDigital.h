#ifndef __NODE_PIFACEDIGITAL_H__
#define __NODE_PIFACEDIGITAL_H__

#include <node/v8.h>
#include <node/node.h>
#include <node/node_object_wrap.h>
#include <node/node_version.h>
#include <node/node_buffer.h>
#include <string.h>
#include <nan.h>
#include <pifacedigital.h>

#define REQ_FUN_ARG(I, VAR)                                             \
  if (args.Length() <= (I) || !args[I]->IsFunction())                   \
    return NanThrowTypeError("Argument " #I " must be a function");  \
  Local<Function> VAR = Local<Function>::Cast(args[I]);


#define SETUP_FUNCTION(TYP)	\
	NanScope();		\
	TYP *self = ObjectWrap::Unwrap<TYP>(args.This());

#define JSFUNC(NAME) \
  static NAN_METHOD(NAME);

#define JSTHROW_TYPE(ERR) \
  NanThrowTypeError( ERR );


#define JSTHROW(ERR) \
  NanThrowError( ERR );


#define INT_FROM_ARGS(NAME, IND) \
  if (args[IND]->IsInt32()){ \
    NAME = args[IND]->Uint32Value(); \
  }

#define DOUBLE_FROM_ARGS(NAME, IND) \
  if (args[IND]->IsInt32()){ \
    NAME = args[IND]->NumberValue(); \
  }

using namespace v8;
using namespace node;

class PIFaceDigital: public node::ObjectWrap {
  public:
    static Persistent<FunctionTemplate> constructor;

    static void Init(Handle<Object> target);
    static NAN_METHOD(New);

    PIFaceDigital();
    PIFaceDigital(int addr);

    JSFUNC(Get)
    JSFUNC(Set)
    JSFUNC(Open)
    JSFUNC(Close)
    
  private:
    int hw_addr;
};

#endif
