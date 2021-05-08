#!/bin/bash
#compile and link
echo "Script File c.sh"
#yasm -g dwarf2 -iformat=yasm -f elf64 -o asmfiles.o asmfiles.asm -l asmfiles.lst
gcc -c -Wa,-adhln -g -masm=intel helloworld.c > helloworld.lst
gcc -Xlinker -Map=helloworld.map -o helloworld helloworld.o 
echo "Done"
