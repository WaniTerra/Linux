
KDIR := /home/$(USER)/src/WSL2-Linux-Kernel

obj-m += my_driver.o

all:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean