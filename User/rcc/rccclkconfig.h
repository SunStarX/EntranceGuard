#ifndef _RCCCLKCONFIG_H
#define _RCCCLKCONFIG_H


#include "stm32f10x.h"
void HSE_SetSysClk(uint32_t RCC_PLLMul_x); //��HSE����ϵͳʱ��
void MOC_GOIO_Config();                    //����MOC
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);  //��HSI����ϵͳʱ��
#endif