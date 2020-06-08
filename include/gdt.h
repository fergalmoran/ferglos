#ifndef __FERGLOS_GDT_H
#define __FERGLOS_GDT_H
#include <common/types.h>
using namespace ferglos::common;

namespace ferglos {
/*
    The Global Descriptor Table (GDT) is a data structure used by Intel x86-family processors 
    starting with the 80286 in order to define the characteristics of the various memory areas 
    used during program execution, including the base address, the size, and access privileges 
    like executability and writability. 
    These memory areas are called segments in Intel terminology.
    
    https://en.wikipedia.org/wiki/Global_Descriptor_Table

*/

class GlobalDescriptorTable {
   public:
    class SegmentDescriptor {
       private:
        uint16_t limit_lo;
        uint16_t base_lo;
        uint8_t base_hi;
        uint8_t type;
        uint8_t limit_hi_flags;
        uint8_t base_vhi;

       public:
        SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags);
        uint32_t Base();
        uint32_t Limit();

    } __attribute__((packed));

    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();
};
}  // namespace ferglos
#endif