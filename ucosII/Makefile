objs := os_core.o os_cpu_a.o os_cpu_c.o os_flag.o os_mbox.o os_mutex.o os_mem.o os_q.o os_task.o os_time.o os_sem.o div64.o

ucosII.a: $(objs)
	${AR} -r -o $@ $^
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f ucosII.a *.o		
