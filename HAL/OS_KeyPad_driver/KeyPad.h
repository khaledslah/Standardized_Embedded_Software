/*
 * KeyPad.h
 *
 * Created: 9/4/2019 3:37:06 PM
 *  Author: AVE-LAP-052
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../MCAL/DIO.h"
#include "../HAL/global.h"

extern uint8_t answer;
#define HIGH 1
#define LOW 0
#define INPUT 0

#define START_ROW 18
#define END_ROW 20
#define START_COLUMN 21
#define END_COLUMN 24
#define KEYPAD_MATRIX 3

uint8_t KeyPad_vidInit(void);
uint8_t KeyPad_vidGetSwitch(uint8_t * pressed_switch);

#endif /* KEYPAD_H_ */
