#include <pifacedigital.h>

class AsyncWorker : public NanAsyncWorker {
 public:
  AsyncWorker(NanCallback callback, int hw_addr): NanAsyncWorker(callback), points(points) {}
  ~AsyncWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on this.
  void Execute () {
    pifacedigital_enable_interrupts();
    int success = pifacedigital_wait_for_input(&this->inputs, -1, this->hw_addr); ) > 0){
    printf("Interrupt detected. Inputs: 0x%x\n", this->inputs);
    pifacedigital_disable_interrupts();
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    NanScope();
    printf("HandleOKCallback\n");
    Local<Value> argv[] = { Local<Value>::New(Null()) , Number::New(inputs) };
    callback->Call(2, argv);
  };

 private:
  int hw_addr;
  uint8_t inputs;
};
