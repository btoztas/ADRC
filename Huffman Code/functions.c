#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"
#include "random.h"

#define MAX 256

void errorMalloc(){
  printf("Error allocating memory\n");
  exit(-1);
}

void readFile(char *symbols, float *freq){
	FILE *fp;
	char *line = (char *)malloc(256*sizeof(char));
	int i;
	float readfreq;
	fp = fopen("symbols.txt", "r");

	for(i=0; fscanf(fp, "%s", line)!=-1; i++){
		if(line[1]=='\0'){
			symbols[i]=line[0];
			fscanf(fp, "%f", &readfreq);
			freq[i]=readfreq;
		}else{
			symbols[i]=line[0];
			line++;
			line++;
			readfreq = atof(line);
      freq[i]=readfreq;
		}
	}

	fclose(fp);
	return;
}

Code *initCode(int size){
  Code *c = (Code *) malloc(sizeof(Code));
  if(c==NULL)
    errorMalloc();
  c->list = (Entry**) malloc(sizeof(Entry)*size);
  if(c->list==NULL)
    errorMalloc();
  return c;
}

Node *newNode(char *d, float p){
  Node *n = (Node*) malloc(sizeof(Node));
  if(n==NULL)
    errorMalloc();
  n->d=d;
  n->p=p;
  n->l=n->r=NULL;
  return n;
}

Tree *initTree(){
  Tree *t = (Tree*) malloc(sizeof(Tree));
  if(t==NULL)
    errorMalloc();
  t->root = NULL;
  return t;
}

int isLeaf(Node *n){
  if(n->l == NULL && n->r == NULL){
    return 1;
  }
  return 0;
}

Heap *initHeap(int size){
  int i;
  Heap *h = (Heap*) malloc(sizeof(Heap));
  if(h==NULL)
    errorMalloc();
  h->q = (Node**) malloc(size*sizeof(Node));
  if(h->q==NULL)
    errorMalloc();
  for(i=0; i<size; i++)
    h->q[i] = NULL;
  h->size = 0;
  return h;
}

void fixHeapUp(Heap *h){
  Node *aux;
  int k = h->size-1;
  while ((k > 0) && ((((h->q)[k])->p) < (((h->q)[(k-1)/2])->p)) ) {
    aux = (h->q)[k];
    (h->q)[k] = (h->q)[(k - 1) / 2];
    (h->q)[(k - 1) / 2] = aux;
    k = (k - 1) / 2;
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
  printf("Starting fixHeapDown\n");
  int i=0, k=0;
  int found=0;
  Node *aux;

  if(h->size>1){
    while (i < h->size && !found) {
      k = 2*i+1;
      if(k<h->size){
        if(k+1<h->size){
          if( ((((h->q)[i])->p) < (((h->q)[i*2+1])->p) && (((h->q)[i])->p) < (((h->q)[i*2+2])->p)) )
            found = 1;
          else{
            aux = (h->q)[i];
            k = ((h->q)[i*2+1])->p < ((h->q)[i*2+2])->p ? i*2+1 : i*2+2;

            printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
            (h->q)[i] = (h->q)[k];
            (h->q)[k] = aux;
            i = k;

          }
        }
        else if( (h->q)[i]->p < (h->q)[i*2+1]->p)
          found = 1;
        else{
          aux = (h->q)[i];

          printf("Vou trocar o %c-%f com o %c-%f\n",(h->q)[i]->d, (h->q)[i]->p, (h->q)[k]->d, (h->q)[k]->p);
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

void printHeap(Heap *h){
  int i;
  if(h->size==0){
    printf("Heap is empty.\n");
  }else{
    for(i=0; i<h->size; i++)
      printf("%c %f\n", (h->q[i])->d,(h->q[i])->p);
    printf("\n");
  }
  return;
}

void printTree(Node *root){

  if (isLeaf(root)){
    printf("%c\n", root->d);
  }else{
    printf("-\n");
    printTree(root->l);
    printTree(root->r);
  }
  return;
}

<<<<<<< HEAD

void makeTree(Tree *t, char *Symbols, int size){

  int i, j;
  Node *new, *q, *p;
  srand(time(NULL));

  for (i=0; i < size; i++) {
      new = newNode(Symbols[i],0);
      if(t->root==NULL){
        t->root = new;
      }else{
        q=t->root;
        while(!isLeaf(q)){
          j=(rand()%2);
          p=q;
          if(!j)
            q=q->l;
          else
            q=q->r;
        }
        if(!j){
          p->l=newNode("\0", 0);
          (p->l)->l=q;
          (p->l)->r=q;
        }else{
          p->r=newNode("\0", 0);
          (p->r)->l=q;
          (p->r)->r=q;
        }
      }
  }
}


=======
>>>>>>> parent of 9a45476... Started implementin makeTree
void searchCodeTree(Node *root, Code *code, char *hops, int *nhop, int *n){
  int i;
  printf("%d\n", (*nhop));

  if (isLeaf(root)) {
    printf("---Found a leaf!---\n");
    Entry *aux = (Entry*) malloc(sizeof(Entry));
    aux->d = root->d;
    aux->c = (char*)malloc((*nhop)*sizeof(char));
    for(i=0; i<(*nhop); i++)
      aux->c[i]=hops[i];
    code->list[(*n)]=aux;
    printf("Added leaf %c with code %s to the list on position %d.\n\n", code->list[(*n)]->d, code->list[(*n)]->c, *n);
    (*n)++;
  }

  else{
    (*nhop)++;
    hops[(*nhop)-1]='0';
    printf("Searching left node\n");
    searchCodeTree(root->l, code, hops, nhop, n);

    (*nhop)++;
    hops[(*nhop)-1]='1';
    printf("Searching right node\n");
    searchCodeTree(root->r, code, hops, nhop, n);
  }
  printf("Returning\n");
  (*nhop)--;
  return;
}

void GenereteCode(Node *root, Code *code){
  char hops[MAX+1];
  int nhop=0, n=0;
  searchCodeTree(root, code, hops, &nhop, &n);
}

void Decode(Node *root, char *InString, char *OutString){
	int i;
	int j=0;
	Node *realRoot = root;

	printf("starting decoding \n");
	for(i=0;InString[i]!='\0';){
		if(isLeaf(root)){
			OutString[j]=root->d;
			j++;
			root=realRoot;
		}else{
			if(InString[i]=='0'){
				root = root->l;
			}else{
				root = root->r;
			}
			i++;
		}
	}
	OutString[j]=root->d;
	OutString[j+1]='\0';
	return;
}

void printCode(Code *Code, int size){
	int i;
  printf("---------------------------\nCurrently, your code is:\n");
	for(i=0;i<size;i++){
		printf("Symbol: %c  Code: %s\n", (Code->list)[i]->d, (Code->list)[i]->c);
	}
  printf("---------------------------\n");
}

void HuffmanCode(char *Symbols, float *Freq, Code *code){

  int size = strlen(Symbols);
  int i;
  Tree *t;
  Node *n, *m, *s;
  printf("Creating a Heap of maximum size %d\n", size);
  Heap *h = initHeap(size);
  for(i=0; i<strlen(Symbols); i++)
    addToHeap(newNode(Symbols[i], Freq[i]),h);
  printf("Finished adding to Heap\nHeap state:\n");
  printHeap(h);
  t = initTree();
  printf("Making Huffman tree.\n\n------------------------\n");
  for(i=0; h->size!=1; i++) {
    printf("LOOP NUMBER %d.\nHeap state:\n", i);
    printHeap(h);
    n = removeFromHeap(h);
    printf("Removed node %c of size %f from heap.\n",n->d, n->p);
    m = removeFromHeap(h);
    printf("Removed node %c of size %f from heap.\n",m->d, m->p);
    s = newNode('\0', n->p + m->p);
    s->l = n;
    s->r = m;
    printf("Merged node %c of size %f with node %c of size %f.\n",n->d, n->p, m->d, m->p);
    addToHeap(s, h);
    printf("Subtree made:\n");
    printTree(s);
    printf("Added node of size %f to heap\n----END OF LOOP----\n-------------------\n", s->p);
  }
  t->root = removeFromHeap(h);
  printf("\n\n\n-------------------\nWe have a Huffman tree now.\nPrinting the tree:\n");
  printTree(t->root);
  printf("Generating code.\n");
  GenereteCode(t->root, code);
  printf("Finished generating code.\n");

  return;
}

void heapTest(char *Symbols, float *Freq){
  int i;
  Node *n;
  Heap *h = initHeap(strlen(Symbols));
  for(i=0; i<strlen(Symbols); i++)
    addToHeap(newNode(Symbols[i], Freq[i]),h);
  printf("Finished adding to Heap\n");
  for (i = 0; i<strlen(Symbols); i++){
    printf("Iteracao numero %d:\nEstado do Heap:\n",i+1);
    printHeap(h);
    n=removeFromHeap(h);
    printf("Node retirado:\n%c %f\n-----------------\n",n->d, n->p);
  }
}

void testReadFile(char *symbols, float *freq){
  int i;
  printf("Testing the symbols read:\n");
  for(i=0;i<strlen(symbols);i++){
		printf("%c  %f\n", symbols[i], freq[i]);
	}
  printf("-----------------------------\n\n\n");
  return;
}

void testHuffman(char *symbols,float *freq){
  Code *c = initCode(strlen(symbols));
  HuffmanCode(symbols, freq, c);
  printCode(c, strlen(symbols));
  return;
}
