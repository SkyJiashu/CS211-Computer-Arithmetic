CC = gcc

CCFLAGS = -Wall

all: calc format

calc: calc.o
	$(CC) $(CCFLAGS) -o calc calc.o

calc.o: calc.c calc.h
	$(CC) $(CCFLAGS) -c calc.c

format: format.o
	$(CC) $(CCFLAGS) -o format format.o

format.o: format.c format.h
	$(CC) $(CCFLAGS) -c format.c

clean:
	rm -f calc calc.o format format.o

