typedef struct {int v; int w;} Edge;
Edge	EDGE(int, int);

typedef struct node *link;
struct node {int v; link next;};
typedef struct {int V; int E; link *adj;} *Graph;
link NEW(int v, link next);

Graph GRAPHinit(int);
void GRAPHinsertE(Graph, Edge);
void GRAPHshow(Graph);
void GRAPHplot(Graph, char *);
int randV(Graph);
Graph GRAPHrandE(int, int);
Graph GRAPHrandp(int, int);
