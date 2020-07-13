ifneq ($(KERNELRELEASE),)
obj-m := gettcp.o
else
KERNELBUILD :=/lib/modules/$(shell uname -r)/build
PWD :=$(shell pwd)
all:
	make -C $(KERNELBUILD) M=$(PWD) modules
clean:
	rm -rf *.o *.ko.unsigned *.mod.c .*.cmd *.markers *.order *.symvers .tmp_versions
endif
