#include "image.h"
uint8 image_binaryzation[MT9V03X_H][MT9V03X_W];
uint8 midline[MT9V03X_H], leftline[MT9V03X_H], rightline[MT9V03X_H], temp_data[MT9V03X_H];
uint8 image_copy[MT9V03X_H][MT9V03X_W];


//================复制图像=================//
//void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W])
//========================================//
void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W])
{
	uint8 i, j;
	for (i = 0; i < MT9V03X_H; i++){
		for (j = 0; j < MT9V03X_W; j++)	image_copy[i][j] = mt9v03x_image[i][j]; 
	}
}


//==============大津法获取阈值===================//
//GetOSTU(uint tmp_image[MT9V03X_H][MT9V03X_W]);
//tmp_image[MT9V03X_H][MT9V03X_W] ==> image灰度图像
//==============================================//
uint8 GetOSTU(uint8 tmp_image[MT9V03X_H][MT9V03X_W])
{
	unsigned int i, j;
	unsigned long amount = 0;
	unsigned long pixel_back = 0;
	unsigned long pixel_fore = 0;
	unsigned long gray_fore = 0;
	unsigned long gray_back = 0;
	unsigned long gray_value;
	uint8 max_value, min_value, threshold;
	float sigma, omega, sigma_b, omega_fore, omega_back, percentage_fore, percentage_back;
	uint8 histogram[256];

	for (i = 0; i < MT9V03X_IMAGE_SIZE; i++)	histogram[i] = 0;	//初始化灰度直方图
	for (i = 0; i < MT9V03X_H; i ++){
		//统计灰度级中的每个像素在整幅图像中的个数
		for (j = 0; j < MT9V03X_W; j ++)	histogram[tmp_image[i][j]] ++;
	}
	for (min_value = 0; min_value <= 255 && !histogram[min_value]; min_value ++);	//获取最小灰度值
	for (max_value = 255; max_value > min_value && !histogram[min_value]; max_value --);	// 获取最大灰度值

	if (max_value == min_value)		return max_value;		//图像中只有一个颜色
	if (min_value + 1 == max_value)	return min_value;		//图像中有两个颜色

	for (i = min_value; i <= max_value; i ++)	amount += histogram[i];		//像素总数
	gray_value = 0;
	for (i = min_value; i <= max_value; i ++)	gray_value += histogram[i] * i;		//灰度值总数
	sigma_b = -1;
	for (i = min_value; i < max_value; i ++){
		pixel_fore += histogram[i];			//前景像素
		pixel_back = amount - pixel_back;	//背景像素
		omega_fore = (float) pixel_fore / amount;	//前景像素百分比
		omega_back = (float) pixel_back / amount;	 //背景像素百分比
		gray_fore += histogram[i] * i;		//前景的灰度值
		gray_back = gray_fore - gray_back; 	//背景的灰度值
		percentage_fore = (float) gray_fore / pixel_fore;	//前景灰度百分比
		percentage_back = (float) gray_back / pixel_back;	//背景灰度百分比
		sigma = omega_fore * omega_back * pow((percentage_fore - percentage_back), 2);	//类间方差
		if (sigma > sigma_b){
			sigma_b = sigma;
			threshold = i;
		}
	}
	return threshold;
}

//===============图像二值化================//
//Image_Binaryzation(uint8 value)
//value ==>	阈值
//========================================//
void Image_Binaryzation(uint8 value)//图像二值化
{
	uint8 temp_value;	
	for (uint8 i = 0; i < MT9V03X_H; i ++){
		for (uint8 j = 0; j < MT9V03X_W; j ++){
			temp_value = mt9v03x_image[i][j];
			if (temp_value < value)		image_binaryzation[i][j] = 0;
			else 						image_binaryzation[i][j] = 255;	
		}
	}
}	

//==================================================//
//Sweep_Line 扫线函数
//=================================================//
void Sweep_Line(void)
{
	uint8 i, j;
	if (image_binaryzation[MT9V03X_H - 1][MT9V03X_W / 2] == 0){
		if (image_binaryzation[MT9V03X_H - 1][5] == 255)	midline[MT9V03X_H - 1] = 5;
		else if (image_binaryzation[MT9V03X_H - 1][MT9V03X_W - 5] == 255)	midline[MT9V03X_H - 1] = MT9V03X_W - 5;
		else 	midline[MT9V03X_H - 1] = MT9V03X_W / 2;
	}
	else midline[MT9V03X_H - 1] = MT9V03X_W / 2;

	for (i = MT9V03X_H - 1; i > 0; i--){
		for (j = midline[i + 1]; j >= 0; j--){
			if (image_binaryzation[i][j] == 0 || j == 0){
				leftline[i] = j;
				break;
			}
		}
		for (j = midline[i + 1]; j <= MT9V03X_W - 1; j++){
			if (image_binaryzation[i][j] == 0 || j == MT9V03X_H){
				rightline[i] = j;
				break;
			}
		}
		midline[i] = (leftline[i] + rightline[i]) / 2;
		if (image_binaryzation[i - 1][midline[i]] == 0 || i == 0){
			for (j = i; j > 0; j--){
				midline[j] = midline[i];
				leftline[j] = leftline[i];
				rightline[j] = rightline[i];
			}
			break;
		}
	}
}
//===============画点===============//
//Draw_Dots(uint8 x, uint8, y, uint16 color)
//x ==> x坐标， y ==> y坐标， color ==> 需要设定的颜色
//color 在rgb565_color_enum中
//=================================//
void Draw_Dots(uint8 x, uint8 y, uint16 color)
{
	if ((x != MT9V03X_W - 1) &&(x != 0) ){
		if ((y != 0 && y != MT9V03X_H - 1)){
			ips200_draw_point(x, y, color);
			ips200_draw_point(x - 1, y, color);
			ips200_draw_point(x + 1, y, color);
		}
		else ips200_draw_point(x, y, color);
	}
	else 	ips200_draw_point(x, y, color);
}

//=============画线==================//
//Draw_Lines(void)
//===================================//

void Draw_Lines(void)
{
	for (uint8 i = MT9V03X_H - 1; i > 0; i --){
		Draw_Dots(rightline[i], i, RGB565_BLUE);
		Draw_Dots(leftline[i], i, RGB565_GREEN);
		Draw_Dots(midline[i], i, RGB565_RED);
	}
}


