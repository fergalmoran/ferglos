#ifndef __STDIO_H
#define __STDIO_H
#include "types.h"

void printf(const char* str);
void wprintf(const wchar_t* str);
void printfHex(uint8_t key);
void clear();

#endif