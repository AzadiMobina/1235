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
uint8_t date_Mode = SET_YEAR;
uint8_t time_Hour = 0, time_Minute = 0, time_Second = 0;
uint8_t time_SecBit = 0;
uint16_t gdate_Year = 0, gdate_Mounth = 0, gdate_Day = 0, gdate_Date = 0; 
uint16_t pdate_Year = 0, pdate_Mounth = 0, pdate_Day = 0, pdate_Date = 0;
uint8_t dateYear_t = 0, dateMounth_t = 0, dateDay_t = 0, dateWeek_t = 0, date_Week = 2, dateOfWeek = 0;
uint8_t time_Hour_t = 0, time_Minute_t = 0;
uint8_t timeValue = 0;
uint16_t irRemote = 0;
uint8_t  uart_Flag = 0, send_Flag = 0;

uint8_t tmpShow = 1;
uint8_t time_TmpShow = 0;
uint8_t time_DateShow = 0;
uint8_t dateShow = 0;
uint8_t date_Read = 0;
uint8_t dateValue = 0;
uint8_t temperature = 10;
uint8_t tempreture_read = 0;
long jalali_Calender[3] = {0};
long miladi_Calender[3] = {0};
uint8_t numarray[6] = {0};
uint8_t received_data = 0;
uint8_t rxBuffer[10] = {0};
//uint8_t uart_Flag = 0;



#ifdef  CROSS
#elif   BASHGHAHI
    uint8_t  upTime_Second = 0;
    uint8_t upTime_Minute = 0;
    uint8_t upTime_Minute_Defult = 0;
    uint8_t dnTime_Second = 0;
    uint8_t dnTime_Minute = 0;
    uint8_t dnTime_Minute_Defult = 0;
    uint8_t timer_TimeStarting = 0;
    uint8_t timer_Mode = 0;
    uint8_t timer_StartUp = 0;
    uint8_t timer_Run = 0;
    uint8_t timer_Value = 0;
    uint8_t timer_SrUpEn = 0;
#endif

#endif /* INC_INITIALIZATION_H_ */
