#ifndef __ULTRA_SONIC_H__
#define __ULTRA_SONIC_H__
#include <reg52.h>
#include <intrins.h>

sbit Trig = P1^6;
sbit Echo = P1^7;

#define VELOCITY 0.034       //ÉùËÙ

extern float Distance;

void Timer1Init(void);
void StartModule(void);
long Measure_Distance(void);
void Delay20us(void);		//@12.000MHz
	
#endif