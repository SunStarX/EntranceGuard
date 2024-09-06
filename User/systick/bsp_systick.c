#include "bsp_systick.h"

void SysTick_Delay_us(uint32_t us)             //SysTIck微秒延时
{
		uint32_t i;
		SysTick_Config(72);                        //初始化并启动SysTick计数器及其中断
	                                             //72*（1/72M）=1us
		for(i=0;i<us;i++)                          //每个循环为1us
		{
				while(!((SysTick->CTRL)&(1<<16)));     //判断COUNTFALAG位是否置1
		}
		SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;  //关闭使能
}


void SysTick_Delay_ms(uint32_t ms)       			 //SysTIck毫秒延时
{
		uint32_t i;
		SysTick_Config(72000);                     //初始化并启动SysTick计数器及其中断
	                                             //72000*（1/72M）=1ms
		for(i=0;i<ms;i++)
		{
				while(!((SysTick->CTRL)&(1<<16)));     //判断COUNTFALAG位是否置1
		}
		SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;  //关闭使能
}

