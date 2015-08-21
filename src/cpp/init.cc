#include "NPIFaceDigital.h"

extern "C" void 
init(Handle<Object> target) {
    NanScope();
    PIFaceDigital::Init(target);
};

NODE_MODULE(pifacedigital, init)
