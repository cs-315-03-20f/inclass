# Sample makefile. Remember to edit with hard tabs, not spaces

# name of our output program
PROG = scan3

# intermediate object files
OBJS = scan3.o

# C compiler name
CC = gcc

# flags for the C compiler. -g = debug symbols. -c = compile C source
CFLAGS = -c -g

# object (.o) files depend on the .c prerequisites
# the recipe compiles the current target ($@) from the current predicate ($<)
%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# the executable program depends on the .o prerequisites
# the recipe links the current target ($@) from the list of prerequisites ($^)
$(PROG): $(OBJS)
	$(CC) -o $@ $^

# "make clean" runs the recipe below to delete all build products
clean:
	rm -rf $(PROG) $(OBJS)
