#include "../include/keyboard.h"

#include "../include/stdio.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager) : InterruptHandler(0x21, manager),
                                                            _dataport(0x60),
                                                            _commandport(0x64) {
    while (_commandport.Read() & 0x01) {
        _dataport.Read();
    }
    _commandport.Write(0xAE);
    _commandport.Write(0x20);
    uint8_t status = (_dataport.Read() | 1) & ~0x10;
    _commandport.Write(0x60);
    _dataport.Write(status);

    _dataport.Write(0xF4);
}
KeyboardDriver::~KeyboardDriver() {}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    uint8_t key = _dataport.Read();
    static bool __shift = false;

    switch (key) {
        case 0xFA:
        case 0x45:
        case 0xC5:
            break;
        case 0x02:
            __shift ? printf("!") : printf("1");
            break;
        case 0x03:
            __shift ? printf("\"") : printf("2");
            break;
        case 0x04:
            __shift ? printf("£") : printf("3");
            break;
        case 0x05:
            __shift ? printf("$") : printf("4");
            break;
        case 0x06:
            __shift ? printf("%") : printf("5");
            break;
        case 0x07:
            __shift ? printf("^") : printf("6");
            break;
        case 0x08:
            __shift ? printf("&") : printf("7");
            break;
        case 0x09:
            __shift ? printf("*") : printf("8");
            break;
        case 0x0A:
            __shift ? printf("(") : printf("9");
            break;
        case 0x0B:
            __shift ? printf(")") : printf("0");
            break;

        case 0x10:
            __shift ? printf("Q") : printf("q");
            break;
        case 0x11:
            __shift ? printf("W") : printf("w");
            break;
        case 0x12:
            __shift ? printf("E") : printf("e");
            break;
        case 0x13:
            __shift ? printf("R") : printf("r");
            break;
        case 0x14:
            __shift ? printf("T") : printf("t");
            break;
        case 0x15:
            __shift ? printf("Y") : printf("y");
            break;
        case 0x16:
            __shift ? printf("U") : printf("u");
            break;
        case 0x17:
            __shift ? printf("I") : printf("i");
            break;
        case 0x18:
            __shift ? printf("O") : printf("o");
            break;
        case 0x19:
            __shift ? printf("P") : printf("p");
            break;

        case 0x1E:
            __shift ? printf("A") : printf("a");
            break;
        case 0x1F:
            __shift ? printf("S") : printf("s");
            break;
        case 0x20:
            __shift ? printf("D") : printf("d");
            break;
        case 0x21:
            __shift ? printf("F") : printf("f");
            break;
        case 0x22:
            __shift ? printf("G") : printf("g");
            break;
        case 0x23:
            __shift ? printf("H") : printf("h");
            break;
        case 0x24:
            __shift ? printf("J") : printf("j");
            break;
        case 0x25:
            __shift ? printf("K") : printf("k");
            break;
        case 0x26:
            __shift ? printf("L") : printf("l");
            break;

        case 0x2C:
            __shift ? printf("Z") : printf("z");
            break;
        case 0x2D:
            __shift ? printf("X") : printf("x");
            break;
        case 0x2E:
            __shift ? printf("C") : printf("c");
            break;
        case 0x2F:
            __shift ? printf("V") : printf("v");
            break;
        case 0x30:
            __shift ? printf("B") : printf("b");
            break;
        case 0x31:
            __shift ? printf("N") : printf("n");
            break;
        case 0x32:
            __shift ? printf("M") : printf("m");
            break;
        case 0x33:
            __shift ? printf("<") : printf(",");
            break;
        case 0x34:
            __shift ? printf(">") : printf(".");
            break;
        case 0x35:
            __shift ? printf("~") : printf("-");
            break;

        case 0x1C:
            __shift ? printf("\n") : printf("\n");
            break;
        case 0x39:
            __shift ? printf(" ") : printf(" ");
            break;

        case 0x2A:
        case 0x36:
            __shift = true;
            break;
        case 0xAA:
        case 0xB6:
            __shift = false;
            break;
        default:
            if (key < 0x80) {  //ignore unhandled key up events
                char* foo = (char*)"KEYBOARD 0x00";
                const char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[12] = hex[key & 0x0F];
                printf(foo);
                printf("\n");
                break;
            }
    }

    return esp;
}