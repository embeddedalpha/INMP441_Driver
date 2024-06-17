/*
 * I2S.c
 *
 *  Created on: Jun 12, 2024
 *      Author: kunal
 */



#include "I2S.h"


/*
 * full duplex
 *
 */

struct I2S2_DMA_Full_Duplex
{
		struct Receiver{
			DMA_Config RX;
			DMA_Config TX;
		}Receiver;

		struct Transmitter{
			DMA_Config RX;
			DMA_Config TX;
		}Transmitter;

}I2S2_DMA_Full_Duplex;

struct I2S2_DMA_Half_Duplex
{
	DMA_Config RX;
	DMA_Config TX;

}I2S2_DMA_Half_Duplex;

struct I2S3_DMA_Full_Duplex
{
	DMA_Config Master_TX;
	DMA_Config Master_RX;
	DMA_Config Slave_TX;
	DMA_Config Slave_RX;
}I2S3_DMA_Full_Duplex;

struct I2S3_DMA_Half_Duplex
{
	DMA_Config Master_TX;
	DMA_Config Master_RX;
	DMA_Config Slave_TX;
	DMA_Config Slave_RX;
}I2S3_DMA_Half_Duplex;




static int8_t SCK_PIN_INIT2(I2S_Config *config)
{
	if(config->Full_Duplex.SCK_Pin == I2S_Pin.SCK.I2S2.PB10){
		GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.SCK_Pin == I2S_Pin.SCK.I2S2.PB13){
		GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.SCK_Pin_Error = true;
		return -1;
	}
	return 1;
}
static int8_t WS_PIN_INIT2(I2S_Config *config)
{
	if(config->Full_Duplex.WS_Pin == I2S_Pin.WS.I2S2.PB09){
		GPIO_Pin_Init(GPIOB, 9, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.WS_Pin == I2S_Pin.WS.I2S2.PB12){
		GPIO_Pin_Init(GPIOB, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.WS_Pin_Error = true;
		return -1;
	}
	return 1;
}
static int8_t SD_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.SD_Pin == I2S_Pin.SD.I2S2.PB15){
		GPIO_Pin_Init(GPIOB, 15, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.SD_Pin == I2S_Pin.SD.I2S2.PC03){
		GPIO_Pin_Init(GPIOC, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.SD_Pin_Error = true;
		return -1;
	}
	return 1;
}
static int8_t MCK_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.MCK_Pin != I2S_Pin.MCK.I2S2.Disable)
	{
		if((config->Full_Duplex.MCK_Pin == I2S_Pin.MCK.I2S2.PC7)){
			GPIO_Pin_Init(GPIOC, 7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2);
		}
		else{
			config->Error.MCK_PIN_Error = true;
			return -1;
		}
	}
	return 1;
}
static int8_t EXT_SD_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.EXT_SD == I2S_Pin.EXT_SD.I2S2.PB14){
		GPIO_Pin_Init(GPIOB, 14, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.EXT_SD == I2S_Pin.EXT_SD.I2S2.PC02){
		GPIO_Pin_Init(GPIOC, 2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.Ext_SD_Pin_Error = true;
		return -1;
	}
	return 1;
}



/********************************************************************************************************/
int8_t I2S_Init(I2S_Config *config)
{
	if(config->Port == I2S_Port.I2S2)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

		SD_PIN_Init2(config);
		WS_PIN_INIT2(config);
		SCK_PIN_INIT2(config);
		MCK_PIN_Init2(config);
		if(config->Full_Duplex.Enable == true){
			EXT_SD_PIN_Init2(config);
		}
		else if(config->Half_Duplex.Enable == true)
		{

		}





	}else if(config->Port == I2S_Port.I2S3)
	{
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

	}else{

		config->Error.Port_Error = true;

	}



	config->Port->I2SCFGR |= 1 << 11;


	// I2S Mode
	if(config->Full_Duplex.mode == I2S_Mode.Master.Transmit){
		config->Port->I2SCFGR |= 2 << 8;
	}else if(config->Full_Duplex.mode == I2S_Mode.Master.Receive){
		config->Port->I2SCFGR |= 3 << 8;
	}else if(config->Full_Duplex.mode == I2S_Mode.Slave.Transmit){
		config->Port->I2SCFGR &= ~(3 << 8);
	}else if(config->Full_Duplex.mode == I2S_Mode.Slave.Receive){
		config->Port->I2SCFGR |= (1 << 8);
	}

	// Standard
	if(config->Standard == I2S_Standard.Standard_Philips){
		config->Port->I2SCFGR &= ~(3 << 4);
	}else if(config->Standard == I2S_Standard.Left_Justified){
		config->Port->I2SCFGR |= (1 << 4);
	}else if(config->Standard == I2S_Standard.Right_Justified){
		config->Port->I2SCFGR |= (2 << 4);
	}else if(config->Standard == I2S_Standard.PCM){
		config->Port->I2SCFGR |= (3 << 4);
	}else{
		config->Error.Standard_Error  = true;
	}

	if(config->Data_Length == I2S_Data_Length._16_bit){
		config->Port->I2SCFGR &= ~(3<<1);
	}else if(config->Data_Length == I2S_Data_Length._24_bit){
		config->Port->I2SCFGR |= (1<1);
	}else if(config->Data_Length == I2S_Data_Length._32_bit){
		config->Port->I2SCFGR |= (2<1);
	}else{
		config->Error.Data_Len_Error = true;
	}


	if(config->Channel_Length == I2S_Channel_Length._16_bit){
		config->Port->I2SCFGR &= ~(1<<0);
	}else if(config->Channel_Length == I2S_Channel_Length._16_bit){
		config->Port->I2SCFGR =  (1<<0);
	}else{
		config->Error.Channel_Length_Error = true;
	}


	int plli2s_n = 128;
	int plli2s_r = 5;
	if(config->Audio_Frequency == I2S_Audio_Frequency._8000KHz)
	{
		//
		  plli2s_n = 64;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 50;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._16000Hz)
	{
		//
		  plli2s_n = 128;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 50;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._22050Hz)
	{
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._32000Hz)
	{
		//
		  plli2s_n = 64;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 12;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._44100Hz)
	{
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._48000Hz)
	{
		//
		  plli2s_n = 96;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 12;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._64000Hz)
	{
		//
		  plli2s_n = 128;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 12;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._96000Hz)
	{
		//
		  plli2s_n = 192;
		  plli2s_r = 5;
		RCC -> PLLI2SCFGR = (plli2s_n << 6) | (plli2s_r << 28);
		RCC -> CR |= RCC_CR_PLLI2SON;
		while(!(RCC -> CR & RCC_CR_PLLI2SRDY));
		config->Port->I2SPR |= 12;
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._192000Hz)
	{
		//
	}else if(config->Audio_Frequency == I2S_Audio_Frequency._384000Hz)
	{
		//
	}else
	{
		config->Error.Audio_Frequency_Error = true;
	}

	//  I2S Enable
	config->Port->I2SCFGR |= 1 << 10;


	I2S_Mode_Set(config);

	return 1;

}
/********************************************************************************************************/
/********************************************************************************************************/
void I2S_Print_Errors(I2S_Config *config)
{
	if(config->Error.Audio_Frequency_Error) printConsole("Audio_Frequency_Error \r\n");
	if(config->Error.Channel_Length_Error) printConsole("Channel_Length_Error \r\n");
	if(config->Error.Data_Len_Error) printConsole("Data_Len_Error \r\n");
	if(config->Error.Ext_SD_Pin_Error) printConsole("Ext_SD_Pin_Error \r\n");
	if(config->Error.MCK_PIN_Error) printConsole("MCK_PIN_Error \r\n");
	if(config->Error.Mode_Error) printConsole("Mode_Error \r\n");
	if(config->Error.Port_Error) printConsole("Port_Error \r\n");
	if(config->Error.SCK_Pin_Error) printConsole("SCK_Pin_Error \r\n");
	if(config->Error.SD_Pin_Error) printConsole("SD_Pin_Error \r\n");
	if(config->Error.Standard_Error) printConsole("Standard_Error \r\n");
	if(config->Error.WS_Pin_Error) printConsole("WS_Pin_Error \r\n");
}
/********************************************************************************************************/
void I2S_Start(I2S_Config *config)
{
	config -> Port -> I2SCFGR |= SPI_I2SCFGR_I2SE;
}
/********************************************************************************************************/
void I2S_Stop(I2S_Config *config)
{
	config -> Port -> I2SCFGR &= ~SPI_I2SCFGR_I2SMOD;
}
/********************************************************************************************************/
void I2S_Read_Left_Data(I2S_Config *config, void *data, uint16_t len)
{
	if(config->Port == I2S_Port.I2S2)
	{
		if(config->Full_Duplex.Enable == ENABLE)
		{




		}
	}


}
/********************************************************************************************************/
int8_t I2S_Mode_Set(I2S_Config *config)
{
	int8_t retval = 0;
	if(config->Port == I2S_Port.I2S2)
	{
		if(config->Full_Duplex.Enable == ENABLE)
		{
			if((config->Full_Duplex.mode == I2S_Mode.Master.Receive) || config->Full_Duplex.mode == I2S_Mode.Slave.Receive)
			{
				I2S2_DMA_Full_Duplex.Receiver.RX.channel = 0;
				I2S2_DMA_Full_Duplex.Receiver.RX.stream = DMA1_Stream3;
				I2S2_DMA_Full_Duplex.Receiver.RX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Full_Duplex.Receiver.RX.controller = DMA1;
				I2S2_DMA_Full_Duplex.Receiver.RX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Full_Duplex.Receiver.RX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Full_Duplex.Receiver.RX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Full_Duplex.Receiver.RX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Full_Duplex.Receiver.RX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Full_Duplex.Receiver.RX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Full_Duplex.Receiver.RX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Full_Duplex.Receiver.RX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Full_Duplex.Receiver.RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;

				DMA_Init(&I2S2_DMA_Full_Duplex.Receiver.RX);

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

				I2S2_DMA_Full_Duplex.Receiver.TX.channel = 2;
				I2S2_DMA_Full_Duplex.Receiver.TX.stream = DMA1_Stream4;
				I2S2_DMA_Full_Duplex.Receiver.TX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Full_Duplex.Receiver.TX.controller = DMA1;
				I2S2_DMA_Full_Duplex.Receiver.TX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Full_Duplex.Receiver.TX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Full_Duplex.Receiver.TX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Full_Duplex.Receiver.TX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Full_Duplex.Receiver.TX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Full_Duplex.Receiver.TX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Full_Duplex.Receiver.TX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Full_Duplex.Receiver.TX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Full_Duplex.Receiver.TX.transfer_direction = DMA_Transfer_Direction.Memory_to_peripheral;
				DMA_Init(&I2S2_DMA_Full_Duplex.Receiver.TX);
			}

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

			else if((config->Full_Duplex.mode == I2S_Mode.Master.Transmit) || config->Full_Duplex.mode == I2S_Mode.Slave.Transmit)
			{
				I2S2_DMA_Full_Duplex.Transmitter.RX.channel = 0;
				I2S2_DMA_Full_Duplex.Transmitter.RX.stream = DMA1_Stream4;
				I2S2_DMA_Full_Duplex.Transmitter.RX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Full_Duplex.Transmitter.RX.controller = DMA1;
				I2S2_DMA_Full_Duplex.Transmitter.RX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Full_Duplex.Transmitter.RX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Full_Duplex.Transmitter.RX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Full_Duplex.Transmitter.RX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Full_Duplex.Transmitter.RX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Full_Duplex.Transmitter.RX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Full_Duplex.Transmitter.RX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Full_Duplex.Transmitter.RX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Full_Duplex.Transmitter.RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;

				DMA_Init(&I2S2_DMA_Full_Duplex.Transmitter.RX);

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

				I2S2_DMA_Full_Duplex.Transmitter.TX.channel = 2;
				I2S2_DMA_Full_Duplex.Transmitter.TX.stream = DMA1_Stream3;
				I2S2_DMA_Full_Duplex.Transmitter.TX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Full_Duplex.Transmitter.TX.controller = DMA1;
				I2S2_DMA_Full_Duplex.Transmitter.TX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Full_Duplex.Transmitter.TX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Full_Duplex.Transmitter.TX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Full_Duplex.Transmitter.TX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Full_Duplex.Transmitter.TX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Full_Duplex.Transmitter.TX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Full_Duplex.Transmitter.TX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Full_Duplex.Transmitter.TX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Full_Duplex.Transmitter.TX.transfer_direction = DMA_Transfer_Direction.Memory_to_peripheral;
				DMA_Init(&I2S2_DMA_Full_Duplex.Transmitter.TX);
			}



		}
		if(config->Half_Duplex.Enable == ENABLE)
		{
			if((config->Half_Duplex.mode == I2S_Mode.Master.Receive) || config->Half_Duplex.mode == I2S_Mode.Slave.Receive)
			{
				I2S2_DMA_Half_Duplex.RX.channel = 0;
				I2S2_DMA_Half_Duplex.RX.stream = DMA1_Stream3;
				I2S2_DMA_Half_Duplex.RX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Half_Duplex.RX.controller = DMA1;
				I2S2_DMA_Half_Duplex.RX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Half_Duplex.RX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Half_Duplex.RX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Half_Duplex.RX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Half_Duplex.RX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Half_Duplex.RX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Half_Duplex.RX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Half_Duplex.RX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Half_Duplex.RX.transfer_direction = DMA_Transfer_Direction.Peripheral_to_memory;

				DMA_Init(&I2S2_DMA_Half_Duplex.RX);
			}
			else if((config->Half_Duplex.mode == I2S_Mode.Master.Transmit) || config->Half_Duplex.mode == I2S_Mode.Slave.Transmit)
			{
				I2S2_DMA_Half_Duplex.TX.channel = 0;
				I2S2_DMA_Half_Duplex.TX.stream = DMA1_Stream4;
				I2S2_DMA_Half_Duplex.TX.circular_mode = DMA_Circular_Mode.Disable;
				I2S2_DMA_Half_Duplex.TX.controller = DMA1;
				I2S2_DMA_Half_Duplex.TX.flow_control = DMA_Flow_Control.DMA_Control;
				I2S2_DMA_Half_Duplex.TX.interrupts = DMA_Interrupts.Half_Transfer_Complete | DMA_Interrupts.Transfer_Complete;
				if(config->Data_Length == I2S_Data_Length._16_bit)
				{
					I2S2_DMA_Half_Duplex.TX.memory_data_size = DMA_Memory_Data_Size.half_word;
					I2S2_DMA_Half_Duplex.TX.peripheral_data_size = DMA_Peripheral_Data_Size.half_word;
				}
				else if((config->Data_Length == I2S_Data_Length._24_bit) || (config->Data_Length == I2S_Data_Length._32_bit))
				{
					I2S2_DMA_Half_Duplex.TX.memory_data_size = DMA_Memory_Data_Size.word;
					I2S2_DMA_Half_Duplex.TX.peripheral_data_size = DMA_Peripheral_Data_Size.word;
				}
				I2S2_DMA_Half_Duplex.TX.peripheral_pointer_increment = DMA_Peripheral_Pointer_Incremet.Disable;
				I2S2_DMA_Half_Duplex.TX.memory_pointer_increment = DMA_Memory_Pointer_Incremet.Enable;
				I2S2_DMA_Half_Duplex.TX.transfer_direction = DMA_Transfer_Direction.Memory_to_peripheral;

				DMA_Init(&I2S2_DMA_Half_Duplex.TX);
			}

		}
	}
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	if(config->Port == I2S_Port.I2S3)
	{

	}
	else
	{
		retval = -1;
	}


	return retval;
}


uint32_t I2S_Read_Data(I2S_Config *config)
{
	uint32_t retval = 0;
	if(config->Channel_Length == I2S_Channel_Length._16_bit)
	{
		while(!(config -> Port -> SR & SPI_SR_CHSIDE)){}
		retval =   (config -> Port -> DR);
	}
	else if(config->Channel_Length == I2S_Channel_Length._32_bit)
	{
		while(!(config -> Port -> SR & SPI_SR_CHSIDE)){}
		retval =   ((config -> Port -> DR) << 16) | ((config -> Port -> DR));
	}

	return retval;
}

void I2S_Select_Left_Channel(I2S_Config *config)
{
	GPIO_Pin_High(config->LR_Pin_Port, config->LR_Pin_Number);
}
void I2S_Select_Right_Channel(I2S_Config *config)
{
	GPIO_Pin_Low(config->LR_Pin_Port, config->LR_Pin_Number);
}


void I2S_Write_Data(I2S_Config *config, uint32_t data, int len)
{
	if(config->Channel_Length == I2S_Channel_Length._16_bit)
	{
		config -> Port -> DR = (0xFFFF & data);
	}
	else if(config->Channel_Length == I2S_Data_Length._24_bit)
	{
		config -> Port -> DR = (0x00FF0000 & data)>>16;
		config -> Port -> DR = (0x0000FFFF & data);
	}
	else if(config->Channel_Length == I2S_Data_Length._24_bit)
	{
		config -> Port -> DR = (0xFFFF0000 & data)>>16;
		config -> Port -> DR = (0x0000FFFF & data);
	}
}
