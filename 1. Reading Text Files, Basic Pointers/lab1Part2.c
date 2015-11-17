#include "lab1.h"

void readMatrix(char fileName[STRINGSIZE])
{
	/*takes a filename 'fileName' which is a text file of a matrix. This function reads the file and prints out the matrix*/
	int nums[MATSIZE][MATSIZE];
	int i, j;
	FILE *fp = fopen(fileName, "r"); /*declare a pointer in the file fp*/
	for(i = 0; i < MATSIZE; i++) /*iterate through the matrix row i and column j*/
	{
		for(j = 0; j < MATSIZE; j++)
		{
			fscanf(fp, "%d", &nums[i][j]); 
		}
	}
	fclose(fp); /*closes the file*/
	printMatrix(nums); /*calls the printMatrix function from part 1 to print out the formed matrix*/
}
