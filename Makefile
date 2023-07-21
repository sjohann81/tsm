CC = gcc
CFLAGS = -Wall -O2

all: assemble tsm

tsm: tsm.o
	$(CC) $(CFLAGS) -o tsm tsm.o

tsm.o: tsm.c
	$(CC) $(CFLAGS) -c tsm.c
	
assemble: operand.o symbol.o assemble.o
	$(CC) $(CFLAGS) -o assemble operand.o symbol.o assemble.o
	
assemble.o: assemble.c
	$(CC) $(CFLAGS) -c assemble.c
	
symbol.o: symbol.c
	$(CC) $(CFLAGS) -c symbol.c
	
operand.o: operand.c
	$(CC) $(CFLAGS) -c operand.c

clean:
	rm -f *.o tsm assemble objects/*.tsm
