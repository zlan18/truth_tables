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
extern int ind;
extern char* inputFormula;

//prints out subformula evaluations from left to right
void printFormulaEval(int* vars) {

	//set index pointer to beginning of formula
	ind = 0;

	//integer array same size as input formula to hold either -1 or boolean value of 0 or 1
	//initialized to entirely values of -1
	int* prettyPrint = malloc(sizeof(int) * (strlen(inputFormula) + 1));
	memset(prettyPrint, -1, (sizeof(int) * (strlen(inputFormula) + 1)));

	//until end of input formula is reached
	while(ind < (int)strlen(inputFormula)) {
		switch(inputFormula[ind]) {
			case '-': {
				int pointer = ind;	//remember where the propositional symbol is
				prettyPrint[pointer] = evalFormula(vars);	//evaluate the subformula
				ind = pointer + 1;	//put the index pointer back, just in case of nested subformulas
				break;
			}
			case '|':
			case '&':
			case '#':
			case '>':
			case '=': {
				int pointer = ind;	//remember where the propositional symbol is
				int pCount = 1;	//number of parentheses to 'match'

				//backtrack until beginning of full subformula is reached
				while ((inputFormula[ind] != '(') || (pCount == 0)) {
					if(inputFormula[ind] == ')') {
						pCount++;
					} else if(inputFormula[ind] == '(') {
						pCount--;
					}
					--ind;
				}
				prettyPrint[pointer] = evalFormula(vars); //evaluate the subformula
				ind = pointer + 1;	//put the index pointer back, just in case of nested subformulas on the righthand side
				break;
			}
			default: {
				++ind;	//either a parentheses or atomic formula, no need to print anything
				break;
			}
		}
	}
	//indicates end of array
	prettyPrint[strlen(inputFormula)] = 9;
	
	//set index pointer back to beginning of formula
	ind = 0;
	while(prettyPrint[ind] != 9) {
		//if a propositional symbol was evaluated here, print the value
		//else print a space
		if ((prettyPrint[ind] == 1) || (prettyPrint[ind] == 0)){
			printf("%d ", prettyPrint[ind]);
		} else {
			printf("  ");
		}
		++ind;
	}
	free(prettyPrint);
}

//print out the propositional variable name(s) and formula
void printHeader(int n) {

	for(int i = 0; i < n; i++) {
		printf("%c ", (97+i));	//add 97 to convert to appropriate lowercase letter in ASCII
	}

	printf(": ");

	//print out each character of input formula
	while(inputFormula[ind] != '\0') {
		printf("%c ", inputFormula[ind]);
		ind++;
	}
	
	//set index pointer back to beginning of formula
	ind = 0;

	printf(": Result\n");

	//prints out line of '=' to separate header from truth table
	for(int i=0; i<(n + (int)strlen(inputFormula) + (int)strlen(": Res")); i++) {
		printf("==");
	}
	printf("\n");
}
