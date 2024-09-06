#include "bsp.key.h"



void Matrix_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK,ENABLE);
/**********************配置按键1引脚参数*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY1_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //通用推挽输出
    GPIO_Init(KEY1_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
/**********************配置按键2引脚参数*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY2_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //通用推挽输出
	GPIO_Init(KEY2_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO

/**********************配置按键3引脚参数*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY3_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //通用推挽输出
    GPIO_Init(KEY3_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
/**********************配置按键4引脚参数*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY4_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;   //通用推挽输出
	GPIO_Init(KEY4_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
	
	/**********************配置按键5引脚参数*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY5_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //通用推挽输出
    GPIO_Init(KEY5_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
/**********************配置按键6引脚参数*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY6_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //通用推挽输出
	GPIO_Init(KEY6_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
	
	/**********************配置按键7引脚参数*********************/
	GPIO_InitStruct.GPIO_Pin   = KEY7_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //通用推挽输出
    GPIO_Init(KEY7_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	
/**********************配置按键8引脚参数*********************/
    GPIO_InitStruct.GPIO_Pin   = KEY8_GPIO_PIN;           //选择引脚
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;   //通用推挽输出
	GPIO_Init(KEY8_GPIO_PORT, & GPIO_InitStruct);         //初始化GPIO
	

	
}


/**********************按键扫描检测函数**********************/
/****功能描述：若按键按下，返回KEY_ON,若按键未按下，返回KEY_OFF****/
uint8_t KEY_Scan(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	
		 if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
			 {
					while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
					return KEY_ON;
			 }
			else return KEY_OFF;
}



/**********************矩阵键盘检测**************************/
uint16_t Matrix_Scan(GPIO_TypeDef* GPIOx)
{
	uint16_t Matrix_Value;
	Matrix_Value = GPIO_ReadInputData(GPIOx);
	return Matrix_Value;
}


/*******************向GPIO写入值***************************/
void Write_Date(GPIO_TypeDef* GPIOx,uint16_t PortVal)
{
		GPIO_Write(GPIOx, PortVal);
}