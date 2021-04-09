// Avaliação 2 - Estrutura de dados - T02
// Professor Doutor Rodolfo Botto de Barros Garcia
// Aluno: Ayrton Fernandes Hora
// Matrícula: 201800083651 
// E-mail: ayrtonhora@academico.ufs.br

// Fase 3 - Two gate's update (new search methods)

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Binary_Tree.h"
#include "AVL_Tree.h"
#include "Hash_Table.h"

#define CAPACITY_MAX 50 // Size of the Hash Table

// Global variables
float money = 0; // Money
bool upgrade = true; // State of upgrade

// Cash of park lot for doubly linked list structure
void cash_Bin (struct TreeNode* vehicle) { 
  float time = vehicle->time; // In seconds
  while (time > -1) {
     if (time <= 3600) {
      money = money + 12;
      time = -1;
    }
    if (time > 3600) {
      money = money + 12;
      time = time - 3600;
    }
  }
}

void cash_AVL (struct AVLnode* vehicle) { 
  float time = vehicle->time; // In seconds
  while (time > -1) {
     if (time <= 3600) {
      money = money + 12;
      time = -1;
    }
    if (time > 3600) {
      money = money + 12;
      time = time - 3600;
    }
  }
}

void cash_Hash (struct Hash_table* table, char* key, int n) { 
  struct Data* ref = search_Data(table, key, n); // In seconds
  float time = ref->time;
  while (time > -1) {
     if (time <= 3600) {
      money = money + 12;
      time = -1;
    }
    if (time > 3600) {
      money = money + 12;
      time = time - 3600;
    }
  }
}

void main() {
  // Creating root's
  struct TreeNode* binary_tree = NULL;

  struct AVLnode* avl_tree = NULL;
  struct Hash_table* h_table = createTable(CAPACITY_MAX);

  // Control variables
  int total_movements;

  // Intro
  printf("|-----Welcome to the parking lot software-----|\n");
  printf("|-----Max capacity = %d vehicles-----|\n\n", CAPACITY_MAX);
  
  // Cleaning
}




