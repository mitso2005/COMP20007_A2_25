#include <stdio.h>
#include <string.h>
#include "birds.h"

int main(int argc, char **argv){
    if (strcmp(argv[1], "B")==0) {
        return standardBF(argv[2], argv[3]);
    } else if (strcmp(argv[1], "C")==0){
        return countingBF(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "D")==0) {
        return dynamicBF(argv[2], argv[3], argv[4]);
    } else {
        printf("Invalid Method.\n Use with ./birds [method] [data_file] [test_file] [deletion_file (if method == 'D' only)]\n");
    }
    return 0;
}


