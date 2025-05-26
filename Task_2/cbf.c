/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */

#include "bit.h"
#include "hash.h"
#include "utils.h"
#include "birds.h"

int cbfCount(bf* birds, char* name, unsigned int hashNum);

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

    // Clean up properly
    uh1(NULL, 0, hashNum, NULL);
    if (birds->arr) {
        free(birds->arr);
    }
    free(birds);
    
    return 0;
}

/* This function adds an element to the CBF.
 * Should return 1 on error (i.e. an overflow occuring) and 0 otherwise. */
int addCBF(bf* birds, char* nextName, unsigned int* hashNum) {
    unsigned int hashes[NUM_HASHES];
    unsigned int k = uh1(nextName, birds->bfBits/BUCKET_SIZE, *hashNum, hashes);
    
    // Check for overflow before incrementing
    for (unsigned int i = 0; i < k; i++) {
        if (countBucket(birds->arr, hashes[i]) >= 15) {
            return 1; // Would overflow
        }
    }
    
    // Safe to increment all buckets
    for (unsigned int i = 0; i < k; i++) {
        addBits(birds->arr, hashes[i]);
    }
    return 0;
}

/* This function deletes an element from the CBF 
 * Return 1 if the bird is definitely not in the Bloom Filter and cannot be deleted. 
 * Otherwise return 0 */
int birdDeleteCBF(bf* birds, char* nextName, unsigned int* hashNum) {
    unsigned int hashes[NUM_HASHES];
    unsigned int k = uh1(nextName, birds->bfBits/BUCKET_SIZE, *hashNum, hashes);
    
    // Check if bird exists first
    if (cbfCount(birds, nextName, *hashNum) == 0) {
        return 1;  // Bird definitely not in list
    }
    
    // Decrement all buckets
    for (unsigned int i = 0; i < k; i++) {
        subtractBits(birds->arr, hashes[i]);
    }
    
    // Check if bird is still possibly in the list after deletion
    if (cbfCount(birds, nextName, *hashNum) > 0) {
        return 2;  // Bird was deleted but still possibly in list
    }
    return 0;  // Successfully deleted and definitely not in list
}

// Count how many times a bird has probably been seen before.
int cbfCount(bf* birds, char* nextName, unsigned int hashNum) {
    unsigned int hashes[NUM_HASHES];
    unsigned int k = uh1(nextName, birds->bfBits/BUCKET_SIZE, hashNum, hashes);
    
    // Find minimum count among all buckets
    int minCount = 15;
    for (unsigned int i = 0; i < k; i++) {
        int count = countBucket(birds->arr, hashes[i]);
        if (count < minCount) minCount = count;
    }
    return minCount;
}


// Read in the birds to the CBF
void birdReadCBF(bf* birds, char* fname, unsigned int* hashNum) {
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    // First line: number of birds and false positive rate
    assert(fscanf(inFile, "%d %lf\n", &birds->numBirds, &birds->fp_rate) == 2);

    // Calculate bits needed and multiply by bucket size for 4-bit counters
    birds->bfBits = calc_m(birds->numBirds, birds->fp_rate) * BUCKET_SIZE;

    // Allocate and initialize array
    unsigned int numInts = (birds->bfBits + 31) / 32;
    birds->arr = (unsigned int*)malloc(numInts * sizeof(unsigned int));
    assert(birds->arr);
    initBits(birds->arr, birds->bfBits);

    // Read and add birds using fgets instead of getline
    char nextName[MAXBIRDNAME];
    while (fgets(nextName, MAXBIRDNAME, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') {
            nextName[len-1] = '\0';
        }
        if (addCBF(birds, nextName, hashNum)) {
            printf("Overflow occurred.\n");
            break;
        }
    }
    fclose(inFile);
}

// Check if a bird is in the CBF
int checkCBF(bf* birds, char* nextName, unsigned int hashNum) {
    return cbfCount(birds, nextName, hashNum) > 0;
}


// Check if a list of birds is in the CBF
void birdCheckCBF(bf* birds, char* fname, unsigned int hashNum){
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    size_t bufsize = MAXBIRDNAME;
    char* nextName = (char*)malloc(bufsize * sizeof(char));
    assert(nextName);

    while (fgets(nextName, (int)bufsize, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') {
            nextName[len-1] = '\0';
        }
        
        int count = cbfCount(birds, nextName, hashNum);
        if (count > 0) {
            printf("%-30s : Probably %d in the list\n", nextName, count);
        } else {
            printf("%-30s : Definitely not in the list\n", nextName);
        }
    }
    free(nextName);
    fclose(inFile);
}


// this function reads in a list of birds to delete and calls the relevant function to 
// delete one at a time from the CBF. 
void deleteBirdsCBF(bf *birds, char *deletefile, unsigned int hashNum) {
    FILE *inFile = fopen(deletefile, "r");
    assert(inFile);

    size_t bufsize = MAXBIRDNAME;
    char* nextName = (char*)malloc(bufsize * sizeof(char));
    assert(nextName);

    while (fgets(nextName, (int)bufsize, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') {
            nextName[len-1] = '\0';
        }
        
        int result = birdDeleteCBF(birds, nextName, &hashNum);
        switch(result) {
            case 0:
                printf("%-30s : Deleted, and now definitely not in the list\n", nextName);
                break;
            case 1:
                printf("%-30s : ERROR - Trying to delete an item definitely not in the list\n", nextName);
                break;
            case 2:
                printf("%-30s : Deleted, but still possibly in the list\n", nextName);
                break;
        }
    }
    free(nextName);
    fclose(inFile);
}
