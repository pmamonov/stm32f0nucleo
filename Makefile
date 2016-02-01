CROSS_COMPILE	= ../arm-2011.09/bin/arm-none-eabi-
AS		= $(CROSS_COMPILE)as
CC		= $(CROSS_COMPILE)gcc
CXX		= $(CROSS_COMPILE)g++
LD		= $(CROSS_COMPILE)ld
OBJCOPY		= $(CROSS_COMPILE)objcopy

LDSCRIPT = STM32F091CC_FLASH.ld

CFLAGS =	-mcpu=cortex-m0 -mthumb				\
		-DSTM32F091					\
		-Os -g						\
		-I./inc						\
		-ICMSIS/Device/ST/STM32F0xx/Include		\
		-ICMSIS/Include					\
		-ISTM32F0xx_StdPeriph_Driver/inc

OBJ =	src/startup_stm32f091.o					\
	src/main.o						\
	src/led.o						\
	src/stm32f0xx_it.o					\
	src/system_stm32f0xx.o					\
	STM32F0xx_StdPeriph_Driver/src/stm32f0xx_usart.o	\
	STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rcc.o		\
	STM32F0xx_StdPeriph_Driver/src/stm32f0xx_gpio.o		\
	STM32F0xx_StdPeriph_Driver/src/stm32f0xx_misc.o


all: main.bin

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@
	$(PREFIX)-size $<

main.elf: $(OBJ)
	$(CC) $(CFLAGS) -o $@ -Wl,-T$(LDSCRIPT) -Wl,-Map=linker.map -Wl,-cref -Wl,--gc-sections $^

clean:
	rm -f $(OBJ) *.elf *.bin

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

load: main.bin
	openocd -f fwload.openocd
