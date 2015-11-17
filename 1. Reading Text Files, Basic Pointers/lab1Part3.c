#include "lab1.h"

void add(int matrix1[MATSIZE][MATSIZE], int matrix2[MATSIZE][MATSIZE] )
{
	/*This function takes two matrices matrix1 and matrix2, and prints the sum of the two matrices.*/
	int i,j;
	int sumMatrix[MATSIZE][MATSIZE];

	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
		sumMatrix[i][j] = matrix1[i][j] + matrix2[i][j]; /*the value in the new matrix is the sum of the 
		values of the previous matricies*/
		}
	}
	printMatrix(sumMatrix); /*calls the printMatrix function from part 1 to print out the formed matrix*/
}

void sub(int matrix1[MATSIZE][MATSIZE], int matrix2[MATSIZE][MATSIZE] )
{
	/*This function takes two matrices matrix1 and matrix2, and prints the result of matrix1 - matrix2*/
	int i,j;
	int subMatrix[MATSIZE][MATSIZE];

	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
		subMatrix[i][j] = matrix1[i][j] - matrix2[i][j]; /*the value in the new matrix is the difference of 		
		the values of the previous matricies*/
		}
	}
	printMatrix(subMatrix); /*calls the printMatrix function from part 1 to print out the formed matrix*/
}

void mult(int matrix1[MATSIZE][MATSIZE], int matrix2[MATSIZE][MATSIZE] )
{
	/*This function takes two matrices matrix1 and matrix2 and prints the result of matrix multiplication of matrix*/
	int i,j,k,multsum, prod;
	int multMatrix[MATSIZE][MATSIZE];

	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
			multsum = 0;
			for(k = 0; k < MATSIZE; k++) /*this for-loop is the dot product of row i of matrix1 and 						
			column j of matrix2, and saves that value in the variable multsum*/
			{
				prod = matrix1[i][k] * matrix2[k][j];
				multsum = multsum + prod;
			}
			multMatrix[i][j] = multsum; /*assign multsum, the dot product or row i of matrix1 and column 								j
										of matrix2, to the new matrix at [i][j]*/
		}
	}
	printMatrix(multMatrix); /*calls the printMatrix function from part 1 to print out the formed matrix*/
}

void matrixOperation(char filename1[STRINGSIZE], char filename2[STRINGSIZE], int operation)
{
	/*This function takes two file names, 'filename1' and 'filename2' and an integer 'operation'. 
	The strings {ADD, SUBTRACT, MULTIPLY} correspond to the integers {0,1,2}. If the integer is 0, 
	the function returns the sum of the matricies in the files 'filename1' and 'filename2'. 
	Similarly, subtraction for 1, and multiplication for 2. Otherwise, the function does nothing.*/
	int matrix1[MATSIZE][MATSIZE], matrix2[MATSIZE][MATSIZE];
	int i, j;

	FILE *fp = fopen(filename1, "r");
	FILE *fp2 = fopen(filename2, "r");
	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
			fscanf(fp, "%d", &matrix1[i][j]);
			fscanf(fp2, "%d", &matrix2[i][j]);
		}
	}
	fclose(fp);
	fclose(fp2);
	
	switch(operation){
		case ADD:
			add(matrix1, matrix2); /*calls the add function if addition*/
			break;
		case SUBTRACT:
			sub(matrix1, matrix2); /*calls the subtraction function if subtraction*/
			break;
		case MULTIPLY:
			mult(matrix1, matrix2); /*calls the multiplication function if multiplication*/
			break;
	default : 
		break;
	}
	
}
