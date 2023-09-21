#include <sound_sensor.h>
#include <reg52.h>
#include <intrins.h>

sbit Trig = P3^3;//������IO�ڶ���
sbit Echo = P3^2;//�ⲿ�ж�0���˿ڲ��ɸ���
/************************************

������ģ��
ʹ�ö�ʱ��1���ⲿ�ж�0��
�����̣�soundsensor����->����ʮ΢��ߵ�ƽ->��⵽echo�ߵ�ƽ->\n
->�򿪶�ʱ��1���ⲿ�ж�0->�ȴ��ⲿ�ж�0->�ⲿ�ж�0��϶�ʱ��1��ʱ->\n
->������������distance

*************************************/

/************************************

����ʱģ�壺
#include <sound_sensor.h>

void main()
{
	initTimer1();
	newProc = 1;
	while(1)
	{
		SoundSensor();
//��ʹ��getdistance������distance��ȡ����
		getDistance();
		Distance;
	}
}

���⣺
��ʱ���ж����ⲿ�жϺ����ɲ��������ⲿC�ļ�����
ANS��ò�ƿ�������ţ����Ҳ���Ҫ����
************************************/



unsigned int distance; //���صľ���
unsigned char succeed,newProc;
//succeedΪ���ɹ���־λ������ʱ���ж�һ�򿪣�succeed���㣬���ȴ��ⲿ�жϹرն�ʱ����Ӧ����ɹ���Ӧ��succeed = 1��
//newProcΪһ���ڽ���һ�ֲ��ı�־������=1ʱ��ʼ��࣬��ʼʱ��Ϊ0, ����ʱ��Ϊ1���ⲿ�ж�0�������ⲿ������Ϊ0�����������



void initTimer1()//�ⲿ�ж�0�붨ʱ��1��ʼ������û�д򿪶�ʱ��1
{
	TMOD |= 0x10; //T1����16λ��ʱ����
	//T1���ڲ������룬Ҫ��������ȼ�
	IT0 = 0;			//�ⲿ�ж�0�͵�ƽ��Ч
	IP = 0x08;		//����T1���ж����ȼ���������������������������������������ѧһ��
	EA = 1;				//�����ж�
	EX0 = 0;			//���ⲿ�ж�0
	TH1 = 0;			//��ʱ��1����ֵ
	TL1 = 0;
	Trig = 0;			//����Trig��ƽ
	succeed = 1;	//�����һ��ѭ���ı�־
	newProc = 0;	//�رճ����������ֶ���
}

void SoundSensor()//���÷���distance
{
//	newProc = 1;			//׼����ʼ�µĲ��
	if(newProc)				//��ʼ��һ�ֲ��
	{
		newProc = 0;
		delay(60);			
		//��ʱ60�������ǰһ�γ����������Ӱ�죬
		//�ڴ˴�����delay�������ܻ�Ӱ��ѭ��������ע�����
		TH1 = 0;				//��ʱ��1����ֵ
		TL1 = 0;
		Trig = 1;				//����ߵ�ƽ
		//�ߵ�ƽ����ʮ��
		_nop_();_nop_();_nop_();_nop_();_nop_();
		_nop_();_nop_();_nop_();_nop_();_nop_();
		Trig = 0;				//���10us����
		while(Echo == 0);		//�ȴ��ߵ�ƽ
		//�ߵ�ƽ���˿�ʼ��ʱ
		TR1 = 1;				//��ʱ��1��ʼ��ʱ
		EX0 = 1;				//�ȴ�Echo�͵�ƽ�����ж�
		succeed = 0;		//���ɹ���־λ����
	}
}

void EXT0() interrupt 0 //��Echo�������ⲿ�ж�0
{
	TR1 = 0;					//��ʱ��1�ر�
	EX0 = 0;					//�ⲿ�ж�0�ر�
	succeed = 1;			//�ɹ�������־��1
	distance = TH1;		//��������߰�λ
	distance <<= 8;		//����ʮ��λ�ĸ߰�λ
	distance |= TL1;	//��Ͱ�λ�ϲ�
	distance = distance * 0.0172;//��λcm
	//ԭˢ�����������λ��
	newProc = 1;
}

unsigned int getDistance()	//���ڷ���distance��������������������distance�ܲ���ֱ�������������ã�
{
	return distance;
}

void delay(unsigned int xms) //ms��ʱ����
{
	unsigned int i,j;
	for(i=xms;i>0;i--)
	for(j=112;j>0;j--);
}
