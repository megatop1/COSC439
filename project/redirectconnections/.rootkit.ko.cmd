cmd_/home/rj/COSC439/project/redirectconnections/rootkit.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/rj/COSC439/project/redirectconnections/rootkit.ko /home/rj/COSC439/project/redirectconnections/rootkit.o /home/rj/COSC439/project/redirectconnections/rootkit.mod.o ;  true