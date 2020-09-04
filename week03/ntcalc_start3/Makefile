PROGS = lab03 
OBJS = scan.o parse.o ntcalc.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<


all : ${PROGS}

lab03 : ntcalc.h $(OBJS)
	gcc ${CFLAGS} -o $@ $(OBJS)

clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM

