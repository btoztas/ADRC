#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GraphADT.h"
#include "routing.h"
#define MAX 256

int main(int argc, char *argv[]){

  if (argc < 2) {
    printf("You must pass the file name as an argument!\nUsage: alg1 <filename>.\n");
    exit(-1);
  }

  Graph *G = GRAPHinit(MAX);
  readFile(argv[1], G);


  exit(0);
}
