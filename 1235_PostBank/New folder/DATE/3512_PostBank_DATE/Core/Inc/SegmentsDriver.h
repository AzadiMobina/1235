/*
 * SegmentDriver.h
 *
 *  Created on: Feb 10, 2025
 *      Author: Amin
 */

#ifndef INC_SEGMENTSDRIVER_H_
#define INC_SEGMENTSDRIVER_H_

#include "main.h"

#define SEG_H1        Seg_1_VCC_GPIO_Port,Seg_1_VCC_Pin
#define SEG_H2        Seg_2_VCC_GPIO_Port,Seg_2_VCC_Pin
#define SEG_M1        Seg_3_VCC_GPIO_Port,Seg_3_VCC_Pin
#define SEG_M2        Seg_4_VCC_GPIO_Port,Seg_4_VCC_Pin
#define SEG_S1        Seg_5_VCC_GPIO_Port,Seg_5_VCC_Pin
#define SEG_S2        Seg_6_VCC_GPIO_Port,Seg_6_VCC_Pin

#define SEG_DAY        Seg_7_VCC_GPIO_Port,Seg_7_VCC_Pin

#define A           A_GPIO_Port,A_Pin
#define B           B_GPIO_Port,B_Pin
#define C           C_GPIO_Port,C_Pin
#define D           D_GPIO_Port,D_Pin
#define E           E_GPIO_Port,E_Pin
#define F           F_GPIO_Port,F_Pin
#define G           G_GPIO_Port,G_Pin


#define LOW         GPIO_PIN_RESET
#define HIGH        GPIO_PIN_SET




void Segments_Scan(void);
void Segment_Map(uint8_t value);
void Segment_Set(uint8_t seg, uint8_t value);

#endif /* INC_SEGMENTSDRIVER_H_ */
