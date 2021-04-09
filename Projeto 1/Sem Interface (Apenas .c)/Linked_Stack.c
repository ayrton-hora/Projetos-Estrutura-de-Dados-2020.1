  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <string.h>

struct Stck_Vehicle { // Vehicle (after upper gate)
  char *plate; // Vehicle plate
  float time; // Vehicle time in the parking lot (seconds)
  int movements; // Number of movements per vehicle
  struct Stck_Vehicle *next; // Front link
};

struct Stck_Vehicle* createStckVehicle (char *plate, float time, int movements) { // Create and return a vehicle
  struct Stck_Vehicle* vehicle = (struct Stck_Vehicle*) malloc (sizeof(struct Stck_Vehicle));
  vehicle->plate = plate;
  vehicle->time = time;
  vehicle->movements = movements;
  vehicle->next = NULL;
  return vehicle;
}

bool isFull (struct Stck_Vehicle* root) { // Stack is full? (bool)
  if (root != NULL) return true;
  return false;
}

bool isEmpty (struct Stck_Vehicle* root) { // Stack is empty? (bool)
  if (root == NULL) return true;
  return false;
}

int length_LS (struct Stck_Vehicle** root) { // Return the length of stack
  struct Stck_Vehicle* ref = *root;
  int length = 0; 
  while (ref != NULL) {
    length = length + 1;
    ref = ref->next;
  }
  return length;
}

// void search (struct Stck_Vehicle** root, char *vehicle_plate) { // Search a vehicle
//   struct Stck_Vehicle* fst_stack = *root;
//   struct Stck_Vehicle* scd_stack = NULL;
//   struct Stck_Vehicle* temp = NULL;
//   while (fst_stack != NULL) {
//     if (fst_stack->plate == vehicle_plate) printf("Vehicle found: %s\n", vehicle_plate);
//     if (scd_stack == NULL) {
//       temp = fst_stack;
//       fst_stack = fst_stack->next;
//       temp->next = scd_stack;
//       scd_stack = temp;
//     }
//     else {
//       temp = fst_stack;
//       fst_stack = fst_stack->next;
//       temp->next = scd_stack;
//       scd_stack = temp;
//     }
//   }
//   temp = scd_stack;
//   while (temp != NULL) {  
//     scd_stack = scd_stack->next;
//     temp->next = fst_stack;
//     fst_stack = temp;
//     temp = scd_stack;
//   }
//   free(temp);
//   free(scd_stack);
// }

struct Stck_Vehicle* searchVehicle_Stck (struct Stck_Vehicle** root, char *v_plate) {
  struct Stck_Vehicle* ref = *root;
  while (ref != NULL) {
    if (ref->plate == v_plate) {
      return ref;
    }
    ref = ref->next;
  }
}

void push_stck (struct Stck_Vehicle** root, char *plate, float time, int movements) { // Insert in the top
  struct Stck_Vehicle* new = createStckVehicle(plate, time, movements);
  new->next = *root;
  *root = new;
}

void pop (struct Stck_Vehicle** root) { // Remove the top vehicle (stack propertie)
  if (isEmpty(*root)) return;  // If the stack is empty, stop

  struct Stck_Vehicle* top_stack = *root; // Top reference 
  
  *root = (*root)->next; // New top
  
  free(top_stack);
}

void removeStckVehicle (struct Stck_Vehicle** root, char *vehicle_plate) { // Remove a vehicle from your plate
  struct Stck_Vehicle* fst_stack = *root; // Main stack
  struct Stck_Vehicle* scd_stack = NULL; // Aux stack
  struct Stck_Vehicle* temp = NULL; // Temp varialble
  struct Stck_Vehicle* veh_removed = NULL; // Variable to delete the vehicle

  while (fst_stack != NULL) { 
    if (fst_stack->plate == vehicle_plate) { // If the vehicle is in the top
      printf("Vehicle %s found\n", vehicle_plate);
      temp = fst_stack;
      veh_removed = fst_stack;
      fst_stack = fst_stack->next;
      veh_removed->movements = temp->movements + 1;
      free(veh_removed);
      printf("Vehicle %s removed\n", vehicle_plate);
      break;
    }

    // If not, search
    if (scd_stack == NULL) { // If the aux stack is empty
      temp = fst_stack;
      fst_stack = fst_stack->next;
      temp->next = scd_stack;
      temp->movements = temp->movements + 1;
      scd_stack = temp;
    }
    else { // If the aux stack is not empty
      temp = fst_stack;
      fst_stack = fst_stack->next;
      temp->next = scd_stack;
      temp->movements = temp->movements + 1;
      scd_stack = temp;
    }
  }
  // Reordering
  temp = scd_stack;
  while (temp != NULL) {  
    scd_stack = scd_stack->next;
    temp->next = fst_stack;
    temp->movements = temp->movements + 1;
    fst_stack = temp;
    temp = scd_stack;
  }

  free(temp);
  free(scd_stack);
}

// char peek (struct Stck_Vehicle* root) { // Return the top (vehicle) of stack
//   if (isEmpty(root)) return "None";
//   return root->plate;
// }

void printStack (struct Stck_Vehicle* root) { // Printing the stack
  struct Stck_Vehicle* n = root;
  while (n != NULL) {
    printf("Vehicle: %s\n", n->plate);
    n = n->next;
  }
}

void main() {
  struct Stck_Vehicle* root = NULL; // Creating the root
  
  // Testing
  push_stck(&root, "0001", 10, 1);
  push_stck(&root, "0002", 20, 2);
  push_stck(&root, "0003", 30, 3);
  
  searchVehicle_Stck(&root, "0001");

  // removeStckVehicle(&root, "0001");

  // peek(root);
  
  // pop(&root);

  printf("\nLength of stack is: %d\n", length_LS(&root));
  
  printf("\nVehicles:\n");
  printStack(root);

  free(root);
}