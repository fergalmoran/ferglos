#ifndef __FERGLOS_DRIVERS_BLOCKMOUSEHANDLER_H
#define __FERGLOS_DRIVERS_BLOCKMOUSEHANDLER_H
#include <common/stdio.h>
#include <drivers/mouse.h>

using namespace ferglos::common;

namespace ferglos {
namespace drivers {
class BlockMouseHandler : public MouseEventHandler {
   private:
    int8_t _screenX, _screenY;

   public:
    BlockMouseHandler();
    virtual void OnMouseMove(int xoffset, int yoffset);
};
}  // namespace drivers
}  // namespace ferglos
#endif