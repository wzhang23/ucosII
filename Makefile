CC_DIR=/opt/FriendlyARM/toolschain/4.5.1/bin/arm-linux-
CC=$(CC_DIR)gcc
LD=$(CC_DIR)ld
NM=$(CC_DIR)nm
AR=$(CC_DIR)ar
OBJCOPY=$(CC_DIR)objcopy
OBJDUMP=$(CC_DIR)objdump

INCLUDE_DIR	:= $(shell pwd)/include
CFLAGS		:= -Wall -Os -fno-builtin -nostdinc -fno-builtin-printf -nostdlib -I$(INCLUDE_DIR) -mcpu=arm1176jzf-s

objs	:= startup/startup.o startup/clk.o startup/irq.o startup/sdram.o startup/nand.o startup/uart.o \
				 product/sched.o \
				 lib/ctype.o lib/div64.o lib/muldi3.o lib/printf.o lib/string.o lib/vsprintf.o \
				 ucosII/os_cpu_a.o ucosII/os_cpu_c.o ucosII/os_core.o ucosII/os_task.o ucosII/os_flag.o ucosII/os_mbox.o \
				 ucosII/os_mem.o ucosII/os_mutex.o ucosII/os_q.o ucosII/os_time.o ucosII/os_sem.o \
				 hmi/drv/lcd01_drv.o hmi/rte/hmi_rte.o hmi/rte/font_8x8.o hmi/app/hmi.o \

exec/main.bin:$(objs)
	$(LD) -T main.lds -o exec/main.elf $^
	$(OBJCOPY) -O binary exec/main.elf $@
	$(OBJDUMP) -D exec/main.elf > exec/main.dis
	$(NM) -B --numeric-sort exec/main.elf > exec/main.map

%.o:%.S
	$(CC) $(CFLAGS) -c -o $@ $<
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f exec/* *.o product/*.o startup/*.o lib/*.o ucosII/*.o hmi/drv/*.o hmi/rte/*.o hmi/app/*.o
