#include "rccclkconfig.h"

//用HSE配置系统时钟
void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEStatus;
	RCC_DeInit();                                             //把RCC复位成复位值
	RCC_HSEConfig(RCC_HSE_ON);                                //使能HSE
	HSEStatus=RCC_WaitForHSEStartUp();                        

	if(HSEStatus==SUCCESS)                                    //等待HSE启动 
	{
			//使能预取指
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //预取指
			FLASH_SetLatency(FLASH_Latency_2);                    //设置FLASH延迟时间
		
		  //设置三大总线的分频因子
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                      //设置AHB时钟分频因子
			RCC_PCLK1Config(RCC_HCLK_Div2);                       //设置APB1时钟分频因子
			RCC_PCLK2Config(RCC_HCLK_Div1);                       //设置APB2时钟分频因子
		
			//配置PLLCLK = HSE * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);  //配置锁相环（时钟来源，设置倍频因子）
			RCC_PLLCmd(ENABLE);                                   //使能PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);			//等待PLL稳定
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //选择系统时钟
			while(RCC_GetSYSCLKSource()!=0x08);                   //等待切换完成
	}
	else
	{
	/************如果启动失败，用户可以在这里填写相应的代码**********/
	}
	
}


//用HSI配置系统时钟
void HSI_SetSysClk(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HSIStatus=0;
	RCC_DeInit();                                             //把RCC复位成复位值
	RCC_HSICmd(ENABLE);                                //使能HSE
	HSIStatus=RCC->CR & RCC_CR_HSIRDY;                        

	if(HSIStatus==RCC_CR_HSIRDY)                                    //等待HSE启动 
	{
			//使能预取指 
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable); //预取指
			FLASH_SetLatency(FLASH_Latency_2);                    //设置FLASH延迟时间
		
		  //设置三大总线的分频因子
			RCC_HCLKConfig(RCC_SYSCLK_Div1);                      //设置AHB时钟分频因子
			RCC_PCLK1Config(RCC_HCLK_Div2);                       //设置APB1时钟分频因子
			RCC_PCLK2Config(RCC_HCLK_Div1);                       //设置APB2时钟分频因子
		
			//配置PLLCLK = HSI * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);  //配置锁相环（时钟来源，设置倍频因子）
			RCC_PLLCmd(ENABLE);                                   //使能PLL
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET);			//等待PLL稳定
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);            //选择系统时钟
			while(RCC_GetSYSCLKSource()!=0x08);                   //等待切换完成
	}
	else
	{
	/************如果启动失败，用户可以在这里填写相应的代码**********/
	}
	
}


void MOC_GOIO_Config()
{
		GPIO_InitTypeDef GPIO_InitStruct;
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//时钟配置使能
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8;					//选择引脚
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;				//复用推挽输出
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;				//速率为50MHZ
		GPIO_Init(GPIOA, & GPIO_InitStruct);				//初始化GPIO引脚
}
