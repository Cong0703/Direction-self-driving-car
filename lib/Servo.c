#include "direction_handle.h"
#include "hcsr04.h"
#include "Servo.h"

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void servo_write(Servo *sv, uint8_t goc)
{
	//goc : 0 -> 180
	//CCR : 1000 -> 2000
	// Giai thich : Gia tri ARR = 20000 chinh la chu ki , T(on) có value = 1-2ms
	//=> doi tuong ung :   T(on)=1-2ms       T = 20ms
  //                     CCR = 1000-2000	 ARR=20000
  // su dung ham map chuyen doi khoang gia tri (trong arduino), muc dich chuyen doi khoang goc sang CCR
	//uint16_t CCR = (goc-0)*(2000-1000)/(180-100)+1000;
	// Tren thuc te khoang CCR la 544 den 2400 (theo arduino)
	uint16_t CCR = map(goc,0,180,544,2500);
	switch(sv->channel)
	{
		case TIM_CHANNEL_1:
			sv->htim->Instance->CCR1 = CCR;
			break;
		case TIM_CHANNEL_2:
			sv->htim->Instance->CCR2 = CCR;
			break;
		case TIM_CHANNEL_3:
			sv->htim->Instance->CCR3 = CCR;
			break;
		case TIM_CHANNEL_4:
			sv->htim->Instance->CCR4 = CCR;
			break;
	}
}

//==============Control_from_ADC==============



void servo_init(Servo *sv,TIM_HandleTypeDef *htim,uint16_t channel)
{
	sv->htim = htim;
	sv->channel = channel;
	HAL_TIM_PWM_Start(htim,channel);
}
