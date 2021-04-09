// Avaliação 2 - Estrutura de dados - T02
// Professor Doutor Rodolfo Botto de Barros Garcia
// Aluno: Ayrton Fernandes Hora
// Matrícula: 201800083651 
// E-mail: ayrtonhora@academico.ufs.br

// Fase 3 - Two gate's update (new search methods)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
  char *plate; // Vehicle plate
  float time; // Vehicle time in the parking lot
  int movements; // Number o movements per vehicle
  int height;
  struct TreeNode * left;
  struct TreeNode * right;
};

struct TreeNode* createNode (char *plate, float time, int movements) {
  struct TreeNode* new = (struct TreeNode*) malloc(sizeof(struct TreeNode));
  new->plate = plate;
  new->time = time;
  new->movements = movements;
  new->height = 0;
  new->left = NULL;
  new->right = NULL;
  return new;
}

struct TreeNode* searchNode (struct TreeNode* root, char *plate, int n_comp) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    if (plate == ref->plate) {
      n_comp++;
      printf("\nVehicle %s was found, Total movements: %d\n", plate, n_comp);
      return ref; 
    }

    if (plate < ref->plate) {
      n_comp++;
      return searchNode(ref->left, plate, n_comp);
      
    }

    else {
      n_comp++;
      return searchNode(ref->right, plate, n_comp);
    }  
  }
  printf("Vehicle %s not found, Total movements: %d\n", plate, n_comp);
}

// struct TreeNode* search_forFix (struct TreeNode* root, char* plate, int n) {
//   struct TreeNode* ref = root;
//   if (ref != NULL) {
//     if (plate == ref->plate) {
//       n++;
//       return ref; 
//     }
//     if (plate < ref->plate) {
//       n++;
//       return search_forFix(ref->left, plate, n);
//     }
//     else {
//       n++;
//       return search_forFix(ref->right, plate, n);
//     }  
//   }
// }

int heigh_BinaryNode (struct TreeNode* node, char *plate, int n) {
  struct TreeNode* search_n = searchNode(node, plate, n);
  return (search_n->movements - 1);
}

// void fix_BT_height (struct TreeNode* root, int n) {
//   struct TreeNode* ref = root;
//   char* plate_ref = root->plate;
//   if (root != NULL) {
//     n = search_forFix(root, plate_ref, n);
//     root->height = n ;
//     fix_BT_height(root->left, n);
//     fix_BT_height(root->right, n);
//   } 
// }

struct TreeNode* minNode (struct TreeNode* root) {
  struct TreeNode* ref = root;
  while (ref && ref->left != NULL) ref = ref->left;
  
  return ref;
}

void insertNode (struct TreeNode** root, char *plate, float time, int movements, int n_comp) {
  struct TreeNode* ref = *root;
  struct TreeNode* temp = NULL;
  if (*root == NULL) {
    n_comp++;
    *root = createNode(plate, time, n_comp);
    (*root)->height = n_comp - 1;
    printf("Vehicle %s parked\n", plate);
  }

  else if (plate < (*root)->plate) {
    n_comp++;
    insertNode(&(*root)->left, plate, time, movements, n_comp);
  }

  else if (plate >= (*root)->plate) {
    n_comp++;
    insertNode(&(*root)->right, plate, time, movements, n_comp);
  }
}

struct TreeNode* deleteNode (struct TreeNode** root, char *plate) {
  struct TreeNode* temp = NULL;
  
  // Base
  if (*root == NULL) return *root; 
  
  // Data is smaller than
  if (plate < (*root)->plate) (*root)->left = deleteNode(&(*root)->left, plate); 

  // Data is greater than
  else if (plate > (*root)->plate) (*root)->right = deleteNode(&(*root)->right, plate); 

  // Data is equal
  else { 

    // One or no child
    if ((*root)->left == NULL) {
      temp = (*root)->right;
      free(*root);
      return temp;
    }

    else if ((*root)->right == NULL) {
      temp = (*root)->left;
      free(*root);
      return temp;
    }

    // Two children
    // Smallest in the right (InOrder sucessor)
    temp = minNode((*root)->right); 

    // Copy and save the data
    (*root)->plate = temp->plate; 

    // Delete smallest in the right (InOrder sucessor)
    (*root)->right = deleteNode(&(*root)->right, temp->plate); 
  }
  return (*root);
}

void deleteTree (struct TreeNode* root) {
  if (root) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void print_PreOrder (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (root != NULL) {
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_PreOrder(ref->left);
    print_PreOrder(ref->right);
  }
}

void print_InOrder (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_InOrder(ref->left);
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_InOrder(ref->right);
  }
}

void print_PostOrder(struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_PostOrder(ref->left);
    print_PostOrder(ref->right);
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
  }
}

void main() {
  struct TreeNode* root = NULL;
  int n_comp = 0;
  int height;

  // Inserting
  printf("\nParking...\n");
  insertNode(&root, "0004", 50, 0, n_comp);
  insertNode(&root, "0002", 30, 0, n_comp);
  insertNode(&root, "0001", 40, 0, n_comp);
  insertNode(&root, "0003", 40, 0, n_comp);
  insertNode(&root, "0005", 32, 0, n_comp);
  insertNode(&root, "0006", 64, 0, n_comp);
  insertNode(&root, "0000", 20, 0, n_comp);
  insertNode(&root, "0007", 80, 0, n_comp);
  insertNode(&root, "0008", 100, 0, n_comp);

  // Searching
  printf("\nOnly searching...");
  searchNode(root, "0001", n_comp);
  
  // Searching and comparing
  printf("\nSearching the vehicle and calculating...");
  height = heigh_BinaryNode(root, "0001", n_comp);
  printf("The height of Node is: %d", height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  height = heigh_BinaryNode(root, "0005", n_comp);
  printf("The height of Node is: %d", height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  height = heigh_BinaryNode(root, "0000", n_comp);
  printf("The height of Node is: %d", height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  height = heigh_BinaryNode(root, "0008", n_comp);
  printf("The height of Node is: %d", height);
  printf("\n");

  /* 
  Número de comparações = 
  3 + 5 + 7 + 9 =
  24

  Média de comparações = 
  24 / 4 =
  6

  O portão de saída pode ser determinado simplesmente calculado a altura do nó e a altura máxima da árvore. 
  Caso (valor da altura do nó < (altura máxima/2)) o veículo deverá sair por cima.
  Caso (valor da altura do nó >= (altura máxima/2)) o veículo deverá sair por baixo.
  */

  // Deleting
  printf("\nDeleting...");
  deleteNode(&root, "0004");
  printf("\nVehicle %s removed\n", "0004");

  printf("\nThe minimum Node is: ");
  printf("%s\n", minNode(root)->plate);

  printf("\nBinary Tree:\n");
  print_PreOrder(root);

  // Cleaning
  deleteTree(root);
}