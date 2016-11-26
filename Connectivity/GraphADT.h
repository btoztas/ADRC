typedef struct _edge{
  int v;
  int w;
} Edge;

typedef struct _Graph{
  int V;
  int E;
  int **adj;
} Graph;

Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *, Edge *);
void GRAPHshow(Graph*);
void GRAPHfree(Graph*);
