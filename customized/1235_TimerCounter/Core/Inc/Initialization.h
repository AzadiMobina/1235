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
uint8_t time_Hour = 0, time_Minute = 0, time_Second = 0,time_mili_Second = 0;
uint8_t timer_Run = 0;
uint8_t Counter_Value = 0;

void Buzz(uint16_t time)
{ 
      HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
      HAL_Delay(time);
      HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
}




#endif /* INC_INITIALIZATION_H_ */
