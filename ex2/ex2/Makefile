all: Board.o ErrorHandle.o PlayBoard
	PlayBoard

CC = gcc
CFLAGS = -Wextra -Wall -Wvla -std=c99

PlayBoard: PlayBoard.c Board.h 
	$(CC) $(NDEBUG) $(CFLAGS) PlayBoard.c ErrorHandle.c Board.c -g -o PlayBoard


Board.o: Board.h Board.c ErrorHandle.h
	$(CC) $(NDEBUG) $(CFLAGS) -g -c Board.c

ErrorHandle.o: ErrorHandle.c ErrorHandle.h
	$(CC) $(NDEBUG) $(CFLAGS) -c ErrorHandle.c

Gomoku: Gomoku.c Board.h
	$(CC) $(NDEBUG) $(CFLAGS) Gomoku.c ErrorHandle.c Board.c -g -o Gomoku

tar:
	tar cvf ex2.tar Makefile Gomoku.c Board.c valdbg.out extension.pdf
clean:
	rm -rf *.o PlayBoard Gomoku




