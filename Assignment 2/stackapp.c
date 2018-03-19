/* CS261- Assignment 2 - stackapp.c*/
/* Name:Brandon Lo
 * Date:1/29/17
 * Solution description: Implementation of a stack to check if the inclusion of {}, [], or () is balanced
 */

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string
	pre: s is not null
*/
char nextChar(char* s)
{
	static int i = -1;
	char c;
	++i;
	c = *(s+i);
	if ( c == '\0' )
		return '\0';
	else
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string
	pre: s is not null
	post:
*/
int isBalanced(char* s)
{
	char currentChar,
	top;

	DynArr *balancedStack = newDynArr(25);

	if (s == NULL){
		/*Test if no string is inputted*/
		printf("NO STRING PROVIDED\n");
		return 0;
	}

	else{
		for (currentChar = nextChar(s); currentChar;currentChar = nextChar(s)){

			if(currentChar == '(' || currentChar == '{' || currentChar == '['){
				pushDynArr(balancedStack,currentChar);
			}
			else if(currentChar == ')' || currentChar == '}' || currentChar == ']'){
				/*Edge case testing for only right part of the parentheses aka. hello) should return false*/
				if (isEmptyDynArr(balancedStack) == 1){
					deleteDynArr(balancedStack);
					return 0;
				}

				top = topDynArr(balancedStack);
				if((currentChar == ')' && top == '(') || (currentChar == '}' && top == '{') || (currentChar == ']' && top == '[')) {
					popDynArr(balancedStack);
	        	}
			}
		}
	}

	/*Checks if it is empty. If its is true, that is */
	if(isEmptyDynArr(balancedStack) == 1){
		deleteDynArr(balancedStack);
		return 1;
	}
	else{
		deleteDynArr(balancedStack);
		return 0;
	}
}

int main(int argc, char* argv[]){

	char* s=argv[1];
	int res;

	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else
		printf("The string %s is not balanced\n",s);

	return 0;
}
