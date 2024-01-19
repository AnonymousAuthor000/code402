#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <time.h>
#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"
#include "tensorflow/lite/kernels/kernel_util.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/cpu_backend_context.h"
// #include "tensorflow/lite/kernels/internal/optimized/optimized_ops.h"
#include "tensorflow/lite/kernels/internal/optimized/multithreaded_conv.h"
#include "tensorflow/lite/kernels/eigen_support.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
// const int num = 150528;

using namespace tflite;

extern "C" const float* tflite_minimal(char* path, float* input_v, int num_input, int num_output) {
// int main(int argc, char* argv[]) {
//   srand(time(NULL));
  const char* filename = path;
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromFile(filename);
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model, resolver);
  std::unique_ptr<tflite::Interpreter> interpreter;
  builder(&interpreter);
  interpreter->SetNumThreads(1);
  // gettimeofday( &t_start, NULL);
  interpreter->AllocateTensors();
  // std::cout << "runs in here #3 " << std::endl;
  float* input = interpreter->typed_input_tensor<float>(0);
  memcpy(input, input_v, 1*num_input*sizeof(float));
  // std::cout << "runs in here #4 " << std::endl;
  interpreter->Invoke();
  float* output = interpreter->typed_output_tensor<float>(0);
  float* output_f = new float[num_output];
  memcpy(output_f, output, 1*num_output*sizeof(float));
  return output_f;
  // return 0;
}
