eel: eel.o utils.o
	gcc -Wall -o eel -g eel.o utils.o

eel.o: eel.c utils.h
	gcc -c eel.c -Wall -g

utils.o: utils.c utils.h
	gcc -c utils.c -Wall -g

