/*
 * User_tasks.h
 *
 *  Created on: Jul 3, 2019
 *      Author: AVE-LAP-44
 */

#ifndef USER_TASKS_H_
#define USER_TASKS_H_

/*include required files*/
#include <stdint.h>
#include "../MCAL/DIO.h"
#include <util/delay.h>
#include "global.h"
#include "KeyPad.h"
#include "LCD.h"
#include "OS_SPI_drive.h"

#include "../Kernal/scheduler.h"

#define SENDER_ECU 1
#define  F_CPU 16000000ul

/*declare functions*/
void vTASK_Init(void);
void Display_Question(void);
void Display_Result_Logo(void);
void Display_Answer_Options(void);
void vKEY_Init(void);
void vKEY_Get(void);
void vWrong_Answer(void);
void Final_Task(void);
void task_not_created(void);
uint8_t get_notify(uint8_t task_to_notify);
void give_notify(uint8_t task_to_notify);

#endif /* USER_TASKS_H_ */
