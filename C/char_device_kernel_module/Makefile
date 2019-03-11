obj-m    := chardevso1.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc codec_mod_test.c -o test_char_device -Wall -O3 -I.

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f test_char_device
	rm -f SO1codec_char_dev
