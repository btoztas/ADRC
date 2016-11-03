#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"
#include "routing.h"
#define MAX 500000



void getNodePathType(Graph *G, int s, char *outfile){
  FIFO *f = initFIFO();

  //printf("Initiated FIFO\n");
  int *V;
  int *T;
  int u, v, t;
  link *aux;
  int i;
  V = (int *)calloc(G->V,sizeof(int));
  T = (int *)calloc(G->V,sizeof(int));
  s--;
  T[s] = 3;

  addFIFO(f, s, T[s]);
  //printf("Added node %d to FIFO\n", s+1);
  while(!emptyFIFO(f)){
    removeFIFO(f, &u, &t);
    //printf("Removed node %d type %d from FIFO\n", u+1, t);
    aux = G->adj[u];
    while(aux != NULL){
      v = aux->v;
      if(V[v] == 0)
        if(modeling(aux->t, T[u]) > T[v]){
          T[v] = modeling(aux->t, T[u]);
          //printf("Added node %d to FIFO\n", v+1);
          addFIFO(f, v, T[v]);
        }
      aux=aux->next;
    }
    V[u] = 1;
  }
  FILE *fp;
  fp = fopen (outfile,"w");
  if (fp!=NULL)  {
    for(i = 0; i < G->V; i++) {
      fprintf(fp, "Node %d - %d\n", i+1, T[i]);
    }
    fclose (fp);
  }
  free(T);
  free(V);
  freeFIFO(f);
  return;
}

int main(int argc, char *argv[]){

  if (argc < 4) {
    printf("You must pass the file name as an argument!\nUsage: alg1 <infile> <outfile> <id_destiny>.\n");
    exit(-1);
  }

  Graph *G = GRAPHinit(MAX);
  printf("Initiated graph.\n");
  readFile(argv[1], G);
  printf("Completed reading file.\n");
  //GRAPHshow(G);
  getNodePathType(G, atoi(argv[3]), argv[2]);

  GRAPHfree(G);
  exit(0);
}
