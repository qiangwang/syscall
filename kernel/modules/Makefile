obj-m := syscall/ check/

KERNELDIR := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELDIR) M=$(PWD) modules
