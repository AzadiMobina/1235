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
#include "NTC.h"

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
  
  #ifdef EDAR
    for(int i = 0; i< 8; i++)
    {
      dateOfWeek = GET_DOW(i);
      Segment_Set(6,dateOfWeek);
      HAL_Delay(200);
    }
    dateOfWeek = GET_DOW(date_Week);
    Date_Update();
  #endif
  Buzz(20);
  HAL_Delay(100);
  Buzz(20);

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
#ifdef SIMPLE
    if (work_Mode == MODE_NORMAL)
    {

      HAL_GPIO_WritePin(date_Point, LOW);
      if (tmpShow)
      {
        if (time_TmpShow < 2)
        {
          if (tempreture_read == 0)
          {
            temperature = NTC_Read();
            tempreture_read = 1;
          }
          if (tempreture_read == 1)
          {
            Segment_Set(0, temperature / 10);
            Segment_Set(1, temperature % 10);
            Segment_Set(2, 'o');
            Segment_Set(3, 'C');
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
            HAL_GPIO_WritePin(blinky_Point, LOW);
          }
        }
        else
        {
          tempreture_read = 0;
        }
      }
      if (!tempreture_read)
      {
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
      }
      Segment_Set(6, 'N');

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == MODE_OFF)
    {
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

#elif EDARI
    if (work_Mode == MODE_NORMAL)
    {
      Segment_Set(6, dateOfWeek);
      if ((time_DateShow > 10) && (time_DateShow < 14))
      {
        date_Read = 1;
        // Date_Update();
        Segment_Set(0, jdate_Year / 10);
        Segment_Set(1, jdate_Year % 10);
        Segment_Set(2, jdate_Mounth / 10);
        Segment_Set(3, jdate_Mounth % 10);
        Segment_Set(4, jdate_Day / 10);
        Segment_Set(5, jdate_Day % 10);
        HAL_GPIO_WritePin(blinky_Point, LOW);
        HAL_GPIO_WritePin(date_Point, HIGH);
      }
      else
      {
        date_Read = 0;
      }

      if (tmpShow)
      {
        if (time_TmpShow < 2)
        {
          if (tempreture_read == 0)
          {
            temperature = NTC_Read();
            tempreture_read = 1;
          }

          Segment_Set(0, temperature / 10);
          Segment_Set(1, temperature % 10);
          Segment_Set(2, 'o');
          Segment_Set(3, 'C');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
          HAL_GPIO_WritePin(blinky_Point, LOW);
          HAL_GPIO_WritePin(date_Point, LOW);
        }
        else
        {
          tempreture_read = 0;
        }
      }

      if (!tempreture_read && !date_Read)
      {
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
        HAL_GPIO_WritePin(date_Point, LOW);
        HAL_GPIO_WritePin(blinky_Point, HIGH);
      }
      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == MODE_OFF)
    {
      Segment_Set(0, 'N');
      Segment_Set(1, 'N');
      Segment_Set(2, 'N');
      Segment_Set(3, 'N');
      Segment_Set(4, 'N');
      Segment_Set(5, 'N');
      Segment_Set(6, 'N');
      HAL_GPIO_WritePin(blinky_Point, LOW);
      HAL_GPIO_WritePin(date_Point, LOW);
      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == TIME_SETTING)
    {
      HAL_GPIO_WritePin(blinky_Point, HIGH);
      HAL_GPIO_WritePin(date_Point, LOW);

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
    else if (work_Mode == DATE_SETTING)
    {
      HAL_GPIO_WritePin(blinky_Point, LOW);

      if (date_Mode == SET_YEAR)
      {
        HAL_GPIO_WritePin(date_Point, HIGH);
        Segment_Set(2, dateMounth_t / 10);
        Segment_Set(3, dateMounth_t % 10);
        Segment_Set(4, dateDay_t / 10);
        Segment_Set(5, dateDay_t % 10);
        if (time_SecBit)
        {
          Segment_Set(0, dateValue / 10);
          Segment_Set(1, dateValue % 10);
        }
        else
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
        }
      }
      else if (date_Mode == SET_MOTH)
      {
        HAL_GPIO_WritePin(date_Point, HIGH);
        Segment_Set(0, dateYear_t / 10);
        Segment_Set(1, dateYear_t % 10);

        Segment_Set(4, dateDay_t / 10);
        Segment_Set(5, dateDay_t % 10);
        if (time_SecBit)
        {
          Segment_Set(2, dateValue / 10);
          Segment_Set(3, dateValue % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }
      }
      else if (date_Mode == SET_DAY)
      {
        HAL_GPIO_WritePin(date_Point, HIGH);
        Segment_Set(0, dateYear_t / 10);
        Segment_Set(1, dateYear_t % 10);
        Segment_Set(2, dateMounth_t / 10);
        Segment_Set(3, dateMounth_t % 10);
        if (time_SecBit)
        {
          Segment_Set(4, dateValue / 10);
          Segment_Set(5, dateValue % 10);
        }
        else
        {
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
        }
      }
      else if (date_Mode == SET_DOW)
      {
        HAL_GPIO_WritePin(date_Point, LOW);
        Segment_Set(0, 'N');
        Segment_Set(1, 'N');
        Segment_Set(2, 'N');
        Segment_Set(3, 'N');
        if (time_SecBit)
        {
          Segment_Set(4, dateValue / 10);
          Segment_Set(5, dateValue % 10);
        }
        else
        {
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }

#elif BASHGHAHI

    if (work_Mode == MODE_NORMAL)
    {
      if (time_TmpShow < 2)
      {
        if (tmpShow)
        {
          if (temp_Read)
          {
            temperature = NTC_Read();
            temp_Read = 0;
          }
          HAL_GPIO_WritePin(blinky_Point, LOW);
          Segment_Set(0, temperature / 10);
          Segment_Set(1, temperature % 10);
          Segment_Set(2, 'o');
          Segment_Set(3, 'C');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
        }
      }
      else
      {
        temp_Read = 1;
        HAL_GPIO_WritePin(blinky_Point, HIGH);
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
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }

    else if (work_Mode == MODE_OFF)
    {
      Segment_Set(0, 'N');
      Segment_Set(1, 'N');
      Segment_Set(2, 'N');
      Segment_Set(3, 'N');
      Segment_Set(4, 'N');
      Segment_Set(5, 'N');
      // Segment_Set(6,'N');
      HAL_GPIO_WritePin(blinky_Point, LOW);
      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }

    else if (work_Mode == TIME_SETTING)
    {
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
    /*
    else if(work_Mode == DATE_SETTING)
    {
      HAL_GPIO_WritePin(blinky_Point,LOW);
      HAL_GPIO_WritePin(date_Point,HIGH);
      if(date_Mode == SET_YEAR)
      {
        Segment_Set(2,dateMounth_t/10);
        Segment_Set(3,dateMounth_t%10);
        Segment_Set(4,dateDay_t/10);
        Segment_Set(5,dateDay_t%10);
        if(time_SecBit)
        {
          Segment_Set(0,dateValue/10);
          Segment_Set(1,dateValue%10);
        }
        else
        {
          Segment_Set(0,'N');
          Segment_Set(1,'N');
        }
      }
      else if(date_Mode == SET_MOTH)
      {
        Segment_Set(0,dateYear_t/10);
        Segment_Set(1,dateYear_t%10);

        Segment_Set(4,dateDay_t/10);
        Segment_Set(5,dateDay_t%10);
        if(time_SecBit)
        {
          Segment_Set(2,dateValue/10);
          Segment_Set(3,dateValue%10);
        }
        else
        {
          Segment_Set(2,'N');
          Segment_Set(3,'N');
        }
      }
      else if(date_Mode == SET_DAY)
      {
        Segment_Set(0,dateYear_t/10);
        Segment_Set(1,dateYear_t%10);
        Segment_Set(2,dateMounth_t/10);
        Segment_Set(3,dateMounth_t%10);
        if(time_SecBit)
        {
          Segment_Set(4,dateValue/10);
          Segment_Set(5,dateValue%10);
        }
        else
        {
          Segment_Set(4,'N');
          Segment_Set(5,'N');
        }
      }
      else if(date_Mode == SET_DOW)
      {
        Segment_Set(0,dateYear_t/10);
        Segment_Set(1,dateYear_t%10);
        Segment_Set(2,dateMounth_t/10);
        Segment_Set(3,dateMounth_t%10);
        Segment_Set(4,dateDay_t/10);
        Segment_Set(5,dateDay_t%10);

        if(time_SecBit)
        {
          Segment_Set(6,GET_DOW(dateValue));
        }
        else
        {
          Segment_Set(6,'N');
        }

      }

      irRemote = Ir_GetData();
      if(irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    */
    else if (work_Mode == UP_TIMER)
    {
      if (timer_Mode == SETTING)
      {
        Segment_Set(0, 'U');
        Segment_Set(1, 'P');
        Segment_Set(4, upTime_Second / 10);
        Segment_Set(5, upTime_Second % 10);
        if (time_SecBit)
        {
          Segment_Set(2, timer_Value / 10);
          Segment_Set(3, timer_Value % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (timer_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (timer_StartUp)
        {
          HAL_GPIO_WritePin(blinky_Point, LOW);
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, timer_TimeStarting / 10);
          Segment_Set(5, timer_TimeStarting % 10);
        }
        else
        {
          HAL_GPIO_WritePin(blinky_Point, HIGH);
          Segment_Set(0, 'U');
          Segment_Set(1, 'P');
          Segment_Set(2, upTime_Minute / 10);
          Segment_Set(3, upTime_Minute % 10);
          Segment_Set(4, upTime_Second / 10);
          Segment_Set(5, upTime_Second % 10);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (timer_Run == 1)
          {
            if (timer_SrUpEn)
            {
              timer_StartUp = 1;
              timer_TimeStarting--;

              if (timer_TimeStarting < 4)
                Buzz(100);
              if (timer_TimeStarting < 1)
              {
                timer_SrUpEn = 0;
                timer_StartUp = 0;
                upTime_Minute = 0;
                upTime_Second = 0;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            else
            {
              if (++upTime_Second > 59)
              {
                upTime_Second = 0;
                upTime_Minute++;
                if (upTime_Minute == upTime_Minute_Defult)
                {
                  upTime_Minute = upTime_Minute_Defult;
                  upTime_Second = 0;
                  timer_Run = 0;
                  timer_SrUpEn = 1;
                  timer_TimeStarting = 11;
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                }
              }
            }
          }
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }

    else if (work_Mode == DN_TIMER)
    {
      if (timer_Mode == SETTING)
      {
        Segment_Set(0, 'd');
        Segment_Set(1, 'n');
        Segment_Set(4, dnTime_Second / 10);
        Segment_Set(5, dnTime_Second % 10);
        if (time_SecBit)
        {
          Segment_Set(2, timer_Value / 10);
          Segment_Set(3, timer_Value % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (timer_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (timer_StartUp)
        {
          HAL_GPIO_WritePin(blinky_Point, LOW);
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, timer_TimeStarting / 10);
          Segment_Set(5, timer_TimeStarting % 10);
        }
        else
        {
          HAL_GPIO_WritePin(blinky_Point, HIGH);
          Segment_Set(0, 'd');
          Segment_Set(1, 'n');
          Segment_Set(2, dnTime_Minute / 10);
          Segment_Set(3, dnTime_Minute % 10);
          Segment_Set(4, dnTime_Second / 10);
          Segment_Set(5, dnTime_Second % 10);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (timer_Run == 1)
          {
            if (timer_SrUpEn)
            {
              timer_StartUp = 1;
              timer_TimeStarting--;

              if (timer_TimeStarting < 4)
                Buzz(100);
              if (timer_TimeStarting < 1)
              {
                timer_SrUpEn = 0;
                timer_StartUp = 0;
                dnTime_Minute = dnTime_Minute_Defult;
                dnTime_Second = 0;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            else
            {
              if (dnTime_Second <= 0)
              {
                dnTime_Second = 59;
                dnTime_Minute--;
                if (dnTime_Minute < 0)
                {
                  dnTime_Minute = dnTime_Minute_Defult;
                  dnTime_Second = 0;
                  timer_Run = 0;
                  timer_SrUpEn = 1;
                  timer_TimeStarting = 11;
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                }
              }
              else
                dnTime_Second--;
            }
          }
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
#elif CROSS
    if (work_Mode == MODE_NORMAL)
    {
      HAL_GPIO_WritePin(date_Point, LOW);
      if (tmpShow)
      {
        if (time_TmpShow < 2)
        {
          if (tempreture_read == 0)
          {
            temperature = NTC_Read();
            tempreture_read = 1;
          }
          if (tempreture_read == 1)
          {
            Segment_Set(0, temperature / 10);
            Segment_Set(1, temperature % 10);
            Segment_Set(2, 'o');
            Segment_Set(3, 'C');
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
            HAL_GPIO_WritePin(blinky_Point, LOW);
          }
        }
        else
        {
          tempreture_read = 0;
        }
      }
      if (!tempreture_read)
      {
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
      }
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
    else if (work_Mode == MENU)
    {
      Segment_Set(0, 'f');
      Segment_Set(1, Condition);
      Segment_Set(2, 'N');
      Segment_Set(3, 'N');
      Segment_Set(4, 'N');
      Segment_Set(5, 'N');
      Segment_Set(6, 'N');
      HAL_GPIO_WritePin(blinky_Point, LOW);
      
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
    else if (work_Mode == UP_TIMER)
    {
      Segment_Set(6, 'S');
      if (timer_Mode == SETTING)
      {
        Segment_Set(0, 'U');
        Segment_Set(1, 'P');
        Segment_Set(4, upTime_Second / 10);
        Segment_Set(5, upTime_Second % 10);
        if (time_SecBit)
        {
          Segment_Set(2, timer_Value / 10);
          Segment_Set(3, timer_Value % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }

      else if (timer_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (timer_StartUp)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, timer_TimeStarting / 10);
          Segment_Set(5, timer_TimeStarting % 10);
          HAL_GPIO_WritePin(blinky_Point, LOW);
        }
        else
        {
          Segment_Set(0, 'U');
          Segment_Set(1, 'P');
          Segment_Set(2, upTime_Minute / 10);
          Segment_Set(3, upTime_Minute % 10);
          Segment_Set(4, upTime_Second / 10);
          Segment_Set(5, upTime_Second % 10);
          HAL_GPIO_WritePin(blinky_Point, HIGH);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if ((timer_Run == 1) || (mix_Flag))
          {
            if (mix_Flag)
            {
              mix_Flag = 0;
              mix_Runnig = 1;
              timer_Run = 1;
              timer_SrUpEn = 1;
              timer_TimeStarting = 11;
            }
            if (timer_SrUpEn)
            {
              timer_StartUp = 1;
              timer_TimeStarting--;

              if (timer_TimeStarting < 4)
                Buzz(100);
              if (timer_TimeStarting < 1)
              {
                timer_SrUpEn = 0;
                timer_StartUp = 0;
                upTime_Minute = 0;
                upTime_Second = 0;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            else
            {
              if (++upTime_Second > 59)
              {
                upTime_Second = 0;
                upTime_Minute++;
                if (upTime_Minute == upTime_Minute_Defult)
                {
                  upTime_Minute = 0;
                  upTime_Second = 0;
                  timer_Run = 0;
                  if (mix_Runnig)
                  {
                    work_Mode = MIX;
                    mix_Runnig = 0;
                  }
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                }
              }
            }
          }
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == DN_TIMER)
    {
      Segment_Set(6, 'u');
      if (timer_Mode == SETTING)
      {
        Segment_Set(0, 'd');
        Segment_Set(1, 'n');
        Segment_Set(4, dnTime_Second / 10);
        Segment_Set(5, dnTime_Second % 10);
        if (time_SecBit)
        {
          Segment_Set(2, timer_Value / 10);
          Segment_Set(3, timer_Value % 10);
        }
        else
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }

      else if (timer_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (timer_StartUp)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, timer_TimeStarting / 10);
          Segment_Set(5, timer_TimeStarting % 10);
          HAL_GPIO_WritePin(blinky_Point, LOW);
        }
        else
        {
          Segment_Set(0, 'd');
          Segment_Set(1, 'n');
          Segment_Set(2, dnTime_Minute / 10);
          Segment_Set(3, dnTime_Minute % 10);
          Segment_Set(4, dnTime_Second / 10);
          Segment_Set(5, dnTime_Second % 10);
          HAL_GPIO_WritePin(blinky_Point, HIGH);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (timer_Run || mix_Flag)
          {
            if (mix_Flag)
            {
              mix_Flag = 0;
              mix_Runnig = 1;
              timer_Run = 1;
              timer_SrUpEn = 1;
              timer_TimeStarting = 11;
            }
            if (timer_SrUpEn)
            {
              timer_StartUp = 1;
              timer_TimeStarting--;

              if (timer_TimeStarting < 4)
                Buzz(100);
              if (timer_TimeStarting < 1)
              {
                timer_SrUpEn = 0;
                timer_StartUp = 0;
                dnTime_Minute = dnTime_Minute_Defult;
                dnTime_Second = 0;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            else
            {
              dnTime_Second--;
              if (dnTime_Second < 0)
              {
                dnTime_Second = 59;
                dnTime_Minute--;
                if (dnTime_Minute < 0)
                {
                  dnTime_Minute = dnTime_Minute_Defult;
                  dnTime_Second = 0;
                  timer_Run = 0;
                  if (mix_Runnig)
                  {
                    mix_Runnig = 0;
                    work_Mode = MIX;
                  }
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                  HAL_Delay(100);
                  Buzz(100);
                }
              }
            }
          }
        }
      }

      irRemote = Ir_GetData();
      if (irRemote != 0)
      {
        Haamin_Remote(irRemote, work_Mode);
      }
    }
    else if (work_Mode == TABATA)
    {
      Segment_Set(6, 'M');
      if (cross_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (cross_StartUp)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, cross_TimeStarting / 10);
          Segment_Set(5, cross_TimeStarting % 10);
          HAL_GPIO_WritePin(blinky_Point, LOW);
        }
        else
        {
          Segment_Set(0, tabata_Round / 10);
          Segment_Set(1, tabata_Round % 10);
          Segment_Set(2, tabata_Act / 10);
          Segment_Set(3, tabata_Act % 10);
          Segment_Set(4, tabata_Rest / 10);
          Segment_Set(5, tabata_Rest % 10);
          HAL_GPIO_WritePin(blinky_Point, HIGH);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (cross_Run || mix_Flag)
          {
            if (mix_Flag)
            {
              mix_Flag = 0;
              mix_Runnig = 1;
              cross_Run = 1;
              cross_SrUpEn = 1;
              cross_TimeStarting = 11;
            }
            if (cross_SrUpEn)
            {
              cross_StartUp = 1;
              cross_TimeStarting--;
              if (cross_TimeStarting < 4)
                Buzz(100);
              if (cross_TimeStarting < 1)
              {
                cross_TimeStarting = 11;
                cross_StartUp = 0;
                cross_SrUpEn = 0;
                tabata_Mode = ACT;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            if (tabata_Mode == ACT)
            {
              tabata_Act--;
              if (tabata_Act < 1)
              {
                tabata_Mode = REST;
                tabata_Act = tabata_Act_Def;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            else if (tabata_Mode == REST)
            {
              tabata_Rest--;
              if (tabata_Rest < 4)
                Buzz(100);
              if (tabata_Rest < 1)
              {
                tabata_Mode = ACT;
                tabata_Rest = tabata_Rest_Def;
                tabata_Round--;
                Buzz(300);
              }
            }
            if (tabata_Round < 1)
            {
              tabata_Mode = 1;
              tabata_Round = tabata_Round_Def;
              tabata_Act = tabata_Act_Def;
              tabata_Rest = tabata_Rest_Def;
              cross_Run = 0;
              cross_SrUpEn = 1;
              if (mix_Runnig)
              {
                mix_Runnig = 0;
                work_Mode = MIX;
              }
              Buzz(100);
              HAL_Delay(150);
              Buzz(100);
              HAL_Delay(150);
              Buzz(100);
            }
          }
        }
        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (cross_Mode == SETTING)
      {
        time_Out = 0;
        HAL_GPIO_WritePin(blinky_Point, LOW);
        if (tabata_Mode == ROUND)
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
          if (time_SecBit)
          {
            Segment_Set(0, cross_Value / 10);
            Segment_Set(1, cross_Value % 10);
          }
          else
          {
            Segment_Set(0, 'N');
            Segment_Set(1, 'N');
          }

          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }

        else if (tabata_Mode == ACT)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
          if (time_SecBit)
          {
            Segment_Set(2, cross_Value / 10);
            Segment_Set(3, cross_Value % 10);
          }
          else
          {
            Segment_Set(2, 'N');
            Segment_Set(3, 'N');
          }

          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }

        else if (tabata_Mode == REST)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          if (time_SecBit)
          {
            Segment_Set(4, cross_Value / 10);
            Segment_Set(5, cross_Value % 10);
          }
          else
          {
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
          }

          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }
      }
    }
    else if (work_Mode == EMOM)
    {
      Segment_Set(6, 'T');
      if (cross_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (cross_StartUp)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, cross_TimeStarting / 10);
          Segment_Set(5, cross_TimeStarting % 10);
          HAL_GPIO_WritePin(blinky_Point, LOW);
        }
        else
        {
          Segment_Set(0, emom_Round / 10);
          Segment_Set(1, emom_Round % 10);
          Segment_Set(2, emom_Time / 10);
          Segment_Set(3, emom_Time % 10);
          Segment_Set(4, emom_Act / 10);
          Segment_Set(5, emom_Act % 10);
          HAL_GPIO_WritePin(blinky_Point, HIGH);
        }

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (cross_Run || mix_Flag)
          {
            if (mix_Flag)
            {
              mix_Flag = 0;
              mix_Runnig = 1;
              cross_Run = 1;
              cross_SrUpEn = 1;
              cross_TimeStarting = 11;
            }
            if (cross_SrUpEn)
            {
              cross_StartUp = 1;
              cross_TimeStarting--;
              if (cross_TimeStarting < 4)
                Buzz(100);
              if (cross_TimeStarting < 1)
              {
                cross_TimeStarting = 11;
                cross_StartUp = 0;
                cross_SrUpEn = 0;
                emom_Mode = ACT;
                emom_Time_tmp = emom_Time * 60;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            if (emom_Mode == ACT)
            {
              emom_Time_tmp--;
              emom_Act--;
              if (emom_Time_tmp % 60 == 0)
                emom_Time--;
              if (emom_Act < 4)
                Buzz(100);
              if (emom_Act < 1)
              {
                tabata_Mode = REST;
                emom_Act = emom_Act_Def;
                emom_Round--;
                Buzz(100);
              }
            }

            if (emom_Round < 1)
            {
              emom_Mode = 1;
              emom_Round = emom_Round_Def;
              emom_Act = emom_Act_Def;
              emom_Time = emom_Time_Def;
              emom_Time_tmp = (emom_Time * 60);
              cross_Run = 0;
              cross_SrUpEn = 1;
              cross_TimeStarting = 11;
              if (mix_Runnig)
              {
                mix_Runnig = 0;
                work_Mode = MIX;
              }
              Buzz(100);
              HAL_Delay(150);
              Buzz(100);
              HAL_Delay(150);
              Buzz(100);
            }
          }
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (cross_Mode == SETTING)
      {
        time_Out = 0;
        HAL_GPIO_WritePin(blinky_Point, LOW);
        if (emom_Mode == ROUND)
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
          if (time_SecBit)
          {
            Segment_Set(0, cross_Value / 10);
            Segment_Set(1, cross_Value % 10);
          }
          else
          {
            Segment_Set(0, 'N');
            Segment_Set(1, 'N');
          }

          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }

        else if (emom_Mode == ACT)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');
          if (time_SecBit)
          {
            Segment_Set(2, cross_Value / 10);
            Segment_Set(3, cross_Value % 10);
          }
          else
          {
            Segment_Set(2, 'N');
            Segment_Set(3, 'N');
          }

          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }
      }
    }
    else if (work_Mode == AMRAP)
    {
      Segment_Set(6, 'W');
      if (cross_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        if (cross_StartUp)
        {
          Segment_Set(0, 'N');
          Segment_Set(1, 'N');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          Segment_Set(4, cross_TimeStarting / 10);
          Segment_Set(5, cross_TimeStarting % 10);
          HAL_GPIO_WritePin(blinky_Point, LOW);
        }
        else
        {
          Segment_Set(0, 'A');
          Segment_Set(1, 'r');
          Segment_Set(2, amrap_Minute / 10);
          Segment_Set(3, amrap_Minute % 10);
          Segment_Set(4, amrap_Second / 10);
          Segment_Set(5, amrap_Second % 10);
          HAL_GPIO_WritePin(blinky_Point, HIGH);
        }
        if (time_SecBit)
        {
          time_SecBit = 0;
          if (cross_Run || mix_Flag)
          {
            if (mix_Flag)
            {
              mix_Flag = 0;
              mix_Runnig = 1;
              cross_Run = 1;
              cross_SrUpEn = 1;
              cross_TimeStarting = 11;
              amrap_Minute = amrap_Minute_Def;
              amrap_Second = amrap_Second_Def;
            }
            if (cross_SrUpEn)
            {
              cross_StartUp = 1;
              cross_TimeStarting--;
              if (cross_TimeStarting < 4)
                Buzz(100);
              if (cross_TimeStarting < 1)
              {
                cross_TimeStarting = 11;
                cross_StartUp = 0;
                cross_SrUpEn = 0;
                amrap_Act = 1;
                Buzz(100);
                HAL_Delay(100);
                Buzz(100);
              }
            }
            if (amrap_Act)
            {
              amrap_Second--;
              if (amrap_Second == 0)
              {
                amrap_Second = 59;
                amrap_Minute--;
                if (amrap_Minute < 0)
                {
                  amrap_Minute = amrap_Minute_Def;
                  amrap_Second = amrap_Second_Def;
                  cross_Run = 0;
                  cross_SrUpEn = 1;
                  cross_TimeStarting = 11;
                  amrap_Act = 0;
                  if (mix_Runnig)
                  {
                    mix_Runnig = 0;
                    work_Mode = MIX;
                  }
                  Buzz(100);
                  HAL_Delay(150);
                  Buzz(100);
                  HAL_Delay(150);
                  Buzz(100);
                }
              }
            }
          }
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (cross_Mode == SETTING)
      {
        time_Out = 0;
        HAL_GPIO_WritePin(blinky_Point, LOW);
        if (amrap_Mode == SET_MIN)
        {
          Segment_Set(0, 'A');
          Segment_Set(1, 'r');
          Segment_Set(4, 'N');
          Segment_Set(5, 'N');

          if (time_SecBit)
          {
            Segment_Set(2, cross_Value / 10);
            Segment_Set(3, cross_Value % 10);
          }
          else
          {
            Segment_Set(2, 'N');
            Segment_Set(3, 'N');
          }
          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }
        else if (amrap_Mode == SET_SEC)
        {
          Segment_Set(0, 'A');
          Segment_Set(1, 'r');
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');

          if (time_SecBit)
          {
            Segment_Set(4, cross_Value / 10);
            Segment_Set(5, cross_Value % 10);
          }
          else
          {
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
          }
          irRemote = Ir_GetData();
          if (irRemote != 0)
          {
            Haamin_Remote(irRemote, work_Mode);
          }
        }
      }
    }
    else if (work_Mode == SET_MIX)
    {
      Segment_Set(0, 'N');
      Segment_Set(1, 'N');
      Segment_Set(6, 't');
      if (cross_Mode == MAIN_FUNCTION)
      {
        time_Out = 0;
        HAL_GPIO_WritePin(blinky_Point, LOW);
        Segment_Set(2, 'N');
        Segment_Set(3, 'N');
        Segment_Set(4, 'f');
        Segment_Set(5, first_Set);
        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (cross_Mode == SETTING)
      {
        if (mix_Step == PART_1)
        {
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          HAL_GPIO_WritePin(blinky_Point, LOW);
          if (time_SecBit)
          {
            Segment_Set(4, 'f');
            Segment_Set(5, first_Set);
          }
          else
          {
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
          }
          if ((cross_Value >= 1) && (cross_Value <= 5))
            first_Set = cross_Value;
        }
        else if (mix_Step == PART_2)
        {
          HAL_GPIO_WritePin(blinky_Point, HIGH);
          if (mix_Mode == SET_MIN)
          {
            Segment_Set(4, mix_Second / 10);
            Segment_Set(5, mix_Second / 10);
            if (time_SecBit)
            {
              Segment_Set(2, cross_Value / 10);
              Segment_Set(3, cross_Value % 10);
            }
            else
            {
              Segment_Set(2, 'N');
              Segment_Set(3, 'N');
            }
          }
          else if (mix_Mode == SET_SEC)
          {
            Segment_Set(2, mix_Minute / 10);
            Segment_Set(3, mix_Minute % 10);
            if (time_SecBit)
            {
              Segment_Set(4, cross_Value / 10);
              Segment_Set(5, cross_Value % 10);
            }
            else
            {
              Segment_Set(4, 'N');
              Segment_Set(5, 'N');
            }
          }
        }
        else if (mix_Step == PART_3)
        {
          HAL_GPIO_WritePin(blinky_Point, LOW);
          Segment_Set(2, 'N');
          Segment_Set(3, 'N');
          if (time_SecBit)
          {
            Segment_Set(4, 'f');
            Segment_Set(5, second_Set);
          }
          else
          {
            Segment_Set(4, 'N');
            Segment_Set(5, 'N');
          }

          if ((cross_Value >= 1) && (cross_Value <= 5))
            second_Set = cross_Value;
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
    }
    else if (work_Mode == MIX)
    {
      time_Out = 0;
      if (mix_Step == PART_1)
      {
        mix_Step = PART_2;
        mix_Flag = 1;
        switch (first_Set)
        {
        case 1:
          work_Mode = UP_TIMER;
          break;
        case 2:
          work_Mode = DN_TIMER;
          break;
        case 3:
          work_Mode = TABATA;
          break;
        case 4:
          work_Mode = EMOM;
          break;
        case 5:
          work_Mode = AMRAP;
          break;
        default:
          break;
        }
        cross_Mode = MAIN_FUNCTION;
        timer_Mode = MAIN_FUNCTION;
        Buzz(100);
      }
      else if (mix_Step == PART_2)
      {
        Segment_Set(0, 'N');
        Segment_Set(1, 'N');
        Segment_Set(2, mix_Minute / 10);
        Segment_Set(3, mix_Minute % 10);
        Segment_Set(4, mix_Second / 10);
        Segment_Set(5, mix_Second % 10);
        mix_Flag = 0;

        if (time_SecBit)
        {
          time_SecBit = 0;
          if (--mix_Second < 0)
          {
            mix_Second = 59;
            if (--mix_Minute < 0)
            {
              mix_Minute = 0;
              mix_Second = 0;
              mix_Step = 3;
              Buzz(100);
              HAL_Delay(100);
              Buzz(100);
              HAL_Delay(100);
              Buzz(100);
            }
          }
        }

        irRemote = Ir_GetData();
        if (irRemote != 0)
        {
          Haamin_Remote(irRemote, work_Mode);
        }
      }
      else if (mix_Step == PART_3)
      {
        mix_Step = 0;
        mix_Flag = 1;
        switch (second_Set)
        {
        case 1:
          work_Mode = UP_TIMER;
          break;
        case 2:
          work_Mode = DN_TIMER;
          break;
        case 3:
          work_Mode = TABATA;
          break;
        case 4:
          work_Mode = EMOM;
          break;
        case 5:
          work_Mode = AMRAP;
          break;
        default:
          break;
        }
        Buzz(100);
      }
      else
      {
        work_Mode = SET_MIX;
        cross_Mode = MAIN_FUNCTION;
        Buzz(200);
        HAL_Delay(100);
      }
      Segment_Set(6, 't');
    }

#endif
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
  if (++time_TmpShow > 30)
  {
    time_TmpShow = 0;
  }
  if (++time_DateShow > 30)
  {
    time_DateShow = 0;
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

#ifdef EDARI
  if (time_Second == 1)
  {
    DS3231_ReadCalendar(&hi2c2, &gdate_Year, &gdate_Mounth, &gdate_Day, &date_Week);
    gregorian_to_jalali(gdate_Year + 2000, gdate_Mounth, gdate_Day, jalali_Calender);
    if (jalali_Calender[0] > 1400)
      jdate_Year = jalali_Calender[0] - 1400;
    jdate_Mounth = jalali_Calender[1];
    jdate_Day = jalali_Calender[2];
    dateOfWeek = GET_DOW(date_Week);
  }
#endif
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
