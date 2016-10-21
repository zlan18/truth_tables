//Student ID: 140009228
//23 February 2016
//Logic Practical
//formula_parser.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttable.h"

//global variables to hold current position in formula evaluation
extern int ind;
extern char* inputFormula;

//evaluates atomic formulas
int evalAtomic(int* vars) {
	int asciiVal = (int)inputFormula[ind];	//gets ASCII value of char at current idex
	++ind;

	//convert ASCII value to appropriate integer constant or variable value
	if (asciiVal == 48) {
		return 0;
	} else if (asciiVal == 49) {
		return 1;
	}else if ((asciiVal > 96) && (asciiVal < 123)) {
		return vars[asciiVal-97];
	} else {
		printf("ERROR: ill-formed formula - unsupported atomic formula value, ASCII value %d \n", asciiVal);
		abort();
	}
}

//evaluates reduced compound formulas
int evalComp(int val1, char op, int val2) {
	switch(op) {
		case '=': {
			return (val1 == val2);
			break;
		}
		case '|': {
			return (val1 || val2);
			break;
		}
		case '&': {
			return (val1 && val2);
			break;
		}
		case '#': {
			return ((val1 || val2) && !(val1 && val2));
			break;
		}
		case '>': {
			return (!(val1 && !val2));
			break;
		}
		default: {
			printf("ERROR: ill-formed formula - unsupported logical operator %c \n", op);
			abort();
		}
	}
}

//evaluates a given formula
int evalFormula(int* vars) {
	switch(inputFormula[ind]) {
		case '(': {
			++ind;
			int val1 = evalFormula(vars);	//evaluate the left subformula
			char op = inputFormula[ind];	//grab the logical operator symbol
			++ind;
			int val2 = evalFormula(vars);	//evaluate the right subformula

			//if the compound formula does not both begin and end with parentheses
			//then error else move on
			if(inputFormula[ind] != ')') {
				printf("ERROR: ill-formed formula - bracket mismatch \n");
				abort();
			} else {
				++ind;
			}
			
			//evaluate and return the compound formula
			return evalComp(val1, op, val2);
			break;
		}
		case '-': {	
			++ind;
			
			//return the negated value of the formula immediately following
			return !evalFormula(vars);
			break;
		}
		default:
			//return the value of the atomic formula
			return evalAtomic(vars);
			break;
	}
}
