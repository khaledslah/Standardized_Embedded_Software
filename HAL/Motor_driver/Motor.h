/*
 * Motor.h
 *
 * Created: 7/21/2019 6:29:31 PM
 *  Author: AVE-LAP-062
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

extern void Motor_init(void);
extern void Set_Enable(void);
extern void  Set_Enable_PWM(uint16);
extern void Forword_Step(void);
extern void Backword_Step(void);
extern void Left_Step(void);
extern void Right_Step(void);
extern void Brake(void);


#endif /* MOTOR_H_ */