################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../chats/netUDP_MultiCast.c 

O_SRCS += \
../chats/netUDP_MultiCast.o \
../chats/reader.o \
../chats/writer.o 

OBJS += \
./chats/netUDP_MultiCast.o 

C_DEPS += \
./chats/netUDP_MultiCast.d 


# Each subdirectory must supply rules for building sources it contributes
chats/%.o: ../chats/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../comm -I../ds -I../backEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


