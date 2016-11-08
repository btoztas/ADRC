#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "GraphADT.h"
#include "routing.h"

#define MAX 500000

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

void printHeap(Heap *h){
  int i;
  if(h->size==0){
    printf("Heap is empty.\n");
  }else{
    for(i=0; i<h->size; i++)
      printf("%d %d %d %d\n", (h->q[i])->v,(h->q[i])->t, (h->q[i])->nhops, (h->q[i])->next);
    printf("\n");
  }
  return;
}

Heap *initHeap(int size){
  int i;

  Heap *h = (Heap*)malloc(sizeof(Heap));
  if(h==NULL)
    errorMalloc();

  h->q = (Node**) malloc(size*sizeof(link));
  if(h->q==NULL)
    errorMalloc();

  for(i=0; i<size; i++)
    h->q[i] = NULL;
  h->size = 0;

  return h;
}

void freeHeap(Heap *h){

  free(h->q);
  free(h);

  return;
}

void fixHeapUp(Heap *h){
  Node *aux;
  int i =0;
  int k = h->size-1;
  while ((k > 0) && i == 0) {

	if(((((h->q)[k])->t) > (((h->q)[(k-1)/2])->t))){
		aux = (h->q)[k];
		(h->q)[k] = (h->q)[(k - 1) / 2];
		(h->q)[(k - 1) / 2] = aux;
		k = (k - 1) / 2;
	}else if(((((h->q)[k])->t) == (((h->q)[(k-1)/2])->t)) && ((((h->q)[k])->nhops) < (((h->q)[(k-1)/2])->nhops))){
		aux = (h->q)[k];
		(h->q)[k] = (h->q)[(k - 1) / 2];
		(h->q)[(k - 1) / 2] = aux;
		k = (k - 1) / 2;
	}else{
		i=1;
	}
  }
  return;
}

void addToHeap(Node *n, Heap *h){
  h->q[h->size] = n;
  h->size++;
  if(h->size!=1)
    fixHeapUp(h);
  return;
}

void fixHeapDown(Heap *h){

  //printf("Starting fixHeapDown\n");
  int i=0, k=0;
  int found=0;
  Node *aux;

  if(h->size>1){
    while (i < h->size && !found) {
      k = 2*i+1;
      if(k<h->size){
        if(k+1<h->size){
          if( ((((h->q)[i])->t) > (((h->q)[i*2+1])->t) && (((h->q)[i])->t) > (((h->q)[i*2+2])->t)) ){
            found = 1;
          }else if(((((h->q)[i])->t) == (((h->q)[i*2+1])->t) && (((h->q)[i])->t) == (((h->q)[i*2+2])->t))){
			if( ((((h->q)[i])->nhops) < (((h->q)[i*2+1])->nhops) && (((h->q)[i])->nhops) < (((h->q)[i*2+2])->nhops)) ){
				found = 1;
			}
			else{
				aux = (h->q)[i];
				k = ((h->q)[i*2+1])->nhops < ((h->q)[i*2+2])->nhops ? i*2+1 : i*2+2;
				//printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
				(h->q)[i] = (h->q)[k];
				(h->q)[k] = aux;
				i = k;
			}
          }else{
            aux = (h->q)[i];
            k = ((h->q)[i*2+1])->t < ((h->q)[i*2+2])->t ? i*2+1 : i*2+2;
            //printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
            (h->q)[i] = (h->q)[k];
            (h->q)[k] = aux;
            i = k;
          }
        }
        else if( (h->q)[i]->t > (h->q)[i*2+1]->t){
          found = 1;
        }
        else if( (h->q)[i]->t == (h->q)[i*2+1]->t){
			if((h->q)[i]->nhops < (h->q)[i*2+1]->nhops){
				found=1;
			}else{
				aux = (h->q)[i];
				//printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
				(h->q)[i] = (h->q)[k];
				(h->q)[k] = aux;
				i = k;
			}
		}
        else{
          aux = (h->q)[i];
          //printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
          (h->q)[i] = (h->q)[k];
          (h->q)[k] = aux;
          i = k;
        }
      }else
        found=1;
    }
  }
  return;
}

Node *removeFromHeap(Heap * h){
  Node *n;
  if (h->size > 0) {
    n = (h->q)[0];
    (h->q)[0] = (h->q)[h->size - 1];
    (h->q)[h->size - 1] = NULL;
    h->size--;
    fixHeapDown(h);
    return n;
  }
  return NULL;
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
    removeFIFO(q->c, u, t);
  else if(!emptyFIFO(q->p))
    removeFIFO(q->c, u, t);
  return;
}

int emptyQUEUE(QUEUE *q){
  if(emptyFIFO(q->c) && emptyFIFO(q->c) && emptyFIFO(q->c))
    return 1;
  return 0;
}

void freeQUEUE(QUEUE *q){
  freeFIFO(q->c);
  freeFIFO(q->r);
  freeFIFO(q->p);
  free(q);
}

void getNodePathType(Graph *G, int s, char *outfile){
  QUEUE *q = initQUEUE();
  //printf("Initiated QUEUE\n");
  int *V;
  int *T;
  int u, v, t;
  link *aux;
  int i;
  V = (int *)calloc(G->V,sizeof(int));
  T = (int *)calloc(G->V,sizeof(int));
  s--;
  T[s] = 3;

  addQUEUE(q, s, T[s]);
  //printf("Added node %d to FIFO\n", s+1);
  while(!emptyQUEUE(q)){
    removeQUEUE(q, &u, &t);
    //printf("Removed node %d type %d from FIFO\n", u+1, t);
    aux = G->adj[u];
    while(aux != NULL){
      v = aux->v;
      if(V[v] == 0)
        if(modeling(aux->t, T[u]) > T[v]){
          T[v] = modeling(aux->t, T[u]);
          //printf("Added node %d to FIFO\n", v+1);
          addQUEUE(q, v, T[v]);
        }
      aux=aux->next;
    }
    V[u] = 1;
  }
  FILE *fp;
  fp = fopen (outfile,"w");
  if (fp!=NULL)  {
    for(i = 0; i < G->V; i++) {
      fprintf(fp, "Node %d - %s\n", i+1, numToType(T[i]));
    }
    fclose (fp);
  }
  free(T);
  free(V);
  freeQUEUE(q);
  return;
}



void Disjkstra(Graph *Network, Node **path, int destiny_id){
	int *verify;
	Node *a;
	Heap *H;
	int i;
	link *aux;

	H = initHeap(Network->V);

	verify = (int*)malloc((Network->V)*sizeof(int));

	//printf("estou aqui \n");

	for(i=0;i<(Network->V);i++){
		verify[i] = 0;
		path[i]->t = 0;
		path[i]->nhops = INT_MAX;
		path[i]->next = -1;
	}

	//printf("estou aqui \n");

	destiny_id = destiny_id;

	path[destiny_id - 1]->v = destiny_id;
	path[destiny_id - 1]->t = 3;
	path[destiny_id - 1]->nhops = 0;
	path[destiny_id - 1]->next = destiny_id;

	addToHeap(path[destiny_id - 1], H);

	for(i=0; H->size > 0; i++){
		//printHeap(H);
		a = removeFromHeap(H);
		//printf("iteração %d com o nó %d\n", i, a->v);
		verify[(a->v)-1] = 1;
		//printf("retirado o nó %d do Heap\n", a->v);
		for(aux = Network->adj[(a->v) - 1];aux != NULL; aux=aux->next){
			//printf("A relaxar aresta com nó %d\n", aux->v + 1);
			if(verify[(aux->v)] == 0){
				//printf("ainda não verificada\n");
				//printf("%d ( %d ) = %d será maior que %d?\n", aux->t, a->t, modeling(aux->t, a->t), path[(aux->v)]->t);
				if(modeling(aux->t, a->t) > path[(aux->v)]->t){
					//printf("melhorou por tipo\n");
					path[(aux->v)]->v = aux->v + 1;
					path[(aux->v)]->next = a->v;
					path[(aux->v)]->t = modeling(aux->t, a->t);
					path[(aux->v)]->nhops = a->nhops + 1;
					addToHeap(path[(aux->v)], H);
				}else if(modeling(aux->t, a->t) == path[(aux->v)]->t && (a->nhops + 1) < path[(aux->v)]->nhops){
					//printf("melhorou por saltos\n");
					path[(aux->v)]->next = a->v;
					path[(aux->v)]->v = aux->v + 1;
					path[(aux->v)]->nhops = a->nhops + 1;
					addToHeap(path[(aux->v)], H);
				}
			}
		}
	}

  freeHeap(H);
  free(verify);
}

void bestComercialRoute(Graph *Network, int destiny_id, char *outfile){

	Node **path;
	int i;

	path = (Node**)malloc(sizeof(Node*)*(Network->V));

	for (i = 0; i < (Network->V);i++){
		path[i] = (Node*)malloc(sizeof(Node));
	}


	Disjkstra(Network, path, destiny_id);

	FILE *fp;
  fp = fopen (outfile,"w");
  if (fp!=NULL)  {
    for(i=1; i < ((Network->V)+1); i++){
  	  if((path[i-1]->nhops) == MAX){
  		  fprintf(fp, "AS %d - Unreachable\n", i);
  	  }else{
  		fprintf(fp, "AS %d - %d hops - %s\n", i, path[i-1]->nhops, numToType(path[i-1]->t));
  	  }
    }
  }
  fclose(fp);

  for (i = 0; i < (Network->V);i++){
    free(path[i]);
  }
  free(path);
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
