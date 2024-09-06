#include "bsp_exti.h"


//配置中断优先级
static void  EXTI_NVIC_Config()                                     
{
		NVIC_InitTypeDef NVIC_InitStruct;                              //定义NVIC初始化结构体变量
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);                //配置中断优先级分组为组1（主优先级为0~1，子优先级为0~7）
		NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;    //使能IRQ通道
		NVIC_InitStruct.NVIC_IRQChannel                   = EXTI0_IRQn;//选择IRQ通道
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;         //配置抢占优先级为1
		NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 2;         //配置子优先级为2
		NVIC_Init(&NVIC_InitStruct);                                   //初始化NVIC
}

//初始化GPIO
void  EXTI_Key_Config()
{
		//初始化GPIO
		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		
		EXTI_NVIC_Config();                                       //配置中断优先级
	
	  RCC_APB2PeriphClockCmd(EXTI_KEY1_CLK,ENABLE);							//时钟配置使能
		GPIO_InitStruct.GPIO_Pin   = EXTI_KEY1_PIN;					  		//选择引脚
	  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;				//浮空输入
		GPIO_Init(EXTI_KEY1_PORT, & GPIO_InitStruct);				      //初始化GPIO引脚
	
		//初始化EXTI
		EXTI_InitStruct.EXTI_Line    = EXTI_Line0;                //选择输入线为EXTI_Line0
		EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;       //模式为中断
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;       //触发方式为上升沿
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;                    //使能EXTI
		EXTI_Init(&EXTI_InitStruct);                              //初始化EXTI
}
