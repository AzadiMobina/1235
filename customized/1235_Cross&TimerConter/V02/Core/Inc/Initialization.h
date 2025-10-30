/*
 * Initialization.h
 *
 *  Created on: Feb 16, 2025
 *      Author: Mobina
 */

#ifndef INC_INITIALIZATION_H_
#define INC_INITIALIZATION_H_

#include "Definition.h"

uint8_t work_Mode = MODE_NORMAL;
uint8_t time_Mode = SET_HOUR;
uint8_t time_Hour = 0, time_Minute = 0, time_Second = 0;
uint8_t time_SecBit = 0;
uint8_t time_Out = 0;

uint8_t time_Hour_t = 0, time_Minute_t = 0;
uint8_t timeValue = 0;
uint16_t irRemote = 0;
uint8_t position_Level = 7;

uint8_t tmpShow = 0;
uint8_t temp_Read = 0;
uint8_t time_TmpShow = 0;
uint8_t time_DateShow = 0;
uint8_t temperature = 10;
uint8_t tempreture_read = 0;
uint8_t PM_Mode = 0;
uint8_t Condition = 1;


uint8_t tabata_Act;
uint8_t tabata_Round;
uint8_t tabata_Rest;
uint8_t tabata_Act_Def = 30;
uint8_t tabata_Round_Def = 5;
uint8_t tabata_Rest_Def = 10;
uint8_t tabata_Mode;

uint8_t emom_Act;
uint8_t emom_Round;
uint8_t emom_Time;
uint8_t emom_Act_Def;
uint8_t emom_Round_Def = 2;
uint8_t emom_Time_Def = 1;
uint8_t emom_Time_tmp;
uint8_t emom_Mode;

int		 amrap_Second;
int      amrap_Minute;
uint8_t  amrap_Second_Def = 28;
uint8_t  amrap_Minute_Def = 1;
uint8_t  amrap_Act;
uint8_t  amrap_Mode;

uint8_t  mix_Step;
uint8_t  first_Set = 1;
uint8_t  second_Set = 1;
int      mix_Minute = 1;
int      mix_Second;
uint8_t  mix_Mode;
uint8_t  mix_Flag;
uint8_t  mix_Runnig;

uint8_t cross_TimeStarting;
uint8_t cross_Mode;
uint8_t cross_StartUp;
uint8_t cross_Run;
uint8_t cross_SrUpEn;
uint8_t cross_Value;

uint8_t  upTime_Second = 0;
uint8_t upTime_Minute = 0;
uint8_t upTime_Minute_Defult = 1;
int		dnTime_Second = 0;
int     dnTime_Minute = 0;
uint8_t dnTime_Minute_Defult = 1;

uint8_t timer_Second = 0;
uint8_t timer_mili_Second = 0;
uint8_t counter_Value = 0;

uint8_t timer_TimeStarting = 0;
uint8_t timer_Mode = 0;
uint8_t timer_StartUp = 0;
uint8_t timer_Run = 0;
uint8_t timer_Value = 0;
uint8_t timer_SrUpEn = 1;

#endif /* INC_INITIALIZATION_H_ */
