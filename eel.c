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
    // dp[lake][time] = maximum fat achievable at this lake with this much time remaining
    int** dp = malloc(coralSea.numLakes * sizeof(int*));
    int** parent = malloc(coralSea.numLakes * sizeof(int*));
    int** parentTime = malloc(coralSea.numLakes * sizeof(int*));
    
    for (int i = 0; i < coralSea.numLakes; i++) {
        dp[i] = malloc((timeSteps + 1) * sizeof(int));
        parent[i] = malloc((timeSteps + 1) * sizeof(int));
        parentTime[i] = malloc((timeSteps + 1) * sizeof(int));
        for (int t = 0; t <= timeSteps; t++) {
            dp[i][t] = -1;  // -1 means impossible
            parent[i][t] = -1;
            parentTime[i][t] = -1;
        }
    }
    
    // Initialize: start at origin with just the initial fat
    // Do NOT add origin's fat gain here - only when we arrive at origin later
    if (coralSea.initFat > 0) {
        dp[coralSea.origin][timeSteps] = coralSea.initFat;
    }
    
    // Dynamic programming: process in reverse time order
    for (int time = timeSteps; time >= 1; time--) {
        for (int lake = 0; lake < coralSea.numLakes; lake++) {
            if (dp[lake][time] == -1) continue;
            
            int currentFat = dp[lake][time];
            
            // Try all neighbors
            for (int i = 0; coralSea.lakes[lake][i].id != SENTINEL; i++) {
                int nextLake = coralSea.lakes[lake][i].id;
                int travelCost = coralSea.lakes[lake][i].cost_to_arrive;
                int timeCost = (part == PART_A) ? 1 : travelCost;
                
                // Check constraints
                if (time < timeCost) continue;  // Not enough time
                if (currentFat <= travelCost) continue;  // Not enough fat to survive travel
                
                // Calculate resulting state
                int timeAfter = time - timeCost;
                int fatAfterTravel = currentFat - travelCost;
                int fatAfterEating = fatAfterTravel + coralSea.fatGains[nextLake];
                
                // Check if we die from eating (or negative fat gain)
                if (fatAfterEating <= 0) continue;
                
                // Cap at maximum fat
                if (fatAfterEating > coralSea.maxFat) {
                    fatAfterEating = coralSea.maxFat;
                }
                
                // Update if better (higher fat, or same fat but we prefer earlier arrival times)
                if (dp[nextLake][timeAfter] < fatAfterEating) {
                    dp[nextLake][timeAfter] = fatAfterEating;
                    parent[nextLake][timeAfter] = lake;
                    parentTime[nextLake][timeAfter] = time;
                }
            }
        }
    }
    
    // Find the best solution at destination
    int bestFat = -1;
    int bestTime = -1;
    
    // Check all possible arrival times, prefer earlier arrival for same fat
    for (int time = 0; time <= timeSteps; time++) {
        if (dp[coralSea.dest][time] > bestFat) {
            bestFat = dp[coralSea.dest][time];
            bestTime = time;
        }
    }
    
    if (bestFat == -1) {
        printf("No Path :(\n");
    } else {
        // Reconstruct path
        int* path = malloc((timeSteps + 1) * sizeof(int));
        int pathLen = 0;
        
        int currLake = coralSea.dest;
        int currTime = bestTime;
        
        while (currLake != -1) {
            path[pathLen++] = currLake;
            int prevLake = parent[currLake][currTime];
            int prevTime = parentTime[currLake][currTime];
            currLake = prevLake;
            currTime = prevTime;
        }
        
        printf("Max Fat: %d\nPath: ", bestFat);
        for (int i = pathLen - 1; i >= 0; i--) {
            printf("%d", path[i]);
            if (i > 0) printf(", ");
        }
        printf("\n");
        
        free(path);
    }
    
    // Clean up
    for (int i = 0; i < coralSea.numLakes; i++) {
        free(dp[i]);
        free(parent[i]);
        free(parentTime[i]);
    }
    free(dp);
    free(parent);
    free(parentTime);
}

/* =====================================================================
   This skeleton/program is compiled by the comp20007 teaching team,
   the university of Melbourne.
   Last Updated: 26/04/2025
   ================================================================== */
