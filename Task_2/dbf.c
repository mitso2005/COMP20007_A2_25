/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "bit.h"
#include "hash.h"
#include "utils.h"
#include "birds.h"

int cbfCount(struct bloomFilter* birds, char* nextName, unsigned int hashNum);

// Full definition of struct bloomFilter (needed for bf* usage)
struct bloomFilter {
    unsigned int* arr;
    unsigned int bfBits;
    double fp_rate;
    int numBirds; // Needed for filter capacity tracking
};

// Dynamic Bloom Filter Node: each is a counting bloom filter + tracking
struct dynamicBFNode {
    bf* filter;                    // Counting Bloom filter (reuse from cbf.c)
    int currentBirds;              // Number of birds in this filter
    int maxCapacity;               // Capacity of this filter
    char** birdNames;              // Array of pointers to bird names (O(s) tracking)
    struct dynamicBFNode* next;
    int bird_count;               // Track number of birds in this filter
    char* first_bird;            // First bird in sorted order in this filter
    char* last_bird;             // Last bird in sorted order in this filter
};

struct dynamicBF {
    double fp_rate;
    int maxBirds;
    struct dynamicBFNode *head;
};

typedef struct dynamicBFNode dbfNode;

// Helper: create a new counting bloom filter node
static dbfNode* createNewNode(int capacity, double fp_rate) {
    dbfNode* node = malloc(sizeof(dbfNode));
    assert(node);
    
    // Initialize filter
    node->filter = malloc(sizeof(bf));
    node->filter->bfBits = calc_m(capacity, fp_rate) * BUCKET_SIZE;
    node->filter->fp_rate = fp_rate;
    node->filter->numBirds = 0;
    unsigned int numInts = (node->filter->bfBits + 31) / 32;
    node->filter->arr = calloc(numInts, sizeof(unsigned int));
    
    // Initialize node fields
    node->currentBirds = 0;
    node->maxCapacity = capacity;
    node->birdNames = malloc(capacity * sizeof(char*));
    node->next = NULL;

    // Initialize tracking fields
    node->bird_count = 0;
    node->first_bird = NULL;
    node->last_bird = NULL;

    // Initialize the bit array properly
    initBits(node->filter->arr, node->filter->bfBits);
    
    return node;
}

// Helper: find the node containing a bird (O(s))
static dbfNode* findBirdNode(dbf* birds, const char* name) {
    dbfNode* node = birds->head;
    while (node) {
        for (int i = 0; i < node->currentBirds; i++) {
            if (strcmp(node->birdNames[i], name) == 0) {
                return node;
            }
        }
        node = node->next;
    }
    return NULL;
}

int dynamicBF(char *datafile, char *testfile, char *deletefile) {
    unsigned int hashNum = NUM_HASHES; 
    dbf* birds = (dbf *) malloc(sizeof(dbf));
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
    // Free all memory
    dbfNode* node = birds->head;
    while (node) {
        dbfNode* next = node->next;
        for (int i = 0; i < node->currentBirds; i++) {
            free(node->birdNames[i]);
        }
        free(node->birdNames);
        free(node->filter->arr);
        free(node->filter);
        free(node);
        node = next;
    }
    free(birds);
    return 0;
}

// add an item to a specific bloom filter in the DBF
int addDBF(bf* birds_bf, char* nextName, unsigned int* hashNum) {
    dbf* birds = (dbf*)birds_bf;
    if (!birds->head) {
        birds->head = createNewNode(birds->maxBirds, birds->fp_rate);
    }

    // Check if bird already exists in any filter
    if (findBirdNode(birds, nextName)) {
        return 0;  // Bird already exists, no need to add again
    }

    // Get the last filter
    dbfNode* node = birds->head;
    while (node->next) {
        node = node->next;
    }

    // If current filter is full, create new one
    if (node->currentBirds >= node->maxCapacity) {
        node->next = createNewNode(birds->maxBirds, birds->fp_rate);
        node = node->next;
    }

    // Try to add to current filter
    if (addCBF(node->filter, nextName, hashNum)) {
        return 1;  // Overflow occurred
    }

    // Add to tracking array
    node->birdNames[node->currentBirds] = strdup(nextName);
    node->currentBirds++;
    node->filter->numBirds++;
    return 0;
}

// delete an item from a specific bloom filter in the DBF
int birdDeleteDBF(bf* birds_bf, char* nextName, unsigned int* hashNum) {
    dbf* birds = (dbf*)birds_bf;
    dbfNode* node = findBirdNode(birds, nextName);
    if (!node) return 1; // Not in any filter
    int result = birdDeleteCBF(node->filter, nextName, hashNum);
    if (result != 1) {
        // Remove from birdNames array
        for (int i = 0; i < node->currentBirds; i++) {
            if (strcmp(node->birdNames[i], nextName) == 0) {
                free(node->birdNames[i]);
                for (int j = i; j < node->currentBirds - 1; j++)
                    node->birdNames[j] = node->birdNames[j+1];
                node->currentBirds--;
                node->filter->numBirds--;
                break;
            }
        }
    }
    return result;
}

// Count how many times a bird has been seen in the DBF
int dbfCount(dbf* birds, char* nextName, unsigned int hashNum) {
    // First find which filter contains this bird
    dbfNode* node = findBirdNode(birds, nextName);
    if (!node) {
        return 0;  // Bird not found in any filter
    }

    // Only count in the filter where the bird is actually stored
    unsigned int hashes[hashNum];
    uh1(nextName, node->filter->bfBits / BUCKET_SIZE, hashNum, hashes);
    int min_count = (1 << BUCKET_SIZE);

    for (int i = 0; i < hashNum; i++) {
        int count = countBucket(node->filter->arr, hashes[i]);
        if (count < min_count) {
            min_count = count;
            if (min_count == 0) break;
        }
    }
    return min_count;
}

// Check if a bird is in a specific Bloom Filter
int checkDBF(bf* birds_bf, char* nextName, unsigned int hashNum) {
    dbf* birds = (dbf*)birds_bf;
    return dbfCount(birds, nextName, hashNum) > 0;
}

// Check if a list of birds is in the DBF
void birdCheckDBF(dbf* birds, char* fname, unsigned int hashNum) {
    FILE *inFile = fopen(fname, "r");
    assert(inFile);
    char nextName[MAXBIRDNAME];
    while (fgets(nextName, MAXBIRDNAME, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') nextName[len-1] = '\0';
        int count = dbfCount(birds, nextName, hashNum);
        if (count > 0)
            printf("%-30s : Probably %d in the list\n", nextName, count);
        else
            printf("%-30s : Definitely not in the list\n", nextName);
    }
    fclose(inFile);
}

// Read in the birds and add them to the DBF
void birdReadDBF(dbf* birds, char* fname, unsigned int* hashNum) {
    FILE *inFile = fopen(fname, "r");
    assert(inFile);

    assert(fscanf(inFile, "%d %lf\n", &birds->maxBirds, &birds->fp_rate) == 2);

    // Initialize first filter
    dbfNode* head = createNewNode(birds->maxBirds, birds->fp_rate);
    head->first_bird = NULL;
    head->last_bird = NULL;
    head->bird_count = 0;
    birds->head = head;
    
    char nextName[MAXBIRDNAME];
    char* prev_name = NULL;
    
    while (fgets(nextName, MAXBIRDNAME, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') nextName[len-1] = '\0';

        dbfNode* curr = birds->head;
        while (curr->next) curr = curr->next;

        // Set first bird name if this is first insertion
        if (curr->bird_count == 0 && !curr->first_bird) {
            curr->first_bird = strdup(nextName);
        }

        // Handle filter transitions
        if (curr->bird_count >= birds->maxBirds) {
            curr->last_bird = prev_name ? strdup(prev_name) : NULL;
            curr->next = createNewNode(birds->maxBirds, birds->fp_rate);
            curr = curr->next;
            curr->first_bird = strdup(nextName);
        }

        if (addDBF((bf*)birds, nextName, hashNum)) {
            // Handle overflow
            if (prev_name) {
                curr->last_bird = strdup(prev_name);
                curr->next = createNewNode(birds->maxBirds, birds->fp_rate);
                curr = curr->next;
                curr->first_bird = strdup(nextName);
                addDBF((bf*)birds, nextName, hashNum);
            }
        }
        
        free(prev_name);
        prev_name = strdup(nextName);
        curr->bird_count++;
    }

    free(prev_name);
    fclose(inFile);
}

// this function finds the *first* BF the bird is in and deletes it. 
void deleteBirdsDBF(dbf *birds, char *deletefile, unsigned int hashNum) {
    FILE *inFile = fopen(deletefile, "r");
    assert(inFile);
    char nextName[MAXBIRDNAME];
    while (fgets(nextName, MAXBIRDNAME, inFile) != NULL) {
        size_t len = strlen(nextName);
        if (len > 0 && nextName[len-1] == '\n') nextName[len-1] = '\0';
        int result = birdDeleteDBF((bf*)birds, nextName, &hashNum);
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
    fclose(inFile);
}

