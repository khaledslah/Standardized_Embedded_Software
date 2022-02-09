/*
 * my_pwm_8bit.c
 *
 * Created: 6/23/2019 4:22:24 PM
 *  Author: AVE-LAP-095
 */ 

#include "my_pwm_8bit.h"

void my_pwm_8bit(uint8 dutycycle,uint8 time){
	uint8 time_on =dutycycle*time/100;
	uint8 time_off =time-time_on;
	DIO_WritePin(13,1);
	my_timer_8bit_delay(time_on);
	DIO_WritePin(13,0);
	my_timer_8bit_delay(time_off);
	
}