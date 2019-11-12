/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define X_resize_Width				   28
#define Y_Resize_Height				   28
uint32_t t1;
uint32_t t2;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern I2C_HandleTypeDef hi2c2;
extern uint8_t resizedImage[28*28];
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void SCCB_GPIO_Config(void);
uint8_t DCMI_SingleRandomWrite(uint8_t DeviceAddr, uint16_t Reg, uint8_t Data);
uint8_t DCMI_SingleRandomRead(uint8_t DeviceAddr, uint16_t Reg,uint8_t *Data);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define A23_Pin GPIO_PIN_2
#define A23_GPIO_Port GPIOE
#define BL_PWM_Pin GPIO_PIN_7
#define BL_PWM_GPIO_Port GPIOF
#define Push_button_Pin GPIO_PIN_0
#define Push_button_GPIO_Port GPIOA
#define I2C_SIOC_Pin GPIO_PIN_10
#define I2C_SIOC_GPIO_Port GPIOB
#define I2C_SIOD_Pin GPIO_PIN_11
#define I2C_SIOD_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_12
#define LCD_CS_GPIO_Port GPIOG
#define A24_Pin GPIO_PIN_13
#define A24_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_PORT GPIOH
#define LED_Pin_Capture GPIO_PIN_3
#define LED_Pin_Inference GPIO_PIN_0
#define LED1_GPIO_PORT GPIOI
#define LED_Pin_Ready GPIO_PIN_10
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
