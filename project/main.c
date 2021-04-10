#include "functs.h" //Call in our function prototypes 

MODULE_LICENSE("GPL"); //Prevents no license warning upon compilation

#define DRIVER_AUTHOR "RJ and Group 3"
#define DRIVER_DESC "Hello World Driver"
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);

MODULE_SUPPORTED_DEVICE("testdevice") //devices are anything thats mapped or located to dev. When you have hardware that says something like /dev/sda etc

int Major; //Device number that the driver device will talk too
static int Device_Open = 0; //We will use this to check if the device is open or not. Will be either 1 or 0 so if its open we can set it to close when we are done
static char msg[BUF_Len]; 
static char *msg_Ptr;

static struct file_operations fops = {
	//declare variables to the functions we defined in functs.h so we can give them values
	.read = device_read,
	.write = device_write,
	.open = device_open,
        .release = device_release
};


int init_module(void) { //check if a device has been registered properly and print if its successful or not. Tells how to create a device to talk to our driver

	Major = register_chrdev(0, DEVICE_NAME, &fops);

	if(Major < 0) { //If failed to load the driver print the below 
		printk(KERN_ALERT "I have failed to load!\n");
		return Major;
	}
        //If does not fail just continue 
	printk(KERN_ALERT "I was assigned a major number %d", Major);
	printk(KERN_ALERT "Please create a device with name \n mknod /dev/%s c %d 0", DEVICE_NAME, Major); //When we create our device and try to interact with it, the driver will wait for input for a read/write operation. mknod is how you create a device. It will grab our device name of root_kit
	return 0;
}

//Open Driver Function
int device_open(struct inode * inode, struct file *file) {
	static int counter = 0;
	if(Device_Open) { //if the device is open return that the device is busy
		return -EBUSY;
	}

	//Copy a message into a buffer that will be printed to the screen
	sprintf(msg, "I was opened %d times", counter++);
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);
	return 0;
}

int device_release(struct inode * inode, struct file *file) { //ensures when device is done reading then it will release the device so we can use it again. Similar to close() 
	Device_Open--; //Make it ready to the user next caller
	module_put(THIS_MODULE);
	return 0;
}

ssize_t device_read(struct file * file, char * buffer, size_t length, loff_t *offset) {
	int bytes_read = 0;
	if(*msg_Ptr == 0) { //if the message is nothing, do nothing and return nothing
		return 0;
	}

	while(length && *msg_Ptr) {
		put_user(* (msg_Ptr++), buffer++ );
		length--;
		bytes_read++;
	}

	return bytes_read;

}

ssize_t device_write(struct file * file, const char * buffer, size_t length, loff_t *offset) {
	printk(KERN_ALERT "I don nothing!\n");
	return 0;
}