/******************************************/
//	Created by PengKun on 2024/3/31
/******************************************/

#include "gyroscope.h"




/*******************��������Ʈ��ȡ*******************/
//void GyroOffset_Get(void)
//
/***************************************************/
void GyroOffset_Get(IMU_OFFSET_S * GyroOffset)
{
	GyroOffset->Xdata = 0;
	GyroOffset->Ydata = 0;
	GyroOffset->Zdata = 0;
	for (uint8 i = 0; i < 100; i ++){
		imu963ra_get_acc();		
		imu963ra_get_gyro();
		GyroOffset->Xdata += imu963ra_gyro_x;
		GyroOffset->Ydata += imu963ra_gyro_y;
		GyroOffset->Zdata += imu963ra_gyro_z;
		system_delay_ms(10);
	}
	GyroOffset->Xdata /= 100;
	GyroOffset->Ydata /= 100;
	GyroOffset->Zdata /= 100;
}


/*********************����������ת��***********************/
//void IMU_DataTransition(IMU_Transition_Data *AccData, IMU_Transition_Data *GyroData)
//�������ǲɼ�������ת��Ϊ������
/*********************************************************/
void IMU_DataTransition(IMU_Transition_Data *AccData, IMU_Transition_Data *GyroData, IMU_OFFSET_S * GyroOffset)
{
	AccData->x = imu963ra_acc_transition(imu963ra_acc_x);
	AccData->y = imu963ra_acc_transition(imu963ra_acc_y);
	AccData->z = imu963ra_acc_transition(imu963ra_acc_z);
	
	GyroData->x = imu963ra_gyro_transition(imu963ra_gyro_x - GyroOffset->Xdata);
	GyroData->y = imu963ra_gyro_transition(imu963ra_gyro_y - GyroOffset->Ydata);
	GyroData->z = imu963ra_gyro_transition(imu963ra_gyro_z - GyroOffset->Zdata);
}

/*********************�����Ǵ���***********************/
//void Imu_Deal(void)
//�������ǲɼ�������ת��Ϊ������
/******************************************************/
void Imu_Deal(void)
{
	GyroOffset_Get(&GyroOffset);
	IMU_DataTransition(&AccData, &GyroData, &GyroOffset);
}
