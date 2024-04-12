
#include "image.h"
uint8 image_binaryzation[MT9V03X_H][MT9V03X_W];
uint8 midline[MT9V03X_H], leftline[MT9V03X_H], rightline[MT9V03X_H], temp_data[MT9V03X_H];
uint8 Right_Lost_Line[MT9V03X_H], Left_Lost_Line[MT9V03X_H];
uint8 leftLost_flag, rightLost_flag, bothLost_flag, leftStart_flag, rightStart_flag;

uint8 image_copy[MT9V03X_H][MT9V03X_W];
uint8 threshold;
uint8 midLine_value;

uint8 image_value = 180;	//阈值


uint8 mid_weight_list[120] = 
{
	
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	
	
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	
	10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
//	4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
	9, 9, 9, 9, 9, 9, 9, 9, 9, 9,
	
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
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
	
	leftLost_flag = 0;
	rightLost_flag = 0;
	bothLost_flag = 0;
	leftStart_flag = 0;
	rightStart_flag = 0;

	for (uint8 i = MT9V03X_H - 1; i > 0; i --){
		if (binaryzation_image[i][mid_point] == 255){
			for (uint8 j = mid_point; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					Left_Lost_Line[i] = 0;	//丢线为1，反之为0
					break;
				}
			}
			for (uint8 j = mid_point; j < MT9V03X_W; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					Right_Lost_Line[i] = 0;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2] == 255){
			for (uint8 j = mid_point / 2; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					Left_Lost_Line[i] = 0;
					break;
				}
			}
			for (uint8 j = mid_point / 2; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					Right_Lost_Line[i] = 0;
					break;
				}
			}
		}
		else if (binaryzation_image[i][mid_point / 2 * 3] == 255){
			for (uint8 j = mid_point / 2 * 3; j > 0; j --){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j + 1] == 255){
					left_point = j;
					Left_Lost_Line[i] = 0;
					break;
				}
			}
			for (uint8 j = mid_point / 2 * 3; j < MT9V03X_W - 1; j ++){
				if (binaryzation_image[i][j] == 0 && binaryzation_image[i][j - 1] == 255){
					right_point = j;
					Right_Lost_Line[i] = 0;
					break;
				}
			}
		}
		else{
			left_point = 1;
			right_point = MT9V03X_W - 1;
			Left_Lost_Line[i] = 1;
			Right_Lost_Line[i] = 1;
		}
		leftline[i] = left_point;
		rightline[i] = right_point;
		midline[i] = (left_point + right_point) / 2;
//		ips200_show_float(0, 200, midline[i], 3, 2);
	}
	
//	for (uint8 i = MT9V03X_H - 1; i >= 0; i --){
//		if (Left_Lost_Line[i] == 1)		leftLost_flag ++;//单边丢线
//		if (Right_Lost_Line[i] == 1)	rightLost_flag ++;
//		if (Left_Lost_Line[i] == 1 && Right_Lost_Line[i] == 0)		bothLost_flag ++;
//		if (leftStart_flag == 0 && Left_Lost_Line[i] == 1)	leftStart_flag = i;
//		if (rightStart_flag == 0 && Right_Lost_Line[i] == 1)	rightStart_flag = i;
//	}
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


uint8 Abs_uint8(uint8 value)
{
	if (value < 0)	return -value;
	else			return value;
}

//--------------------------------------------------//
//左下角点检测
//void Fine_Point_RL(void) 
//
//---------------------------------------------------//


uint8 Fine_Point_RL(uint8 start_line, uint8 end_line) 
{
	uint8 RL_line_point = 0;
	if (leftLost_flag >= (0.9 * MT9V03X_H))		return 	RL_line_point;
	if (start_line >= MT9V03X_H - 6)	start_line = MT9V03X_H - 6;
	if (end_line <= 5)					end_line = 5;
	for (uint8 i = start_line; i > end_line; i --){
		if (RL_line_point == 0 &&
			Abs_uint8(leftline[i] - leftline[i + 1]) <= 5 &&
			Abs_uint8(leftline[i + 1] - leftline[i + 2]) <= 5 &&
			Abs_uint8(leftline[i + 2] - leftline[i + 3]) <= 5 &&
			Abs_uint8(leftline[i] - leftline[i - 2]) <= 5 &&
			Abs_uint8(leftline[i] - leftline[i - 3]) <= 10 &&
			Abs_uint8(leftline[i] - leftline[i - 4]) <= 10){
				
				RL_line_point = i;
				break;
			}		
	}
	return RL_line_point;
}

//-----------------------判断十字---------------------//
// 	void Discover_Crossroad(void) 
//
//---------------------------------------------------//
void Discover_Crossroad(void) 
{
	
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
	if (black_count >= 170)		Car_Straight(0);	//直行速度 ==> 0
}



/*******************图像处理*************************
// void Image_Deal(void)
****************************************************/

void Image_Deal(void)
{	
	//threshold = GetOSTU(mt9v03x_image);
	//image_value = threshold;
	Image_Binaryzation(image_value);
	Image_Erosion(image_binaryzation);
	Sweep_Line(image_binaryzation);
	FineMidLine_Weight();
	Draw_Lines();
}





