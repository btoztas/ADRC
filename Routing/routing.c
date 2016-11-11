#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "GraphADT.h"
#include "routing.h"

#define MAX 500000

extern int maxHops;
extern long int countStatistics[100];
extern long int Total;

extern int maxHopsBFS;
extern long int countStatisticsBFS[100];
extern long int TotalBFS;

void errorMalloc(){
  printf("Error allocating memory.\n");
  exit(-1);
}
void errorFile(){
  printf("Error opening file.\n");
  exit(-1);
}

int modeling(int A, int a){
	switch(A) {
	   case 3:
		  switch(a) {
			  case 3:
				return 3;
        break;

			  default :
			  return -1;
        break;
		  }

	   case 2:
		  switch(a) {
			  case 3:
				return 2;
        break;

			  default :
			  return -1;
        break;
		  }

	  case 1:
		  switch(a) {
			  case 0:
				return -1;
        break;

			  default:
			  return 1;
        break;
		  }
	}
  return -1;
}

char *numToType(int n){
	if (n==3)
		return "Costumer path";
	else if(n==2)
		return "Peer path";
  else if(n==1)
		return "Provider path";
	return "Unreachable";
}

FIFO *initFIFO(){
  FIFO *f;
  f = (FIFO*)malloc(sizeof(FIFO));
  f->q = NULL;
  f->last = NULL;
  f->n = 0;
  return f;
}

void addFIFO(FIFO *f, int v, int t){
  link *new;
  new = (link*)malloc(sizeof(link));
  new->v = v;
  new->t = t;
  new->next = NULL;
  if(f->n==0){
    f->last = f->q = new;
  }else{
    f->last->next = new;
    f->last=new;
  }
  f->n++;
  return;
}

void removeFIFO(FIFO *f, int *v, int *t){
  link *aux;

  *t   = (f->q)->t;
  *v   = (f->q)->v;
  aux  = f->q;
  f->q = f->q->next;
  f->n--;
  free(aux);
  return;
}

int emptyFIFO(FIFO *f){
  if(f->n!=0)
    return 0;
  return 1;
}

void freeFIFO(FIFO *f){
  link *aux;
  while(f->q!=NULL){
    aux = f->q;
    f->q=f->q->next;
    free(aux);
  }
  free(f);
}

QUEUE *initQUEUE(){
  QUEUE *q = (QUEUE *)malloc(sizeof(QUEUE));
  q->c = initFIFO();
  q->r = initFIFO();
  q->p = initFIFO();
  return q;
}

void addQUEUE(QUEUE *q, int u, int t){
  if(t==3)
    addFIFO(q->c, u, t);
  else if(t==2)
    addFIFO(q->r, u, t);
  else if(t==1)
    addFIFO(q->p, u, t);
  return;
}

void removeQUEUE(QUEUE *q, int *u, int *t){
  if(!emptyFIFO(q->c))
    removeFIFO(q->c, u, t);
  else if(!emptyFIFO(q->r))
    removeFIFO(q->r, u, t);
  else if(!emptyFIFO(q->p))
    removeFIFO(q->p, u, t);
  return;
}

int emptyQUEUE(QUEUE *q){
  if(emptyFIFO(q->c) && emptyFIFO(q->r) && emptyFIFO(q->p))
    return 1;
  return 0;
}

void freeQUEUE(QUEUE *q){
  freeFIFO(q->c);
  freeFIFO(q->r);
  freeFIFO(q->p);
  free(q);
}

FIFO2 *initFIFO2(){
  FIFO2 *f;
  f = (FIFO2*)malloc(sizeof(FIFO2));
  f->q = NULL;
  f->last = NULL;
  f->n = 0;
  return f;
}

void addFIFO2(FIFO2 *f, Node *N){
  Node *new;
  new = (Node*)malloc(sizeof(Node));
  new->v = N->v;
  new->t = N->t;
  new->next = N->next;
  new->nhops = N->nhops;
  new->next_node = NULL;
  if(f->n==0){
    f->last = f->q = new;
  }else{
    f->last->next_node=new;
    f->last=new;
  }
  f->n++;
  return;
}

Node *removeFIFO2(FIFO2 *f){
  Node *aux = f->q;
  f->q = (f->q)->next_node;
  f->n--;
  return aux;
}

int emptyFIFO2(FIFO2 *f){
  if(f->n!=0)
    return 0;
  return 1;
}

void freeFIFO2(FIFO2 *f){
  Node *aux;
  while(f->q!=NULL){
    aux = f->q;
    f->q=f->q->next_node;
    free(aux);
  }
  free(f);
}


QUEUE2 *initQUEUE2(){
  QUEUE2 *q = (QUEUE2 *)malloc(sizeof(QUEUE2));
  q->c = initFIFO2();
  q->r = initFIFO2();
  q->p = initFIFO2();
  return q;
}

void addQUEUE2(QUEUE2 *q, Node *N){
  if(N->t==3)
    addFIFO2(q->c, N);
  else if(N->t==2)
    addFIFO2(q->r, N);
  else if(N->t==1)
    addFIFO2(q->p, N);
  return;
}

Node *removeQUEUE2(QUEUE2 *q){
  if(!emptyFIFO2(q->c))
    return removeFIFO2(q->c);
  else if(!emptyFIFO2(q->r))
    return removeFIFO2(q->r);
  else if(!emptyFIFO2(q->p))
    return removeFIFO2(q->p);
  return NULL;
}

int emptyQUEUE2(QUEUE2 *q){
  if(emptyFIFO2(q->c) && emptyFIFO2(q->r) && emptyFIFO2(q->p))
    return 1;
  return 0;
}

void freeQUEUE2(QUEUE2 *q){
  freeFIFO2(q->c);
  freeFIFO2(q->r);
  freeFIFO2(q->p);
  free(q);
}
void addLIST(LIST *l, int v){

  LISTNODE *new;
  new = (LISTNODE *)malloc(sizeof(LISTNODE));
  new->v = v;
  new->next = NULL;

  if(l->n==0)
    l->first = l->last=new;
  else{
    (l->last)->next = new;
    l->last=new;
  }
  l->n++;

  return;
}

LIST *initLIST(){

  LIST *l = (LIST*)malloc(sizeof(LIST));
  l->n=0;
  l->first = NULL;
  l->last = NULL;
  return l;
}

void printLIST(LIST *l){
  LISTNODE *aux;
  for (aux=l->first; aux!=NULL; aux=aux->next)
    printf("%d ", aux->v);
  printf("\n");
}

void freeLIST(LIST *l){
  LISTNODE *aux;
  while(l->first!=NULL){
    aux = l->first;
    l->first=l->first->next;
    free(aux);
  }
  free(l);
}


int isGraphComercialConnected(Graph *G){

  LIST *l = initLIST();
  link *aux;
  int i;
  int noProviders;

  for(i=0; i<G->V; i++){
    if(G->adj[i]!=NULL){
      noProviders = 1;
      for(aux=G->adj[i]; aux!=NULL; aux=aux->next)
        if(aux->t == 3)
          noProviders=0;
      if(noProviders){
        addLIST(l, i);
      }
      noProviders=0;
    }
  }

  LISTNODE *x, *y;
  int allPairs=0;
  for(x=l->first; x!=NULL; x=x->next){
    for(y=l->first; y!=NULL; y=y->next){
      if(y->v!=x->v){
        for(aux=G->adj[y->v]; aux!=NULL; aux=aux->next){
          if(aux->t==2 && aux->v==x->v){
            allPairs++;
          }
        }
      }
    }
  }
  if(allPairs==(l->n-1)*l->n){
    freeLIST(l);
    return 1;
  }
  freeLIST(l);
  return 0;
}


int *getNodePathType(Graph *G, int s, int connected, char *outfile, int write){

  QUEUE *q = initQUEUE();
  int *T, *V;
  int u, t, k;
  link *aux;
  int i;

  T = (int *)calloc(G->V,sizeof(int));
  if(connected){
    for(i = 0; i < G->V; i++){
      T[i]=1;
    }
  }
  V = (int *)calloc(G->V,sizeof(int));

  s--;
  T[s] = 3;
  addQUEUE(q, s, T[s]);

  //printf("Added node %d to FIFO\n", s+1);

  while(!emptyQUEUE(q)){
    removeQUEUE(q, &u, &t);
    //printf("Removed node %d type %d from FIFO\n", u+1, t);
    if(!V[u]){
      aux = G->adj[u];
      while(aux != NULL){
        //printf("Checking neighbour %d with type %d.\n", aux->v+1, t);
        k = modeling(aux->t, T[u]);
        if(k > T[aux->v]){
          if(!(connected && k==1)){
            T[aux->v] = k;
            //printf("Added node %d to FIFO with type %d.\n", aux->v+1, T[aux->v]);
            addQUEUE(q, aux->v, T[aux->v]);
          }
        }
        aux=aux->next;
      }
      V[u]=1;
    }
  }

  if(write){
    FILE *fp;
    fp = fopen (outfile,"w");
    if (fp!=NULL)  {
      fprintf(fp, "AS destiny = %d\n", s+1);
      for(i = 0; i < G->V; i++) {
        if(G->adj[i]!=NULL)
          fprintf(fp, "AS %d - %s\n", i+1, numToType(T[i]));
      }
    }
    fclose(fp);
  }
  free(V);
  freeQUEUE(q);
  return T;
}

void Dijkstra(Graph *Network, Node **path, int destiny_id, int *type){
	int *verify;
	Node *a=NULL;
	QUEUE2 *Q;
	int i;
	link *aux;
	Q = initQUEUE2();

	verify = (int*)malloc((Network->V)*sizeof(int));

	for(i=0;i<(Network->V);i++){
		verify[i] = 0;
		path[i]->t = 0;
		path[i]->nhops = MAX;
		path[i]->next = -1;
	}


	path[destiny_id - 1]->v = destiny_id;
	path[destiny_id - 1]->t = 3;
	path[destiny_id - 1]->nhops = 0;
	path[destiny_id - 1]->next = destiny_id;

	addQUEUE2(Q, path[destiny_id - 1]);

	for(i=0; !emptyQUEUE2(Q); i++){

    //printf("Removing AS\n");
		a = removeQUEUE2(Q);
	  //printf("Removed AS %d type %d\n", a->v, a->t);
		//verify[(a->v)-1] = 1;
		for(aux = Network->adj[(a->v) - 1]; aux != NULL; aux=aux->next){
      //printf("Checking AS %d type %d \n", aux->v+1, aux->t);
			if(modeling(aux->t, a->t) == type[(aux->v)] && verify[aux->v] == 0){
			  //printf("Improved\n");
				path[(aux->v)]->v = aux->v + 1;
				path[(aux->v)]->next = a->v;
				path[(aux->v)]->t = modeling(aux->t, a->t);
				path[(aux->v)]->nhops = a->nhops + 1;
        //printf("Adding AS %d type %d\n",path[(aux->v)]->v, path[(aux->v)]->t );
				addQUEUE2(Q, path[(aux->v)]);
        //printf("Added\n");
				verify[aux->v] = 1;
				countStatistics[(a->nhops) + 1] = countStatistics[(a->nhops) + 1] + 1;
        Total++;
				if((a->nhops) + 1 > maxHops){
					maxHops = (a->nhops) + 1;
				}
			}
		}
    //printf("Deleting AS %d\n", a->v);
    free(a);
    //printf("Deleted.\n\n");
    //printf("%d\n", emptyQUEUE2(Q));
	}

  freeQUEUE2(Q);
  free(verify);
}

void bestComercialRoute(Graph *Network, int destiny_id, char *outfile, int *vetor, int write){

	Node **path;
	int i;

	path = (Node**)malloc(sizeof(Node*)*(Network->V));
	for (i = 0; i < (Network->V);i++){
		path[i] = (Node*)malloc(sizeof(Node));
	}


	Dijkstra(Network, path, destiny_id, vetor);

  if(write){
  	FILE *fp;
    fp = fopen (outfile,"w");
    if (fp!=NULL)  {
      fprintf(fp, "AS destiny = %d\n", destiny_id+1);
      for(i=1; i < ((Network->V)+1); i++){
    	  if((path[i-1]->nhops) == MAX){
          if(Network->adj[i-1]!=NULL)
    		    fprintf(fp, "AS %d - Unreachable\n", i);
    	  }else{
          if(Network->adj[i-1]!=NULL)
    		    fprintf(fp, "AS %d - %d hops - %s\n", i, path[i-1]->nhops, numToType(path[i-1]->t));
          //  fprintf(fp, "AS %d - %s\n", i, numToType(path[i-1]->t));
    	  }
      }
    }
    fclose(fp);
  }

  for (i = 0; i < (Network->V);i++){
    free(path[i]);
  }
  free(path);
  free(vetor);
  return;
}

void BFS(Graph *Network, int *nhops, int destiny){
	FIFO *fifo = initFIFO();
	int *verify;
	int actualnode;
	int type;
	int i;
	link *aux;

	destiny--;

	verify = (int*)calloc((Network->V),sizeof(int));

	addFIFO(fifo, destiny, 1);

	nhops[destiny] = 0;

	for(i=0; fifo->n > 0; i++){
		//printf("Removing AS\n");
		removeFIFO(fifo, &actualnode, &type);
		//printf("Removed AS %d\n", actualnode+1);
		verify[actualnode] = 1;
		for(aux = Network->adj[actualnode];aux != NULL; aux=aux->next){
			//printf("Checking AS %d\n", aux->v+1);
			if(verify[(aux->v)] == 0){
        //printf("Improved\n");
				nhops[aux->v] = nhops[actualnode] + 1;
        //printf("Adding AS %d\n",aux->v+1);
				addFIFO(fifo, aux->v, 1);
        //printf("Added\n");
				verify[(aux->v)] = 1;
				countStatisticsBFS[nhops[actualnode] + 1] = countStatisticsBFS[nhops[actualnode] + 1] + 1;
        TotalBFS++;
				if(nhops[actualnode] + 1 > maxHopsBFS){
					maxHopsBFS = nhops[actualnode] + 1;
				}
			}
		}
    //printf("\n");
	}
  free(verify);
  freeFIFO(fifo);
}

void getSmallPath(Graph *Network, int destiny, char *outfile, int write){

	int *nhops;
	int i;
	nhops = (int*)calloc(Network->V, sizeof(int));

	BFS(Network, nhops, destiny);

  if(write){
  	FILE *fp;
  	fp = fopen (outfile,"w");
      if (fp!=NULL)  {
        fprintf(fp, "AS destiny = %d\n", destiny+1);
        for(i = 0; i < Network->V; i++) {
          if(Network->adj[i]!=NULL)
            fprintf(fp, "Node %d - %d hops\n", i+1, nhops[i]);
        }
      fclose (fp);
    }
  }
  free(nhops);
}

void readFile(char *fileName, Graph *G){
  FILE *fp;
  Edge *e;
  e = (Edge*)malloc(sizeof(Edge));
  fp = fopen (fileName,"r");
  if (fp==NULL)
    errorFile();
  else
    while(fscanf(fp, "%d %d %d", &(e->v), &(e->w), &(e->t))!=-1){
      e->v--;
      e->w--;
      GRAPHinsertE(G, e);
      //printf("Inserted edge %d-%d type %d.\n", e->v, e->w, e->t);
    }
  free(e);
  fclose (fp);
}
