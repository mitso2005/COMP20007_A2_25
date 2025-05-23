// Index of BF Input Filename
#define BFFILE 2

struct bloomFilter;
struct dynamicBF;

typedef struct bloomFilter bf;
typedef struct dynamicBF dbf;

int standardBF(char *datafile, char *testfile);
int countingBF(char *datafile, char *testfile, char* deletefile);
int dynamicBF(char *datafile, char *testfile, char *deletefile);


void birdReadBF(bf* birds, char* fname, unsigned int* hashNum);
void birdReadCBF(bf* birds, char* fname, unsigned int* hashNum);
void birdReadDBF(dbf* birds, char* fname, unsigned int* hashNum);

int checkBF(bf* birds, char* nextName, unsigned int hashNum);
int checkCBF(bf* birds, char* nextName, unsigned int hashNum);
int checkDBF(bf* birds, char* nextName, unsigned int hashNum);

void birdCheckBF(bf* birds, char* fname, unsigned int hashNum);
void birdCheckCBF(bf* birds, char* fname, unsigned int hashNum);
void birdCheckDBF(dbf* birds, char* fname, unsigned int hashNum);

void addBF(bf* birds, char* nextName, unsigned int* hashNum);
int addCBF(bf* birds, char* nextName, unsigned int* hashNum);
int addDBF(bf* birds, char* nextName, unsigned int* hashNum);

int birdDeleteCBF(bf* birds, char* nextName, unsigned int* hashNum);
int birdDeleteDBF(bf* birds, char* nextName, unsigned int* hashNum);

void deleteBirdsCBF(bf *birds, char *deletefile, unsigned int hashNum);
void deleteBirdsDBF(dbf *birds, char *deletefile, unsigned int hashNum);
