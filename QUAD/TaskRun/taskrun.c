#include "taskrun.h"
#include "stm32f10x.h"
#include "ANO_DT.h"
#include "mpu6050.h"
#include "ahrs.h"
#include <stdio.h>
#include <math.h>
/**
  ******************************************************************************
  * @fuction    
  * @author  �ԼӺ�
  * @date     16-02-2017
  * @param   
  * @retval   
  * @brief  1000HZ������,��Systick����
  * @CopyRight Sunic-Ocean
  ******************************************************************************
**/
extern uint8_t SYS_INIT_OK;
uint8_t send_anodt=0;		//���͵�������λ��
uint8_t log_attitude=0;		//ͨ�����ڼ�¼��̬��Ϣ
void TaskRun(void)
{
	static uint32_t i=0;
	static u16 ms1 = 0,ms2 = 0,ms5 = 0,ms10 = 0,ms100 = 0,ms1000 = 0;	//�жϴ���������
	if(!SYS_INIT_OK)				//δ��ʼ��		
		return;
	//ÿ���ж϶�ִ��,0.5ms
	ms1++;
	ms2++;
	ms5++;
	ms10++;
	ms100++;
	ms1000++;
	//@HackOS: 1000HZ
	if(ms1==1)				//ÿ�����ж�ִ��һ��,1ms
	{
		ms1=0;
		Prepare_Data();				//��ȡ���ݲ��˲�
		IMU_Update();				//��̬����
		if(send_anodt)
			ANO_DT_Data_Exchange();		//�ϴ�����λ��
	}
	//@HackOS: 500HZ
	if(ms2==2)				//ÿ�Ĵ��ж�ִ��һ��,2ms
	{
		ms2=0;
	}
	//@HackOS: 200HZ
	if(ms5==5)
	{
		ms5=0;					//ÿʮ���ж�ִ��һ��,5ms
	}
	//@HackOS: 100HZ
	if(ms10==10)
	{
		ms10=0;					//ÿ��ʮ���ж�ִ��һ��,10ms
		if(log_attitude)
		{
			i++;
			printf("%5d,%-5.2f,%-5.2f,%-5.2f\r\n",i,Angle.x,Angle.y,Angle.z);
		}
	}
	if(ms100==10)
	{
		ms100=0;
	}
	if(ms1000==1000)
	{
		ms1000=0;
	}
		
}
