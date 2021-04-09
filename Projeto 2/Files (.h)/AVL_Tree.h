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

struct AVLnode* min_AVLnode (struct AVLnode* root) {
  struct AVLnode* ref = root;
  while (ref->left != NULL) ref = ref->left;
  return ref;
}

struct AVLnode* createAVLnode (char *plate, float time, int movements) {
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
  
  n->height = max(height(n->left), height(n->right)) ;
  a->height = max(height(a->left), height(a->right)) ;
  
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

struct AVLnode* insertAVLnode (struct AVLnode* root, char *plate, float time, int movements) {
  // Base
  if (root == NULL) {
    movements++;
    printf("Vehicle %s parked\n", plate);
    return (createAVLnode(plate, time, movements)); 
  }

  // Searching
  if (plate < root->plate) {
    movements++;
    root->left = insertAVLnode(root->left, plate, time, movements);
  }

  else if (plate > root->plate) {
    movements++;
    root->right = insertAVLnode(root->right, plate, time, movements);
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
    return (rightRotation(root));  // <-1
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

struct AVLnode* deleteAVLnode (struct AVLnode* root, char *plate, int movements) {
  // Base
  if (root == NULL) {
    movements++;
    root->movements = root->movements + movements;
    return root; 
  }

  // Searching
  if (plate < root->plate) {
    movements++;
    root->left = deleteAVLnode(root->left, plate, movements);
  }

  else if (plate > root->plate) {
    movements++;
    root->right = deleteAVLnode(root->right, plate, movements);
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
      struct AVLnode* min_n = min_AVLnode(root->right);
      
      // Save the data
      root->plate = min_n->plate;

      // Delete min_n with recursion and go to another child
      root->right = deleteAVLnode(root->right, min_n->plate, movements);
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

void deleteAVLtree (struct AVLnode* root) {
  if (root) {
    deleteAVLtree(root->left);
    deleteAVLtree(root->right);
    free(root);
  }
}

void print_PreOrderAVLtree (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (root != NULL) {
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_PreOrderAVLtree(ref->left);
    print_PreOrderAVLtree(ref->right);
  }
}

void print_InOrderAVLtree (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_InOrderAVLtree(ref->left);
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d\n", root->plate, root->time, root->movements);
    print_InOrderAVLtree(ref->right);
  }
}

void print_PostOrderAVLtree(struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_PostOrderAVLtree(ref->left);
    print_PostOrderAVLtree(ref->right);
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d\n", root->plate, root->time, root->movements);
  }
}

// void main() {
//   struct AVLnode* root = NULL;
//   int n_comp = 0;

//   // Inserting
//   printf("\nParking...\n");
//   root = insertAVLnode(root, "0001", 50, 0); 
//   root = insertAVLnode(root, "0002", 30, 0); 
//   root = insertAVLnode(root, "0003", 40, 0); 
//   root = insertAVLnode(root, "0004", 32, 0); 
//   root = insertAVLnode(root, "0005", 64, 0); 
//   root = insertAVLnode(root, "0000", 20, 0); 

//   printf("\nAVL Tree:\n");
//   print_PreOrderAVLtree(root);

//   // Searching
//   printf("\nSearching...\n");
//   searchAVLnode(root, "0001", n_comp);

//   // Deleting
//   printf("\nDeleting...");
//   root = deleteAVLnode(root, "0004", n_comp);
//   printf("\nVehicle %s removed", "0004");
  
//   // Searching
//   printf("\n\nSearching...");
//   searchAVLnode(root, "0005", n_comp);

//   printf("\nAfter deleting:\n");
//   print_PreOrderAVLtree(root);
  
//   // Cleaning
//   deleteAVLtree(root);
// }