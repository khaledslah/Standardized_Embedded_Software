#include "LCD.h"

void vLCDsendcommand(uint8_t cmd) {
	DIO_WritePin(LCD_REGISTER_PIN, CMD);
	DIO_WritePin(LCD_RW_PIN, WRITE);
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);
	DIO_WritePin(LCD_ENABLE_PIN, HIGH);
	_delay_us(1);
	DIO_WritePin(LCD_ENABLE_PIN, LOW);
	_delay_us(200);
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd << 4);
	DIO_WritePin(LCD_ENABLE_PIN, HIGH);
	_delay_us(1);
	DIO_WritePin(LCD_ENABLE_PIN, LOW);
}
void vLCDdisplaychar(uint8_t data) {
	DIO_WritePin(LCD_REGISTER_PIN, DATA);
	DIO_WritePin(LCD_RW_PIN, WRITE);
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	DIO_WritePin(LCD_ENABLE_PIN, HIGH);
	_delay_us(1);
	DIO_WritePin(LCD_ENABLE_PIN, LOW);
	_delay_us(1);
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data << 4);
	DIO_WritePin(LCD_ENABLE_PIN, HIGH);
	_delay_us(1);
	DIO_WritePin(LCD_ENABLE_PIN, LOW);

}
uint8_t vLCDdisplaystring(uint8_t * data, uint8_t size) {
	uint8_t status = PENDING;
	static uint8_t index = 0;
	if (index < size)
	 {
		status = PENDING;
		vLCDdisplaychar(data[index++]);
		} 
		else {
		status = OK;
		index = 0;
	}
	return status;
}
void vLCDclear(void) {
	vLCDsendcommand(Clear_display_screen);
}
void vLCDgotoRowcolumn(uint8_t row, uint8_t column) 
{

	if ((row == LINE_ONE) && (column < LCD_LINE_SIZE))
	vLCDsendcommand(column | Force_cursor_to_beginning_1st_line); /* Command of first row and required position<16 */
	else if ((row == LINE_TWO) && (column < LCD_LINE_SIZE))
	vLCDsendcommand(column | Force_cursor_to_beginning_2nd_line); /* Command of first row and required position<16 */
	else 
	{
	}
}

uint8_t vLCDcustomchar(uint8_t loc, uint8_t *msg) {
	static uint8_t state = INIT_STATE;
	static uint8_t index = ZERO;
	uint8_t status = PENDING;
	switch (state) {
		case INIT_STATE:
		if (loc < EIGHT) {
			vLCDsendcommand(Custom_char + (loc * EIGHT));
			state++;
		}
		status = PENDING;
		break;
		case STATE_TWO:
		if (index < EIGHT) {
			vLCDdisplaychar(msg[index]);
			index++;
			} else {
			state++;
			index = ZERO;
		}
		status = PENDING;
		break;
		case STATE_THREE:
		vLCDsendcommand(Force_cursor_to_beginning_1st_line);
		state = INIT_STATE;
		status = OK;
		break;
	}
	return status;
}

void SmilyFace(void) {
	vLCDsendcommand(Clear_display_screen);

	vLCDsendcommand(Custom_char);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00010001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 8);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00010001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 16);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00001000);
	vLCDdisplaychar(0b00000111);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 24);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000010);
	vLCDdisplaychar(0b00011100);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);

	vLCDgotoRowcolumn(LINE_ONE, ONE);
	vLCDdisplaychar(ZERO);
	vLCDgotoRowcolumn(LINE_ONE, TWO);
	vLCDdisplaychar(ONE);
	vLCDgotoRowcolumn(LINE_TWO, ONE);
	vLCDdisplaychar(TWO);
	vLCDgotoRowcolumn(LINE_TWO, TWO);
	vLCDdisplaychar(THREE);
	_delay_ms(2000);
}

void SadFace(void) {
	vLCDsendcommand(Clear_display_screen);

	vLCDsendcommand(Custom_char + 32);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00010001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 40);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00010001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00001110);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 48);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000111);
	vLCDdisplaychar(0b00001000);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00000000);

	vLCDsendcommand(Custom_char + 56);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00010000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00000000);
	vLCDdisplaychar(0b00011100);
	vLCDdisplaychar(0b00000010);
	vLCDdisplaychar(0b00000001);
	vLCDdisplaychar(0b00000000);

	vLCDgotoRowcolumn(LINE_ONE, ONE);
	vLCDdisplaychar(FOUR);
	vLCDgotoRowcolumn(LINE_ONE, TWO);
	vLCDdisplaychar(FIVE);
	vLCDgotoRowcolumn(LINE_TWO, ONE);
	vLCDdisplaychar(SIX);
	vLCDgotoRowcolumn(LINE_TWO, TWO);
	vLCDdisplaychar(SEVEN);
	_delay_ms(2000);
}