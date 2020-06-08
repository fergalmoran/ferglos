#ifndef __BLOCKMOUSEHANDLER_H
#define __BLOCKMOUSEHANDLER_H
#include "mouse.h"
#include "stdio.h"

class BlockMouseHandler : public MouseEventHandler {
   private:
    int8_t _screenX, _screenY;

   public:
    BlockMouseHandler();
    virtual void OnMouseMove(int xoffset, int yoffset);
};
#endif