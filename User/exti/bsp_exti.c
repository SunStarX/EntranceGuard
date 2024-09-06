#include "bsp_exti.h"


//�����ж����ȼ�
static void  EXTI_NVIC_Config()                                     
{
		NVIC_InitTypeDef NVIC_InitStruct;                              //����NVIC��ʼ���ṹ�����
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                //�����ж����ȼ�����Ϊ��1�������ȼ�Ϊ0~1�������ȼ�Ϊ0~7��
		NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;    //ʹ��IRQͨ��
		NVIC_InitStruct.NVIC_IRQChannel                   = EXTI0_IRQn;//ѡ��IRQͨ��
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;         //������ռ���ȼ�Ϊ1
		NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;         //���������ȼ�Ϊ2
		NVIC_Init(&NVIC_InitStruct);                                   //��ʼ��NVIC
}

//��ʼ��GPIO
void  EXTI_Key_Config()
{
		//��ʼ��GPIO
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		
		EXTI_NVIC_Config();                                       //�����ж����ȼ�
	
	  RCC_APB2PeriphClockCmd(EXTI_KEY1_CLK,ENABLE);							//ʱ������ʹ��
		GPIO_InitStruct.GPIO_Pin   = EXTI_KEY1_PIN;					  		//ѡ������
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;				//��������
		GPIO_Init(EXTI_KEY1_PORT, & GPIO_InitStruct);				      //��ʼ��GPIO����
	
		//��ʼ��EXTI
		EXTI_InitStruct.EXTI_Line    = EXTI_Line0;                //ѡ��������ΪEXTI_Line0
		EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;       //ģʽΪ�ж�
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;       //������ʽΪ������
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;                    //ʹ��EXTI
		EXTI_Init(&EXTI_InitStruct);                              //��ʼ��EXTI
}
