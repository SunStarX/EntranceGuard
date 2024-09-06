#ifndef   _BSP_EXTI_H_
#define   _BSP_EXTI_H_
 

#include "stm32f10x.h"


#define EXTI_KEY1_PIN           GPIO_Pin_0                           //引脚为0
#define EXTI_KEY1_PORT          GPIOA																 //端口A
#define EXTI_KEY1_CLK           RCC_APB2Periph_GPIOA                 //端口A时钟使能配置

static void  EXTI_NVIC_Config(void);                                     //初始化NVIC
void  EXTI_Key_Config(void);                                             //初始化GPIO

#endif
