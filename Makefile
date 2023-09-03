
\arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c boot.S -o ofiles/boot.o

\arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -std=gnu99 -c main.c -o ofiles/main.o -O2 -Wall -Wextra

\arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -T link.ld -o DaareOS.elf -ffreestanding -O2 -nostdlib ofiles/boot.o ofiles/main.o