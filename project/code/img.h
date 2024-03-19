#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "fsl_qtmr.h"
#include "fsl_iomuxc.h"
#include "zf_driver_gpio.h"

#include "zf_driver_encoder.h"

extern int encoder_rear_L, encoder_rear_R, encoder_front_L, encoder_front_R;	//±àÂëÆ÷µÄÖµ

void Encoder_Init(void);
void Encode_Get(void);

#endif