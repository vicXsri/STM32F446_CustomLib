################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/core_m4.c \
../Src/debounce.c \
../Src/exti.c \
../Src/flash.c \
../Src/gpio.c \
../Src/it.c \
../Src/main.c \
../Src/msp.c \
../Src/pwr.c \
../Src/rcc.c \
../Src/syscalls.c \
../Src/syscfg.c \
../Src/sysmem.c \
../Src/timebase.c \
../Src/uart.c 

OBJS += \
./Src/core_m4.o \
./Src/debounce.o \
./Src/exti.o \
./Src/flash.o \
./Src/gpio.o \
./Src/it.o \
./Src/main.o \
./Src/msp.o \
./Src/pwr.o \
./Src/rcc.o \
./Src/syscalls.o \
./Src/syscfg.o \
./Src/sysmem.o \
./Src/timebase.o \
./Src/uart.o 

C_DEPS += \
./Src/core_m4.d \
./Src/debounce.d \
./Src/exti.d \
./Src/flash.d \
./Src/gpio.d \
./Src/it.d \
./Src/main.d \
./Src/msp.d \
./Src/pwr.d \
./Src/rcc.d \
./Src/syscalls.d \
./Src/syscfg.d \
./Src/sysmem.d \
./Src/timebase.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/core_m4.cyclo ./Src/core_m4.d ./Src/core_m4.o ./Src/core_m4.su ./Src/debounce.cyclo ./Src/debounce.d ./Src/debounce.o ./Src/debounce.su ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/flash.cyclo ./Src/flash.d ./Src/flash.o ./Src/flash.su ./Src/gpio.cyclo ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/it.cyclo ./Src/it.d ./Src/it.o ./Src/it.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/msp.cyclo ./Src/msp.d ./Src/msp.o ./Src/msp.su ./Src/pwr.cyclo ./Src/pwr.d ./Src/pwr.o ./Src/pwr.su ./Src/rcc.cyclo ./Src/rcc.d ./Src/rcc.o ./Src/rcc.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/syscfg.cyclo ./Src/syscfg.d ./Src/syscfg.o ./Src/syscfg.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timebase.cyclo ./Src/timebase.d ./Src/timebase.o ./Src/timebase.su ./Src/uart.cyclo ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

