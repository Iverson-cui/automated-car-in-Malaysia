#include <obstacle_avoidance.h>

int counter = 0;				//需要在外部置零
unsigned int k;


void tiaojian(void){
    Distance = Measure_Distance();	
	if(Distance <= 20){		//开始避障的距离，跟车速相关
		counter = 1000;
	}
    
}
/*
void ObstacleAvoidance(void)
{
	tiaojian();
	if(counter == 0)
	{
		TRACK();				//正常循迹
		tiaojian();
		
	}
	else if(counter > 0)		//顺时针原地调头
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
//	else if(counter >= 100)		//1000~500左转
//	{
//		//Motor_Stop();
//		Motor_Left(1, 30); 
//		Motor_Right(1, 50);
//		counter--;
//		
//	}
//	else if(counter >= 50&& counter < 100)		//500~0右转
//	{
//		//Motor_Stop();
//		Motor_Left(1, 40); 
//		Motor_Right(1, 40);
//		counter--;
//	}
//	else if(counter > 0&& counter < 50)		//500~0右转
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

//counter循环：0检测状态，触发循迹置600，减小到300转身返回。