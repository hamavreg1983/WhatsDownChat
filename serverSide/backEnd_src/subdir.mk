################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../backEnd_src/backEnd_main.c \
../backEnd_src/groupsHandle.c \
../backEnd_src/ipHandle.c \
../backEnd_src/logic_backEnd.c \
../backEnd_src/usersHandle.c \
../backEnd_src/whatDownBackEndApp.c 

OBJS += \
./backEnd_src/backEnd_main.o \
./backEnd_src/groupsHandle.o \
./backEnd_src/ipHandle.o \
./backEnd_src/logic_backEnd.o \
./backEnd_src/usersHandle.o \
./backEnd_src/whatDownBackEndApp.o 

C_DEPS += \
./backEnd_src/backEnd_main.d \
./backEnd_src/groupsHandle.d \
./backEnd_src/ipHandle.d \
./backEnd_src/logic_backEnd.d \
./backEnd_src/usersHandle.d \
./backEnd_src/whatDownBackEndApp.d 


# Each subdirectory must supply rules for building sources it contributes
backEnd_src/%.o: ../backEnd_src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I../comm -I../ds -I../backEnd_src -I../comm/tcp/list/src -I../comm/tcp/src -I../src -O0 -g3 -pedantic -Wall -Wextra -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


