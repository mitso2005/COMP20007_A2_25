# Makefile for the racecar module and testing program.
#
# Created for COMP20007 Design of Algorithms 2025
# Written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>


birds: bf.o cbf.o dbf.o hash.o bit.o utils.o birds.o
	gcc -Wall -o birds bf.o cbf.o dbf.o hash.o bit.o utils.o birds.o -lm -g

birds.o: birds.c birds.h
	gcc -Wall -c birds.c -g

hash.o: hash.c hash.h
	gcc -Wall -c hash.c -g

bf.o: bf.c birds.h
	gcc -Wall -c bf.c -g

cbf.o: cbf.c birds.h
	gcc -Wall -c cbf.c -g

dbf.o: dbf.c birds.h
	gcc -Wall -c dbf.c -g

bit.o: bit.c
	gcc -Wall -c bit.c -g

utils.o: utils.c utils.h bit.h
	gcc -Wall -c utils.c -g

# The following rule doesn't create any files, but rather helps us clean up
# our working environment by deleting the files which result from the
# compilation of this program.
#
# Since nothing is created during this rule, we have to mark it as "phony",
# i.e., it runs the instructions but make doesn't need to expect for there
# to be a file named clean after the rule is run.

.PHONY: clean

clean:
	rm *.o birds
