/*
 * timer.h
 *
 * Created: 8/21/2019 4:59:14 PM
 *  Author: AVE-LAP-005
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "my_std_int.h"

void Timer0_Normal_Init(uint8 time_ms);
extern void (*callback_to_setFlag) () ;
void setCallBack(void(*a_ptr)(void));
extern void timer2_init_PWM(uint8 compareValue);



#endif /* TIMER_H_ */