#include "motor.h"
#include "pwm.h"

void motor_control(Motor_t *motor, MotorState state,uint8_t speed)
{
	switch(state)
	{
		case MOTOR_STOP:
		{
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,GPIO_PIN_RESET);
			pwm_set_duty(motor->htim,motor->htim_chanel,0); // set ccr1=0=> duty_1=0=>chan nhan muc low
			break;
		}
		case MOTOR_CW:
		{
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,GPIO_PIN_RESET);
			pwm_set_duty(motor->htim,motor->htim_chanel,speed);
			/*
			duty  : 0=>100 (speed tu 0=>100%)
			ccr1  : 0=>999
			*/
			break;
		}
		case MOTOR_CCW:
		{
			HAL_GPIO_WritePin(motor->io_port,motor->io_pin,GPIO_PIN_SET);
			pwm_set_duty(motor->htim,motor->htim_chanel,100-speed);
			/*
			duty<< => CCR << => in2=1, in1 >>  => U << => Chay cang cham
			*/
			break;
		}
		
	}
}

void motor_init(	Motor_t *motor,
									GPIO_TypeDef *io_port,
									uint16_t io_pin,
									TIM_HandleTypeDef *htim,
									uint16_t htim_chanel)
  {
			motor->io_pin=io_pin;
			motor->io_port=io_port;
			motor->htim=htim;
			motor->htim_chanel=htim_chanel;
		  HAL_TIM_PWM_Start(motor->htim, motor->htim_chanel);
  }




