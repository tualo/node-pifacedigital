#include "NPIFaceDigital.h"

v8::Persistent<FunctionTemplate> PIFaceDigital::constructor;


void PIFaceDigital::Init(v8::Handle<v8::Object> exports) {
  Isolate* isolate = Isolate::GetCurrent();
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(Tile::New);
  constructor.Reset(tpl);

  tpl->SetClassName(String::NewFromUtf8(isolate, "PIFaceDigital"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "get", Get);
	Nan::SetPrototypeMethod(tpl, "set", Set);
	Nan::SetPrototypeMethod(tpl, "open", Open);
	Nan::SetPrototypeMethod(tpl, "close", Close);
	Nan::SetPrototypeMethod(tpl, "getInput", GetInput);
	Nan::SetPrototypeMethod(tpl, "getOutput", GetOutput);
	//Nan::SetPrototypeMethod(tpl, "watch", Watch);
	exports->Set(String::NewFromUtf8(isolate, "PIFaceDigital"), tpl->GetFunction());
}

/*
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
	NODE_SET_PROTOTYPE_METHOD(ctor, "getInput", GetInput);
	NODE_SET_PROTOTYPE_METHOD(ctor, "getOutput", GetOutput);
	NODE_SET_PROTOTYPE_METHOD(ctor, "watch", Watch);

	target->Set(NanNew("PIFaceDigital"), ctor->GetFunction());


}
*/

void PIFaceDigital::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  if (info.IsConstructCall()) {
		PIFaceDigital *pifacedigital;
	  if (args.Length() == 0){
	    pifacedigital = new PIFaceDigital;
	  } else if (args.Length() == 1){
	    pifacedigital = new PIFaceDigital( args[0]->IntegerValue() );
	  }
	  pifacedigital->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }
}

/*
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
*/

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


void PIFaceDigital::Open(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	if(info.Length() == 1) {
  	obj->hw_addr = info[0]->IntegerValue();
	}
	pifacedigital_open(obj->hw_addr);
	info.GetReturnValue().Set(true);
}

/*
NAN_METHOD(PIFaceDigital::Open){
  SETUP_FUNCTION(PIFaceDigital)
	if(args.Length() == 1) {
  	self->hw_addr = args[0]->IntegerValue();
	}
  pifacedigital_open(self->hw_addr);
}
*/
void PIFaceDigital::Close(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	pifacedigital_close(obj->hw_addr);
	info.GetReturnValue().Set(true);
	obj->hw_addr = -1;
}
/*
NAN_METHOD(PIFaceDigital::Close){
  SETUP_FUNCTION(PIFaceDigital)
  pifacedigital_close(self->hw_addr);
  self->hw_addr = -1;
}
*/

void PIFaceDigital::Set(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	if(info.Length() == 2) {
  	int i = info[0]->IntegerValue();
  	int j = info[1]->IntegerValue();
    pifacedigital_write_bit(i, j, OUTPUT, self->hw_addr);
  }
	info.GetReturnValue().Set(true);
}
/*
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
*/

void PIFaceDigital::Get(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	uint8_t res = 0;
	if(info.Length() == 1) {
  	int i = info[0]->IntegerValue();
    res = pifacedigital_read_bit(i, INPUT, obj->hw_addr);
  }else if(info.Length() == 2) {
		int i = info[0]->IntegerValue();
		int t = info[1]->IntegerValue();
		if (t==0){
			res = pifacedigital_read_bit(i, INPUT, obj->hw_addr);
		}else if (t==1){
			res = pifacedigital_read_bit(i, OUTPUT, obj->hw_addr);
		}
  } else {
		Nan::ThrowTypeError("Invalid number of arguments");
  }
	info.GetReturnValue().Set(res);
}

/*
NAN_METHOD(PIFaceDigital::Get){
	SETUP_FUNCTION(PIFaceDigital)
  uint8_t res = 0;
  if(args.Length() == 1) {
  	int i = args[0]->IntegerValue();
    res = pifacedigital_read_bit(i, INPUT, self->hw_addr);

  }else if(args.Length() == 2) {
		int i = args[0]->IntegerValue();
		int t = args[1]->IntegerValue();
		if (t==0){
			res = pifacedigital_read_bit(i, INPUT, self->hw_addr);
		}else if (t==1){
			res = pifacedigital_read_bit(i, OUTPUT, self->hw_addr);
		}
  } else {
    NanThrowTypeError( "Invalid number of arguments" );
  }

	NanReturnValue(res);
}
*/


void PIFaceDigital::GetInput(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	uint8_t inputs = pifacedigital_read_reg(INPUT, obj->hw_addr);
	info.GetReturnValue().Set(inputs);
}

/*
NAN_METHOD(PIFaceDigital::GetInput){
	SETUP_FUNCTION(PIFaceDigital)
	uint8_t inputs = pifacedigital_read_reg(INPUT, self->hw_addr);
	NanReturnValue(inputs);
}
*/

void PIFaceDigital::GetOutput(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	uint8_t outputs = pifacedigital_read_reg(OUTPUT, obj->hw_addr);
	info.GetReturnValue().Set(outputs);
}

/*
NAN_METHOD(PIFaceDigital::GetOutput){
	SETUP_FUNCTION(PIFaceDigital)
	uint8_t inputs = pifacedigital_read_reg(OUTPUT, self->hw_addr);
	NanReturnValue(inputs);
}
*/


void PIFaceDigital::GetOutput(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);
  PIFaceDigital* obj = Nan::ObjectWrap::Unwrap<PIFaceDigital>(info.This());
	uint8_t outputs = pifacedigital_read_reg(OUTPUT, obj->hw_addr);
	info.GetReturnValue().Set(outputs);
}

/*
NAN_METHOD(PIFaceDigital::Watch){
	SETUP_FUNCTION(PIFaceDigital)
	//int points = args[0]->Uint32Value();
  NanCallback callback = new NanCallback(args[0].As<Function>());
  NanAsyncQueueWorker(new AsyncWorker(callback, self->hw_addr));
  NanReturnUndefined();
}
*/
