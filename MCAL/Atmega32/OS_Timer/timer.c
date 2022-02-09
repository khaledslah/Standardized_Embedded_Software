/*
 * timer.c
 *
 *  Created on: Aug 20, 2019
 *      Author: AVE-LAP-095
 */

#include "timer.h"

/*used static data*/
static void (*call_back_function)()='\0';

/*the implementation of systick interrupt is to set call the callback function which sets the flag*/
 ISR(TIMER1_OVF_vect){
    (*call_back_function)();
}

/*initialize the systick with tick time defined with macro OS_TICK_INTERVAL_MSEC defined in timer.h*/
void systick_OS_init(){
    TCCR1A = 3<<WGM10; //enable PWM mode so that overflow occurs when value at ocr1A register is reached
	TCCR1B |= (1<<CS10) | (3<<WGM12);	// initialize timer1 (16 bit register) with prescaller 1  
	OCR1A = SysClock/1000ul*OS_TICK_INTERVAL_MSEC; //set value for ocr1a register to overflow at defined microseconds and invokes the interrupt
	TIMSK |= 1<<TOIE1; //enable interrupt for overflow 
    //
    // Enable interrupts to the processor.
    //
    sei();
}
/*saves the pointer to the callback function*/
void save_call_back(void (*call_back_pointer)()){
    call_back_function=call_back_pointer;
}
