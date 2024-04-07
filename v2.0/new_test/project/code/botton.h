#ifndef _BOTTON_H_
#define _BOTTON_H_

#include "zf_device_key.h"
#include "zf_device_ips200.h"
#include "image.h"
#include "display.h"
#include "motor.h"

typedef enum BOTTON_ENUM
{
	show_image_value,
	show_car_speed,
	show_car_run_OR_stop,
}BOTTON_ENUM;

extern BOTTON_ENUM DisplayShow;		//×´Ì¬»ú³õÊ¼»¯

void Key_Set(void);
void Botton_Init(void);
#endif