#include <node.h>
#include "pfdig.h"
#include <napi.h>

// Initialize native add-on
Napi::Object Init (Napi::Env env, Napi::Object exports) {
    PIFaceDigital::Init(env, exports);
    return exports;
}

// Register and initialize native add-on
NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
