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
uint8_t chaleng_Level = 4;
uint8_t chaleng_Level_Val = 4;
uint8_t PM_Mode = 0;
uint8_t target_Number = 1;
uint8_t chaleng_Number = 1;

uint8_t timer_Second = 0;
uint8_t timer_mili_Second = 0;
uint8_t target_Second = 0;
uint8_t target_mili_Second = 0;
uint8_t resultCheck_Flag = 0;
uint8_t win_Buzzer = 0;

uint8_t timer_TimeStarting = 0;
uint8_t timer_Mode = 0;
uint8_t timer_StartUp = 0;
uint8_t timer_Run = 0;
uint8_t timer_Value = 0;
uint8_t timer_SrUpEn = 1;

#endif /* INC_INITIALIZATION_H_ */
