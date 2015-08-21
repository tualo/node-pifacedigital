#include "NPIFaceDigital.h"
#include <pifacedigital.h>

v8::Persistent<FunctionTemplate> PIFaceDigital::constructor;

void PIFaceDigital::Init(Handle<Object> target) {
	NanScope();

  // Version string.
  char out [21];
  int n = sprintf(out, "%i.%i", 1, 0);
  target->Set(NanNew<String>("version"), NanNew<String>(out, n));

  //NODE_SET_METHOD(target, "readImage", ReadImage);

	//Class
  Local<FunctionTemplate> ctor = NanNew<FunctionTemplate>(PIFaceDigital::New);
  NanAssignPersistent(constructor, ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(NanNew("PIFaceDigital"));

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(ctor, "get", Get);
  NODE_SET_PROTOTYPE_METHOD(ctor, "set", Set);
	NODE_SET_PROTOTYPE_METHOD(ctor, "open", Open);
	NODE_SET_PROTOTYPE_METHOD(ctor, "close", Close);

	target->Set(NanNew("PIFaceDigital"), ctor->GetFunction());

}

NAN_METHOD(PIFaceDigital::New) {
  NanScope();
	if (args.This()->InternalFieldCount() == 0){
    NanThrowTypeError("Cannot instantiate without new");
  }
  PIFaceDigital *pifacedigital;
  if (args.Length() == 0){
    pifacedigital = new PIFaceDigital;
  } else if (args.Length() == 1){
    pifacedigital = new PIFaceDigital( args[0]->IntegerValue() );
  }
  pifacedigital->Wrap(args.Holder());
  NanReturnValue(args.Holder());
}

PIFaceDigital::PIFaceDigital(): ObjectWrap() {
	hw_addr = 0;
}


PIFaceDigital::PIFaceDigital(int addr): ObjectWrap() {
  hw_addr = addr;
}

PIFaceDigital::~PIFaceDigital(){
  if (hw_addr!=-1){
		pifacedigital_write_reg(0x00, OUTPUT, hw_addr);
    pifacedigital_close(hw_addr);
    hw_addr = -1;
  }
}


NAN_METHOD(PIFaceDigital::Open){
  SETUP_FUNCTION(PIFaceDigital)
	if(args.Length() == 1) {
  	self->hw_addr = args[0]->IntegerValue();
	}
  pifacedigital_open(self->hw_addr);
}

NAN_METHOD(PIFaceDigital::Close){
  SETUP_FUNCTION(PIFaceDigital)
  pifacedigital_close(self->hw_addr);
  self->hw_addr = -1;
}

NAN_METHOD(PIFaceDigital::Set){
	SETUP_FUNCTION(PIFaceDigital)

  if(args.Length() == 2) {
  	int i = args[0]->IntegerValue();
  	int j = args[1]->IntegerValue();
    pifacedigital_write_bit(i, j, OUTPUT, self->hw_addr);
  } else {
    NanThrowTypeError( "Invalid number of arguments" );
  }

	NanReturnUndefined();
}

NAN_METHOD(PIFaceDigital::Get){
	SETUP_FUNCTION(PIFaceDigital)
  uint8_t res = 0;
  if(args.Length() == 1) {
  	int i = args[0]->IntegerValue();
    //res = pifacedigital_digital_read(i);
    res = pifacedigital_read_bit(i, OUTPUT, self->hw_addr);
  } else {
    NanThrowTypeError( "Invalid number of arguments" );
  }

	NanReturnValue(res);
}
