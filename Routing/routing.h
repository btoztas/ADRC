typedef struct _Node{
  int v;
  int t;
  int nhops;
  int next;
  struct _Node *next_node;
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

typedef struct _queue{
  FIFO *c, *r, *p;
} QUEUE;

typedef struct _fifo2{
  int n;
  Node *q;
  Node *last;
} FIFO2;

typedef struct _queue2{
  FIFO2 *c, *r, *p;
} QUEUE2;


typedef struct _listnode{

  int v;
  struct _listnode *next;

} LISTNODE;

typedef struct _list{

  int n;
  LISTNODE *first;
  LISTNODE *last;

} LIST;

int isGraphComercialConnected(Graph *G);
int *getNodePathType(Graph *G, int s, int connected, char *outfile, int write);

int modeling(int A, int a);

FIFO *initFIFO();
void addFIFO(FIFO *f, int v, int t);
void removeFIFO(FIFO *f, int *v, int *t);
int emptyFIFO(FIFO *f);
void freeFIFO(FIFO *f);

void getSmallPath(Graph *Network, int destiny, char *outfile, int write);
void bestComercialRoute(Graph *Network, int destiny_id, char *outfile, int *vetor, int write);
void Dijsktra(Graph *Network, Node **path, int destiny_id, int *type);

void readFile(char *fileName, Graph *G);
