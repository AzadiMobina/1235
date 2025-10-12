/*
 * NTC.C
 *
 *  Created on: Feb 17, 2025
 *      Author: Mobina
 */
#include "NTC.h"

float samples[NUMSAMPLES];          //Array to store ADC sample values
float average = 0;               //Variable to store the average of ADC samples
float steinhart;                   //Variable to store the calculated temperature in Celsius
uint8_t i;
uint8_t tempRead = 1;

float resistance;


extern ADC_HandleTypeDef hadc1;

uint8_t NTC_Read(void)
{
  average = 0;  //Clear previous average value to ensure correct calculation for the new set of samples
  float T0_K;
    //Collect multiple ADC samples and store them in the array
  for (i = 0; i < NUMSAMPLES; i++) 
  {
    HAL_ADC_Start(&hadc1);                              //Start the ADC conversion
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);   //Wait for the conversion to complete
    samples[i] = HAL_ADC_GetValue(&hadc1);              //Read the ADC conversion result
    HAL_Delay(10);                                      //Delay between samples to stabilize the ADC readings
  }
    
  //Compute the average of the collected ADC samples
  for (i = 0; i < NUMSAMPLES; i++) 
  {
    average += samples[i];  //Sum up all the ADC sample values
  }
  average /= NUMSAMPLES;  //Calculate the average of the ADC samples

  //Convert the average ADC reading to thermistor resistance and calculate temperature
  if (average > 0) 
  {  // Ensure the average is not zero to avoid division errors
    // average = 4095.0 / average - 1;  // Convert ADC reading to resistance using 12-bit ADC resolution
    float voltage = (average / 4095.0f) * VREF;
    resistance = SERIESRESISTOR * ((VIN / voltage) - 1.0f);   

    // T0_K = TEMPERATURENOMINAL + 273.15f;
    // steinhart = (1.0f/ BCOEFFICIENT) * log(resistance / THERMISTORNOMINAL);
    // steinhart = (1.0f/T0_K) + steinhart;
    // steinhart = (1.0f/ steinhart);
    // steinhart = steinhart - 273.15f;
    steinhart = resistance / THERMISTORNOMINAL;  //Compute the ratio of thermistor resistance to nominal resistance
    steinhart = log(steinhart);  //Compute the natural logarithm of the resistance ratio
    steinhart /= BCOEFFICIENT;  //Divide by the thermistor's Beta coefficient
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);  //Add the reciprocal of the nominal temperature in Kelvin
    steinhart = 1.0 / steinhart;  //Compute the reciprocal to get the temperature in Kelvin
    steinhart -= 273.15;  //Convert the temperature from Kelvin to Celsius
    //steinhart = steinhart - 2;
  }
  if ((steinhart > 100)||(steinhart < 0))
  {
    steinhart = 2;
  }
  
  return (uint8_t)steinhart;
}
