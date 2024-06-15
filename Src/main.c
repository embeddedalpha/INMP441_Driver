/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"
#include "I2S.h"


I2S_Config INMP441_I2S;

int main(void)
{
	MCU_Clock_Setup();


	INMP441_I2S.I2S_Port = I2S_Config_Port.I2S2;

	INMP441_I2S.Full_Duplex.Enable = true;
	INMP441_I2S.Full_Duplex.mode = I2S_Mode.Master.Transmit;
	INMP441_I2S.Full_Duplex.MCK_Pin = I2S_MCK_Pin.I2S2.Disable;
	INMP441_I2S.Full_Duplex.EXT_SD = I2S_ext_SD_Pin.I2S2.PC02;
	INMP441_I2S.Full_Duplex.SCK_Pin = I2S_SCK_Pin.I2S2.PB10;

	I2S_Init(&INMP441_I2S);






    /* Loop forever */
	for(;;);
}