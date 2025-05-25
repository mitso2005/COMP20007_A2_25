#include "utils.h"
#include "bit.h"

struct bloomFilter;
struct dynamicBF;

typedef struct bloomFilter bf;

struct bloomFilter {
    unsigned int* arr;
    unsigned int bfBits;
};

/* This function calculates the number of bits you need to store n birds and maintain a false positive rate of fp_rate.
 * It then finds the closest prime number larger, to ensure our hash table size is a prime number. */
int calc_m(int n, double fp_rate) {
    int m = (int)((double)-n * log(fp_rate) / (double)(log(2) * log(2))) + 1;
    
    // Simple prime number finder - find next prime after m
    while (1) {
        int isPrime = 1;
        for (int i = 2; i * i <= m; i++) {
            if (m % i == 0) {
                isPrime = 0;
                break;
            }
        }
        if (isPrime) break;
        m++;
    }
    return m;
}

/* Prints the entire CBF */
/* If you are curious why the CBF prints this way, see:
 * https://en.wikipedia.org/wiki/Endianness */
void printCBF(bf* birds) {
    for (int i=0;i<birds->bfBits;i++) {
        printf("%d ", checkBit(birds->arr, i));
        if ((i+1)%BUCKET_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");
}

/* Prints the entire CBF and highlights which buckets have changed */
void printCBFHighlight(bf* birds, int highlights, unsigned int *hl) {
    for (int i=0;i<birds->bfBits;i++) {
        int toHighlight = 0;
        for(int j = 0; j < highlights; j++){
            if (hl[j] == (i/BUCKET_SIZE)){
                toHighlight = 1;
                break;
            }
        }
        if(toHighlight){
            printf("\e[42m\e[97m%d\e[0m ", checkBit(birds->arr, i));
        } else {
            printf("%d ", checkBit(birds->arr, i));
        }
        if ((i+1)%BUCKET_SIZE == 0) {
            printf("| ");
        }
    }
    printf("\n");
}

/* Prints the entire BF */
void printBF(bf* birds) {
    for (int i=0;i<birds->bfBits;i++) {
        printf("%d ", checkBit(birds->arr, i));
    }
    printf("\n");
}

/* Prints the entire BF and highlights which buckets have changed */
void printBFHighlight(bf* birds, int highlights, unsigned int *hl) {
    for (int i=0;i<birds->bfBits;i++) {
        int toHighlight = 0;
        for(int j = 0; j < highlights; j++){
            if (hl[j] == i){
                toHighlight = 1;
                break;
            }
        }
        if(toHighlight){
            printf("\e[42m\e[97m%d\e[0m ", checkBit(birds->arr, i));
        } else {
            printf("%d ", checkBit(birds->arr, i));
        }
    }
    printf("\n");
}

