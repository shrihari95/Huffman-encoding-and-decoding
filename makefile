CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -Wunreachable-code -Wuninitialized -Wcomment
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) # $(COVFLAGS) $(PROFFLAG)




pa15.o:  huffman.h 
	$(GCC) -c pa15.c

all : stack.o huffman.o pa15.o
	$(GCC) stack.o huffman.o pa15.o -o pa15	
  
stack.o: huffman.h
	$(GCC) -c stack.c huffman.c pa15.c

huffman.o: huffman.h
	$(GCC) -c stack.c huffman.c 

clean:
	/bin/rm -f *.o
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa15

