#include <sound_sensor.h>
#include <reg52.h>
#include <intrins.h>

sbit Trig = P3^3;//超声波IO口定义
sbit Echo = P3^2;//外部中断0，端口不可更改
/************************************

超声波模块
使用定时器1，外部中断0；
测距过程：soundsensor进入->发送十微秒高电平->检测到echo高电平->\n
->打开定时器1，外部中断0->等待外部中断0->外部中断0打断定时器1计时->\n
->将距离结果存入distance

*************************************/

/************************************

调用时模板：
#include <sound_sensor.h>

void main()
{
	initTimer1();
	newProc = 1;
	while(1)
	{
		SoundSensor();
//可使用getdistance函数和distance调取距离
		getDistance();
		Distance;
	}
}

问题：
定时器中断与外部中断函数可不可以在外部C文件定义
ANS：貌似可以随意放，并且不需要声明
************************************/



unsigned int distance; //返回的距离
unsigned char succeed,newProc;
//succeed为测距成功标志位，当定时器中断一打开，succeed清零，并等待外部中断关闭定时器相应，如成功相应，succeed = 1；
//newProc为一正在进行一轮测距的标志符，当=1时开始测距，开始时置为0, 结束时置为1（外部中断0），从外部调整其为0会结束超声波



void initTimer1()//外部中断0与定时器1初始化，并没有打开定时器1
{
	TMOD |= 0x10; //T1置于16位定时器；
	//T1用于测量距离，要求最高优先级
	IT0 = 0;			//外部中断0低电平有效
	IP = 0x08;		//提升T1的中断优先级————————————————？？再学一下
	EA = 1;				//打卡总中断
	EX0 = 0;			//打开外部中断0
	TH1 = 0;			//定时器1赋初值
	TL1 = 0;
	Trig = 0;			//拉低Trig电平
	succeed = 1;	//完成上一次循环的标志
	newProc = 0;	//关闭超声波，需手动打开
}

void SoundSensor()//设置返回distance
{
//	newProc = 1;			//准备开始新的测距
	if(newProc)				//开始新一轮测距
	{
		newProc = 0;
		delay(60);			
		//延时60毫秒避免前一次超声波发射的影响，
		//在此处设置delay函数可能会影响循迹函数，注意测试
		TH1 = 0;				//定时器1赋初值
		TL1 = 0;
		Trig = 1;				//输出高电平
		//高电平保持十秒
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		Trig = 0;				//输出10us脉冲
		while(Echo == 0);		//等待高电平
		//高电平来了开始计时
		TR1 = 1;				//定时器1开始计时
		EX0 = 1;				//等待Echo低电平触发中断
		succeed = 0;		//测距成功标志位清零
	}
}

void EXT0() interrupt 0 //由Echo触发的外部中断0
{
	TR1 = 0;					//定时器1关闭
	EX0 = 0;					//外部中断0关闭
	succeed = 1;			//成功测量标志置1
	distance = TH1;		//测量结果高八位
	distance <<= 8;		//放入十六位的高八位
	distance |= TL1;	//与低八位合并
	distance = distance * 0.0172;//单位cm
	//原刷新数码管内容位置
	newProc = 1;
}

unsigned int getDistance()	//便于返回distance————————？？distance能不能直接在主函数调用？
{
	return distance;
}

void delay(unsigned int xms) //ms延时函数
{
	unsigned int i,j;
	for(i=xms;i>0;i--)
	for(j=112;j>0;j--);
}
