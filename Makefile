CC = gcc
CFLAGS = -Wall -O2

all: tsm

tsm: tsm.o
	$(CC) $(CFLAGS) -o tsm tsm.o

tsm.o: tsm.c
	$(CC) $(CFLAGS) -c tsm.c

clean:
	rm -f *.o tsm
