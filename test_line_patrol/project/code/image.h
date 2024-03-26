#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "zf_device_mt9v03x.h"
#include "zf_device_ips200.h"
#include "zf_common_font.h"
#include "motor.h"

extern uint8 image_copy[MT9V03X_H][MT9V03X_W];
extern uint8 image_binaryzation[MT9V03X_H][MT9V03X_W], temp_data[MT9V03X_H];
extern uint8 image_value;



void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W]);
//uint8 GetOSTU(uint8 tmImage[MT9V03X_H][MT9V03X_W]);
void Image_Binaryzation(uint8 value);//Í¼Ïñ¶þÖµ»¯
void Image_Erosion(uint8 image[MT9V03X_H][MT9V03X_W]);
short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W]);
void Draw_Dots(uint8 x, uint8 y, uint16 color);
void Sweep_Line(uint8 binaryzation_image[MT9V03X_H][MT9V03X_W]);
void Draw_Lines(void);
void Image_Deal(void);
#endif