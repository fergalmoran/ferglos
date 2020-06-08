#include <drivers/echokeyboardhandler.h>
namespace ferglos {
namespace drivers {
void EchoKeyboardHandler::OnKeyDown(const wchar_t* key) {
    wchar_t* foo = (wchar_t*)" ";
    foo = (wchar_t*)key;
    wprintf(foo);
}
}  // namespace drivers
}  // namespace ferglos