#include <stdio.h>
#include <stdlib.h>
#include "GraphADT.h"

link *NEW(int v, link *next) {

	link	*x;
	x = (link*)malloc(sizeof(link));
	x -> v = v;
	x -> next = next;
	return x;
}

Graph *GRAPHinit(int V) {

	int	v;
	Graph	*G = (Graph*)malloc(sizeof(Graph));

	G -> V = 0;
	G -> E = 0;
	G -> adj = (link **) malloc(V*sizeof(link));
	for (v = 0; v < V; v++)
		G -> adj[v] = NULL;
	return G;
}

void GRAPHinsertE(Graph *G, Edge *e) {

	G -> adj[e->v] = NEW(e->w, G -> adj[e->v]);
	G -> adj[e->w] = NEW(e->v, G -> adj[e->w]);
	G -> E++;

	if(e->w+1 > G->V)
		G -> V = e->w+1;
	if(e->v+1> G->V)
		G -> V = e->v+1;

}

void GRAPHshow(Graph *G) {
	int		v;
	link	*t;

	printf("%d vertices, %d edges\n", G -> V, G -> E);
	for (v = 0; v < G -> V; v++) {
		printf("%2d:", v+1);
		for (t = G -> adj[v]; t != NULL; t = t -> next)
			printf(" (%d)", t -> v+1);
		printf("\n");
	}
}

void GRAPHfree(Graph *G){
	int i;
	link *aux;
	for(i=0; i<G->V; i++)
		while((G->adj[i])!=NULL){
			aux = G->adj[i];
			G->adj[i] = (G->adj[i])->next;
			free(aux);
		}
	free(G->adj);
	free(G);
	return;
}
