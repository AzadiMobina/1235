/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#define G_Pin GPIO_PIN_13
#define G_GPIO_Port GPIOC
#define E_Pin GPIO_PIN_14
#define E_GPIO_Port GPIOC
#define C_Pin GPIO_PIN_15
#define C_GPIO_Port GPIOC
#define D_Pin GPIO_PIN_0
#define D_GPIO_Port GPIOA
#define NTC_Pin GPIO_PIN_1
#define NTC_GPIO_Port GPIOA
#define Blinky_Point_Pin GPIO_PIN_4
#define Blinky_Point_GPIO_Port GPIOA
#define Date_Point_Pin GPIO_PIN_0
#define Date_Point_GPIO_Port GPIOB
#define SQW_Pin GPIO_PIN_1
#define SQW_GPIO_Port GPIOB
#define SQW_EXTI_IRQn EXTI1_IRQn
#define A_Pin GPIO_PIN_12
#define A_GPIO_Port GPIOB
#define F_Pin GPIO_PIN_13
#define F_GPIO_Port GPIOB
#define B_Pin GPIO_PIN_14
#define B_GPIO_Port GPIOB
#define Seg_1_VCC_Pin GPIO_PIN_15
#define Seg_1_VCC_GPIO_Port GPIOB
#define Seg_2_VCC_Pin GPIO_PIN_8
#define Seg_2_VCC_GPIO_Port GPIOA
#define Seg_3_VCC_Pin GPIO_PIN_9
#define Seg_3_VCC_GPIO_Port GPIOA
#define Seg_4_VCC_Pin GPIO_PIN_10
#define Seg_4_VCC_GPIO_Port GPIOA
#define Seg_5_VCC_Pin GPIO_PIN_11
#define Seg_5_VCC_GPIO_Port GPIOA
#define Seg_6_VCC_Pin GPIO_PIN_12
#define Seg_6_VCC_GPIO_Port GPIOA
#define Seg_7_VCC_Pin GPIO_PIN_15
#define Seg_7_VCC_GPIO_Port GPIOA
#define IR_Pin GPIO_PIN_3
#define IR_GPIO_Port GPIOB
#define IR_EXTI_IRQn EXTI3_IRQn
#define Buzzer_Pin GPIO_PIN_5
#define Buzzer_GPIO_Port GPIOB
#define Timer_Pin GPIO_PIN_8
#define Timer_GPIO_Port GPIOB
#define Counter_Pin GPIO_PIN_9
#define Counter_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
