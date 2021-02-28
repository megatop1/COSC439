#include <linux/module.h>
#include <linux/kernel.h> // Debug Messages like KERN_INFO
#include <linux/init.h> //gives us access to macros


static int HelloInit(void) { 
	
	printk(KERN_INFO "ROOTKITDEV_DEBUG: Hello World! \n"); //KERN_INFO is the level of msg we are sending (DEBUG message), lvl of severity, like KERNEL_WARN etc
                                                               //Will print when the driver is successfully loaded into memory
	return 0; //return 0 upon success
}

static void HelloExit(void) { 
   printk(KERN_INFO "ROOTKIT_DEBUG: GOODBYE WORLD \n"); 
}

//Prototypes
module_init(HelloInit);
module_exit(HelloExit);

MODULE_LICENSE("GPL");
