ifeq ($(strip $(MODULE)),)
	obj-m += pa2_char_driver.o
else
	obj-m += $(MODULE).o
endif


KERNEL_SRC = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KERNEL_SRC) M=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean

test:
	gcc -Wall test_driver_implementation.c -o test_driver_implementation.o

cleantest:
	rm test_driver_implementation.o

runtest:
	./test_driver_implementation.o /dev/schrdev
