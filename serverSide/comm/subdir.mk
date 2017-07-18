################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../comm/protocol.c \
../comm/tlv.c 

OBJS += \
./comm/protocol.o \
./comm/tlv.o 

C_DEPS += \
./comm/protocol.d \
./comm/tlv.d 


# Each subdirectory must supply rules for building sources it contributes
comm/%.o: ../comm/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../comm -I../ds -I../backEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


