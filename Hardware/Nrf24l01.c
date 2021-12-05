#include "stm32f10x.h"
#include "stm32f10x_spi.h"
#include "BitBand.h"
#include "Nrf24l01.h"


const u8 RF2G4_ADDR_TX[5] = { 'j', 'i', 'x', 'i', 'n' } ;		// 0X6A,0X69,0X78,0X69,0X6E
const u8 RF2G4_ADDR_RX[5] = { 'j', 'i', 'x', 'i', 'n' } ;		// ASCII:jixin
//------------------------------------------------------------------------------------------
u8 RF2G4_Send_Data[14] = { 0 };		
u8 RF2G4_Receive_Data[14] = { 0 };	

u8 SPI2_ReadWriteByte(u8 data);

void SPI2_Init(void){

    GPIO_InitTypeDef    GPIO_InitStructure;
    SPI_InitTypeDef     SPI_InitStructure;
    
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  	
	
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;		
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;		
    GPIO_Init(GPIOB,&GPIO_InitStructure);
	SPI2_SCK = 1;
	SPI2_MISO = 1;
	SPI2_MOSI = 1;
    
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;//according to datasheet, check diagram analysis below
    //SPI_CPOL_High -> When CS is high, CLK is High
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;//according to datasheet, check diagram analysis below
    //SPI_CPHA_2Edge -> Read data at the second raising or falling edge
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;//CS chip select is controlled by software
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	//APB1 is CLK Source ->APB1MHz/4 = 36/4 = 9MHz 
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//datasheet will specify
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI2, &SPI_InitStructure); 
    
    SPI_Cmd(SPI2,ENABLE);
    
    SPI2_ReadWriteByte(0xFF);//start delivery
}

void SPI2_SetSpeed(u8 SPI_DivideFrequency)
{
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_DivideFrequency;	
	//SPI_Cmd(SPI2,ENABLE); 
} 

u8 SPI2_ReadWriteByte(u8 data){
    u8 TxRetry = 0;
	u8 RxRetry = 0;
    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == 0){
        TxRetry++;
        if(TxRetry>200)
		return 0;    
    }
    SPI_I2S_SendData(SPI2,data);
    TxRetry = 0;
    while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == 0){
        RxRetry ++;
        if(RxRetry>200)
		return 0;    
    }
    return SPI_I2S_ReceiveData(SPI2);
}


void Nrf24l01_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 	
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12;		
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 	GPIO_Init(GPIOB, &GPIO_InitStructure);									
  
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 				
	GPIO_Init(GPIOB, &GPIO_InitStructure);
						 

	SPI2_Init();  

	SPI2_CE = 0;	
	SPI2_CSN = 1;

	 
}

u8  Nrf24l01_Write_Reg(u8 Command,u8 Write_Value){
	
	u8 status;
	
	SPI2_CSN = 0;                 		

	status =SPI2_ReadWriteByte(Command);		

	SPI2_ReadWriteByte(Write_Value);	

	SPI2_CSN = 1;                 		

	return (status);       				

}

u8 Nrf24l01_Write_Cont(u8 Command, u8* P_Data, u8 N_Data){
	u8 status = 0;
	u8 C_Write = 0;
	SPI2_CSN = 0;          			

	status = SPI2_ReadWriteByte(Command);	

	for(C_Write = 0 ; C_Write < N_Data ; C_Write++){
		SPI2_ReadWriteByte(*P_Data++); 	
	}
	 
	SPI2_CSN = 1;       				

	return status;          				

}

u8 Nrf24l01_Read_Reg(u8 Command){
	u8 status;
	
	SPI2_CSN = 0;          					

	SPI2_ReadWriteByte(Command);   			

	status=SPI2_ReadWriteByte(0xFF);		       

	SPI2_CSN = 1;          					    

	return (status);           			

}	

u8 Nrf24l01_Read_Cont(u8 Command, u8* P_Data, u8 N_Data){
	u8 status;
	u8 C_Read = 0;
	
	SPI2_CSN = 0;           			

	status=SPI2_ReadWriteByte(Command);		

	for(C_Read = 0 ; C_Read < N_Data ; C_Read++){
		P_Data[C_Read] = SPI2_ReadWriteByte(0xFF);	
	}

	SPI2_CSN = 1;       				

	return status;        				

}

u8 Nrf24l01_Check(void){
	u8 Array_Test[5]={0X66,0X66,0X66,0X66,0X66};
	u8 C_Test = 0;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4);	

	Nrf24l01_Write_Cont(W_REGISTER+TX_ADDR,Array_Test,5);	

	Nrf24l01_Read_Cont(TX_ADDR,Array_Test,5); 				

	for(C_Test = 0; C_Test<5; C_Test++){
		if(Array_Test[C_Test]!=0X66)
			break;
	}	
	if(C_Test!=5){
		return 1;
	}
	return 0;	
}

void Nrf24l01_RX_Mode(void){
	SPI2_CE = 0;	
	Nrf24l01_Write_Cont(W_REGISTER+RX_ADDR_P0, (u8*)RF2G4_ADDR_RX, RX_ADR_WIDTH);	
	Nrf24l01_Write_Reg(W_REGISTER+EN_AA,0x01);    		
	Nrf24l01_Write_Reg(W_REGISTER+EN_RXADDR,0x01);		
	Nrf24l01_Write_Reg(W_REGISTER+RF_CH,40);	     	        
	Nrf24l01_Write_Reg(W_REGISTER+RX_PW_P0,14);		
	Nrf24l01_Write_Reg(W_REGISTER+RF_SETUP,0x27);		
	Nrf24l01_Write_Reg(W_REGISTER+CONFIG, 0x0F);		
	SPI2_CE = 1; 	

}

void Nrf24l01_TX_Mode(void){														
	SPI2_CE = 0;	
	Nrf24l01_Write_Cont(W_REGISTER+TX_ADDR,(u8*)RF2G4_ADDR_TX,TX_ADR_WIDTH);		
	Nrf24l01_Write_Cont(W_REGISTER+RX_ADDR_P0,(u8*)RF2G4_ADDR_RX,RX_ADR_WIDTH); 	
	Nrf24l01_Write_Reg(W_REGISTER+EN_AA,0x00);     	
	Nrf24l01_Write_Reg(W_REGISTER+EN_RXADDR,0x01); 	
	Nrf24l01_Write_Reg(W_REGISTER+SETUP_RETR,0x1A);	
	Nrf24l01_Write_Reg(W_REGISTER+RF_CH,40);       	
	Nrf24l01_Write_Reg(W_REGISTER+RF_SETUP,0x0F);  	
	Nrf24l01_Write_Reg(W_REGISTER+CONFIG,0x0E);    	
	SPI2_CE = 1;	

}

u8 Nrf24l01_Tx_Packet(u8* P_Data,u8 N_Data){
	u8 status;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4);
  
	SPI2_CE = 0;

	Nrf24l01_Write_Cont(W_TX_PAYLOAD,P_Data,N_Data);	

	SPI2_CE = 1;				   

	while(SPI2_IRQ != 0);	

	status = Nrf24l01_Read_Reg(STATUS);  	   

	Nrf24l01_Write_Reg(W_REGISTER+STATUS,status); 	


	if(status & TX_MAX)	
	{
		Nrf24l01_Write_Reg(FLUSH_TX,0xFF);	
		
		return TX_FAIL_MAX; 	
	}

	if(status & TX_OK)	
	{
		return TX_SUCCESS;		
	}

	return 0xFF;				

}

u8 Nrf24l01_Rx_Packet(u8* P_Data,u8 N_Data){
	u8 status;		    
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4);	

	status=Nrf24l01_Read_Reg(STATUS);  				   	 

	Nrf24l01_Write_Reg(W_REGISTER+STATUS,status); 	

	if(status & RX_OK){
		Nrf24l01_Read_Cont(R_RX_PAYLOAD,P_Data,N_Data);	
	
		Nrf24l01_Write_Reg(FLUSH_RX,0xFF);					
	
		return RX_SUCCESS; 	
	}	  

	return RX_FAIL;			

}




