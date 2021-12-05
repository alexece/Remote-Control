#include "ADC1.h"

//-----------------------------------------------------------------------------------------------
void ADC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC1, ENABLE);	

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			
	GPIO_Init(GPIOA, &GPIO_InitStructure);	


	//---------------------------------------------------------------------------------------------------------------------
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//can't exceed 14MHz. 72/6 = 12MHz				

	ADC_DeInit(ADC1);  										

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC1, &ADC_InitStructure);						
	
	
	//--------------------------------------------------------------------				
	
	ADC_Cmd(ADC1, ENABLE);						
	
	
	ADC_ResetCalibration(ADC1);					 
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	
	
	ADC_StartCalibration(ADC1);	 				
 
	while(ADC_GetCalibrationStatus(ADC1));	 	

}


void ADC2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_ADC2, ENABLE);	

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			
	GPIO_Init(GPIOA, &GPIO_InitStructure);	


	//---------------------------------------------------------------------------------------------------------------------
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//can't exceed 14MHz. 72/6 = 12MHz				

	ADC_DeInit(ADC2);  										

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;			
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = 1;	
	ADC_Init(ADC2, &ADC_InitStructure);						
	
	
	//--------------------------------------------------------------------				
	
	ADC_Cmd(ADC2, ENABLE);						
	
	
	ADC_ResetCalibration(ADC2);					 
	 
	while(ADC_GetResetCalibrationStatus(ADC2));	
	
	ADC_StartCalibration(ADC2);	 				
 
	while(ADC_GetCalibrationStatus(ADC2));	 	

}


u16 Read_ADC_Throttle(void){
	
	vu16 ADC2_Read_Buff = 0;
	
	u32 avg_accum = 0;
	
	u8 n = 25;
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_3,1 , ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);	
	
	while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC)==RESET);
	
	
	for(u8 i = 0; i < n; i++){
		ADC2_Read_Buff = ADC_GetConversionValue(ADC2);
		avg_accum += ADC2_Read_Buff;
	
	}
	 ADC2_Read_Buff = (u16)(avg_accum/n);
	
	return ADC2_Read_Buff;

}

u16 Read_ADC_Yaw(void){
	
	u32 avg_accum = 0;
	
	u8 n = 25;
	
	vu16 ADC2_Read_Buff = 0;
	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);	
	
	while(ADC_GetFlagStatus(ADC2,ADC_FLAG_EOC)==RESET);
	
	
	for(u8 i = 0; i < n; i++){
		ADC2_Read_Buff = ADC_GetConversionValue(ADC2);
		avg_accum += ADC2_Read_Buff;
	
	}
	 ADC2_Read_Buff = (u16)(avg_accum/n);
	
	return ADC2_Read_Buff;

}

u16 Read_ADC_Pitch(void){
	
	u32 avg_accum = 0;
	
	u8 n = 25;
	
	vu16 ADC1_Read_Buff = 0;
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	for(u8 i = 0; i < n; i++){
		ADC1_Read_Buff = ADC_GetConversionValue(ADC1);
		avg_accum += ADC1_Read_Buff;
	
	}
	 ADC1_Read_Buff = (u16)(avg_accum/n);
	
	return ADC1_Read_Buff;

}

u16 Read_ADC_Roll(void){
	
	u32 avg_accum = 0;
	
	u8 n = 25;
	
	vu16 ADC1_Read_Buff = 0;
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	
	
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
	
	
	for(u8 i = 0; i < n; i++){
		ADC1_Read_Buff = ADC_GetConversionValue(ADC1);
		avg_accum += ADC1_Read_Buff;
	
	}
	 ADC1_Read_Buff = (u16)(avg_accum/n);
	
	return ADC1_Read_Buff;

}

//-----------------------------------------------------------------------------------------------
//void ADC1_Value_average(void)
//{

//	//------------------------------------------------------------------------
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);					
//	

//		
//	AM_ADC_Channel1_Sample += ADC1_Read_Buff[ADC_Sample][0];	
//		
//	AM_ADC_Channel2_Sample += ADC1_Read_Buff[ADC_Sample][1];

//	ADC_Sample++ ;	

//	if(ADC_Sample >= Channel_Sample)
//	{ 
//		ADC_Sample = 0; 
//		
//		AV_ADC_Channel1_Sample = AM_ADC_Channel1_Sample / Channel_Sample;		
//		
//		AM_ADC_Channel1_Sample = 0 ;
//		
//		
//		AV_ADC_Channel2_Sample = AM_ADC_Channel2_Sample / Channel_Sample;		
//		
//		AM_ADC_Channel2_Sample = 0 ;
//	}

//}
//-----------------------------------------------------------------------------------------------
