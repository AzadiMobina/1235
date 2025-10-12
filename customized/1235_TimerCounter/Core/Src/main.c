/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SegmentsDriver.h"
#include "Variable.h"
#include "Initialization.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  for (int i = 0; i < 10; i++)
  {
    Segment_Set(0,i);
    Segment_Set(1,i);
    Segment_Set(2,i);
    Segment_Set(3,i);
    Segment_Set(4,i);
    Segment_Set(5,i);
    Segment_Set(6,'N');
    HAL_Delay(200);
    HAL_GPIO_WritePin(blinky_Point,HIGH);
    HAL_GPIO_WritePin(date_Point,LOW);
  }
  Buzz(20);
  HAL_Delay(100);
  Buzz(20);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if(HAL_GPIO_ReadPin(Counter_GPIO_Port,Counter_Pin) == GPIO_PIN_RESET)
    {
      HAL_Delay(50);
      if(HAL_GPIO_ReadPin(Counter_GPIO_Port,Counter_Pin)== GPIO_PIN_RESET)
      {
        Counter_Value++;
        if(Counter_Value > 999999)
        {
          Counter_Value = 0;
        }
        Buzz(50);
      }while(HAL_GPIO_ReadPin(Counter_GPIO_Port,Counter_Pin) == GPIO_PIN_RESET);
    }

    if(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin)== GPIO_PIN_RESET)
    {
      HAL_Delay(50);
      if(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin)== GPIO_PIN_RESET)
      {
        timer_Run = !timer_Run;
        Buzz(50);
      }while(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin) == GPIO_PIN_RESET);
    }

    if(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET)
    {
      HAL_Delay(50);
      if(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET)
      {
        Counter_Value = 0;
        time_Second = 0;
        time_mili_Second = 0;
        timer_Run = 0;
        Buzz(100);HAL_Delay(50);Buzz(100);
      }while(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET);
    }
    
    if(timer_Run)
    {
      if(++time_mili_Second > 99)
        time_mili_Second = 0;
        
      HAL_Delay(8);
    }

    Segment_Set(0,time_Second/10);
    Segment_Set(1,time_Second%10);
    Segment_Set(2,time_mili_Second/10);
    Segment_Set(3,time_mili_Second%10);
    Segment_Set(4,(Counter_Value/10));
    Segment_Set(5,Counter_Value%10);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void Time_Update(void)
{
  if(timer_Run)
  {
    time_mili_Second = 0;
    if(++time_Second > 99)
    {
      time_Second = 0;
    }
  }

  
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
