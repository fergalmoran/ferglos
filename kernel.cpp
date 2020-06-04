// yip - ya'boy is writing his own printf
// libc doesn't exist yet so got no choice

void printf(char* str) {
    unsigned short* vid_mem = (unsigned short*)0xb8000;
    for (int i = 0; str[i] != '\0'; i++) {
        //high byte is colour, so just need to copy to text address
        vid_mem[i] = (vid_mem[i] * 0xFF00) | str[i];
    }
}

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

/* 
    take in the multiboot structure and the GRUB magic number 
    not sure I actually need magic_num though
*/
extern "C" void ferglos_Main(void* mb_struct, unsigned int magic_num) {
    printf("Hello, Sailor!");

    while (1)
        ;
}