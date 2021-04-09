// Avaliação 2 - Estrutura de dados - T02
// Professor Doutor Rodolfo Botto de Barros Garcia
// Aluno: Ayrton Fernandes Hora
// Matrícula: 201800083651 
// E-mail: ayrtonhora@academico.ufs.br

// Fase 3 - Two gate's update (new search methods)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct AVLnode {
  char *plate; // Vehicle plate
  float time; // Vehicle time in the parking lot
  int movements; // Number o movements per vehicle
  int height; // The height is from highest to lowest
  struct AVLnode *left;
  struct AVLnode *right;
};

int max (int a, int b) {
  return (a > b)? a : b;
}

int height (struct AVLnode* n) {
  if (n == NULL) return 0;
  
  else return n->height;
}

int getTreebalance (struct AVLnode* n) {
  if (n == NULL) return 0;
  
  else return (height(n->left) - height(n->right));
}

struct AVLnode* min_Node (struct AVLnode* root) {
  struct AVLnode* ref = root;
  while (ref->left != NULL) ref = ref->left;
  return ref;
}

struct AVLnode* createNode (char *plate, float time, int movements) {
  struct AVLnode* new = (struct AVLnode*) malloc(sizeof(struct AVLnode));
  new->plate = plate;
  new->time = time;
  new->movements = movements;
  new->height = 1;
  new->left = NULL;
  new->right = NULL;
  return (new);
}

struct AVLnode* leftRotation (struct AVLnode* n) {
  struct AVLnode* a = n->right;
  struct AVLnode* b = a->left;

  a->left = n;
  n->right = b;

  n->height = max(height(n->left), height(n->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;
  
  return a;
}

struct AVLnode* rightRotation (struct AVLnode* n) {
  struct AVLnode* a = n->left;
  struct AVLnode* b = a->right;

  a->right = n;
  n->left = b;
  
  n->height = max(height(n->left), height(n->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;
  
  return a;
}

struct AVLnode* searchAVLnode (struct AVLnode* root, char *plate, int n_comp) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    if (ref->plate == plate) {
      n_comp++;
      printf("\nVehicle %s was found, Total movements: %d\n", plate, n_comp);
      return ref;
    }

    if (plate < ref->plate) {
      n_comp++;
      return searchAVLnode(ref->left, plate, n_comp);
    }

    if (plate > ref->plate) {
      n_comp++;
      return searchAVLnode(ref->right, plate, n_comp);
    }
  }
  printf("Vehicle %s not found, Total movements: %d\n", plate, n_comp);
}

struct AVLnode* insertNode (struct AVLnode* root, char *plate, float time, int movements) {
  // Base
  if (root == NULL) {
    movements++;
    printf("Vehicle %s parked\n", plate);
    return (createNode(plate, time, movements)); 
  }

  // Searching
  if (plate < root->plate) {
    movements++;
    root->left = insertNode(root->left, plate, time, movements);
  }

  else if (plate > root->plate) {
    movements++;
    root->right = insertNode(root->right, plate, time, movements);
  }

  // If data is equal = error
  else return root;

  // Updating height of actual state of recursin after insertion
  root->height = max(height(root->left), height(root->right)) + 1;

  // Check and fix the balance
  int actual_balance = getTreebalance(root);

  // Left Left Case
  if ((actual_balance > 1) && (plate < root->left->plate)) {
    root->movements++;
    return (rightRotation(root));  // < -1
  }

  // Right Right Case
  if ((actual_balance < -1) && (plate > root->right->plate)) {
    root->movements++;
    return (leftRotation(root));  // > 1
  }

  // Left Right Case
  if ((actual_balance > 1) && (plate > root->left->plate)) { 
    root->left->movements++;
    root->left = leftRotation(root->left);
    root->movements++;
    return (rightRotation(root));
  } 

  // Right Left Case
  if ((actual_balance < -1) && (plate < root->right->plate)) { 
    root->right->movements++;
    root->right = rightRotation(root->right);
    root->movements++;
    return (leftRotation(root));
  }

  // Returning
  return root;
}

struct AVLnode* deleteNode (struct AVLnode* root, char *plate, int movements) {
  // Base
  if (root == NULL) {
    movements++;
    root->movements = root->movements + movements;
    return root; 
  }

  // Searching
  if (plate < root->plate) {
    movements++;
    root->left = deleteNode(root->left, plate, movements);
  }

  else if (plate > root->plate) {
    movements++;
    root->right = deleteNode(root->right, plate, movements);
  }

  else {
    
    // Only one child or none
    if ((root->left == NULL) || (root->right == NULL)) { 
      struct AVLnode* n = root->left ? root->left : root->right; // Auxiliar
     
      //  No child
      if (n == NULL) {
        n = root; 
        root = NULL;
      } 
      
      // One child
      else *root = *n; // Saving

      free(n); // Deleting
    }
    
    // Two children
    else {
      // Get smallest in the right
      struct AVLnode* min_n = min_Node(root->right);
      
      // Save the data
      root->plate = min_n->plate;

      // Delete min_n with recursion and go to another child
      root->right = deleteNode(root->right, min_n->plate, movements);
    }
  }
  // Tree has only one node
  if (root == NULL) return root; 

  
  root->height = max(height(root->left), height(root->right)) + 1;
  
  // Check and fix the balance
  int actual_balance = getTreebalance(root);
  
  // Left Left Case
  if ((actual_balance > 1) && (getTreebalance(root->left) >= 0)) {
    root->movements++;
    return rightRotation(root);
  }
  
  // Right Right Case
  if ((actual_balance < -1) && (getTreebalance(root->right) <= 0)) {
    root->movements++;
    return leftRotation(root);
  }

  // Left Right Case
  if ((actual_balance > 1) && (getTreebalance(root->left) < 0)) {
    root->left->movements++;
    root->left = leftRotation(root->left);
    root->movements++;
    return rightRotation(root);
  }

  // Right Left Case
  if ((actual_balance < -1) && (getTreebalance(root->right) > 0)) {
    root->right->movements++;
    root->right = rightRotation(root->right);
    root->movements++;
    return leftRotation(root);
  }

  // Returning
  return root;
}

void deleteTree (struct AVLnode* root) {
  if (root) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void print_PreOrder (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (root != NULL) {
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_PreOrder(ref->left);
    print_PreOrder(ref->right);
  }
}

void print_InOrder (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_InOrder(ref->left);
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d\n", root->plate, root->time, root->movements);
    print_InOrder(ref->right);
  }
}

void print_PostOrder(struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_PostOrder(ref->left);
    print_PostOrder(ref->right);
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d\n", root->plate, root->time, root->movements);
  }
}

void main() {
  struct AVLnode* root = NULL;
  struct AVLnode* temp = NULL;
  int n_comp = 0;
  int h;

  // Inserting
  printf("\nParking...\n");
  root = insertNode(root, "0004", 50, 0); 
  root = insertNode(root, "0002", 30, 0); 
  root = insertNode(root, "0001", 40, 0); 
  root = insertNode(root, "0003", 40, 0); 
  root = insertNode(root, "0005", 32, 0); 
  root = insertNode(root, "0006", 64, 0); 
  root = insertNode(root, "0000", 20, 0);
  root = insertNode(root, "0007", 80, 0);
  root = insertNode(root, "0008", 100, 0);

  printf("\nAVL Tree:\n");
  print_PreOrder(root);

  // Searching and comparing
  printf("\nSearching the vehicle and calculating...");
  temp = searchAVLnode(root, "0001", n_comp);
  printf("The height of Node is: %d", temp->height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  temp = searchAVLnode(root, "0005", n_comp);
  printf("The height of Node is: %d", temp->height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  temp = searchAVLnode(root, "0000", n_comp);
  printf("The height of Node is: %d", temp->height);
  printf("\n");

  printf("\nSearching the vehicle and calculating...");
  temp = searchAVLnode(root, "0008", n_comp);
  printf("The height of Node is: %d", temp->height);
  printf("\n");

  /* 
  Número de comparações = 
  3 + 3 + 4 + 4 =
  14

  Média de comparações = 
  14 / 4 =
  3,5
  
  O portão de saída pode ser determinado simplesmente calculado a altura do nó e a altura máxima da árvore. 
  Caso (valor da altura do nó < (altura máxima/2)) o veículo deverá sair por cima.
  Caso (valor da altura do nó >= (altura máxima/2)) o veículo deverá sair por baixo.
  */

  // Deleting
  printf("\nDeleting...");
  root = deleteNode(root, "0004", n_comp);
  printf("\nVehicle %s removed", "0004");
  
  // Searching
  printf("\n\nSearching...");
  searchAVLnode(root, "0005", n_comp);

  printf("\nAfter deleting:\n");
  print_PreOrder(root);
  
  // Cleaning
  deleteTree(root);
}