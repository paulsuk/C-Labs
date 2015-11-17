#include "lab4.h"

void insertNode(int d, struct Node ** lPtr)
{
	struct Node * currNode = *lPtr;
	struct Node * prevNode = NULL;
	struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = d;

	//Empty list 
	if(*lPtr == NULL)
	{
		*lPtr = newNode;
		newNode->next = NULL;
	}
	else
	{	
		//NewNode goes at the front
		if(currNode->data > d)
		{
			newNode->next = *lPtr;
			*lPtr = newNode;
		}
	
		else
		{
			while((currNode!= NULL) && (currNode->data < d))
			{
				prevNode = currNode;
				currNode = currNode->next;
			}

			//NewNode goes at the end
			if(currNode == NULL)
			{
				prevNode->next = newNode;
				newNode->next = NULL;
			}

			//Anything in between
			else
			{
				prevNode->next = newNode;
				newNode->next = currNode;
			}
			return;	
		}
	}
}

void deleteNode(int d, struct Node ** lPtr)
{
	struct Node * currNode = *lPtr, *prevNode = NULL;
	
	while(currNode!=NULL)
	{
		if(currNode->data == d)
		{
			if(prevNode == NULL)
			{
				*lPtr = currNode->next;
			}	
			else
			{
				prevNode->next = currNode->next;
			}
			free(currNode);
			return;
		}
		prevNode = currNode;
		currNode = currNode->next;
	}	
}

void printList(struct Node * L)
{
	struct Node * currNode = L;
	if(currNode!=NULL)
	{
		while(currNode!=NULL)
		{
			printf("%d ", currNode->data);
			currNode = currNode->next;
		}
		printf("\n");
	}
}

struct Node ** createTable(int buckets)
{
	struct Node ** newTable = (struct Node**)malloc(sizeof(struct Node *)*(unsigned long) buckets);
	int i;	
	for(i = 0; i < buckets; i++)
	{
		newTable[i] = NULL;
	}
	return newTable;
}

int findHash(int key, int buckets)
{
	int hash = key%buckets;
	return hash;
}

void insertTable(int key, int buckets, struct Node ** tablePtr)
{
	int index = findHash(key, buckets);
	insertNode(key, &tablePtr[index]);
}

void freeTable(struct Node ** tablePtr, int buckets)
{
	int i;
	struct Node * temp1, * temp2;
	for(i = 0; i < buckets; i++)
	{
		temp1 = tablePtr[i];
		while(temp1 != NULL)
		{
			temp2 = temp1;
			temp1 = temp1->next;
			free(temp2);
		}			
	}
	free(tablePtr);
}


