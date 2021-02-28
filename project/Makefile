obj-m += rootkit.o #Create the output file

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules #Creates all the required files we need. Allows us to use linux modules in init.h

clean: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean #Clean the modules
