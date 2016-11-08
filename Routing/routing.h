typedef struct _Node{
  int v;
  int t;
  int nhops;
  int next;
} Node;

typedef struct _heap{
  int size;                     /* max size of the heap. */
  Node **q;               /* An array of Items. */
} Heap;

typedef struct _fifo{
  int n;
  link *q;
  link *last;
} FIFO;

typedef struct _QUEUE{
  FIFO *c, *r, *p;
} QUEUE;

void getNodePathType(Graph *G, int s, char *outfile);

int modeling(int A, int a);
void printHeap(Heap *h);
char *numToType(int n);
void fixHeapUp(Heap *h);
void addToHeap(Node *n, Heap *h);
void fixHeapDown(Heap *h);
Node *removeFromHeap(Heap * h);
void bestComercialRoute(Graph *Network, int destiny_id, char *outfile);
void Disjkstra(Graph *Network, Node **path, int destiny_id);
Heap *initHeap(int size);
void readFile(char *fileName, Graph *G);

FIFO *initFIFO();
void addFIFO(FIFO *f, int v, int t);
void removeFIFO(FIFO *f, int *v, int *t);
int emptyFIFO(FIFO *f);
void freeFIFO(FIFO *f);
