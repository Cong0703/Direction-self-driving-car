/*
Author : Cong
Note: when using the library need
- declare hcsr04_t hcsr04; (in main)
- kc is a variable to save the measured distance, so it can be extern to other libraries to use
- Declare 2 pin trigger and echo(pin interrupt)
*/



#ifndef HCSR04_H
#define HCSR04_H
#include "stdint.h"
#include "main.h"

typedef enum{
 HCSR04_IDLE_STATE,              // idle : nhan roi, tuc la trang thai chua do dat gi ca
 HCSR04_GEN_PULSE_STATE,         //tao song
 HCSR04_WAIT_EXT_RISING_STATE,  // state doi cho chan echo len 1 (nhan duoc song am phan lai)
 HCSR04_WAIT_EXT_FALLING_STATE,	// state doi cho chan echo xuong 0
 HCSR04_COMPLETE_STATE
}HCSR04_State;

typedef struct
{
	TIM_HandleTypeDef *htim;
	float distance;
}hcsr04_t;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HCSR04_start(void);
void HCSR04_COMPLETE_CALLBACK(void);
void HCSR04_handle(void);
void HCSR04_init(hcsr04_t *hcsr, TIM_HandleTypeDef *htim);
void get_instance(void);

#endif
