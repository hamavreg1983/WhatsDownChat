################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include frontEnd_src/subdir.mk
-include ds/subdir.mk
-include comm/tcp/src/subdir.mk
-include comm/tcp/server/subdir.mk
-include comm/tcp/list/src/subdir.mk
-include comm/subdir.mk
-include chats/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: whatDownApp

# Tool invocations
whatDownApp: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "whatDownApp" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) whatDownApp
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
