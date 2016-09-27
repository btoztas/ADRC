#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include "math.h"


/*
typedef struct _Node {int item; struct _Node *l, *r;}Node;

typedef struct _Tree{Node *root; int size;}Tree;

void init(Tree *tree){
	tree->root=NULL;
	tree->size = 0;
}


Node *newNode(int x){
  Node *new=calloc(1, sizeof(Node));
  if(new==NULL){
    printf("erro a alocar\n");
    exit(-1);
  }
  new->item = x;
  new->l = NULL;
  new->r = NULL;
  return new;
}

void createExampleTree(Tree *tree){
  Node *new;
  
  new=newNode(0);
  tree->root=new;
  new->l=newNode(0);
  (new->l)->l=newNode(1);
  (new->l)->r=newNode(0);
  ((new->l)->r)->l=newNode(2);
  ((new->l)->r)->r=newNode(3);
  
  new->r=newNode(0);
  (new->r)->l=newNode(4);
  (new->r)->r=newNode(0);
  ((new->r)->r)->l=newNode(5);
  ((new->r)->r)->r=newNode(6);
  tree->size=11;
}

void printTree(Tree *tree){
	printf("00:%d 010:%d 011:%d 10:%d 110:%d 111:%d", (((tree->root)->l)->l)->item, ((((tree->root)->l)->r)->l)->item,
	((((tree->root)->l)->r)->r)->item, (((tree->root)->r)->l)->item, ((((tree->root)->r)->r)->l)->item,
	((((tree->root)->r)->r)->r)->item);
}

void createPrefixCode(Tree *tree, Node *root, char *code){
	if(root == NULL) return;
	
	if((root->l)->item == 0){
		strcat(code, "0");
		createPrefixCode(tree, root->l, code);
	}
	
	if((root->l)->item != 0){
		printf("o número %d tem código é %c/n", (root->l)->item, code)
		strcpy(code,"");
		root=root->r;
	}
	for(i=0; i<tree->size; i++){
			
	}
	
}
*/

typedef struct _Node{int position; char symbol;}Node;

void tobinstr(int value, int bitsCount, char* output)
{
    int i;
    output[bitsCount] = '\0';
    for (i = bitsCount - 1; i >= 0; --i, value >>= 1)
    {
        output[i] = (value & 1) + '0';
    }
}

int main(){
	
	Node tree[15];
	int twobase;
	double tbase;
	int dif;
	char binary[20];
	int i;
	
	tree[0].position = 4;
	tree[0].symbol = 'a';
	
	tree[1].position = 6;
	tree[1].symbol = 'd';
	
	tree[2].position = 10;
	tree[2].symbol = 'b';
	
	tree[3].position = 11;
	tree[3].symbol = 'c';
	
	tree[4].position = 14;
	tree[4].symbol = 'e';
	
	tree[5].position = 15;
	tree[5].symbol = 'f';
	
	tree[6].position = 0;
	
	for(i=0;tree[i].position!=0;i++){
		tbase = (log(tree[i].position))/(log(2));
		twobase = pow(2,floor(tbase));
		dif = tree[i].position - twobase;
		tobinstr(dif, log(twobase)/log(2), binary);
		printf("i = %d, tbase = %f, twobase = %d, dif = %d, pos = %d\n", i, tbase, twobase, dif, tree[i].position);
		printf("o símbolo com '%c' tem código %s\n", tree[i].symbol, binary);
	}
	
	/*Tree tree;
	
	init(&tree);
	
	createExampleTree(&tree);
	
	printTree(&tree);*/
	
	
	
	return;
}
