CC = gcc
CFLAGS = -Wall -g

all: eel.exe

eel.exe: eel.c utils.c
	$(CC) $(CFLAGS) -o eel.exe eel.c utils.c

clean:
	rm -f eel.exe

