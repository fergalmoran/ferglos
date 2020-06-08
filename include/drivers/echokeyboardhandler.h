#ifndef __FERGLOS_DRIVERS_ECHOKEYBOARDHANDLER_H
#define __FERGLOS_DRIVERS_ECHOKEYBOARDHANDLER_H
#include <common/stdio.h>
#include <drivers/keyboard.h>

namespace ferglos {
namespace drivers {

class EchoKeyboardHandler : public KeyboardEventHandler {
   public:
    virtual void OnKeyDown(const wchar_t* key);
};
}  // namespace drivers
}  // namespace ferglos
#endif