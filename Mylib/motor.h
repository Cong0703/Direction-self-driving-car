#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f1xx.h"

//==========control_motor==============
typedef enum
{
	MOTOR_STOP,
	MOTOR_CW, //clockwise : cung chieu kim dong ho
	MOTOR_CCW //Counter clockwise : nguoc chieu kim dong ho
}MotorState;

typedef struct
{
	GPIO_TypeDef *io_port;
	uint16_t io_pin;
	TIM_HandleTypeDef *htim;
	uint16_t htim_chanel;
	MotorState motor_state;
	uint8_t speed;
}Motor_t;

void motor_control(Motor_t *motor, MotorState state,uint8_t speed);
void motor_init(	Motor_t *motor,
									GPIO_TypeDef *io_port,
									uint16_t io_pin,
									TIM_HandleTypeDef *htim,
									uint16_t htim_chanel);

#endif
