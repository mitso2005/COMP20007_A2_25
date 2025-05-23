#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_KEY_LEN 128

/* This function will hash a key into a table of a given size, and will do this hashNum times. 
It will store the results in the array 'hashes' */
unsigned int uh1(const char *key, unsigned int size, int hashNum, unsigned int* hashes);

