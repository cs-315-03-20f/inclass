PROG = mc
OBJS = add_s.o mc.o

%.o: %.c
	gcc -c -g -o $@ $<

%.o: %.s
	as -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $(PROG) $(OBJS)

clean:
	rm -rf $(PROG) $(OBJS)
