/*
 * global.h
 *
 * Created: 9/8/2019 10:52:57 AM
 *  Author: AVE-LAP-095
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_
enum Answers {
	ZERO = 0,
	ONE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	ELEVEN = 11,
	SKIP = 3
};
enum Notify_Status
{
	DISABLED = 0,
	ENABLED = 1
};
enum States {
	INIT_STATE = 1,
	STATE_TWO,
	STATE_THREE,
	STATE_FOUR,
	STATE_FIVE,
	STATE_SIX,
	STATE_SEVEN,
	STATE_EIGHT,
	STATE_NINE,
	STATE_TEN
};

enum Function_Status {
	OK = 1, NOK = 2, PENDING = 3
};

enum Lcd_commands {
	Clear_display_screen = 0x01,
	Return_home = 0x02,
	Increment_cursor_shift_cursor_to_right = 0x06,
	Display_on_cursor_blinking = 0x0F,
	Custom_char = 0x40,
	Force_cursor_to_beginning_1st_line = 0x80,
	Force_cursor_to_beginning_2nd_line = 0xC0,
	Two_lines_and_5_7_matrix_4_bit_mode = 0x28

};
enum Lcd_lines {
	LINE_ONE = 0, LINE_TWO = 1
};
#endif /* GLOBAL_H_ */
