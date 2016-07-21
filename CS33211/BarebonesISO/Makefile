all: boot kernel loader iso
clean:
	rm boot.o kernel.o kern.iso iso/boot/kern
boot: boot.asm
	nasm -f elf64 boot.asm -o boot.o
kernel: kernel.cpp
	g++ -c kernel.cpp -o kernel.o -ffreestanding -fno-exceptions -fno-rtti
loader:
	gcc boot.o kernel.o -T linker.ld -o kern -nostdlib -nodefaultlibs -lgcc && mv kern iso/boot/
iso:
	grub-mkrescue iso --output=kern.iso
