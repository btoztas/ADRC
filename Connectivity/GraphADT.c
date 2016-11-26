#include <stdio.h>
#include <stdlib.h>
#include "GraphADT.h"

Graph *GRAPHinit(int V) {

	Graph	*G = (Graph*)malloc(sizeof(Graph));
	printf("FSDAFSADSADF\n");
	G -> V = 0;
	G -> E = 0;
	G -> adj = (int **)calloc(V,sizeof(int*));
	for (int i = 0; i < V; i++)
		G -> adj[i] =(int *)calloc(V,sizeof(int));
	return G;
}

void GRAPHinsertE(Graph *G, Edge *e) {

	G -> adj[e->w][e->v] = 1;
	G -> adj[e->v][e->w] = 1;
	G -> E++;

	if(e->w+1 > G->V)
		G -> V = e->w+1;
	if(e->v+1> G->V)
		G -> V = e->v+1;

}

void GRAPHshow(Graph *G) {
	int		v, t;

	printf("%d vertices, %d edges\n", G -> V, G -> E);
	for (v = 0; v < G -> V; v++) {
		printf("%2d:", v+1);
		for (t=0; t < G -> V; t++)
			if(G -> adj[v][t])
			printf(" (%d)", t+1);
		printf("\n");
	}
}

void GRAPHfree(Graph *G, int V){

	for (int i = 0; i < V; i++)
		free(G->adj[i]);
	free(G->adj);
	free(G);
	return;
}
