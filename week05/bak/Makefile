PROG = lab04
OBJS = scan.o parse.o ntcalc.o eval.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<


all : ${PROG}

${PROG} : ntcalc.h ${OBJS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM

