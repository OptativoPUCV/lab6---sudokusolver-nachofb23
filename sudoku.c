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
    int i, j, k;

    for (i = 0; i < 9; i++) {
      int row_check[10] = {0};
      for (j = 0; j < 9; j++) {
        int num = n->sudo[i][j];
        if (num != 0) {
          if (row_check[num] == 1) {
            return 0;
          } else {
            row_check[num] = 1;
          }
        }
      }
    }

    for (j = 0; j < 9; j++) {
      int col_check[10] = {0};
      for (i = 0; i < 9; i++) {
        int num = n->sudo[i][j];
        if (num != 0) {
          if (col_check[num] == 1) {
            return 0;
          } else {
            col_check[num] = 1;
          }
        }
      }
    }

    for (i = 0; i < 9; i+= 3) {
      for (j = 0; j < 9; j+= 3) {
        int submatrix_check[10] = {0};
        for (k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) { 
            int num = n->sudo[i + k][j + l];
            if (num != 0) {
              if (submatrix_check[num] == 1) {
                return 0;
              } else {
                submatrix_check[num] = 1;
              }
            }
            
          }
        }
      }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    int i, j;

    for (i = 0; i < 9; i++) {
      for (j = 0; j < 9; j++) {
        if (n->sudo[i][j] == 0) {
          int k;
          Node* adj_node;
          for (k = 1; k <= 9; k++) {
            adj_node = copy(n);
            adj_node->sudo[i][j] = k;

            if (is_valid(adj_node)) {
              pushBack(list, adj_node);
            } else {
              free(adj_node);
            }
          }
          return list;
        }
      }
    }
  return list;
}


int is_final(Node* n){
  int i, j;
  for (i = 0; i< 9; i++) {
    for (j = 0; j< 9; j++) {
      if (n->sudo[i][j] == 0) {
        return 0;
      }
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* stack = createStack();
  push(stack, initial);

  while (!is_empty(stack)) {
    (*cont)++;
    Node* current = top(stack);
    pop(stack);
    
    if (is_final(current)) {
      free(stack);
      return current;
    }
    
    List* adj_node = get_adj_nodes(current);
    Node* temp = front(adj_node);
    
    for (temp = front(adj_node); temp != NULL; temp = next(adj_node)) {
      if (is_valid(temp)) {
        push(stack, temp);
      } else {
        free(temp);
      }
    }
    clean(adj_node);
  }
  free(stack);
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