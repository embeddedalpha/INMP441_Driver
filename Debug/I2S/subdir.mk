################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2S/I2S.c 

OBJS += \
./I2S/I2S.o 

C_DEPS += \
./I2S/I2S.d 


# Each subdirectory must supply rules for building sources it contributes
I2S/%.o I2S/%.su I2S/%.cyclo: ../I2S/%.c I2S/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"D:/STM32F407_Firmware/I2S_Driver/Console" -I"D:/STM32F407_Firmware/I2S_Driver/DMA" -I"D:/STM32F407_Firmware/I2S_Driver/GPIO" -I"D:/STM32F407_Firmware/I2S_Driver/I2S" -I"D:/STM32F407_Firmware/I2S_Driver/USART" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-I2S

clean-I2S:
	-$(RM) ./I2S/I2S.cyclo ./I2S/I2S.d ./I2S/I2S.o ./I2S/I2S.su

.PHONY: clean-I2S

