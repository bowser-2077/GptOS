CXX = clang++
AS = clang
LD = ld.lld
CXXFLAGS = --target=i386-elf -ffreestanding -fno-rtti -fno-exceptions -m32 -O2
ASFLAGS = --target=i386-elf -ffreestanding -m32
OBJ = boot.o kernel.o keyboard.o console.o shell.o isr.o  # <- ajouter boot.o en premier

all: iso

boot.o: kernel/boot.S
	$(AS) $(ASFLAGS) -c kernel/boot.S -o boot.o

kernel.o: kernel/kernel.cpp
	$(CXX) $(CXXFLAGS) -c kernel/kernel.cpp -o kernel.o

console.o: kernel/console.cpp
	$(CXX) $(CXXFLAGS) -c kernel/console.cpp -o console.o

keyboard.o: kernel/keyboard.cpp
	$(CXX) $(CXXFLAGS) -c kernel/keyboard.cpp -o keyboard.o

shell.o: kernel/shell.cpp
	$(CXX) $(CXXFLAGS) -c kernel/shell.cpp -o shell.o

isr.o: kernel/isr.cpp
	$(CXX) $(CXXFLAGS) -c kernel/isr.cpp -o isr.o

kernel.bin: $(OBJ)
	$(LD) -T kernel/linker.ld -o kernel.bin $(OBJ)

iso: kernel.bin
	mkdir -p isodir/boot/grub
	cp kernel.bin isodir/boot/
	cp boot/grub.cfg isodir/boot/grub/
	grub-mkrescue -o gptos.iso isodir

run: iso
	qemu-system-i386 -cdrom gptos.iso

clean:
	rm -f *.o kernel.bin gptos.iso
	rm -rf isodir
