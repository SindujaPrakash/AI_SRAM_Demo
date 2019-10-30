/**
  ******************************************************************************
  * @file    imageclassify.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Mon Oct 28 16:45:56 2019
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */



#include "imageclassify.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 4
#define AI_TOOLS_VERSION_MINOR 0
#define AI_TOOLS_VERSION_MICRO 0

#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_imageclassify
 
#undef AI_IMAGECLASSIFY_MODEL_SIGNATURE
#define AI_IMAGECLASSIFY_MODEL_SIGNATURE     "f75dc7e8bcf6dce5430471969d491fe0"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Mon Oct 28 16:45:56 2019"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_IMAGECLASSIFY_N_BATCHES
#define AI_IMAGECLASSIFY_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array dense_2_bias_array;   /* Array #0 */
AI_STATIC ai_array dense_2_weights_array;   /* Array #1 */
AI_STATIC ai_array dense_1_bias_array;   /* Array #2 */
AI_STATIC ai_array dense_1_weights_array;   /* Array #3 */
AI_STATIC ai_array input_0_output_array;   /* Array #4 */
AI_STATIC ai_array dense_1_output_array;   /* Array #6 */
AI_STATIC ai_array dense_1_nl_output_array;   /* Array #7 */
AI_STATIC ai_array dense_2_output_array;   /* Array #8 */
AI_STATIC ai_array dense_2_nl_output_array;   /* Array #9 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor dense_2_bias;   /* Tensor #0 */
AI_STATIC ai_tensor dense_2_weights;   /* Tensor #1 */
AI_STATIC ai_tensor dense_1_bias;   /* Tensor #2 */
AI_STATIC ai_tensor dense_1_weights;   /* Tensor #3 */
AI_STATIC ai_tensor input_0_output;   /* Tensor #4 */
AI_STATIC ai_tensor input_0_output0;   /* Tensor #5 */
AI_STATIC ai_tensor dense_1_output;   /* Tensor #6 */
AI_STATIC ai_tensor dense_1_nl_output;   /* Tensor #7 */
AI_STATIC ai_tensor dense_2_output;   /* Tensor #8 */
AI_STATIC ai_tensor dense_2_nl_output;   /* Tensor #9 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain dense_1_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain dense_1_nl_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain dense_2_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_2_nl_chain;   /* Chain #3 */


/**  Subgraph network operator tensor chain declarations  *********************/


/**  Subgraph network operator declarations  *********************************/


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_dense dense_1_layer; /* Layer #0 */
AI_STATIC ai_layer_nl dense_1_nl_layer; /* Layer #1 */
AI_STATIC ai_layer_dense dense_2_layer; /* Layer #2 */
AI_STATIC ai_layer_nl dense_2_nl_layer; /* Layer #3 */


/**  Array declarations section  **********************************************/
AI_ARRAY_OBJ_DECLARE(
  dense_2_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_2_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 1280,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_1_bias_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_1_weights_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 100352,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 784,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_1_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_1_nl_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 128,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_2_output_array, AI_ARRAY_FORMAT_FLOAT,
  NULL, NULL, 10,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_2_nl_output_array, AI_ARRAY_FORMAT_FLOAT|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 10,
  AI_STATIC)


/**  Tensor declarations section  *********************************************/
AI_TENSOR_OBJ_DECLARE(
  dense_2_bias,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &dense_2_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_2_weights,
  AI_SHAPE_INIT(1, 1, 10, 128),
  AI_STRIDE_INIT(5120, 5120, 512, 4),
  &dense_2_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_1_bias,
  AI_SHAPE_INIT(1, 1, 128, 1),
  AI_STRIDE_INIT(512, 512, 4, 4),
  &dense_1_bias_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_1_weights,
  AI_SHAPE_INIT(1, 1, 128, 784),
  AI_STRIDE_INIT(401408, 401408, 3136, 4),
  &dense_1_weights_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  input_0_output,
  AI_SHAPE_INIT(28, 1, 28, 1),
  AI_STRIDE_INIT(112, 112, 4, 4),
  &input_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  input_0_output0,
  AI_SHAPE_INIT(1, 1, 784, 1),
  AI_STRIDE_INIT(3136, 3136, 4, 4),
  &input_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_1_output,
  AI_SHAPE_INIT(1, 1, 128, 1),
  AI_STRIDE_INIT(512, 512, 4, 4),
  &dense_1_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_1_nl_output,
  AI_SHAPE_INIT(1, 1, 128, 1),
  AI_STRIDE_INIT(512, 512, 4, 4),
  &dense_1_nl_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_2_output,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &dense_2_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_2_nl_output,
  AI_SHAPE_INIT(1, 1, 10, 1),
  AI_STRIDE_INIT(40, 40, 4, 4),
  &dense_2_nl_output_array,
  AI_STATIC)


/**  Layer declarations section  **********************************************/



AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&input_0_output0),
  AI_TENSOR_LIST_ENTRY(&dense_1_output),
  AI_TENSOR_LIST_ENTRY(&dense_1_weights, &dense_1_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_layer, 1,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_1_nl_layer, AI_STATIC,
  .tensors = &dense_1_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_1_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_1_output),
  AI_TENSOR_LIST_ENTRY(&dense_1_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_1_nl_layer, 1,
  NL_TYPE,
  nl, forward_relu,
  &AI_NET_OBJ_INSTANCE, &dense_2_layer, AI_STATIC,
  .tensors = &dense_1_nl_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_2_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_1_nl_output),
  AI_TENSOR_LIST_ENTRY(&dense_2_output),
  AI_TENSOR_LIST_ENTRY(&dense_2_weights, &dense_2_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_2_layer, 2,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_2_nl_layer, AI_STATIC,
  .tensors = &dense_2_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_2_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_2_output),
  AI_TENSOR_LIST_ENTRY(&dense_2_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_2_nl_layer, 2,
  NL_TYPE,
  nl, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_2_nl_layer, AI_STATIC,
  .tensors = &dense_2_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 407080, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 552, 1,
                     NULL),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_IMAGECLASSIFY_IN_NUM, &input_0_output),
  AI_TENSOR_LIST_IO_ENTRY(AI_FLAG_NONE, AI_IMAGECLASSIFY_OUT_NUM, &dense_2_nl_output),
  &dense_1_layer, 0)



AI_DECLARE_STATIC
ai_bool imageclassify_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT( activations )

  {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = AI_PTR(NULL);
    input_0_output_array.data_start = AI_PTR(NULL);
    dense_1_output_array.data = AI_PTR(activations + 0);
    dense_1_output_array.data_start = AI_PTR(activations + 0);
    dense_1_nl_output_array.data = AI_PTR(activations + 0);
    dense_1_nl_output_array.data_start = AI_PTR(activations + 0);
    dense_2_output_array.data = AI_PTR(activations + 512);
    dense_2_output_array.data_start = AI_PTR(activations + 512);
    dense_2_nl_output_array.data = AI_PTR(NULL);
    dense_2_nl_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool imageclassify_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT( weights )

  {
    /* Updating weights (byte) offsets */
    dense_2_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_2_bias_array.data = AI_PTR(weights + 407040);
    dense_2_bias_array.data_start = AI_PTR(weights + 407040);
  dense_2_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_2_weights_array.data = AI_PTR(weights + 401920);
    dense_2_weights_array.data_start = AI_PTR(weights + 401920);
  dense_1_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_1_bias_array.data = AI_PTR(weights + 401408);
    dense_1_bias_array.data_start = AI_PTR(weights + 401408);
  dense_1_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_1_weights_array.data = AI_PTR(weights + 0);
    dense_1_weights_array.data_start = AI_PTR(weights + 0);
  
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_imageclassify_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_IMAGECLASSIFY_MODEL_NAME,
      .model_signature   = AI_IMAGECLASSIFY_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 101910,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_imageclassify_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_imageclassify_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_imageclassify_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_imageclassify_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= imageclassify_configure_weights(net_ctx, &params->params);
  ok &= imageclassify_configure_activations(net_ctx, &params->activations);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_imageclassify_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_imageclassify_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_IMAGECLASSIFY_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

