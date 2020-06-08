#include "../include/blockmousehandler.h"

#include "stdio.h"

BlockMouseHandler::BlockMouseHandler() {
    //flip bit in center of screen - so mousepointer is initially here
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    _screenX = 40;
    _screenY = 12;
    VideoMemory[80 * _screenY + _screenX] =
        (VideoMemory[80 * _screenY + _screenX] & 0x0F00) << 4 |
        (VideoMemory[80 * _screenY + _screenX] & 0xF000) >> 4 |
        (VideoMemory[80 * _screenY + _screenX] & 0x00FF);
}

void BlockMouseHandler::OnMouseMove(int xoffset, int yoffset) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    //flip bit on screen where mouse cursor is
    VideoMemory[80 * _screenY + _screenX] =
        ((VideoMemory[80 * _screenY + _screenX] & 0xF000) >> 4) |
        ((VideoMemory[80 * _screenY + _screenX] & 0x0F00) << 4) |
        ((VideoMemory[80 * _screenY + _screenX] & 0x00FF));

    _screenX += xoffset;
    _screenY += yoffset;

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
