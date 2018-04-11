#include "moto.h"
#include "stm32f10x.h"
#include <stdio.h>
int16_t MOTO1_PWM = 0;
int16_t MOTO2_PWM = 0;
int16_t MOTO3_PWM = 0;
int16_t MOTO4_PWM = 0;

/***********************************************
��������MotorInit(void)
���ܣ����PWM�Ķ�ʱ��2��ʼ��
�����������
���:��
���������øú���������ʼ����ʱ��2ΪPWM���ģʽ,Ƶ��:24KHZ,���ֵ999
��ע��
***********************************************/
void MotorInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;    //���Ƶ��PWMƵ��


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //������A��ʱ�Ӻ͸���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);  //�򿪶�ʱ��2ʱ��


	// ����GPIO���ܡ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);


	// ��λ��ʱ����
	TIM_DeInit(TIM2);

	// ���ü�ʱ����
	PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;

	TIM_TimeBaseStructure.TIM_Period = 999;						//��������
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;		//pwmʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


	// ����TIM2ΪPWM���ģʽ
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;    //0
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);

	// ������ʱ����
	TIM_Cmd(TIM2, ENABLE);
	printf("Motor init success...\r\n");
}

/***********************************************
��������MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM)
���ܣ�������·PWMֵ
���������MOTO1_PWM,MOTO2_PWM,MOTO3_PWM,MOTO4_PWM
���:��
��������·PWM�ɶ�ʱ��2��������뷶Χ0-999
��ע��
***********************************************/
void MotorPwmFlash(int16_t MOTO1_PWM, int16_t MOTO2_PWM, int16_t MOTO3_PWM, int16_t MOTO4_PWM)
{
	if(MOTO1_PWM >= Moto_PwmMax)	{ MOTO1_PWM = Moto_PwmMax; }
	if(MOTO2_PWM >= Moto_PwmMax)	{ MOTO2_PWM = Moto_PwmMax; }
	if(MOTO3_PWM >= Moto_PwmMax)	{ MOTO3_PWM = Moto_PwmMax; }
	if(MOTO4_PWM >= Moto_PwmMax)	{ MOTO4_PWM = Moto_PwmMax; }
	if(MOTO1_PWM <= 0)	{ MOTO1_PWM = 0; }
	if(MOTO2_PWM <= 0)	{ MOTO2_PWM = 0; }
	if(MOTO3_PWM <= 0)	{ MOTO3_PWM = 0; }
	if(MOTO4_PWM <= 0)	{ MOTO4_PWM = 0; } //�޶����벻��С��0������999

	TIM2->CCR1 = MOTO1_PWM;
	TIM2->CCR2 = MOTO2_PWM;
	TIM2->CCR3 = MOTO3_PWM;
	TIM2->CCR4 = MOTO4_PWM;        //�Զ�ʱ���Ĵ�����ֵ
}
