################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../comm/tcp/list/src/list.c \
../comm/tcp/list/src/list_iterator.c \
../comm/tcp/list/src/list_node.c 

OBJS += \
./comm/tcp/list/src/list.o \
./comm/tcp/list/src/list_iterator.o \
./comm/tcp/list/src/list_node.o 

C_DEPS += \
./comm/tcp/list/src/list.d \
./comm/tcp/list/src/list_iterator.d \
./comm/tcp/list/src/list_node.d 


# Each subdirectory must supply rules for building sources it contributes
comm/tcp/list/src/%.o: ../comm/tcp/list/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../comm -I../hashmap -Isrc -I../frontEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


