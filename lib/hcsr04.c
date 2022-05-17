#include "direction_handle.h"
#include "hcsr04.h"
#include "Servo.h"
#include "main.h"

/*==============Handle==============*/

HCSR04_State hcsr04_state; // koi tao trang thai ban dau dang là idol
uint32_t time_start_gen_pulse;
float buff_distance[2];
uint16_t goc=90;
extern Servo sv1;
extern hcsr04_t hcsr04;
float kc;


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  if(GPIO_Pin == HCSR04_ECHO_Pin)
		{
		
		// check trang thai cua echo
		switch(hcsr04_state){
   // Do enum phai xu li het tat ca cac truong hop
	 // nen la khi xu li switch thi muon xu li mot vai truong hop thoi thi can cho them default o duoi
			case HCSR04_WAIT_EXT_RISING_STATE: 
			{
				 if (HAL_GPIO_ReadPin(HCSR04_ECHO_GPIO_Port,HCSR04_ECHO_Pin)==1)
					 {
					 // ngat canh len, set CNT ve 0 va bat timer len
					 hcsr04.htim->Instance->CNT = 0;        // Cho timer ve 0, ban chat la CNT = 0
					 HAL_TIM_Base_Start(hcsr04.htim);     // Khoi dong time
					 hcsr04_state = HCSR04_WAIT_EXT_FALLING_STATE;
					 }  
				 else  hcsr04_state = HCSR04_IDLE_STATE;	
			   break;
			}	
			
			case HCSR04_WAIT_EXT_FALLING_STATE: 
			{
			  if (HAL_GPIO_ReadPin(HCSR04_ECHO_GPIO_Port,HCSR04_ECHO_Pin) == 0){
				// ngat canh xuong thi tat timer di va tinh toan khoang cach
					HAL_TIM_Base_Stop(hcsr04.htim); // tat timer3
					// Khong nen tao ham con trong ngat, co the bi treo may 
					// Giai phap : tao mot state bao hoan thanh va check state nay lien tuc trong while(1) o int main()
				  hcsr04_state = HCSR04_COMPLETE_STATE; // bao la da hoan thanh
				}
			  else hcsr04_state = HCSR04_IDLE_STATE; // neu ngat lan 2 ma echo van =1 thi bao loi va cho ve idle
			  break;
			}
			
			default : break;
		}
   }
}

void HCSR04_start()
{	
 HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port,HCSR04_TRIG_Pin,GPIO_PIN_SET);
 hcsr04_state = HCSR04_GEN_PULSE_STATE;
 time_start_gen_pulse = HAL_GetTick();
}


void HCSR04_COMPLETE_CALLBACK(){
 // cac lenh xu li sau khi da complete
	// k nen de trong ngat nen ban vao day
	hcsr04.distance = kc;
  direction_handle(buff_distance);
}

void HCSR04_handle()
{
  switch(hcsr04_state){
		case HCSR04_GEN_PULSE_STATE:
		{
			if(HAL_GetTick()-time_start_gen_pulse>=1)
			{
				 HAL_GPIO_WritePin(HCSR04_TRIG_GPIO_Port,HCSR04_TRIG_Pin,GPIO_PIN_RESET);
         hcsr04_state = HCSR04_WAIT_EXT_RISING_STATE; // Ngay khi chan trigger len muc 1 thi chan echo cung len muc 1 de chuan bi nhan tin hieu
			}
			break;
		}
		
		case HCSR04_COMPLETE_STATE:
		{
			 kc = 0.017*(hcsr04.htim->Instance->CNT);
		   HCSR04_COMPLETE_CALLBACK();
			 break;
		} 
		default : break;
	}
}

void get_instance()
{   servo_write(&sv1,goc);
    static uint32_t t_read_hcsr;
		if (HAL_GetTick() - t_read_hcsr >= 300)
			{
					HCSR04_start();
					t_read_hcsr = HAL_GetTick();
		  } // cu 300ms cho chay hcsr04 1 lan de do duoc nhieu khoang cach
		HCSR04_handle();
}


/*==============init==============*/
void HCSR04_init(hcsr04_t *hcsr, TIM_HandleTypeDef *htim)
{
	 hcsr->htim= htim;
}
