#ifndef __CAR_H
#define __CAR_H
#include "stdint.h"
#include "motor.h"

typedef enum
{
	CAR_STOP_STATE,
	CAR_FORWARD_STATE,  //TIEN
	CAR_BACKWARD_STATE, //LUI
	CAR_LEFT_STATE,     //TRAI
	CAR_RIGHT_STATE     //PHAI
}Carstate;

void car_control(Carstate car_state, uint8_t speed);
void car_init(TIM_HandleTypeDef *htim);
#endif
