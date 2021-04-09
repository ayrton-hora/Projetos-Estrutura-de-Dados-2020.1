  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <assert.h>
  
struct DL_Vehicle { // Vehicle (before upper gate)
  char *plate; // Vehicle plate
  float time; // Vehicle time in the parking lot
  int movements; // Number o movements per vehicle
  int pos; // Vehicle position in the parking lot
  struct DL_Vehicle* next; // Front link
  struct DL_Vehicle* prev; // Back link
};

struct DL_Vehicle* createDLVehicle (char *plate, float time, int movements) { // Create and return a vehicle 
  struct DL_Vehicle* new = (struct DL_Vehicle*) malloc (sizeof(struct DL_Vehicle)); 
  new->plate = plate;
  new->time = time;
  new->movements = movements;
  new->next = NULL;
  new->prev = NULL;
  return new; 
}

int length_DLL (struct DL_Vehicle** head) { // Return the lenght of list
  struct DL_Vehicle* ref = *head; // Head reference 
  int length = -1;  // Starts in -1
  while (ref != NULL) {  // Main loop
    length++;
    ref = ref->next;
  }
  return length;
}

struct DL_Vehicle* lastVehicle (struct DL_Vehicle** head) { // Return the last vehicle of list
  struct DL_Vehicle* ref = *head; // Head reference
  while (ref->next != NULL) { // Searching
    ref = ref->next;
  }
  return ref;
}

void push_DLL (struct DL_Vehicle** head, char *plate, float time, int movements) { // Inserting in the beginning
  struct DL_Vehicle* new = createDLVehicle(plate, time, movements);
  new->next = *head; 
  new->prev = NULL;

  if (*head != NULL) (*head)->prev = new;

  *head = new;
  new->pos = -1;

  struct DL_Vehicle* ref = *head; // Fixing another vehicle's positions
  while (ref != NULL) {
    ref->pos++;
    ref = ref->next;
  }
  return;
}

void append (struct DL_Vehicle** head, char *plate, float time, int movements) { // Inserting at the end
  struct DL_Vehicle* new = createDLVehicle(plate, time, movements);
  struct DL_Vehicle* last = *head;

  if (*head == NULL) {
    new->prev = NULL;
    *head = new;
    return;
  }
  while (last->next != NULL) last = last->next;

  last->next = new;
  new->prev = last;
  new->pos = length_DLL(head); // Vehicle position is equal to the lenght of list
  return;
}

struct DL_Vehicle* searchDLVehicle (struct DL_Vehicle** head, char *plate) {
  struct DL_Vehicle* ref = *head;
  while (ref->plate != plate) {
    ref = ref->next;
  }
  return ref;
}

int searchVehiclePos (struct DL_Vehicle** head, char *plate) { // Return the position of Vehicle v
  struct DL_Vehicle* ref = *head;

  if (ref == NULL) return -1; // If he is not in the list, return -1

  while (ref != NULL) { // Searching
    if (ref->plate == plate) {
      printf("Seaching...Vehicle found: %s in the position: %d\n", ref->plate, ref->pos);
      return ref->pos;
    }
    ref = ref->next;
  }
  return -1;
}

void removeDLLVehicle (struct DL_Vehicle** head, char *plate) { // Remove a vehicle from your plate
  struct DL_Vehicle* fst_list = *head; // Main list
  struct DL_Vehicle* scd_list = NULL; // Aux list

  struct DL_Vehicle* temp = NULL; // Temp variable
  struct DL_Vehicle* veh_removed = NULL; // Variable to delete the vehicle 
  struct DL_Vehicle* last_veh = lastVehicle(head); // Last vehicle of list
  struct DL_Vehicle* new_last1 = NULL; // Aux variable 1
  struct DL_Vehicle* new_last2 = NULL; // Aux varialble 2

  int lst_lenght = length_DLL(head); // Lenght of list
  int half_lenght = (lst_lenght / 2); // Half lenght
  int vehicle_pos = searchVehiclePos(head, plate); // Vehicle position in the list
   
  if (fst_list == NULL) return; // If list is empty, stop

  if (vehicle_pos == -1) return; // If vehicle is not in the list, stop

  // Remove the vehicle based on its position in the list

  // If the vehicle is halfway down, search and remove up to pos
  if (vehicle_pos <= half_lenght) {
    if (fst_list->plate == plate) { // If the vehicle is in the fst position
      printf("Vehicle found in the first position: %s\n", plate);
      temp = fst_list;
      veh_removed = fst_list;
      fst_list->next->prev = NULL;
      *head = fst_list->next;
      veh_removed->movements++;
      free(veh_removed);
      printf("Vehicle removed from the first position: %s\n", plate);
        
      // Fixing atribute position of the elements 
      struct DL_Vehicle* ref = *head;
      while (ref != NULL) {
        ref->pos--;
        ref = ref->next;
      }
    }
    else { // If not the fst
      while (fst_list->plate != plate) { // Search saving in another list (stack) saving the vehicles
        if (scd_list == NULL) { // If list (stack) is empty, insert in the beginnig
          temp = fst_list;
          fst_list = fst_list->next;
          temp->next = scd_list;
          temp->prev = NULL;
          temp->movements++;
          scd_list = temp;
        }
        else { // If list (stack) is not empty, push_DLL
          temp = fst_list;
          fst_list = fst_list->next;
          scd_list->prev = temp;
          temp->next = scd_list;
          temp->prev = NULL;
          temp->movements++;
          scd_list = temp;
        }
      }
      // Removing the vehicle
      printf("Vehicle found: %s in the position: %d\n", plate, fst_list->pos);
      veh_removed = fst_list;
      veh_removed->movements++;
      new_last1 = fst_list->next;
      new_last1->prev = NULL;
      printf("Vehicle removed: %s from the position: %d\n", plate, veh_removed->pos);
      free(veh_removed);
      
      // Reordening the list getting vehicle's from stack
      temp = scd_list;
      while (temp != NULL) {
        scd_list = scd_list->next;
        new_last1->prev = temp;
        temp->next = new_last1;
        temp->movements++;
        fst_list = temp;
        new_last1 = fst_list;
        temp = scd_list;
      }
    }
    fst_list->prev = NULL;
    // free(temp);
    free(scd_list);
  }

  // If the vehicle is halfway up, search from the last up to pos and remove
  if (vehicle_pos > half_lenght) {
    if (last_veh->plate == plate) { // If the vehicle is in the last position
      printf("Vehicle found in the last position: %s\n", plate);
  
      veh_removed = last_veh;
      veh_removed->movements++;
      veh_removed->prev->next = NULL;
      
      free(veh_removed);
      printf("Vehicle removed from the last position: %s\n", plate);
    }
    else { // If not
      while (last_veh->plate != plate) { // Searching vehicle
        if (scd_list == NULL) { // If scd_list is empty, insert in the head
          temp = last_veh;
          last_veh = last_veh->prev;
          temp->next = scd_list;
          temp->prev = NULL;
          temp->movements++;
          scd_list = temp;
        }
        else { // If not, insert in the head, push_DLLing
          temp = last_veh;
          last_veh = last_veh->prev;
          scd_list->prev = temp;
          temp->next = scd_list;
          temp->prev = NULL;
          temp->movements++;
          scd_list = temp;
        }
      }
      // Removing vehicle
      printf("Vehicle found: %s in the position: %d\n", plate, last_veh->pos);
      veh_removed = last_veh;
      veh_removed->movements++;
      new_last2 = last_veh->prev;
      new_last2->next = NULL;
      printf("Vehicle removed: %s from the position: %d\n", plate, veh_removed->pos);
      free(veh_removed);
      
      // Reordening 
      temp = scd_list;
      while (temp != NULL)
      scd_list = scd_list->next;
      new_last2->next = temp;
      temp->prev = new_last2;
      temp->movements++;
      new_last2 = temp;
      temp = scd_list;
    }
    // Cleaning
    // new_last2->next = NULL;
    free(temp);
    free(scd_list); 
  }

}

void printList(struct DL_Vehicle* head) { // Print the list, with Plate, time and movements
  while (head != NULL) {
    printf("Vehicle: %s, Time: %0.0f seconds, Movements: %d\n", head->plate, head->time, head->movements);  
    head = head->next;
  }
} 

// void main() { // Main
  // struct DL_Vehicle* head = NULL; // Creating the head
  
  // Testing
  // append(&head, "0001", 50, 1);
  // append(&head, "0002", 30, 2);
  // append(&head, "0003", 40, 3);
  // append(&head, "0004", 32, 4);
  // append(&head, "0005", 64, 5);
  // push_DLL(&head, "0000", 20, 8);

  // removeDLLVehicle(&head, "0005"); // Unstill not 100% working
  
  // printf("Lenght of Doubly Linked List is: %d\n", length(&head));

  // printList(head);

  // free(head);
// }