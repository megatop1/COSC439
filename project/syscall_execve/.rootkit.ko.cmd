cmd_/home/rj/COSC439/project/syscall_execve/rootkit.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/rj/COSC439/project/syscall_execve/rootkit.ko /home/rj/COSC439/project/syscall_execve/rootkit.o /home/rj/COSC439/project/syscall_execve/rootkit.mod.o ;  true
