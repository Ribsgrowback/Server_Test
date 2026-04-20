CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
LDFLAGS = -lpthread

TARGETS = echoserveri echoclient
COMMON = csapp.o

all: $(TARGETS)

echoserveri: echoserveri.o echo.o $(COMMON)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

echoclient: echoclient.o $(COMMON)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c csapp.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean
