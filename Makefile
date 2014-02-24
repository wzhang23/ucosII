CC_DIR=/opt/FriendlyARM/toolschain/4.5.1/bin/arm-linux-
CC=$(CC_DIR)gcc
CC_CMD=-Iinclude -Wall
LD=$(CC_DIR)ld
NM=$(CC_DIR)nm
AR=$(CC_DIR)ar
OBJCOPY=$(CC_DIR)objcopy
OBJDUMP=$(CC_DIR)objdump

INCLUDEDIR := $(shell pwd)/include
CFLAGS		:= -Wall -Os -fno-builtin-printf -mcpu=arm1176jzf-s
CPPFLAGS	:= -nostdinc -I$(INCLUDEDIR)

export CC AR LD NM OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

objs	:= startup.o sdram.o nand.o clk.o uart.o main.o irq.o lib/libc.a ucosII/ucosII.a

main.bin:$(objs)
	$(LD) -T main.lds -o main.elf $^
	$(OBJCOPY) -O binary main.elf $@
	$(OBJDUMP) -D main.elf > main.dis
	$(NM) -B --numeric-sort main.elf > main.map

.PHONY :	lib/lib.a
lib/libc.a:
	cd lib; make; cd ..

.PHONY :	ucosII/ucosII.a
ucosII/ucosII.a:
	cd ucosII; make; cd ..

%.o:%.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
%.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	make clean -C lib
	make clean -C ucosII
	rm -f *.o *.elf *.bin *.dis *.out *.map
