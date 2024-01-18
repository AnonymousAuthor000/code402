#include <stddef.h>
// #include <stdint.h>

#include "tensorflow/lite/c/builtin_op_data.h"
#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/kernels/internal/compatibility.h"
// #include "tensorflow/lite/kernels/internal/optimized/cpu_check.h"
// #include "tensorflow/lite/kernels/internal/optimized/neon_check.h"
#include "tensorflow/lite/kernels/internal/optimized/optimized_ops.h"
// #include "tensorflow/lite/kernels/internal/quantization_util.h"
#include "tensorflow/lite/kernels/internal/reference/process_broadcast_shapes.h"
#include "tensorflow/lite/kernels/internal/reference/reference_ops.h"
#include "tensorflow/lite/kernels/internal/tensor.h"
#include "tensorflow/lite/kernels/internal/tensor_ctypes.h"
#include "tensorflow/lite/kernels/internal/types.h"
#include "tensorflow/lite/kernels/kernel_util.h"
using namespace tflite;
namespace randomname {

const TfLiteFusedActivation activation=;

const int input_0_dims_size=;
const int32_t input_0_dims_raw=;

input_0_raw=;
input_v_0=input_0_raw;

const int input_1_dims_size=;
const int32_t input_1_dims_raw=;

input_1_raw=;
input_v_1=input_1_raw;


const int output_dims_size=;
const int32_t output_dims_raw=;
const int32_t output_num=;
const float scale_output=;
const int32_t zero_point_output=;
const TfLiteType output_type=;



auto* randomname(auguments_placeholder) {

  // float* output_data = new float[output_num];
  float* output_data = (float*)malloc(sizeof(float) * output_num);


  tflite::ArithmeticParams op_params;
  float output_activation_min, output_activation_max;
  const bool need_broadcast = optimized_ops::ProcessBroadcastShapes(
      RuntimeShape(input_0_dims_size, input_0_dims_raw), RuntimeShape(input_1_dims_size, input_1_dims_raw), &op_params);
  CalculateActivationRange(activation, &output_activation_min,
                           &output_activation_max);
  SetActivationParams(output_activation_min, output_activation_max,
                      &op_params);

  if (need_broadcast) {
    optimized_ops::BroadcastDivSlow(op_params, RuntimeShape(input_0_dims_size, input_0_dims_raw),                        \
              input_v_0, RuntimeShape(input_1_dims_size, input_1_dims_raw), \
              input_v_1, RuntimeShape(output_dims_size, output_dims_raw), \
              output_data);
  } else {
    optimized_ops::Div(op_params, RuntimeShape(input_0_dims_size, input_0_dims_raw),                        \
              input_v_0, RuntimeShape(input_1_dims_size, input_1_dims_raw), \
              input_v_1, RuntimeShape(output_dims_size, output_dims_raw), \
              output_data);;
  }
  // tflite::ArithmeticParams op_params;
  // const bool need_broadcast = optimized_ops::ProcessBroadcastShapes(
  //     RuntimeShape(input_0_dims_size, input_0_dims_raw), RuntimeShape(input_1_dims_size, input_1_dims_raw), &op_params);
  // float output_activation_min, output_activation_max;
  // CalculateActivationRange(activation, &output_activation_min,   \
  //                          &output_activation_max);                      \
  // SetActivationParams(output_activation_min, output_activation_max,      \
  //                     &op_params);

  // if (need_broadcast) {
  //   optimized_ops::BroadcastMulDispatch(op_params, RuntimeShape(input_0_dims_size, input_0_dims_raw),                        \
  //             input_v_0, RuntimeShape(input_1_dims_size, input_1_dims_raw), \
  //             input_v_1, RuntimeShape(output_dims_size, output_dims_raw), \
  //             output_data);
  // } else {
  //   optimized_ops::Mul(op_params, RuntimeShape(input_0_dims_size, input_0_dims_raw),                        \
  //             input_v_0, RuntimeShape(input_1_dims_size, input_1_dims_raw), \
  //             input_v_1, RuntimeShape(output_dims_size, output_dims_raw), \
  //             output_data);;
  // }

  return output_data;
}
}  // namespace randomname