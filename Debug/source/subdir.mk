################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/hello_world.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/hello_world.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/hello_world.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL46Z256VLL4_cm0plus -DCPU_MKL46Z256VLL4 -DFRDM_KL46Z -DFREEDOM -DPRINTF_FLOAT_ENABLE=0 -DSCANF_FLOAT_ENABLE=0 -DPRINTF_ADVANCED_ENABLE=0 -DSCANF_ADVANCED_ENABLE=0 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/source" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/CMSIS" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/drivers" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/startup" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/utilities" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/board/src" -I"/home/ngotantrung/Documents/MCUXpresso_24.9.25/workspace/spotify_hello_world/board" -O0 -fno-common -g -gdwarf-4 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/hello_world.d ./source/hello_world.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

