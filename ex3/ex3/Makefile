all: main Complex.o GenGroup tar
		MyGroupMain
CC = gcc

OBJECTS = Complex.o GenGroup MyGroupMain libgenGroup.a tar

CFLAGS = -Wextra -Wall -Wvla -std=c99

main: GenGroup.h Complex.h IntFunctions.c ComplexFunctions.c
	$(CC) $(NDEBUG) $(CFLAGS) GenGroup.c Complex.c MyGroupMain.c -g -o MyGroupMain

GenGroup.o: GenGroup.h GenGroup.c
	$(CC) $(NDEBUG) $(CFLAGS) -c GenGroup.c


GenGroup: libgenGroup.a
	ranlib libgenGroup.a

libgenGroup.a: GenGroup.o
	ar rcs libgenGroup.a GenGroup.o

Complex.o: Complex.c Complex.h
	$(CC) $(NDEBUG) $(CFLAGS) -c Complex.c

tar:
	tar cvf ex3.tar Makefile GenGroup.c GenGroup.h Complex.c Complex.h \
	MyGroupMain.c AddMultComplex.c AddMultIntegersZ6.c valdbg.out

clean:
	rm -rf *.o  $(OBJECTS) 
