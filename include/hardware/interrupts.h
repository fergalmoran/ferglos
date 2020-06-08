#ifndef __FERGLOS_HARDWARE_INTERRUPTS_H
#define __FERGLOS_HARDWARE_INTERRUPTS_H

#include <common/types.h>
#include <gdt.h>
#include <hardware/port.h>

using namespace ferglos::drivers;

namespace ferglos {
namespace hardware {
class InterruptManager;
class InterruptHandler {
   protected:
    uint8_t _interruptNumber;
    InterruptManager* _interruptManager;

    InterruptHandler(uint8_t interruptNumber, InterruptManager* interruptManager);
    ~InterruptHandler();

   public:
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

class InterruptManager {
    friend class InterruptHandler;

   protected:
    static InterruptManager* _activeInterruptManager;

    InterruptHandler* _handlers[256];

    struct GateDescriptor {
        uint16_t handlerAddressLowBits;
        uint16_t gdt_codeSegmentSelector;
        uint8_t reserved;
        uint8_t access;
        uint16_t handlerAddressHiBits;

    } __attribute__((packed));

    static GateDescriptor _interruptDescriptorTable[256];

    struct InterruptDescriptorTablePointer {
        uint16_t size;
        uint32_t base;
    } __attribute__((packed));

    static void
    SetInterruptDescriptorTableEntries(
        uint8_t interruptNumber,
        uint16_t codeSegmentSelectorOffset,
        void (*handler)(),
        uint8_t descriptorPrivilegeLevel,
        uint8_t descriptorType);

    Port8Bit_Slow _picPrimaryCommand;
    Port8Bit_Slow _picPrimaryData;
    Port8Bit_Slow _picSecondaryCommand;
    Port8Bit_Slow _picSecondaryData;

   public:
    InterruptManager(GlobalDescriptorTable* gdt);
    ~InterruptManager();

    void Activate();
    void Deactivate();

    static uint32_t HandleInterrupt(uint8_t interrupt, uint32_t esp);
    uint32_t DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp);

    static void IgnoreInterruptRequest();
    static void HandleInterruptRequest0x00();
    static void HandleInterruptRequest0x01();
    static void HandleInterruptRequest0x0C();
};
}  // namespace hardware
}  // namespace ferglos
#endif