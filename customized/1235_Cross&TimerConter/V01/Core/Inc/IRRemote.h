/*
 * IRRemote.h
 *
 *  Created on: Feb 6, 2025
 *      Author: Amin
 */

#ifndef INC_IRREMOTE_H_
#define INC_IRREMOTE_H_

#include "stm32f1xx_hal.h"
#include "tim.h"

// ****** Key Mapp of Remote ******
#define ON_OFF            345
#define MUTE            281
#define X1_KEY            333
#define PgUp              270
#define X2_KEY            269
#define PgDn              274
#define X4_KEY            337
#define MENU_KEY          325
#define EXIT_KEY          261
#define OK_KEY            282
#define VOLn              346
#define VOLp              283
#define INCREASE          262 //CHu
#define DECREASE          278 //CHd
#define INFO              341
#define AM_PM               277
#define UP_TIMER_KEY            275 //TV_RADIO
#define DN_TIMER_KEY            279 //RECALL
#define TABATA_KEY        330 // AUDIO
#define EMOM_KEY          328 //SUB_T
#define AMRAP_KEY         264 //TTX
#define MIX_KEY           267
#define PLAY_KEY          326
#define PUSE_KEY          324//TIMESHIFT 
#define RESET_KEY         260
#define TIMER_COUNTER_KEY               263
#define RED               322
#define GREEN             320
#define YELLOW            256
#define BLUE              259

#define KEY_1             338
#define KEY_2             336
#define KEY_3             272
#define KEY_4             342
#define KEY_5             340
#define KEY_6             276
#define KEY_7             334
#define KEY_8             332
#define KEY_9             268
#define KEY_0             271



#define IR_FRAME_SIZE 33  // NEC IR frame has 33 transitions



void IR_SetTimeArrayValues(uint16_t timevalue);
uint16_t Ir_AnalyzeTimeArrayValues(void);
uint16_t Ir_GetData(void);
void Ir_ResetRunning(void);


#endif /* INC_IRREMOTE_H_ */
