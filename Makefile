KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
SRC := $(PWD)/src
OUT := $(PWD)/temp
BIN := $(PWD)/bin
APP := $(BIN)/led_control

KBUILD_ARTIFACTS := *.o *.mod.c *.mod *.ko *.symvers *.order

all:
	@mkdir -p $(OUT)
	@mkdir -p $(BIN)
	$(MAKE) -C $(KDIR) M=$(SRC) modules
	@mv -f $(addprefix $(SRC)/,$(KBUILD_ARTIFACTS)) $(OUT) 2>/dev/null || true
	gcc -o $(APP) $(SRC)/led_control.c

clean:
	$(MAKE) -C $(KDIR) M=$(SRC) clean
	@rm -rf $(OUT)/*
	@rm -f $(APP)
