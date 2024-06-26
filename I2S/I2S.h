/**
 * @file I2S.h
 * @brief This file contains the definitions and function prototypes for I2S configuration and operations.
 * @author kunal
 * @date Jun 12, 2024
 */

#ifndef I2S_H_
#define I2S_H_

#include "main.h"
#include "GPIO.h"
#include "DMA.h"
#include "I2S_Defs.h"

#define I2S_Console_Debug 0 ///< Macro for enabling console debug for I2S.

#if I2S_Console_Debug
	#include "Console.h" ///< Include Console header if I2S_Console_Debug is defined.
#endif

/**
 * @struct I2S_Config
 * @brief This structure contains the configuration parameters for I2S.
 */
typedef struct I2S_Config
{
	SPI_TypeDef *Port; ///< SPI port for I2S.

	GPIO_TypeDef *LR_Pin_Port; ///< GPIO port for LR pin.
	int8_t LR_Pin_Number; ///< LR pin number.

	int8_t Standard; ///< I2S standard.
	int8_t Data_Length; ///< Data length for I2S.
	int8_t Channel_Length; ///< Channel length for I2S.
	int8_t Audio_Frequency; ///< Audio frequency for I2S.

	/**
	 * @struct Full_Duplex
	 * @brief This structure contains the configuration parameters for full duplex mode.
	 */
	struct Full_Duplex
	{
		bool Enable; ///< Enable full duplex mode.
		int8_t mode; ///< Full duplex mode.
		int8_t MCK_Pin; ///< MCK pin for full duplex mode.
		int8_t SCK_Pin; ///< SCK pin for full duplex mode.
		int8_t SD_Pin; ///< SD pin for full duplex mode.
		int8_t WS_Pin; ///< WS pin for full duplex mode.
		int8_t EXT_SD; ///< External SD for full duplex mode.
	}Full_Duplex;

	/**
	 * @struct Half_Duplex
	 * @brief This structure contains the configuration parameters for half duplex mode.
	 */
	struct Half_Duplex
	{
		bool Enable; ///< Enable half duplex mode.
		int8_t mode; ///< Half duplex mode.
		int8_t MCK_Pin; ///< MCK pin for half duplex mode.
		int8_t SCK_Pin; ///< SCK pin for half duplex mode.
		int8_t SD_Pin; ///< SD pin for half duplex mode.
		int8_t WS_Pin; ///< WS pin for half duplex mode.
	}Half_Duplex;

	/**
	 * @struct Error
	 * @brief This structure contains the error flags for I2S configuration.
	 */
	struct Error
	{
		bool Port_Error; ///< Flag for port error.
		bool Mode_Error; ///< Flag for mode error.
		bool Ext_SD_Pin_Error; ///< Flag for external SD pin error.
		bool SD_Pin_Error; ///< Flag for SD pin error.
		bool WS_Pin_Error; ///< Flag for WS pin error.
		bool SCK_Pin_Error; ///< Flag for SCK pin error.
		bool MCK_PIN_Error; ///< Flag for MCK pin error.
		bool Data_Len_Error; ///< Flag for data length error.
		bool Standard_Error; ///< Flag for standard error.
		bool Channel_Length_Error; ///< Flag for channel length error.
		bool Audio_Frequency_Error; ///< Flag for audio frequency error.
	}Error;

}I2S_Config;

void I2S_DeInit(I2S_Config *config); ///< Function for de-initializing I2S.
int8_t I2S_Init(I2S_Config *config); ///< Function for initializing I2S.
void I2S_Print_Errors(I2S_Config *config); ///< Function for printing I2S errors.

int8_t I2S_Mode_Set(I2S_Config *config); ///< Function for setting I2S mode.

void I2S_Start(I2S_Config *config); ///< Function for starting I2S.
void I2S_Stop(I2S_Config *config); ///< Function for stopping I2S.

void I2S_Select_Left_Channel(I2S_Config *config); ///< Function for selecting left channel in I2S.
void I2S_Select_Right_Channel(I2S_Config *config); ///< Function for selecting right channel in I2S.

int16_t I2S_Read_Data(I2S_Config *config); ///< Function for reading data from I2S.
void I2S_Write_Data(I2S_Config *config, uint32_t data, int len); ///< Function for writing data to I2S.

#endif /* I2S_H_ */
