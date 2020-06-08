#include "../include/keyboard.h"

#include "../include/stdio.h"

KeyboardEventHandler::KeyboardEventHandler() {}

void KeyboardEventHandler::OnKeyDown(const wchar_t* /*key*/) {}
void KeyboardEventHandler::OnKeyUp(const wchar_t* /*key*/) {}

KeyboardDriver::KeyboardDriver(
    InterruptManager* manager,
    KeyboardEventHandler* handler) : InterruptHandler(0x21, manager),
                                     _dataport(0x60),
                                     _commandport(0x64) {
    this->_handler = handler;
}
KeyboardDriver::~KeyboardDriver() {}

void KeyboardDriver::Activate() {
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

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp) {
    uint8_t key = _dataport.Read();
    static bool __shift = false;

    if (_handler == 0) {
        return esp;
    }

    switch (key) {
        case 0xFA:
        case 0x45:
        case 0xC5:
            break;
        case 0x02:
            __shift ? _handler->OnKeyDown(L"!") : _handler->OnKeyDown(L"1");
            break;
        case 0x03:
            __shift ? _handler->OnKeyDown(L"\"") : _handler->OnKeyDown(L"2");
            break;
        case 0x04:
            __shift ? _handler->OnKeyDown(L"€") : _handler->OnKeyDown(L"3");
            break;
        case 0x05:
            __shift ? _handler->OnKeyDown(L"$") : _handler->OnKeyDown(L"4");
            break;
        case 0x06:
            __shift ? _handler->OnKeyDown(L"%") : _handler->OnKeyDown(L"5");
            break;
        case 0x07:
            __shift ? _handler->OnKeyDown(L"^") : _handler->OnKeyDown(L"6");
            break;
        case 0x08:
            __shift ? _handler->OnKeyDown(L"&") : _handler->OnKeyDown(L"7");
            break;
        case 0x09:
            __shift ? _handler->OnKeyDown(L"*") : _handler->OnKeyDown(L"8");
            break;
        case 0x0A:
            __shift ? _handler->OnKeyDown(L"(") : _handler->OnKeyDown(L"9");
            break;
        case 0x0B:
            __shift ? _handler->OnKeyDown(L")") : _handler->OnKeyDown(L"0");
            break;

        case 0x10:
            __shift ? _handler->OnKeyDown(L"Q") : _handler->OnKeyDown(L"q");
            break;
        case 0x11:
            __shift ? _handler->OnKeyDown(L"W") : _handler->OnKeyDown(L"w");
            break;
        case 0x12:
            __shift ? _handler->OnKeyDown(L"E") : _handler->OnKeyDown(L"e");
            break;
        case 0x13:
            __shift ? _handler->OnKeyDown(L"R") : _handler->OnKeyDown(L"r");
            break;
        case 0x14:
            __shift ? _handler->OnKeyDown(L"T") : _handler->OnKeyDown(L"t");
            break;
        case 0x15:
            __shift ? _handler->OnKeyDown(L"Y") : _handler->OnKeyDown(L"y");
            break;
        case 0x16:
            __shift ? _handler->OnKeyDown(L"U") : _handler->OnKeyDown(L"u");
            break;
        case 0x17:
            __shift ? _handler->OnKeyDown(L"I") : _handler->OnKeyDown(L"i");
            break;
        case 0x18:
            __shift ? _handler->OnKeyDown(L"O") : _handler->OnKeyDown(L"o");
            break;
        case 0x19:
            __shift ? _handler->OnKeyDown(L"P") : _handler->OnKeyDown(L"p");
            break;

        case 0x1E:
            __shift ? _handler->OnKeyDown(L"A") : _handler->OnKeyDown(L"a");
            break;
        case 0x1F:
            __shift ? _handler->OnKeyDown(L"S") : _handler->OnKeyDown(L"s");
            break;
        case 0x20:
            __shift ? _handler->OnKeyDown(L"D") : _handler->OnKeyDown(L"d");
            break;
        case 0x21:
            __shift ? _handler->OnKeyDown(L"F") : _handler->OnKeyDown(L"f");
            break;
        case 0x22:
            __shift ? _handler->OnKeyDown(L"G") : _handler->OnKeyDown(L"g");
            break;
        case 0x23:
            __shift ? _handler->OnKeyDown(L"H") : _handler->OnKeyDown(L"h");
            break;
        case 0x24:
            __shift ? _handler->OnKeyDown(L"J") : _handler->OnKeyDown(L"j");
            break;
        case 0x25:
            __shift ? _handler->OnKeyDown(L"K") : _handler->OnKeyDown(L"k");
            break;
        case 0x26:
            __shift ? _handler->OnKeyDown(L"L") : _handler->OnKeyDown(L"l");
            break;

        case 0x2C:
            __shift ? _handler->OnKeyDown(L"Z") : _handler->OnKeyDown(L"z");
            break;
        case 0x2D:
            __shift ? _handler->OnKeyDown(L"X") : _handler->OnKeyDown(L"x");
            break;
        case 0x2E:
            __shift ? _handler->OnKeyDown(L"C") : _handler->OnKeyDown(L"c");
            break;
        case 0x2F:
            __shift ? _handler->OnKeyDown(L"V") : _handler->OnKeyDown(L"v");
            break;
        case 0x30:
            __shift ? _handler->OnKeyDown(L"B") : _handler->OnKeyDown(L"b");
            break;
        case 0x31:
            __shift ? _handler->OnKeyDown(L"N") : _handler->OnKeyDown(L"n");
            break;
        case 0x32:
            __shift ? _handler->OnKeyDown(L"M") : _handler->OnKeyDown(L"m");
            break;
        case 0x33:
            __shift ? _handler->OnKeyDown(L"<") : _handler->OnKeyDown(L",");
            break;
        case 0x34:
            __shift ? _handler->OnKeyDown(L">") : _handler->OnKeyDown(L".");
            break;
        case 0x35:
            __shift ? _handler->OnKeyDown(L"~") : _handler->OnKeyDown(L"-");
            break;

        case 0x1C:
            __shift ? _handler->OnKeyDown(L"\n") : _handler->OnKeyDown(L"\n");
            break;
        case 0x39:
            __shift ? _handler->OnKeyDown(L" ") : _handler->OnKeyDown(L" ");
            break;

        case 0x2A:
        case 0x36:
            __shift = true;
            break;
        case 0xAA:
        case 0xB6:
            __shift = false;
            break;
        default
            :
            if (key < 0x80) {  //ignore unhandled key up events
                printf("KBD: 0x");
                printfHex(key);
                printf("\n");
                break;
            }
    }

    return esp;
}