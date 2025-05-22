/*
 * Starter file for Assignment 2 Task 1
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */
#include <stdio.h>

#define SENTINEL -1

// Structure to store path information
typedef struct {
    int maxFat;
    int prevLake;
    int prevTime;
    int prevFatLevel;
} State;

// This is a lake
struct graphNode {
  int id;
  int cost_to_arrive;
};

typedef struct graphNode lake;

// This is the river system
typedef struct graph {
  int numLakes;
  int numRivers;
  int origin;
  int dest;
  int initFat;
  int maxFat;
  // List of fat gains at each lake
  int* fatGains;
  // Adjacency List of lakes
  lake** lakes;
} riverSystem;

/* Reads the graph */
void readGraph(char* fname, riverSystem* coralSea, int *timeSteps, int part);


/* =====================================================================
   This skeleton/program is compiled by the comp20007 teaching team,
   the university of Melbourne.
   Last Updated: 26/04/2025
   ================================================================== */
