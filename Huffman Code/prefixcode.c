#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256


int main(){

  char Symbols[MAX] = {"qwertyuiop"};
  char bitstring[MAX];
  char word[MAX];
  Code *Code;
  Tree *t;
  int leave = 0;
  char option;

  readFileS(Symbols);
  printf("%s\n",Symbols);

  t = makeTree(Symbols, strlen(Symbols));
  Code = initCode(strlen(Symbols));
  GenereteCode(t->root, Code);
  printCode(Code, strlen(Symbols));

  while (!leave) {
    printf("OPTIONS:\nD - DECODE\nR - RELOAD FILE\nE - EXIT\n");
    scanf("%c\n", &option);
    switch (option) {
      case 'D':
        scanf("%s\n", bitstring);
        Decode(t->root, bitstring, word);
        printf("%s\n",word);
        break;
      case 'R':
        break;
      case 'E':
        leave=1;
        break;
      default:
        printf("Inserted a valid option\n");
        break;
    }
  }

  exit(0);
}
