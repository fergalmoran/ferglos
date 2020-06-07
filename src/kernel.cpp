/* 
 *  kernel.cpp 
 *  Author: Fergal Moran
 *  Copyright: 2020 Fergal Moran
 *  
 *  BSD License - do what you want
 */

#include "../include/gdt.h"
#include "../include/types.h"

void printf(char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void ferglos_Main(const void* multiboot_structure, uint32_t /*mb_mag*/) {
    printf("Welcome to FerglOS v0.0.1!");
    while (1)
        ;
}