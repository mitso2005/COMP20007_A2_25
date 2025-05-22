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

void swim(riverSystem coralSea, int timeSteps, int part) {
    // Create 3D DP array [lake][time][fat]
    // dp[lake][time][fat] stores the state for being at 'lake' at 'time' with 'fat' units
    State*** dp = malloc(coralSea.numLakes * sizeof(State**));
    for (int i = 0; i < coralSea.numLakes; i++) {
        dp[i] = malloc((timeSteps + 1) * sizeof(State*));
        for (int j = 0; j <= timeSteps; j++) {
            dp[i][j] = malloc((coralSea.maxFat + 1) * sizeof(State));
            for (int k = 0; k <= coralSea.maxFat; k++) {
                dp[i][j][k].maxFat = -1;  // Initialize as impossible
                dp[i][j][k].prevLake = -1;
            }
        }
    }

    // Initialize starting state by adding lake's fat gain to initial fat
    int startFat = coralSea.initFat + coralSea.fatGains[coralSea.origin];
    startFat = startFat > coralSea.maxFat ? coralSea.maxFat : startFat;
    dp[coralSea.origin][timeSteps][startFat].maxFat = startFat;

    // Bottom-up DP: Work backwards from timeSteps to 0
    for (int time = timeSteps; time > 0; time--) {
        // Consider each possible current lake
        for (int lake = 0; lake < coralSea.numLakes; lake++) {
            // Consider each possible fat level at current lake
            for (int fat = 0; fat <= coralSea.maxFat; fat++) {
                // Skip impossible states
                if (dp[lake][time][fat].maxFat == -1) continue;

                // Try all possible next lakes connected by rivers
                for (int i = 0; coralSea.lakes[lake][i].id != SENTINEL; i++) {
                    struct graphNode nextLake = coralSea.lakes[lake][i];
                    
                    // Skip if not enough fat to traverse river
                    if (fat < nextLake.cost_to_arrive) continue;
                    
                    // Update fat after river traversal and lake effects
                    int newFat = fat - nextLake.cost_to_arrive;
                    newFat += coralSea.fatGains[nextLake.id];
                    
                    // Skip if fat would drop to 0 or below
                    if (newFat <= 0) continue;
                    // Cap fat at maximum allowed
                    if (newFat > coralSea.maxFat) newFat = coralSea.maxFat;
                    
                    // Update state if better fat level found
                    if (dp[nextLake.id][time-1][newFat].maxFat < newFat) {
                        dp[nextLake.id][time-1][newFat].maxFat = newFat;
                        dp[nextLake.id][time-1][newFat].prevLake = lake;
                        dp[nextLake.id][time-1][newFat].prevTime = time;
                        dp[nextLake.id][time-1][newFat].prevFatLevel = fat;
                    }
                }
            }
        }
    }

    // Find best result at ocean
    int bestFat = -1;
    int bestTime = 0;
    int bestFatLevel = 0;
    for (int time = 0; time <= timeSteps; time++) {
        for (int fat = 0; fat <= coralSea.maxFat; fat++) {
            if (dp[coralSea.dest][time][fat].maxFat > bestFat) {
                bestFat = dp[coralSea.dest][time][fat].maxFat;
                bestTime = time;
                bestFatLevel = fat;
            }
        }
    }

    if (bestFat == -1) {
        printf("No path :(\n");
    } else {
        // Reconstruct path
        int* path = malloc(timeSteps * sizeof(int));
        int pathLen = 0;
        int currLake = coralSea.dest;
        int currTime = bestTime;
        int currFat = bestFatLevel;

        while (currLake != -1) {
            path[pathLen++] = currLake;
            State prevState = dp[currLake][currTime][currFat];
            currLake = prevState.prevLake;
            currTime = prevState.prevTime;
            currFat = prevState.prevFatLevel;
        }

        printf("Max Fat: %d\nPath: ", bestFat);
        for (int i = pathLen - 1; i >= 0; i--) {
            printf("%d%s", path[i], i > 0 ? ", " : "\n");
        }
        free(path);
    }

    // Free memory
    for (int i = 0; i < coralSea.numLakes; i++) {
        for (int j = 0; j <= timeSteps; j++) {
            free(dp[i][j]);
        }
        free(dp[i]);
    }
    free(dp);
}

/* =====================================================================
   This skeleton/program is compiled by the comp20007 teaching team,
   the university of Melbourne.
   Last Updated: 26/04/2025
   ================================================================== */
