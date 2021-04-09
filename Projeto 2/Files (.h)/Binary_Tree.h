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

struct TreeNode* createBinNode (char *plate, float time, int movements) {
  struct TreeNode* new = (struct TreeNode*) malloc(sizeof(struct TreeNode));
  new->plate = plate;
  new->time = time;
  new->movements = movements;
  new->height = 0;
  new->left = NULL;
  new->right = NULL;
  return new;
}

struct TreeNode* searchBinNode (struct TreeNode* root, char *plate, int n_comp) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    if (plate == ref->plate) {
      n_comp++;
      printf("\nVehicle %s was found, Total movements: %d\n", plate, n_comp);
      return ref; 
    }

    if (plate < ref->plate) {
      n_comp++;
      return searchBinNode(ref->left, plate, n_comp);
      
    }

    else {
      n_comp++;
      return searchBinNode(ref->right, plate, n_comp);
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
  struct TreeNode* search_n = searchBinNode(node, plate, n);
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

struct TreeNode* min_BinNode (struct TreeNode* root) {
  struct TreeNode* ref = root;
  while (ref && ref->left != NULL) ref = ref->left;
  
  return ref;
}

void insertBinNode (struct TreeNode** root, char *plate, float time, int movements, int n_comp) {
  struct TreeNode* ref = *root;
  struct TreeNode* temp = NULL;
  if (*root == NULL) {
    n_comp++;
    *root = createBinNode(plate, time, n_comp);
    (*root)->height = n_comp - 1;
    // temp = search_forFix(ref, plate,)
    printf("Vehicle %s parked\n", plate);
  }

  else if (plate < (*root)->plate) {
    n_comp++;
    insertBinNode(&(*root)->left, plate, time, movements, n_comp);
  }

  else if (plate >= (*root)->plate) {
    n_comp++;
    insertBinNode(&(*root)->right, plate, time, movements, n_comp);
  }
}

struct TreeNode* deleteBinNode (struct TreeNode** root, char *plate) {
  struct TreeNode* temp = NULL;
  
  // Base
  if (*root == NULL) return *root; 
  
  // Data is smaller than
  if (plate < (*root)->plate) (*root)->left = deleteBinNode(&(*root)->left, plate); 

  // Data is greater than
  else if (plate > (*root)->plate) (*root)->right = deleteBinNode(&(*root)->right, plate); 

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
    temp = min_BinNode((*root)->right); 

    // Copy and save the data
    (*root)->plate = temp->plate; 

    // Delete smallest in the right (InOrder sucessor)
    (*root)->right = deleteBinNode(&(*root)->right, temp->plate); 
  }
  return (*root);
}

void deleteBinTree (struct TreeNode* root) {
  if (root) {
    deleteBinTree(root->left);
    deleteBinTree(root->right);
    free(root);
  }
}

void print_PreOrderBinTree (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (root != NULL) {
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_PreOrderBinTree(ref->left);
    print_PreOrderBinTree(ref->right);
  }
}

void print_InOrderBinTree (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_InOrderBinTree(ref->left);
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
    print_InOrderBinTree(ref->right);
  }
}

void print_PostOrderBinTree(struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_PostOrderBinTree(ref->left);
    print_PostOrderBinTree(ref->right);
    printf("Vehicle: %s, Time: %0.0f, Movements: %d, Height: %d\n", root->plate, root->time, root->movements, root->height);
  }
}

// void main() {
//   struct TreeNode* root = NULL;
//   int n_comp = 0;
//   int height;

//   // Inserting
//   printf("\nParking...\n");
//   insertBinNode(&root, "0004", 50, 0, n_comp);
//   insertBinNode(&root, "0002", 30, 0, n_comp);
//   insertBinNode(&root, "0001", 40, 0, n_comp);
//   insertBinNode(&root, "0003", 40, 0, n_comp);
//   insertBinNode(&root, "0005", 32, 0, n_comp);
//   insertBinNode(&root, "0006", 64, 0, n_comp);
//   insertBinNode(&root, "0000", 20, 0, n_comp);

//   // fix_BT_height(root, n_comp);

//   // Searching
//   printf("\nSearching...");
//   searchBinNode(root, "0001", n_comp);

//   printf("\nSearching the vehicle...");
//   height = heigh_BinaryNode(root, "0001", n_comp);
//   printf("The height of Node is: %d", height);
//   printf("\n");

//   // Deleting
//   printf("\nDeleting...");
//   deleteBinNode(&root, "0004");
//   printf("\nVehicle %s removed\n", "0004");

//   printf("\nThe minimum Node is: ");
//   printf("%s\n", min_BinNode(root)->plate);

//   printf("\nBinary Tree:\n");
//   print_PreOrderBinTree(root);

//   // Cleaning
//   deleteBinTree(root);
// }