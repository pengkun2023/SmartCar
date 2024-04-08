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

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������


// *************************** ����Ӳ������˵�� ***************************
// ʹ����ɿƼ� CMSIS-DAP | ARM ��������������
//      ֱ�ӽ���������ȷ�����ں��İ�ĵ������ؽӿڼ���
// 
// ���� ����Wifi SPI ģ��
//      ģ��ܽ�            ��Ƭ���ܽ�
//      RST                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_RST_PIN �궨��
//      INT                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_INT_PIN �궨��
//      CS                  �鿴 zf_device_wifi_spi.h �� WIFI_SPI_CS_PIN �궨��
//      MISO                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MISO_PIN �궨��
//      SCK                 �鿴 zf_device_wifi_spi.h �� WIFI_SPI_SCK_PIN �궨��
//      MOSI                �鿴 zf_device_wifi_spi.h �� WIFI_SPI_MOSI_PIN �궨��
//      5V                  5V ��Դ
//      GND                 ��Դ��


// *************************** ����ʹ�ò���˵�� ***************************
// 1.����Ӳ������˵�����Ӻ�ģ�飬ʹ�õ�Դ����(����������ᵼ��ģ���ѹ����)
//
// 2.�鿴���������ӵ�wifi����¼wifi���ƣ����룬IP��ַ
//
// 3.���·��Ĵ����������޸ĺ궨�壬WIFI_SSID_TESTΪwifi���ƣ�WIFI_PASSWORD_TESTΪwifi����
//
// 4.��zf_device_wifi_spi.h���޸�WIFI_SPI_TARGET_IP�궨�壬����Ϊ����wifi��IP��ַ
//
// 5.�������̵���Ƭ���У��򿪴������֣����������Ĵ���
//
// 6.����ɿƼ���������������ѡ��ͼ���书��
//
// 7.ѡ�����磬����ΪTCP Server��������ַ��ѡ��WIFI����Ȼ��������


// *************************** ���̲���˵�� ***************************
// 1.�����̻�ͨ�� Debug �������������Ϣ ����ؽӺõ��Դ����Ա��ȡ������Ϣ
// 
// 2.���Ӻ�ģ��ͺ��İ�󣨾���ʹ��������������Ա��⹩�粻������⣩ ��¼������ ���¸�λ�����ʼ����
// 
// 3.���ģ��δ��������ʼ�� ��ͨ�� DEBUG �������δ�ܳɹ���ʼ����ԭ�� ������᳢�����³�ʼ�� һ����������Ի�ɹ�
// 
// 4.���һֱ�� Debug ����������� ����Ҫ��鱨������ ���鿴���ļ��·��ĳ��������б�����Ų�
// 
// 5.����Ĭ�ϲ����� WIFI_SPI_AUTO_CONNECT �궨�� ͨ�� main �����еĽӿڽ����������� �����Ҫ�̶����н������� ���Կ����ú궨��
// 
// 6.��ģ���ʼ����ɺ��ͨ�� DEBUG ���������ǰģ�����Ҫ��Ϣ���̼��汾��IP��Ϣ��MAC��Ϣ��PORT��Ϣ
// 
// 7.�������� TCP Client ���� ģ��ᱻ����Ϊ TCP Client ��Ҫ���ӵ��������ڵ� TCP Server ���ܽ���ͨ��
//   Ŀ�����ӵ� TCP Server �� IP ��˿�Ĭ��ʹ�� zf_device_wifi_spi.h �� WIFI_SPI_TARGET_IP �� WIFI_SPI_TARGET_PORT ����
//   ʵ�ʲ�����Ҫ�����ֳ� TCP Server ��ʵ�� IP ��ַ��˿�����
// 
// 8.�������豸�������ӵ� TCP Server ���������ʹ�����������λ������ TCP Server ģʽ Ȼ�󱾻����ӵ����Ե� IP ��˿ڣ�
//   �����̻�ɼ������ͼ�񲢷��͵����������λ��
// 
// 9.Ĭ����������������ʾ����ͷ��ͼ��֡�ʿ��Դﵽ50֡�������������Ƚϸ������總���н϶��WIFI�ȵ㣬���ܻᵼ����ʾ֡�ʽϵ�
//   
// 
// �������������˵�����ز��� ����ձ��ļ����·� ���̳�������˵�� �����Ų�


// **************************** �������� ****************************

//0���������߽���Ϣ  
//1����������������Ϣ��������Ϣֻ�����������꣬����������ͼ��߶ȵõ�����ζ��ÿ���߽���һ����ֻ����һ����
//2����������������Ϣ���߽���Ϣֻ�����������꣬����������ͼ���ȵõ�����ζ��ÿ���߽���һ����ֻ����һ���㣬һ����˵������������ʹ������
//3����������������Ϣ���߽���Ϣ���к��������꣬��ζ�������ָ��ÿ����ĺ������꣬���ߵ�����Ҳ���Դ��ڻ���С��ͼ��ĸ߶ȣ�ͨ����˵������������ͼ��ĸ߶ȣ�һ���������㷨���ҳ���������
//4��û��ͼ����Ϣ������������������Ϣ��������Ϣֻ�����������꣬����������ͼ��߶ȵõ�����ζ��ÿ���߽���һ����ֻ����һ���㣬�����ķ�ʽ���Լ���Ľ��ʹ����������
#define INCLUDE_BOUNDARY_TYPE   0


#define WIFI_SSID_TEST          "abc"
#define WIFI_PASSWORD_TEST      "01010101"  // �����Ҫ���ӵ�WIFI û����������Ҫ�� "12345678" �滻Ϊ NULL




// �߽�ĵ�����Զ����ͼ��߶ȣ����ڱ����������
#define BOUNDARY_NUM            (MT9V03X_H * 3 / 2)

// ֻ��X�߽�
uint8 xy_x1_boundary[BOUNDARY_NUM], xy_x2_boundary[BOUNDARY_NUM], xy_x3_boundary[BOUNDARY_NUM];

// ֻ��Y�߽�
uint8 xy_y1_boundary[BOUNDARY_NUM], xy_y2_boundary[BOUNDARY_NUM], xy_y3_boundary[BOUNDARY_NUM];

// X Y�߽綼�ǵ���ָ����
uint8 x1_boundary[MT9V03X_H], x2_boundary[MT9V03X_H], x3_boundary[MT9V03X_H];
uint8 y1_boundary[MT9V03X_W], y2_boundary[MT9V03X_W], y3_boundary[MT9V03X_W];

// ͼ�񱸷����飬�ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
uint8 image_copy[MT9V03X_H][MT9V03X_W];
uint8 image_binaryzation[MT9V03X_H][MT9V03X_W];
void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W]);
void Image_Binaryzation(uint8 value);
void Image_Erosion(uint8 image[MT9V03X_H][MT9V03X_W]);
int main(void)
{
#if(1 == INCLUDE_BOUNDARY_TYPE || 2 == INCLUDE_BOUNDARY_TYPE || 4 == INCLUDE_BOUNDARY_TYPE)
    int32 i = 0;
#elif(3 == INCLUDE_BOUNDARY_TYPE)
    int32 j = 0;
#endif
    
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��

    system_delay_ms(300);
    
    while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
    {
		printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // ��ʼ��ʧ�� �ȴ� 100ms
    }
    
    printf("\r\n module version:%s", wifi_spi_version);      					// ģ��̼��汾
    printf("\r\n module mac    :%s", wifi_spi_mac_addr);     					// ģ�� MAC ��Ϣ
    printf("\r\n module ip     :%s", wifi_spi_ip_addr_port); 					// ģ�� IP ��ַ

    // zf_device_wifi_spi.h �ļ��ڵĺ궨����Ը���ģ������(����) WIFI ֮���Ƿ��Զ����� TCP ������������ UDP ����
    if(1 != WIFI_SPI_AUTO_CONNECT)                                              // ���û�п����Զ����� ����Ҫ�ֶ�����Ŀ�� IP
    {
        while(wifi_spi_socket_connect(                                          // ��ָ��Ŀ�� IP �Ķ˿ڽ��� TCP ����
            "TCP",                                                              // ָ��ʹ��TCP��ʽͨѶ
            WIFI_SPI_TARGET_IP,                                                 // ָ��Զ�˵�IP��ַ����д��λ����IP��ַ
            WIFI_SPI_TARGET_PORT,                                               // ָ��Զ�˵Ķ˿ںţ���д��λ���Ķ˿ںţ�ͨ����λ��Ĭ����8080
            WIFI_SPI_LOCAL_PORT))                                               // ָ�������Ķ˿ں�
        {
            // ���һֱ����ʧ�� ����һ���ǲ���û�н�Ӳ����λ
            printf("\r\n Connect TCP Servers error, try again.");
            system_delay_ms(100);                                               // ��������ʧ�� �ȴ� 100ms
        }
    }
    
    // �Ƽ��ȳ�ʼ������ͷ�����ʼ���������
    mt9v03x_init();
    Image_Copy(image_binaryzation);

    
    // ʹ�ø��� WIFI SPIģ��ʱ�޷�ʹ�ò�����Ļ����Ϊ�����й��ã�������ѡ��ʹ�����紮����Ļ
    // ʹ�ø��� WIFI SPIģ��ʱ�޷�ʹ�ò�����Ļ����Ϊ�����й��ã�������ѡ��ʹ�����紮����Ļ
    // ʹ�ø��� WIFI SPIģ��ʱ�޷�ʹ�ò�����Ļ����Ϊ�����й��ã�������ѡ��ʹ�����紮����Ļ
    //ips200_init(IPS200_TYPE_SPI);
    

    
    // ������ֳ�ʼ�� ���ݴ���ʹ�ø���WIFI SPI
    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIFI_SPI);
    
    // ���Ҫ����ͼ����Ϣ������ص���seekfree_assistant_camera_information_config�������б�Ҫ�Ĳ�������
    // �����Ҫ���ͱ����������seekfree_assistant_camera_boundary_config�������ñ��ߵ���Ϣ
    
#if(0 == INCLUDE_BOUNDARY_TYPE)
    // ���������ͼ����Ϣ(������ԭʼͼ����Ϣ)
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_binaryzation[0], MT9V03X_W, MT9V03X_H);
    
    
#elif(1 == INCLUDE_BOUNDARY_TYPE)
    // ���������ͼ����Ϣ(���Ұ��������߽���Ϣ���߽���Ϣֻ���к������꣬����������ͼ��߶ȵõ�����ζ��ÿ���߽���һ����ֻ����һ����)
    // �Ա߽�����д������
    for(i = 0; i < MT9V03X_H; i++)
    {
        x1_boundary[i] = 70 - (70 - 20) * i / MT9V03X_H;
        x2_boundary[i] = MT9V03X_W / 2;
        x3_boundary[i] = 118 + (168 - 118) * i / MT9V03X_H;
    }
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL ,NULL);
    
    
#elif(2 == INCLUDE_BOUNDARY_TYPE)
    // ���������ͼ����Ϣ(���Ұ��������߽���Ϣ���߽���Ϣֻ�����������꣬����������ͼ���ȵõ�����ζ��ÿ���߽���һ����ֻ����һ����)
    // ͨ��������������ʹ������
    // �Ա߽�����д������
    for(i = 0; i < MT9V03X_W; i++)
    {
        y1_boundary[i] = i * MT9V03X_H / MT9V03X_W;
        y2_boundary[i] = MT9V03X_H / 2;
        y3_boundary[i] = (MT9V03X_W - i) * MT9V03X_H / MT9V03X_W;
    }
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(Y_BOUNDARY, MT9V03X_W, NULL, NULL ,NULL, y1_boundary, y2_boundary, y3_boundary);
    
    
#elif(3 == INCLUDE_BOUNDARY_TYPE)
    // ���������ͼ����Ϣ(���Ұ��������߽���Ϣ���߽���Ϣ���к���������)
    // �����ķ�ʽ����ʵ�ֶ����л���ı߽���ʾ
    j = 0;
    for(i = MT9V03X_H - 1; i >= MT9V03X_H / 2; i--)
    {
        // ֱ�߲���
        xy_x1_boundary[j] = 34;
        xy_y1_boundary[j] = i;
        
        xy_x2_boundary[j] = 47;
        xy_y2_boundary[j] = i;
        
        xy_x3_boundary[j] = 60;
        xy_y3_boundary[j] = i;
        j++;
    }
    
    for(i = MT9V03X_H / 2 - 1; i >= 0; i--)
    {
        // ֱ�������������
        xy_x1_boundary[j] = 34 + (MT9V03X_H / 2 - i) * (MT9V03X_W / 2 - 34) / (MT9V03X_H / 2);
        xy_y1_boundary[j] = i;
        
        xy_x2_boundary[j] = 47 + (MT9V03X_H / 2 - i) * (MT9V03X_W / 2 - 47) / (MT9V03X_H / 2);
        xy_y2_boundary[j] = 15 + i * 3 / 4;
        
        xy_x3_boundary[j] = 60 + (MT9V03X_H / 2 - i) * (MT9V03X_W / 2 - 60) / (MT9V03X_H / 2);
        xy_y3_boundary[j] = 30 + i / 2;
        j++;
    }
    
    for(i = 0; i < MT9V03X_H / 2; i++)
    {
        // ���䲿��
        xy_x1_boundary[j] = MT9V03X_W / 2 + i * (138 - MT9V03X_W / 2) / (MT9V03X_H / 2);
        xy_y1_boundary[j] = i;
        
        xy_x2_boundary[j] = MT9V03X_W / 2 + i * (133 - MT9V03X_W / 2) / (MT9V03X_H / 2);
        xy_y2_boundary[j] = 15 + i * 3 / 4;
        
        xy_x3_boundary[j] = MT9V03X_W / 2 + i * (128 - MT9V03X_W / 2) / (MT9V03X_H / 2);
        xy_y3_boundary[j] = 30 + i / 2;
        j++;
    }
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(XY_BOUNDARY, BOUNDARY_NUM, xy_x1_boundary, xy_x2_boundary, xy_x3_boundary, xy_y1_boundary, xy_y2_boundary, xy_y3_boundary);
    
    
#elif(4 == INCLUDE_BOUNDARY_TYPE)
    // ���������ͼ����Ϣ(���Ұ��������߽���Ϣ���߽���Ϣֻ���к������꣬����������ͼ��߶ȵõ�����ζ��ÿ���߽���һ����ֻ����һ����)
    // �Ա߽�����д������
    for(i = 0; i < MT9V03X_H; i++)
    {
        x1_boundary[i] = 70 - (70 - 20) * i / MT9V03X_H;
        x2_boundary[i] = MT9V03X_W / 2;
        x3_boundary[i] = 118 + (168 - 118) * i / MT9V03X_H;
    }
    seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, NULL, MT9V03X_W, MT9V03X_H);
    seekfree_assistant_camera_boundary_config(X_BOUNDARY, MT9V03X_H, x1_boundary, x2_boundary, x3_boundary, NULL, NULL ,NULL);
    
    
#endif
    
    

    // �˴���д�û����� ���������ʼ�������
    while(1)
    {
        if(mt9v03x_finish_flag)
        {
            mt9v03x_finish_flag = 0;
            
            // �ڷ���ǰ��ͼ�񱸷��ٽ��з��ͣ��������Ա���ͼ�����˺�ѵ�����
            //memcpy(image_copy[0], mt9v03x_image[0], MT9V03X_IMAGE_SIZE);
            Image_Binaryzation(210);
			Image_Erosion(image_binaryzation);
            // ����ͼ��
            seekfree_assistant_camera_send();
            
            // ���ʹ��UDPЭ�鴫���������Ƽ�������ȫ�����͵�ģ��֮����������wifi_spi_udp_send_now()�������Ը�֪ģ���������յ������ݷ��͵�������
            // ���û������������ģ����ڳ���2����δ�յ����ݺ󣬽����ݷ��͵�������
            // ����wifi_spi_udp_send_now()ǰ�����ģ��������������鲻Ҫ����40960�ֽ�
            // wifi_spi_udp_send_now();
        }
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}
// **************************** �������� ****************************
void Image_Copy(uint8 image_copy[MT9V03X_H][MT9V03X_W])
{
	uint8 i, j;
	for (i = 0; i < MT9V03X_H; i++){
		for (j = 0; j < MT9V03X_W; j++)	image_copy[i][j] = mt9v03x_image[i][j]; 
	}
}
void Image_Binaryzation(uint8 value)
{
	uint8 temp_value;	
	for (uint8 i = 0; i < MT9V03X_H; i ++){
		for (uint8 j = 0; j < MT9V03X_W; j ++){
			temp_value = mt9v03x_image[i][j];
			if (temp_value < value)		image_binaryzation[i][j] = 0;			//Black
			else 						image_binaryzation[i][j] = 255;			//White
		}
	}
}
void Image_Erosion(uint8 image[MT9V03X_H][MT9V03X_W])
{
	for (uint8 i = 1; i < MT9V03X_H - 1; i ++){
		for (uint8 j = 1; j < MT9V03X_W; j ++){
			if ((image[i][j] == 0)
				&& (image[i + 1][j] + image[i][j + 1] + image[i - 1][j] + image[i][j - 1]) > (255 * 2)) 	image[i][j] = 255;			
			else if ((image[i][j] == 255)
					&& (image[i + 1][j] + image[i - 1][j] + image[i][j + 1] + image[i][j - 1]) < (255 * 2))	image[i][j] = 0;
		}
	}
}
// *************************** ���̳�������˵�� ***************************
// ����1������û������
//      �鿴�������ִ򿪵��Ƿ�����ȷ�Ĵ��� ���򿪵� COM ���Ƿ��Ӧ���� Debug UART(USB ת TTL ���� ����������) �� COM ��
// 
// ����2��������������
//      �鿴��������ʹ�õĲ������Ƿ��� zf_common_debug.h �� DEBUG_UART_BAUDRATE �궨���һ�� Ĭ���� 115200
// 
// ����3����λ���ղ������ݻ���һֱ��ʾConnect TCP Servers error, try again.
//      ���Ĭ��ʹ�õ�IP ��ַ��zf_device_wifi_spi.h �� WIFI_SPI_TARGET_IP���Ƿ�����λ���ı�����ַһ��
//      ���Ĭ��ʹ�õ�ͨ�Ŷ˿ڣ�zf_device_wifi_spi.h �� WIFI_SPI_TARGET_PORT���Ƿ�����λ���Ķ˿ں�һ��
// 
// ����4��һֱ��ʾ connect wifi failed
//      �� WIFI_SSID_TEST �궨���޸�Ϊ�����ʹ�õ� Wi-Fi ���� 
//      �� WIFI_PASSWORD_TEST �궨���޸�Ϊ�����ʹ�õ� Wi-Fi ���� 



