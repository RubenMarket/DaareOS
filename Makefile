CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
GCCFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding
GCCPATH = \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin

all: clean kernel8.img

boot.o: boot.S
	$(GCCPATH)\arm-none-eabi-gcc $(GCCFLAGS) -c boot.S -o boot.o

%.o: %.c
	$(GCCPATH)\arm-none-eabi-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OFILES)
	$(GCCPATH)\arm-none-eabi-gcc -nostdlib boot.o $(OFILES) -T link.ld -o DaareOS.elf
	$(GCCPATH)\arm-none-eabi-objcopy -O binary DaareOS.elf kernel8.img

clean:
	del kernel8.elf *.o *.img


# \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c boot.S -o boot.o

# \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -std=gnu99 -c main.c -o main.o -O2 -Wall -Wextra

# \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -T link.ld -o DaareOS.elf -ffreestanding -O2 -nostdlib boot.o main.o

# \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-objcopy -O binary DaareOS.elf exe/kernel8.img

# MAKE