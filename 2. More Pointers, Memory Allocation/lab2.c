#include "lab2.h"

void initMatrix(int ***mat,int n)
{
	/*This function takes a triple pointer mat, and makes it point to an nxn zero matrix*/
	int i, j;
	int **dynMat=(int **)malloc(sizeof(int*)*(unsigned long)n); /*makes a double pointer dynMat that points 									to an array of n single pointers*/
	for (i = 0; i < n; i++)
		{
			dynMat[i] = (int *)malloc(sizeof(int)*(unsigned long)n);/*Makes each pointer in dynMat 										point to a memory space storing integers*/
		}
	
	for (i = 0; i < n; i++) /*Assigns a value of 0 to every element in the dynamically allocated matrix*/
	{
		for (j =0; j < n; j++)
		{
			dynMat[i][j] = 0;
		}
	}
	*mat = dynMat;
}

void freeMatrix(int n, int ** matrix)
{
	/*This function frees the nxn matrix 'matrix'*/
	int i;
	for (i = 0; i < n; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

int **readMatrix(char * filename)
{
	/*This function reads the contents of a data file called 'filename' and stores the contents of this file in an array of size MATSIZE created by the function initMatrix()*/
	int ** matrix;
	initMatrix(&matrix, MATSIZE); /*dynamically allocates a 2D array of size MATSIZE*/
	int i, j;
	FILE *fp = fopen(filename, "r");
	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
			fscanf(fp, "%d", &matrix[i][j]); /*Assigns the values in filename into the matrix*/
		}
	}
	fclose(fp);
	return matrix;

}

void printMatrix(int n, int ** A)
{
	/*This function prints the nxn matrix 'A' into the console*/
	int i,j;
	for (i = 0; i < n; i++) 
	{
		for(j = 0; j < n; j++)
		{
			printf("%d ", A[i][j]); /*prints every value in the matrix*/
		}
		printf("\n"); /*prints a new line after every row*/
	}	
	freeMatrix(n, A);
}

int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
	/*This function takes two matrices A and B, and returns the sum of their sub-matrices. The sub-matrices are both of size nxn. The sub-matrix of A begins at the element (x1,y1) and the sub-matrix of B begins at the element (x2, y2)*/

	int i,j;
	int ** sumMat;
	initMatrix(&sumMat, n);

	/*This code makes us break from the function if the input is invalid. If the starting location plus the size of the sub-matrix is larger than the original matrix of size MATSIZE, then the input is invalid*/
	int start[4] = {x1, x2, y1, y2};
	for(i = 0; i < 4; i++)
	{
		if (start[i] + n > MATSIZE)
		{
			break;
		}
	}

	/*This section performs the action operation*/
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			sumMat[i][j] = A[x1 + i][y1 + j] + B[x2 + i][y2 + j];
		}
	}
	return sumMat;
	
}

int **sub(int **A, int **B, int x1, int y1, int x2, int y2, int n)
{
	/*This function takes two matrices A and B, and returns the difference of their sub-matrices. The sub-matrices are both of size nxn. The sub-matrix of A begins at the element (x1,y1) and the sub-matrix of B begins at the element (x2, y2)*/
	int i,j;
	int ** subMat;
	initMatrix(&subMat, n);


	/*This code makes us break from the function if the input is invalid. If the starting location plus the size of the sub-matrix is larger than the original matrix of size MATSIZE, then the input is invalid*/
	int start[4] = {x1, x2, y1, y2};
	for(i = 0; i < 4; i++)
	{
		if (start[i] + n > MATSIZE)
		{
			break;
		}
	}

	/*This section performs the action operation*/
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			subMat[i][j] = A[x1 + i][y1 + j] - B[x2 + i][y2 + j];
		}
	}
	return subMat;
}
