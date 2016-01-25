#include <node.h>
#include "NPIFaceDigital.h"

using namespace v8;

void Init(Handle<Object> target) {
  PIFaceDigital::Init(target);
}

NODE_MODULE(pifacedigital, Init)
