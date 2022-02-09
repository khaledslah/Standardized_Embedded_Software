/*
 * UART.h
 *
 * Created: 8/5/2019 2:53:08 PM
 *  Author: AVE-LAP-039
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>



#define Input 0
#define Output 1

void UART_init();
void UART_send_byte(uint8_t data_send);
void UART_send_one_byte_decimal(uint8_t number);
uint8_t UART_receive_byte(void);
void UART_send_string(uint8_t string_to_send[]);
void UART_send_data_from_array_by_specified_length(uint8_t* string_to_send, uint8_t length);




#endif /* UART_H_ */