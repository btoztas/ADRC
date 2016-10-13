#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256


int main(){

  char Symbols[MAX] = {"qwertyuiop"};
  Code *Code;
  Tree *t;

  readFileS(Symbols);
  printf("%s\n",Symbols);
  
  t = makeTree(Symbols, strlen(Symbols));
  Code = initCode(strlen(Symbols));
  GenereteCode(t->root, Code);
  printCode(Code, strlen(Symbols));

  exit(0);
}
