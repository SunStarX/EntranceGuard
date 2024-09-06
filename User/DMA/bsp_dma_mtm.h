#ifndef _BSP_DMA_MTM_H_
#define _BSP_DMA_MTM_H_


#include "stm32f10x.h"

#define   BUFFER_SIZE    32
// 当使用存储器到存储器模式时候，通道可以随便选，没有硬性的规定
#define DMA_CHANNEL     DMA1_Channel4
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// 传输完成标志
#define DMA_FLAG_TC     DMA1_FLAG_TC4

#define Addr_USART1     (USART1_BASE+0x04)


uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);

void DMA_MTM_Config(void);

void DMA_MTP_Config(void);

#endif


