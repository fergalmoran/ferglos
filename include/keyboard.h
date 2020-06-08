#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "driver.h"
#include "interrupts.h"
#include "port.h"
#include "types.h"

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
#endif