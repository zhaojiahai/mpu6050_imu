#ifndef __AHRS_H_
#define __AHRS_H_
#include "config.h"
#define SAMPLE_HALF_T 0.0005f	//�������ڵ�һ�룬��λ��s
#define FILTER_LENGTH 20		//�����˲����ڳ���

#define GYRO_G 	0.0610351f		//���ٶȱ�ɶ�/S   �˲�����Ӧ����2000��ÿ��  Gyro_G=1/16.375=0.0610687
#define GYRO_GR	0.0010652f		//���ٶȱ�ɻ���/S	�˲�����Ӧ����2000��ÿ��

#define IMU_KP 2.0f     		//����
#define IMU_KI 0.005f 			//����

extern xyz_s16_t Acc_Avg;		//�����˲�����ٶȼ�ֵ
extern xyz_f_t Angle;			//�����ںϼ�����ĽǶ�
extern xyz_s16_t Acc_Buf[FILTER_LENGTH];	//�����˲�����

extern void ACC_Flitter(void);
extern void AHRS_Data_Init(void);
extern void IMU_Update(void);
extern void Prepare_Data(void);

#endif
