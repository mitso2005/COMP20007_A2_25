/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by YOUR NAME HERE.
 */

#include "bit.h"
#define SIZE 32U
#define ONE 1U

// Set the i-th bit to true (in A)
void bitOn( unsigned int A[], unsigned int bitIndex ) {
    // FILL-IN
}

// set the i-th bit to false
void bitOff( unsigned int A[], unsigned int bitIndex ) {
    // FILL-IN
}

// check the value of a single bit and return it
int checkBit( unsigned int A[], unsigned int bitIndex ) {
    return // FILL-IN  
}

// Initialise every bit to 0
void initBits( unsigned int A[], unsigned int arraySize ) {
    // FILL IN
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
// Remember to do this check before you increment a bucket!
// bucketIndex is the index of the bucket we wish to insert into. 
int addBits( unsigned int A[], unsigned int bucketIndex ) {
    // FILL-IN
    return 0;
}

// take one from a specific bucket, if subtracting will cause an underflow, return 1.
// Remember to do this check before you decrement a bucket!
// bucketIndex is the index of the bucket we wish to insert into. 
int subtractBits( unsigned int A[], unsigned int bucketIndex ) {
    // FILL-IN
    return 0;
}

