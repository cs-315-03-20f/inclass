PROGS = first_c first_s add_main max_main hello_c hello_s  
OBJS = first_c.o first_s.o hello_c.o hello_s.o\
       add_c.o add_s.o max_c.o max_s.o 

CFLAGS = -g

# Pattern rules to avoid explicit rules
%_c.o : %_c.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as ${CFLAGS} -o $@ $<

all : ${PROGS}

first_s : first_s.o
	gcc ${CFLAGS} -o $@ $<

hello_s : hello_s.o
	gcc ${CFLAGS} -o $@ $<

add_main : add_main.c add_c.o add_s.o
	gcc ${CFLAGS} -o $@ $^

max_main : max_main.c max_c.o max_s.o
	gcc ${CFLAGS} -o $@ $^
	
clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM
	
