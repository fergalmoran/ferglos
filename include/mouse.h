#ifndef __MOUSE_H
#define __MOUSE_H

#include "interrupts.h"
#include "port.h"
#include "types.h"

class MouseDriver : public InterruptHandler {
   private:
    Port8Bit _dataport;
    Port8Bit _commandport;

    uint8_t _buffer[3];
    uint8_t _offset;
    uint8_t _buttons;

    int8_t _screenX, _screenY;

   public:
    MouseDriver(InterruptManager* manager);
    ~MouseDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);
};
#endif