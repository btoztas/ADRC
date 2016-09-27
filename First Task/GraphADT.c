#include <stdio.h>
#include <stdlib.h>
#include "GraphADT.h"
#include "random.h"

Edge EDGE(int v, int w) {
	Edge	*eptr = (Edge *) malloc(sizeof(Edge)) ;

	eptr -> v = v;
	eptr -> w = w;
	return *eptr;
}

link NEW(int v, link next) {
	link	x = (link) malloc(sizeof(*x));

	x -> v = v;
	x -> next = next;
	return x;
}

Graph GRAPHinit(int V) {
	int		v;
	Graph	G = (Graph) malloc(sizeof *G);

	G -> V = V;
	G -> E = 0;
	G -> adj = (link *) malloc(V * sizeof(link));
	for (v = 0; v < V; v++)
		G -> adj[v] = NULL;
	return G;
}

void GRAPHinsertE(Graph G, Edge e) {
	int		v = e.v;
	int		w = e.w;

	G -> adj[v] = NEW(w, G -> adj[v]);
	G -> adj[w] = NEW(v, G -> adj[w]);
	G -> E++;
}

void GRAPHshow(Graph G) {
	int		v;
	link	t;

	printf("%d vertices, %d edges\n", G -> V, G -> E);
	for (v = 0; v < G -> V; v++) {
		printf("%2d:", v);
		for (t = G -> adj[v]; t != NULL; t = t -> next) 
			printf(" %2d", t -> v);
		printf("\n");
	}
}

void GRAPHplot(Graph G, char *filename) {
	FILE	*ofp;
	int		v;
	link	t;
	
	ofp = fopen(filename, "w");
	fprintf(ofp, "%s", "size 12 12\n");
	randini();
	for (v = 0; v < G -> V; v++) {
		fprintf(ofp, "%s%6.1f%6.1f\n", "amove ", rand_unif(2,13), rand_unif(3,13));
		fprintf(ofp, "%s\n", "circle 0.12 fill black");
		fprintf(ofp, "%s%d\n", "save v", v);
	}
	for (v = 0; v < G -> V; v++) 
		for (t = G -> adj[v]; t != NULL; t = t -> next) 
			fprintf(ofp, "%s%d%s%d%s\n", "join v", v, ".cc - v", t -> v, ".cc");
		
	fclose(ofp);
}

Graph GRAPHrandp(int V, int E) {
	int		i, j;
	double	p = 2.0 * E / (V * (V - 1));
	Graph	G = GRAPHinit(V);

	randini();
	for (i = 0; i < V; i++)
			for (j = 0; j <i; j++)
				if (randlcg(1) < p)
					GRAPHinsertE(G, EDGE(i, j));
	return G;
}

		
