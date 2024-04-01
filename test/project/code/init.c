/******************************************/
//	Created by pengkun on 2024/4/1
/******************************************/

#include "init.h"

void All_Init(void)
{
	imu963ra_init();	//ÍÓÂÝÒÇ
	Encoder_Init();		//±àÂëÆ÷
	Motor_Init();		//µç»ú¿ØÖÆ
	pit_ms_init(PIT_CH0, 5);	
	wireless_uart_init();	
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
	ips200_init(IPS200_TYPE_SPI);
    mt9v03x_init();	
	key_init(10);
	seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_binaryzation[0], MT9V03X_W, MT9V03X_H);
}