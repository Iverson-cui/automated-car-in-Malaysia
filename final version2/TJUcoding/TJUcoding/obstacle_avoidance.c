#include <obstacle_avoidance.h>

int counter = 0;				//��Ҫ���ⲿ����
unsigned int k;


void tiaojian(void){
    Distance = Measure_Distance();	
	if(Distance <= 20){		//��ʼ���ϵľ��룬���������
		counter = 1000;
	}
    
}
/*
void ObstacleAvoidance(void)
{
	tiaojian();
	if(counter == 0)
	{
		TRACK();				//����ѭ��
		tiaojian();
		
	}
	else if(counter > 0)		//˳ʱ��ԭ�ص�ͷ
	{
		//Motor_Stop();
		while(counter){		
					for(m=100;m>=2;m--){
					dazhuan1();
					}
		for(m=500;m>=2;m--){
					zhizou();
					}
		for(m=100;m>=2;m--){
					dazhuan2();
					}
		for(m=500;m>=2;m--){
					zhizou();
					}
		for(m=100;m>=2;m--){
					dazhuan2();
					}
		for(m=500;m>=2;m--){
					zhizou();
					}
		for(m=100;m>=2;m--){
					dazhuan2();
					}
		}
	}*/
//	else if(counter >= 100)		//1000~500��ת
//	{
//		//Motor_Stop();
//		Motor_Left(1, 30); 
//		Motor_Right(1, 50);
//		counter--;
//		
//	}
//	else if(counter >= 50&& counter < 100)		//500~0��ת
//	{
//		//Motor_Stop();
//		Motor_Left(1, 40); 
//		Motor_Right(1, 40);
//		counter--;
//	}
//	else if(counter > 0&& counter < 50)		//500~0��ת
//	{
//		//Motor_Stop();
//		Motor_Left(1, 50); 
//		Motor_Right(1, 30);
//		counter--;
//	}
	//else
		//counter = 0;



//        Distance = Measure_Distance();
//         if(Distance <= 20){
//		 Motor_Stop();
//		 }		 
//         else if(Distance > 20){
//		 TRACK();
//			 Distance = Measure_Distance();
//		 }
			 
//}

//counterѭ����0���״̬������ѭ����600����С��300ת���ء�