#include "../include/interrupts.h"

#include "../include/stdio.h"

InterruptHandler::InterruptHandler(uint8_t interruptNumber, InterruptManager* interruptManager) {
    this->_interruptNumber = interruptNumber;
    this->_interruptManager = interruptManager;

    interruptManager->_handlers[interruptNumber] = this;
}
InterruptHandler::~InterruptHandler() {
    if (_interruptManager->_handlers[_interruptNumber] == this) {
        _interruptManager->_handlers[_interruptNumber] = 0;
    }
}

uint32_t InterruptHandler::HandleInterrupt(uint32_t esp) {
    return esp;
}

InterruptManager::GateDescriptor InterruptManager::_interruptDescriptorTable[256];
InterruptManager* InterruptManager::_activeInterruptManager = 0;

InterruptManager::InterruptManager(GlobalDescriptorTable* gdt)
    : _picPrimaryCommand(0x20), _picPrimaryData(0x21), _picSecondaryCommand(0xA0), _picSecondaryData(0xA1) {
    uint16_t codeSegment = gdt->CodeSegmentSelector();
    const uint8_t IDT_INTERRUPT_GATE = 0xE;

    for (uint16_t i = 0; i < 256; i++) {
        _handlers[i] = 0;
        SetInterruptDescriptorTableEntries(i, codeSegment, &IgnoreInterruptRequest, 0, IDT_INTERRUPT_GATE);
    }
    // see HandleInterruptRequest in interrupts.s
    SetInterruptDescriptorTableEntries(0x20, codeSegment, &HandleInterruptRequest0x00, 0, IDT_INTERRUPT_GATE);
    SetInterruptDescriptorTableEntries(0x21, codeSegment, &HandleInterruptRequest0x01, 0, IDT_INTERRUPT_GATE);

    _picPrimaryCommand.Write(0x11);
    _picSecondaryCommand.Write(0x11);

    _picPrimaryData.Write(0x20);
    _picSecondaryData.Write(0x28);

    _picPrimaryData.Write(0x04);
    _picSecondaryData.Write(0x02);

    _picPrimaryData.Write(0x01);
    _picSecondaryData.Write(0x01);

    _picPrimaryData.Write(0x00);
    _picSecondaryData.Write(0x00);

    InterruptDescriptorTablePointer idt;
    idt.size = 256 * sizeof(GateDescriptor) - 1;
    idt.base = (uint32_t)_interruptDescriptorTable;

    asm volatile("lidt %0"
                 :
                 : "m"(idt));
}
InterruptManager::~InterruptManager() {}

void InterruptManager::Activate() {
    if (_activeInterruptManager != 0) {
        _activeInterruptManager->Deactivate();
    }

    _activeInterruptManager = this;
    asm("sti");
}

void InterruptManager::Deactivate() {
    if (_activeInterruptManager == this) {
        _activeInterruptManager = 0;
        asm("cli");
    }
}

void InterruptManager::SetInterruptDescriptorTableEntries(
    uint8_t interruptNumber,
    uint16_t codeSegmentSelectorOffset,
    void (*handler)(),
    uint8_t descriptorPrivilegeLevel,
    uint8_t descriptorType) {
    const uint8_t IDT_DESC_PRESENT = 0x80;

    _interruptDescriptorTable[interruptNumber].handlerAddressLowBits = ((uint32_t)handler) & 0xFFFF;
    _interruptDescriptorTable[interruptNumber].handlerAddressHiBits = ((uint32_t)handler >> 16) & 0xFFFF;
    _interruptDescriptorTable[interruptNumber].gdt_codeSegmentSelector = codeSegmentSelectorOffset;
    _interruptDescriptorTable[interruptNumber].access = IDT_DESC_PRESENT | descriptorType | ((descriptorPrivilegeLevel & 3) << 5);
    _interruptDescriptorTable[interruptNumber].reserved = 0;
}

uint32_t InterruptManager::HandleInterrupt(uint8_t interruptNumber, uint32_t esp) {
    if (_activeInterruptManager != 0) {
        return _activeInterruptManager->DoHandleInterrupt(interruptNumber, esp);
    }
    return esp;
}
uint32_t InterruptManager::DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp) {
    if (_handlers[interruptNumber] != 0) {
        //we have a handler registered for this interrupt
        esp = _handlers[interruptNumber]->HandleInterrupt(esp);
    } else if (interruptNumber != 0x20) {
        //no handler registered
        char* foo = (char*)"UNHANDLED INTERRUPT";
        const char* hex = "0123456789ABCDEF";
        foo[22] = hex[(interruptNumber >> 4) & 0x0F];
        foo[23] = hex[interruptNumber & 0x0F];
        printf(foo);
    }
    if (0x20 <= interruptNumber && interruptNumber < 0x30) {
        _picPrimaryCommand.Write(0x20);
        if (0x28 <= interruptNumber && interruptNumber < 0x30) {
            _picSecondaryCommand.Write(0x20);
        }
    }
    return esp;
}
