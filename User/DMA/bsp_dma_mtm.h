#ifndef _BSP_DMA_MTM_H_
#define _BSP_DMA_MTM_H_


#include "stm32f10x.h"

#define   BUFFER_SIZE    32
// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨
#define DMA_CHANNEL     DMA1_Channel4
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// ������ɱ�־
#define DMA_FLAG_TC     DMA1_FLAG_TC4

#define Addr_USART1     (USART1_BASE+0x04)


uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength);

void DMA_MTM_Config(void);

void DMA_MTP_Config(void);

#endif


