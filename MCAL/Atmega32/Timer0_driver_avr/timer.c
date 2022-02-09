/*
 * timer.c
 *
 * Created: 8/21/2019 4:58:59 PM
 *  Author: AVE-LAP-005
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "my_std_int.h"
# define F_CPU 16000000UL

static void (*callback_to_setFlag) () =0 ;

void Timer0_Normal_Init(uint8 time_ms){

	TCNT0 = 0;
	OCR0 = time_ms*63;
	TCCR0 = (1<<WGM01) | (1<<CS02);
	TIMSK |= (1<<OCIE0) ;
	sei();
}

void setCallBack(void(*a_ptr)(void))
{
	
	callback_to_setFlag = a_ptr;
}

ISR (TIMER0_COMP_vect){
	
	
	if(callback_to_setFlag != 0)
	{
		
		(*callback_to_setFlag)();
	}

}


void timer2_init_PWM(uint16 compareValue)
{
	/*set fast PWM mode with non-inverted output*/
	TCCR2 = (1<<WGM20) | (1<<WGM21) | (1<<COM21) | (1<<CS20);
	DDRD|=(1<<7);  /*set OC0 pin as output*/
	OCR2=compareValue;
}
