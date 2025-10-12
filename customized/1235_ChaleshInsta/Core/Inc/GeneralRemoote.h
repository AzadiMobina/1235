/*
 * GeneralRemoote.h
 *
 *  Created on: Feb 15, 2025
 *      Author: Mobina
 */

#ifndef INC_GENERALREMOOTE_H_
#define INC_GENERALREMOOTE_H_

#include "IRRemote.h"
// #include "Variable.h"
// #include "Definition.h"
#include "i2c.h"
#include "SegmentsDriver.h"


void Haamin_Remote(uint16_t action, uint8_t workMode);
uint8_t Haamin_NumberKey (uint16_t numberKey);
void Buzz(uint16_t time);

#endif /* INC_GENERALREMOOTE_H_ */
