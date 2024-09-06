#ifndef   _BSP_EXTI_H_
#define   _BSP_EXTI_H_
 

#include "stm32f10x.h"


#define EXTI_KEY1_PIN           GPIO_Pin_0                           //����Ϊ0
#define EXTI_KEY1_PORT          GPIOA																 //�˿�A
#define EXTI_KEY1_CLK           RCC_APB2Periph_GPIOA                 //�˿�Aʱ��ʹ������

static void  EXTI_NVIC_Config(void);                                     //��ʼ��NVIC
void  EXTI_Key_Config(void);                                             //��ʼ��GPIO

#endif
