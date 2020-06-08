#include <common/stdio.h>
#include <drivers/mouse.h>
namespace ferglos {
namespace drivers {
MouseEventHandler::MouseEventHandler() {}

void MouseEventHandler::OnActivate() {}
void MouseEventHandler::OnMouseDown(uint8_t /*button*/) {}
void MouseEventHandler::OnMouseUp(uint8_t /*button*/) {}
void MouseEventHandler::OnMouseMove(int /*x*/, int /*y*/) {}

MouseDriver::MouseDriver(
    InterruptManager* manager,
    MouseEventHandler* handler) : InterruptHandler(0x2C, manager),
                                  _dataport(0x60),
                                  _commandport(0x64) {
    this->_handler = handler;
}
MouseDriver::~MouseDriver() {}

void MouseDriver::Activate() {
    _offset = 0;
    _buttons = 0;

    _commandport.Write(0xA8);
    _commandport.Write(0x20);
    uint8_t status = _dataport.Read() | 2;
    _commandport.Write(0x60);
    _dataport.Write(status);

    _commandport.Write(0xD4);
    _dataport.Write(0xF4);
    _dataport.Read();
}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp) {
    uint8_t status = _commandport.Read();

    if (!(status & 0x20)) {
        return esp;
    }

    _buffer[_offset] = _dataport.Read();

    if (_handler == 0) {
        return esp;
    }

    _offset = (_offset + 1) % 3;

    //mouse position
    if (_offset == 0) {
        _handler->OnMouseMove(_buffer[1], -_buffer[2]);

        for (uint8_t i = 0; i < 3; i++) {
            if ((_buffer[0] & (0x01 << i)) != (_buttons & (0x01 << i))) {
                if (_buttons & (0x1 << i)) {
                    _handler->OnMouseUp(i + 1);
                } else {
                    _handler->OnMouseDown(i + 1);
                }
            }
        }
        _buttons = _buffer[0];
    }
    return esp;
}
}  // namespace drivers
}  // namespace ferglos