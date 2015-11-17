#include "lab8.h"

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

	if(fN->visitedNodes[t] == 0)
	{
		return 0;
	}
	return 1;
}
