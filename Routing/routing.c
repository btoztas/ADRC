#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"

#define MAX 256

typedef struct _heap{
  int size;                     /* max size of the heap. */
  link **q;               /* An array of Items. */
} Heap;

void errorMalloc(){
  printf("Error allocating memory.\n");
  exit(-1);
}
void errorFile(){
  printf("Error opening file.\n");
  exit(-1);
}

Heap *initHeap(int size){
  int i;

  Heap *h = (Heap*)malloc(sizeof(Heap));
  if(h==NULL)
    errorMalloc();

  h->q = (link**) malloc(size*sizeof(link));
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


void readFile(char *fileName, Graph *G){
  FILE *fp;
  Edge *e;
  e = (Edge*)malloc(sizeof(Edge));
  fp = fopen (fileName,"r");
  if (fp==NULL)
    errorFile();
  else
    while(fscanf(fp, "%d %d %d", &(e->v), &(e->w), &(e->t)))
      GRAPHinsertE(G, e);
  free(e);
  fclose (fp);
}


int main(){


  exit(0);
}
