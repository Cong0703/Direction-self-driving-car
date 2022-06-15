#ifndef __PWM_H
#define __PWM_H
#include "stm32f1xx.h"
#include "motor.h"

void pwm_set_duty(TIM_HandleTypeDef *htim, uint16_t chanel, uint8_t duty);
#endif
