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
  while (1) {
    printf("%d", head->item);
    head = head->next;
    if (head == NULL) {
      break;
    }
    printf(",");
  }
  printf("]\n");
}

void rev_print_list(node_t* head) {
  printf("Reversed: ");
  printf("[");
  while (1) { // Get final item
    if (head->next == NULL) {
      break;
    }
    head = head->next;
  }
  while (1) {
    printf("%d", head->item);
    head = head->prev;
    if (head == NULL) {
      break;
    }
    printf(",");
  }
  printf("]\n");
}

void push(node_t* head, int value) {
  while (1) { // Get to last item
    if (head->next == NULL) {
      head->next = (node_t*) malloc(sizeof(node_t));
      if (head->next == NULL) {
        printf("Could not allocate memory");
        return;
      }
      head->next->prev = head;
      head = head->next;
      break;
    }
    head = head->next;
  }
  head->item = value;
  head->next = NULL;
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

int* get(node_t* head, int index) {
  int i = 0;
  while (i != index) {
    head = head->next;
    if (head == NULL) {
      printf("Error: Index out of range!\n");
      return NULL;
    }
    i++;
  }
  return &head->item;
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

  int* res = get(head, 9);
  if (res == NULL) {
    return -1;
  }
  printf("Result: %d\n", *res);

  print_list(head);
  rev_print_list(head);
  free_list(head);
  return 1;
}

