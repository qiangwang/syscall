MOD_NAME = syscall

obj-m := $(MOD_NAME).o

KERNELDIR := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.mod.c *.o *.symvers *.order .*.cmd .tmp_versions
ins:
	[ -d /var/log/syscall ] || sudo mkdir -p /var/log/syscall
	sudo insmod $(MOD_NAME).ko
rm:
	sudo rmmod $(MOD_NAME)
	make clean
ls:
	sudo lsmod | grep $(MOD_NAME) || echo 'not found'
msg:
	dmesg | tail
