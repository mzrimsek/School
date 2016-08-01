# create bootloader
nasm -f elf32 loader.s
# create executable
ld -T link.ld -melf_i386 loader.o -o kernel.elf
# move executable to correct location
mv kernel.elf iso/boot/
# create iso
genisoimage -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o os.iso iso
