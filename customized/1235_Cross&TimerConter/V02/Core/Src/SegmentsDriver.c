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
    if (++segment_position > position_Level)
        segment_position = 0;

    HAL_GPIO_WritePin(SEG_H1, LOW);
    HAL_GPIO_WritePin(SEG_H2, LOW);
    HAL_GPIO_WritePin(SEG_M1, LOW);
    HAL_GPIO_WritePin(SEG_M2, LOW);
    HAL_GPIO_WritePin(SEG_S1, LOW);
    HAL_GPIO_WritePin(SEG_S2, LOW);

    HAL_GPIO_WritePin(SEG_DAY, LOW);

    Segment_Map(segment_value[segment_position]);

    switch (segment_position)
    {
    case 0:
        HAL_GPIO_WritePin(SEG_H1, HIGH);
        break;
    case 1:
        HAL_GPIO_WritePin(SEG_H2, HIGH);
        break;
    case 2:
        HAL_GPIO_WritePin(SEG_M1, HIGH);
        break;
    case 3:
        HAL_GPIO_WritePin(SEG_M2, HIGH);
        break;
    case 4:
        HAL_GPIO_WritePin(SEG_S1, HIGH);
        break;
    case 5:
        HAL_GPIO_WritePin(SEG_S2, HIGH);
        break;
    case 6:
        HAL_GPIO_WritePin(SEG_DAY, HIGH);
        break;
    default:
        HAL_GPIO_WritePin(SEG_H1, LOW);
        HAL_GPIO_WritePin(SEG_H2, LOW);
        HAL_GPIO_WritePin(SEG_M1, LOW);
        HAL_GPIO_WritePin(SEG_M2, LOW);
        HAL_GPIO_WritePin(SEG_S1, LOW);
        HAL_GPIO_WritePin(SEG_S2, LOW);
        HAL_GPIO_WritePin(SEG_DAY, LOW);
        break;
    }
}

void Segment_Map(uint8_t value)
{
    switch (value)
    {
    case 'N':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 0:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 1:
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 2:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 3:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 4:
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 5:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 6:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 7:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 8:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 9:
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'o':
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'C':
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'U':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'P':
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'd':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'n':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'D':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
     case 'f':
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'A':
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'r':
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'u': // sunday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, HIGH);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'M': // munday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, HIGH);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'T': // tuseday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    case 'W': // wednesday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, HIGH);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 't': // thursday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, HIGH);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'F': // friday
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, HIGH);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;
    case 'S': // saturday
        HAL_GPIO_WritePin(A, HIGH);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, LOW);
        break;

    default:
        HAL_GPIO_WritePin(A, LOW);
        HAL_GPIO_WritePin(B, LOW);
        HAL_GPIO_WritePin(C, LOW);
        HAL_GPIO_WritePin(D, LOW);
        HAL_GPIO_WritePin(E, LOW);
        HAL_GPIO_WritePin(F, LOW);
        HAL_GPIO_WritePin(G, HIGH);
        break;
    }
}

void Segment_Set(uint8_t seg, uint8_t value)
{

    segment_value[seg] = value;
}

uint8_t GET_DOW(uint8_t Date_of_Week)
{
    uint8_t dow;
    switch (Date_of_Week)
    {
    case 1:
        dow = 'S';
        break;
    case 2:
        dow = 'u';
        break;
    case 3:
        dow = 'M';
        break;
    case 4:
        dow = 'T';
        break;
    case 5:
        dow = 'W';
        break;
    case 6:
        dow = 't';
        break;
    case 7:
        dow = 'F';
        break;
    default:
        dow = 'S';
        break;
    }
    return dow;
}
