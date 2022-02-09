/*
 * UART.c
 *
 * Created: 8/5/2019 2:52:56 PM
 *  Author: AVE-LAP-039
 */ 

#include "UART.h"
#include "DIO.h"
#define F_CPU 16000000
#define  BAUD	9600

#define  BAUDRATE	(((F_CPU / (BAUD * 16UL-1))) )
			
void UART_init()
{
	DIO_SetPinDirection(24,Input);				/* Input => receive pin */
	DIO_SetPinDirection(25,Output);				/* Output => transmit pin */
	
	UCSRB|= ((1<<TXEN)|(1<<RXEN));                /* enable receiver and transmitter */
	UCSRC|= ((1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1));   /* 8bit data format, no Parity bit, 1 stop bit */
		
	UBRRL = BAUDRATE;						/* set baud rate */
	UBRRH = (BAUDRATE>>8);				/* shift the register right by 8 bits*/
	

}


// #define F_CPU (16000000UL)
// #define BAUD	9600								// define baud
// #define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)			// set baud rate value for UBRR
// void Usart_Initialization()
// {
// 	UBRRL= BAUDRATE;											//Put baud rate into UBRR
// 	UCSRB|=(1U<<TXEN)|(1U<<RXEN);								//Enable RX and TX pins
// 	UCSRC|=(1U<<UCSZ1)|(1U<<UCSZ0)|(1U<<URSEL);					//8bit , select UCSRC
// }
void UART_send_byte(uint8_t data_send)
{


	  /* Transmit data */
	  UDR = data_send;
	  	  /* Wait until last byte has been transmitted */
	  	  while(!(UCSRA &(1<<UDRE)));
	 
}
void UART_send_one_byte_decimal(uint8_t number){
	uint8_t j=0;
			   for(j=100;j>=1;j/=10){
				   UART_send_byte(number/j+'0');
				   number%=j;
			   }
}
uint8_t UART_receive_byte(void)
{
	/*wait while data is being received*/
	 while((UCSRA &(1<<RXC)) == 0);
	 
	 /*return 8-bit data*/
	 return UDR;
}


/* send number of bytes based on the length of the argument  */
void UART_send_data_from_array_by_specified_length(uint8_t* string_to_send, uint8_t length)
{
	for (int i = 0 ; i < length ; i++) 
	{
		UART_send_byte(string_to_send[i]);
		i++;
	}
}

void UART_send_string(uint8_t string_to_send[])
{
	int i =0;
	
	while (string_to_send[i] != '\0')
	{
		UART_send_byte(string_to_send[i]);
		i++;
	}
}