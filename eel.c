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

#define PART_A 0
#define PART_B 1

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
	// Convert part letter to number (A=0, B=1)
	int part = strcmp(argv[1], "A");
	assert(part == PART_A || part == PART_B);
	readGraph(argv[2], &coralSea, &timeSteps, part);
	
	// Solve the problem
	swim(coralSea,timeSteps, part);

	return 0;
}

void swim(riverSystem coralSea, int timeSteps, int part) {
    // State space: dp[lake][time][fat]
    // - lake: current location (0 to numLakes-1)
    // - time: remaining days (0 to timeSteps)
    // - fat: current fat level (0 to maxFat)
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

    // Initialize origin state with lake's fat gain
    // Cap initial fat to prevent exceeding maximum capacity
    int startFat = coralSea.initFat + coralSea.fatGains[coralSea.origin];
    startFat = startFat > coralSea.maxFat ? coralSea.maxFat : startFat;
    dp[coralSea.origin][timeSteps][startFat].maxFat = startFat;

    // Bottom-up DP: Work backwards from timeSteps to find optimal paths
    // For each possible state (lake, time, fat), try all possible transitions
    for (int time = timeSteps; time > 0; time--) {
        for (int lake = 0; lake < coralSea.numLakes; lake++) {
            for (int fat = 0; fat <= coralSea.maxFat; fat++) {
                // Skip unreachable states
                if (dp[lake][time][fat].maxFat == -1) continue;

                // Try all possible river transitions from current lake
                for (int i = 0; coralSea.lakes[lake][i].id != SENTINEL; i++) {
                    struct graphNode nextLake = coralSea.lakes[lake][i];
                    int riverCost = nextLake.cost_to_arrive;
                    
                    // Validate transition constraints:
                    // 1. Must have enough fat to traverse river
                    if (fat < riverCost) continue;

                    // Calculate time cost based on part
                    int timeCost;
                    if (part == PART_A) {
                        timeCost = 1;  // Part A: Fixed 1 day per river
                    } else {
                        timeCost = riverCost;  // Part B: Time = fat cost
                    }
                    
                    // 3. Must have enough remaining time
                    if (time - timeCost < 0) continue;
                    
                    // Calculate new state after transition:
                    // - Subtract river traversal cost
                    // - Add/subtract lake's fat effect
                    int newFat = fat - riverCost;
                    newFat += coralSea.fatGains[nextLake.id];
                    
                    // Skip if fat would drop to 0 or below
                    if (newFat <= 0) continue;
                    // Cap fat at maximum allowed
                    if (newFat > coralSea.maxFat) newFat = coralSea.maxFat;
                    
                    // Update if better solution found
                    if (dp[nextLake.id][time-timeCost][newFat].maxFat < newFat) {
                        dp[nextLake.id][time-timeCost][newFat].maxFat = newFat;
                        dp[nextLake.id][time-timeCost][newFat].prevLake = lake;
                        dp[nextLake.id][time-timeCost][newFat].prevTime = time;
                        dp[nextLake.id][time-timeCost][newFat].prevFatLevel = fat;
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
        printf("No Path :(\n");  // Fix case sensitivity
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
