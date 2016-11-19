typedef struct _edge{
  int v;
  int w;
} Edge;

typedef struct _link{
  int v;
  struct _link *next;
} link;

typedef struct _Graph{
  int V;
  int E;
  link **adj;
} Graph;

link *NEW(int v, link *next);
Graph *GRAPHinit(int);
void GRAPHinsertE(Graph *, Edge *);
void GRAPHshow(Graph*);
void GRAPHfree(Graph*);
