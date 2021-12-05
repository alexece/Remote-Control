/*
Project name: Project COTY controller V1
Author: Alex Tian
Date: Oct 1st, 21
Status: Optimizing
Feature: 
	1. nRF sending data
	2. ADC reading Joystick
	3. OLDE with SPI
Optimization:
	1. LED power on indicating light
	2. buzzer
	3. QT GUI(LCD, MCU need to change)
	4. UCOS/FreeRTOS
	5. Drone open receving signal.Otherwire keep searching and pending signal. Tx may fail without receving Rx.
	6. DMA and ADC
	7. Joystick Calibration -> Make sure Throttle is low. 
	8. Add more channels
	9. Add buttons to active HMI
*/

// Device header

#include "stm32f10x.h"                  
#include "Delay.h"
#include "OLED.h"
#include "Nrf24l01.h"
#include "ADC1.h"

/*Creating a Tx buff for nRF24
stored content
{[0]Throttle reading;[1]Yaw reading; [2]Pitch Reading; [3]Roll reading}
*/
u8 Tx_Buff[14] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};	
u16 Throttle_OledDisplay =0;
u16 Yaw_OledDisplay =0;
u16 Pitch_OledDisplay =0;
u16 Roll_OledDisplay =0;

int main(void)
{	
	u8 SystemCheck_Wait_Time=0;
	u8 Joystick_Wait_Time=0;
	//initialization
	Nrf24l01_Init();
	OLED_Init();
	ADC1_Init();
	ADC2_Init();
	//boosting delay
	delay_ms(500);
	
	
	//welcoming GUI
	OLED_ShowString(1, 2, "Welcome to");
	OLED_ShowString(3, 4, "Project:COTY!");
	delay_ms(1500);
	OLED_Clear();//clear the OLED Buff
	
	
	//System Check
	OLED_ShowString(1, 2, "System   Check");
	OLED_ShowString(2, 2, "nRF24l01  Test");
	while(1){
	SystemCheck_Wait_Time = 1;
		OLED_ShowString(3, 2, "Wait Time: ");
		OLED_ShowNum(3, 13, SystemCheck_Wait_Time, 2);
		OLED_ShowString(3, 15, "S");
	if(Nrf24l01_Check()){
			OLED_ShowString(4, 2, "Status:  Fail!");
		}
		else{ 
			OLED_ShowString(4, 2, "Status:    OK!");
			break;		
		}
	delay_ms(1000);
	SystemCheck_Wait_Time++;
	}
	delay_ms(1000);
	OLED_Clear();
	//
		

	//getting ADC reading GUI
	for(Joystick_Wait_Time=0;Joystick_Wait_Time<=2;Joystick_Wait_Time++){
		OLED_ShowString(1, 2, "Joystick");
		OLED_ShowString(2, 2, "  Calibration");
		switch (Joystick_Wait_Time){
			case 0:
				OLED_ShowString(3, 2, ".");
			break;
		
			case 1:
				OLED_ShowString(3, 2, "..");
			break;
			case 2:
				OLED_ShowString(3, 2, "...");
			break;
		
		}
		delay_ms(500);
	}
	if( ((u8)(Read_ADC_Throttle()/16)) < 25){
		OLED_ShowString(3, 2, "Completed!");
	}
	else{
		OLED_ShowString(3, 2, "Plz adjust");
		OLED_ShowString(4, 2, "  Throttle down");
		while(1){
			if( ((u8)(Read_ADC_Throttle()/16)) < 25){
				break;
			}
		}
	}
	
	delay_ms(1000);
	OLED_Clear();
	
	//need to set up mode after nFR config is completed
	Nrf24l01_TX_Mode();


	
	
	while (1)
	{
		Tx_Buff[0] = (u8)(Read_ADC_Throttle()/16);
		delay_ms(30);
		Tx_Buff[1] = (u8)(Read_ADC_Yaw()/16);
		delay_ms(30);
		Tx_Buff[2] = (u8)(Read_ADC_Pitch()/16);
		delay_ms(30);
		Tx_Buff[3] = (u8)(Read_ADC_Roll()/16);

		if(Nrf24l01_Tx_Packet(Tx_Buff,14)==TX_SUCCESS){
			delay_ms(30);
		}
		else{
			while(1){
				OLED_Clear();
				OLED_ShowString(2, 2, "TX FAIL");
				OLED_ShowString(3, 2, "RETRY");
				if(Nrf24l01_Tx_Packet(Tx_Buff,14)==TX_SUCCESS){
					break;
				}
			}

		}
		OLED_Clear();
		
		Throttle_OledDisplay = (u16)(Tx_Buff[0]*4+1000);
		Yaw_OledDisplay = (u16)(Tx_Buff[1]*4+1000);
		Pitch_OledDisplay = (u16)(Tx_Buff[2]*4+1000);
		Roll_OledDisplay = (u16)(Tx_Buff[3]*4+1000);

		OLED_ShowString(1, 2, "Throttle:");
		OLED_ShowNum(1, 11, Throttle_OledDisplay, 4);
		
		
		OLED_ShowString(2, 2, "Yaw:");
		OLED_ShowNum(2, 11,Yaw_OledDisplay , 4);
		

		OLED_ShowString(3, 2, "Pitch: ");
		OLED_ShowNum(3, 11, Pitch_OledDisplay, 4);
		
		
		OLED_ShowString(4, 2, "Roll: ");
		OLED_ShowNum(4, 11,Roll_OledDisplay , 4);
		

		
	}
}
