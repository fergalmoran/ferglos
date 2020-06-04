GPPPARAMS = -m32 
ASPARAMS = --32
LDPARAMS = -melf_i386

objs = loader.o kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

ferglos.bin: linker.ld $(objs)
	ld $(LDPARAMS) -T linker.ld $< -o $@ $(objs)

install: ferglos.bin
	sudo cp $< /boot/ferglos.bin
