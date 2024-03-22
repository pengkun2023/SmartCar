#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "zf_device_mt9v03x.h"
#include "zf_device_ips200.h"
#include "zf_common_font.h"
#include "motor.h"

extern uint8 image_copy[MT9V03X_H][MT9V03X_W];
extern uint8 image_binaryzation[MT9V03X_H][MT9V03X_W], temp_data[MT9V03X_H];
uint8 GetOSTU(uint8 tmImage[MT9V03X_H][MT9V03X_W]);
void Sweep_Line(void);
void Image_Binaryzation(uint8 value);//Í¼Ïñ¶þÖµ»¯
void Draw_Dots(uint8 x, uint8 y, uint16 color);
void Draw_Lines(void);
void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W]);
#endif