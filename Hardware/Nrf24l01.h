#ifndef __NRF24L01_H
#define __NRF24L01_H

#include "stm32f10x.h"
#include "BitBand.h"
#include "stm32f10x_spi.h"

extern const u8 RF2G4_ADDR_TX[5];

extern const u8 RF2G4_ADDR_RX[5];

extern u8 RF2G4_Send_Data[14];

extern u8 RF2G4_Receive_Data[14];
//--------------------------------
//SPI Config and Init API
extern void SPI2_Init(void);			
extern u8 SPI2_ReadWriteByte(u8 data);
extern void SPI2_SetSpeed (u8 SPI_DivideFrequency);
//--------------------------------


extern void Nrf24l01_Init(void);
		 
//--------------------------------
//-------------------------------------------------------------------------------------							
u8 Nrf24l01_Write_Reg(u8 Reg,u8 Write_Value);				
u8 Nrf24l01_Write_Cont(u8 Reg, u8* P_Data, u8 N_Data);		
u8 Nrf24l01_Read_Reg(u8 Reg);								
u8 Nrf24l01_Read_Cont(u8 Reg, u8* P_Data, u8 N_Data);		

u8 Nrf24l01_Check(void);		

void Nrf24l01_RX_Mode(void);	
void Nrf24l01_TX_Mode(void);	

u8 Nrf24l01_Tx_Packet(u8* P_Data,u8 N_Data);	
u8 Nrf24l01_Rx_Packet(u8* P_Data,u8 N_Data);	


//--------------------------------------


//-----------------------------------------------------------------------------------
#define 	R_REGISTER    		0x00  	
#define 	W_REGISTER   		0x20  	
#define 	R_RX_PAYLOAD     	0x61  	
#define 	W_TX_PAYLOAD     	0xA0  	
#define 	FLUSH_TX        	0xE1  	
#define 	FLUSH_RX        	0xE2  	
#define 	REUSE_TX_PL     	0xE3  	
#define 	NOP             	0xFF  		 
//-----------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
#define 	CONFIG          	0x00  	
#define 	EN_AA           	0x01  	
#define 	EN_RXADDR       	0x02  	
#define 	SETUP_AW        	0x03  	
#define 	SETUP_RETR      	0x04  	
#define 	RF_CH           	0x05  	
#define 	RF_SETUP        	0x06  	
#define 	STATUS          	0x07  	
										
										
#define 	OBSERVE_TX      	0x08  	
#define 	RSSI              	0x09  	
#define 	RX_ADDR_P0      	0x0A  	
#define 	RX_ADDR_P1      	0x0B  	
#define 	RX_ADDR_P2      	0x0C  	
#define 	RX_ADDR_P3      	0x0D  	
#define 	RX_ADDR_P4      	0x0E  	
#define 	RX_ADDR_P5      	0x0F  	
#define 	TX_ADDR         	0x10  	
#define 	RX_PW_P0        	0x11  	
#define 	RX_PW_P1        	0x12  	
#define 	RX_PW_P2        	0x13  	
#define 	RX_PW_P3        	0x14  	
#define 	RX_PW_P4        	0x15  	
#define 	RX_PW_P5        	0x16  	
#define 	FIFO_STATUS 		0x17  	
										
										
#define 	TX_MAX  			0x10  	
#define 	TX_OK   			0x20  	
#define 	RX_OK   			0x40  	


#define		TX_SUCCESS			0		
#define		TX_FAIL				1		
#define		TX_FAIL_MAX			2		
#define		RX_SUCCESS			0		
#define		RX_FAIL				1		
//----------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------
	   

#define 	SPI2_CE			PBout(12)
#define 	SPI2_CSN		PBout(10)
#define 	SPI2_IRQ  		PBin(11) 

#define 	SPI2_SCK		PBout(13)
#define 	SPI2_MISO		PBout(14)
#define 	SPI2_MOSI		PBout(15)



#define 	TX_ADR_WIDTH    5   		
#define 	RX_ADR_WIDTH    5   		
//---------------------------------------------------------------					   	   


//--------------------------------
#endif	/* __NRF24L01_H */


