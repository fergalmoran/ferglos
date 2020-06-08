GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wall -Wextra
ASPARAMS = --32
LDPARAMS = -melf_i386

objs = stdio.o loader.o gdt.o port.o interruptstubs.o interrupts.o keyboard.o mouse.o kernel.o

%.o: src/%.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: src/%.s
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

clean:
	rm -rfv $(objects) iso *.o *.bin
