#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Employee { // Employee
  char *name; // Employee name
  unsigned int Id; // Employee id
  int age; // Employee age
  bool free; // Employee state
  struct Employee* next; // Next employee
};

struct Queue_Employees { // Queue struct
  struct Employee *front;
  struct Employee *rear;
};

int length_Queue (struct Queue_Employees* q) { // Lenght of queue
  struct Employee* ref = q->front;
  int length = 0; 
  while (ref != NULL) {
    length = length + 1;
    ref = ref->next;
  }
  return length;
}

struct Employee* searchEmployee (struct Queue_Employees* q, char *name) {
  struct Employee* ref = q->front;
  while (ref->name != name) {
    ref = ref->next;
  }
  return ref;
}

void setEmployee_state (struct Queue_Employees* q, char *name, bool state) { // Set a state to a employee
  struct Employee* employee = searchEmployee(q, name);
  employee->free = state;
}

struct Employee* newEmployee (char *name, int age, unsigned int id) { // Create a employee
  struct Employee* employee = (struct Employee*) malloc (sizeof(struct Employee));
  employee->name = name;
  employee->age = age;
  employee->Id = id;
  employee->free = true;
  employee->next = NULL;
  printf("Employee: %s was registred in the system\n", employee->name);
  return employee;
}

struct Queue_Employees* createQueue_Employees () { // Create a queue
  struct Queue_Employees* Queue_Employees = (struct Queue_Employees*) malloc (sizeof(struct Queue_Employees));
  Queue_Employees->front = NULL;
  Queue_Employees->rear = NULL;
  return Queue_Employees;
}

void insertEmployee (struct Queue_Employees* q, char *name, int age, unsigned int id) { // Inserting a employee in the queue
  struct Employee* new = newEmployee(name, age, id);
  if (q->rear == NULL) {
    q->front = q->rear = new;
    printf("Employee: %s is in the service queue\n", new->name);
    return;
  }
  q->rear->next = new;
  q->rear = new;
  printf("Employee: %s is in the service queue\n", new->name);
}

void removeEmployee (struct Queue_Employees* q) { // Removing
  if (q->front == NULL) return;
    
  struct Employee* n = q->front;
  q->front = q->front->next;

  if (q->front == NULL) q->rear = NULL;
  printf("Employee: %s was removed from system\n", n->name);
  free(n);
}

// struct Employee* swap (struct Employee* employee1, struct Employee* employee2) { // Swap employees position's --> BubbleSort
//   struct Employee* temp;
//   temp = employee2->next;
//   employee2->next = employee1;
//   employee1->next = temp;
//   return employee2;
// }


// void bubbleSort_Id (struct Queue_Employees* queue, int lenght) { // BubbleSort ID
//   struct Employee* front;
//   int i, j, swapped;
//   int lenght1 = length(queue);
//   for (int i = 0; i <= lenght1; i++) {
//     front = queue->front;
//     swapped = 0;
//     for (int j = 0; j < lenght1 - i - 1; j++) {
//       struct Employee* employee1 = front;
//       struct Employee* employee2 = employee1->next;
//       if (employee1->Id > employee2->Id) {
//         front = swap(employee1, employee2);
//         swapped = 1;
//       }
//       front = front->next;
//     }
//     if (swapped == 0) break;
//   }
// }

void printQueue_Employees (struct Queue_Employees* q) { // Printing name, age, id, and employee's state
  struct Employee* current = q->front;
  while (current != NULL) {
    printf("Employee - %s, Age: %d years, Id: %d, Free: %s\n",current->name, current->age, current->Id,
    current->free ? "true" : "false");
    current = current->next;
  }
}

void main() { // Main
  struct Queue_Employees* q = createQueue_Employees(); // Create a new queue
  
  // Testing
  insertEmployee(q, "Lucas", 27, 2019001);
  insertEmployee(q, "Pedro", 49, 2019002);
  insertEmployee(q, "Jose", 31, 2019003);
  insertEmployee(q, "Tiago", 40, 2019004);
  insertEmployee(q, "Larissa", 30, 2019005);
  
  // Testing
  removeEmployee(q); 
  removeEmployee(q);

  // bubbleSort_Id(q, length(q)); // Not working

  printf("\nLenght of Queue: %d\n", length_Queue(q));

  printf("\nQueue of employees:\n");
  printQueue_Employees(q);

  free(q);
}