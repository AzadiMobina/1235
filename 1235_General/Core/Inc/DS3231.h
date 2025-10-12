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

void DS3231_WriteCalendar(I2C_HandleTypeDef *hi2c, uint8_t year, uint8_t month, uint8_t day, uint8_t weekday) {
    uint8_t dateData[4];

    dateData[0] = Decimal_to_BCD(weekday);  // Convert weekday to BCD (1-7)
    dateData[1] = Decimal_to_BCD(day);      // Convert day to BCD (1-31)
    dateData[2] = Decimal_to_BCD(month);    // Convert month to BCD (1-12)
    dateData[3] = Decimal_to_BCD(year);     // Convert year to BCD (0-99)

    // DS3231 I2C address (0x68 is default address)
    HAL_I2C_Mem_Write(hi2c, 0xD0, 0x03, I2C_MEMADD_SIZE_8BIT, dateData, 4, 1000);
}

void DS3231_ReadCalendar(I2C_HandleTypeDef *hi2c, uint16_t *year, uint16_t *month, uint16_t *day, uint8_t *weekday) {
    uint8_t dateData[5];
    
    HAL_I2C_Mem_Read(hi2c, 0xD0, 0x03, I2C_MEMADD_SIZE_8BIT, dateData, 5, 1000);
    

    *weekday = BCD_to_Decimal(dateData[0]);  // Convert BCD to decimal
    *day = (uint16_t)BCD_to_Decimal(dateData[1]);      // Convert BCD to decimal
    *month = (uint16_t)BCD_to_Decimal(dateData[2]);    // Convert BCD to decimal
    *year = (uint16_t)BCD_to_Decimal(dateData[3]);     // Convert BCD to decimal

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



/**  Gregorian & Jalali (Hijri_Shamsi,Solar) Date Converter Functions
Author: JDF.SCR.IR =>> Download Full Version :  http://jdf.scr.ir/jdf
License: GNU/LGPL _ Open Source & Free :: Version: 2.80 : [2020=1399]
---------------------------------------------------------------------
355746=361590-5844 & 361590=(30*33*365)+(30*8) & 5844=(16*365)+(16/4)
355666=355746-79-1 & 355668=355746-79+1 &  1595=605+990 &  605=621-16
990=30*33 & 12053=(365*33)+(32/4) & 36524=(365*100)+(100/4)-(100/100)
1461=(365*4)+(4/4) & 146097=(365*400)+(400/4)-(400/100)+(400/400)  */

long *gregorian_to_jalali(long gy, long gm, long gd, long out[]) {
  long days;
  {
    long gy2 = (gm > 2) ? (gy + 1) : gy;
    long g_d_m[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    days = 355666 + (365 * gy) + ((int)((gy2 + 3) / 4)) - ((int)((gy2 + 99) / 100)) + ((int)((gy2 + 399) / 400)) + gd + g_d_m[gm - 1];
  }
  long jy = -1595 + (33 * ((int)(days / 12053)));
  days %= 12053;
  jy += 4 * ((int)(days / 1461));
  days %= 1461;
  if (days > 365) {
    jy += (int)((days - 1) / 365);
    days = (days - 1) % 365;
  }
  out[0] = jy;
  if (days < 186) {
    out[1]/*jm*/ = 1 + (int)(days / 31);
    out[2]/*jd*/ = 1 + (days % 31);
  } else {
    out[1]/*jm*/ = 7 + (int)((days - 186) / 30);
    out[2]/*jd*/ = 1 + ((days - 186) % 30);
  }
  return out;
}

long *jalali_to_gregorian(long jy, long jm, long jd, long out[]) {
  jy += 1595;
  long days = -355668 + (365 * jy) + (((int)(jy / 33)) * 8) + ((int)(((jy % 33) + 3) / 4)) + jd + ((jm < 7) ? (jm - 1) * 31 : ((jm - 7) * 30) + 186);
  long gy = 400 * ((int)(days / 146097));
  days %= 146097;
  if (days > 36524) {
    gy += 100 * ((int)(--days / 36524));
    days %= 36524;
    if (days >= 365) days++;
  }
  gy += 4 * ((int)(days / 1461));
  days %= 1461;
  if (days > 365) {
    gy += (int)((days - 1) / 365);
    days = (days - 1) % 365;
  }
  long gd = days + 1;
  long gm;
  {
    long sal_a[13] = {0, 31, ((gy % 4 == 0 && gy % 100 != 0) || (gy % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (gm = 0; gm < 13 && gd > sal_a[gm]; gm++) gd -= sal_a[gm];
  }
  out[0] = gy;
  out[1] = gm;
  out[2] = gd;
  return out;
}


void Date_Update(void)
{
  DS3231_ReadCalendar(&hi2c2,&gdate_Year,&gdate_Mounth,&gdate_Day,&date_Week);
  gregorian_to_jalali(gdate_Year+2000,gdate_Mounth,gdate_Day,jalali_Calender);
  jdate_Year = jalali_Calender[0] - 1400;
  jdate_Mounth = jalali_Calender[1];
  jdate_Day = jalali_Calender[2];
}
#endif /* INC_DS3231_H_ */
