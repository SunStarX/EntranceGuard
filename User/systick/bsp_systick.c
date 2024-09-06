#include "bsp_systick.h"

void SysTick_Delay_us(uint32_t us)             //SysTIck΢����ʱ
{
		uint32_t i;
		SysTick_Config(72);                        //��ʼ��������SysTick�����������ж�
	                                             //72*��1/72M��=1us
		for(i=0;i<us;i++)                          //ÿ��ѭ��Ϊ1us
		{
				while(!((SysTick->CTRL)&(1<<16)));     //�ж�COUNTFALAGλ�Ƿ���1
		}
		SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;  //�ر�ʹ��
}


void SysTick_Delay_ms(uint32_t ms)       			 //SysTIck������ʱ
{
		uint32_t i;
		SysTick_Config(72000);                     //��ʼ��������SysTick�����������ж�
	                                             //72000*��1/72M��=1ms
		for(i=0;i<ms;i++)
		{
				while(!((SysTick->CTRL)&(1<<16)));     //�ж�COUNTFALAGλ�Ƿ���1
		}
		SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;  //�ر�ʹ��
}

