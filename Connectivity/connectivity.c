#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphADT.h"
#include "routing.h"
#include "connectivity.h"

#define MAX 100

int EdKarp(Graph *G, int s, int d){

	Graph *ResG = GRAPHinit(G->V);

	ResG->V = G->V;
	ResG->E = G->E;
	for(int i=0; i<G->V; i++)
		for(int j=0; j<G->V; j++)
			ResG->adj[i][j] = G->adj[i][j];

	//GRAPHshow(ResG);

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
		//GRAPHshow(ResG);
	}
	GRAPHfree(ResG, ResG->V);
	free(p);
  return maxFlow;
}
