#ifndef _BSP_SYSTICK_H_
#define _BSP_SYSTICK_H_

#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_us(uint32_t us);  //SysTIck΢����ʱ
void SysTick_Delay_ms(uint32_t ms);  //SysTIck������ʱ

#endif 


