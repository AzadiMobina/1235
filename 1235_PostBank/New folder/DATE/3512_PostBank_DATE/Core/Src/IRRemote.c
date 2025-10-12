/*
 * IRRemote.c
 *
 *  Created on: Feb 6, 2025
 *      Author: Amin
 */

#include "IRRemote.h"

// Global Variables
uint16_t ir_TimeValue[IR_FRAME_SIZE]; // Store pulse times
uint8_t ir_ArrayIndex = 0;            // Index for storing values
uint8_t ir_DataReady = 0;
uint16_t ir_Data = 0;
uint8_t ir_running = 0;

void IR_SetTimeArrayValues(uint16_t timevalue)// daryaft , zakhire zaman har palse 
{
  if (ir_running == 2)
  {
    ir_TimeValue[ir_ArrayIndex] = timevalue;
    if (++ir_ArrayIndex >= IR_FRAME_SIZE)
    {
      ir_ArrayIndex = 0;
      ir_running = 0;
      uint8_t res = Ir_AnalyzeTimeArrayValues();
      if (res == 13)
      {
        ir_DataReady = 1;
      }
    }
  }
  else if (ir_running == 1)
  {
    ir_running = 2;
  }
}

// NEC IR Data Analysis Function
uint16_t Ir_AnalyzeTimeArrayValues(void)
{

  uint8_t address = 0, address_inv = 0, command = 0, command_inv = 0;

  // Validate NEC Frame Start Pulse (9ms + 4.5ms)
  if (ir_TimeValue[0] < 12500 || ir_TimeValue[0] > 14500)
  {
    return 1; // Invalid NEC frame
  }

  // Decode 32-bit NEC frame (Address + Address_inv + Command + Command_inv)
  for (int i = 0; i <= 8; i++)
  {
    if (ir_TimeValue[i + 1 + 0] > 2000)
      address |= (1 << i); // Logical 1 threshold
    if (ir_TimeValue[i + 1 + 8] > 2000)
      address_inv |= (1 << i);
    if (ir_TimeValue[i + 1 + 16] > 2000)
      command |= (1 << i);
    if (ir_TimeValue[i + 1 + 24] > 2000)
      command_inv |= (1 << i);
  }

  // Validate Address and Command Integrity
  if ((address ^ address_inv) == 0xFF && (command ^ command_inv) == 0xFF)
  {
    // NEC Protocol Successfully Decoded
    ir_Data = (address << 8) + command;
    return 13;
  }

  return 0;
}

uint16_t Ir_GetData(void)
{
  if (!ir_DataReady)
    return 0;
  else
  {
    ir_DataReady = 0;
    return ir_Data;
  }
}

void Ir_ResetRunning(void)
{
  ir_running = 1;
  ir_ArrayIndex = 0;
}
