#include "../include/echokeyboardhandler.h"

void EchoKeyboardHandler::OnKeyDown(const wchar_t* key) {
    wchar_t* foo = (wchar_t*)" ";
    foo = (wchar_t*)key;
    wprintf(foo);
}
