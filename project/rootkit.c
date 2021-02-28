#include <linux/module.h>
#include <linux/kernel.h> // Debug Messages like KERN_INFO
#include <linux/init.h> //gives us access to macros
#include <linux/moduleparam.h> //gives us access to the parameter functions 
#include <linux/stat.h> 

MODULE_LICENSE("GPL"); //Prevents no license warning upon compilation

#define DRIVER_AUTHOR "RJ and Group 3"
#define DRIVER_DESC "Hello World Driver"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice") //devices are anything thats mapped or located to dev. When you have hardware that says something like /dev/sda etc

static char *MyString = ""; //We want to have a driver where we can pass an argument and it will echo that argument. MUST have pointer
module_param(MyString, charp, 0000); //Takes in parameter for the function module_param, takes in the type of parameter of character pointer, then specifies the permissions of 0
MODULE_PARM_DESC(MyString, "This is a string that gets echoed"); //Speify the string

static int HelloInit(void) { 
	
	printk(KERN_INFO "ROOTKITDEV_DEBUG: %s \n", MyString); //KERN_INFO is the level of msg we are sending (DEBUG message), lvl of severity, like KERNEL_WARN etc
                                                               //Will print when the driver is successfully loaded into memory. Use %s since we are printing a character char
	return 0; //return 0 upon success
}

static void HelloExit(void) { 
   printk(KERN_INFO "ROOTKIT_DEBUG: GOODBYE WORLD \n"); 
}

//Calls the functions 
module_init(HelloInit);
module_exit(HelloExit);
