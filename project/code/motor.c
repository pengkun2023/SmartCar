#include "motor.h"

#define DIR_REAR_R 		D1
#define DIR_REAR_L		D0
#define DIR_FRONT_R		D15
#define DIR_FRONT_L		D14

#define PWM_MAX			2000
#define MAX_INTEGRAL	100

#define PWM_REAR_R		PWM2_MODULE3_CHB_D3
#define PWM_REAR_L		PWM2_MODULE3_CHA_D2
#define PWM_FRONT_R		PWM1_MODULE0_CHB_D13
#define PWM_FRONT_L		PWM1_MODULE0_CHA_D12

int motor_rear_R, motor_rear_L, motor_front_L, motor_front_R;
int speed_target_RL =50;
int speed_target_RR =50;
int speed_target_FL = 50;
int speed_target_FR = 50;

void Motor_Init(void)
{
	gpio_init(DIR_REAR_R, GPO, 0, GPI_PULL_UP);
	gpio_init(DIR_REAR_L, GPO, 0, GPI_PULL_UP);	
	gpio_init(DIR_FRONT_R, GPO, 0, GPI_PULL_UP);	
	gpio_init(DIR_FRONT_L, GPO, 0, GPI_PULL_UP);	

	pwm_init(PWM_REAR_R, 17 * 1000, 0);
	pwm_init(PWM_REAR_L, 17 * 1000, 0);
	pwm_init(PWM_FRONT_R, 17 * 1000, 0);
	pwm_init(PWM_FRONT_L, 17 * 1000, 0);
}


//----------------------位置式PID-----------------------//


//--------PWM限值函数-------//
float Limit_Pwm(float pwm_value)
{
	if (pwm_value > PWM_MAX)		return PWM_MAX;
	else if (pwm_value < -PWM_MAX)  return -PWM_MAX;
	else							return pwm_value;
	
}
//-----------END-----------//

//--------取绝对值函数-------//
int Abs_value(int value)
{
	if (value >= 0){
		return value;
	}
	else {
		return -value;
	}
}
//----------END------------//

//----------速度环----------/

PID SpeedPid;

void PID_Init(void)
{
	SpeedPid.RL_kp = 3.0;			//3.0    
	SpeedPid.RL_ki = 0.07;

	SpeedPid.RR_kp = 3.5;
	SpeedPid.RR_ki = 0.05;

	SpeedPid.FL_kp = 3.0;
	SpeedPid.FL_ki = 0.07;

	SpeedPid.FR_kp = 3.0;
	SpeedPid.FR_ki = 0.05;

	SpeedPid.integral_RL = 0.0;
	SpeedPid.integral_RR = 0.0;
	SpeedPid.integral_FL = 0.0;
	SpeedPid.integral_FR = 0.0;
	
	SpeedPid.integralRL_MAX = 800;
	SpeedPid.integralRR_MAX = 700;
	SpeedPid.integralFL_MAX = 800;
	SpeedPid.integralFR_MAX = 700;

	SpeedPid.integralRL_MIN = -SpeedPid.integralRL_MAX;
	SpeedPid.integralRR_MIN = -SpeedPid.integralRR_MAX;
	SpeedPid.integralFL_MIN = -SpeedPid.integralFL_MAX;
	SpeedPid.integralFR_MIN = -SpeedPid.integralFR_MAX;
}


int	pid_output = 0;

int SpeedPid_RL(PID *SpeedPid, int encoder_value_rl, int target_speed_RL)
{
	static float err_RL, output_RL;


	err_RL = target_speed_RL - encoder_value_rl;
	SpeedPid->integral_RL += SpeedPid->RL_ki * err_RL;
	//积分限值
	if (SpeedPid->integral_RL > SpeedPid->integralRL_MAX)		SpeedPid->integral_RL = SpeedPid->integralRL_MAX;
	if (SpeedPid->integral_RL < SpeedPid->integralRL_MIN)		SpeedPid->integral_RL = SpeedPid->integralRL_MIN;

	output_RL = SpeedPid->RL_kp * (target_speed_RL + err_RL * 3) + SpeedPid->integral_RL;
	return (int)output_RL;
}

int SpeedPid_RR(PID *SpeedPid, int encoder_value_rr, int target_speed_RR)
{
	static float err_RR, output_RR;


	err_RR = target_speed_RR - encoder_value_rr;
	SpeedPid->integral_RR += SpeedPid->RR_ki * err_RR;
	//积分限值
	if (SpeedPid->integral_RR > SpeedPid->integralRR_MAX)		SpeedPid->integral_RR = SpeedPid->integralRR_MAX;
	if (SpeedPid->integral_RR < SpeedPid->integralRR_MIN)		SpeedPid->integral_RR = SpeedPid->integralRR_MIN;

	output_RR = SpeedPid->RR_kp * (target_speed_RR + err_RR * 3) + SpeedPid->integral_RR;
	return (int)output_RR;
}

int SpeedPid_FL(PID *SpeedPid, int encoder_value_fl, int target_speed_FL)
{
	static float err_FL, output_FL;


	err_FL = target_speed_FL - encoder_value_fl;
	SpeedPid->integral_FL += SpeedPid->FL_ki * err_FL;
	//积分限值
	if (SpeedPid->integral_FL > SpeedPid->integralFL_MAX)		SpeedPid->integral_FL = SpeedPid->integralFL_MAX;
	if (SpeedPid->integral_FL < SpeedPid->integralFL_MIN)		SpeedPid->integral_FL = SpeedPid->integralFL_MIN;

	output_FL = SpeedPid->FL_kp * (target_speed_FL + err_FL * 3) + SpeedPid->integral_FL;
	return (int)output_FL;
}

int SpeedPid_FR(PID *SpeedPid, int encoder_value_fr, int target_speed_FR)
{
	static float err_FR, output_FR;


	err_FR = target_speed_FR - encoder_value_fr;
	SpeedPid->integral_FR += SpeedPid->FR_ki * err_FR;
	//积分限值
	if (SpeedPid->integral_FR > SpeedPid->integralFR_MAX)		SpeedPid->integral_FR = SpeedPid->integralFR_MAX;
	if (SpeedPid->integral_FR < SpeedPid->integralFR_MIN)		SpeedPid->integral_FR = SpeedPid->integralFR_MIN;

	output_FR = SpeedPid->FR_kp * (target_speed_FR + err_FR * 2) + SpeedPid->integral_FR;
	return (int)output_FR;
}

//-------------END-------------//



void Pid_SpeedControl(void)
{
	int SC_pid_RL = SpeedPid_RL(&SpeedPid, encoder_rear_L, speed_target_RL);
	motor_rear_L = (int)Limit_Pwm(SC_pid_RL);
	
	int SC_pid_RR = SpeedPid_RR(&SpeedPid, encoder_rear_R, speed_target_RR);
	motor_rear_R = (int)Limit_Pwm(SC_pid_RR);
	
	int SC_pid_FL = SpeedPid_FL(&SpeedPid, encoder_front_L, speed_target_FL);
	motor_front_L = (int)Limit_Pwm(SC_pid_FL);
	
	int SC_pid_FR = SpeedPid_FR(&SpeedPid, encoder_front_R, speed_target_FR);
	motor_front_R = (int)Limit_Pwm(SC_pid_FR);
}

//-----------------------END--------------------------//
void Motor_Control(bool run)
{
	if(run){
		Pid_SpeedControl();					// pid校正
	}
	else{
		motor_front_L = 0, motor_front_R = 0, motor_rear_L = 0, motor_rear_R = 0;
	}

	//需要使用三段式进行迭代！！！
	if (motor_rear_R > 0) {
			gpio_set_level(DIR_REAR_R, 0);
			pwm_set_duty(PWM_REAR_R, motor_rear_R);
	}
	else {
			gpio_set_level(DIR_REAR_R, 1);
			pwm_set_duty(PWM_REAR_R, -motor_rear_R);
	}
	
	// 左后轮
	if (motor_rear_L  > 0) {
			gpio_set_level(DIR_REAR_L, 0);
			pwm_set_duty(PWM_REAR_L, motor_rear_L);
	}
	else {
			gpio_set_level(DIR_REAR_L, 1);
			pwm_set_duty(PWM_REAR_L, -motor_rear_L);
	}
	
	//左前轮
	if (motor_front_L  > 0) {
			gpio_set_level(DIR_FRONT_L, 1);
			pwm_set_duty(PWM_FRONT_L, motor_front_L);
	}
	else {
			gpio_set_level(DIR_FRONT_L, 0);
			pwm_set_duty(PWM_FRONT_L, -motor_front_L);
	}
	// 右前轮
	if (motor_front_R  > 0) {
			gpio_set_level(DIR_FRONT_R, 1);
			pwm_set_duty(PWM_FRONT_R, motor_front_R);
	}
	else {
			gpio_set_level(DIR_FRONT_R, 0);
			pwm_set_duty(PWM_FRONT_R, -motor_front_R);
	}
	
}

