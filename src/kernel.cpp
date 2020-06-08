/* 
 *  kernel.cpp 
 *  Author: Fergal Moran
 *  Copyright: 2020 Fergal Moran
 *  
 *  BSD License - do what you want
 */

#include "../include/gdt.h"
#include "../include/interrupts.h"
#include "../include/keyboard.h"
#include "../include/stdio.h"
#include "../include/types.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void ferglos_Main(const void* multiboot_structure, uint32_t /*mb_mag*/) {
    printf("Welcome to FerglOS v0.0.2!\n\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);
    KeyboardDriver keyboard(&interrupts);

    interrupts.Activate();

    while (1)
        ;
}