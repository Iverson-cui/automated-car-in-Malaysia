#ifndef __sound_sensor_h__
#define __sound_sensor_h__

extern unsigned int Distance; //返回的距离
extern unsigned char newProc; //启动超声波

//函数声明
void initTimer1();
void SoundSensor();
unsigned int getDistance();
void delay(unsigned int xms);
void EXT0(); //由Echo触发的外部中断0

#endif