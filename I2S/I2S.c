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

static int8_t SCK_PIN_INIT2(I2S_Config *config)
{
	if(config->Full_Duplex.SCK_Pin == I2S_SCK_Pin.I2S2.PB10){
		GPIO_Pin_Init(GPIOB, 10, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.SCK_Pin == I2S_SCK_Pin.I2S2.PB13){
		GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.SCK_Pin_Error = 1;
		return -1;
	}
	return 1;
}
static int8_t WS_PIN_INIT2(I2S_Config *config)
{
	if(config->Full_Duplex.WS_Pin == I2S_WS_Pin.I2S2.PB09){
		GPIO_Pin_Init(GPIOB, 9, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.WS_Pin == I2S_WS_Pin.I2S2.PB12){
		GPIO_Pin_Init(GPIOB, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.WS_Pin_Error = 1;
		return -1;
	}
	return 1;
}
static int8_t SD_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.SD_Pin == I2S_SD_Pin.I2S2.PB15){
		GPIO_Pin_Init(GPIOB, 15, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.SD_Pin == I2S_SD_Pin.I2S2.PC03){
		GPIO_Pin_Init(GPIOC, 3, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.SD_Pin_Error = 1;
		return -1;
	}
	return 1;
}
static int8_t MCK_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.MCK_Pin != I2S_MCK_Pin.I2S2.Disable)
	{
		if((config->Full_Duplex.MCK_Pin == I2S_MCK_Pin.I2S2.PC7)){
			GPIO_Pin_Init(GPIOC, 7, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2);
		}
		else{
			config->Error.MCK_PIN_Error = 1;
			return -1;
		}
	}
	return 1;
}
static int8_t EXT_SD_PIN_Init2(I2S_Config *config)
{
	if(config->Full_Duplex.EXT_SD == I2S_ext_SD_Pin.I2S2.PB14){
		GPIO_Pin_Init(GPIOB, 14, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else if(config->Full_Duplex.EXT_SD == I2S_ext_SD_Pin.I2S2.PC02){
		GPIO_Pin_Init(GPIOC, 2, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.I2S_2EXT);
	}
	else{
		config->Error.Ext_SD_Pin_Error = 1;
		return -1;
	}
	return 1;
}



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



	}else if(config->Port == I2S_Port.I2S3)
	{

	}else{

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
	if(config->Standard == I2S_Standard.I2S_Philips){
		config->Port->I2SCFGR &= ~(3 << 4);
	}else if(config->Standard == I2S_Standard.Left_Justified){
		config->Port->I2SCFGR |= (1 << 4);
	}else if(config->Standard == I2S_Standard.Right_Justified){
		config->Port->I2SCFGR |= (2 << 4);
	}else if(config->Standard == I2S_Standard.PCM){
		config->Port->I2SCFGR |= (3 << 4);
	}else{
		config->Error.Standard_Error = 1;
	}

	if(config->Data_Length == I2S_Data_Length._16_bit){
		config->Port->I2SCFGR &= ~(3<<1);
	}else if(config->Data_Length == I2S_Data_Length._24_bit){
		config->Port->I2SCFGR |= (1<1);
	}else if(config->Data_Length == I2S_Data_Length._32_bit){
		config->Port->I2SCFGR |= (2<1);
	}else{
		config->Error.Data_Len_Error = 1;
	}


	if(config->Channel_Length == I2S_Channel_Length._16_bit){
		config->Port->I2SCFGR &= ~(1<<0);
	}else if(config->Channel_Length == I2S_Channel_Length._16_bit){
		config->Port->I2SCFGR =  (1<<0);
	}else{
		config->Error.Channel_Length_Error = 1;
	}

	//  I2S Enable
	config->Port->I2SCFGR |= 1 << 10;







	return 1;

}
