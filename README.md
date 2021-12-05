# Remote-Control

This is the initial program for STM32 based remote controller.

a TX_Buff array is created with Tx_Buff[14], so theoretically it supports 14 channels. However, only 4 channels are being used

MCU: STM32F103C8T6
CORE: Cortex M3

Function: 
  1. reading 2 joysticks from ADC
  2. sending signal from nRF24L01+ module
  3. sending information and displayed at OLED module(I am using a 1.1 inch OLED, the code will be compatible with other size. Detail please check the OLED driver)
 
 Schematic will be availale once the  design is getting close to the finsh line
 
 Reaching me for questioning, developing, and improving together
 
  email: 619631221@qq.com
