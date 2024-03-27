#include "botton.h"


BOTTON_ENUM DisplayShow;

/***********************跳转****************************
//void Jump_Next(void)
//按下Key4 ==> 显示下一个
********************************************************/

void Jump_Nxet(void)
{
	if (DisplayShow == show_car_run_OR_stop)	DisplayShow = show_image_value;
	else 										DisplayShow ++;
}

/********************按键设置**************************
//void Key_Set(void)
//通过按键调试
*******************************************************/
void Key_Set(void)
{
	
	speed_target_RL = speed_begin;
	speed_target_FL = speed_begin;
	speed_target_RR = speed_begin;
	speed_target_FR	= speed_begin;
	
	if (KEY_SHORT_PRESS == key_get_state(KEY_1)){
		switch (DisplayShow)
		{
			case show_image_value:
				image_value += 5;
				break;
			case show_car_speed:
				speed_begin += 1;
				break;
			case show_car_run_OR_stop:
				
				break;
			default:
				
				break;
				
		}	
		key_clear_state(KEY_1);
	}
	if (KEY_SHORT_PRESS == key_get_state(KEY_2)){
		switch (DisplayShow)
		{
			case show_image_value:
				image_value -= 5;
				break;
			case show_car_speed:
				speed_begin -= 1;
				break;
			case show_car_run_OR_stop:
				SpeedMode.stop = true;
				break;
			default:
				
				break;
				
		}	
		key_clear_state(KEY_2);
	}
	if (KEY_SHORT_PRESS == key_get_state(KEY_3)){
		switch (DisplayShow)
		{
			case show_image_value:
	
				break;
			case show_car_speed:
				
				break;
			case show_car_run_OR_stop:
				SpeedMode.stop = false;
				break;
			default:
				
				break;
				
		}	
		key_clear_state(KEY_3);
	}
	if (KEY_SHORT_PRESS == key_get_state(KEY_4)){
		Jump_Nxet();
		clear_flag = true;
		key_clear_state(KEY_4);
	}
}

