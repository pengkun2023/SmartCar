
#include "my_pwm.h"


void My_PWM_Init(void)
{
		gpio_init(D0, GPO, 0, GPI_PULL_UP);
		gpio_init(D1, GPO, 0, GPI_PULL_UP);	
		gpio_init(D14, GPO, 0, GPI_PULL_UP);	
		gpio_init(D15, GPO, 0, GPI_PULL_UP);	

		pwm_init(PWM2_MODULE3_CHA_D2, 17 * 1000, 0);
		pwm_init(PWM2_MODULE3_CHB_D3, 17 * 1000, 0);
		pwm_init(PWM1_MODULE0_CHA_D12, 17 * 1000, 0);
		pwm_init(PWM1_MODULE0_CHB_D13, 17 * 1000, 0);
}


		

void Motor_Cart(int motor_rear_L, int motor_rear_R, int motor_front_L, int motor_front_R)
{
	// 右后轮 ==> 使用 D1引脚为方向引脚， D3引脚为PWM输出
		if (motor_rear_R > 0) {
				gpio_set_level(D1, 0);
				pwm_set_duty(PWM2_MODULE3_CHB_D3, motor_rear_R);
		}
		else {
				gpio_set_level(D1, 1);
				pwm_set_duty(PWM2_MODULE3_CHB_D3, -motor_rear_R);
		}
		
		// 左后轮
		if (motor_rear_L  > 0) {
				gpio_set_level(D0, 0);
				pwm_set_duty(PWM2_MODULE3_CHA_D2, motor_rear_L);
		}
		else {
				gpio_set_level(D0, 1);
				pwm_set_duty(PWM2_MODULE3_CHA_D2, -motor_rear_L);
		}
		
		//左前轮
		if (motor_front_L  > 0) {
				gpio_set_level(D14, 1);
				pwm_set_duty(PWM1_MODULE0_CHA_D12, motor_front_L);
		}
		else {
				gpio_set_level(D14, 0);
				pwm_set_duty(PWM1_MODULE0_CHA_D12, -motor_front_L);
		}
		// 右前轮
		if (motor_front_R  > 0) {
				gpio_set_level(D15, 1);
				pwm_set_duty(PWM1_MODULE0_CHB_D13, motor_front_R);
		}
		else {
				gpio_set_level(D15, 0);
				pwm_set_duty(PWM1_MODULE0_CHB_D13, -motor_front_R);
		}
}