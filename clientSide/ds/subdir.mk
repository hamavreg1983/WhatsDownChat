################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ds/hashmap.c \
../ds/queue.c \
../ds/vector.c 

OBJS += \
./ds/hashmap.o \
./ds/queue.o \
./ds/vector.o 

C_DEPS += \
./ds/hashmap.d \
./ds/queue.d \
./ds/vector.d 


# Each subdirectory must supply rules for building sources it contributes
ds/%.o: ../ds/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c90 -I../comm -I../hashmap -Isrc -I../frontEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


