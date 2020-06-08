#include "../include/interrupts.h"

void printf(char* str);

InterruptManager::GateDescriptor InterruptManager::interruptDescriptorTable[256];

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
    : picPrimaryCommand(0x20), picPrimaryData(0x21), picSecondaryCommand(0xA0), picSecondaryData(0xA1) {
    uint16_t codeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for (uint16_t i = 0; i < 256; i++) {
        SetInterruptDescriptorTableEntries(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
    }
    // see HandleInterruptRequest in interrupts.s
    SetInterruptDescriptorTableEntries(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntries(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    picPrimaryCommand.Write(0x11);
    picSecondaryCommand.Write(0x11);

    picPrimaryData.Write(0x20);
    picSecondaryData.Write(0x28);

    picPrimaryData.Write(0x04);
    picSecondaryData.Write(0x02);

    picPrimaryData.Write(0x01);
    picSecondaryData.Write(0x01);

    picPrimaryData.Write(0x00);
    picSecondaryData.Write(0x00);

    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)interruptDescriptorTable;

    asm volatile("lidt %0"
                 :
                 : "m"(idt));
}
InterruptManager::~InterruptManager() {}

void InterruptManager::Activate() {
    asm("sti");
}

void InterruptManager::SetInterruptDescriptorTableEntries(
    uint8_t interruptNumber,
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t descriptorPrivilegeLevel,
    uint8_t descriptorType) {
    const uint8_t IDT_DESC_PRESENT = 0x80;

    interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].handlerAddressHiBits = ((uint32_t)handler >> 16) & 0xFFFF;
    interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLevel & 3) << 5);
    interruptDescriptorTable[interruptNumber].reserved = 0;
}

uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp) {
    printf("INTERRUPT");
    return esp;
}
