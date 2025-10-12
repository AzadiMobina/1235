/*
 * GeneralRemoote.c
 *
 *  Created on: Feb 15, 2025
 *      Author: Mobina
 */
#include "GeneralRemoote.h"




uint8_t valuSetting_tmp = 0;
uint8_t valueNumber = 0;
uint8_t valueFeedback = 0;
uint8_t muteFlag = 1;

void Haamin_Remote(uint16_t action, uint8_t workMode)
{
    
    if(workMode == MODE_NORMAL)
    {
        if(action == INFO)
        {
            work_Mode = TIME_SETTING;
            time_Mode = SET_HOUR;
            timeValue = time_Hour;
            time_Minute_t = time_Minute;
        }
        else if(action == MUTE)
        {
            if(muteFlag)
                muteFlag = 0;
            else
                muteFlag = 1;
        }
        else if(action == ON_OFF)
        {
            work_Mode = MODE_OFF;
        }
        else if(action == AM_PM)
        {
            if(PM_Mode)
                PM_Mode = 0;
            else 
                PM_Mode = 1;
            Buzz(100);
        }
        else if(action == INCREASE)  
        {
            if(position_Level == 7)
            {
                position_Level = 7;
                Buzz(50);
                HAL_Delay(50);
            }
            else 
                position_Level--;
            Buzz(50);

        }
        else if(action == DECREASE)
        {
            
            if(position_Level > 20)
            {
                position_Level = 20;
                Buzz(50);
                HAL_Delay(50);
            }
            else 
                position_Level++;
            Buzz(50);
        }
        else if(action == MENU_KEY)
        {
            work_Mode = SELECT_LEVEL;
            timer_Run = 0;
            timer_Second = 0;
            timer_mili_Second = 0;
        }
        Buzz(100);
    }
    else if(workMode == MODE_OFF)
    {
        if(action == ON_OFF)
        {
            work_Mode = MODE_NORMAL;
        }
        Buzz(100);
    }
    else if(workMode == TIME_SETTING)
    {
        if(action == INCREASE)
        {
            if(time_Mode == SET_HOUR)
            {
                if(++timeValue > 23)
                timeValue = 0;
            }
            else 
            {
                if(++timeValue > 59)
                timeValue = 0;
            }
            
            
        }
        else if(action == DECREASE)
        {
            if(time_Mode == SET_HOUR)
            {
                if(timeValue == 0)
                timeValue = 23;
                else
                timeValue--;
            }
            else 
            {
                if(timeValue == 0)
                timeValue = 59;
                else
                timeValue--;
            }
            
        }
        else if(action == EXIT_KEY)
        {
            work_Mode = MODE_NORMAL;
        }
        else if(action == OK_KEY)
        {
            if(time_Mode == SET_HOUR)
            {
                time_Hour_t = timeValue;
                time_Mode = SET_MIN;
                timeValue = time_Minute;
            }
            else if(time_Mode == SET_MIN)
            {
                time_Minute_t = timeValue;
                time_Minute = time_Minute_t;
                time_Hour = time_Hour_t;
                time_Second = 0;
                work_Mode = MODE_NORMAL;
                time_Mode = SET_HOUR;
                DS3231_WriteTime(&hi2c2, time_Hour,time_Minute,0);
                
            }
            
        }
        else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
        {
            valueFeedback = Haamin_NumberKey(action);
            timeValue = ((valuSetting_tmp * 10) + valueFeedback);
            valuSetting_tmp = valueFeedback;
        }
        Buzz(100);
    }
    else if(work_Mode == SELECT_LEVEL)
    {
        time_Out = 0;
        if(action == EXIT_KEY)
        {
            timer_Run = 0;
            work_Mode = MODE_NORMAL;
            Buzz(100);
        }
        else if(action ==DECREASE)  
        {
            if(chaleng_Level == 1)
            {
                chaleng_Level = 1;
                Buzz(50);
                HAL_Delay(50);
            }
            else 
                chaleng_Level--;
            Buzz(50);

        }
        else if(action == INCREASE )
        {
            
            if(chaleng_Level == 4)
            {
                chaleng_Level = 4;
                Buzz(50);
                HAL_Delay(50);
            }
            else 
                chaleng_Level++;
            Buzz(50);
        }
        else if(action == OK_KEY)
        {
            switch (chaleng_Level)
            {
            case 1:
                chaleng_Level_Val = 1;
                break;
            case 2:
                chaleng_Level_Val = 2;
                break;
            case 3:
                chaleng_Level_Val = 5;
                break;
            case 4:
                chaleng_Level_Val = 10;
                break;
            default:
                chaleng_Level_Val = 1;
                break;
            }
            work_Mode = SET_TARGET; 
            time_Mode = SET_SEC;
            Buzz(100); 
        }        
        else if((action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) )
        {
            chaleng_Level = Haamin_NumberKey(action);
            Buzz(100);
        }
    
    }
    else if(work_Mode == SET_TARGET)
    {
        time_Out = 0;
        if(action == INCREASE)
        {
            if(time_Mode == SET_SEC)
            {
                if(++target_Second > 99)
                    target_Second = 0;
            }
            else 
            {
                if(++target_mili_Second > 99)
                    target_mili_Second = 0;
            }
             Buzz(100);
        }
        else if(action == DECREASE)
        {
            if(time_Mode == SET_SEC)
            {
                if(target_Second == 0)
                    target_Second = 99;
                else
                    target_Second--;
            }
            else 
            {
                if(target_mili_Second == 0)
                    target_mili_Second = 99;
                else
                    target_mili_Second--;
            }
             Buzz(100);
        }
        else if(action == EXIT_KEY)
        {
            work_Mode = SELECT_LEVEL;
            Buzz(100);
        }
        else if(action == OK_KEY)
        {
            if(time_Mode == SET_SEC)
            {
                time_Mode = SET_MILI;
                timeValue = 0;
            }
            else if(time_Mode == SET_MILI)
            {
                work_Mode = CHALENG;
                target_Number = (target_Second * 100) + target_mili_Second;
            }
             Buzz(100);
        }
        else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
        {
            valueFeedback = Haamin_NumberKey(action);
            timeValue = ((valuSetting_tmp * 10) + valueFeedback);
            valuSetting_tmp = valueFeedback;
            if(time_Mode == SET_SEC)              target_Second = timeValue;
            else if(time_Mode == SET_MILI)        target_mili_Second = timeValue;
            Buzz(100);
        }
        
    }
    else if(work_Mode == CHALENG)
    {
        
        if(action == EXIT_KEY)
        {
            timer_Run = 0;
            work_Mode = MODE_NORMAL;
            Buzz(100);
        }
        else if(action == INFO)
        {
            work_Mode = SET_TARGET;
            time_Mode = SET_SEC;
            Buzz(100);
        }
        else if(action == RESET_KEY)
        {
            timer_Run = 0;
            timer_Second = 0;
            timer_mili_Second = 0;
            Buzz(100);
        }
        else if(action == PLAY_KEY)
        {
            timer_Run = 1;
            Buzz(100);
        }
        else if(action == PUSE_KEY)
        {
            timer_Run = 0;
            Buzz(100);
        }
    }
}

uint8_t Haamin_NumberKey (uint16_t numberKey)
{
    if(numberKey == KEY_0)
        valueNumber = 0;
    else if(numberKey == KEY_1)
        valueNumber = 1;
    else if(numberKey == KEY_2)
        valueNumber = 2;
    else if(numberKey == KEY_3)
        valueNumber = 3;
    else if(numberKey == KEY_4)
        valueNumber = 4;
    else if(numberKey == KEY_5)
        valueNumber = 5;
    else if(numberKey == KEY_6)
        valueNumber = 6;
    else if(numberKey == KEY_7)
        valueNumber = 7;
    else if(numberKey == KEY_8)
        valueNumber = 8;
    else if(numberKey == KEY_9)
        valueNumber = 9;

    return valueNumber;

}


void Buzz(uint16_t time)
{
  if(muteFlag)
  {
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
    HAL_Delay(time);
    HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
  }
}


