#ifndef DMA_H_
#define DMA_H_
#include <stdio.h>
#include "support_common.h" 


void DMA_init(void);
uint32 GET_count1(void);
uint32 GET_count3(void);
void right_dma_counter_init(void);
void left_dma_counter_init(void);

#endif