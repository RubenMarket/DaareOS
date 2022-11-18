#include <stdio.h>
#include <main.h>
/*
   compile DaareOS Desktop and DaareOS Mini

   DaareOS mini(the light device)
   - only buttons and clickable joystick control
   - fixed screen size

   DaareOS Desktop
   - Web3 Server Host
   - variable screen size
   - custom chip(abracted low level)
*/

int start = 0;
//bootloader params

int core(int begin) {
/*
begin arguement contains abstracted OS workers,variables and constants with references
*/
// GUI(int screenWidth,int screenHeight)
  return 0;
}


int main(int start) {
  /*
   Abract and Setup low level links
   input and output drivers
   interrupts and timers
   multithreading and multicore jobs and priorities
   Pass references through core function arguement
   */
  core(begin);
  return 0;
}
