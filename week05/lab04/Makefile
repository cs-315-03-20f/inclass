PROG = lab04
OBJS = scan.o parse.o eval.o ntcalc.o conv.o

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c ntcalc.h
	gcc ${CFLAGS} -c -o $@ $<

${PROG} : ${OBJS}
	gcc ${CFLAGS} -o $@ ${OBJS}

clean :
	rm -rf ${PROG} ${OBJS} *~ *.dSYM

