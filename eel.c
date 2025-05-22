/*
 * Starter file for Assignment 2 Task 1
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 * Implementation by DIMITRIOS PETRAKIS.
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "utils.h"
#include <string.h>

/* This function finds the path in a river system that grants you (the eel) the most fat
 * given you must reach the ocean in time. */
void swim(riverSystem coralSea, int timeSteps, int part);

int main(int argc, char* argv[]) {
	if(argc < 3){
		fprintf(stderr, "./eel [part] [input_file]\n");
		exit(EXIT_FAILURE);
	}

	// our river system
	riverSystem coralSea;

	// time until breeding season
	int timeSteps;

	// Read the problem in
	int part = strcmp(argv[1], "A");
	assert(part >=0);
	readGraph(argv[2], &coralSea, &timeSteps, part);
	
	// Solve the problem
	swim(coralSea,timeSteps, part);

	return 0;
}

/* This will be the function where you write your dynamic programming solution.
 * It should handle finding the path. */
void swim(riverSystem coralSea, int timeSteps, int part) {
	/* ************ FILL-IN ************ */

}

/* =====================================================================
   This skeleton/program is compiled by the comp20007 teaching team,
   the university of Melbourne.
   Last Updated: 26/04/2025
   ================================================================== */
