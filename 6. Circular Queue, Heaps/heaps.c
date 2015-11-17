#include <stdio.h>
#include <stdlib.h>
#include "lab6.h"

struct Heap * initMinHeap()
{
	struct Heap* heap = (struct Heap*)malloc(sizeof(struct Heap));
	heap->count = 0;
	return heap;		
}

void insertMinHeap(struct Heap * h, struct Data d)
{
	int childIndex = h->count + 1;
	int parentIndex = childIndex/2;
	while(parentIndex > 0)
	{
		if(h->heapArray[parentIndex].data.data > d.data)
		{
			h->heapArray[childIndex] = h->heapArray[parentIndex];
			childIndex = parentIndex;
			parentIndex = parentIndex/2;
		}
		else
		{
			h->heapArray[childIndex].data = d;
			h->count ++;
			return;
		}
	}
	h->heapArray[childIndex].data = d;
	h->count ++;
	
}

struct Data removeMinHeap(struct Heap * h)
{
	struct Data value = h->heapArray[1].data;
	h->heapArray[1] = h->heapArray[h->count];
	h->count = h->count - 1;
	
	int parentIndex = 1;
	int childIndex = 2;
	struct Data temp;
	while(childIndex <= h->count)
	{
		if(childIndex < h->count)
		{
			if(h->heapArray[childIndex].data.data > h->heapArray[childIndex+1].data.data)
			{
				childIndex++;
			}
		}
		if(h->heapArray[parentIndex].data.data > h->heapArray[childIndex].data.data)
		{
			temp = h->heapArray[parentIndex].data;
			h->heapArray[parentIndex] = h->heapArray[childIndex];
			h->heapArray[childIndex].data = temp;
		}
		parentIndex = childIndex;
		childIndex = childIndex * 2;
	}
	return value;			
}

void freeMinHeap(struct Heap * h)
{
	free(h);
}
