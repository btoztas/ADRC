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

void errorReading(){
  printf("Error reading or wrong input.\n");
  exit(-1);
}

void progressBar(int actual, int max) {
  int j;
  printf("\rProgress: [");
  for(j=0; j<(actual*50)/max;j++)
    printf("#");
  for(j=0; j<(50-(actual*50)/max);j++)
    printf(" ");
  printf("] %.0f%%", (int)100*((float)actual/max));
  fflush(stdout);
  return;
}

void progressBarFull(){
  int j;
  printf("\rProgress: [");
  for(j=0; j<50;j++)
    printf("#");
  printf("] %d%%", 100);
  fflush(stdout);
  printf("\n");
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
    while(fscanf(fp, "%d %d", &(e->v), &(e->w))!=-1){
      e->v--;
      e->w--;
      //printf("Inserted edge %d-%d.\n", e->v, e->w);
      GRAPHinsertE(G, e);
    }
  free(e);
  fclose (fp);
}

void  saveStatistics(int *nedges, int size, char* out) {
  FILE *fp;
  fp = fopen(out,"w");
  //printf("no máximo um nó demora %d saltos a chegar a qualquer destino\n", maxHopsBFS);
  for(int i = 1; i < size; i++){
    printf("%d edges = %d\n", i, nedges[i]);
    fprintf(fp,"%d edges = %d\n", i, nedges[i]);
  }
  fclose(fp);
}

int main(int argc, char *argv[]){
  int leave = 0;
  int s, t;
  int opt;
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

  int *nedges;
  int maxEdges;
  int result;
  nedges = malloc(G->V*sizeof(int));
  char name[255];
  strcpy(name, argv[1]);
  char *out = (char*)malloc(sizeof(name)+sizeof(".out"));
  sprintf(out, "%s.path", name);
  while(!leave){
    for (int i = 0; i < G->V; i++) {
      nedges[i]=0;
    }
    maxEdges=0;
    printf("What do you want to do?\n1. Select two nodes\n2. All node to all nodes\n3. Exit\nOption: ");
    if(scanf("%d", &opt)!=1)
      errorReading();
    if(opt==1){
      printf("Source: ");
      scanf("%d", &s);
      printf("Destiny: ");
      scanf("%d", &t);
      printf("Result: %d\n",EdKarp(G, s-1, t-1));
    }
    else if(opt==2){
      for (int i = 0; i < G->V; i++)
        for (int j = 0; j < G->V; j++)
          if(j!=i){
            result=EdKarp(G, i, j);
            nedges[result]++;
            if(result > maxEdges)
              maxEdges=result;
            progressBar(i, G->V);
          }
      progressBarFull();
      saveStatistics(nedges, maxEdges, out);
      printf("Saved results to %s\n", out);
    }else if(opt==3){
      printf("Goodbye!\n");
      leave = 1;
    }
    else{
      printf("Select a valid option.\n");
    }
    printf("\n\n\n");
  }
  free(nedges);
  free(out);
  GRAPHfree(G, MAX);
  exit(1);
}
