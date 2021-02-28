#include <linux/module.h>
#include <linux/kernel.h> // Debug Messages like KERN_INFO
#include <linux/init.h> //gives us access to macros
#include <linux/moduleparam.h> //gives us access to the parameter functions 
#include <linux/stat.h>

static void HelloExit(void) {
   printk(KERN_INFO "ROOTKIT_DEBUG: GOODBYE WORLD \n");
}

//Calls the functions
module_exit(HelloExit);
