/*
 * Definition.h
 *
 *  Created on: Feb 16, 2025
 *      Author: Mobina
 */

#ifndef INC_DEFINITION_H_
#define INC_DEFINITION_H_

#define MODE_NORMAL     'R'
#define MODE_OFF        'F'
#define TIME_SETTING    'T'
#define DATE_SETTING    'D'
#define SET_MIN         'M'
#define SET_HOUR        'H'
#define SET_YEAR        'Y'
#define SET_MOTH        't'
#define SET_DAY         'A'
#define SET_DOW         'B'



//#define SIMPLE          'S'
#define EDARI           'E'
// #define CROSS             'C'
// #define BASHGHAHI         'B'

#define blinky_Point          Blinky_Point_GPIO_Port,Blinky_Point_Pin
#define date_Point            Date_Point_GPIO_Port,Date_Point_Pin

#ifdef  CROSS

    #define  SETTING         's'
    #define  MAIN_FUNCTION   'f'
    #define  TABATA     't'
    #define  EMOM       'e'
    #define  AMRAP      'a'
    #define  UP_TIMER        'u'
    #define  DN_TIMER        'd'
    #define  MIX_MODE        'm'
    

#elif  BASHGHAHI

    #define  SETTING         's'
    #define  MAIN_FUNCTION   'f'
    #define  UP_TIMER        'u'
    #define  DN_TIMER        'd'

#endif


#endif /* INC_DEFINITION_H_ */
