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
  FILE *fp=NULL;
  Code *Code;
  Tree *t;
  int i, j, k;

  k=0;

  printf("File name:\n");

  for(i=0;fp==NULL;i++){
	  if(i>0)
      printf("No file named after %s. New file name:\n", file);
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
  			if(j==0)
          printf("Do you want do decode a bitstring? [y/n]\n");
  			else
          printf("Do you want to decode any other bitstring? [y/n]\n");
  			fgets(readString, 20, stdin);
			  readString[strlen(readString)-1] = '\0';
		  }

		  if(strcmp(readString,"n")==0){
  			printf("goodbye\n");
  			exit(-1);
		  }
		  printf("Write a bitstring do be decoded:\n");

		  for(i=0;k == 0;i++){
  			if(i>0)
          printf("Write a bitstring:\n");
  			fgets(readString, 246, stdin);
  			readString[strlen(readString)-1] = '\0';
  			k = checkIfBitString(readString);
		  }

		  Decode(t->root, readString, OutString);
		  k=0;
  }

  exit(0);
}
