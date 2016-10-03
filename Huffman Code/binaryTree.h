typedef struct _Node {
  struct _Node *l;
  struct _Node *r;
  int d;
} Node;


typedef struct Tree* {
  Node *root;
} Tree;


Tree *initTree();
