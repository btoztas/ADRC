#include <stdio.h>
#include <stdlib.h>
#include "GraphADT.h"

link *NEW(int v, int t, link *next) {

	link	*x;
	x = (link*)malloc(sizeof(link));
	x -> v = v;
	x -> t = t;
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
	int		v = e->v;
	int		w = e->w;
	int   t_v = e->t;
	int   t_w;

	if(w+1 > G->V)
		G -> V = w+1;
	if(v > G->V)
		G -> V = v+1;

	if(t_v == 2)
		t_w = 2;
	else
		t_w = t_v == 3 ? 1 : 3;


	G -> adj[w] = NEW(v, t_w, G -> adj[w]);
	G -> E++;

}

void GRAPHshow(Graph *G) {
	int		v;
	link	*t;

	printf("%d vertices, %d edges\n", G -> V, G -> E);
	for (v = 0; v < G -> V; v++) {
		printf("%2d:", v+1);
		for (t = G -> adj[v]; t != NULL; t = t -> next)
			printf(" (%d,%d)", t -> v+1, t->t);
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
