#ifndef KERNAL_SCHEDULER_H_
#define KERNAL_SCHEDULER_H_

/*include required files*/
#include "../MCAL/timer.h"
#include "../HAL/global.h"
#include <stdint.h>

/*definitions*/
#define MAX_NUM_TASKS   10
#define INIT_TASK_STRUCT(i)    tasks[i].task_pointer='\0'; tasks[i].task_periodicity=0;tasks[i].task_priority=-1; tasks[i].task_remaining_ticks=0; tasks[i].task_delay_ticks=0


/*typedef structure of tasks and call it tasks*/
typedef struct {
	void (*task_pointer)(void);
	uint64_t task_periodicity;
	int8_t task_priority;
	uint64_t task_remaining_ticks;
	uint64_t task_delay_ticks;
} task;

/*declare functions*/
void SchedulerStart(void);
void SchedulerInit(void);
int8_t scheduler_Add_Task(void(*task)(void), uint64_t periodicity,
int8_t task_priority);
void vtasksuspend(void);
void vtaskdelay(uint16_t milsec);
#endif /* KERNAL_SCHEDULER_H_ */
