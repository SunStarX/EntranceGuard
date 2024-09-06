#ifndef _BEEP_H_
#define _BEEP_H_

#include "stm32f10x.h"



#define  Beep_Pin            GPIO_Pin_8
#define  Beep_GPIO	         GPIOA
#define  Beep_RCC            RCC_APB2Periph_GPIOA


#define Beep_ON   GPIO_SetBits(Beep_GPIO, Beep_Pin);
#define Beep_OFF  GPIO_ResetBits(Beep_GPIO, Beep_Pin);


#define  Relay_Pin            GPIO_Pin_8
#define  Relay_GPIO	         GPIOA
#define  Relay_RCC            RCC_APB2Periph_GPIOA


#define Relay_ON   GPIO_SetBits(Relay_GPIO, Relay_Pin);
#define Relay_OFF  GPIO_ResetBits(Relay_GPIO, Relay_Pin);

void Beep_GPIO_Config(void);

#endif