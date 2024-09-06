#ifndef MAIN_H_
#define MAIN_H_


#include "stm32f10x.h"
#include "bsp_ili9341_lcd.h"
#include "bsp_led.h"
#include "bsp.key.h"
#include "rc522_config.h"
#include "rc522_function.h"
#include "stdio.h"
#include "bsp_Beep.h"
#include "as608_test.h"
#include "bsp_as608.h"
#include "rx_data_queue.h"
#include "bsp_i2c_ee.h"
#include "bsp_i2c_gpio.h"
#include <stdbool.h>

#define TRUE   1
#define FALSE  0


void Delay_1ms(unsigned int Del_1ms);
void RCC_Iden(void);
void Matrix_Test(void);
uint8_t Count_KEY(uint8_t Key);
void PASSWORD(uint8_t Key);
void Pass();

#endif