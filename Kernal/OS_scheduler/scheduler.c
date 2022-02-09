/*include required files*/
#include "scheduler.h"

/*declare static functions*/
static void Sort_tasks();
static void sys_tick_callback();
static uint8_t suspendflag = DISABLED;
static uint8_t delayflag = DISABLED;
static uint16_t milliseconds = ZERO;

/*used static data*/
static uint8_t NewTickFlag = DISABLED;
static task tasks[MAX_NUM_TASKS];

/*this function send the call back pointer to the timer
 and initialize the array os tasks with max number declared in the header MAX_NUM_TASKS
 and initial values declared in the header INIT_TASK_STRUCT*/
void SchedulerInit()
 {
	uint8_t index = ZERO;
	save_call_back(sys_tick_callback);

	for (index = ZERO; index < MAX_NUM_TASKS; index++) {
		INIT_TASK_STRUCT(index);
	}
}
/*this function start by arranging the created tasks according to priority
 then start executing tasks accoriding to higher priority -note: the lower the number the higher the priority-*/
void SchedulerStart() 
{
	uint8_t index = ZERO;
	
	/*sort the tasks from higher priority to lower priority*/
	Sort_tasks();
	
	/*initializer systick interrupt with tick time of macro OS_TICK_INTERVAL_MSEC defined in timer.h*/
	systick_OS_init();
	
	/*enter the infinite loop*/
	while (1) 
	{
		/*checks if new tick occurred and flag is set by callback function*/
		if (NewTickFlag == ENABLED)
		 {
			/*reduces the remaining ticks of tasks that are in block state*/
			for (index = 0; index < MAX_NUM_TASKS; index++)
			 {
				if (tasks[index].task_remaining_ticks > 0)
					tasks[index].task_remaining_ticks--;
			}
			/*start looping of tasks queue sorted according to higher priority and checks if it is in ready state
			 -note: ready state means task_remaining_ticks equals 0- then execute it and get out of the loop*/
			for (index = 0; index < MAX_NUM_TASKS; index++) 
			{
				if ((tasks[index].task_pointer != '\0') && (tasks[index].task_remaining_ticks == 0))
				{
					tasks[index].task_pointer();
					if (suspendflag) 
					{
						tasks[index].task_pointer = '\0';
						suspendflag = 0;
					}
					if (delayflag == ENABLED) 
					{
						tasks[index].task_remaining_ticks = milliseconds;
						delayflag = DISABLED;
					} 
					else if (delayflag == DISABLED) 
					{
						tasks[index].task_remaining_ticks = tasks[index].task_periodicity;
					}

					/*makes i equals MAX_NUM_TASKS to get out of the loop and that is instead of using break as it is bad use in embedded*/
					index = MAX_NUM_TASKS;
				}
			}
			/*clear the flag and wait for systick to set the flag*/
			NewTickFlag = DISABLED;
		}
	}
}

/*the callback function called by the systick interrupt to set the flag*/
void sys_tick_callback() 
{
	NewTickFlag = ENABLED;
}

/*function to ass new task by the application and returns -1 if failed*/
int8_t scheduler_Add_Task(void(*task)(void), uint64_t periodicity,int8_t priority) 
{
	static uint32_t number_of_tasks = ZERO;
	if (number_of_tasks < MAX_NUM_TASKS - 1)
	 {
		tasks[number_of_tasks].task_pointer = task;
		tasks[number_of_tasks].task_priority = priority;
		tasks[number_of_tasks++].task_periodicity = periodicity;

		return 1;
	} 
	else 
	{
		return -1;
	}
}

/*A function to sort the tasks according to higher priority using bubble sort algorithm*/
void Sort_tasks() {
	uint8_t index, second_index;
	for (index = ZERO; index < MAX_NUM_TASKS - ONE; index++)

		// Last index elements are already in place
		for (second_index = ZERO; second_index < MAX_NUM_TASKS - index - ONE; second_index++)
			if ((tasks[second_index].task_priority > tasks[second_index + ONE].task_priority)
					&& (tasks[second_index + ONE].task_priority > ZERO)) {
				task temp = tasks[second_index];
				tasks[second_index] = tasks[second_index + ONE];
				tasks[second_index + ONE] = temp;
			}
}

void vtasksuspend(void) 
{
	suspendflag = ENABLED;
}

void vtaskdelay(uint16_t milsec) 
{
	milliseconds = milsec;
	delayflag = ENABLED;
}