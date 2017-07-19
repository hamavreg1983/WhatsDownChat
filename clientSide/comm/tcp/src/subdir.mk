################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../comm/tcp/src/tcp.c \
../comm/tcp/src/tcp_client.c 

OBJS += \
./comm/tcp/src/tcp.o \
./comm/tcp/src/tcp_client.o 

C_DEPS += \
./comm/tcp/src/tcp.d \
./comm/tcp/src/tcp_client.d 


# Each subdirectory must supply rules for building sources it contributes
comm/tcp/src/%.o: ../comm/tcp/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c90 -I../comm -I../hashmap -Isrc -I../frontEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


