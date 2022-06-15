#ifndef __SERVO_H
#define __SERVO_H
#include "main.h"

typedef struct
{
	TIM_HandleTypeDef *htim;
	uint16_t channel;
	uint8_t goc;
}Servo;
void servo_write(Servo *sv, uint8_t goc);
void servo_init(Servo *sv,TIM_HandleTypeDef *htim,uint16_t channel);
#endif
