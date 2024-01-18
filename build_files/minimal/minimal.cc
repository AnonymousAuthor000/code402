/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include <cstdio>
#include <iostream>
#include <sys/time.h>
// #include <time.h>
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

using namespace tflite;

extern "C" const float* forward(char* path, float *input_v) {
  const char* filename = path;
  std::cout << "TFLite model: " << filename << std::endl;
  // Load model
  // timeval t_start, t_end;
  std::unique_ptr<tflite::FlatBufferModel> model =
      tflite::FlatBufferModel::BuildFromFile(filename);
  InterpreterOptions* options_experimental = new InterpreterOptions();
  // We set it to true to show the maximal mem cost because we do not optimize the mem usage in our tool (i.e., detel intermediate tensors)
  options_experimental->SetPreserveAllTensors();  
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder builder(*model, resolver, options_experimental);
  std::unique_ptr<tflite::Interpreter> interpreter;
  builder(&interpreter);
  // gettimeofday( &t_start, NULL);
  interpreter->AllocateTensors();
  float* input = interpreter->typed_input_tensor<float>(0);
  memcpy(input, input_v, 1*224*224*3*sizeof(float)); 
  interpreter->Invoke();
  float* output = interpreter->typed_output_tensor<float>(0);

  // gettimeofday( &t_end, NULL);
  // double delta_t = (t_end.tv_sec-t_start.tv_sec) + 
  //                 (t_end.tv_usec-t_start.tv_usec)/1000000.0;
  // std::cout << "TFLite time cost: " << delta_t  << "s" << std::endl;
  // std::cout << "TFLite output: " << output[0] << std::endl;
  return output;
}