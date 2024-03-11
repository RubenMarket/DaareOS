/* #include <stdio.h>
#include <main.h>

   compile DaareOS Desktop and DaareOS Mini

   DaareOS mini(the light device)
   - only buttons and clickable joystick control
   - fixed screen size

   DaareOS Desktop
   - Web3 Server Host
   - variable screen size
   - custom chip(abracted low level)


  Compile boot.S -> boot.o
   \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c boot.S -o ofiles/boot.o

  Compile kernel.c - > kernel.o
  \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -std=gnu99 -c main.c -o ofiles/main.o -O2 -Wall -Wextra

  Link files to OS
  \arm-gnu-toolchain-12.3.rel1-mingw-w64-i686-arm-none-eabi\bin\arm-none-eabi-gcc -T link.ld -o myos.elf -ffreestanding -O2 -nostdlib ofiles/boot.o ofiles/main.o

    
    1G raspberryi pi 2b specs


   \qemu\qemu-system-arm -m 1G -M raspi2b -serial stdio -kernel myos.elf
   \qemu\qemu-system-aarch64 -m 4G -M virt -serial stdio -kernel DaareOS.elf

MAKEFile = make

int start = 0;
bootloader params

int core() {

begin arguement contains abstracted OS workers,variables and constants with references

  
GUI(int screenWidth,int screenHeight)
  return 0;
}*/


/* void main() {
  
   Abract and Setup low level links
   input and output drivers
   interrupts and timers
   multithreading and multicore jobs and priorities
   Pass references through core function arguement
   
  while (1);
}*/
#include "io.h"
#include "fb.h"

void main()
{
   uart_init();
    fb_init();

    drawRect(150,150,400,400,0x03,0);
    drawRect(300,300,350,350,0x2e,1);

    drawCircle(960,540,250,0x0e,0);
    drawCircle(960,540,50,0x13,1);

    drawPixel(250,250,0x0e);

    drawChar('O',500,500,0x05);
    drawString(100,100,"Hello world!",0x0f);

    drawLine(100,500,350,700,0x0c);

  while (1);
}