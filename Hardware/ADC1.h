#ifndef __ADC1_H
#define __ADC1_H


#include "stm32f10x.h"
#include "BitBand.h"
#include "delay.h"
//#include "dma.h"


//------------------------------------------------------------
//#define		ADC_Channel				2		
//#define		N_ADC_Channel_1			1		
//#define		N_ADC_Channel_2			2		
//#define		N_ADC_Channel_3			3		
//#define		N_ADC_Channel_6			6		
//#define 	Channel_Sample			10		
//------------------------------------------------------------

//--------------------------------------------------------------------------
//extern u8   ADC_Sample ;					
//	
//extern u32  AM_ADC_Channel1_Sample ;		
//extern u32  AM_ADC_Channel2_Sample ;		
//	
//extern u16  AV_ADC_Channel1_Sample ;		
//extern u16  AV_ADC_Channel2_Sample ;		


//extern vu16 ADC1_Read_Buff[Channel_Sample][ADC_Channel];	
//--------------------------------------------------------------------------


extern void ADC1_Init(void);
extern void ADC2_Init(void);
//extern u16 read_adc_value(u8 ch);
extern u16 Read_ADC_Throttle(void);
extern u16 Read_ADC_Yaw(void);
extern u16 Read_ADC_Pitch(void);
extern u16 Read_ADC_Roll(void);

//void ADC1_Value_average(void);


#endif	/* __ADC_H */
