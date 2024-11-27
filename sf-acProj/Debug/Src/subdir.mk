################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/LED.c \
../Src/button.c \
../Src/buzzer.c \
../Src/delay.c \
../Src/main.c \
../Src/sf344fun.c \
../Src/sys_init.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timers.c 

OBJS += \
./Src/LED.o \
./Src/button.o \
./Src/buzzer.o \
./Src/delay.o \
./Src/main.o \
./Src/sf344fun.o \
./Src/sys_init.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timers.o 

C_DEPS += \
./Src/LED.d \
./Src/button.d \
./Src/buzzer.d \
./Src/delay.d \
./Src/main.d \
./Src/sf344fun.d \
./Src/sys_init.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32L4 -DSTM32 -DNUCLEO_L476RG -DSTM32L476RGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/LED.cyclo ./Src/LED.d ./Src/LED.o ./Src/LED.su ./Src/button.cyclo ./Src/button.d ./Src/button.o ./Src/button.su ./Src/buzzer.cyclo ./Src/buzzer.d ./Src/buzzer.o ./Src/buzzer.su ./Src/delay.cyclo ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/sf344fun.cyclo ./Src/sf344fun.d ./Src/sf344fun.o ./Src/sf344fun.su ./Src/sys_init.cyclo ./Src/sys_init.d ./Src/sys_init.o ./Src/sys_init.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timers.cyclo ./Src/timers.d ./Src/timers.o ./Src/timers.su

.PHONY: clean-Src

