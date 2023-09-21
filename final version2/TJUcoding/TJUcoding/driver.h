#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <reg52.h>

sbit AIN1 = P2^1; //定义左电机控制引脚
sbit AIN2 = P2^2;
sbit BIN1 = P2^3; //定义右电机控制引脚
sbit BIN2 = P2^4;

sbit PWMA = P2^0; //定义电机PWM输入端/使能端                               
sbit PWMB = P2^5;

void Driver_Timer0Init(void);
void Motor_Left(bit Dir, unsigned char DutyCycle); //传递正反转(1为正转，0为反转)、占空比参数
void Motor_Right(bit Dir, unsigned char DutyCycle); //传递正反转(1为正转，0为反转)、占空比参数
void Motor_Stop(void);

#endif