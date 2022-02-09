/*
 * DIO.h
 *
 * Created: 6/23/2019 3:34:42 PM
 *  Author: AVE-LAP-095
 */

#ifndef DIO_H_
#define DIO_H_
#include "../MCAL/my_std_int.h"
#include <avr/io.h>
#include "../MCAL/bit_manipulation.h"
void delay(uint32 n);
void DIO_WritePin(uint8 PinNum, uint8 PinValue);
uint8 DIO_ReadPin(uint8 PinNum);
void DIO_SetPinDirection(uint8 PinNum, uint8 PinDirection);

#endif /* DIO_H_ */
