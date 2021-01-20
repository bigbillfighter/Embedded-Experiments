ifeq ($(KERNELRELEASE),)
KERNELDIR ?= /home/linux/workdir/Fs6818/kernel/
CC = /home/linux/workdir/Fs6818/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi-gcc
PWD := $(shell pwd)

modules:
	$(MAKE) ARCH=arm CROSS_COMPILE=/home/linux/workdir/Fs6818/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi- -C $(KERNELDIR) M=$(PWD) modules

modules_install:
	$(MAKE) ARCH=arm CROSS_COMPILE=/home/linux/workdir/Fs6818/prebuilts/gcc/linux-x86/arm/arm-eabi-4.8/bin/arm-eabi- -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module* module* test

.PHONY: modules modules_install clean

else
    obj-m := fs6818_led.o
endif

