#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphADT.h"

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
    while(fscanf(fp, "%d %d %d", &(e->v), &(e->w), &(e->p))
      GRAPHinsertE(G, e);

  free(e);
  fclose (fp);
}
