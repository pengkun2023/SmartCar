/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/
#include "zf_common_headfile.h"

// *************************** ����ʹ�ò���˵�� ***************************
// 1.����Ӳ������˵�����Ӻ�ģ�飬ʹ�õ�Դ����(����������ᵼ��ģ���ѹ����)
//
// 2.�������̵���Ƭ���У�����ɴ������֡�
//
// 3.����ɴ��������У�ѡ��ʾ������
//
// 4.ѡ����������Ӧ�Ĵ��ںţ�������(Ĭ��115200)���������
//
// 5.ʾ���������̿�������

// *************************** ���̲���˵�� ***************************
// 1.�����̻�ͨ�� Debug �������������Ϣ ����ؽӺõ��Դ����Ա��ȡ������Ϣ
//
// 2.���Ӻ�ģ��ͺ��İ�󣨾���ʹ��������������Ա��⹩�粻������⣩ ��¼������ ���¸�λ�����ʼ����
//


int main (void)
{
    clock_init(SYSTEM_CLOCK_600M);                                              // ����ɾ��
    debug_init();                                                               // ���Զ˿ڳ�ʼ��
    system_delay_ms(300);

	Encoder_Init();
	Motor_Init();
	pit_ms_init(PIT_CH0, 5);
	wireless_uart_init();
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
	ips200_init(IPS200_TYPE_SPI);
    mt9v03x_init();
	
	key_init(10);
	seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_binaryzation[0], MT9V03X_W, MT9V03X_H);
	system_delay_ms(1000);
	
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
		key_scanner();
		Display_Show();
            // �ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
		if (mt9v03x_finish_flag){
			//image_value = GetOSTU(image_binaryzation);
			Image_Binaryzation(image_value);
			Image_Erosion(image_binaryzation);
			Sweep_Line(image_binaryzation);
			FineMidLine_Weight();
			Draw_Lines();
			//wireless_uart_send_buffer(temp_data, 120);
			//seekfree_assistant_camera_send();
			ips200_show_gray_image(0, 0, image_binaryzation[0], MT9V03X_W, MT9V03X_H, MT9V03X_W, MT9V03X_H, 0);
			mt9v03x_finish_flag = 0;
			
		}

		//ips200_show_int(0, 250, pid_output, 4);
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


