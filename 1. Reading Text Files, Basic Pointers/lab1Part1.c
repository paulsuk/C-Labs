#include "lab1.h"

void printMatrix(int matrix[MATSIZE][MATSIZE])
{ 
	/* prints the values of the given array one by one, and adds a new line after every row */
	int a, b; /* a is the row number, and b is the column number*/
	for(a = 0; a < MATSIZE; a = a + 1) 
	{
		for(b = 0; b < MATSIZE; b = b + 1)
		{
			printf("%d ", matrix[a][b]); /*prints the value at the specific index*/
		}
		printf("\n"); /*prints a new line after a row has been printed*/
	}
}
