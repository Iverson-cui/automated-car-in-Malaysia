#ifndef __sound_sensor_h__
#define __sound_sensor_h__

extern unsigned int Distance; //���صľ���
extern unsigned char newProc; //����������

//��������
void initTimer1();
void SoundSensor();
unsigned int getDistance();
void delay(unsigned int xms);
void EXT0(); //��Echo�������ⲿ�ж�0

#endif