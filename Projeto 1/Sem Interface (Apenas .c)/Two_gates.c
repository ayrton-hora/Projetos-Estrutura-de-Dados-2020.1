// Avaliação 1 - Estrutura de dados - T02
// Aluno: Ayrton Fernandes Hora
// Matrícula: 201800083651 
// E-mail: ayrtonhora@academico.ufs.br

// Fase 2 - (two gate's)

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "Linked_Stack.h"
// #include "Linked_Queue.h"
// #include "Doubly_Linked_List.h"

// Not finished
// struct meta1 { // Meta1 
//   float top_gate = 0; // Money
//   bool upgrade = false; // State of upgrade
// };

// Global variables
float top_gate = 0; // Money
bool upgrade = false; // State of upgrade

// Cash of park lot for doubly linked list structure
void cash_DLL (struct DL_Vehicle* vehicle) { 
  float time = vehicle->time; // In seconds
  while (time > -1) {
     if (time =< 3600) {
      top_gate = top_gate + 12;
      time = -1;
    }
    if (time > 3600) {
      top_gate = top_gate + 12;
      time = time - 3600;
    }
  }
}

void main() {
  // Creating root's
  struct Queue_Employees* queue_e = createQueue_Employees();
  struct Stck_Vehicle* root = NULL;
  struct DL_Vehicle* head = NULL; 

  // Control variables
  int max = 8;
  int n;
  int total_movements;

  // Employee variables
  char *name;
  int id;
  unsigned int age;
  bool state;

  // Vehicles variables
  char *plate;
  int movements;
  float time;
  int pos;

  // Intro
  printf("|-----Welcome to the parking lot software-----|\n");
  printf("|-----Max capacity = %d vehicles-----|\n\n", max);
  while (n != -1) {
  
    // Interface
    printf("1 - Register a employee\n");
    printf("2 - Remove a employee\n");
    printf("3 - State of a employee\n");
    printf("4 - Show employee's\n");
    printf("5 - Number of employee's\n");
    printf("6 - Sort employee's by name\n");
    printf("7 - Sort employee's by Id\n");
    printf("8 - Sort employee's by age\n");
    printf("9 - Park a vehicle\n");
    printf("10 - Remove a vehicle\n");
    printf("11 - Show vehicles\n");
    printf("\nPlease choose a option:\n\n");
    scanf("%d", &n);
   
    // Loop
    if (n == 1) {
      printf("\nPlease type the employee name: ");
      scanf("%s", name);
      printf("\nPlease type the age of employee: ");
      scanf("%d", &age);
      printf("\nPlease type the Id of employee: ");
      scanf("%d", &id);
      printf("\n");
      insertEmployee(queue_e, name, age, id);
    }
    if (n == 2) {
      removeEmployee(queue_e);
    }
    if (n == 3) {
      printf("\nPlease type the employer name: ");
      scanf("%s", name);
      printf("\nPlease type the state to set: 'true' or 'false'");
      scanf(&state ? "true" : "false");
      setEmployee_state(queue_e, name,  state);
    }
    if (n == 4) {
      printf("\nEmployees:\n");
      printQueue_Employees(queue_e);
    }
    if (n == 5) {
      printf("\nNumber of employees: %d\n", length_Queue(queue_e));
    }
    if (n == 6) {
      printf("\nSorry this service is unavailable");
    }
    if (n == 7) {
      printf("\nSorry this service is unavailable");
    }
    if (n == 8) {
      printf("\nSorry this service is unavailable");
    }
    if (n == 9) {
      printf("\nPlease type the plate: ");
      scanf("%s", plate);
      printf("\nPlease type the time: ");
      scanf("%f", &time);
      printf("\nPlease type the movements: ");
      scanf("%d", &movements);
      append(&head, plate, time, movements);
    }
    if (n == 10) {
      printf("\nPlease type the plate of vehicle: ");
      scanf("%s", plate);
      struct DL_Vehicle* v = searchDLVehicle(&head, plate);
      cash_DLL(v);
      removeDLLVehicle(&head, plate);
    }
    if (n == 11) {
      printf("\nVehicles:\n");
      printList(head);
    }   
  }
  free(queue_e);
  free(root);
  free(head);
}




