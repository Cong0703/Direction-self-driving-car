#include "pwm.h"
#include "motor.h"

void pwm_set_duty(TIM_HandleTypeDef *htim, uint16_t chanel, uint8_t duty)
{
	uint16_t ccr = (uint16_t)duty*(htim->Instance->ARR)/100;
	switch(chanel)
	{
		case TIM_CHANNEL_1:
			{
				htim->Instance->CCR1=ccr;
			}
			break;
		case TIM_CHANNEL_2:
			{
				htim->Instance->CCR2=ccr;
			}	
			break;
		case TIM_CHANNEL_3:
			{
				htim->Instance->CCR3=ccr;
			}	
			break;
		case TIM_CHANNEL_4:
			{
				htim->Instance->CCR4=ccr;
			}	
			break;
	}
	
}
