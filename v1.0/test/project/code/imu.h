#ifndef _IMU_H_
#define _IMU_H_

#include "zf_device_imu963ra.h"
#include "motor.h"
#include "zf_driver_delay.h"


typedef struct IMU_OFFSET_S
{
	float Xdata, Ydata, Zdata;
}IMU_OFFSET_S;
 
typedef struct IMU_Transition_Data
{
	float x, y, z;
}IMU_Transition_Data;


extern IMU_OFFSET_S GyroOffset;
extern IMU_Transition_Data 	AccData, GyroData;
void GyroOffset_Get(IMU_OFFSET_S * GyroOffset);
void IMU_DataTransition(IMU_Transition_Data *AccData, IMU_Transition_Data *GyroData, IMU_OFFSET_S * GyroOffset);
void Imu_Deal(void);
#endif