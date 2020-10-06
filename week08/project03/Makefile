PROG = week08

OBJS = week08.o strcat_c.o strcat_s.o sum_array_rec_c.o sum_array_rec_s.o

%.o: %.c
	gcc -c -g -o $@ $<

%.o: %.s
	as -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $(PROG) $(OBJS)

clean:
	rm -rf $(PROG) $(OBJS)
