#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256

int main(){

  char Symbols[MAX];
  int i, j, k;
  float Freq[MAX];
  char readString[256];
  char file[20];
  char OutString[256];
  FILE *fp = NULL;
  Code *Code;
  
  k=0;
  
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
  
  for(j=0;j<100;j++){
		  for(i=0;strcmp(readString,"y")!=0&&strcmp(readString,"n")!=0;i++){
			if(j==0)printf("Predente descoodificar algum código? [y/n]\n");
			else printf("Predente descoodificar mais algum código? [y/n]\n");
			fgets(readString, 20, stdin);
			readString[strlen(readString)-1] = '\0';
		  }
		  
		  if(strcmp(readString,"n")==0) exit(-1);

		  printf("Introduza o nome do ficheiro que contém o código:\n");
		  
		  for(i=0;k == 0;i++){
			if(i>0)printf("Indroduza um conjunto de bits para descoodificar:\n");
			fgets(readString, 246, stdin);
			readString[strlen(readString)-1] = '\0';
			k = checkIfBitString(readString);
		  }
  }
  
  Decode
  exit(0);
}
