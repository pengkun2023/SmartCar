#include "encoder.h"


//-------------------------//
//补充：  需要进行滤波！！！
//------------------------//
#define	PASSAGE_R_L		QTIMER1_ENCODER1
#define	PASSAGE_R_R		QTIMER1_ENCODER2
#define	PASSAGE_F_L		QTIMER2_ENCODER2
#define	PASSAGE_F_R		QTIMER2_ENCODER1

int encoder_rear_L = 0, encoder_rear_R = 0, encoder_front_L = 0, encoder_front_R = 0;


void Encoder_Init(void)
{
	encoder_dir_init(QTIMER1_ENCODER2, QTIMER1_ENCODER2_CH1_C2, QTIMER1_ENCODER2_CH2_C24);	//rear left
	encoder_dir_init(QTIMER1_ENCODER1, QTIMER1_ENCODER1_CH1_C0, QTIMER1_ENCODER1_CH2_C1);	//rear right
	encoder_dir_init(QTIMER2_ENCODER2, QTIMER2_ENCODER2_CH1_C5, QTIMER2_ENCODER2_CH2_C25);	//front right
	encoder_dir_init(QTIMER2_ENCODER1, QTIMER2_ENCODER1_CH1_C3, QTIMER2_ENCODER1_CH2_C4);	//front left
	//编码器通道， 步进脉冲， 计数方向控制
}


void Encode_Get(void)
{
	encoder_rear_R = encoder_get_count(PASSAGE_R_R);
	encoder_rear_L = -encoder_get_count(PASSAGE_R_L);
	encoder_front_L = -encoder_get_count(PASSAGE_F_L);
	encoder_front_R = encoder_get_count(PASSAGE_F_R);
	
	encoder_clear_count(PASSAGE_R_R);
	encoder_clear_count(PASSAGE_R_L);
	encoder_clear_count(PASSAGE_F_L);
	encoder_clear_count(PASSAGE_F_R);
}