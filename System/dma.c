#include "stm32f10x_dma.h"
#include "stm32f10x.h"
#include "ADC1.h"


//#define	ADC_Channel			2
//#define 	Channel_Sample		10

//vu16 ADC1_Read_Buff[Channel_Sample][ADC_Channel] = { 0 };
//vu16 ADC1_Read_Buff =  0 ;

//-----------------------------------------------------------------------------
//void DMA_ADC1_Init(void)
//{
//	DMA_InitTypeDef DMA_InitStructure;
//	
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); 			
//	
//	// DMA_CH1(ADC1)
//	//-------------------------------------------------------------------------
//	DMA_DeInit(DMA1_Channel1); 													
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; 					
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC1_Read_Buff; 					
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; 							
//	//DMA_InitStructure.DMA_BufferSize = ADC_Channel * Channel_Sample; 
//	DMA_InitStructure.DMA_BufferSize = 1; 	
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 			
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 					
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 		
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; 							
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High; 						
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; 								
//	DMA_Init(DMA1_Channel1, &DMA_InitStructure); 								
//	//-------------------------------------------------------------------------
//	
//	DMA_Cmd(DMA1_Channel1, ENABLE);		
//	
//}
//-----------------------------------------------------------------------------
