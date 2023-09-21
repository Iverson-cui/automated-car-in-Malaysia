#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <reg52.h>

sbit AIN1 = P2^1; //����������������
sbit AIN2 = P2^2;
sbit BIN1 = P2^3; //�����ҵ����������
sbit BIN2 = P2^4;

sbit PWMA = P2^0; //������PWM�����/ʹ�ܶ�                               
sbit PWMB = P2^5;

void Driver_Timer0Init(void);
void Motor_Left(bit Dir, unsigned char DutyCycle); //��������ת(1Ϊ��ת��0Ϊ��ת)��ռ�ձȲ���
void Motor_Right(bit Dir, unsigned char DutyCycle); //��������ת(1Ϊ��ת��0Ϊ��ת)��ռ�ձȲ���
void Motor_Stop(void);

#endif