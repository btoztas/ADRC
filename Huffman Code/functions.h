typedef struct _Node {
  struct _Node *l;
  struct _Node *r;
  char d;
  float p;
} Node;

typedef struct _Tree {
  Node *root;
} Tree;

typedef struct _Heap {
  Node **q;
  int size;
} Heap;

typedef struct _Entry{
  char d;
  char *c;
} Entry;

typedef struct _Code {
  Entry **list;
} Code;

void HuffmanCode(char *Symbols, float *Freq, Code *code);

void GenereteCode(Node *root, Code *code);

void Decode(Node *root, char *InString, char *OutString);
