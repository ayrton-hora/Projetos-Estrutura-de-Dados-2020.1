// Avaliação 2 - Estrutura de dados - T02
// Professor Doutor Rodolfo Botto de Barros Garcia
// Aluno: Ayrton Fernandes Hora
// Matrícula: 201800083651 
// E-mail: ayrtonhora@academico.ufs.br

// Fase 3 - Two gate's update (new search methods)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 1000 // Size of the Hash Table

typedef struct Linked_list Linked_list;

struct Linked_list {
  struct Data* data;
  struct Linked_list* next;
};

typedef struct Data Data;

struct Data {
  char* key;
  char* plate;
  float time;
  int movements;
};

typedef struct Hash_table Hash_table;

struct Hash_table {
  int size;
  int elements;
  struct Data** data_array;
  struct Linked_list** chaining;
};

struct Linked_list* createLLNode (struct Data* data) {
  struct Linked_list* new = (Linked_list*) malloc (sizeof(struct Linked_list));
  new->data = data;
  new->next = NULL;
  return new;
}

struct Linked_list* insertLLNode (struct Linked_list* lst, Data* data) {
  struct Linked_list* node = createLLNode(data);
  // Head case
  if (!lst) {
    lst = node;
    printf("Vehicle %s parked\n", node->data->plate);
    return lst;
  }

  // Next
  else if (lst->next == NULL) {
    lst->next = node;
    printf("Vehicle %s parked\n", node->data->plate);
    return lst;
  }

  // Searching free space
  struct Linked_list* ref = lst;
  while (ref->next->next != NULL) ref = ref->next;
  ref->next = node;
  printf("Vehicle %s parked\n", node->data->plate);

  // Returning
  return lst;
}

struct Data* popLLNode (struct Linked_list* lst) {  
  if (lst == NULL) return NULL;

  if (lst->next == NULL) return NULL;

  struct Linked_list* ref = lst;
  struct Linked_list* ref_next = lst->next;
  struct Data* popped = NULL;
  
  ref->next = NULL;
  lst = ref_next;

  memcpy(ref->data, popped, sizeof(struct Data));
  
  free(ref->data->key);
  free(ref->data->plate);
  free(ref->data);
  free(ref);

  return popped;
}

void clear_Linkedlist (struct Linked_list* lst) {
  struct Linked_list* ref = lst;
  while (lst != NULL) {
    ref = lst;
    lst = lst->next;
    free(ref->data->key);
    free(ref->data->plate);
    free(ref->data);
    free(ref);
  }
}

struct Linked_list** createChaining (struct Hash_table* table) {
  struct Linked_list** chains = (Linked_list**) calloc (table->size, sizeof(Linked_list*));
  
  for (int i = 0; i < table->size; i++) chains[i] = NULL;

  return chains;
}

void clear_Chains (struct Hash_table* table) {
  struct Linked_list** chains = table->chaining;

  for (int i = 0; i < table->size; i++) clear_Linkedlist(chains[i]);

  free(chains);
}
 
unsigned long hash_function (char* string) {
  unsigned long i = 0;
  for (int j = 0; string[j]; j++) i = i + string[j];
  return i % CAPACITY;
}

struct Data* createData (char* key, char* plate, float time, int movements) {
  struct Data* new = (struct Data*) malloc(sizeof(struct Data));
  new->key = (char*) malloc (strlen(key) + 1);
  new->plate = (char*) malloc (strlen(plate) + 1);

  strcpy(new->key, key);
  strcpy(new->plate, plate);
  new->time = time;
  new->movements = movements;
  return new;
}

struct Hash_table* createTable (int size) {
  struct Hash_table* new_table = (struct Hash_table*) malloc (sizeof(struct Hash_table));
  new_table->size = size;
  new_table->elements = 0;
  new_table->data_array = (struct Data**) calloc (new_table->size, sizeof(struct Data*));
  
  // Setting Null
  for (int i = 0; i < new_table->size; i++) {
    new_table->data_array[i] = NULL;
  }
  
  // Creating chaining
  new_table->chaining = createChaining(new_table);

  return new_table;
}

struct Data* search_Data (struct Hash_table* table, char* key, int n_comp) {
  int index = hash_function(key);
  struct Data* target_data = table->data_array[index];
  struct Linked_list* chaining_ref = table->chaining[index];
  
  // Searching
  while (target_data != NULL) {
    if (strcmp(target_data->key, key) == 0) {
      n_comp++;
      printf("\nNumber of comparisons: %d\n", n_comp);
      return target_data;
    }

    if (chaining_ref == NULL) {
      printf("\nNumber of comparisons: %d\n", n_comp);
      return NULL;
    }

    target_data = chaining_ref->data;
    n_comp++;
    chaining_ref = chaining_ref->next;
  }

  // Returning
  printf("\nNumber of comparisons: %d\n", n_comp);
  return NULL;
}

void colision (struct Hash_table* table, unsigned long index, Data* data) {
  struct Linked_list* chaining_head = table->chaining[index];

  // If is empty
  if (chaining_head == NULL) {
    chaining_head = (Linked_list*) malloc (sizeof(struct Linked_list));
    chaining_head->data = data;
    chaining_head->next = NULL;
    table->chaining[index] = chaining_head;
    printf("Vehicle %s parked\n", chaining_head->data->plate);
  }

  // If not
  else table->chaining[index] = insertLLNode(chaining_head, data);
}

void insert_Data (struct Hash_table* table, char* key, char* plate, float time, int movements) {
  struct Data* new = createData(key, plate, time, movements);

  // Find the index
  int index = hash_function(key);

  struct Data* current_data = table->data_array[index];

  // If the key does not exist
  if (current_data == NULL) {
    
    // If table is full
    if (table->elements == table->size) printf("Error: Hash Table is full\n");

    // Insert
    table->data_array[index] = new;
    printf("Vehicle %s parked\n", plate);
    table->elements++;
  }
  
  // If key exist in table
  else {
    
    // Comparing
    if (strcmp(current_data->key, key) == 0) {
      strcpy(table->data_array[index]->plate, plate);
      table->data_array[index]->time = time;
      table->data_array[index]->movements = movements;
      printf("Vehicle %s parked\n", plate);
    }
    
    // Collision
    else colision(table, index, new);
  }
}

void clear_Data (struct Data* data) {
  free(data->key);
  free(data->plate);
  free(data);
}

void delete_Data (struct Hash_table* table, char* key) {
  int index = hash_function(key);
  struct Data* ref_data = table->data_array[index];
  struct Linked_list* ref_chains = table->chaining[index];

  // if is NULL, end
  if (ref_data == NULL) return; 
  
  // Searching
  else {
    // No collision, just remove
    if ((ref_chains == NULL) && (strcmp(ref_data->key, key) == 0)) {
      table->data_array[index] = NULL;
      clear_Data(ref_data);
      table->elements--;
    }

    // Collision
    else if (ref_chains != NULL) {
      // Key is in the head
      if (strcmp(ref_data->key, key) == 0) {
        
        clear_Data(ref_data);
        
        struct Linked_list* temp = ref_chains;
        ref_chains = ref_chains->next;
        temp->next = NULL;    
        table->data_array[index] = createData(temp->data->key, temp->data->plate, temp->data->time, temp->data->movements);

        clear_Linkedlist(temp);
        
        table->chaining[index] = ref_chains;
      }
      // Key is in the Linked List
      struct Linked_list* current = ref_chains;
      struct Linked_list* previest = NULL;
      
      // Searching in the chaining
      while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
          // First in the chaining
          if (previest == NULL) {
            clear_Linkedlist(ref_chains);
            table->chaining[index] = NULL;
          }
          // If not
          else {
            previest->next = current;
            current->next = NULL;
            clear_Linkedlist(current);
            table->chaining[index] = ref_chains;
          }
        }
        // Possible error
        current = current->next;
        previest = current;
      } 
    }
  }
}

void clear_Table (struct Hash_table* table) {
  for (int i = 0; i < table->size; i++) {
    struct Data* ref = table->data_array[i];
    
    if (ref != NULL) clear_Data(ref);
  }
  clear_Chains(table);
  free(table->data_array);
  free(table);
}

void print_Search(struct Hash_table* table, char* key, int n_comp) {
  struct Data* temp = NULL; 

  if ((temp = search_Data(table, key, n_comp)) == NULL) printf("The vehicle %s doesn't exist\n", key);

  else printf("Vehicle %s was found!\nKey: %s, Value: %s, Time: %0.0f, Movements: %d\n", temp->plate, key, temp->plate, temp->time, temp->movements);

}

void print_Table (struct Hash_table* table) {
    printf("\nHash Table\n--------------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->data_array[i]) {
            printf("Index: %d, Key: %s, Data: %s, Time: %0.0f, Movements: %d\n", i, table->data_array[i]->key, table->data_array[i]->plate, table->data_array[i]->time, table->data_array[i]->movements);
            if (table->chaining[i]) {
              printf(" '--> Chaining ");
              struct Linked_list* ref = table->chaining[i];
              while (ref != NULL) {
                printf("--> Key: %s, Data: %s, Time: %0.0f, Movements: %d ", ref->data->key, ref->data->plate, ref->data->time, ref->data->movements);
                ref = ref->next;
              }
            }
            // printf("\n");
        }
    }
    printf("\n--------------------------------------\n\n");
}

void main () {
  struct Hash_table* table = createTable(CAPACITY);
  int n_comp = 0;

  // Inserting
  printf("\nParking...\n");
  insert_Data(table, "1", "0004", 50, 1);
  insert_Data(table, "2", "0002", 30, 1);
  insert_Data(table, "3", "0001", 40, 1);
  insert_Data(table, "4", "0003", 40, 1);
  insert_Data(table, "Hel", "0005", 32, 1); 
  insert_Data(table, "Cau", "0006", 64, 2); // Chain
  insert_Data(table, "Hdm", "0000", 20, 3); // Chain
  insert_Data(table, "5", "0007", 80, 1);
  insert_Data(table, "6", "0008", 100, 1);


  // Searching 
  printf("\nSearching the vehicle...");
  print_Search(table, "Hel", n_comp);

  printf("\nSearching the vehicle...");
  print_Search(table, "Cau", n_comp);

  printf("\nSearching the vehicle...");
  print_Search(table, "4", n_comp);

  // Searching and comparing
  printf("\nSearching the vehicle and calculating...");
  print_Search(table, "3", n_comp);

  printf("\nSearching the vehicle and calculating...");
  print_Search(table, "Hel", n_comp);
  
  printf("\nSearching the vehicle and calculating...");
  print_Search(table, "Hdm", n_comp);

  printf("\nSearching the vehicle and calculating...");
  print_Search(table, "6", n_comp);

  /* 
  Número de comparações = 
  1 + 1 + 3 + 1 =
  6

  Média de comparações = 
  6 / 4 =
  1,5
  
  O portão de saída pode ser determinado simplesmente calculado a altura do nó e a altura máxima da árvore. 
  Caso (valor da altura do nó < (altura máxima/2)) o veículo deverá sair por cima.
  Caso (valor da altura do nó >= (altura máxima/2)) o veículo deverá sair por baixo.
  */
  
  // Deleting
  printf("\nDeleting...");
  delete_Data(table, "4");
  printf("\nVehicle %s removed\n", "0004");
  
  // Printing
  printf("\nPrinting...");
  print_Table(table);

  // Cleaning
  clear_Table(table);
}