#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"
#include "routing.h"
#define MAX 500000

int main(int argc, char *argv[]){

  if (argc != 3) {
    printf("Usage: getpath <infile> <id_destiny>.\n");
    exit(-1);
  }

  char *out1, *out2;
  char name[246];
  strcpy(name, argv[1]);
  out1 = (char*)malloc(sizeof(name)+sizeof(".pathtype"));
  out2 = (char*)malloc(sizeof(name)+sizeof(".nhops"));
  sprintf(out1, "%s.pathtype", name);
  sprintf(out2, "%s.nhops", name);

  Graph *G = GRAPHinit(MAX);
  readFile(name, G);
  printf("Completed reading file.\n");
  //GRAPHshow(G);

  getNodePathType(G, atoi(argv[2]), out1);
  bestComercialRoute(G, atoi(argv[2]), out2);
  printf("Wrote results to file %s and %s.\n", out1, out2);

  GRAPHfree(G);
  free(out1);
  free(out2);
  exit(0);
}
