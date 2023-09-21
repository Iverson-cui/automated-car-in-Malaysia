#include <reg52.h>
#include "driver.h"
#include "tracking.h"


sbit button1 = P3^3;  //P3^2 is S4


void START(void)
{
	while(1){
		Motor_Stop();
		if(!button1)
		{
			return;
		}
	}
}

//Ö÷º¯Êý
void main()
{
	Driver_Timer0Init();
	START();
	while(1)
	{
	TRACK();
	}
}

