#include "assignment1.h"

void denseMatrixMult(int ** A, int ** B, int *** resultMatrix, int n)
{
	//Inititialize all variables used.
	int i, j;
	int ** zero;
	//temp1, temp2 are variables to be used to perform operations
	int ** temp1, ** temp2;
	//m0 through m6 are our 7 n/2 x n/2 matricies, C0-C3 are the four submatricies in res
	int ** m0, ** m1, ** m2, ** m3, ** m4, ** m5, ** m6; 	
	int ** C0, ** C1, ** C2, ** C3;
	int ** res;
	//Dynamically allocate a zero vector and a result vector
	initMatrix(&res, n);
	initMatrix(&zero, n);
	
	//Base case: if the matrix is 1x1, it is just scalar multiplication
	if(n == 1)
	{	
		res[0][0] = (A[0][0]) * (B[0][0]);
	}
	
	else
	{


		/*M0*/
		temp1 = sum(A, A, 0, 0, n/2, n/2, n/2);
		temp2 = sum(B, B, 0, 0, n/2, n/2, n/2);
		denseMatrixMult(temp1, temp2, &m0, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		/*M1*/
		temp1 = sum(A, A, n/2, 0, n/2, n/2, n/2);
		temp2 = sum(B, zero, 0, 0, 0, 0, n/2);
		denseMatrixMult(temp1, temp2, &m1, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		/*M2*/
		temp1 = sum(A, zero, 0, 0, 0, 0, n/2);
		temp2 = sub(B, B, 0, n/2, n/2, n/2, n/2);
		denseMatrixMult(temp1, temp2, &m2, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		/*M3*/
		temp1 = sum(A, zero, n/2, n/2, 0, 0, n/2);
		temp2 = sub(B, B, n/2, 0, 0, 0, n/2);
		denseMatrixMult(temp1, temp2, &m3, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		/*M4*/
		temp1 = sum(A, A, 0, 0, 0, n/2, n/2);
		temp2 = sum(B, zero, n/2, n/2, 0, 0, n/2);
		denseMatrixMult(temp1, temp2, &m4, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);	

		/*M5*/
		temp1 = sub(A, A, n/2, 0, 0, 0, n/2);
		temp2 = sum(B, B, 0, 0, 0, n/2, n/2);
		denseMatrixMult(temp1, temp2, &m5, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);
	
		/*M6*/
		temp1 = sub(A, A, 0, n/2, n/2, n/2, n/2);
		temp2 = sum(B, B, n/2, 0, n/2, n/2, n/2);
		denseMatrixMult(temp1, temp2, &m6, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		
		/*C0,0*/
		temp1 = sum(m0, m3, 0, 0, 0, 0, n/2);
		temp2 = sub(m4, m6, 0, 0, 0, 0, n/2);
		C0 = sub(temp1, temp2, 0, 0, 0, 0, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);
	
		/*C0,1*/
		C1 = sum(m2, m4, 0, 0, 0, 0, n/2);


		/*C1,0*/
		C2 = sum(m1, m3, 0, 0, 0, 0, n/2);

		/*C1,1*/
		temp1 = sub(m0, m1, 0, 0, 0, 0, n/2);
		temp2 = sum(m2, m5, 0, 0, 0, 0, n/2);
		C3 = sum(temp1, temp2, 0, 0, 0, 0, n/2);
		freeMatrix(n/2, temp1);
		freeMatrix(n/2, temp2);

		/*Result*/
		for(i = 0; i < n/2; i++)
		{
			for(j = 0; j < n/2; j++)
			{
				res[i][j] = C0[i][j];
				res[i][j + (n/2)] = C1[i][j];
				res[i + (n/2)][j] = C2[i][j];
				res[i + (n/2)][j + (n/2)] = C3[i][j];
				
			}
		}
		


		/*Freeing all m and c matricies*/

		
		freeMatrix(n/2, m0);
		freeMatrix(n/2, m1);
		freeMatrix(n/2, m2);
		freeMatrix(n/2, m3);
		freeMatrix(n/2, m4);
		freeMatrix(n/2, m5);
		freeMatrix(n/2, m6);
		
		freeMatrix(n/2, C0);
		freeMatrix(n/2, C1);
		freeMatrix(n/2, C2);
		freeMatrix(n/2, C3);

	}
	//free zero matrix
	freeMatrix(n, zero);

	//Assign result matrix to the input matrix
	*resultMatrix = res;	
}



int **sum(int ** A, int ** B, int x1, int y1, int x2, int y2, int n)
{
	/*This function takes two matrices A and B, and returns the sum of their sub-matrices. The sub-matrices are both of size nxn. The sub-matrix of A begins at the element (x1,y1) and the sub-matrix of B begins at the element (x2, y2)*/

	int i,j;
	int ** sumMat;
	initMatrix(&sumMat, n);


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
}
