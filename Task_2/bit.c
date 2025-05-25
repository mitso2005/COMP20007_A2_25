/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRI PETRAKIS.
 */

#include "bit.h"
#define SIZE 32U
#define ONE 1U

// Set the i-th bit to true (in A)
void bitOn(unsigned int A[], unsigned int bitIndex) {
    unsigned int idx = bitIndex / SIZE;
    unsigned int pos = bitIndex % SIZE;
    A[idx] |= (ONE << pos);
}

// set the i-th bit to false
void bitOff(unsigned int A[], unsigned int bitIndex) {
    unsigned int idx = bitIndex / SIZE;
    unsigned int pos = bitIndex % SIZE;
    A[idx] &= ~(ONE << pos);
}

// check the value of a single bit and return it
int checkBit(unsigned int A[], unsigned int bitIndex) {
    unsigned int idx = bitIndex / SIZE;
    unsigned int pos = bitIndex % SIZE;
    return (A[idx] & (ONE << pos)) ? 1 : 0;
}

// Initialise every bit to 0
void initBits(unsigned int A[], unsigned int arraySize) {
    unsigned int numInts = (arraySize + SIZE - 1) / SIZE; 
    for (unsigned int i = 0; i < numInts; i++) {
        A[i] = 0U;
    }
}

// This returns the value of a bucket. 
// bucketIndex is the index of the bucket we wish to insert into. 
int countBucket( unsigned int A[], unsigned int bucketIndex ){
    int value = 0;
    for (int j =0; j<BUCKET_SIZE; j++) {
        value +=  checkBit( A, bucketIndex*BUCKET_SIZE +j ) << j;
    }
    return value;
}

// Add one to a specific bucket. If adding will cause an overflow, return 1.
int addBits(unsigned int A[], unsigned int bucketIndex) {
    int currentValue = countBucket(A, bucketIndex);
    
    // Check for overflow (max value in 4 bits is 15)
    if (currentValue >= 15) {
        return 1;
    }
    
    // Clear the current bucket bits
    for (int j = 0; j < BUCKET_SIZE; j++) {
        bitOff(A, bucketIndex * BUCKET_SIZE + j);
    }
    
    // Set new value (currentValue + 1) in binary
    currentValue++;
    for (int j = 0; j < BUCKET_SIZE; j++) {
        if (currentValue & (1 << j)) {
            bitOn(A, bucketIndex * BUCKET_SIZE + j);
        }
    }
    
    return 0;
}

// take one from a specific bucket, if subtracting will cause an underflow, return 1.
int subtractBits(unsigned int A[], unsigned int bucketIndex) {
    int currentValue = countBucket(A, bucketIndex);
    
    // Check for underflow
    if (currentValue <= 0) {
        return 1;
    }
    
    // Clear the current bucket bits
    for (int j = 0; j < BUCKET_SIZE; j++) {
        bitOff(A, bucketIndex * BUCKET_SIZE + j);
    }
    
    // Set new value (currentValue - 1) in binary
    currentValue--;
    for (int j = 0; j < BUCKET_SIZE; j++) {
        if (currentValue & (1 << j)) {
            bitOn(A, bucketIndex * BUCKET_SIZE + j);
        }
    }
    
    return 0;
}
