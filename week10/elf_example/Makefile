PROGS = count_main elf_main
OBJS_COUNT = count_main.o count_s.o
OBJS_ELF = elf_main.o
OBJS = $(OBJS_COUNT) $(OBJS_ELF)

ELF = elf/elf.a

CFLAGS = -g

# Pattern rules to avoid explicit rules
%.o : %.c
	gcc ${CFLAGS} -c -o $@ $<

%.o : %.s
	as -o $@ $<

all : ${PROGS}

$(ELF):
	make -C elf

count_main : $(OBJS_COUNT)
	gcc ${CFLAGS} -o $@ $(OBJS_COUNT)

elf_main : $(OBJS_ELF) $(ELF)
	gcc ${CFLAGS} -o $@ $(OBJS_ELF) $(ELF)

count_elf: ${PROGS}
	./elf_main
	gcc -o count_main count_main.c count_s.o

clean :
	make -C elf clean
	rm -rf ${PROGS} ${OBJS} *~ *.dSYM *.o *.hex project04
