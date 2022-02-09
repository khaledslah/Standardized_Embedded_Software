/*
 * my_timer_8bit.h
 *
 * Created: 6/23/2019 4:18:04 PM
 *  Author: AVE-LAP-095
 */ 


#ifndef MY_TIMER_8BIT_H_
#define MY_TIMER_8BIT_H_

#include "my_std_int.h"
#include "bit_manipulation.h"
#include <avr/io.h>

void my_timer_8bit_init(void);
void my_timer_8bit_delay(uint64 seconds);


#endif /* MY_TIMER_8BIT_H_ */