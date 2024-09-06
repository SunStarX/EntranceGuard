#include "bsp.key.h"



void Matrix_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
/**********************���ð���1���Ų���*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY1_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //ͨ���������
    GPIO_Init(KEY1_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
/**********************���ð���2���Ų���*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY2_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //ͨ���������
	GPIO_Init(KEY2_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO

/**********************���ð���3���Ų���*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY3_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //ͨ���������
    GPIO_Init(KEY3_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
/**********************���ð���4���Ų���*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY4_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //ͨ���������
	GPIO_Init(KEY4_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
	
	/**********************���ð���5���Ų���*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY5_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //ͨ���������
    GPIO_Init(KEY5_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
/**********************���ð���6���Ų���*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY6_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //ͨ���������
	GPIO_Init(KEY6_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
	
	/**********************���ð���7���Ų���*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY7_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //ͨ���������
    GPIO_Init(KEY7_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	
/**********************���ð���8���Ų���*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY8_GPIO_PIN;           //ѡ������
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //ͨ���������
	GPIO_Init(KEY8_GPIO_PORT, & GPIO_InitStruct);         //��ʼ��GPIO
	

	
}


/**********************����ɨ���⺯��**********************/
/****�������������������£�����KEY_ON,������δ���£�����KEY_OFF****/
uint8_t KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	
		 if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
			 {
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
					return KEY_ON;
			 }
			else return KEY_OFF;
}



/**********************������̼��**************************/
uint16_t Matrix_Scan(GPIO_TypeDef* GPIOx)
{
	uint16_t Matrix_Value;
	Matrix_Value = GPIO_ReadInputData(GPIOx);
	return Matrix_Value;
}


/*******************��GPIOд��ֵ***************************/
void Write_Date(GPIO_TypeDef* GPIOx,uint16_t PortVal)
{
		GPIO_Write(GPIOx, PortVal);
}