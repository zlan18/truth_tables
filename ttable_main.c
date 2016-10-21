//Student ID: 140009228
//22 February 2016
//Logic Practical
//ttable.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "ttable.h"

//global variables to hold current position in formula evaluation
int ind;
char* inputFormula;

//calculates all possible combinations of n variables
//inspired by binary counting
int** makeVarArray(int n) {
	int** arr = malloc(sizeof(int) * ((int)pow(2, n)) * n);

	//will loop for each possible combination (2^n times)
	for(int c = 0; c < pow(2, n); c++) {
		int* subArr = malloc(sizeof(int) * n);
		int counter = 0;
		
		//will loop to ensure each variable is given a value (n times)
		for(int p = (n-1); p >= 0; p--) {
			
			//if the counter has not exceeded the greater for loop number
			//and 2^(variable index) is less than the difference between the counter and greater for loop number
			if((counter < c) && (pow(2, p) <= (c - counter))) {
				subArr[p] = 1;		//then set the variable to '1' (true)
				counter += pow(2, p);	//and add 2^(variable index) to the current counter
			} else {
				subArr[p] = 0;		//otherwise set the variable to '0' (false)
			}
		}
		arr[c] = subArr;	//add the combination of values to the array
	}
	return arr;
}

//main function
int main (int argc, char* const args[]) {
	if (argc == 3) {
		int numVars = atoi(args[1]);	     //number of variables as specified by user
		int numPoss = (int)pow(2,numVars);   //number of possible combinations of these variable values

		int** vars = makeVarArray(numVars);
		inputFormula = args[2];

		printHeader(numVars);
		
		//for each possible combination of variable values
		for(int p = 0; p < numPoss; p++) {

			//print out their corresponding values
			for (int c = 0; c < numVars; c++) {
				printf("%d ", vars[p][c]);
			}
			printf(": ");

			//print out the values of the propositional subformulas
			printFormulaEval(vars[p]);

			//start back at the beginning of the input formula
			//print out the result
			ind = 0;
			printf(": %d \n", evalFormula(vars[p]));
		}		
		free(vars);
	} else if (argc < 3) {
		printf("Two arguments expected: the number of propositional variables in the formula followed by a formula.");
	} else {
		printf("Too many arguments supplied. Please do not use whitespace within the input formula.");
	}
}
