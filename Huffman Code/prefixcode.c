#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256


int main(){

  char Symbols[MAX];
  char readString[MAX];
  char OutString[MAX];
  char file[20];
  FILE *fp;
  /*char word[MAX];*/
  Code *Code;
  Tree *t;
  /*int leave = 0;
  char option;*/
  int i, j, k;
  
  k=0;
  
  printf("Introduza o nome do ficheiro:\n");
  
  for(i=0;fp==NULL;i++){
	if(i>0)printf("Indroduza um nome de ficheiro que exista:\n");
	fgets(file, 20, stdin);
	file[strlen(file)-1] = '\0';
	fp = fopen(file, "r");
  }
  
  fclose(fp);
  
  readFileS(Symbols, file);
  printf("%s\n",Symbols);

  t = makeTree(Symbols, strlen(Symbols));
  Code = initCode(strlen(Symbols));
  GenereteCode(t->root, Code);
  printCode(Code, strlen(Symbols));
  
  for(j=0;j<100;j++){
		  for(i=0;strcmp(readString,"y")!=0&&strcmp(readString,"n")!=0;i++){
			if(j==0)printf("Predente descoodificar algum código? [y/n]\n");
			else printf("Predente descoodificar mais algum código? [y/n]\n");
			fgets(readString, 20, stdin);
			readString[strlen(readString)-1] = '\0';
		  }
		  
		  if(strcmp(readString,"n")==0){
			printf("goodbye\n");
			exit(-1);
		  }
		  printf("Indroduza um conjunto de bits para descoodificar:\n");
		  
		  for(i=0;k == 0;i++){
			if(i>0)printf("Indroduza um conjunto de bits:\n");
			fgets(readString, 246, stdin);
			readString[strlen(readString)-1] = '\0';
			k = checkIfBitString(readString);
		  }
		  
		  Decode(t->root, readString, OutString);
		  k=0;
  }
  
  

  /*while (!leave) {
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
  }*/

  exit(0);
}
