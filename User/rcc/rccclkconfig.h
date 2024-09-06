#ifndef _RCCCLKCONFIG_H
#define _RCCCLKCONFIG_H


#include "stm32f10x.h"
void HSE_SetSysClk(uint32_t RCC_PLLMul_x); //用HSE配置系统时钟
void MOC_GOIO_Config();                    //配置MOC
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);  //用HSI配置系统时钟
#endif