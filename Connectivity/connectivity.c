#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphADT.h"
#include "routing.h"
#include "connectivity.h"

int EdKarp(Graph *G, int s, int d){
	Graph *ResG;
	ResG = G;
	int maxFlow;
	maxFlow=0;
	int *p = (int*)malloc(sizeof(int)*G->V);
	int pre=s;
	while(BFS(ResG, p, s, d)){
		while(pre!=d){
			ResG->adj[pre][p[pre]] = 0;
  		ResG->adj[p[pre]][pre] = 0;
			pre = p[pre];
		}
		ResG->adj[pre][p[pre]] = 0;
		ResG->adj[p[pre]][pre] = 0;
		maxFlow++;
		pre=s;
		GRAPHshow(ResG);
	}
	free(p);
  return maxFlow;
}
