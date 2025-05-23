/*
 * Starter file for Assignment 2 Part 2
 *
 * Created for COMP20007 Design of Algorithms 2025
 * Template written by Danielle Jayanthy <d.jayanthy@unimelb.edu.au>
 */

#include <math.h>
#include "birds.h"
#include <stdio.h>
#include <string.h>

#define MAXBIRDNAME 60
#define NUM_HASHES 7

int calc_m(int n, double fp_rate);

void printBF(bf* birds);
void printCBF(bf* birds);

void printBFHighlight(bf* birds, int highlights, unsigned int *hl);
void printCBFHighlight(bf* birds, int highlights, unsigned int *hl);
