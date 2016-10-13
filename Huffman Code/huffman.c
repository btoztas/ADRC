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
  Code *Code;

  readFile(Symbols, Freq);
  Code = initCode(strlen(Symbols));
  HuffmanCode(Symbols, Freq, Code);
  printCode(Code, strlen(Symbols));

  exit(0);
}
