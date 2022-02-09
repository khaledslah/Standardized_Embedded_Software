/*
 * Ultrasonic.c
 *
 * Created: 8/5/2019 1:22:59 PM
 *  Author: AVE-LAP-095
 */ 

#include "Ultrasonic.h"

void trigger_sensor(uint8_t ID){
		/* Give 10us trigger pulse on trig. pin to HC-SR04 */
		PORTA |= (1 << (ID-1));
		_delay_us(10);
		PORTA &= (~(1 << (ID-1)));
}

uint8_t calculate_distance(uint8_t ID, uint16 time_out){
	if((ID >= 1) && (ID <= 4)){
			if (DIO_ReadPin(ID-1) == 1)
			{
				TCNT1=0;
	        while(TCNT1<time_out){
				if (DIO_ReadPin(ID-1) == 0)
				{
					return (uint8_t)((double)TCNT1 / 58.308);
				}
				
			}
			}
	}
			return -1;
			
/*
			TCNT1 = 0;	/ * Clear Timer counter * /
			TCCR1B = 0x41;	/ * Capture on rising edge, No prescaler* /
			TIFR = 1<<ICF1;	/ * Clear ICP flag (Input Capture flag) * /
			TIFR = 1<<TOV1;	/ * Clear Timer Overflow flag * /

			/ *Calculate width of Echo by Input Capture (ICP) * /
			
			while ((TIFR & (1 << ICF1)) == 0);/ * Wait for rising edge * /
			TCNT1 = 0;	/ * Clear Timer counter * /
			TCCR1B = 0x01;	/ * Capture on falling edge, No prescaler * /
			TIFR = 1<<ICF1;	/ * Clear ICP flag (Input Capture flag) * /
			TIFR = 1<<TOV1;	/ * Clear Timer Overflow flag * /
			TimerOverflow = 0;/ * Clear Timer overflow count * /

			while ((TIFR & (1 << ICF1)) == 0);/ * Wait for falling edge * /
			count = ICR1 + (65535 * TimerOverflow);	/ * Take count * /
			/ * 8MHz Timer freq, sound speed =343 m/s * /
			distance = (double)count / 466.47;
	        return distance;
*/
}