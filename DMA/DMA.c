/*
 * DMA.c
 *
 *  Created on: Nov 16, 2023
 *      Author: kunal
 */


#include "DMA.h"

/**
 * @brief Enables the clock for the specified DMA controller.
 * 
 * This function enables the clock for the DMA controller specified in the 
 * DMA_Config structure.
 * 
 * @param config Pointer to the DMA configuration structure.
 */
void DMA_Clock_Enable(DMA_Config *config)
{
	if(config->controller == DMA1) RCC -> AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	if(config->controller == DMA2) RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
}

/**
 * @brief Disables the clock for the specified DMA controller.
 * 
 * This function disables the clock for the DMA controller specified in the 
 * DMA_Config structure.
 * 
 * @param config Pointer to the DMA configuration structure.
 */
void DMA_Clock_Disable(DMA_Config *config)
{

	if(config->controller == DMA1) RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA1EN;
	if(config->controller == DMA2) RCC -> AHB1ENR &= ~RCC_AHB1ENR_DMA2EN;
}


/**
 * @brief Resets the specified DMA controller.
 * 
 * This function resets the DMA controller specified in the DMA_Config structure.
 * 
 * @param config Pointer to the DMA configuration structure.
 */
void DMA_Reset(DMA_Config *config)
{
	if(config->controller == DMA1) RCC -> AHB1RSTR |= RCC_AHB1RSTR_DMA1RST;
	if(config->controller == DMA2) RCC -> AHB1RSTR |= RCC_AHB1RSTR_DMA2RST;
}



/**
 * @brief Initializes the DMA with the given configuration.
 * 
 * This function initializes the DMA stream with the settings provided 
 * in the DMA_Config structure.
 * 
 * @param config Pointer to the DMA configuration structure.
 */

void DMA_Init(DMA_Config *config)
{
	DMA_Clock_Enable(config);
	config -> stream -> CR |= config -> channel << DMA_SxCR_CHSEL_Pos;
	config -> stream -> CR |= config -> circular_mode;
	config -> stream -> CR |= config -> flow_control;
	config -> stream -> CR |= config -> priority_level;
	config -> stream -> CR |= config -> memory_data_size;
	config -> stream -> CR |= config -> peripheral_data_size;
	config -> stream -> CR |= config -> transfer_direction;
	config -> stream -> CR |= config -> interrupts;
	config -> stream -> CR |= config -> memory_pointer_increment;
	config -> stream -> CR |= config -> peripheral_pointer_increment;
}



/**
 * @brief Sets the target addresses and buffer length for the DMA transfer.
 * 
 * This function sets the memory address, peripheral address, and buffer length 
 * for the DMA transfer as specified in the DMA_Config structure.
 * 
 * @param config Pointer to the DMA configuration structure.
 */

void DMA_Set_Target(DMA_Config *config)
{
	config -> stream -> NDTR = config -> buffer_length;
	config -> stream -> M0AR = (uint32_t)config->memory_address;
	config -> stream -> PAR = (uint32_t)config->peripheral_address;

}

/**
 * @brief Starts the DMA transfer.
 * 
 * This function triggers the DMA transfer and waits for its completion.
 * 
 * @param config Pointer to the DMA configuration structure.
 * @return Returns 1 upon successful completion of the transfer.
 */

void DMA_Set_Trigger(DMA_Config *config)
{

	config->controller->LIFCR = 0xF7D0F7D;
	config->controller->HIFCR = 0xF7D0F7D;
	config -> stream -> CR |= DMA_SxCR_EN;




	if((config->stream == DMA1_Stream0) || (config->stream == DMA2_Stream0))
	{
		while(!(config->controller->LISR & DMA_LISR_TCIF0));
		config->controller->LIFCR |= 0x3D;
	}
	else if((config->stream == DMA1_Stream1) || (config->stream == DMA2_Stream1))
	{
		while(!(config->controller->LISR & DMA_LISR_TCIF1));
		config->controller->LIFCR |= 0x3D<<6;
	}
	else if((config->stream == DMA1_Stream2) || (config->stream == DMA2_Stream2))
	{
		while(!(config->controller->LISR & DMA_LISR_TCIF2));
		config->controller->LIFCR |= 0x3D<<16;
	}
	else if((config->stream == DMA1_Stream3) || (config->stream == DMA2_Stream3))
	{
		while(!(config->controller->LISR & DMA_LISR_TCIF3));
		config->controller->LIFCR |= 0x3D<<22;
	}
	if((config->stream == DMA1_Stream4) || (config->stream == DMA2_Stream4))
	{
		while(!(config->controller->HISR & DMA_HISR_TCIF4));
		config->controller->HIFCR |= (1 << 0);
	}
	else if((config->stream == DMA1_Stream5) || (config->stream == DMA2_Stream5))
	{
		while(!(config->controller->HISR & DMA_HISR_TCIF5));
		config->controller->LIFCR |= 0x3D<<6;
	}
	else if((config->stream == DMA1_Stream6) || (config->stream == DMA2_Stream6))
	{
		while(!(config->controller->HISR & DMA_HISR_TCIF6));
		config->controller->HIFCR |= 0x3D<<16;
	}
	else if((config->stream == DMA1_Stream7) || (config->stream == DMA2_Stream7))
	{
		while(!(config->controller->HISR & DMA_HISR_TCIF7));
		config->controller->HIFCR |= 0x3D<<22;
	}





}


void DMA_Memory_To_Memory_Transfer(uint32_t *source,
						  uint8_t source_data_size, uint8_t dest_data_size,
		                  uint32_t *destination, bool source_increment,
						  bool destination_increment, uint16_t length)
{

	RCC -> AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	DMA2_Stream0->CR &= (DMA_SxCR_CHSEL);
	DMA2_Stream0->CR |= (DMA_Transfer_Direction.Memory_to_memory);
	DMA2_Stream0->CR |= (DMA_SxCR_TCIE | DMA_SxCR_PL);

	if(source_data_size == 32)
	{
		DMA2_Stream0->CR |= DMA_SxCR_PSIZE;
	}else if(source_data_size == 16)
	{
		DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0;
		DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE_1;
	}else
	{
		DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE;
	}

	if(dest_data_size == 32)
	{
		DMA2_Stream0->CR |= DMA_SxCR_MSIZE;
	}else if(dest_data_size == 16)
	{
		DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0;
		DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE_1;
	}else
	{
		DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE;
	}

	if(source_increment == 1)
	{
		DMA2_Stream0->CR |= DMA_SxCR_PINC;
	}
	else{
		DMA2_Stream0->CR &= ~DMA_SxCR_PINC;
	}

	if(destination_increment == 1)
	{
		DMA2_Stream0->CR |= DMA_SxCR_MINC;
	}
	else{
		DMA2_Stream0->CR &= ~DMA_SxCR_MINC;
	}

	DMA2_Stream0 -> PAR = (uint32_t)(source);
	DMA2_Stream0 -> M0AR = (uint32_t)(destination);
	DMA2_Stream0 -> NDTR = (uint16_t)length;
	DMA2_Stream0 -> CR |= DMA_SxCR_EN;

	while((DMA2 -> LISR & (DMA_LISR_TCIF0_Msk)) == 0){}
	DMA2 -> LIFCR |= DMA_LIFCR_CTCIF0;

	DMA2_Stream0 -> CR &= ~DMA_SxCR_EN;
}


