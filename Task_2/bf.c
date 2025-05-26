/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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
    bf* birds = malloc(sizeof(bf));
    assert(birds);

    printf("\t ...Reading... \n");
    birdReadBF(birds, datafile, &hashNum);

    printf("\t ...Checking... \n");
    birdCheckBF(birds, testfile, hashNum);
    
    // Clean up properly
    uh1(NULL, 0, hashNum, NULL);  // Clean up hash function resources
    if (birds->arr) {
        free(birds->arr);
    }
    free(birds);

    return 0;
}

/* This function adds an element to the bloom filter */
void addBF(bf* birds, char* nextName, unsigned int* hashNum) {
    unsigned int hashes[NUM_HASHES];
    uh1(nextName, birds->bfBits, *hashNum, hashes);
    for (unsigned int i = 0; i < *hashNum; i++) {
        bitOn(birds->arr, hashes[i]);
    }
}

int checkBF(bf* birds, char* nextName, unsigned int hashNum) {
    unsigned int hashes[NUM_HASHES];
    uh1(nextName, birds->bfBits, hashNum, hashes);
    for (unsigned int i = 0; i < hashNum; i++) {
        if (!checkBit(birds->arr, hashes[i])) {
            return 0;
        }
    }
    return 1;
}

void birdCheckBF(bf* birds, char* fname, unsigned int hashNum){
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    size_t bufsize = MAXBIRDNAME;
    char* nextName = malloc(bufsize * sizeof(char));
    assert(nextName);

    while (fgets(nextName, (int)bufsize, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') {
            nextName[len-1] = '\0';
        }
        int result = checkBF(birds, nextName, hashNum);
        printf("%-30s : %s\n", nextName, result ? "Possibly in the list" : "Definitely not in the list");
    }

    free(nextName);
    fclose(inFile);
}

void birdReadBF(bf* birds, char* fname, unsigned int* hashNum){
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    assert(fscanf(inFile, "%d %lf\n", &birds->numBirds, &birds->fp_rate) == 2);

    birds->bfBits = calc_m(birds->numBirds, birds->fp_rate);

    // Calculate number of bits needed, then compute words needed
    unsigned int words = (birds->bfBits + sizeof(unsigned int) * 8 - 1) / (sizeof(unsigned int) * 8);
    birds->arr = calloc(words, sizeof(unsigned int));  // safer: zero-initialized
    assert(birds->arr);

    char *nextName = NULL;
    size_t bufsize = 0;
    while (getline(&nextName, &bufsize, inFile) != -1) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') {
            nextName[len-1] = '\0';
        }
        addBF(birds, nextName, hashNum);
    }

    free(nextName);
    fclose(inFile);
}
