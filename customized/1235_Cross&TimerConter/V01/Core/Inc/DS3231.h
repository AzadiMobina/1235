/*
 * DS3231.h
 *
 *  Created on: Feb 11, 2025
 *      Author: Haamin
 */

#ifndef INC_DS3231_H_
#define INC_DS3231_H_

#include "stm32f1xx_hal.h"
#include "Variable.h"
#include "Definition.h"
#include "i2c.h"


uint8_t BCD_to_Decimal(uint8_t bcd) {
    return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

uint8_t Decimal_to_BCD(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

void DS3231_WriteTime(I2C_HandleTypeDef *hi2c, uint8_t hour, uint8_t minute, uint8_t second) {
    uint8_t timeData[3];

    timeData[0] = Decimal_to_BCD(second);  // Convert second to BCD
    timeData[1] = Decimal_to_BCD(minute);  // Convert minute to BCD
    timeData[2] = Decimal_to_BCD(hour);    // Convert hour to BCD

    // DS3231 I2C address (0x68 is default address)
    HAL_I2C_Mem_Write(hi2c, 0xD0, 0x00, I2C_MEMADD_SIZE_8BIT, timeData, 3, 1000);
}

void DS3231_ReadTime(I2C_HandleTypeDef *hi2c, uint8_t *hour, uint8_t *minute, uint8_t *second) {
    uint8_t timeData[4];

    // DS3231 I2C address (0x68 is default address)
    HAL_I2C_Mem_Read(hi2c, 0xD0, 0x00, I2C_MEMADD_SIZE_8BIT, timeData, 4, 1000);

    *second = BCD_to_Decimal(timeData[0]);  // Convert BCD to decimal
    *minute = BCD_to_Decimal(timeData[1]);  // Convert BCD to decimal
    *hour = BCD_to_Decimal(timeData[2]);    // Convert BCD to decimal
}


void DS3231_EnableSQW1Hz(I2C_HandleTypeDef *hi2c) {
    uint8_t controlRegValue;

    // Read the current Control/Status Register value (0x0E)
    //HAL_I2C_Mem_Read(hi2c, 0xD0, 0x0E, I2C_MEMADD_SIZE_8BIT, &controlRegValue, 1, 1000);

    // Set the square wave frequency to 1Hz (bits 0-1 = 00) and enable SQW output (bit 7 = 1)
    controlRegValue = 0x00;

    // Write the updated value back to the Control/Status Register
    HAL_I2C_Mem_Write(hi2c, 0xD0, 0x0E, I2C_MEMADD_SIZE_8BIT, &controlRegValue, 1, 1000);
}



#endif /* INC_DS3231_H_ */
