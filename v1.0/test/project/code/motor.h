#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "fsl_iomuxc.h"
#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_driver_gpio.h"
#include "zf_driver_timer.h"
#include "zf_driver_pwm.h"

#include <math.h>

#include "encoder.h"

typedef struct 
{
	float RL_kp, RL_ki, RL_kd;
	float RR_kp, RR_ki, RR_kd;
	float FL_kp, FL_ki, FL_kd;
	float FR_kp, FR_ki, FR_kd;

	float integral_RL, integral_RR, integral_FL, integral_FR;
	int integralRL_MAX, integralRR_MAX, integralFL_MAX, integralFR_MAX;
	int integralRL_MIN, integralRR_MIN, integralFL_MIN, integralFR_MIN;

}PID;

typedef struct 
{
	bool stop;
	int forward, back, left, right;
}Speed;

extern Speed SpeedMode;
extern int pid_output;
extern int speed_target_RL, speed_target_RR, speed_target_FL, speed_target_FR;
extern int speed_begin;
void Motor_Init(void);
void Motor_Control(bool run);
void Car_Straight(int speed);
int Abs_value(int value);

#endif