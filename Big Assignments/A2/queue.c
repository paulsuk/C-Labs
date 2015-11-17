#include "queue.h"

struct Queue initQueue()
{
	//This function initiallizes a queue
	struct Queue queue;
	queue.currSize = 0;
	queue.front = NULL;
	queue.rear = NULL;
	return queue;
}

void enqueue(struct Queue *qPtr, struct Data d)
{
	//This function adds a node to a queue that has the data d
	struct Node * newNode;
	newNode = (struct Node *)malloc(sizeof(struct Node));
	qPtr->currSize += 1;
	newNode->next = NULL;
	newNode->data = d;
	if(qPtr->front == NULL)
	{
		qPtr->front = newNode;
		qPtr->rear = newNode;
	}
	else
	{
		qPtr->rear->next = newNode;
		qPtr->rear = newNode;
	}
}

struct Data dequeue(struct Queue *qPtr)
{
	//This function takes out the front node to the queue and returns the data that was in that node
	struct Data value;
	struct Node * temp;
	qPtr->currSize -= 1;
	temp = qPtr->front;
	qPtr->front = qPtr->front->next;
	value = temp->data;
	free(temp);
	return value;	
}

void freeQueue(struct Queue *qPtr)
{
	//This frees the queue by calling the function dequeue multiple times
	while(qPtr->currSize != 0)
	{
		dequeue(qPtr);
	}
}
