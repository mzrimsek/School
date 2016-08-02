all: loader kernel iso run
loader:
	nasm -f elf32 loader.s
kernel:
	ld -T link.ld -melf_i386 loader.o -o kernel.elf
iso: kernel.elf
	cp kernel.elf iso/boot/
	genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso
run:
	bochs -f bochsrc.txt -q
clean:
	rm -rf *.o kernel.elf os.iso bochslog.txt
