#include "rccclkconfig.h"

//��HSE����ϵͳʱ��
void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	RCC_DeInit();                                             //��RCC��λ�ɸ�λֵ
	RCC_HSEConfig(RCC_HSE_ON);                                //ʹ��HSE
	HSEStatus=RCC_WaitForHSEStartUp();                        

	if(HSEStatus==SUCCESS)                                    //�ȴ�HSE���� 
	{
			//ʹ��Ԥȡָ
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Ԥȡָ
			FLASH_SetLatency(FLASH_Latency_2);                    //����FLASH�ӳ�ʱ��
		
		  //�����������ߵķ�Ƶ����
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                      //����AHBʱ�ӷ�Ƶ����
			RCC_PCLK1Config(RCC_HCLK_Div2);                       //����APB1ʱ�ӷ�Ƶ����
			RCC_PCLK2Config(RCC_HCLK_Div1);                       //����APB2ʱ�ӷ�Ƶ����
		
			//����PLLCLK = HSE * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);  //�������໷��ʱ����Դ�����ñ�Ƶ���ӣ�
			RCC_PLLCmd(ENABLE);                                   //ʹ��PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);			//�ȴ�PLL�ȶ�
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //ѡ��ϵͳʱ��
			while(RCC_GetSYSCLKSource()!=0x08);                   //�ȴ��л����
	}
	else
	{
	/************�������ʧ�ܣ��û�������������д��Ӧ�Ĵ���**********/
	}
	
}


//��HSI����ϵͳʱ��
void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus=0;
	RCC_DeInit();                                             //��RCC��λ�ɸ�λֵ
	RCC_HSICmd(ENABLE);                                //ʹ��HSE
	HSIStatus=RCC->CR & RCC_CR_HSIRDY;                        

	if(HSIStatus==RCC_CR_HSIRDY)                                    //�ȴ�HSE���� 
	{
			//ʹ��Ԥȡָ 
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //Ԥȡָ
			FLASH_SetLatency(FLASH_Latency_2);                    //����FLASH�ӳ�ʱ��
		
		  //�����������ߵķ�Ƶ����
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                      //����AHBʱ�ӷ�Ƶ����
			RCC_PCLK1Config(RCC_HCLK_Div2);                       //����APB1ʱ�ӷ�Ƶ����
			RCC_PCLK2Config(RCC_HCLK_Div1);                       //����APB2ʱ�ӷ�Ƶ����
		
			//����PLLCLK = HSI * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);  //�������໷��ʱ����Դ�����ñ�Ƶ���ӣ�
			RCC_PLLCmd(ENABLE);                                   //ʹ��PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);			//�ȴ�PLL�ȶ�
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //ѡ��ϵͳʱ��
			while(RCC_GetSYSCLKSource()!=0x08);                   //�ȴ��л����
	}
	else
	{
	/************�������ʧ�ܣ��û�������������д��Ӧ�Ĵ���**********/
	}
	
}


void MOC_GOIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʱ������ʹ��
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8;					//ѡ������
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;				//�����������
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;				//����Ϊ50MHZ
		GPIO_Init(GPIOA, & GPIO_InitStruct);				//��ʼ��GPIO����
}
