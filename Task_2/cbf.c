/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by YOUR NAME HERE.
 */

#include "bit.h"
#include "hash.h"
#include "utils.h"
#include "birds.h"

// Our counting Bloom Filter
struct bloomFilter {
    unsigned int* arr;
    unsigned int bfBits;
    double fp_rate;
    int numBirds;
};

/* The main function in this file */
int countingBF(char *datafile, char *testfile, char* deletefile) {
    unsigned int hashNum = NUM_HASHES; 
    bf* birds;
    birds = (bf*) malloc(sizeof(bf));
    printf("\t ...Reading... \n");
    birdReadCBF(birds, datafile, &hashNum);
    printf("\t ...Checking... \n");
    birdCheckCBF(birds, testfile, hashNum);
    printf("\t ...Deleting... \n");
    deleteBirdsCBF(birds, deletefile, hashNum);

    // free allocated memory
    uh1(NULL, 0, hashNum, NULL);
    free(birds->arr);
    free(birds);
    return 0;
}

/* This function adds an element to the CBF.
 * Should return 1 on error (i.e. an overflow occuring) and 0 otherwise. */
int addCBF(bf* birds, char* nextName, unsigned int* hashNum) {
    // FILL-IN
    return 0;
}

/* This function deletes an element from the CBF 
 * Return 1 if the bird is definitely not in the Bloom Filter and cannot be deleted. 
 * Otherwise return 0 */
int birdDeleteCBF(bf* birds, char* nextName, unsigned int* hashNum) {
    // FILL-IN

    return 0;
}

// Count how many times a bird has probably been seen before.
int cbfCount(bf* birds, char* nextName, unsigned int hashNum) {
    // FILL-IN
}


// Read in the birds to the CBF
void birdReadCBF(bf* birds, char* fname, unsigned int* hashNum){
    // FILL-IN
    // Note: Here the number of bits will be equal to the return value of the calc_m function multipled by the bucket size.
}

// Check if a bird is in the CBF
int checkCBF(bf* birds, char* nextName, unsigned int hashNum) {
    // FILL-IN
}

// Check if a list of birds is in the CBF
void birdCheckCBF(bf* birds, char* fname, unsigned int hashNum){
    // FILL-IN
}


// this function reads in a list of birds to delete and calls the relevant function to 
// delete one at a time from the CBF. 
void deleteBirdsCBF(bf *birds, char *deletefile, unsigned int hashNum) {
    // FILL-IN
}

