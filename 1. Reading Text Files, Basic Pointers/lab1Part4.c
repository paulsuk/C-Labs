#include "lab1.h"

void findDeterminant(char filename[STRINGSIZE])
{	
	/*This function takes in a filename, and by calling the function determinant, prints the determinant of the matrix in the file 'filename'*/
	int nums[MATSIZE][MATSIZE];
	int i, j;
	FILE *fp3 = fopen(filename, "r");
	for(i = 0; i < MATSIZE; i++)
	{
		for(j = 0; j < MATSIZE; j++)
		{
			fscanf(fp3, "%d", &nums[i][j]);
		}
	}
	fclose(fp3);
	int ans = determinant(MATSIZE, nums); /*calling the function determinant*/
	printf("The determinant of the matrix in %s is %d\n", filename, ans);
}

int determinant(int n, int matrix[n][n])
{
	/*This function takes in an integer 'n' which is the size of the square matrix 'matrix[n][n]' and recursively calculates the determinant of the matrix. Then, the function returns that value.*/
	int i,j,k, pass, minor[n-1][n-1];

	if(n == 1) /*Base case 1: The matrix is a 1x1 matrix in which case, the determinant is the value of the one element*/
	{
		return matrix[0][0];
	}

	else if(n==2) /*Base case 2: The matrix is a 2x2 matrix in which case, we return ad-bc where the matrix is [a,b;c,d]*/
	{
		return(matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
	}
	else /*Otherwise, uses the method of determinant expansion by minors, to recursively calculate the determinant, until the matrix is 2x2 or smaller*/
	{
		int det = 0;
		
		for(i=0; i<n; i++)
		{
			for(j=0; j<n-1 ; j++)
			{
				pass = false;
				for(k=0; k<n-1; k++)
				{
					if(k == i)
					{
						pass = true;
						minor[j][k] = matrix[j+1][k+1];
					}
					else if(pass)
					{
						minor[j][k] = matrix[j+1][k+1];
					}
					else
					{
						minor[j][k] = matrix[j+1][k];
					}
				}
			}
			det += (pow(-1,i+2))*matrix[0][i]*determinant(n-1, minor);
		}
		return det;
	}
}



