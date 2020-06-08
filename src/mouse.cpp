#include "../include/mouse.h"

#include "../include/stdio.h"

MouseDriver::MouseDriver(InterruptManager* manager) : InterruptHandler(0x2C, manager),
                                                      _dataport(0x60),
                                                      _commandport(0x64) {
    _offset = 0;
    _buttons = 0;

    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    //flip bit in center of screen - so mousepointer is initially here
    _screenX = 40;
    _screenY = 12;

    VideoMemory[80 * _screenY + _screenX] =
        (VideoMemory[80 * _screenY + _screenX] & 0x0F00) << 4 |
        (VideoMemory[80 * _screenY + _screenX] & 0xF000) >> 4 |
        (VideoMemory[80 * _screenY + _screenX] & 0x00FF);

    _commandport.Write(0xA8);
    _commandport.Write(0x20);
    uint8_t status = _dataport.Read() | 2;
    _commandport.Write(0x60);
    _dataport.Write(status);

    _commandport.Write(0xD4);
    _dataport.Write(0xF4);
    _dataport.Read();
}
MouseDriver::~MouseDriver() {}

uint32_t MouseDriver::HandleInterrupt(uint32_t esp) {
    uint8_t status = _commandport.Read();

    if (!(status & 0x20)) {
        return esp;
    }

    _buffer[_offset] = _dataport.Read();
    _offset = (_offset + 1) % 3;

    //mouse position
    if (_offset == 0) {
        static uint16_t* VideoMemory = (uint16_t*)0xb8000;

        //flip bit on screen where mouse cursor is
        VideoMemory[80 * _screenY + _screenX] =
            ((VideoMemory[80 * _screenY + _screenX] & 0xF000) >> 4) |
            ((VideoMemory[80 * _screenY + _screenX] & 0x0F00) << 4) |
            ((VideoMemory[80 * _screenY + _screenX] & 0x00FF));

        _screenX += _buffer[1];
        _screenY -= _buffer[2];

        // check for mouse moving off screen
        if (_screenX < 0) {
            _screenX = 0;
        }
        if (_screenX >= 80) {
            _screenX = 79;
        }
        if (_screenY < 0) {
            _screenY = 0;
        }
        if (_screenY >= 25) {
            _screenY = 24;
        }

        VideoMemory[80 * _screenY + _screenX] =
            ((VideoMemory[80 * _screenY + _screenX] & 0xF000) >> 4) |
            ((VideoMemory[80 * _screenY + _screenX] & 0x0F00) << 4) |
            ((VideoMemory[80 * _screenY + _screenX] & 0x00FF));
    }
    return esp;
}