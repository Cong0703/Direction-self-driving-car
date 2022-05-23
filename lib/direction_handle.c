/*
Dem : la bien dem so lan quay cua servo G90, max =2 vi chi quay trai va phai
*/

#include "direction_handle.h"
#include "hcsr04.h"
#include "Servo.h"
#include "main.h"

uint8_t dem=0;
extern Servo sv1;
extern hcsr04_t hcsr04;
extern float kc;
extern uint16_t goc;
uint32_t time;

void direction_handle(float *buff)
{
   if (dem==2) 
	 {
		 dem=0;
		 buff[1] = kc;
		 //servo_write(&sv1,goc);
     time=HAL_GetTick();		 
	 }
   
   if (HAL_GetTick()-time <=700 && goc==90)
	 {
		 //waiting
	 }		 
	 else if (kc <=10 && goc==90 && dem==0) 
    {
						goc=0;
						dem++;
    }
	else if (goc==0)
    {
			 
       goc=180;
			 time=HAL_GetTick();
			 while(HAL_GetTick()-time <=500)
			 {
				 //waiting
			 }
    }
  else if (goc==180)
    { 
			  
				goc=90;
			  buff[0] = kc;
			  dem++;
			  time=HAL_GetTick();
			 while(HAL_GetTick()-time <=500)
			 {
				 //waiting
			 }
    } 
}


