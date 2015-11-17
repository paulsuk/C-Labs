#include "queue.h"

struct Queue initQueue()
{
	struct Queue queue;
	queue.currSize = 0;
	queue.front = NULL;
	queue.rear = NULL;
	return queue;
}

void enqueue(struct Queue *qPtr, struct Data d)
{
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
	while(qPtr->currSize != 0)
	{
		dequeue(qPtr);
	}
}
