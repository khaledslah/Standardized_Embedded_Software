/*
 * timer.h
 *
 *  Created on: Aug 20, 2019
 *      Author: AVE-LAP-095
 */

#ifndef MCAL_TIMER_H_
#define MCAL_TIMER_H_

/*include required files*/
#include <avr/io.h>
#include <avr/interrupt.h>

/*definitions*/
#define OS_TICK_INTERVAL_MSEC 1
#define SysClock	16000000ul

/*declare functions*/
void systick_OS_init();
void save_call_back(void(*call_back_pointer)());

#endif /* MCAL_TIMER_H_ */
