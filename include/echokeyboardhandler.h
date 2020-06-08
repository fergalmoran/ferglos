#ifndef __ECHOKEYBOARDHANDLER_H
#define __ECHOKEYBOARDHANDLER_H
#include "keyboard.h"
#include "stdio.h"

class EchoKeyboardHandler : public KeyboardEventHandler {
   public:
    virtual void OnKeyDown(const wchar_t* key);
};
#endif