#include "delay_ms.h"

void delay_ms(uint32_t *time, uint32_t delay)
{
	     *time=HAL_GetTick();
		 		while(HAL_GetTick() - *time <= delay)
			 {
				 //waiting for rotating
			 }
			 *time=HAL_GetTick();
}



