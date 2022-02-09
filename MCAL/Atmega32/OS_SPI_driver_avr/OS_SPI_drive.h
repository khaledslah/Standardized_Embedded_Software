/*
 * SPI_drive.h
 *
 * Created: 8/5/2019 11:02:37 AM
 *  Author: AVE-LAP-095
 */

#ifndef OS_SPI_DRIVE_H_
#define OS_SPI_DRIVE_H_

#include <string.h>
#include <avr/io.h>
#include "stdint.h"

#include "../MCAL/bit_manipulation.h"

#include "../MCAL/DIO.h"

#include <math.h>
#include "global.h"

#define SPI_ss 12
#define SPI_mosi 13
#define SPI_miso 14
#define SPI_clk 15

#define OUTPUT 1
#define INPUT 0

void SPI_init(const int8_t * ED_interrupt, const int8_t * M_Slave,
		const uint8_t prescaler);
uint8_t OS_SPI_Write(uint8_t data);
void SPI_Write_buffer(uint8_t * data, uint8_t length);
uint8_t OS_SPI_Read(uint8_t * recieved_data);
void SPI_read_buffer(uint8_t * data, uint8_t length);
uint8_t log_base2(uint8_t);

#endif /* OS_SPI_DRIVE_H_ */
