
#ifdef __cplusplus
 extern "C" {
#endif
/**
  ******************************************************************************
  * @file           : app_x-cube-ai.c
  * @brief          : AI program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "app_x-cube-ai.h"
#include "main.h"
#include "constants_ai.h"
#include "ai_datatypes_defines.h"

/* USER CODE BEGIN includes */
/* USER CODE END includes */
/* USER CODE BEGIN initandrun */
#include <stdlib.h>

/* Global handle to reference the instance of the NN */
static ai_handle imageclassify = AI_HANDLE_NULL;
static ai_buffer ai_input[AI_IMAGECLASSIFY_IN_NUM] = AI_IMAGECLASSIFY_IN ;
static ai_buffer ai_output[AI_IMAGECLASSIFY_OUT_NUM] = AI_IMAGECLASSIFY_OUT ;
static void bubblesort(float *, int *, int);

const char *g_classes[]  = {
   "T-shirt/Top", "Trouser", "Pullover", "Dress",
   "Coat", "Sandal", "Shirt", "Sneaker",
   "Bag", "Ankle Boot"};
/*
 * Init function to create and initialize a NN.
 */
int aiInit(const ai_u8* activations)
{
    ai_error err;

    /* 1 - Specific AI data structure to provide the references of the
     * activation/working memory chunk and the weights/bias parameters */
    const ai_network_params params = {
            AI_IMAGECLASSIFY_DATA_WEIGHTS(ai_imageclassify_data_weights_get()),
            AI_IMAGECLASSIFY_DATA_ACTIVATIONS(activations)
    };

    /* 2 - Create an instance of the NN */
    err = ai_imageclassify_create(&imageclassify, AI_IMAGECLASSIFY_DATA_CONFIG);
    if (err.type != AI_ERROR_NONE) {
	    return -1;
    }

    /* 3 - Initialize the NN - Ready to be used */
    if (!ai_imageclassify_init(imageclassify, &params)) {
        err = ai_imageclassify_get_error(imageclassify);
        ai_imageclassify_destroy(imageclassify);
        imageclassify = AI_HANDLE_NULL;
	    return -2;
    }

    return 0;
}

/*
 * Run function to execute an inference.
 */
int aiRun(const void *in_data, void *out_data)
{
    ai_i32 nbatch;
    ai_error err;

    /* Parameters checking */
    if (!in_data || !out_data || !imageclassify)
        return -1;

    /* Initialize input/output buffer handlers */
    ai_input[0].n_batches = 1;
    ai_input[0].data = AI_HANDLE_PTR(in_data);
    ai_output[0].n_batches = 1;
    ai_output[0].data = AI_HANDLE_PTR(out_data);

    /* 2 - Perform the inference */
    nbatch = ai_imageclassify_run(imageclassify, &ai_input[0], &ai_output[0]);
    if (nbatch != 1) {
        err = ai_imageclassify_get_error(imageclassify);
        // ...
        return err.code;
    }

    return 0;
}
/* USER CODE END initandrun */

/*************************************************************************
  *
  */
void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 0 */
    /* Activation/working buffer is allocated as a static memory chunk
     * (bss section) */
    AI_ALIGNED(4)
    static ai_u8 activations[AI_IMAGECLASSIFY_DATA_ACTIVATIONS_SIZE];

    aiInit(activations);
    /* USER CODE END 0 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 1 */
	int nb_run = 2;
    int res;
    int ranking[OUTPUT_CLASS_NUMBER];

    for(int i=0; i<OUTPUT_CLASS_NUMBER;i++) ranking[i]=i;

    /* Example of definition of the buffers to store the tensor input/output */
    /*  type is dependent of the expected format                             */
    AI_ALIGNED(4)
    static ai_i8 in_data[AI_IMAGECLASSIFY_IN_1_SIZE_BYTES];

    AI_ALIGNED(4)
    static ai_i8 out_data[AI_IMAGECLASSIFY_OUT_1_SIZE_BYTES];

    /* Retrieve format/type of the first input tensor - index 0 */
    const ai_buffer_format fmt_ = AI_BUFFER_FORMAT(&ai_input[0]);
    const uint32_t type_ = AI_BUFFER_FMT_GET_TYPE(fmt_);

    /* Perform nb_rub inferences (batch = 1) */
    while (--nb_run) {

        /* ---------------------------------------- */
        /* Data generation and Pre-Process          */
        /* ---------------------------------------- */
        for (ai_size i=0;  i < AI_IMAGECLASSIFY_IN_1_SIZE; i++ ) {

            /* Fill the input buffer with pixel data */
            float val = resizedImage[i];

            /* Convert the data if necessary */
            if (type_ == AI_BUFFER_FMT_TYPE_FLOAT) {
                ((float *)in_data)[i] = val;
            }
        }

        /* Perform the inference */
        t1=HAL_GetTick();
        res = aiRun(in_data, out_data);
        t2=HAL_GetTick();
        /* Post-Process - process the output buffer */
        if(res==0)
               {
               	bubblesort(out_data,ranking,OUTPUT_CLASS_NUMBER);
               	/* Print the classification result */
               	printf("Inference Time: %d ms\n",((t2>=t1)?(t2-t1):((1<<24)-t1+t2)));
               	printf("The Prediction is: %s",g_classes[ranking[0]]);
               	printf("\n");
               	uint8_t *ptr = g_classes[ranking[0]];
               	BSP_LCD_SetTextColor(0x07E0);
               	BSP_LCD_DisplayStringAt(0, 100, ptr , 0x01);
               }
    }
    /* USER CODE END 1 */
}

/**
  * @brief  Bubble sorting algorithm
  * @param  None
  * @retval None
  */
static void bubblesort(float *prob,int *classes, int size)
{
  float p;
  int c;

  for(int i=0; i<size; i++)
  {
    for(int ii=0; ii<size-i-1; ii++)
    {
      if(prob[ii]<prob[ii+1])
      {
        p=prob[ii];
        prob[ii]=prob[ii+1];
        prob[ii+1]=p;
        c = classes[ii];
        classes[ii]=classes[ii+1];
        classes[ii+1]=c;
      }
    }
  }
}

#ifdef __cplusplus
}
#endif
