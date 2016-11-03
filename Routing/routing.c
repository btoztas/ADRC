#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"
#include "routing.h"

void errorMalloc(){
  printf("Error allocating memory.\n");
  exit(-1);
}
void errorFile(){
  printf("Error opening file.\n");
  exit(-1);
}
/*
Heap *initHeap(int size){
  int i;

  Heap *h = (Heap*)malloc(sizeof(Heap));
  if(h==NULL)
    errorMalloc();

  h->q = (Node**) malloc(size*sizeof(link));
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
  while ((k > 0) && ((((h->q)[k])->t) > (((h->q)[(k-1)/2])->t)) ) {
    aux = (h->q)[k];
    (h->q)[k] = (h->q)[(k - 1) / 2];
    (h->q)[(k - 1) / 2] = aux;
    k = (k - 1) / 2;
  }
  return;
}*/

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

FIFO *initFIFO(){
  FIFO *f;
  f = (FIFO*)malloc(sizeof(FIFO));
  f->q = NULL;
  f->last = NULL;
  f->n=0;
  return f;
}

void addFIFO(FIFO *f, int v, int t){
  link *new;
  new = (link*)malloc(sizeof(link));
  new->v = v;
  new->t = t;
  new->next = NULL;

  f->last->next = new;
  f->last=new;
  f->n++;
  return;
}

void removeFIFO(FIFO *f, int *v, int *t){
  link *aux;

  *t   = (f->q)->t;
  *v   = (f->q)->v;
  aux  = f->q;
  f->q = f->q->next;
  f->n--;
  free(aux);
  return;
}

int emptyFIFO(FIFO *f){
  if(f->n!=0)
    return 0;
  return 1;
}

void freeFIFO(FIFO *f){
  link *aux;
  while(f->q!=NULL){
    aux = f->q;
    f->q=f->q->next;
    free(aux);
  }
  free(f);
}
