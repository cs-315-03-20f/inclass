PROGS = lab04
OBJS = scan.o parse.o eval.o ntcalc.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

all : ${PROGS}

lab04 : $(OBJS)
	gcc ${CFLAGS} -o $@ $(OBJS)

clean :
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM

