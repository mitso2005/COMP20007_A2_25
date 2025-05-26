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
    if (!node) return NULL;

    node->filter = malloc(sizeof(bf));
    if (!node->filter) {
        free(node);
        return NULL;
    }

    node->filter->bfBits = calc_m(capacity, fp_rate) * BUCKET_SIZE;
    node->filter->fp_rate = fp_rate;
    node->filter->numBirds = 0;
    
    unsigned int numInts = (node->filter->bfBits + 31) / 32;
    node->filter->arr = calloc(numInts, sizeof(unsigned int));
    if (!node->filter->arr) {
        free(node->filter);
        free(node);
        return NULL;
    }

    node->birdNames = malloc(capacity * sizeof(char*));
    if (!node->birdNames) {
        free(node->filter->arr);
        free(node->filter);
        free(node);
        return NULL;
    }

    node->currentBirds = 0;
    node->maxCapacity = capacity;
    node->next = NULL;
    node->first_bird = NULL;
    node->last_bird = NULL;
    node->bird_count = 0;

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

// Helper: free a single dbfNode
static void freeDBFNode(dbfNode* node) {
    if (!node) return;

    // Free all bird name strings in this node
    if (node->birdNames) {
        for (int i = 0; i < node->currentBirds; i++) {
            free(node->birdNames[i]);
        }
        free(node->birdNames);
    }

    // Free first and last bird if they exist
    free(node->first_bird);
    free(node->last_bird);

    // Free the Bloom filter
    if (node->filter) {
        if (node->filter->arr) {
            free(node->filter->arr);
        }
        free(node->filter);
    }

    // Finally, free the node itself
    free(node);
}

// Helper: free the entire DBF linked list
static void freeDBF(dbf* birds) {
    if (!birds) return;

    dbfNode* node = birds->head;
    while (node) {
        dbfNode* next = node->next;
        freeDBFNode(node);
        node = next;
    }

    // Free the main dbf structure itself
    free(birds);
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

    // Clean up hash function resources
    uh1(NULL, 0, hashNum, NULL);
    
    // Clean up all memory allocations
    freeDBF(birds);

    return 0;
}

// add an item to a specific bloom filter in the DBF
int addDBF(bf* birds, char* nextName, unsigned int* hashNum) {
    unsigned int hashes[*hashNum];
    uh1(nextName, birds->bfBits / BUCKET_SIZE, *hashNum, hashes);
   
    // check whether a bird has all unique hashes
    int* viewed = calloc(birds->bfBits / BUCKET_SIZE, sizeof(int));
    assert(viewed);
    for (int i = 0; i < *hashNum; i++) {
        if (!viewed[hashes[i]]) {
            viewed[hashes[i]] = 1;
            if (addBits(birds->arr, hashes[i])) {
                free(viewed);
                return 1;
            }
        } 
    }
    free(viewed);
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
    dbfNode* curr = birds->head;
    int totalCount = 0;
    unsigned int hashes[hashNum];

    while (curr != NULL) {
        // If filter has defined range
        if (curr->last_bird) {
            if (strcmp(nextName, curr->first_bird) >= 0 && strcmp(nextName, curr->last_bird) <= 0) {
                uh1(nextName, curr->filter->bfBits / BUCKET_SIZE, hashNum, hashes);
                int min_count = (1 << BUCKET_SIZE);

                for (int i = 0; i < hashNum; i++) {
                    int count = countBucket(curr->filter->arr, hashes[i]);
                    if (count < min_count) {
                        min_count = count;
                        if (min_count == 0) break;
                    }
                }
                totalCount += min_count;
            }
        }
        // Check last filter without upper bound
        else if (curr->next == NULL && strcmp(nextName, curr->first_bird) >= 0) {
            uh1(nextName, curr->filter->bfBits / BUCKET_SIZE, hashNum, hashes);
            int min_count = (1 << BUCKET_SIZE);

            for (int i = 0; i < hashNum; i++) {
                int count = countBucket(curr->filter->arr, hashes[i]);
                if (count < min_count) {
                    min_count = count;
                    if (min_count == 0) break;
                }
            }
            totalCount += min_count;
        }
        curr = curr->next;
    }
    return totalCount;
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
    if (!inFile) {
        fprintf(stderr, "Failed to open file: %s\n", fname);
        return;
    }

    if (fscanf(inFile, "%d %lf\n", &birds->maxBirds, &birds->fp_rate) != 2) {
        fprintf(stderr, "Failed to read header information\n");
        fclose(inFile);
        return;
    }

    // Initialize first filter
    dbfNode* head = createNewNode(birds->maxBirds, birds->fp_rate);
    if (!head) {
        fclose(inFile);
        return;
    }
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

        // Pass the current node's filter to addDBF
        if (addDBF(curr->filter, nextName, hashNum)) {
            // Handle overflow
            if (prev_name) {
                curr->last_bird = strdup(prev_name);
                curr->next = createNewNode(birds->maxBirds, birds->fp_rate);
                curr = curr->next;
                curr->first_bird = strdup(nextName);
                addDBF(curr->filter, nextName, hashNum);
            }
        }
        
        // Update tracking information
        curr->birdNames[curr->currentBirds] = strdup(nextName);
        curr->currentBirds++;
        curr->filter->numBirds++;
        
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

