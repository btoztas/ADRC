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
  while(!leave){
    printf("What do you want to do?\n1. Select two nodes\n2. All node to all nodes\n3. Exit\nOption: ");
    if(scanf("%d", &opt)!=1)
      errorReading();
    if(opt==1){
      printf("Source: ");
      scanf("%d", &s);
      printf("Destiny: ");
      scanf("%d", &t);
      printf("Result: %d\n",EdKarp(G, s--, t--));
    }
    else if(opt==2){
      printf("Option under construction... Sorry for the delay.\n");
    }
    else if(opt==3){
      printf("Goodbye!\n");
      leave = 1;
    }
    else{
      printf("Select a valid option.\n");
    }
    printf("\n\n\n");
  }
  GRAPHfree(G, MAX);
  exit(1);
}
