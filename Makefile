obj-m := LED_Driver.o
LED_Driver-objs := src/LED_Driver_main.o src/kernel_module.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
OUT := $(PWD)/temp

all:
	@mkdir -p $(OUT)
	$(MAKE) -C $(KDIR) M=$(PWD) O=$(OUT) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) O=$(OUT) clean
	@rm -rf $(OUT)
