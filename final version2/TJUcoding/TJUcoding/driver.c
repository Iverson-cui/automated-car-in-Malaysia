#include "driver.h"

unsigned char pwm_val_left  =0;     //PWM��������
unsigned char pwm_val_right =0;

void Driver_Timer0Init(void)		//10΢��@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	
	TL0 = 0xF6;		//���ö�ʱ��ֵ 0.01ms��ʱ��1khz
	TH0 = 0xFF;		//���ö�ʱ��ֵ
	
	
	ET0 = 1;    //��ʱ��0�ж�������
	EA = 1;     //��ʱ���ж��ܿ���
	
	PT0 = 0;    //���ö�ʱ��0�����ȼ�
	
	TF0 = 0;		//���TF0��־
	
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
		
	//TH0 = (65536 - )/256;
	//TL0 = (65536 - )%256;
}

void Motor_Left(bit Dir, unsigned char DutyCycle) //��������ת(1Ϊ��ת��0Ϊ��ת)��ռ�ձȲ���
{
	if(Dir == 1)
	{
		PWMA=1;
		AIN1 = 0;
		AIN2 = 1;
		if(pwm_val_left <= DutyCycle)
		{
			PWMA = 1;
		}
		else
		{
			PWMA = 0;
		}
	}
	else
	{
		PWMA=1;
		AIN1 = 1;
		AIN2 = 0;
		if(pwm_val_left <= DutyCycle)
		{
			PWMA = 1;
		}
		else
		{
			PWMA = 0;
		}
	}
}

void Motor_Right(bit Dir, unsigned char DutyCycle) //��������ת(1Ϊ��ת��0Ϊ��ת)��ռ�ձȲ���
{
	if(Dir == 1)
	{
		PWMB=1;
		BIN1 = 1;
		BIN2 = 0;
		if(pwm_val_right <= DutyCycle)
		{
			PWMB = 1;
		}
		else
		{
			PWMB = 0;
		}
	}
	else
	{
		PWMB=1;
		BIN1 = 0;
		BIN2 = 1;
		if(pwm_val_right <= DutyCycle)
		{
			PWMB = 1;
		}
		else
		{
			PWMB = 0;
		}
	}
}

void Motor_Stop(void)
{
	PWMA = 0;
	PWMB = 0;
}

void InterruptTimer0() interrupt 1
{
	TR0 = 0;
	TL0 = 0xF6;		//���ض�ʱ��ֵ
	TH0 = 0xFF;		//���ض�ʱ��ֵ
	pwm_val_left++;
	pwm_val_right++;
	if(pwm_val_left >= 100)
	{
		pwm_val_left = 0;
	}
	if(pwm_val_right >= 100)
	{
		pwm_val_right = 0;
	}
	TR0 = 1;
}