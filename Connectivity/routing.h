typedef struct _link{
  int v;
  struct _link *next;
} link;

typedef struct _fifo{
  int n;
  link *q;
  link *last;
} FIFO;

FIFO *initFIFO();
void addFIFO(FIFO *f, int v);
void removeFIFO(FIFO *f, int *v);
int emptyFIFO(FIFO *f);
void freeFIFO(FIFO *f);
