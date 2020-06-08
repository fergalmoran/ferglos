#include "../include/stdio.h"

#include "../include/types.h"
extern uint8_t x = 0, y = 0;

void printf(const char* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    for (int i = 0; str[i] != '\0'; ++i) {
        switch (str[i]) {
            case '\n':
                y++;
                x = 0;
                break;
            default:
                VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
                x++;
                break;
        }

        //line feed after 80 chars (terminal width)
        if (x >= 80) {
            y++;
            x = 0;
        }
        //we've reached max screen rows
        if (y > 25) {
            clear();
        }
    }
}
void wprintf(const wchar_t* str) {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    for (int i = 0; str[i] != '\0'; ++i) {
        switch (str[i]) {
            case '\n':
                y++;
                x = 0;
                break;
            default:
                VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
                x++;
                break;
        }

        //line feed after 80 chars (terminal width)
        if (x >= 80) {
            y++;
            x = 0;
        }
        //we've reached max screen rows
        if (y > 25) {
            clear();
        }
    }
}
void printfHex(uint8_t key) {
    char* foo = (char*)"00";
    const char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(foo);
}
void clear() {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;
    static uint8_t x = 0, y = 0;
    for (y = 0; y < 25; y++) {
        for (x = 0; x < 80; x++) {
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
        }
    }
}