/*
 * SPI_drive.c
 *
 * Created: 8/5/2019 11:02:26 AM
 *  Author: AVE-LAP-095
 */ 

#include "SPI_drive.h"
#include <math.h>


void Spi_Initialization_Master (void)
{
	DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS) ;
	DDRB &= ~(1<<MISO);
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);			//Enable SPI, Set as Master
	SPSR |= (1<<SPI2X);								//set sck=1MHZ
}


void SPI_init(const int8_t * ED_interrupt,const int8_t * M_Slave,const uint8_t prescaler){
	uint8_t log_base2_prescaler=0;
	log_base2_prescaler = log2(prescaler);
	SPCR=0;
	
	/* Assign bits of master/slave*/
	if (strcmp (M_Slave, "master") == 0)
	{
		SPCR |= 1<<MSTR;
	}
	else {}
		
		/* Assign bits of enable/disable interrupt */
		if (strcmp (ED_interrupt, "enable_interrupt") == 0)
		{
			SPCR |= 1<<SPIE;
		}
		
		/* Assign bits of prescaler */
		if ((log_base2_prescaler >=1) && (log_base2_prescaler <=7)){
		if(log_base2_prescaler % 2 == 0){ 
			SPCR |= (log_base2_prescaler/2-1)<<SPR0;
			
		}
		else if (log_base2_prescaler % 2 == 1)
		{
			SPCR |= (log_base2_prescaler/2)<<SPR0;
			SPSR |= 1<<SPI2X;
		}
		else{}
		}
		SPCR |= 1<<SPE;
}

void SPI_Write(uint8_t data)		/* SPI write data function */
{
	uint8_t flush_buffer;
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	flush_buffer = SPDR;		/* Flush received data */
	/* Note: SPIF flag is cleared by first reading SPSR (with SPIF set) and then accessing SPDR hence flush buffer used here to access SPDR after SPSR read */
}

void SPI_Write_buffer(uint8_t * data, uint8_t length)		
{
	uint8_t i=0;
	for (i=0; i<length; i++)
	{
		SPI_Write(data[i]);
	}
}

uint8_t SPI_Read(uint8_t old_data)				/* SPI read data function */
{
	SPDR = old_data;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}
void SPI_read_buffer(uint8_t * data, uint8_t length)
{
	uint8_t i=0;
	for (i=0; i<length; i++)
	{
		data[i]=SPI_Read(0xff);
	}
}
uint8_t log2(uint8_t x){
	return log(x)/log(2);
}