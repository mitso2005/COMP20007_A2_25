/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 */

#include "hash.h"

#define INITIAL_SIZE 5

/* This function will hash a key into a table of a given size, and will do this hashNum times. 
It will store the results in the array 'hashes' */
// random-array based universal hash function
// uses a static flag to initialise the random array the first time the function
// is called, and uses the same array afterwards
// assumes strlen(key) <= MAX_KEY_LEN = 128
// uh = universal hash
// key = key to be hashed
// size = size of hash table
// hashNum = desired number of hashings (1 or more)
// hashes = array where hash values will be stored - these values may not be unique. 
// output: the number of times we hashed (ideally, this is the same as hashNum).
unsigned int uh1(const char *key, unsigned int size, int hashNum, unsigned int* hashes) {
	static int initialisedFunctions = 0;
	static int **r = NULL;
	if (size == 0) {
		for (int i =0; i<hashNum; i++) {
			free(r[i]);
		}
		free(r);
		return 0;
	} 
	if (hashNum > initialisedFunctions) {
		r = realloc(r, (hashNum)*(sizeof *r));
		assert(r);
        FILE* inFile = fopen("auxillary_data/randomNumbers.txt", "r");
		for (int i =initialisedFunctions; i<hashNum; i++) {
			//srand(i*(MAX_KEY_LEN+1));
			r[i] = malloc(MAX_KEY_LEN * (sizeof *(r[i])));
			assert(r[i]);
			for (int j = 0; j < MAX_KEY_LEN; j++) {
				// normally, this would use rand, but here we have provided the 
				// random numbers for you in a file for consistency
				// r[i][j] = rand();
				fscanf(inFile, "%d", &(r[i][j]));
				//fprintf(inFile, "%d ", r[i][j]);
				
			}
			//fprintf(inFile, "\n");
		}
		initialisedFunctions = hashNum;
		fclose(inFile);
	}

	//unsigned int hashes[hashNum];
	for (int j=0; j<initialisedFunctions; j++) {
		unsigned int h = 0;
		for (int i = 0; key[i] != '\0'; i++) {
			h = h + r[j][i] * key[i];
		}
		//printf("%u ", h);
		hashes[j]=h%size;
	}
	return initialisedFunctions;
}

