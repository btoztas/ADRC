#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256


int main(){

  char Symbols[MAX] = {"absckdkdkdk"};
  Code *Code;
  Tree *t;
  //readFile

  t = makeTree(Symbols, strlen(Symbols));
  printTree(t->root);
  Code = initCode(strlen(Symbols));
  GenereteCode(t->root, Code);
  printCode(Code, strlen(Symbols));

  exit(0);
}
