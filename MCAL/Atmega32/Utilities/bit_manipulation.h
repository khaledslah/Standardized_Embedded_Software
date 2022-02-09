/*
 * bit_manipulation.h
 *
 * Created: 6/19/2019 11:09:27 AM
 *  Author: AVE-LAP-095
 */

#ifndef BIT_MANIPULATION_H_
#define BIT_MANIPULATION_H_
#include <avr/io.h>

#define Set_Bit(Register,Bit) Register |= (1<<(Bit))
#define Clear_Bit(Register,Bit) Register &= ~(1<<(Bit))
#define Get_Bit(Register,Bit) (Register & (1<<(Bit)))?1:0 /* (Register>>Bit) & (0x01)*/
#define Toggle_Bit(Register,Bit) Register ^= (1<<(Bit))

#endif /* BIT_MANIPULATION_H_ */
