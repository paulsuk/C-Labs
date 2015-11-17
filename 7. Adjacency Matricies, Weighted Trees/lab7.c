#include "lab7.h"

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
