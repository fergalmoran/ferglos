#include "../include/blockmousehandler.h"
#include "../include/driver.h"
#include "../include/echokeyboardhandler.h"
#include "../include/gdt.h"
#include "../include/interrupts.h"
#include "../include/keyboard.h"
#include "../include/mouse.h"
#include "../include/stdio.h"
#include "../include/types.h"

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors() {
    for (constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void ferglos_Main(const void* /*multiboot_structure*/, uint32_t /*mb_mag*/) {
    clear();
    printf("FerglOS v0.0.2!\n");
    printf("Floats like a lepidoptera, stings like a hymenoptera\n");

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    printf("Initialising hardware\n");
    DriverManager drvManager;

    EchoKeyboardHandler kbHandler;
    KeyboardDriver keyboard(&interrupts, &kbHandler);
    drvManager.AddDriver(&keyboard);

    BlockMouseHandler mouseHandler;
    MouseDriver mouse(&interrupts, &mouseHandler);
    drvManager.AddDriver(&mouse);

    printf("Initialising driver manager\n");
    drvManager.ActivateAll();

    printf("Initialising interrupt handler\n");
    interrupts.Activate();

    while (1)
        ;
}