/*
 * my_timer_8bit.c
 *
 * Created: 6/23/2019 4:17:52 PM
 *  Author: AVE-LAP-095
 */ 
#include "my_timer_8bit.h"

void my_timer_8bit_init(void)
{
	TCNT0 =0x00;
	TCCR0 |= (5<<CS00); 
}

void my_timer_8bit_delay(uint64 seconds)
{
	uint64 no_over_flow, i=1, no_ticks;
	no_ticks = seconds*(1000000/1024);
	no_over_flow = no_ticks/(0xff);
	OCR0= no_ticks % 0xff;
	i += no_over_flow;
	TCNT0 = 0x0000;
	do
	{
		while(!Get_Bit(TIFR,OCF0));
		Set_Bit(TIFR,OCF0);
		--i;
	}while(i);
	
}