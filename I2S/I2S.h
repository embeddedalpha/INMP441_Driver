/*
 * I2S.h
 *
 *  Created on: Jun 12, 2024
 *      Author: kunal
 */

#ifndef I2S_H_
#define I2S_H_

#include "main.h"
#include "GPIO.h"
#include "DMA.h"
#include "I2S_Defs.h"

#define I2S_Console_Debug


#ifdef I2S_Console_Debug
	#include "Console.h"
#endif


typedef struct I2S_Config
{
	SPI_TypeDef *Port;

	GPIO_TypeDef *LR_Pin_Port;
	uint8_t LR_Pin_Number;

	uint8_t Standard;

	uint8_t Data_Length;

	uint8_t Channel_Length;

	uint8_t Audio_Frequency;


	struct Full_Duplex
	{
		bool Enable;
		uint8_t mode;
		uint8_t MCK_Pin;
		uint8_t SCK_Pin;
		uint8_t SD_Pin;
		uint8_t WS_Pin;
		uint8_t EXT_SD;
	}Full_Duplex;

	struct Half_Duplex
	{
		bool Enable;
		uint8_t mode;
		uint8_t MCK_Pin;
		uint8_t SCK_Pin;
		uint8_t SD_Pin;
		uint8_t WS_Pin;
	}Half_Duplex;


	struct Error
	{
		bool Port_Error;
		bool Mode_Error;
		bool Ext_SD_Pin_Error;
		bool SD_Pin_Error;
		bool WS_Pin_Error;
		bool SCK_Pin_Error;
		bool MCK_PIN_Error;
		bool Data_Len_Error;
		bool Standard_Error;
		bool Channel_Length_Error;
	}Error;




}I2S_Config;


int8_t I2S_Init(I2S_Config *config);


#endif /* I2S_H_ */