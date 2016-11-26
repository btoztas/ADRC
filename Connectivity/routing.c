#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "GraphADT.h"
#include "routing.h"


FIFO *initFIFO(){
  FIFO *f;
  f = (FIFO*)malloc(sizeof(FIFO));
  f->q = NULL;
  f->last = NULL;
  f->n = 0;
  return f;
}

void addFIFO(FIFO *f, int v){
  link *new;
  new = (link*)malloc(sizeof(link));
  new->v = v;
  new->next = NULL;
  if(f->n==0){
    f->last = f->q = new;
  }else{
    f->last->next = new;
    f->last=new;
  }
  f->n++;
  return;
}

void removeFIFO(FIFO *f, int *v){
  link *aux;
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


int BFS(Graph *G, int *path, int source, int destiny){
	FIFO *fifo = initFIFO();
	int actualnode;
	int i;
  int found=0;

  for(i=0; i<G->V; i++)
    path[i]=-1;

  path[destiny]=destiny;

	addFIFO(fifo, destiny);
  while(fifo->n > 0 && !found){
		//printf("Removing AS\n");
		removeFIFO(fifo, &actualnode);
		//printf("Removed AS %d\n", actualnode+1);
		for(i = 0; i<G->V && !found; i++){
      if(G->adj[actualnode][i]){
        //printf("Checking AS %d\n", aux->v+1);
  			if(path[i] == -1){
          path[i]=actualnode;
          if(i == source)
            found = 1;
          else
  				  addFIFO(fifo, i);
        }
      }
		}
    //printf("\n");
	}
  freeFIFO(fifo);
  return found;
}
