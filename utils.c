/*
 * Starter file for Assignment 2 Task 1
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

/* Read in the problem */
void readGraph(char* fname, riverSystem* coralSea, int* timeSteps, int part) {
	FILE *inputFile = fopen(fname, "r");
	assert(inputFile);
	assert(fscanf(inputFile, "%d %d %d %d\n %d %d %d", &(coralSea->numLakes), &(coralSea->numRivers), &(coralSea->origin), \
											&(coralSea->dest), &(coralSea->initFat), &(coralSea->maxFat), timeSteps)  == 7);

	(*coralSea).fatGains = malloc(sizeof(int)*(*coralSea).numLakes);
	assert((*coralSea).fatGains);
	// Add all edges to graph.
	for(int i = 0; i < coralSea->numLakes; i++){
		assert(fscanf(inputFile, "%d", &(coralSea->fatGains[i])) == 1);
	}

	// Initialise Adjacency Lists
	coralSea->lakes = (lake **) malloc(sizeof(lake *) * (coralSea)->numLakes);
	assert(coralSea->lakes);
	for(int i = 0; i < coralSea->numLakes; i++){
		coralSea->lakes[i] = (lake *) malloc(sizeof(lake));
		assert(coralSea->lakes[i]);
		coralSea->lakes[i][0].id = SENTINEL;
	}

	// Add edges 
	int fromLake;
	for(int i = 0; i < coralSea->numRivers; i++){
		assert(fscanf(inputFile, "%d", &fromLake) == 1);
		// Find end of Adjacency List (marked by SENTINEL) of source lake
		int endOfList = 0;
		while(coralSea->lakes[fromLake][endOfList].id != SENTINEL){
			endOfList++;
		}
		assert(fscanf(inputFile, "%d %d",&(coralSea->lakes[fromLake][endOfList].id), &(coralSea->lakes[fromLake][endOfList].cost_to_arrive)) == 2);
		// Extend list to include SENTINEL at new end
		coralSea->lakes[fromLake] = realloc(coralSea->lakes[fromLake], sizeof(lake)*(endOfList + 2));
		assert(coralSea->lakes[fromLake]);
		coralSea->lakes[fromLake][endOfList + 1].id = SENTINEL;

	}
	assert(fclose(inputFile) == 0);

}


/* =====================================================================
   This skeleton/program is compiled by the comp20007 teaching team,
   the university of Melbourne.
   Last Updated: 26/04/2025
   ================================================================== */
