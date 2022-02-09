/*
 * SPI_drive.h
 *
 * Created: 8/5/2019 11:02:37 AM
 *  Author: AVE-LAP-095
 */ 


#ifndef SPI_DRIVE_H_
#define SPI_DRIVE_H_

#include <string.h>

#include <avr/io.h>
#include "stdint.h"


#define SS 4		// Slave Select        is Bit No.4
#define MOSI 5 		// Master Out Slave In is Bit No.5
#define MISO 6		// Master In Slave Out is Bit No.6
#define SCK 7 		// Shift Clock         is Bit No.7

void SPI_init(const int8_t * ED_interrupt,const int8_t * M_Slave,const uint8_t prescaler);
void SPI_Write(uint8_t data);
void SPI_Write_buffer(uint8_t * data, uint8_t length);
uint8_t SPI_Read(uint8_t old_data);
void SPI_read_buffer(uint8_t * data, uint8_t length);
void Spi_Initialization_Master (void);
uint8_t log2(uint8_t);


#endif /* SPI_DRIVE_H_ */