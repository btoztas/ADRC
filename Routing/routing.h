typedef struct _Node{
  int v;
  int t;
  int nhops;
} Node;

typedef struct _heap{
  int size;                     /* max size of the heap. */
  link **q;               /* An array of Items. */
} Heap;

void readFile(char *fileName, Graph *G);
