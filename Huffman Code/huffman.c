#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "random.h"

typedef struct _Node {
  struct _Node *l;
  struct _Node *r;
  char d;
  int p;
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
  Entry *list;
} Code;

void errorMalloc(){
  printf("Error allocating memory\n");
  exit(-1);
}

Node *newNode(char d, int p){
  Node *n = (Node*) malloc(sizeof(Node));
  if(n==NULL)
    errorMalloc();
  n->d=d;
  n->p=p;
  n->l=n->r=NULL;
  return n;
}

Tree *initTree(){
  Tree *t = (Tree*) malloc(sizeof(Tree));
  if(t==NULL)
    errorMalloc();
  t->root = NULL;
  return t;
}

Heap *initHeap(int size){
  int i;
  Heap *h = (Heap*) malloc(sizeof(Heap));
  if(h==NULL)
    errorMalloc();
  h->q = (Node**) malloc(size*sizeof(Node));
  if(h->q==NULL)
    errorMalloc();
  for(i=0; i<size; i++)
    h->q[i] = NULL;
  h->size = 0;
  return h;
}

void fixHeapUp(Heap *h){
  Node *aux;
  int k = h->size-1;
  while ((k > 0) && ((((h->q)[k])->p) < (((h->q)[(k-1)/2])->p)) ) {
    aux = (h->q)[k];
    (h->q)[k] = (h->q)[(k - 1) / 2];
    (h->q)[(k - 1) / 2] = aux;
    k = (k - 1) / 2;
  }
  return;
}

void addToHeap(Node *n, Heap *h){
  h->q[h->size] = n;
  h->size++;
  if(h->size!=1)
    fixHeapUp(h);
  return;
}

void fixHeapDown(Heap *h){

  printf("Starting fixHeapDown\n");
  int i=0, k=0;
  int found=0;
  Node *aux;

  if(h->size>1){
    while (i < h->size && !found) {
      k = 2*i+1;
      if(k<h->size){
        if(k+1<h->size){
          if( ((((h->q)[i])->p) < (((h->q)[i*2+1])->p) && (((h->q)[i])->p) < (((h->q)[i*2+2])->p)) )
            found = 1;
          else{
            aux = (h->q)[i];
            k = ((h->q)[i*2+1])->p < ((h->q)[i*2+2])->p ? i*2+1 : i*2+2;

            printf("Vou trocar o %c-%d com o %c-%d\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
            (h->q)[i] = (h->q)[k];
            (h->q)[k] = aux;
            i = k;

          }
        }
        else if( (h->q)[i]->p < (h->q)[i*2+1]->p)
          found = 1;
        else{
          aux = (h->q)[i];

          printf("Vou trocar o %c-%d com o %c-%d\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
          (h->q)[i] = (h->q)[k];
          (h->q)[k] = aux;
          i = k;
        }
      }else
        found=1;
    }
  }
  return;
}

Node *removeFromHeap(Heap * h){
  Node *n;
  if (h->size > 0) {
    n = (h->q)[0];
    (h->q)[0] = (h->q)[h->size - 1];
    (h->q)[h->size - 1] = NULL;
    h->size--;
    fixHeapDown(h);
    return n;
  }
  return NULL;
}


void printHeap(Heap *h){
  int i;
  if(h->size==0){
    printf("Heap is empty.\n");
  }else{
    for(i=0; i<h->size; i++)
      printf("%c %d\n", (h->q[i])->d,(h->q[i])->p);
    printf("\n");
  }
  return;
}

Heap *HuffmanCode(char *Symbols, int *Freq){

  int size = strlen(Symbols);
  int i;
  printf("Creating a Heap of maximum size %d\n", size);
  Heap *h = initHeap(size);
  for(i=0; i<10 ;i++)
    addToHeap(newNode(Symbols[i], Freq[i]),h);

  return h;

}

void heapTest(){

  int i=0;
  Node *n;
  char Symbols[10] = "abcdefghij";
  int Freq[10] = {30, 1, 15, 10, 10, 5, 3, 20, 5, 1};
  Heap *h = HuffmanCode(Symbols, Freq);

  for (i = 0; i < 10; i++){
    printf("Iteracao numero %d:\nEstado do Heap:\n",i+1);
    printHeap(h);
    n=removeFromHeap(h);
    printf("Node retirado:\n%c %d\n-----------------\n",n->d, n->p);
  }
}

int main(){

  heapTest();

  exit(0);
}
