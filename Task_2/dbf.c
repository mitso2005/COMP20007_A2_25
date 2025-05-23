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
};

struct dynamicBFNode {
    // FILL-IN
};

struct dynamicBF {
    double fp_rate;
    int maxBirds;
    struct dynamicBFNode *head;
};

typedef struct dynamicBFNode dbfNode;

int dynamicBF(char *datafile, char *testfile, char *deletefile) {
    unsigned int hashNum = NUM_HASHES; 
    dbf* birds;
    birds = (dbf *) malloc(sizeof(dbf));
    assert(birds);
    birds->fp_rate = 0;
    birds->maxBirds = 0;
    birds->head = NULL;
    printf("\t ...Reading... \n");
    birdReadDBF(birds, datafile, &hashNum);
    printf("\t ...Checking... \n");
    birdCheckDBF(birds, testfile, hashNum);
    printf("\t ...Deleting... \n");
    deleteBirdsDBF(birds, deletefile, hashNum);


    // free allocated memory
    // FILL-IN

    return 0;
}

// add an item to a specific bloom filter in the DBF
int addDBF(bf* birds, char* nextName, unsigned int* hashNum) {
    // FILL-IN
    return 0;
}

// delete an item from a specific bloom filter in the DBF
int birdDeleteDBF(bf* birds, char* nextName, unsigned int* hashNum) {
    // FILL-IN

    return 0;
}

// Count how many times a bird has been seen in the DBF
int dbfCount(dbf* birds, char* nextName, unsigned int hashNum) {
    // FILL-IN
}

// Check if a bird is in a specific Bloom Filter
int checkDBF(bf* birds, char* nextName, unsigned int hashNum) {
    // FILL-IN
}

// Check if a list of birds is in the DBF
void birdCheckDBF(dbf* birds, char* fname, unsigned int hashNum){
    // FILL-IN
}

// Read in the birds and add them to the DBF
void birdReadDBF(dbf* birds, char* fname, unsigned int* hashNum){
    // FILL-IN
}

// this function finds the *first* BF the bird is in and deletes it. 
void deleteBirdsDBF(dbf *birds, char *deletefile, unsigned int hashNum) {
    // FILL-IN
}
