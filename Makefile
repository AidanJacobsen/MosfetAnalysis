PROJECT_NAME = program

WARNING = -Wall -Wshadow -Wno-unused-function --pedantic -Wno-unused-variable -Wno-error=div-by-zero
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(TESTFLAGS) $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

SRCS = main.c networkGeneration.c analysis.c 
OBJS = $(SRCS:%.c=%.o)

$(PROJECT_NAME): $(OBJS)
	$(GCC) $(OBJS) -o $(PROJECT_NAME)

.c.o:
	$(GCC) -c $*.c

testall: test1

testmemory: $(PROJECT_NAME)
	$(VAL) ./$(PROJECT_NAME) inputs/test6in inputs/test6post output6

test1: $(PROJECT_NAME)
	./$(PROJECT_NAME)

clean: # remove all machine generated files
	rm -f $(PROJECT_NAME) *.o output??? output?? output? *~ memcheck.txt
