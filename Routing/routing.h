typedef struct _Node{
  int v;
  int t;
  int nhops;
} Node;

typedef struct _heap{
  int size;                     /* max size of the heap. */
  link **q;               /* An array of Items. */
} Heap;

typedef struct _fifo{
  int n;
  link *q;
  link *last;
} FIFO;

void readFile(char *fileName, Graph *G);

FIFO *initFIFO();
void addFIFO(FIFO *f, int v, int t);
void removeFIFO(FIFO *f, int *v, int *t);
int emptyFIFO(FIFO *f);
void freeFIFO(FIFO *f);

int modeling(int A, int a);
