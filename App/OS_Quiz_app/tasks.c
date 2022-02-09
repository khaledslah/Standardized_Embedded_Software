/*this file has the tasks created by the user*/

#include "tasks.h"

/* --------------------------------- ENUMS -------------------------------------------*/

enum Logos 
{
	CORRECT = 1, 
	WRONG = 2, 
	SKIPPER = 3
};


enum tasks 
{
	LCD_INIT, 
	DISP_ANSW, 
	DISP_QUEST, 
	DISP_RES, 
	KEY_GET, 
	KEY_INIT,
	FINAL_TASK,
	WRONG_ANSW
};

/* ---------------------------------- Global Variables -------------------------------------------*/

uint8_t answer = ONE;
uint32_t correct_answers_counter = ZERO;
uint32_t result = ZERO;

uint8_t GLOBAL_DIS_ANS_get_notify = DISABLED;
uint8_t GLOBAL_DIS_QUEST_get_notify = DISABLED;
uint8_t GLOBAL_DIS_RES_get_notify = DISABLED;
uint8_t GLOBAL_KEY_get_get_notify = DISABLED;
uint8_t GLOBAL_KEY_init_get_notify = DISABLED;
uint8_t GLOBAL_LCD_init_get_notify = DISABLED;
uint8_t GLOBAL_FINAL_Task_get_notify = DISABLED;
uint8_t GLOBAL_WRONG_ANSWER_get_notify = DISABLED;
uint8_t SHARED_WRONG_ANSWER_A_DIS_QUEST_A_DIS_ANSW = DISABLED;
/* -------------- MACRO -------------------- MACROS -------------------------------------------*/
#define HIGH 1
#define LOW 0
#define INPUT 0
#define MAX_QUESTIONS 5
#define QUESTION_SIZE 16
#define ANSWER_SIZE 8
#define SPI_PRESC 16
#define ASCI_ZERO '0'
#define PIN_13 13
#define ALL_PORT 0xFF

/* --------------------------------- Tasks -------------------------------------------*/

#ifdef SENDER_ECU
void vTASK_Init(void) {
	static uint8_t state = INIT_STATE;
	uint8_t status = PENDING;
	switch (state)
	{
		case INIT_STATE:
		SPI_init("disable_interrupt","master",SPI_PRESC);
		state++;
		break;
		case STATE_TWO:
		status = KeyPad_vidInit();
		if (status == OK) {
			state++;
		}
		break;
		case STATE_THREE:
		DDRA = ALL_PORT;
		state++;
		break;
		
		case STATE_FOUR:
		vLCDsendcommand(Return_home);
		state++;
		break; /* Send for 4 bit initialization of LCD  */
		
		case STATE_FIVE:
		vLCDsendcommand(Two_lines_and_5_7_matrix_4_bit_mode);
		state++;
		break; /* 2 line, 5*7 matrix in 4-bit mode */
		
		case STATE_SIX:
		vLCDsendcommand(Display_on_cursor_blinking);
		state++;
		break; /* Display on cursor off */
		
		case STATE_SEVEN:
		vLCDsendcommand(Increment_cursor_shift_cursor_to_right);
		state++;
		break; /* Increment cursor (shift cursor to right) */
		
		case STATE_EIGHT:
		vLCDsendcommand(Clear_display_screen);
		state++;
		break;
		case STATE_NINE:
		vLCDdisplaychar('I');
		state++;
		break;				
		case STATE_TEN:
		give_notify(KEY_GET);
		vtasksuspend();
		break;
	}
}
void vKEY_Get(void) 
{
	uint8_t comming_status = PENDING;
	uint8_t temp_answer=ZERO;
	static uint8_t state = INIT_STATE;
	switch (state) 
	{
		case INIT_STATE :
		if (get_notify(KEY_GET)) {
			state++;
		}
		break;
		case STATE_TWO:
		comming_status = KeyPad_vidGetSwitch(&temp_answer);
		if (comming_status == OK) {
			vLCDdisplaychar('S');
			answer=temp_answer;
			state++;
		}
		break;		
		case STATE_THREE:
				
		comming_status = OS_SPI_Write(answer);
		if (comming_status == OK) {
			vLCDdisplaychar(answer+ASCI_ZERO);
			state++;
		}			
		break;
		case STATE_FOUR:
				vLCDdisplaychar('D');
		give_notify(KEY_GET);
		state = INIT_STATE;
		break;
	}
}
#else
void vTASK_Init(void) {
	static uint8_t state = ONE;
	uint8_t status = PENDING;
	switch (state)
	{
		case INIT_STATE :
		DDRA = ALL_PORT;
		state++;
		break;
		
		case STATE_TWO:
		vLCDsendcommand(Return_home);
		state++;
		break; /* Send for 4 bit initialization of LCD  */
		
		case STATE_THREE:
		vLCDsendcommand(Two_lines_and_5_7_matrix_4_bit_mode);
		state++;
		break; /* 2 line, 5*7 matrix in 4-bit mode */
		
		case STATE_FOUR:
		vLCDsendcommand(Display_on_cursor_blinking);
		state++;
		break; /* Display on cursor off */
		
		case STATE_FIVE:
		vLCDsendcommand(Increment_cursor_shift_cursor_to_right);
		state++;
		break; /* Increment cursor (shift cursor to right) */
		
		case STATE_SIX:
		vLCDsendcommand(Clear_display_screen);
		state++;
		break;
		
		case STATE_SEVEN:
		SPI_init("disable_interrupt","slave",SPI_PRESC);
		state++;
		break;
		case STATE_EIGHT:
		give_notify(DISP_QUEST);
		vtasksuspend();
		break;
	}
}
void vKEY_Get(void)
{
	uint8_t comming_status = PENDING;
	uint8_t temp_answer = ONE;
	static uint8_t state = INIT_STATE;
	switch (state) {
		case INIT_STATE :
		if (get_notify(KEY_GET)) {
			state++;
		}
		break;
		case STATE_TWO:
			state++;
		break;
		case STATE_THREE:
			comming_status = OS_SPI_Read(&temp_answer);
			if (comming_status == OK) {
				answer=temp_answer;
				state++;
			}
		break;
		case STATE_FOUR:
		if((answer>=1)&&(answer<=3)) 
		give_notify(DISP_RES);
		else
		give_notify(WRONG_ANSW);
		state = INIT_STATE;
		break;
	}
}
#endif
/*if task not created call this function to light a red led*/
void task_not_created(void) {
	while (1) {
		DIO_WritePin(PIN_13, HIGH);
	}
}
void Display_Question(void) 
{
	uint8_t comming_status = PENDING;
	static uint8_t state = INIT_STATE;
	static uint8_t question_number = 0;
	uint8_t questions[5][16] = {{'S','h','r','t','s','t',' ','S','u','r','a','h',' ','I','s',' '},
							   {'W','h','o',' ','B','e','s','t',' ','o','f',' ','U','m','a','h'},
							   {'N','u','m','b','e','r',' ','O','f',' ','S','u','r','a','h','s'},
							   {'S','u','r','a','h',' ','N','a','m','e',' ','S','h','f','i','a'},
							   {'M','i','d',' ','S','U','r','h',' ','Q','u','r','a','N',' ',' '}};
 switch (state) {
	case INIT_STATE :
	if (get_notify(DISP_QUEST)) {
		vLCDsendcommand(Clear_display_screen);
			if(SHARED_WRONG_ANSWER_A_DIS_QUEST_A_DIS_ANSW == HIGH)
			{
				question_number--;
			}
		state++;
	}
	break;
	case STATE_TWO:
	comming_status = vLCDdisplaystring(questions[question_number], QUESTION_SIZE);
	if (comming_status == OK) {
		state++;
	}
	break;
	case STATE_THREE:
	question_number++;
	give_notify(DISP_ANSW);
	state = INIT_STATE;
	break;
	}

}
void Display_Answer_Options(void) {
	static uint8_t state = INIT_STATE;
	uint8_t coming_status = PENDING;
	static uint8_t choices_number = 0;
	uint8_t choice1[5][8] = {{'A','L','A','S','R',' ',' ',' '},
							{'O','m','r','K','h','t','a','b'},
							{'1','1','4',' ',' ',' ',' ',' '},
							{'F','a','t','i','h','a',' ',' '},
							{'A','l','I','s','r','a','a',' '}};
								
	uint8_t choice2[5][8] = {{'A','L','K','A','W','T','H','R'},
							{' ','A','b','u','B','a','k','r'},
							{'1','1','6',' ',' ',' ',' ',' '},
							{'B','a','k','r','a',' ',' ',' '},
							{'A','l','K','a','h','f',' ',' '}};
switch (state) {
	case INIT_STATE :
	if (get_notify(DISP_ANSW)) {
		vLCDgotoRowcolumn(LINE_TWO, 0);
		state++;
	}
	break;
	case STATE_TWO:
	if(SHARED_WRONG_ANSWER_A_DIS_QUEST_A_DIS_ANSW == HIGH)
	{
		choices_number--;
		SHARED_WRONG_ANSWER_A_DIS_QUEST_A_DIS_ANSW = LOW;
	}
	coming_status = vLCDdisplaystring(choice1[choices_number], ANSWER_SIZE);
	if (coming_status == OK) {
		state++;
	}
	break;
	case STATE_THREE:
	vLCDgotoRowcolumn(LINE_TWO, 8);
	state++;
	break;
	case STATE_FOUR:
	coming_status = vLCDdisplaystring(choice2[choices_number], ANSWER_SIZE);
	if (coming_status == OK) {
		state++;
	}
	;
	break;
	case STATE_FIVE:
	vLCDgotoRowcolumn(LINE_TWO, 15);
	state++;
	break;
	case STATE_SIX:
	choices_number++;
	state = INIT_STATE;
	give_notify(KEY_GET);
	break;
	default:
	break;
}

}
void Display_Result_Logo(void) {
	static uint8_t state = 1;
	static uint8_t question_number = 0;

	switch (state) {
		case INIT_STATE :
		if (get_notify(DISP_RES)) {
			vLCDsendcommand(Clear_display_screen);
			state++;
		}
		break;
		case STATE_TWO:
		question_number++;
		switch (question_number) {
			case INIT_STATE :
			if (answer == ONE) {
				result = WRONG;
				} else if (answer == TWO) {
				result = CORRECT;
				} else if (answer == SKIP) {
				result = SKIPPER;
			}
			break;
			case STATE_TWO:
			if (answer == ONE) {
				result = WRONG;
				} else if (answer == TWO) {
				result = CORRECT;
				} else if (answer == SKIP) {
				result = SKIPPER;
			}
			break;
			case STATE_THREE:
			if (answer == ONE) {
				result = CORRECT;
				} else if (answer == TWO) {
				result = WRONG;
				} else if (answer == SKIP) {
				result = SKIPPER;
			}
			break;
			case STATE_FOUR:
			if (answer == ONE) {
				result = CORRECT;
				} else if (answer == TWO) {
				result = WRONG;
				} else if (answer == SKIP) {
				result = SKIPPER;
			}
			break;
			case STATE_FIVE:
			if (answer == ONE) {
				result = WRONG;
				} else if (answer == TWO) {
				result = CORRECT;
				} else if (answer == SKIP) {
				result = SKIPPER;
			}
			break;
		}
		vLCDgotoRowcolumn(LINE_TWO, 5);
		state++;
		break;
		case STATE_THREE:
		if (result == CORRECT) {
			correct_answers_counter++;
			SmilyFace();
			} else if (result == WRONG) {
			SadFace();
			} else if (result == SKIPPER) {
			vLCDdisplaychar(' ');
		}
		state++;
		break;
		case STATE_FOUR:
		if(question_number < MAX_QUESTIONS)
		give_notify(DISP_QUEST);
		else
		give_notify(FINAL_TASK);
		state = INIT_STATE;
		default:
		break;
	}

}

void Final_Task(void){
	static uint8_t state = 1;
	uint8_t coming_status = PENDING;

	switch (state) {
		case INIT_STATE :
		if (get_notify(FINAL_TASK)) {
			vLCDsendcommand(Clear_display_screen);
			state++;
		}
		break;
		case STATE_TWO:
		coming_status = vLCDdisplaystring("YOU GOT ", ANSWER_SIZE);
		if (coming_status == OK) {
		state++;
		};
		break;
		case STATE_THREE:
		vLCDdisplaychar(correct_answers_counter+ASCI_ZERO);
		vLCDsendcommand(Force_cursor_to_beginning_2nd_line);
		state++;
		break;		
		case STATE_FOUR:
		coming_status = vLCDdisplaystring("OUT OF  ", ANSWER_SIZE);
		if (coming_status == OK) {
			state++;
		};
		break;
		case STATE_FIVE: 
		vLCDdisplaychar(MAX_QUESTIONS+ASCI_ZERO);
		state++;
		break;
		case STATE_SIX:
		break;
		default:
		break;
	}

}

void vWrong_Answer(void)
{
	uint8_t comming_status = PENDING;
	static uint8_t state = INIT_STATE;
	switch (state) {
		case INIT_STATE :
		if (get_notify(WRONG_ANSW)){
			SHARED_WRONG_ANSWER_A_DIS_QUEST_A_DIS_ANSW = ENABLED;
			vLCDsendcommand(Clear_display_screen);
			state++;
		}
		break;
		case STATE_TWO:
		comming_status = vLCDdisplaystring("INVALID KEY",ELEVEN);
		if (comming_status == OK) {
			state++;
		}
		break;
		case STATE_THREE:
		give_notify(DISP_QUEST);
		state = INIT_STATE;
		break;
	}
}
void give_notify(uint8_t task_to_notify) {
	switch (task_to_notify) {
		case DISP_ANSW:
		GLOBAL_DIS_ANS_get_notify = ENABLED;
		break;
		case DISP_QUEST:
		GLOBAL_DIS_QUEST_get_notify = ENABLED;
		break;
		case DISP_RES:
		GLOBAL_DIS_RES_get_notify = ENABLED;
		break;
		case KEY_GET:
		GLOBAL_KEY_get_get_notify = ENABLED;
		break;
		case KEY_INIT:
		GLOBAL_KEY_init_get_notify = ENABLED;
		break;
		case LCD_INIT:
		GLOBAL_LCD_init_get_notify = ENABLED;
		break;
		case FINAL_TASK:
		GLOBAL_FINAL_Task_get_notify = ENABLED;
		break;
		case WRONG_ANSW:
		GLOBAL_WRONG_ANSWER_get_notify = ENABLED;
		break;
	}
}
uint8_t get_notify(uint8_t task_to_notify) {
	uint8_t state = DISABLED;
	switch (task_to_notify) {
		case DISP_ANSW:
		state = GLOBAL_DIS_ANS_get_notify;
		GLOBAL_DIS_ANS_get_notify = DISABLED;
		break;
		case DISP_QUEST:
		state = GLOBAL_DIS_QUEST_get_notify;
		GLOBAL_DIS_QUEST_get_notify = DISABLED;
		break;
		case DISP_RES:
		state = GLOBAL_DIS_RES_get_notify;
		GLOBAL_DIS_RES_get_notify = DISABLED;
		break;
		case KEY_GET:
		state = GLOBAL_KEY_get_get_notify;
		GLOBAL_KEY_get_get_notify = DISABLED;
		break;
		case KEY_INIT:
		state = GLOBAL_KEY_init_get_notify;
		GLOBAL_KEY_init_get_notify = DISABLED;
		break;
		case LCD_INIT:
		state = GLOBAL_LCD_init_get_notify;
		GLOBAL_LCD_init_get_notify = DISABLED;
		break;
		case FINAL_TASK:
		state = GLOBAL_FINAL_Task_get_notify;
		GLOBAL_FINAL_Task_get_notify = DISABLED;
		break;
		case WRONG_ANSW:
		state = GLOBAL_WRONG_ANSWER_get_notify;
		GLOBAL_WRONG_ANSWER_get_notify = DISABLED;
		break;				
	}
	return state;
}
