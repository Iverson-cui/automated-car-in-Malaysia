#include "driver.h"

unsigned char pwm_val_left  =0;     //PWM变量定义
unsigned char pwm_val_right =0;

void Driver_Timer0Init(void)		//10微秒@12.000MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	
	TL0 = 0xF6;		//设置定时初值 0.01ms定时，1khz
	TH0 = 0xFF;		//设置定时初值
	
	
	ET0 = 1;    //定时器0中断允许开关
	EA = 1;     //定时器中断总开关
	
	PT0 = 0;    //设置定时器0的优先级
	
	TF0 = 0;		//清除TF0标志
	
	TR0 = 1;		//定时器0开始计时
	
		
	//TH0 = (65536 - )/256;
	//TL0 = (65536 - )%256;
}

void Motor_Left(bit Dir, unsigned char DutyCycle) //传递正反转(1为正转，0为反转)、占空比参数
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

void Motor_Right(bit Dir, unsigned char DutyCycle) //传递正反转(1为正转，0为反转)、占空比参数
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
	TL0 = 0xF6;		//重载定时初值
	TH0 = 0xFF;		//重载定时初值
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