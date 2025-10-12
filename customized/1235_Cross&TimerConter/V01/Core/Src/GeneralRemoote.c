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
        else if(action == MENU_KEY)
        {
            work_Mode = MENU;
        }
        else if(action == PgDn)
        {
            if(tmpShow == 0)
            {
                tmpShow = 1;
                time_TmpShow = 0;
                Buzz(50);
                HAL_Delay(50);
                Buzz(50);
            }
            else 
            {
                if(time_TmpShow < 5)
                    tmpShow = 0;
                else
                    time_TmpShow = 0;
            }
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
        else if(action == UP_TIMER_KEY)
        {
            work_Mode = UP_TIMER;
            timer_Mode = MAIN_FUNCTION;
            upTime_Minute = 0;
            upTime_Second = 0;
            timer_TimeStarting = 11;
        }
        else if(action == DN_TIMER_KEY)
        {
            work_Mode = DN_TIMER;
            timer_Mode = MAIN_FUNCTION;
            dnTime_Minute = dnTime_Minute_Defult;
            dnTime_Second = 0;
            timer_TimeStarting = 11;
        }
        else if(action == TABATA_KEY)
        {
            work_Mode = TABATA;
            cross_Mode = MAIN_FUNCTION;
            tabata_Round = tabata_Round_Def;
            tabata_Act = tabata_Act_Def;
            tabata_Rest = tabata_Rest_Def;
            cross_SrUpEn = 1;
            cross_TimeStarting = 11; 
        }
        else if(action == EMOM_KEY)
        {
            work_Mode = EMOM;
            cross_Mode = MAIN_FUNCTION;
            emom_Round = emom_Round;
            emom_Time = emom_Time_Def;
            cross_SrUpEn = 1;
            cross_TimeStarting = 11;
        }
        else if(action == AMRAP_KEY)
        {
            work_Mode = AMRAP;
            cross_Mode = MAIN_FUNCTION;
            amrap_Minute = amrap_Minute_Def;
            amrap_Second = amrap_Second_Def;
            cross_SrUpEn = 1;
            cross_TimeStarting = 11;
        }
        else if(action == MIX_KEY)
        {
            work_Mode = SET_MIX;
            cross_Mode = SETTING;
            mix_Step = PART_1;
        }
        else if(action == TIMER_COUNTER_KEY)
        {
            work_Mode = TIMER_COUNTER;
            timer_Run = 0;
            timer_Second = 0;
            timer_mili_Second = 0;
            counter_Value = 0;
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
    else if (workMode == MENU)
    {
        time_Out = 0;
        if (action == INCREASE)
        {
            if (++Condition > 6)
                Condition = 1;
            Buzz(100);
        }
        else if (action == DECREASE)
        {
            if (Condition == 1)
                Condition = 6;
            else
                Condition--;
            Buzz(100);
        }
        else if (action == MUTE)
        {
            if (muteFlag)
                muteFlag = 0;
            else
                muteFlag = 1;
            Buzz(100);
        }
        else if (action == OK_KEY)
        {
            switch (Condition)
            {
            case 1:
                work_Mode = UP_TIMER;
                timer_Mode = MAIN_FUNCTION;
                timer_SrUpEn = 1;
                upTime_Minute = 0;
                upTime_Second = 0;
                timer_TimeStarting = 11;
                break;

            case 2:
                work_Mode = DN_TIMER;
                timer_Mode = MAIN_FUNCTION;
                dnTime_Minute = dnTime_Minute_Defult;
                dnTime_Second = 0;
                timer_SrUpEn = 1;
                timer_TimeStarting = 11;
                break;

            case 3:
                work_Mode = TABATA;
                cross_Mode = MAIN_FUNCTION;
                tabata_Round = tabata_Round_Def;
                tabata_Act = tabata_Act_Def;
                tabata_Rest = tabata_Rest_Def;
                cross_Run = 0;
                cross_SrUpEn = 1;
                cross_TimeStarting = 11;
                break;

            case 4:
                work_Mode = EMOM;
                cross_Mode = MAIN_FUNCTION;
                emom_Round = emom_Round;
                emom_Time = emom_Time_Def;
                cross_Run = 0;
                cross_SrUpEn = 1;
                cross_TimeStarting = 11;
                break;

            case 5:
                work_Mode = AMRAP;
                cross_Mode = MAIN_FUNCTION;
                amrap_Minute = amrap_Minute_Def;
                amrap_Second = amrap_Second_Def;
                cross_SrUpEn = 1;
                cross_Run = 0;
                cross_TimeStarting = 11;
                break;

            case 6:
                work_Mode = SET_MIX;
                cross_Mode = SETTING;
                mix_Step = PART_1;
                break;

            default:
                break;
            }
            Buzz(100);
        }
        
        else if (action == EXIT_KEY)
        {
            work_Mode = MODE_NORMAL;
            Buzz(50);
            HAL_Delay(50);
            Buzz(100);
        }
    
        else if ((action == KEY_0) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
        {
            Condition = Haamin_NumberKey(action);
            if(Condition > 6)   Condition =6;
            if(Condition == 0)  Condition = 1;
            Buzz(100);
        }
    }
    else if(workMode == UP_TIMER)
    {
        if(timer_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(++timer_Value > 99)
                    timer_Value = 0;
            }
            else if(action == DECREASE)
            {
                if(timer_Value == 0)
                    timer_Value = 99;
                else
                    timer_Value--;
            }
            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                upTime_Minute_Defult = timer_Value;
                upTime_Minute = upTime_Minute_Defult;
                timer_SrUpEn = 1;
                timer_Mode = MAIN_FUNCTION;
                timer_TimeStarting = 11;
            }
            else if (action == EXIT_KEY)
            {
                timer_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                valueFeedback = Haamin_NumberKey(action);
                timer_Value = ((valuSetting_tmp * 10) + valueFeedback);
                valuSetting_tmp = valueFeedback; 
            }
        }
        else 
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }

            else if(action == INFO)
            {
                timer_Mode = SETTING;
                timer_Value = upTime_Minute_Defult;
                upTime_Second = 0;
                timer_Run = 0;
            }
            else if(action == RESET_KEY)
            {
                upTime_Minute = 0;
                upTime_Second = 0;
                timer_SrUpEn = 1;
                timer_Run = 0;
                timer_TimeStarting = 11;
                timer_StartUp = 0;
            }
            else if(action == PLAY_KEY)
            {
                timer_StartUp = 0;
                timer_Run = 1;
            }
            else if(action == PUSE_KEY)
            {
                timer_StartUp = 0;
                timer_Run = 0;
            }
            else if(action == EXIT_KEY)
            {
                timer_SrUpEn = 1;
                timer_StartUp = 0;
                timer_Run = 0;
                upTime_Minute = 0;
                upTime_Second = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
            
        }           
        Buzz(100);
    }
    else if(workMode == DN_TIMER) 
    {
        if(timer_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(++timer_Value > 99)
                    timer_Value = 0;
            }
            else if(action == DECREASE)
            {
                if(timer_Value == 0)
                    timer_Value = 99;
                else
                    timer_Value--;
            }
            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                dnTime_Minute_Defult = timer_Value;
                dnTime_Minute = dnTime_Minute_Defult;
                timer_SrUpEn = 1;
                timer_Mode = MAIN_FUNCTION;
                timer_TimeStarting = 11;
            }
            else if (action == EXIT_KEY)
            {
                timer_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                valueFeedback = Haamin_NumberKey(action);
                timer_Value = ((valuSetting_tmp * 10) + valueFeedback);
                valuSetting_tmp = valueFeedback; 
            }
        }
        else 
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }

            else if(action == INFO)
            {
                timer_Mode = SETTING;
                timer_Value = dnTime_Minute_Defult;
                dnTime_Second = 0;
                timer_Run = 0;
            }
            else if(action == RESET_KEY)
            {
                dnTime_Minute = dnTime_Minute_Defult;
                dnTime_Second = 0;
                timer_Run = 0;
                timer_TimeStarting = 11;
                timer_SrUpEn = 1;
                timer_StartUp = 0;
            }
            else if(action == PLAY_KEY)
            {
                timer_StartUp = 0;
                timer_Run = 1;
            }
            else if(action == PUSE_KEY)
            {
                timer_StartUp = 0;
                timer_Run = 0;
            }
            else if(action == EXIT_KEY)
            {
                timer_SrUpEn = 1;
                timer_StartUp = 0;
                timer_Run = 0;
                dnTime_Minute = 0;
                dnTime_Second = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
        }           
        Buzz(100);
    } 
    else if(work_Mode == TABATA)
    {
        if(cross_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(++cross_Value > 99)
                    cross_Value = 0;
            }
            else if(action == DECREASE)
            {
                if(cross_Value == 0)
                    cross_Value = 99;
                else
                    cross_Value--;
            }
            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                if(tabata_Mode == ROUND)
                {
                    tabata_Round_Def = cross_Value;
                    cross_Value = tabata_Act_Def;
                    tabata_Mode = ACT;
                }
                else if(tabata_Mode == ACT)
                {
                    tabata_Act_Def = cross_Value;
                    cross_Value = tabata_Rest_Def;
                    tabata_Mode = REST;
                }
                else if(tabata_Mode == REST)
                {
                    tabata_Rest_Def = cross_Value;
                    tabata_Round = tabata_Round_Def;
                    tabata_Act = tabata_Act_Def;
                    tabata_Rest = tabata_Rest_Def;
                    tabata_Mode = ROUND;
                    cross_Mode = MAIN_FUNCTION;
                }
            }
            else if (action == EXIT_KEY)
            {
                tabata_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                valueFeedback = Haamin_NumberKey(action);
                cross_Value = ((valuSetting_tmp * 10) + valueFeedback);
                valuSetting_tmp = valueFeedback; 
            }
        }
        else if(cross_Mode == MAIN_FUNCTION)
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if(action == INFO)
            {
                cross_Mode = SETTING;
                tabata_Mode = ROUND;
                cross_Value = tabata_Round_Def;
                cross_Run = 0;
            }
            else if(action == RESET_KEY)
            {
                tabata_Round = tabata_Round_Def;
                tabata_Act = tabata_Act_Def;
                tabata_Rest = tabata_Rest_Def;
                cross_SrUpEn = 1;
                cross_Run = 0;
                cross_TimeStarting = 11;
                cross_StartUp = 0;
            }
            else if(action == PLAY_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 1;
            }
            else if(action == PUSE_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 0;
            }
            else if(action == EXIT_KEY)
            {
                cross_SrUpEn = 1;
                cross_StartUp = 0;
                cross_Run = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
        }
        Buzz(100);
    } 
    else if(work_Mode == EMOM)
    {
        if(cross_Mode == MAIN_FUNCTION)
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if(action == INFO)
            {
                cross_Mode = SETTING;
                emom_Mode = ROUND;
                cross_Value = emom_Round_Def;
                cross_Run = 0;
            }
            else if(action == RESET_KEY)
            {
                emom_Round = emom_Round_Def;
                emom_Act = emom_Act_Def;
                emom_Time = emom_Time_Def;
                emom_Time_tmp = (emom_Time * 60);
                emom_Mode = 1;
                cross_SrUpEn = 1;
                cross_Run = 0;
                cross_TimeStarting = 11;
                cross_StartUp = 0;
            }
            else if(action == PLAY_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 1;
            }
            else if(action == PUSE_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 0;
            }
            else if(action == EXIT_KEY)
            {
                cross_SrUpEn = 1;
                cross_StartUp = 0;
                cross_Run = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
            Buzz(100);
        }
        else if(cross_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(++cross_Value > 99)
                    cross_Value = 0;
            }
            else if(action == DECREASE)
            {
                if(cross_Value == 0)
                    cross_Value = 99;
                else
                    cross_Value--;
            }
            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                if(emom_Mode == ROUND)
                {
                    emom_Round_Def = cross_Value;
                    cross_Value = emom_Time_Def;
                    emom_Mode = ACT;
                }
                else if(emom_Mode == ACT)
                {
                    emom_Time_Def = cross_Value;
                    emom_Round = emom_Round_Def;
                    emom_Time = emom_Time_Def;
                    emom_Act = (emom_Time * 60) / emom_Round;
                    if(emom_Act > 99)
                        emom_Act = 99;
                    emom_Act_Def = emom_Act;
                    emom_Time_tmp = (emom_Time * 60);
                    cross_Mode = MAIN_FUNCTION;
                    emom_Mode = 1;
                }
            }
            else if (action == EXIT_KEY)
            {
                emom_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                valueFeedback = Haamin_NumberKey(action);
                cross_Value = ((valuSetting_tmp * 10) + valueFeedback);
                valuSetting_tmp = valueFeedback; 
            }
        }
        Buzz(100);
    } 
    else if(work_Mode == AMRAP)
    {
        if(cross_Mode == MAIN_FUNCTION)
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if(action == INFO)
            {
                cross_Mode = SETTING;
                amrap_Mode = SET_MIN;
                cross_Value = amrap_Minute_Def;
                cross_Run = 0;
            }
            else if(action == RESET_KEY)
            {
                amrap_Minute = amrap_Minute_Def;
                amrap_Second = amrap_Second;
                cross_SrUpEn = 1;
                cross_Run = 0;
                cross_TimeStarting = 11;
                cross_StartUp = 0;
            }
            else if(action == PLAY_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 1;
            }
            else if(action == PUSE_KEY)
            {
                cross_StartUp = 0;
                cross_Run = 0;
            }
            else if(action == EXIT_KEY)
            {
                cross_SrUpEn = 1;
                cross_StartUp = 0;
                cross_Run = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
            Buzz(100);
        }
        else if(cross_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(++cross_Value > 99)
                    cross_Value = 0;
            }
            else if(action == DECREASE)
            {
                if(cross_Value == 0)
                    cross_Value = 99;
                else
                    cross_Value--;
            }
            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                if(amrap_Mode == SET_MIN)
                {
                    amrap_Minute_Def = cross_Value;
                    cross_Value = amrap_Second_Def;
                    amrap_Mode = SET_SEC;
                }
                else if(amrap_Mode == SET_SEC)
                {
                    amrap_Second_Def = cross_Value;
                    amrap_Minute  = amrap_Minute_Def;
                    amrap_Second = amrap_Second_Def;
                    amrap_Mode = SET_MIN;
                    cross_Mode = MAIN_FUNCTION;
                }
            }
            else if (action == EXIT_KEY)
            {
                amrap_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                valueFeedback = Haamin_NumberKey(action);
                cross_Value = ((valuSetting_tmp * 10) + valueFeedback);
                valuSetting_tmp = valueFeedback; 
            }
        
        }
        Buzz(100);
    }
    else if(work_Mode == SET_MIX)
    {
        if(cross_Mode == MAIN_FUNCTION)
        {
            if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if(action == INFO)
            {
                cross_Mode = SETTING;
                mix_Step = PART_1;
                cross_Value = 1;
            }
            else if(action == EXIT_KEY)
            {
                cross_SrUpEn = 1;
                cross_StartUp = 0;
                cross_Run = 0;
                work_Mode = MODE_NORMAL;
                Buzz(50);
                HAL_Delay(50);
            }
            Buzz(100);
        }
        else if(cross_Mode == SETTING)
        {
            if(action == INCREASE)
            {
                if(mix_Step == 2)
                {
                    if(++cross_Value > 99)
                        cross_Value = 0;
                }
                else
                {
                    if(++cross_Value > 5)
                        cross_Value = 1;
                }
            }
            else if(action == DECREASE)
            {
                if(mix_Step == 2)
                {
                    if(cross_Value == 0)
                        cross_Value = 99;
                    else
                        cross_Value--;
                }
                else
                {
                    if(cross_Value == 1)
                        cross_Value = 5;
                    else
                        cross_Value--;
                }
            }

            else if(action == MUTE)
            {
                if(muteFlag)
                    muteFlag = 0;
                else
                    muteFlag = 1;
            }
            else if (action == OK_KEY)
            {
                if(mix_Step == PART_1)
                {
                    mix_Step = PART_2;
                    mix_Mode = SET_MIN;
                    cross_Value = mix_Minute;
                }
                else if(mix_Step == PART_2)
                {
                    if(mix_Mode == SET_MIN)
                    {
                        mix_Minute = cross_Value;
                        cross_Value = mix_Second;
                        mix_Mode = SET_SEC;
                    }
                    else if(mix_Mode == SET_SEC)
                    {
                        mix_Mode = SET_MIN;
                        mix_Second = cross_Value;
                        mix_Step = 3;
                    }
                }
                else if(mix_Step == PART_3)
                {
                    mix_Step = PART_1;
                    work_Mode = MIX;
                    cross_Mode = MAIN_FUNCTION;
                }
            }
            else if (action == EXIT_KEY)
            {
                cross_Mode = MAIN_FUNCTION;
                Buzz(50);
                HAL_Delay(50);
            }
            else if((action == KEY_0 ) || (action == KEY_1) || (action == KEY_2) || (action == KEY_3) || (action == KEY_4) || (action == KEY_5) || (action == KEY_6) || (action == KEY_7) || (action == KEY_8) || (action == KEY_9))
            {
                if(mix_Step == 2)
                {
                    valueFeedback = Haamin_NumberKey(action);
                    cross_Value = ((valuSetting_tmp * 10) + valueFeedback);
                    valuSetting_tmp = valueFeedback; 
                    if(mix_Mode == SET_SEC)
                {
                    if(cross_Value > 60)
                        cross_Value = 59;
                }
                }
                else 
                {
                    cross_Value = Haamin_NumberKey(action);
                }
            }
            Buzz(100);
        
        }
        Buzz(100);
    }
    else if(work_Mode == MIX)
        {
            if(mix_Step == 2)
            {
                if(action == EXIT_KEY)
                {
                    mix_Flag = 0;
                    work_Mode = MODE_NORMAL;
                }
            }
            Buzz(100);

        }
    else if(work_Mode == TIMER_COUNTER)
    {
        
        if(action == EXIT_KEY)
        {
            timer_Run = 0;
            work_Mode = MODE_NORMAL;
            Buzz(100);
        }
        else if(action == RESET_KEY)
        {
            timer_Run = 0;
            timer_Second = 0;
            timer_mili_Second = 0;
            counter_Value = 0;
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


