.set MAGIC, 0x1badb002
.set FLAGS, (1<<0 | 1<<1)
.set CHECKSUM, -(MAGIC + FLAGS) ; #GRUB needs all this stuff, I'll figure out why later

.section multiboot
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .text
.extern ferglos_Main
.extern call_constructors
.global loader

loader:
    mov $kernel_stack, %esp 

    call call_constructors
    
    push %eax
    push %ebx
    call ferglos_Main

_stop:; #infinite loop to ensure kernel stays running
    cli
    hlt
    jmp _stop

.section .bss
.space 2*1024*1024; #2MiB padding to ensure ESP doesn't get landed onto anything useful
kernel_stack:
