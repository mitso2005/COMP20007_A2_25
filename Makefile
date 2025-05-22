CC = gcc
CFLAGS = -Wall -g

all: eel

eel: eel.c utils.c
	$(CC) $(CFLAGS) -o eel eel.c utils.c

clean:
	rm -f eel

