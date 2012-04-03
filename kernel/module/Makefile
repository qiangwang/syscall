MOD_NAME = syscall

obj-m := $(MOD_NAME).o

KERNELDIR := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.mod.c *.o *.symvers *.order .*.cmd
ins:
	sudo insmod $(MOD_NAME).ko
rm:
	sudo rmmod $(MOD_NAME)
ls:
	sudo lsmod | grep $(MOD_NAME) || echo 'not found'
msg:
	dmesg | tail
