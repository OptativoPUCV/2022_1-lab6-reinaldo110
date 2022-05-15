#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int * vector = (int *) calloc (10, sizeof(int));
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] != 0)
        {
          vector[n->sudo[i][j]]++;
          if (vector[n->sudo[i][j]] > 1) return 0;
        }
      }
      vector = (int *) calloc (10, sizeof(int));
    }
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(n->sudo[j][i] != 0)
        {
          vector[n->sudo[j][i]]++;
          if (vector[n->sudo[j][i]] > 1) return 0;
        }
      }
      vector = (int *) calloc (10, sizeof(int));
    }
    for(int m = 0; m < 9; m++)
    {
      for(int k = 0; k < 9; k++)
      {
        int i = 3*(m/3) + (k/3);
        int j = 3*(m%3) + (k%3);
        if(n->sudo[i][j] != 0)
        {
          vector[n->sudo[i][j]]++;
          if(vector[n->sudo[i][j]] > 1) return 0;
        }
      }
      vector = (int *) calloc (10, sizeof(int));
    }
    free(vector);
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for (int k = 1; k < 10; k++)
          {
            n->sudo[i][j] = k;
            if (is_valid(n))
            {
              Node * adj = copy(n);
              pushBack(list, adj);
              free(adj);
            }
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
        if(n->sudo[i][j] == 0) return 0;
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack * S = createStack();
  push(S, initial);
  while (get_size(S) != 0)
  {
    Node * n = first(S);
    if(!n) return NULL;
    popFront(S);
    if(is_final(n)) return n;

    List * adj = get_adj_nodes(n);
    Node * aux = first(adj);

    while(aux)
    {
      push(S, aux);
      aux = next(adj);
    }
    free(aux);
    free(adj);
    free(n);
    (*cont)++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/