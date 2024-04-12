#include "sevor.h"


#define SERVO_MOTOR_PWM1                (PWM4_MODULE2_CHA_C30)                      // 舵机1
#define SERVO_MOTOR_PWM2                (PWM1_MODULE3_CHA_D0)                       // 舵机2
#define SERVO_MOTOR_FREQ                (50 )                                       // 定义主板上舵机频率  范围 50-300
//------------------舵机占空比计算方式-----------------------//
#define SERVO_MOTOR_DUTY(x)         ((float)PWM_DUTY_MAX/(1000.0/(float)SERVO_MOTOR_FREQ)*(0.5+(float)(x)/90.0))    //舵机角度设置为0 - 180，90度为中值

static uint16 servo1_duty = 0, servo2_duty = 0;
//-------------------------------------------------------------------------------------------------------------------
// 函数简介     舵机连续控制函数
// 参数说明     _servo1_angle               舵机1的目标角度
// 参数说明     _servo2_angle               舵机2的目标角度
// 返回参数     _step_count                 舵机连续控制间隔次数
// 使用示例     servo_slow_ctrl(90, 90, 100);
// 备注信息     
//-------------------------------------------------------------------------------------------------------------------
void servo_slow_ctrl(uint16 _servo1_angle, uint16 _servo2_angle, float _step_count)
{
    float servo1_start = (float)servo1_duty, servo2_start = (float)servo2_duty;
    float servo1_step = (float)(_servo1_angle - servo1_duty)/_step_count, servo2_step = (float)(_servo2_angle - servo2_duty)/_step_count;
    while(1)
    {
        system_delay_ms(5);
        if(fabsf(servo1_start - (float)_servo1_angle) >= servo1_step)servo1_start += servo1_step;
        else servo1_start = _servo1_angle;
        pwm_set_duty(SERVO_MOTOR_PWM1, (uint32)SERVO_MOTOR_DUTY((uint16)servo1_start));
        
        if(fabsf(servo2_start - (float)_servo2_angle) >= servo2_step)servo2_start += servo2_step;
        else servo2_start = _servo2_angle;
        pwm_set_duty(SERVO_MOTOR_PWM2, (uint32)SERVO_MOTOR_DUTY((uint16)servo2_start));
        
        if(fabsf(servo1_start - (float)_servo1_angle) < 1 && fabsf(servo2_start - (float)_servo2_angle) < 1)
        {
            servo1_duty = (uint16)_servo1_angle;
            servo2_duty = (uint16)_servo2_angle;
            return;
        }
    }
    
}


//--------------------抓取------------------------//
//函数名称 	void Sevor_Crawl(void)
//功能		捡起地面上的卡片
//-----------------------------------------------//
void Sevor_Crawl(void)
{
	gpio_set_level(D1, 1);
	if(servo1_duty != 151 || servo2_duty != 134)	servo_slow_ctrl(151, 134, 120);
	servo_slow_ctrl(155, 132, 100);
	servo_slow_ctrl(130, 142, 50);
	servo_slow_ctrl(30, 10, 100);
	gpio_set_level(D1, 0);
}

//--------------------放下------------------------//
//函数名称 	void Sevor_Drop(void)
//功能		将收纳筐里的卡片放下
//-----------------------------------------------//
void Sevor_Drop(void)
{
	gpio_set_level(D1, 1);
	if(servo1_duty != 20 || servo2_duty != 2)		servo_slow_ctrl(20, 2, 120);
	servo_slow_ctrl(1, 0, 100);
	servo_slow_ctrl(40, 10, 50);
	servo_slow_ctrl(130, 142, 100);
	
	gpio_set_level(D1, 0);
}
//--------------------初始化------------------------//
//函数名称 	void Sevor_Init(void)
//功能		初始化舵机相关的功能和引脚
//--------------------------------------------------//
void Sevor_Init(void)
{
	gpio_init(D1, GPO, 0, GPO_PUSH_PULL);		//初始化电磁铁引脚
	//初始化机械臂舵机PWM
    pwm_init(SERVO_MOTOR_PWM1, SERVO_MOTOR_FREQ, (uint32)SERVO_MOTOR_DUTY(20));            
    pwm_init(SERVO_MOTOR_PWM2, SERVO_MOTOR_FREQ, (uint32)SERVO_MOTOR_DUTY(2)); 
	servo1_duty = 151;servo2_duty = 134;
}

