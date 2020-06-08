#ifndef __FERGLOS_COMMON_STDIO_H
#define __FERGLOS_COMMON_STDIO_H
#include <common/types.h>
namespace ferglos {
namespace common {
void printf(const char* str);
void wprintf(const wchar_t* str);
void printfHex(uint8_t key);
void clear();
}  // namespace common
}  // namespace ferglos
#endif