/*
 * Motor.c
 *
 * Created: 7/21/2019 6:29:17 PM
 *  Author: AVE-LAP-062
 */ 


#include "timer.h"
#include "Motor_cfg.h"
#include "DIO.h"

void Motor_init(void)
{
	DIO_SetPinDirection(MOTOR1A,HIGH);
	DIO_SetPinDirection(MOTOR1B,HIGH);
	DIO_SetPinDirection(MOTOR2A,HIGH);
	DIO_SetPinDirection(MOTOR2B,HIGH);

	
}



void Set_Enable(void)
{
	DIO_SetPinDirection(ENABLE1,HIGH);
	DIO_SetPinDirection(ENABLE2,HIGH);
	DIO_WritePin(ENABLE1,HIGH);
	DIO_WritePin(ENABLE2,HIGH);
	
}

/********this function generate PWM for enable **********************************/
/********* it takes duty cycle of PWM as an input *******************************/

void Set_Enable_PWM(uint16 dutycycle1)
{
	uint16 X=(dutycycle1*255)/100;
	timer2_init_PWM(X);
}


void Forword_Step(void)
{
	
	Set_Enable_PWM(80);
	DIO_WritePin(MOTOR1A,HIGH);
	DIO_WritePin(MOTOR1B,LOW);
	
	DIO_WritePin(MOTOR2A,HIGH);
	DIO_WritePin(MOTOR2B,LOW);
	
}

/*
void Backword_Step(void)
{
	Set_Enable_PWM(80, 80);
	DIO_WritePin(MOTOR1A,LOW);
	DIO_WritePin(MOTOR1B,HIGH);
	
	DIO_WritePin(MOTOR2A,LOW);
	DIO_WritePin(MOTOR2B,HIGH);
	
}
*/

/*

void Left_Step(void)
{
	Set_Enable_PWM(50, 95);
	 
	DIO_WritePin(MOTOR1A,HIGH);
	DIO_WritePin(MOTOR1B,LOW);
	
	DIO_WritePin(MOTOR2A,HIGH);
	DIO_WritePin(MOTOR2B,LOW);
	
}


void Right_Step(void)
{
	Set_Enable_PWM(95, 50);
	
	DIO_WritePin(MOTOR1A,HIGH);
	DIO_WritePin(MOTOR1B,LOW);
	
	DIO_WritePin(MOTOR2A,HIGH);
	DIO_WritePin(MOTOR2B,LOW);
	
}
*/
void Brake(void)
{
	
	DIO_WritePin(MOTOR1A,LOW);
	DIO_WritePin(MOTOR1B,LOW);
	
	DIO_WritePin(MOTOR2A,LOW);
	DIO_WritePin(MOTOR2B,LOW);
	
}