#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"
#include "routing.h"
#define MAX 256



void getNodePathType(Graph *G, int s){
  FIFO *f = initFIFO();
  int V[MAX]={0};
  int T[MAX]={0};
  int u;
  int t;
  link *aux;

  T[s] = 3;

  addFIFO(f, s, T[s]);
  while(!emptyFIFO(f)){
    removeFIFO(f, &u, &t);
    aux = G->adj[u];
    while(aux->next!=NULL){
      
      aux=aux->next;
    }

  }


  freeFIFO(f);
  return;
}


int main(int argc, char *argv[]){

  if (argc < 3) {
    printf("You must pass the file name as an argument!\nUsage: alg1 <filename> <id_destiny>.\n");
    exit(-1);
  }

  Graph *G = GRAPHinit(MAX);
  readFile(argv[1], G);

  getNodePathType(G, atoi(argv[2]));

  GRAPHfree(G, MAX);
  exit(0);
}
