################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/fonts.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f1xx.c 

CPP_SRCS += \
../Src/HourglassColorSettings.cpp \
../Src/ILI9341.cpp \
../Src/MadgwickAHRS.cpp \
../Src/Menu.cpp \
../Src/grain.cpp \
../Src/grains.cpp \
../Src/hourglass.cpp \
../Src/loadingAnimation.cpp \
../Src/main.cpp 

C_DEPS += \
./Src/fonts.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f1xx.d 

OBJS += \
./Src/HourglassColorSettings.o \
./Src/ILI9341.o \
./Src/MadgwickAHRS.o \
./Src/Menu.o \
./Src/fonts.o \
./Src/grain.o \
./Src/grains.o \
./Src/hourglass.o \
./Src/loadingAnimation.o \
./Src/main.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f1xx.o 

CPP_DEPS += \
./Src/HourglassColorSettings.d \
./Src/ILI9341.d \
./Src/MadgwickAHRS.d \
./Src/Menu.d \
./Src/grain.d \
./Src/grains.d \
./Src/hourglass.d \
./Src/loadingAnimation.d \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -c "$<" -mcpu=cortex-m3 -std=gnu11 -g3 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/HourglassColorSettings.d ./Src/HourglassColorSettings.o ./Src/HourglassColorSettings.su ./Src/ILI9341.d ./Src/ILI9341.o ./Src/ILI9341.su ./Src/MadgwickAHRS.d ./Src/MadgwickAHRS.o ./Src/MadgwickAHRS.su ./Src/Menu.d ./Src/Menu.o ./Src/Menu.su ./Src/fonts.d ./Src/fonts.o ./Src/fonts.su ./Src/grain.d ./Src/grain.o ./Src/grain.su ./Src/grains.d ./Src/grains.o ./Src/grains.su ./Src/hourglass.d ./Src/hourglass.o ./Src/hourglass.su ./Src/loadingAnimation.d ./Src/loadingAnimation.o ./Src/loadingAnimation.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f1xx_hal_msp.d ./Src/stm32f1xx_hal_msp.o ./Src/stm32f1xx_hal_msp.su ./Src/stm32f1xx_it.d ./Src/stm32f1xx_it.o ./Src/stm32f1xx_it.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/system_stm32f1xx.d ./Src/system_stm32f1xx.o ./Src/system_stm32f1xx.su

.PHONY: clean-Src

