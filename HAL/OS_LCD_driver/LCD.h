/*
 * LCD.h
 *
 * Created: 9/2/2019 1:01:05 PM
 *  Author: AVE-LAP-095
 */

#ifndef LCD_H_
#define LCD_H_

#define  F_CPU 16000000ul
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>
#include "../Kernal/scheduler.h"
#include "../MCAL/DIO.h"
#include "global.h"

#define LCD_LINE_SIZE 16
#define LCD_REGISTER_PIN 1
#define LCD_RW_PIN 2
#define LCD_ENABLE_PIN 3
#define LCD_DATA_PORT PORTA
#define DATA 1
#define CMD 0
#define READ 1
#define WRITE 0
#define HIGH 1
#define LOW 0

void vLCDinit(void);
void vLCDsendcommand(uint8_t cmd);
void vLCDdisplaychar(uint8_t data);
uint8_t vLCDdisplaystring(uint8_t * data, uint8_t size);
void vLCDclear(void);
void vLCDgotoRowcolumn(uint8_t row, uint8_t column);
uint8_t vLCDcustomchar(uint8_t loc, uint8_t *msg);
void SadFace(void);
void SmilyFace(void);
#endif /* LCD_H_ */
