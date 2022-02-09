/*
 * KeyPad.c
 *
 * Created: 9/4/2019 3:36:47 PM
 *  Author: AVE-LAP-052
 */ 

#include "KeyPad.h"

uint8_t KeyPad_vidInit(void)
{
	static uint8_t state = INIT_STATE;
	uint8_t return_status = PENDING;
	switch(state)
	{
		case INIT_STATE : 
		{
			DIO_WritePin(18,HIGH);
			DIO_WritePin(19,HIGH);
			DIO_WritePin(20,HIGH);
			DIO_SetPinDirection(18,INPUT);
			DIO_SetPinDirection(19,INPUT);
			DIO_SetPinDirection(20,INPUT);
			DIO_WritePin(21,HIGH);
			DIO_WritePin(22,HIGH);
			DIO_WritePin(23,HIGH);
			return_status = OK;
			break;
		}
		default: break;
	}
	return return_status; 
}

uint8_t KeyPad_vidGetSwitch(uint8_t * pressed_switch)
{
	static uint8_t state = INIT_STATE;
	static uint8_t IpCounter = START_ROW; 
	static uint8_t OutCounter = START_COLUMN;
	static uint8_t SwitchNumber = LOW;
	static uint8_t RowValue = HIGH;
	uint8_t return_status = PENDING;
	
	switch(state)
	{
		case INIT_STATE :
		
			if (OutCounter < END_COLUMN)
			{
				DIO_WritePin(OutCounter,LOW);
				state++;
			}
			else
			{
				SwitchNumber = LOW;
				RowValue = HIGH;
				OutCounter = START_COLUMN;
				state = INIT_STATE;
			}
			return_status = PENDING;
			break;
		
		
		case STATE_TWO :
		
			if(IpCounter < START_COLUMN)
			{
				RowValue = DIO_ReadPin(IpCounter);
				if(RowValue == LOW)
				{
					SwitchNumber = (OutCounter-START_COLUMN) + ((IpCounter-START_ROW)*KEYPAD_MATRIX) + HIGH;
					IpCounter=END_ROW;
				}
				IpCounter++;
			}
			else
			{
				IpCounter = START_ROW;
				DIO_WritePin(OutCounter,HIGH);
				OutCounter++;
				state++;
			}
			return_status = PENDING;
			break;
		
		
		case STATE_THREE: 
		
			if((SwitchNumber >= HIGH)&&(SwitchNumber <= 9))
			{
				return_status = OK;
				*pressed_switch = SwitchNumber;
				SwitchNumber = 0;
			}
			else if(SwitchNumber == 0)
			{
				return_status = PENDING;
			}  
			else
			{
				return_status = PENDING;
				SwitchNumber = 0;
			}
			state = INIT_STATE;
			
			break;
		
	}
	
	return return_status;
}

