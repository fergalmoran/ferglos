GCCPARAMS = -m32 -Iinclude -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wall -Wextra
ASPARAMS = --32
LDPARAMS = -melf_i386

objs = obj/common/stdio.o \
	   obj/loader.o  \
	   obj/gdt.o  \
	   obj/drivers/driver.o  \
	   obj/hardware/port.o  \
	   obj/hardware/interrupts.o  \
	   obj/drivers/keyboard.o  \
	   obj/drivers/echokeyboardhandler.o  \
	   obj/drivers/blockmousehandler.o  \
	   obj/drivers/mouse.o  \
	   obj/interruptstubs.o  \
	   obj/kernel.o

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	gcc $(GCCPARAMS) -c -o $@ $<

obj/%.o: src/%.s
	mkdir -p $(@D)
	as $(ASPARAMS) -o $@ $<

ferglos.bin: linker.ld $(objs)
	ld $(LDPARAMS) -T $< -o $@ $(objs)

ferglos.iso: ferglos.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp ferglos.bin iso/boot/ferglos.bin
	echo 'set timeout=0'                      > iso/boot/grub/grub.cfg
	echo 'set default=0'                     >> iso/boot/grub/grub.cfg
	echo ''                                  >> iso/boot/grub/grub.cfg
	echo 'menuentry "FerglOS" {' 			 >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/ferglos.bin'     >> iso/boot/grub/grub.cfg
	echo '  boot'                            >> iso/boot/grub/grub.cfg
	echo '}'                                 >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=ferglos.iso iso
	rm -rf iso

run: ferglos.iso
	/usr/lib/virtualbox/VirtualBoxVM --startvm ferglos
	
run-qemu: ferglos.iso
	qemu-system-i386 -boot d -cdrom ferglos.iso -m 512

.PHONY: clean
clean:
	rm -rfv obj iso *.iso *.o *.bin
