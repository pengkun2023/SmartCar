#ifndef _my_pwm_h_
#define _my_pwm_h_

#include "fsl_iomuxc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"
#include "zf_driver_pwm.h"




void My_PWM_Init(void);
void Motor_Cart(int motor_rear_L, int motor_rear_R, int motor_front_L, int motor_front_R);

#endif