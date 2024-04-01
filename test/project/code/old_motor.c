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
	if (pwm_value > PWM_MAX)	return PWM_MAX;
	else if (pwm_value < -PWM_MAX)  return -PWM_MAX;
	else	return pwm_value;
	
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

//----------增量式pid----------/
struct IncrementalPid
{
	float rear_L_kp, rear_L_ki, rear_L_kd;
	float rear_R_kp, rear_R_ki, rear_R_kd;
	float front_L_kp, front_L_ki, front_L_kd;
	float front_R_kp, front_R_ki, front_R_kd;

	float RL_last_err, RR_last_err, FL_last_err, FR_last_err;
	float RL_last2_err, RR_last2_err, FL_last2_err, FR_last2_err;
}IncrementalPid;

void IncrementalPid_Init(void)
{
	IncrementalPid.rear_L_kp = 3.0;
	IncrementalPid.rear_L_ki = 0.05;
	IncrementalPid.rear_L_kd = 10.0;
	
	IncrementalPid.rear_R_kp = 1.0;
	IncrementalPid.rear_R_ki = 5.0;
	IncrementalPid.rear_R_kd = 10.0;
	
	IncrementalPid.front_L_kp = 1.0;
	IncrementalPid.front_L_ki = 5.0;
	IncrementalPid.front_L_kd = 10.0;
	
	IncrementalPid.front_R_kp = 1.0;
	IncrementalPid.front_R_ki = 5.0;
	IncrementalPid.front_R_kd = 10.0;
	
	IncrementalPid.RL_last_err = 0.0f;
	IncrementalPid.RL_last2_err = 0.0f;
	
	IncrementalPid.RR_last_err = 0.0f;
	IncrementalPid.RR_last2_err = 0.0f;
	
	IncrementalPid.FL_last_err = 0.0f;
	IncrementalPid.FL_last2_err = 0.0f;
	
	IncrementalPid.FR_last_err = 0.0f;
	IncrementalPid.FR_last2_err = 0.0f;
}

int	pid_output = 0;

int IncrementalPidRear_L(int encoder_value_rl, int target_speed_LR)
{
	static float err_RL, incremnt_RL_out, output_RL;
	err_RL = target_speed_LR - encoder_value_rl;
	
	//incremnt_RL_out = IncrementalPid.rear_L_kp * (err_RL - IncrementalPid.RL_last_err) + IncrementalPid.rear_L_ki * err_RL + IncrementalPid.rear_L_kd * (err_RL - 2 * IncrementalPid.RL_last2_err + IncrementalPid.RL_last_err);
	incremnt_RL_out = 1.0 * IncrementalPid.rear_L_kp * target_speed_LR * 1;
	
//	if (abs(err_RL) < 0.1)	incremnt_RL_out = err_RL;
	//output_RL += incremnt_RL_out;
	IncrementalPid.RL_last2_err = IncrementalPid.RL_last_err;
	IncrementalPid.RL_last_err = err_RL;
	output_RL = Limit_Pwm(output_RL);
	
	pid_output = output_RL;
	
	static float error=0;
	error+=err_RL * IncrementalPid.rear_L_ki;
	if(error > 700)    error = 700;
	if(error < -700)   error = -700;
	return (target_speed_LR+err_RL*3) * IncrementalPid.rear_L_kp+(int)error;
	//return (int)output_RL;
}

int IncrementalPidRear_R(int encoder_value_rr, int target_speed_RR)
{
	static float err_RR, incremnt_RR_out, output_RR;
	err_RR = target_speed_RR - encoder_value_rr;
	
	incremnt_RR_out = IncrementalPid.rear_R_kp * (err_RR - IncrementalPid.RR_last_err) + IncrementalPid.rear_R_ki * err_RR + IncrementalPid.rear_R_kd * (err_RR - 2 * IncrementalPid.RR_last2_err + IncrementalPid.RR_last_err);
	
	if (abs(err_RR) < 0.1)	incremnt_RR_out = err_RR;
	output_RR += incremnt_RR_out;
	IncrementalPid.RR_last2_err = IncrementalPid.RR_last_err;
	IncrementalPid.RR_last_err = err_RR;
	output_RR = Limit_Pwm(output_RR);
	
	return (int)output_RR;
}

int IncrementalPidFront_L(int encoder_value_fl, int target_speed_LF)
{
	static float err_FL, incremnt_FL_out, output_FL;
	err_FL = target_speed_LF - encoder_value_fl;
	
	incremnt_FL_out = IncrementalPid.front_L_kp * (err_FL - IncrementalPid.FL_last_err) + IncrementalPid.front_L_ki * err_FL + IncrementalPid.front_L_kd * (err_FL - 2 * IncrementalPid.FL_last2_err + IncrementalPid.FL_last_err);
	
	if (abs(err_FL) < 0.1)	incremnt_FL_out = err_FL;
	output_FL += incremnt_FL_out;
	IncrementalPid.FL_last2_err = IncrementalPid.FL_last_err;
	IncrementalPid.FL_last_err = err_FL;
	output_FL = Limit_Pwm(output_FL);
	
	return (int)output_FL;
}

int IncrementalPidFront_R(int encoder_value_fr, int target_speed_RF)
{
	static float err_FR, incremnt_FR_out, output_FR;
	err_FR = target_speed_RF - encoder_value_fr;
	
	incremnt_FR_out = IncrementalPid.front_R_kp * (err_FR - IncrementalPid.FR_last_err) + IncrementalPid.front_R_ki * err_FR + IncrementalPid.front_R_kd * (err_FR - 2 * IncrementalPid.FR_last2_err + IncrementalPid.FR_last_err);
	
	if (abs(err_FR) < 0.1)	incremnt_FR_out = err_FR;
	output_FR += incremnt_FR_out;
	IncrementalPid.FR_last2_err = IncrementalPid.FR_last_err;
	IncrementalPid.FR_last_err = err_FR;
	output_FR = Limit_Pwm(output_FR);
	
	return (int)output_FR;
}


//-------------END-------------//



void Pid_SpeedControl(void)
{
	int SC_pid_RL = IncrementalPidRear_L(encoder_rear_L, speed_target_RL);
	motor_rear_L = (int)Limit_Pwm(SC_pid_RL);
	
//	int SC_pid_RR = IncrementalPidRear_R(encoder_rear_R, speed_target_RR);
//	motor_rear_R = (int)Limit_Pwm(SC_pid_RR);
//	
//	int SC_pid_FL = IncrementalPidFront_L(encoder_front_L, speed_target_FL);
//	motor_front_L = (int)Limit_Pwm(SC_pid_FL);
//	
//	int SC_pid_FR = IncrementalPidFront_R(encoder_front_R, speed_target_FR);
//	motor_front_R = (int)Limit_Pwm(SC_pid_FR);
}

//-----------------------END--------------------------//
void Motor_Control(bool run)
{
	if(run){
		Pid_SpeedControl();					// 增量式pid校正
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

