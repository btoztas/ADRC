#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

Tree *initTree(){
  Tree *t = (Tree*) malloc(sizeof(Tree));
  t->root = NULL;
  return *t;
}

void addToTree(char data, Tree *t){

  Node *n = (Node*) malloc(sizeof(Node));
  n->r = NULL;
  n->l = NULL;
  n->d = data;

  if (t->root == NULL) {
    t->root = n;
  }else{

  }
}
