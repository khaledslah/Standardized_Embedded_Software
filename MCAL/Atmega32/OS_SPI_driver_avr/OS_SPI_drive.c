/*
 * SPI_drive.c
 *
 * Created: 8/5/2019 11:02:26 AM
 *  Author: AVE-LAP-095
 */ 

#include "OS_SPI_drive.h"



void SPI_init(const int8_t * ED_interrupt,const int8_t * M_Slave,const uint8_t prescaler){
	uint8_t log_base2_prescaler=0;
	log_base2_prescaler = log_base2(prescaler);
	SPCR=0;
	
	/* Assign bits of master/slave*/
	if (strcmp (M_Slave, "master") == 0)
	{
		DIO_SetPinDirection(SPI_mosi,OUTPUT);
		DIO_SetPinDirection(SPI_miso,INPUT);
		DIO_SetPinDirection(SPI_clk,OUTPUT);
		DIO_SetPinDirection(SPI_ss,OUTPUT);
		SPCR |= 1<<MSTR;
	}
	else {
		DIO_SetPinDirection(SPI_mosi,INPUT);
		DIO_SetPinDirection(SPI_miso,OUTPUT);
		DIO_SetPinDirection(SPI_clk,INPUT);
		DIO_SetPinDirection(SPI_ss,INPUT);	
	}
		
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

uint8_t OS_SPI_Write(uint8_t data)		/* SPI write data function */
{
	uint8_t flush_buffer;
	static uint8_t state = INIT_STATE;
	uint8_t status = PENDING;
		switch(state){
			case INIT_STATE: SPDR = data;/* Write data to SPI data register */
			 status = PENDING;
			 state++; break;
			case STATE_TWO: if(Get_Bit(SPSR,SPIF)){state++;} /* Wait till transmission complete */else {}status = PENDING; break;
			case STATE_THREE:	flush_buffer = SPDR;/* Flush received data */state++;status = PENDING; break;
			case STATE_FOUR: state =INIT_STATE; status = OK; break;
		}
	return status;		
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

uint8_t OS_SPI_Read(uint8_t * recieved_data)				/* SPI read data function */
{
		static uint8_t state = INIT_STATE;
		uint8_t status = PENDING;
		switch(state){
			case INIT_STATE: if((SPSR & (1<<SPIF))){state++;} /* Wait till transmission complete */else {}status = PENDING;break;
			//case STATE_TWO:	/* Flush received data */state++;status = PENDING; break;
			case STATE_TWO: *recieved_data = SPDR;SPDR=1;state =INIT_STATE; status = OK; break;
		}
		return status;
}
void SPI_read_buffer(uint8_t * data, uint8_t length)
{
	uint8_t i=0;
	for (i=0; i<length; i++)
	{
		data[i]=SPI_Read(0xff);
	}
}
uint8_t log_base2(uint8_t x){
	return log(x)/log(2);
}