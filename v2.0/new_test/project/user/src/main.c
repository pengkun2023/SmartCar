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







int main (void)
{
    clock_init(SYSTEM_CLOCK_600M);                                              // 不可删除
    debug_init();                                                               // 调试端口初始化
    system_delay_ms(300);
	Init();
	system_delay_ms(1000);
	
    // 此处编写用户代码 例如外设初始化代码等

    while(1)
    {
        // 此处编写需要循环执行的代码
		key_scanner();
		Display_Show();
            // 在发送前将图像备份再进行发送，这样可以避免图像出现撕裂的问题
		if (mt9v03x_finish_flag){
			//image_value = GetOSTU(image_binaryzation);
			Image_Deal();
			//wireless_uart_send_buffer(temp_data, 120);
			//seekfree_assistant_camera_send();
			ips200_show_gray_image(0, 0, image_binaryzation[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
			mt9v03x_finish_flag = 0;
			
		}
		

		//ips200_show_int(0, 250, pid_output, 4);
        // 此处编写需要循环执行的代码
    }
}


