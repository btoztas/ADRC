#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256

int main(){

  char Symbols[MAX];
  float Freq[MAX];
  char file[20];
  Code *Code;

  printf("Introduza o nome do ficheiro:\n");
  fgets(file, 20, stdin);
  file[strlen(file)-1] = '\0';
  readFile(Symbols, Freq, file);
  Code = initCode(strlen(Symbols));
  HuffmanCode(Symbols, Freq, Code);
  printCode(Code, strlen(Symbols));

  exit(0);
}
