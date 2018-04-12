#include "sys.h"
#include "uart4.h"
#include "mpu6050.h"
#include "moto.h"
#include <stdlib.h>
#include "ahrs.h"
#include "tim3.h"
#include "taskrun.h"
#include "delay.h"
#include "config.h"

uint8_t SYS_INIT_OK=0;

int main(void)
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	SYS_INIT_OK=0;									//��ʼ�����
	UART4_Init(500000);								//���ڳ�ʼ��Ϊ115200
	
	TIM3_Int_Init(1000-1,72-1);
	AHRS_Data_Init();								//��̬�������ݳ�ʼ��
	if(!MPU_Init())									//MPU6050��ʼ��
	{
		printf("\r\nMPU6050 init success...\r\n");
	}
	else
	{
		printf("\r\nMPU6050 init failed...\r\n");
	}
//	MotorInit();	//�����ʼ��
//	MotorPwmFlash(0,0,0,0);
	GetConfig();
	printf("config: \r\n");
	printf("gyro--->\tX: %d\tY: %d\tZ: %d\r\nAcc --->\tX: %d\tY: %d\tZ: %d\r\n",
		mpu6050.Gyro_Offset.x,mpu6050.Gyro_Offset.y,mpu6050.Gyro_Offset.z,
		mpu6050.Acc_Offset.x,mpu6050.Acc_Offset.y,mpu6050.Acc_Offset.z
	);
	SYS_INIT_OK=1;									//��ʼ�����
	
	
	
	while(1)
	{
		if(tim3_int)
		{
			tim3_int=0;
			TaskRun();
		}
	}
} 

