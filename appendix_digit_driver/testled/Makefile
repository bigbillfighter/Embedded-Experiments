CC:= /usr/local/toolchain/toolchain-4.5.1/bin/arm-linux-gcc
CFLAGS:= -Wall -O2 -c
LIBS:= 
OUT:=led_test
OUT1:=keyboard_test

.PHONY: clean

all: led_test keyboard_test

led_test.o : led_test.c
keyboard_test.o: keyboard_test.c
clean:
		rm *.o *_test

