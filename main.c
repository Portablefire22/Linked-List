#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  struct node* prev;
  int item;
  struct node* next;
} node_t;

void print_list(node_t* head) {
  printf("Normal: ");
  printf("[");
  node_t* current = head;
  while (1) {
    printf("%d", current->item);
    current = current->next;
    if (current == NULL) {
      break;
    }
    printf(",");
  }
  printf("]\n");
}

void rev_print_list(node_t* head) {
  printf("Reversed: ");
  printf("[");
  node_t* current = head;
  while (1) { // Get final item
    if (current->next == NULL) {
      break;
    }
    current = current->next;
  }
  while (1) {
    printf("%d", current->item);
    current = current->prev;
    if (current == NULL) {
      break;
    }
    printf(",");
  }
  printf("]\n");
}

void push(node_t* head, int value) {
  node_t* current = head;
  while (1) { // Get to last item
    if (current->next == NULL) {
      current->next = (node_t*) malloc(sizeof(node_t));
      if (current == NULL) {
        printf("Could not allocate memory");
        return;
      }
      current->next->prev = current;
      current = current->next;
      break;
    }
    current = current->next;
  }
  current->item = value;
  current->next = NULL;
}

void insert(node_t* head, int value, int index) {
  int i = 0;
  while (i != index - 1) {
    head = head->next;
    i++;
  }
  node_t* tmp = (node_t*) malloc(sizeof(node_t));

  tmp->prev = head;
  tmp->item = value;
  tmp->next = head->next;
  tmp->next->prev = tmp;
  head->next = tmp;
}

void free_list(node_t* head) {
  node_t* tmp = NULL;
  while (head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}

int main() {

  node_t* head = NULL;
  head = (node_t*) malloc(sizeof(node_t));

  if (head == NULL) { // If failed to allocate memory
    return -1; 
  }
  head->prev = NULL;
  head->item = 0;
  head->next = NULL;

  for (int i = 1; i <= 25; i++) {
    push(head, i);
  }

  insert(head, 420, 3);

  print_list(head);
  rev_print_list(head);
  free_list(head);
  return 1;
}

