#include <ultra_sonic.h>

float Distance = 0;

long Measure_Distance(void)//距离测量函数
{   
	//TR1 = 0;
	long int dis = 0;
	Timer1Init(); //配置定时器0
	TL0 = 0;
	//TH1 = 0;
	TH0 = 0;
	StartModule(); //触发超声波
	
	while(!Echo);	//等待超声波的返回脉冲
	
	TR0 = 1;      //打开定时器，开始计时
	while(Echo);  //等待超声波的返回脉冲结束
	TR0 = 0;      //计时结束
	
//	Distance = ((TH1*256+TL1)*VELOCITY)/2+1.5; //计算距离
	dis = TH0;		//测量结果高八位
	dis <<= 8;		//放入十六位的高八位
	dis |= TL0;	//与低八位合并
	Distance = dis * 0.0172;//单位cm
	return Distance;
}

void StartModule() //触发一次超声波模块
{
	Trig = 1;
	Delay20us();
	Trig = 0;
}


void Timer1Init(void)
{
	//TMOD &= 0x0F;		//设置定时器模式
	
	//TMOD |= 0x10;		//设置定时器模式
	TMOD &= 0xF0;
	TMOD |= 0x01;
	//TL1 = 0;
	TL0 = 0;
	//TH1 = 0;
	TH0 = 0;
}

void Delay20us()		//@12.000MHz
{
	unsigned char i;
	_nop_();
	i = 7;
	while (--i);
}
