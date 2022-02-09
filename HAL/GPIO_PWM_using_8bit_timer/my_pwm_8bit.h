/*
 * my_pwm_8bit.h
 *
 * Created: 6/23/2019 4:22:13 PM
 *  Author: AVE-LAP-095
 */ 


#ifndef MY_PWM_8BIT_H_
#define MY_PWM_8BIT_H_

#include "my_timer_8bit.h"
#include "my_std_int.h"
#include <avr/io.h>
#include "bit_manipulation.h"
#include "DIO.h"

void my_pwm_8bit(uint8 dutycycle,uint8 time);



#endif /* MY_PWM_8BIT_H_ */