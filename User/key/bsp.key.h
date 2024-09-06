#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "stm32f10x.h"


/*矩阵键盘GPIO宏定义*/
#define KEY1_GPIO_PIN    GPIO_Pin_5                   //按键引脚0
#define KEY1_GPIO_PORT   GPIOC                        //按键端口
#define KEY1_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置 

#define KEY2_GPIO_PIN    GPIO_Pin_6                   //按键引脚13
#define KEY2_GPIO_PORT   GPIOC                      //按键端口
#define KEY2_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置


#define KEY3_GPIO_PIN    GPIO_Pin_7                   //按键引脚0
#define KEY3_GPIO_PORT   GPIOC                        //按键端口
#define KEY3_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置 


#define KEY4_GPIO_PIN    GPIO_Pin_8                   //按键引脚0
#define KEY4_GPIO_PORT   GPIOC                        //按键端口
#define KEY4_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置 

#define KEY5_GPIO_PIN    GPIO_Pin_9                   //按键引脚13
#define KEY5_GPIO_PORT   GPIOC                      //按键端口
#define KEY5_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置


#define KEY6_GPIO_PIN    GPIO_Pin_10                   //按键引脚0
#define KEY6_GPIO_PORT   GPIOC                        //按键端口
#define KEY6_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置 



#define KEY7_GPIO_PIN    GPIO_Pin_11                   //按键引脚13
#define KEY7_GPIO_PORT   GPIOC                      //按键端口
#define KEY7_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置



#define KEY8_GPIO_PIN    GPIO_Pin_12                   //按键引脚0
#define KEY8_GPIO_PORT   GPIOC                        //按键端口
#define KEY8_GPIO_CLK    RCC_APB2Periph_GPIOC         //端口A时钟使能配置 


#define KEY_GPIO_PORT   GPIOC





#define     KEY_ON         1
#define     KEY_OFF        0



void Matrix_Key_Config(void);                                //按键参数配置函数
uint8_t KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  //按键扫描检测
uint16_t Matrix_Scan(GPIO_TypeDef* GPIOx);    //矩阵键盘扫描检测
void Write_Date(GPIO_TypeDef* GPIOx,uint16_t PortVal); //向GPIO写入值
#endif
