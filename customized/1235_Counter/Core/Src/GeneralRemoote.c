/*
 * GeneralRemoote.c
 *
 *  Created on: Feb 15, 2025
 *      Author: Mobina
 */
#include "GeneralRemoote.h"
#include "DS3231.h"



uint8_t valuSetting_tmp = 0;
uint8_t valueNumber = 0;
uint8_t valueFeedback = 0;
uint8_t muteFlag = 1;

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


