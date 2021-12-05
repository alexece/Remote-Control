//****************************************************************************************************
//
//	#define FLASH_BASE            ((uint32_t)0x08000000) 	
//	#define SRAM_BASE             ((uint32_t)0x20000000) 	
//	#define PERIPH_BASE           ((uint32_t)0x40000000) 	
//
//	#define SRAM_BB_BASE          ((uint32_t)0x22000000) 	
//	#define PERIPH_BB_BASE        ((uint32_t)0x42000000) 	
//
//	#define FSMC_R_BASE           ((uint32_t)0xA0000000) 	
//
//
//	bit_word_addr = bit_band_base + (byte_offset * 32) + (bit_number * 4)
//

//
//****************************************************************************************************
#ifndef __BITBAND_H
#define __BITBAND_H

#include "stm32f10x.h"	


//****************************************************************************************************
#define	PAout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X1080C * 32) + (Pin_x * 4)))
#define	PBout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X10C0C * 32) + (Pin_x * 4)))
#define	PCout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X1100C * 32) + (Pin_x * 4)))
#define	PDout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X1140C * 32) + (Pin_x * 4)))
#define	PEout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X1180C * 32) + (Pin_x * 4)))
#define	PFout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X11C0C * 32) + (Pin_x * 4)))
#define	PGout(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X1200C * 32) + (Pin_x * 4)))


#define	PAin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X10808 * 32) + (Pin_x * 4)))
#define	PBin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X10C08 * 32) + (Pin_x * 4)))
#define	PCin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X11008 * 32) + (Pin_x * 4)))
#define	PDin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X11408 * 32) + (Pin_x * 4)))
#define	PEin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X11808 * 32) + (Pin_x * 4)))
#define	PFin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X11C08 * 32) + (Pin_x * 4)))
#define	PGin(Pin_x)		* ((volatile unsigned long *)(0x42000000 + (0X12008 * 32) + (Pin_x * 4)))
//****************************************************************************************************

#endif	/* __BITBAND_H */
