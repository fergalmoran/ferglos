#ifndef __FERGLOS_HARDWARE_PORT_H
#define __FERGLOS_HARDWARE_PORT_H

#include <common/types.h>
using namespace ferglos::common;

namespace ferglos {
namespace drivers {

class Port {
   protected:
    uint16_t portNumber;
    Port(uint16_t portNumber);
    ~Port();
};

class Port8Bit : public Port {
   public:
    Port8Bit(uint16_t portNumber);
    ~Port8Bit();

    virtual void Write(uint8_t data);
    virtual uint8_t Read();
};

class Port8Bit_Slow : public Port8Bit {
   public:
    Port8Bit_Slow(uint16_t portNumber);
    ~Port8Bit_Slow();

    virtual void Write(uint8_t data);
};

class Port16Bit : public Port {
   public:
    Port16Bit(uint16_t portNumber);
    ~Port16Bit();

    virtual void Write(uint16_t data);
    virtual uint16_t Read();
};

class Port32Bit : public Port {
   public:
    Port32Bit(uint16_t portNumber);
    ~Port32Bit();

    virtual void Write(uint32_t data);
    virtual uint32_t Read();
};
}  // namespace drivers
}  // namespace ferglos
#endif