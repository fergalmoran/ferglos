#ifndef __FERGLOS_DRIVERS_MOUSE_H
#define __FERGLOS_DRIVERS_MOUSE_H

#include <common/types.h>
#include <drivers/driver.h>
#include <hardware/interrupts.h>
#include <hardware/port.h>
using namespace ferglos::common;
using namespace ferglos::hardware;

namespace ferglos {
namespace drivers {
class MouseEventHandler {
   private:
   public:
    MouseEventHandler();

    virtual void OnActivate();
    virtual void OnMouseDown(uint8_t button);
    virtual void OnMouseUp(uint8_t button);
    virtual void OnMouseMove(int x, int y);
};

class MouseDriver : public InterruptHandler, public Driver {
   private:
    Port8Bit _dataport;
    Port8Bit _commandport;

    uint8_t _buffer[3];
    uint8_t _offset;
    uint8_t _buttons;

    MouseEventHandler* _handler;

   public:
    MouseDriver(InterruptManager* manager, MouseEventHandler* handler);
    ~MouseDriver();

    virtual uint32_t HandleInterrupt(uint32_t esp);
    virtual void Activate();
};
}  // namespace drivers
}  // namespace ferglos
#endif