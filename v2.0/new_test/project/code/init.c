/**********************初始化*************************/
//Created by PengKun
/*****************************************************/

#include "init.h"

/**********************所有模块初始化*************************/
//void Init(void)
/************************************************************/

void Init(void)
{
	Encoder_Init();
	Motor_Init();
	pit_ms_init(PIT_CH0, 5);
	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
	ips200_init(IPS200_TYPE_SPI);
    mt9v03x_init();
	wireless_uart_init();
	Botton_Init();
	seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_binaryzation[0], MT9V03X_W, MT9V03X_H);
}