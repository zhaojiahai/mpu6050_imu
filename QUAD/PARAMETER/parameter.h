#ifndef __PARAMETER_H_
#define __PARAMETER_H_
#include "stm32f10x.h"
typedef struct
{
	float kp;
	float kd;
	float ki;
	float kdamp;

}pid_t;

typedef struct 
{
	float x;
	float y;
	float z;
}xyz_f_t;

typedef struct 
{
	s16 x;
	s16 y;
	s16 z;

}xyz_s16_t;

typedef struct 
{
	s32 x;
	s32 y;
	s32 z;

}xyz_s32_t;



typedef union
{
	uint8_t raw_data[64];
	struct
	{
		xyz_f_t Accel;
		xyz_f_t Gyro;
		xyz_f_t Mag;
		xyz_f_t vec_3d_cali;
		uint32_t mpu_flag;
		float Acc_Temperature;
		float Gyro_Temperature;
	}Offset;
}sensor_setup_t; //__attribute__((packed)) 

typedef  struct{
pid_t roll;
pid_t pitch;	
pid_t yaw;	
 }pid_group_t;

typedef union
{
 uint8_t raw_data[192];
 struct
 {
	 pid_group_t ctrl1;
	 pid_group_t ctrl2;
 /////////////////////
	 pid_t hc_sp;
	 pid_t hc_height;
	 pid_t ctrl3;
	 pid_t ctrl4;
 	  
 }groups;

}pid_setup_t;

#endif
