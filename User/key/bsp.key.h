#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "stm32f10x.h"


/*�������GPIO�궨��*/
#define KEY1_GPIO_PIN    GPIO_Pin_5                   //��������0
#define KEY1_GPIO_PORT   GPIOC                        //�����˿�
#define KEY1_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������ 

#define KEY2_GPIO_PIN    GPIO_Pin_6                   //��������13
#define KEY2_GPIO_PORT   GPIOC                      //�����˿�
#define KEY2_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������


#define KEY3_GPIO_PIN    GPIO_Pin_7                   //��������0
#define KEY3_GPIO_PORT   GPIOC                        //�����˿�
#define KEY3_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������ 


#define KEY4_GPIO_PIN    GPIO_Pin_8                   //��������0
#define KEY4_GPIO_PORT   GPIOC                        //�����˿�
#define KEY4_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������ 

#define KEY5_GPIO_PIN    GPIO_Pin_9                   //��������13
#define KEY5_GPIO_PORT   GPIOC                      //�����˿�
#define KEY5_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������


#define KEY6_GPIO_PIN    GPIO_Pin_10                   //��������0
#define KEY6_GPIO_PORT   GPIOC                        //�����˿�
#define KEY6_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������ 



#define KEY7_GPIO_PIN    GPIO_Pin_11                   //��������13
#define KEY7_GPIO_PORT   GPIOC                      //�����˿�
#define KEY7_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������



#define KEY8_GPIO_PIN    GPIO_Pin_12                   //��������0
#define KEY8_GPIO_PORT   GPIOC                        //�����˿�
#define KEY8_GPIO_CLK    RCC_APB2Periph_GPIOC         //�˿�Aʱ��ʹ������ 


#define KEY_GPIO_PORT   GPIOC





#define     KEY_ON         1
#define     KEY_OFF        0



void Matrix_Key_Config(void);                                //�����������ú���
uint8_t KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);  //����ɨ����
uint16_t Matrix_Scan(GPIO_TypeDef* GPIOx);    //�������ɨ����
void Write_Date(GPIO_TypeDef* GPIOx,uint16_t PortVal); //��GPIOд��ֵ
#endif
