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
    system_delay_ms(3000);
	Motor_Init();
	
	//My_PWM_Init();
	
	pit_ms_init(PIT_CH0, 5);
	Encoder_Init();
	PID_Init();
	//uart_init(UART_1, 115200, UART1_TX_B12, UART1_RX_B13);
	wireless_uart_init();
	//wireless_uart_init();
    // �����������ʹ��DEBUG���ڽ����շ�
    //seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);
	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
    // ��ʼ���������ʾ�����Ľṹ��
	ips200_init(IPS200_TYPE_SPI);

	mt9v03x_init();

   
	

    
	system_delay_ms(1000);
	
    // �˴���д�û����� ���������ʼ�������

    while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
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

        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
