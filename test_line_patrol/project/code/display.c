#include "display.h"

#define SHOW_X_MAX 		240
#define SHOW_Y_MAX		320

bool clear_flag;

void Display_Show(void)
{
	if (clear_flag){
		//ips200_clear();
	}
	switch (DisplayShow)
	{
		case show_image_value:
			ips200_show_string(0, 270, "show image value");
			ips200_show_int(0, 150, image_value, 3);
			ips200_show_int(0, 200, midLine_value, 3);
			break;
		case show_car_speed:
			ips200_show_string(0, 270, "show car speed");
			ips200_show_int(0, 150, image_value, 3);
			ips200_show_int(0, 200, speed_begin, 3);
			break;
		case show_car_run_OR_stop:
			ips200_show_string(0, 270, "show run_OR_stop");
			break;
		default:
			
			break;
			
	}	
}