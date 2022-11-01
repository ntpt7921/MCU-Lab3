/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SEG0_Pin GPIO_PIN_0
#define SEG0_GPIO_Port GPIOA
#define SEG1_Pin GPIO_PIN_1
#define SEG1_GPIO_Port GPIOA
#define SEG2_Pin GPIO_PIN_2
#define SEG2_GPIO_Port GPIOA
#define SEG3_Pin GPIO_PIN_3
#define SEG3_GPIO_Port GPIOA
#define SEG4_Pin GPIO_PIN_4
#define SEG4_GPIO_Port GPIOA
#define SEG5_Pin GPIO_PIN_5
#define SEG5_GPIO_Port GPIOA
#define SEG6_Pin GPIO_PIN_6
#define SEG6_GPIO_Port GPIOA
#define CONTROL_7SEG_0_0_Pin GPIO_PIN_7
#define CONTROL_7SEG_0_0_GPIO_Port GPIOA
#define BUTTON_MODE_SELECT_Pin GPIO_PIN_0
#define BUTTON_MODE_SELECT_GPIO_Port GPIOB
#define BUTTON_MODE_SET_Pin GPIO_PIN_1
#define BUTTON_MODE_SET_GPIO_Port GPIOB
#define BUTTON_TIME_CHANGE_Pin GPIO_PIN_2
#define BUTTON_TIME_CHANGE_GPIO_Port GPIOB
#define CONTROL_7SEG_0_1_Pin GPIO_PIN_8
#define CONTROL_7SEG_0_1_GPIO_Port GPIOA
#define CONTROL_7SEG_1_0_Pin GPIO_PIN_9
#define CONTROL_7SEG_1_0_GPIO_Port GPIOA
#define CONTROL_7SEG_1_1_Pin GPIO_PIN_10
#define CONTROL_7SEG_1_1_GPIO_Port GPIOA
#define TRAFFIC_LIGHT_0_RED_Pin GPIO_PIN_3
#define TRAFFIC_LIGHT_0_RED_GPIO_Port GPIOB
#define TRAFFIC_LIGHT_0_YELLOW_Pin GPIO_PIN_4
#define TRAFFIC_LIGHT_0_YELLOW_GPIO_Port GPIOB
#define TRAFFIC_LIGHT_0_GREEN_Pin GPIO_PIN_5
#define TRAFFIC_LIGHT_0_GREEN_GPIO_Port GPIOB
#define TRAFFIC_LIGHT_1_RED_Pin GPIO_PIN_6
#define TRAFFIC_LIGHT_1_RED_GPIO_Port GPIOB
#define TRAFFIC_LIGHT_1_YELLOW_Pin GPIO_PIN_7
#define TRAFFIC_LIGHT_1_YELLOW_GPIO_Port GPIOB
#define TRAFFIC_LIGHT_1_GREEN_Pin GPIO_PIN_8
#define TRAFFIC_LIGHT_1_GREEN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
