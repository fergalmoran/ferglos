#ifndef __FERGLOS_DRIVERS_KEYBOARD_H
#define __FERGLOS_DRIVERS_KEYBOARD_H
#include <common/stdio.h>
#include <common/types.h>
#include <drivers/driver.h>
#include <hardware/interrupts.h>
#include <hardware/port.h>

using namespace ferglos::common;
using namespace ferglos::hardware;

namespace ferglos {
namespace drivers {

class KeyboardEventHandler {
   public:
    KeyboardEventHandler();

    virtual void OnKeyDown(const wchar_t* key);
    virtual void OnKeyUp(const wchar_t* key);
};
class KeyboardDriver : public InterruptHandler, public Driver {
   private:
    Port8Bit _dataport;
    Port8Bit _commandport;

    KeyboardEventHandler* _handler;

   public:
    KeyboardDriver(InterruptManager* manager, KeyboardEventHandler* handler);
    ~KeyboardDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();
};
}  // namespace drivers
}  // namespace ferglos
#endif