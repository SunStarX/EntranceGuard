
#include "stm32f10x.h"
#include "bsp_Beep.h"


void Beep_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(Beep_RCC, ENABLE);
	GPIO_InitStruct.GPIO_Pin = Beep_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(Beep_GPIO, &GPIO_InitStruct);

}


//void Beep_Init(void)
//{
//	GPIO_Config();
//}
