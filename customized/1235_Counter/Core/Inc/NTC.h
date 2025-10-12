/*
 * NTC.h
 *
 *  Created on: Feb 17, 2025
 *      Author: Mobina
 */

#ifndef INC_NTC_H_
#define INC_NTC_H_

#include "stm32f1xx_hal.h"
#include "adc.h"
//#include <math.h>

#define VREF 3.3f                     // ولتاژ مرجع ADC (میکرو)
#define VIN 5.0f

#define NUMSAMPLES          10                  //Number of ADC samples to average for better measurement accuracy
#define SERIESRESISTOR      10000          //Value of the series resistor in ohms
#define THERMISTORNOMINAL   10000       //Nominal resistance of the thermistor at 25°C in ohms
#define TEMPERATURENOMINAL  25           //Nominal temperature for the thermistor resistance in degrees Celsius
#define BCOEFFICIENT        3950


uint8_t NTC_Read(void);

#endif /* INC_NTC_H_ */
