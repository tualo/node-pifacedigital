#include "NPIFaceDigital.h"

extern "C" void
init(Handle<Object> target) {
  PIFaceDigital::Init(target);
};

NODE_MODULE(pifacedigital, init)
