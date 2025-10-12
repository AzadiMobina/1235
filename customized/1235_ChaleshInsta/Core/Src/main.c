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
#include "DS3231.h"
#include "GeneralRemoote.h"
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
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim3);
  HAL_TIM_Base_Start_IT(&htim4);
  DS3231_ReadTime(&hi2c2, &time_Hour, &time_Minute, &time_Second);
  DS3231_EnableSQW1Hz(&hi2c2);
  for (int i = 0; i < 10; i++)
  {
    Segment_Set(0, i);
    Segment_Set(1, i);
    Segment_Set(2, i);
    Segment_Set(3, i);
    Segment_Set(4, i);
    Segment_Set(5, i);
    Segment_Set(6, 'N');
    HAL_Delay(200);
    HAL_GPIO_WritePin(blinky_Point, HIGH);
    HAL_GPIO_WritePin(date_Point, LOW);
  }
  Buzz(20);
  HAL_Delay(100);
  Buzz(20);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    if (work_Mode == MODE_NORMAL)
    {
      HAL_GPIO_WritePin(date_Point, LOW);
      
      if (PM_Mode)
      {
        if (time_Hour > 12)
        {
          Segment_Set(0, (time_Hour - 12) / 10);
          Segment_Set(1, (time_Hour - 12) % 10);
        }
        else
        {
          Segment_Set(0, time_Hour / 10);
          Segment_Set(1, time_Hour % 10);
        }
      }
      else
      {
        Segment_Set(0, time_Hour / 10);
        Segment_Set(1, time_Hour % 10);
      }
      Segment_Set(2, time_Minute / 10);
      Segment_Set(3, time_Minute % 10);
      Segment_Set(4, time_Second / 10);
      Segment_Set(5, time_Second % 10);
      HAL_GPIO_WritePin(blinky_Point, HIGH);
      Segment_Set(6, 'N');

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == MODE_OFF)
    {
      time_Out = 0;
      Segment_Set(0, 'N');
      Segment_Set(1, 'N');
      Segment_Set(2, 'N');
      Segment_Set(3, 'N');
      Segment_Set(4, 'N');
      Segment_Set(5, 'N');
      Segment_Set(6, 'N');

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == TIME_SETTING)
    {
      Segment_Set(6, 'N');
      if (time_Mode == SET_HOUR)
      {

        Segment_Set(2, time_Minute_t / 10);
        Segment_Set(3, time_Minute_t % 10);

        if (time_SecBit)
        {
          Segment_Set(0, timeValue / 10);
          Segment_Set(1, timeValue % 10);
        }
        else
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
        }
      }
      else if (time_Mode == SET_MIN)
      {
        Segment_Set(0, time_Hour_t / 10);
        Segment_Set(1, time_Hour_t % 10);

        if (time_SecBit)
        {
          Segment_Set(2, timeValue / 10);
          Segment_Set(3, timeValue % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == SELECT_LEVEL)
    {
      Segment_Set(0,'H');
      Segment_Set(1,'L');
      Segment_Set(2,chaleng_Level);
      Segment_Set(3,'N');
      Segment_Set(4,'N');
      Segment_Set(5,'N');
      Segment_Set(6,'N');
      HAL_GPIO_WritePin(blinky_Point, LOW);

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == SET_TARGET)
    {
      Segment_Set(0, 't');
      Segment_Set(1, 'n');
      HAL_GPIO_WritePin(blinky_Point, HIGH);
      if (time_Mode == SET_SEC)
      {

        Segment_Set(4, target_mili_Second / 10);
        Segment_Set(5, target_mili_Second % 10);

        if (time_SecBit)
        {
          Segment_Set(2, target_Second / 10);
          Segment_Set(3, target_Second % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }
      }
      else if (time_Mode == SET_MILI)
      {
        Segment_Set(2, target_Second / 10);
        Segment_Set(3, target_Second % 10);

        if (time_SecBit)
        {
          Segment_Set(4, target_mili_Second / 10);
          Segment_Set(5, target_mili_Second % 10);
        }
        else
        {
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
        }
      }
      
      Segment_Set(6, 'N');
      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == CHALENG)
    {
      time_Out = 0;
      if(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin)== GPIO_PIN_RESET)
      {
        HAL_Delay(50);
        if(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin)== GPIO_PIN_RESET)
        {
          if(timer_Run)
          {
            timer_Run = 0;
            resultCheck_Flag = 1;
          }
          else
          {
            timer_Run = 1;
          }
          Buzz(50);
        }while(HAL_GPIO_ReadPin(Timer_GPIO_Port,Timer_Pin)== GPIO_PIN_RESET);
      }

      if(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET)
      {
        HAL_Delay(50);
        if(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET)
        {
          timer_Second = 0;
          timer_mili_Second = 0;
          timer_Run = 0;
          Buzz(100);HAL_Delay(50);Buzz(100);
        }while(HAL_GPIO_ReadPin(Reset_GPIO_Port,Reset_Pin)== GPIO_PIN_RESET);
      }

      if(resultCheck_Flag)
      {
        resultCheck_Flag = 0;
        chaleng_Number =( timer_Second * 100) + timer_mili_Second;
        if(((chaleng_Number + chaleng_Level_Val) >= target_Number) && (target_Number >= (chaleng_Number - chaleng_Level_Val)))
        {
          timer_Second = target_Second;
          timer_mili_Second = target_mili_Second;
          win_Buzzer = 1;
        }
      }

      Segment_Set(0,'C');
      Segment_Set(1,'L');
      Segment_Set(2,timer_Second/10);
      Segment_Set(3,timer_Second%10);
      Segment_Set(4,timer_mili_Second/10);
      Segment_Set(5,timer_mili_Second%10);
      Segment_Set(6, 's');

      if(win_Buzzer)
      {
        win_Buzzer = 0;
        Segment_Set(0,'S');Segment_Set(1,'U');Segment_Set(2,'C');Segment_Set(3,'C');Segment_Set(4,'E');Segment_Set(5,'S');
        HAL_GPIO_WritePin(blinky_Point, LOW);
        Buzz(100);HAL_Delay(100);
       // Segment_Set(0,'N');Segment_Set(1,'N');Segment_Set(2,timer_Second/10);Segment_Set(3,timer_Second%10);Segment_Set(4,timer_mili_Second/10);Segment_Set(5,timer_mili_Second%10);
        Buzz(100);HAL_Delay(100);
        //Segment_Set(0,'S');Segment_Set(1,'U');Segment_Set(2,'C');Segment_Set(3,'C');Segment_Set(4,'E');Segment_Set(5,'S');
        Buzz(100);HAL_Delay(100);
        //Segment_Set(0,'N');Segment_Set(1,'N');Segment_Set(2,timer_Second/10);Segment_Set(3,timer_Second%10);Segment_Set(4,timer_mili_Second/10);Segment_Set(5,timer_mili_Second%10);
        Buzz(100);HAL_Delay(100);
        //Segment_Set(0,'S');Segment_Set(1,'U');Segment_Set(2,'C');Segment_Set(3,'C');Segment_Set(4,'E');Segment_Set(5,'S');
        Buzz(100);HAL_Delay(100);
        //Segment_Set(0,'N');Segment_Set(1,'N');Segment_Set(2,timer_Second/10);Segment_Set(3,timer_Second%10);Segment_Set(4,timer_mili_Second/10);Segment_Set(5,timer_mili_Second%10);
        Buzz(100);HAL_Delay(100);
        //Segment_Set(0,'S');Segment_Set(1,'U');Segment_Set(2,'C');Segment_Set(3,'C');Segment_Set(4,'E');Segment_Set(5,'S');
        HAL_Delay(400);
        HAL_GPIO_WritePin(blinky_Point, HIGH);
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
      
    }
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
  if (++time_Second > 59)
  {
    time_Second = 0;
    if (++time_Minute > 59)
    {
      time_Minute = 0;

      if (++time_Hour > 23)
        time_Hour = 0;
    }
  }
  
  if (time_SecBit)
    time_SecBit = 0;
  else
    time_SecBit = 1;

  if (++time_Out > 90)
  {
    time_Out = 0;
    if (work_Mode != MODE_NORMAL)
    {
      DS3231_ReadTime(&hi2c2, &time_Hour, &time_Minute, &time_Second);
      work_Mode = MODE_NORMAL;
      // Buzz(50);
    }
  }
}

void Chaleng_Timer(void)
{
  if(timer_Run ==1)
  {
    if(++ timer_mili_Second > 99)
    {
      timer_mili_Second = 0;
      if(++timer_Second > 99)
        timer_Second = 0;
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
