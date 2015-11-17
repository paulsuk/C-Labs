#include "assignment3.h"

struct flowNetwork * initFlowNetwork(){
	struct flowNetwork * flow = (struct flowNetwork *)malloc(sizeof(struct flowNetwork));
	flow->adjMatrix = initAdjMatrix();

	int i;

	for(i = 0; i < NODES; i++)
	{
		flow->visitedNodes[i] = 0;
		flow->parent[i] = -1;
	}

	return flow;
}

void deleteFlowNetwork(struct flowNetwork * fN){
	deleteAdjMatrix(fN->adjMatrix);
	free(fN);
}

int breadthFirstPathSearch(struct flowNetwork * fN, int s, int t){
	int i, j, curr;

	struct Queue* q;
	initQueue(&q);
	struct Data * d = (struct Data *)malloc(sizeof(struct Data));
	d->vertex = s;
	enqueue(q, *d);
	
	for(i = 0; i < NODES; i ++)
	{
		fN->parent[i] = -1;
		fN->visitedNodes[i] = 0;
	}
	
	while(isQueueEmpty(q) !=1)
	{
		dequeue(q, d);
		i = d->vertex;
		fN->visitedNodes[i] = 1;
		for(j = 0; j < NODES; j++)
		{
			if(fN->adjMatrix[i][j].flowCap != 0)
			{
				if(fN->visitedNodes[j] == 0 && fN->adjMatrix[i][j].flow < fN->adjMatrix[i][j].flowCap)
				{
					fN->parent[j] = i;
					d->vertex = j;
					enqueue(q, *d);
					fN->visitedNodes[j] = 1;
				}
			}
		}
	}
	
	free(d);
	free(q);

	if(fN->visitedNodes[t] != 0)
	{
		return 1;
	}
	return 0;
}

void maximizeFlowNetwork(struct flowNetwork * fN, int s, int t){
	int i, temp, temp2, j, k, curr, minFlow = 0;
	struct Queue * queue;
	initQueue(&queue);
	struct Data * d = (struct Data *)malloc(sizeof(struct Data));

	while(breadthFirstPathSearch(fN,s,t) == 1)
	{
		minFlow = INF;
		k = t;
		j = fN->parent[k];
		while(k != s)
		{
			temp = fN->adjMatrix[j][k].flowCap - fN->adjMatrix[j][k].flow;
			if(minFlow > temp)
			{
				minFlow = temp;
			}
			d->vertex = k;
			enqueue(queue, *d);
			k = j;
			j = fN->parent[j];
		}

		temp2 = t;
		while(isQueueEmpty(queue) == 0)
		{
			dequeue(queue, d);
			temp = fN->parent[d->vertex];
			fN->adjMatrix[temp][temp2].flow += minFlow;
			fN->adjMatrix[temp2][temp].flow -= minFlow;
			temp2 = temp;
		}
		

	}
	free(d);
	free(queue);
}
