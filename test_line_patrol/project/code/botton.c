#include "botton.h"


BOTTON_ENUM DisplayShow;

/***********************��ת****************************
//void Jump_Next(void)
//����Key4 ==> ��ʾ��һ��
********************************************************/

void Jump_Nxet(void)
{
	if (DisplayShow == show_car_run_OR_stop)	DisplayShow = show_image_value;
	else 										DisplayShow ++;
}

/********************��������**************************
//void Key_Set(void)
//ͨ����������
*******************************************************/
void Key_Set(void)
{
	if (KEY_SHORT_PRESS == key_get_state(KEY_1)){
		switch (DisplayShow)
		{
			case show_image_value:
				image_value += 5;
				break;
			case show_car_speed:
				
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
				
				break;
			case show_car_run_OR_stop:
				
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
				SpeedMode.stop = ~SpeedMode.stop;
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

