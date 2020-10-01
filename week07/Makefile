PROGS = in_range sum_array count_zeros strlen fact

IN_RANGE_OBJS = in_range_main.o in_range_c.o in_range_s.o
SUM_ARRAY_OBJS = sum_array_main.o sum_array_c.o sum_array_s.o 
COUNT_ZEROS_OBJS = count_zeros_main.o count_zeros_c.o count_zeros_s.o
STRLEN_OBJS = strlen_main.o strlen_c.o strlen_s.o
FACT_OBJS = fact_main.o fact_c.o fact_s.o

OBJS = $(IN_RANGE_OBJS) $(SUM_ARRAY_OBJS) $(COUNT_ZEROS_OBJS) $(STRLEN_OBJS) $(FACT_OBJS)

%.o: %.c
	gcc -g -c -o $@ $<

%.o: %.s
	as -march=armv6 -g -o $@ $<

all: $(PROGS)

in_range: $(IN_RANGE_OBJS)
	gcc -o $@ $^ 

sum_array: $(SUM_ARRAY_OBJS)
	gcc -o $@ $^

count_zeros: $(COUNT_ZEROS_OBJS)
	gcc -o $@ $^

strlen: $(STRLEN_OBJS)
	gcc -o $@ $^

fact: $(FACT_OBJS)
	gcc -o $@ $^

clean:
	rm -rf $(OBJS) $(PROGS)
