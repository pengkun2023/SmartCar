#include "display.h"


void Display_Init(void)
{
	// 设置屏幕为SPI
	ips200_init(IPS200_TYPE_SPI);
}

void Display_Img(void)
{
	// 显示灰度图像（未被二值化处理的）
	ips200_displayimage03x((const uint8 *)mt9v03x_image, 240, 100);
	
}