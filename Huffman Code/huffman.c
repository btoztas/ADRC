#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256

int main(){

  char Symbols[MAX];
  int i;
  float Freq[MAX];
  char file[20];
  FILE *fp = NULL;
  Code *Code;
  
  
  
  printf("Introduza o nome do ficheiro:\n");
  
  for(i=0;fp==NULL;i++){
	if(i>0)printf("Indroduza um nome de ficheiro que exista:\n");
	fgets(file, 20, stdin);
	file[strlen(file)-1] = '\0';
	fp = fopen(file, "r");
  }
  
  fclose(fp);
  
  readFile(Symbols, Freq, file);
  Code = initCode(strlen(Symbols));
  HuffmanCode(Symbols, Freq, Code);
  printCode(Code, strlen(Symbols));
  

  exit(0);
}
