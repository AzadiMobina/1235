/*
 * SegmentsDriver.c
 *
 *  Created on: Feb 10, 2025
 *      Author: Amin
 */

#include "SegmentsDriver.h"

uint8_t segment_position = 0;
uint8_t segment_value[14] = {0};

void Segments_Scan(void)
{
  if(++segment_position > 10)
    segment_position = 0;

  HAL_GPIO_WritePin(SEG_H1,LOW);
  HAL_GPIO_WritePin(SEG_H2,LOW);
  HAL_GPIO_WritePin(SEG_M1,LOW);
  HAL_GPIO_WritePin(SEG_M2,LOW);
  HAL_GPIO_WritePin(SEG_S1,LOW);
  HAL_GPIO_WritePin(SEG_S2,LOW);
  HAL_GPIO_WritePin(SEG_DAY,LOW);

  Segment_Map(segment_value[segment_position]);

    switch (segment_position)
    {
    case 0:
        HAL_GPIO_WritePin(SEG_H1,HIGH);
        break;
    case 1:
        HAL_GPIO_WritePin(SEG_H2,HIGH);
        break;
    case 2:
        HAL_GPIO_WritePin(SEG_M1,HIGH);
        break;
    case 3:
        HAL_GPIO_WritePin(SEG_M2,HIGH);
        break;
    case 4:
        HAL_GPIO_WritePin(SEG_S1,HIGH);
        break;
    case 5:
        HAL_GPIO_WritePin(SEG_S2,HIGH);
        break;
    case 6:
        HAL_GPIO_WritePin(SEG_DAY,HIGH);
        break;
    default:
        HAL_GPIO_WritePin(SEG_H1,LOW);
        HAL_GPIO_WritePin(SEG_H2,LOW);
        HAL_GPIO_WritePin(SEG_M1,LOW);
        HAL_GPIO_WritePin(SEG_M2,LOW);
        HAL_GPIO_WritePin(SEG_S1,LOW);
        HAL_GPIO_WritePin(SEG_S2,LOW);
        HAL_GPIO_WritePin(SEG_DAY,LOW);
        break;
    }

}

void Segment_Map(uint8_t value)
{
    switch (value)
    {
    case 'N':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 0:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 1:
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 2:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 3:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 4:
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 5:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 6:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 7:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 8:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 9:
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 'o':
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 'C':
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'U':
        HAL_GPIO_WritePin(A,HIGH);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'D':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 't':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'S':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,HIGH);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'M':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,HIGH);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'T':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,HIGH);
        break;
    case 'W':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,HIGH);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'H':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,HIGH);
        HAL_GPIO_WritePin(D,LOW);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    case 'F':
        HAL_GPIO_WritePin(A,LOW);
        HAL_GPIO_WritePin(B,LOW);
        HAL_GPIO_WritePin(C,LOW);
        HAL_GPIO_WritePin(D,HIGH);
        HAL_GPIO_WritePin(E,LOW);
        HAL_GPIO_WritePin(F,LOW);
        HAL_GPIO_WritePin(G,LOW);
        break;
    default:
    	HAL_GPIO_WritePin(A,LOW);
		HAL_GPIO_WritePin(B,LOW);
		HAL_GPIO_WritePin(C,LOW);
		HAL_GPIO_WritePin(D,LOW);
		HAL_GPIO_WritePin(E,LOW);
		HAL_GPIO_WritePin(F,LOW);
		HAL_GPIO_WritePin(G,HIGH);
        break;
    }
}

void Segment_Set(uint8_t seg, uint8_t value)
{

    segment_value[seg] = value;

}

