#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GraphADT.h"
#include "routing.h"
#define MAX 500000

long int countStatistics[100];
int maxHops = 0;
long int Total;
long int countStatisticsBFS[100];
int maxHopsBFS = 0;
long int TotalBFS;

void errorReading(){
  printf("Error reading or wrong input.\n");
  exit(-1);
}

void progressBar(int actual, int max) {
  int j;
  printf("\rProgress: [");
  for(j=0; j<(actual*50)/max;j++)
    printf("#");
  for(j=0; j<(50-(actual*50)/max);j++)
    printf(" ");
  printf("] %.0f%%", (int)100*((float)actual/max));
  fflush(stdout);
  return;
}

void progressBarFull(){
  int j;
  printf("\rProgress: [");
  for(j=0; j<50;j++)
    printf("#");
  printf("] %d%%", 100);
  fflush(stdout);
  printf("\n");
  return;
}

void writeBFSStatistics(char *out5) {
  int i;
  FILE *fp1;
  fp1 = fopen(out5,"w");
  //printf("no máximo um nó demora %d saltos a chegar a qualquer destino\n", maxHopsBFS);
  for(i = 1; i <= maxHopsBFS; i++){
    fprintf(fp1, "%d hops = %ld\n", i, countStatisticsBFS[i]);
  }
  fprintf(fp1, "Total = %ld\n", TotalBFS);
  fclose(fp1);
  return;
}

void writeCommercialStatistics(char *out4){
  int i;
  FILE *fp;
  fp = fopen(out4,"w");
  for(i = 1; i <= maxHops; i++){
	  fprintf(fp, "%d hops = %ld\n", i, countStatistics[i]);
	}
  fprintf(fp, "Total = %ld\n", Total);
  fclose(fp);
  return;
}

void printSpace(){
  printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main(int argc, char *argv[]){

  if (argc != 2) {
    printf("Usage: getpath <infile>.\n");
    exit(-1);
  }
  int i;
  char name[246];
  strcpy(name, argv[1]);
  char *out1, *out2, *out3, *out4, *out5;
  int opt1=-1, opt3=-1, out=0;
  int opt2=-1;
  clock_t begin =clock();


  int connected=0;

  out1 = (char*)malloc(sizeof(name)+sizeof(".path"));
  out2 = (char*)malloc(sizeof(name)+sizeof(".nhopspath"));
  out3 = (char*)malloc(sizeof(name)+sizeof(".nhops"));
  out4 = (char*)malloc(sizeof(name)+sizeof(".statistics"));
  out5 = (char*)malloc(sizeof(name)+sizeof(".statisticsBFS"));
  sprintf(out1, "%s.path", name);
  sprintf(out2, "%s.nhopspath", name);
  sprintf(out3, "%s.nhops", name);
  sprintf(out4, "%s.statistics", name);
  sprintf(out5, "%s.statisticsBFS", name);

  printSpace();
  Graph *G = GRAPHinit(MAX);
  readFile(name, G);
  int *vetor = NULL;

  printf("Completed reading file.\n");
  //GRAPHshow(G);
  connected = isGraphComercialConnected(G);
  if(connected)
    printf("Graph is commercial connected.\n");
  else
    printf("Graph is not commercial connected.\n");

  printf("---------------------------------------------------------------------\n");
  printf("------------------------------WELCOME!-------------------------------\n");
  printf("---------------------------------------------------------------------\n");
  while(!out){
    for(i=0;i<100;i++){
      countStatistics[i] = 0;
      countStatisticsBFS[i] = 0;
    }
    Total = 0;
    TotalBFS=0;
    maxHops=0;
    maxHopsBFS=0;
    printf("What do you want to do?\n1. Get commercial paths types\n2. Get path types and number of hops in elected route\n3. Run a BFS over the graph\n4. Everything\n5. Exit\nOption: ");
    if(scanf("%d", &opt1)!=1)
      errorReading();
    if(opt1!=5){
      if(opt1!=1){
        printf("Every AS to every AS?\n1. Yes\n2. No\nOption: ");
        if(scanf("%d", &opt2)!=1)
          errorReading();
      }
      if(opt2==2||opt1==1){
        printf("Destiny AS: ");
        if(scanf("%d", &opt3)!=1)
          errorReading();
      }else{
        opt3 = 0;
      }
      if(opt1==4){
        begin = clock();
        if(opt2==2){
          progressBar(0, 3);
          vetor = getNodePathType(G, opt3, connected, out1, 1);
          progressBar(1, 3);
          bestComercialRoute(G, opt2, out2, vetor, 1);
          progressBar(2, 3);
          getSmallPath(G, opt3, out3, 1);
          progressBarFull();
          printf("Wrote path results to file %s, %s and %s.\n", out1, out2, out3);
        }
        else{
          for(i = 0; i<G->V; i++){
            if(G->adj[i]!=NULL){
              if(i%(500)==0)
                progressBar(i, G->V);
              vetor = getNodePathType(G, i+1, connected, out1, 0);
              bestComercialRoute(G, i+1, out2, vetor, 0);
              getSmallPath(G, i+1, out3, 0);
            }
          }
          progressBarFull();
        }
        writeCommercialStatistics(out4);
        writeBFSStatistics(out5);
        printf("Wrote statistics to file %s and %s.\n", out4, out5);
      }else{
        if(opt1==3){
          begin = clock();
          if(opt2==2){
            getSmallPath(G, opt3, out3, 1);
            printf("Wrote BFS result to file %s.\n", out3);
          }
          else{
            for(i = 0; i<G->V; i++){
              if(G->adj[i]!=NULL){
                if(i%(500)==0)
                  progressBar(i, G->V);
                getSmallPath(G, i+1, out3, 0);
              }
            }
            progressBarFull();
          }
          writeBFSStatistics(out5);
          printf("Wrote BFS statistics to file %s.\n", out5);
        }
        if(opt1==2){
          begin = clock();
          if(opt2==2){
            progressBar(0, 2);
            vetor = getNodePathType(G, opt3, connected, out1, 1);
            progressBar(1, 2);
            bestComercialRoute(G, opt2, out2, vetor, 1);
            progressBarFull();
            printf("Wrote path results to file %s and %s.\n", out1, out2);
          }
          else{
            for(i = 0; i<G->V; i++){
              if(G->adj[i]!=NULL){
                if(i%(500)==0)
                  progressBar(i, G->V);
                vetor = getNodePathType(G, i+1, connected, out1, 0);
                bestComercialRoute(G, i+1, out2, vetor, 0);
              }
            }
            progressBarFull();
          }
          writeCommercialStatistics(out4);
          printf("Wrote commercial statistics to file %s.\n", out4);
        }
      }
      if(opt1==1){
        begin = clock();
        progressBar(0, 1);
        vetor = getNodePathType(G, opt3, connected, out1, 1);
        progressBarFull();
        printf("Wrote commercial path type to file %s.\n", out1);
        free(vetor);
      }
      clock_t end = clock();
      double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
      printf("Running time = %lf seconds.\n", time_spent);

    }else if(opt1==5){
      out=1;
    }
    printf("------------------------------COMPLETED-----------------------------\n\n\n\n\n");
  }

  GRAPHfree(G);
  free(out1);
  free(out2);
  free(out3);
  free(out4);
  free(out5);

  exit(0);
}
