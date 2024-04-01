/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"

// *************************** 例程使用步骤说明 ***************************
// 1.根据硬件连接说明连接好模块，使用电源供电(下载器供电会导致模块电压不足)
//
// 2.下载例程到单片机中，打开逐飞串口助手。
//
// 3.在逐飞串口助手中，选择示波器。
//
// 4.选择下载器对应的串口号，波特率(默认115200)，点击连接
//
// 5.示波器能立刻看到波形

// *************************** 例程测试说明 ***************************
// 1.本例程会通过 Debug 串口输出测试信息 请务必接好调试串口以便获取测试信息
//
// 2.连接好模块和核心板后（尽量使用配套主板测试以避免供电不足的问题） 烧录本例程 按下复位后程序开始运行
//


int main (void)
{
    clock_init(SYSTEM_CLOCK_600M);                                              // 不可删除
    debug_init();                                                               // 调试端口初始化
    system_delay_ms(3000);
	Motor_Init();
	
	//My_PWM_Init();
	
	pit_ms_init(PIT_CH0, 5);
	Encoder_Init();
	PID_Init();
	//uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);
	wireless_uart_init();
	//wireless_uart_init();
    // 设置逐飞助手使用DEBUG串口进行收发
    //seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    // 初始化逐飞助手示波器的结构体
	ips200_init(IPS200_TYPE_SPI);

	mt9v03x_init();

   
	

    
	system_delay_ms(1000);
	
    // 此处编写用户代码 例如外设初始化代码等

    while(1)
    {
        // 此处编写需要循环执行的代码
        ips200_show_string(0, 0, "Not Smart");
		ips200_show_string(0, 16, "Now_Speed_RL:");
		ips200_show_string(0, 32, "Now_Speed_RR:");
		ips200_show_string(0, 48, "Now_Speed_FL:");
		ips200_show_string(0, 64, "Now_Speed_FR:");
		ips200_show_float(100, 16, encoder_rear_L, 2, 3);
		ips200_show_float(100, 32, encoder_rear_R, 2, 3);
		ips200_show_float(100, 48, encoder_front_L, 2, 3);
		ips200_show_float(100, 64, encoder_front_R, 2, 3);
		ips200_show_string(0, 80, "Target_Speed:");
		ips200_show_float(100, 80, speed_target_RL, 3, 2);
        system_delay_ms(100);

        // 此处编写需要循环执行的代码
    }
}
