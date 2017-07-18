################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../frontEnd_src/ClientWhatDownApp.c \
../frontEnd_src/Client_ui.c \
../frontEnd_src/client_WhatDownApp_main.c \
../frontEnd_src/logic_FE.c 

OBJS += \
./frontEnd_src/ClientWhatDownApp.o \
./frontEnd_src/Client_ui.o \
./frontEnd_src/client_WhatDownApp_main.o \
./frontEnd_src/logic_FE.o 

C_DEPS += \
./frontEnd_src/ClientWhatDownApp.d \
./frontEnd_src/Client_ui.d \
./frontEnd_src/client_WhatDownApp_main.d \
./frontEnd_src/logic_FE.d 


# Each subdirectory must supply rules for building sources it contributes
frontEnd_src/%.o: ../frontEnd_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../comm -I../hashmap -Isrc -I../frontEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


