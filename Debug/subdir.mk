################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bank.c \
../branch.c \
../client.c \
../common.c \
../main.c \
../matam.c 

OBJS += \
./bank.o \
./branch.o \
./client.o \
./common.o \
./main.o \
./matam.o 

C_DEPS += \
./bank.d \
./branch.d \
./client.d \
./common.d \
./main.d \
./matam.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


