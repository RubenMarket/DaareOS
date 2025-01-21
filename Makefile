# Define variables for source and build directories
CORE := CORE
OUTPUT := output
# Get list of source files
SOURCES := $(wildcard $(CORE)/*.c)
OBJECTS := $(patsubst $(CORE)/%.c,$(OUTPUT)/%.o,$(SOURCES))
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles
GCCPATH = \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin


all: clean $(OUTPUT) kernel8.img

boot.o: boot.S
	$(GCCPATH)\aarch64-none-elf-gcc $(GCCFLAGS) -c boot.S -o boot.o

$(OUTPUT):
	mkdir $(OUTPUT)

$(OUTPUT)/%.o: $(CORE)/%.c
	$(GCCPATH)\aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: boot.o $(OBJECTS)
	$(GCCPATH)\aarch64-none-elf-ld -nostdlib boot.o $(OBJECTS) -T link.ld -o kernel8.elf
	$(GCCPATH)\aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean:
	del kernel8.elf *.img
	rmdir /S /Q output


# \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin\aarch64-none-elf-gcc -mcpu=cortex-a72 -fpic -ffreestanding -c boot.S -o boot.o

# \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin\aarch64-none-elf-gcc -mcpu=cortex-a72 -fpic -ffreestanding -std=gnu99 -c main.c -o main.o -O2 -Wall -Wextra

# \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin\aarch64-none-elf-gcc -mcpu=cortex-a72 -fpic -ffreestanding -std=gnu99 -c io.c -o io.o -O2 -Wall -Wextra

# \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin\aarch64-none-elf-ld -T link.ld -o DaareOS.elf -m aarch64elf -nostdlib boot.o main.o

# \arm-gnu-toolchain-aarch64-none-elf\13.2-Rel1\bin\aarch64-none-elf-objcopy -O binary DaareOS.elf kernel8.img

# MAKE aarch64-elf-gcc 