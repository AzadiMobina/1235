/*
 * Variable.h
 *
 *  Created on: Feb 10, 2025
 *      Author: Mobina
 */

#ifndef INC_VARIABLE_H_
#define INC_VARIABLE_H_

#include "Definition.h"


extern uint8_t time_Hour, time_Minute, time_Second;
extern uint8_t time_Hour_t, time_Minute_t;
extern uint8_t time_SecBit;
extern uint8_t dateYear_t, dateMounth_t, dateDay_t, dateWeek_t, date_Week, dateOfWeek;
extern uint16_t gdate_Year, gdate_Mounth, gdate_Day;
extern uint16_t jdate_Year, jdate_Mounth, jdate_Day;
extern uint8_t work_Mode;
extern uint8_t time_Mode;
extern uint8_t date_Mode;
extern uint8_t timeValue;
extern uint8_t muteFlag;
extern uint8_t time_TmpShow;
extern uint8_t time_DateShow;
extern uint8_t tmpShow;
extern uint8_t temp_Read;
extern uint8_t dateShow;
extern uint8_t date_Read;
extern uint8_t date_Mode;
extern uint8_t dateValue;
extern uint8_t temperature;
extern uint8_t tempreture_read;
extern uint8_t PM_Mode;
extern long jalali_Calender[3];
extern long miladi_Calender[3];
extern uint16_t irRemote;
extern uint8_t time_Out;
extern uint8_t position_Level;
extern uint8_t Condition;

#ifdef  CROSS
    extern uint8_t  tabata_Act;
    extern uint8_t  tabata_Round; 
    extern uint8_t  tabata_Rest;
    extern uint8_t  tabata_Act_Def;
    extern uint8_t  tabata_Round_Def; 
    extern uint8_t  tabata_Rest_Def;  
    extern uint8_t  tabata_Mode; 

    extern uint8_t  emom_Act;
    extern uint8_t  emom_Round;
    extern uint8_t  emom_Time;
    extern uint8_t  emom_Mode;
    extern uint8_t  emom_Act_Def;
    extern uint8_t  emom_Round_Def; 
    extern uint8_t  emom_Time_Def;
    extern uint8_t  emom_Time_tmp;

    extern int 		amrap_Second;
    extern int      amrap_Minute;
    extern uint8_t  amrap_Second_Def;
    extern uint8_t  amrap_Minute_Def;
    extern uint8_t  amrap_Act;
    extern uint8_t  amrap_Mode;

    extern uint8_t  mix_Step;
    extern uint8_t  first_Set; 
    extern uint8_t  second_Set;
    extern int      mix_Minute;
    extern int      mix_Second;
    extern uint8_t  mix_Mode;
    extern uint8_t  mix_Flag;
    extern uint8_t  mix_Runnig;

    extern uint8_t  cross_TimeStarting;
    extern uint8_t  cross_Mode;
    extern uint8_t  cross_StartUp;
    extern uint8_t  cross_Run;
    extern uint8_t  cross_SrUpEn;
    extern uint8_t  cross_Value;

    extern uint8_t  upTime_Second;
    extern uint8_t  upTime_Minute;

    extern int      dnTime_Second;
    extern int      dnTime_Minute;
  
    extern uint8_t  upTime_Minute_Defult;
    extern uint8_t  dnTime_Minute_Defult;

    extern uint8_t  timer_TimeStarting;
    extern uint8_t  timer_Mode;
    extern uint8_t  timer_StartUp;
    extern uint8_t  timer_Run;
    extern uint8_t  timer_Value;
    extern uint8_t  timer_SrUpEn;
#elif BASHGHAHI
    extern uint8_t  upTime_Second;
    extern uint8_t  upTime_Minute;
    extern uint8_t  upTime_Minute_Defult;

    extern uint8_t  dnTime_Second;
    extern int      dnTime_Minute;
    extern uint8_t  dnTime_Minute_Defult;

    extern uint8_t  timer_TimeStarting;
    extern uint8_t  timer_Mode;
    extern uint8_t  timer_StartUp;
    extern uint8_t  timer_Run;
    extern uint8_t  timer_Value;
    extern uint8_t  timer_SrUpEn;
#endif
// uint8_t dateValue;


#endif /* INC_VARIABLE_H_ */
