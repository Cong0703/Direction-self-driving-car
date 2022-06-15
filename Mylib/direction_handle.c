/*
Dem : la bien dem so lan quay cua servo G90, max =2 vi chi quay trai va phai
buff[0] : right
buff[1] : left

*/

#include "direction_handle.h"
#include "hcsr04.h"
#include "Servo.h"
#include "main.h"
#include "car.h"
#include "pwm.h"
#include "motor.h"
#include "delay_ms.h"

uint8_t dem=0;
extern Servo sv1;
extern hcsr04_t hcsr04;
extern float kc;
extern uint16_t goc;
uint32_t time;
uint8_t go_back=0,is_turning = 0;
uint8_t start=1;


void direction_handle(float *buff,Carstate car_state)
{
   if (dem==2) 
	 {
		 dem=0;
		 buff[1] = kc;	
     
		 //Dua vao khoang cach chon huong di
     //TH1 : Ben phai khong co vat can
		 if (buff[0] > buff[1] && buff[0]>=20)
		 {
			  if (buff[0]<50)
				{
				 car_control(CAR_RIGHT_STATE,100);
				 delay_ms(&time,300);
				 go_back=0;
			   is_turning=1;
//				 car_control(CAR_FORWARD_STATE,50);
//				 delay_ms(&time,200);
				 car_control(CAR_STOP_STATE,0);
				}
				else if (buff[0]>=50 && buff[0] < 300)
				{
					car_control(CAR_RIGHT_STATE,100);
				  delay_ms(&time,300);
				  go_back=0;
					car_control(CAR_STOP_STATE,0);
				}
		 }
			else if (buff[1] > buff[0] && buff[1]>=20)
		 {
				 if (buff[1]<50)
				{
				 car_control(CAR_LEFT_STATE,100);
				 delay_ms(&time,300);
				 go_back=0;
			   is_turning=1;
//				 car_control(CAR_FORWARD_STATE,50);
//				 delay_ms(&time,200);
				 car_control(CAR_STOP_STATE,0);
				}
				else if (buff[1]>=50 && buff[1] < 300)
				{
					car_control(CAR_LEFT_STATE,100);
				  delay_ms(&time,300);
				  go_back=0;
					car_control(CAR_STOP_STATE,0);
				}
		 }
		 else if (buff[0] < 20 && buff[1] < 20)
		 {
			 car_control(CAR_BACKWARD_STATE,100);
			 go_back=1;
			 delay_ms(&time,300);
			 car_control(CAR_STOP_STATE,0);	
		 }
		 
			 delay_ms(&time,500);
			 time=HAL_GetTick();
	 }
   	 
	 if (HAL_GetTick()-time <=100 && goc==90)
	 {
		 //waiting
	 }	
	  else if ( (kc <=20 && goc==90 && dem==0) || go_back || is_turning) 
    { 
			      car_control(CAR_STOP_STATE,0);
						goc=0;
						dem++;
			      go_back=0;
			      is_turning=0;
    }
	else if (goc==0)
    {
			 
       goc=180;
			 delay_ms(&time,500);
    }
  else if (goc==180)
    { 
			  
				goc=90;
			  buff[0] = kc;
			  dem++;
			  delay_ms(&time,500);
    }
  if ( ((buff[0]>=50 || buff[1]>=50) && dem==0) || start==1)
   		car_control(CAR_FORWARD_STATE,50);
	    start=0;
}


