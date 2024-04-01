
#include "image.h"
uint8 image_binaryzation[MT9V03X_H][MT9V03X_W];
uint8 midline[MT9V03X_H], leftline[MT9V03X_H], rightline[MT9V03X_H], temp_data[MT9V03X_H];
uint8 image_copy[MT9V03X_H][MT9V03X_W];
uint8 threshold;
uint8 midLine_value;

uint8 image_value = 180;	//阈值


uint8 mid_weight_list[120] = 
{
	
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	

	5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
	
//	4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};


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
//uint8 GetOSTU(uint8 tmp_image[MT9V03X_H][MT9V03X_W])
//{
//	unsigned int i, j;
//	unsigned long amount = 0;
//	unsigned long pixel_back = 0;
//	unsigned long pixel_fore = 0;
//	unsigned long gray_fore = 0;
//	unsigned long gray_back = 0;
//	unsigned long gray_value;
//	uint8 max_value, min_value, threshold;
//	float sigma, omega, sigma_b, omega_fore, omega_back, percentage_fore, percentage_back;
//	uint8 histogram[256];

//	for (i = 0; i < MT9V03X_IMAGE_SIZE; i++)	histogram[i] = 0;	//初始化灰度直方图
//	for (i = 0; i < MT9V03X_H; i ++){
//		//统计灰度级中的每个像素在整幅图像中的个数
//		for (j = 0; j < MT9V03X_W; j ++)	histogram[tmp_image[i][j]] ++;
//	}
//	for (min_value = 0; min_value <= 255 && !histogram[min_value]; min_value ++);	//获取最小灰度值
//	for (max_value = 255; max_value > min_value && !histogram[min_value]; max_value --);	// 获取最大灰度值

//	if (max_value == min_value)		return max_value;		//图像中只有一个颜色
//	if (min_value + 1 == max_value)	return min_value;		//图像中有两个颜色

//	for (i = min_value; i <= max_value; i ++)	amount += histogram[i];		//像素总数
//	gray_value = 0;
//	for (i = min_value; i <= max_value; i ++)	gray_value += histogram[i] * i;		//灰度值总数
//	sigma_b = -1;
//	for (i = min_value; i < max_value; i ++){
//		pixel_fore += histogram[i];			//前景像素
//		pixel_back = amount - pixel_back;	//背景像素
//		omega_fore = (float) pixel_fore / amount;	//前景像素百分比
//		omega_back = (float) pixel_back / amount;	 //背景像素百分比
//		gray_fore += histogram[i] * i;		//前景的灰度值
//		gray_back = gray_fore - gray_back; 	//背景的灰度值
//		percentage_fore = (float) gray_fore / pixel_fore;	//前景灰度百分比
//		percentage_back = (float) gray_back / pixel_back;	//背景灰度百分比
//		sigma = omega_fore * omega_back * pow((percentage_fore - percentage_back), 2);	//类间方差
//		if (sigma > sigma_b){
//			sigma_b = sigma;
//			threshold = i;
//		}
//	}
//	return threshold;
//}
short GetOSTU (unsigned char tmImage[MT9V03X_H][MT9V03X_W])
{
    signed short i, j;
    unsigned long Amount = 0;
    unsigned long PixelBack = 0;
    unsigned long PixelshortegralBack = 0;
    unsigned long Pixelshortegral = 0;
    signed long PixelshortegralFore = 0;
    signed long PixelFore = 0;
    float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差;
    signed short MinValue, MaxValue;
    signed short Threshold = 0;
    unsigned char HistoGram[256];              //

    for (j = 0; j < 256; j++)
        HistoGram[j] = 0; //初始化灰度直方图

    for (j = 0; j < MT9V03X_H; j++)
    {
        for (i = 0; i < MT9V03X_W; i++)
        {
            HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
        }
    }

    for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //获取最小灰度的值
    for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //获取最大灰度的值

    if (MaxValue == MinValue)
        return MaxValue;         // 图像中只有一个颜色
    if (MinValue + 1 == MaxValue)
        return MinValue;        // 图像中只有二个颜色

    for (j = MinValue; j <= MaxValue; j++)
        Amount += HistoGram[j];        //  像素总数

    Pixelshortegral = 0;
    for (j = MinValue; j <= MaxValue; j++)
    {
        Pixelshortegral += HistoGram[j] * j;        //灰度值总数
    }
    SigmaB = -1;
    for (j = MinValue; j < MaxValue; j++)
    {
        PixelBack = PixelBack + HistoGram[j];     //前景像素点数
        PixelFore = Amount - PixelBack;           //背景像素点数
        OmegaBack = (float) PixelBack / Amount;   //前景像素百分比
        OmegaFore = (float) PixelFore / Amount;   //背景像素百分比
        PixelshortegralBack += HistoGram[j] * j;  //前景灰度值
        PixelshortegralFore = Pixelshortegral - PixelshortegralBack;  //背景灰度值
        MicroBack = (float) PixelshortegralBack / PixelBack;   //前景灰度百分比
        MicroFore = (float) PixelshortegralFore / PixelFore;   //背景灰度百分比
        Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);   //计算类间方差
        if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
        {
            SigmaB = Sigma;
            Threshold = j;
        }
    }
    return Threshold;                        //返回最佳阈值;
}



//===============图像二值化================//
//Image_Binaryzation(uint8 value)
//value ==>	阈值
//========================================//
void Image_Binaryzation(uint8 value)
{
	uint8 temp_value;	
	for (uint8 i = 0; i < MT9V03X_H; i ++){
		for (uint8 j = 0; j < MT9V03X_W; j ++){
			temp_value = mt9v03x_image[i][j];
			if (temp_value < value)		image_binaryzation[i][j] = 0;			//Black
			else 						image_binaryzation[i][j] = 255;			//White
		}
	}
}	
//=================图像降噪(腐蚀)=====================//
//void Image_Erosion(uint8 image[MT9V03X_H][MT9V03X_W])
//==================================================//
void Image_Erosion(uint8 image[MT9V03X_H][MT9V03X_W])
{
	for (uint8 i = 1; i < MT9V03X_H - 1; i ++){
		for (uint8 j = 1; j < MT9V03X_W; j ++){
			if ((image[i][j] == 0)
				&& (image[i + 1][j] + image[i][j + 1] + image[i - 1][j] + image[i][j - 1]) > (255 * 2)) 	image[i][j] = 255;			
			else if ((image[i][j] == 255)
					&& (image[i + 1][j] + image[i - 1][j] + image[i][j + 1] + image[i][j - 1]) < (255 * 2))	image[i][j] = 0;
		}
	}
}


//==================================================//
//Sweep_Line 扫线函数
//=================================================//

void Sweep_Line(uint8 binaryzation_image[MT9V03X_H][MT9V03X_W])
{
	uint8 left_point = 1;
	uint8 right_point = MT9V03X_W - 1;
	uint8 mid_point = MT9V03X_W / 2;

	for (uint8 i = MT9V03X_H - 1; i > 0; i --){
		if (binaryzation_image[i][mid_point] == 255){
			for (uint8 j = mid_point; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point; j < MT9V03X_W; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2] == 255){
			for (uint8 j = mid_point / 2; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point / 2; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2 * 3] == 255){
			for (uint8 j = mid_point / 2 * 3; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					break;
				}
			}
			for (uint8 j = mid_point / 2 * 3; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					break;
				}
			}
		}
		else{
			left_point = 1;
			right_point = MT9V03X_W - 1;
		}
		leftline[i] = left_point;
		rightline[i] = right_point;
		midline[i] = (left_point + right_point) / 2;
//		ips200_show_float(0, 200, midline[i], 3, 2);
	}
}



//===============画点===============//
//Draw_Dots(uint8 x, uint8, y, uint16 color)
//x ==> x坐标， y ==> y坐标， color ==> 需要设定的颜色
//color 在rgb565_color_enum中
//=================================//
void Draw_Dots(uint8 x, uint8 y, uint16 color)
{
	if ((x != MT9V03X_W - 1) &&(x != 0) && (x != 1) && (x != MT9V03X_W - 2)){
		if ((y != 0) && (y != MT9V03X_H - 1)){
			ips200_draw_point(x, y, color);
			ips200_draw_point(x - 2, y, color);
			ips200_draw_point(x + 2, y, color);
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

/*******************权重计算中线*************************
// void FineMidLine_Weight(void)
****************************************************/
void FineMidLine_Weight(void)
{
	uint16 weight_sum = 0;
	int mid_deviation = 0;	//偏差值
	uint8 last_line_flag = 0;
	uint16 weight_mid_sum = 0;
	
	for (uint8 i = MT9V03X_H - 1; i > 0; i --){
		if (i == MT9V03X_H - 1){
			weight_mid_sum += midline[i] * mid_weight_list[i];		//分子 ==> 中线值 * 中线权重值
			weight_sum += mid_weight_list[i];	//所有的权重之和
		}
		else {
			mid_deviation = Abs_value((int)(midline[i] - midline[i + 1]));
			if (last_line_flag == 1) 		continue;
			else  if (mid_deviation > 34 && last_line_flag == 0){
				last_line_flag = 1;
				continue;
			}
			else {
				weight_mid_sum += midline[i] * mid_weight_list[i];
				weight_sum += mid_weight_list[i];
			}
		}
	}
	
	midLine_value = (uint8)(weight_mid_sum / weight_sum);
}

/*******************偏差值处理*************************
// void Deviation_Deal()
****************************************************/

void Deviation_Deal(void)
{
	uint8 mid_point = MT9V03X_W / 2;
	int deviation = mid_point - midLine_value;
	if (deviation > 0){
		speed_target_FR = speed_begin + deviation;
		speed_target_RR = speed_target_FR;
		
		speed_target_FL = Abs_value(speed_begin - deviation);
		speed_target_RL = Abs_value(speed_target_FL);
	}
	else if (deviation < 0){
		speed_target_FL = speed_begin - deviation;
		speed_target_RL = speed_target_FL;
		speed_target_FR = Abs_value(speed_begin + deviation);
		speed_target_RR = Abs_value(speed_target_FR);
	}
	else		Car_Straight(speed_begin);
	
}

/***************************************************
//void Protect(void)
//当车冲出赛道的时候，停车
***************************************************/
void Protect(void)
{
	uint8 black_count = 0;
	for (uint8 i = MT9V03X_W - 1; i > 0; i --){
		if (image_binaryzation[MT9V03X_H - 1][i] == RGB565_BLACK)	black_count ++;
	}
	if (black_count >= 170)		Car_Straight(0);
}



/*******************图像处理*************************
// void Image_Deal(void)
****************************************************/

void Image_Deal(void)
{	
	//threshold = GetOSTU(image_binaryzation);
	Image_Binaryzation(image_value);
	Image_Erosion(image_binaryzation);
	Sweep_Line(image_binaryzation);
	FineMidLine_Weight();
	Draw_Lines();
}





