#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphADT.h"
#include "routing.h"
#include "connectivity.h"

#define MAX 100

void errorMalloc(){
  printf("Error allocating memory.\n");
  exit(-1);
}
void errorFile(){
  printf("Error opening file.\n");
  exit(-1);
}

void readFile(char *fileName, Graph *G){
  FILE *fp;
  Edge *e;
  e = (Edge*)malloc(sizeof(Edge));
  fp = fopen (fileName,"r");
  if (fp==NULL)
    errorFile();
  else
    while(fscanf(fp, "%d %d", &(e->v), &(e->w))!=-1){
      e->v--;
      e->w--;
      printf("Inserted edge %d-%d.\n", e->v, e->w);
      GRAPHinsertE(G, e);
    }
  free(e);
  fclose (fp);
}


int main(int argc, char *argv[]){

  if (argc != 2) {
    printf("Usage: getpath <infile>.\n");
    exit(-1);
  }
  printf("Initiating graph\n");
  Graph *G = GRAPHinit(MAX);
  printf("Reading file...\n");
  readFile(argv[1], G);
  printf("Show Graph\n");
  GRAPHshow(G);
  GRAPHfree(G);
  exit(1);
}
