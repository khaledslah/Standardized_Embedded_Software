/*
 * DIO.c
 *
 * Created: 6/23/2019 3:34:24 PM
 *  Author: AVE-LAP-095
 */ 
#include "DIO.h"
void DIO_WritePin(uint8 PinNum,uint8 PinValue){
	DIO_SetPinDirection(PinNum,1);
	if(PinValue ==1){
		if (PinNum<8)
		{
			Set_Bit(PORTA,PinNum);
		}
		else if (PinNum<16)
		{
			Set_Bit(PORTB,PinNum-8);
		}
		else if (PinNum<24)
		{
			Set_Bit(PORTC,PinNum-16);
		}
		else if (PinNum<32)
		{
			Set_Bit(PORTD,PinNum-24);
		}
	}
	else if (PinValue ==0){
		if (PinNum<8)
		{
			Clear_Bit(PORTA,PinNum);
		}
		else if (PinNum<16)
		{
			Clear_Bit(PORTB,PinNum-8);
		}
		else if (PinNum<24)
		{
			Clear_Bit(PORTC,PinNum-16);
		}
		else if (PinNum<32)
		{
			Clear_Bit(PORTD,PinNum-24);
		}
	}
}
uint8 DIO_ReadPin(uint8 PinNum){
	uint8 value = 0xff;
	DIO_SetPinDirection(PinNum,0);
	if (PinNum<8)
	{
		value=Get_Bit(PINA,PinNum);
	}
	else if (PinNum<16)
	{
		value=Get_Bit(PINB,PinNum-8);
	}
	else if (PinNum<24)
	{
		value=Get_Bit(PINC,PinNum-16);
	}
	else if (PinNum<32)
	{
		value=Get_Bit(PIND,PinNum-24);
	}
	return value;
}
void DIO_SetPinDirection(uint8 PinNum,uint8 PinDirection){
	if(PinDirection ==1){
		if (PinNum<8)
		{
			Set_Bit(DDRA,PinNum);
		}
		else if (PinNum<16)
		{
			Set_Bit(DDRB,PinNum-8);
		}
		else if (PinNum<24)
		{
			Set_Bit(DDRC,PinNum-16);
		}
		else if (PinNum<32)
		{
			Set_Bit(DDRD,PinNum-24);
		}
	}
	else if (PinDirection ==0){
		if (PinNum<8)
		{
			Clear_Bit(DDRA,PinNum);
		}
		else if (PinNum<16)
		{
			Clear_Bit(DDRB,PinNum-8);
		}
		else if (PinNum<24)
		{
			Clear_Bit(DDRC,PinNum-16);
		}
		else if (PinNum<32)
		{
			Clear_Bit(DDRD,PinNum - 24);
		}
	}
	
}
