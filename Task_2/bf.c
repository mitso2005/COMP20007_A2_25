/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by YOUR NAME HERE.
 */

#include <assert.h>
#include <string.h>

#include "bit.h"
#include "hash.h"
#include "utils.h"
#include "birds.h"

struct bloomFilter {
    unsigned int* arr;
    unsigned int bfBits;
    double fp_rate;
    int numBirds;
};

/* The main function of this file */
int standardBF(char *datafile, char *testfile) {
    unsigned int hashNum = NUM_HASHES; 
    bf* birds;
    birds = (bf*) malloc(sizeof(bf));
    printf("\t ...Reading... \n");
    birdReadBF(birds, datafile, &hashNum);
    printf("\t ...Checking... \n");
    birdCheckBF(birds, testfile, hashNum);

    // free allocated memory
    uh1(NULL, 0, hashNum, NULL);
    free(birds->arr);
    free(birds);
    return 0;
}

/* This function adds an element to the bloom filter */
void addBF(bf* birds, char* nextName, unsigned int* hashNum) {
    // FILL-IN
}

 /* This function checks if a bird with name “nextName” is in the bloom filter */
int checkBF(bf* birds, char* nextName, unsigned int hashNum) {
    // FILL-IN
}

/* This function reads a list of birds from the file “fname”        
 * and prints out if each of the birds is in the bloom filter */
void birdCheckBF(bf* birds, char* fname, unsigned int hashNum){
    // FILL-IN
}

/* This function reads birds in and adds them to the bloom filter. 
   This is given to you for the standard Bloom Filter. */
void birdReadBF(bf* birds, char* fname, unsigned int* hashNum){
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    // First line comprises of number of birds, false positive rate
    assert(fscanf(inFile, "%d %lf\n", &birds->numBirds, &birds->fp_rate) == 2);

    // calculate the number of bits we need for this number of birds
    birds->bfBits = calc_m(birds->numBirds, birds->fp_rate);

    // debugging: 
    // printf("%d\n", birds->bfBits);

    // our bloom filter will have exactly this many bits
    birds->arr = (unsigned int*) malloc(birds->bfBits);
    assert(birds->arr);
    
    initBits(birds->arr, birds->bfBits);

    size_t bufsize = MAXBIRDNAME;
    char* nextName;
    nextName = (char *)malloc(bufsize * sizeof(char));
    assert(nextName);
    while (getline(&nextName, &bufsize, inFile) != -1) {
        nextName[strlen(nextName)-1] = '\0';
        //printf("%s\n", nextName);
        addBF(birds, nextName, hashNum);
        // debugging: 
        // printBF(birds);
    }
    fclose(inFile);
    free(nextName);
}

