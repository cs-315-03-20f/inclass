PROGS = in_range sum_array
OBJS = in_range_main.o in_range_c.o in_range_s.o \
	sum_array_main.o sum_array_c.o sum_array_s.o

%.o: %.c
	gcc -g -c -o $@ $<

%.o: %.s
	as -g -o $@ $<

all: $(PROGS)

in_range: $(OBJS)
	gcc -o $@ in_range_main.o in_range_c.o in_range_s.o 

sum_array: $(OBJS)
	gcc -o $@ sum_array_main.o sum_array_c.o sum_array_s.o

clean:
	rm -rf $(OBJS) $(PROGS)
