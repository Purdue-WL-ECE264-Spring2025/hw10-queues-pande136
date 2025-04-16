#include "linked_list.h"


#include <stdlib.h>




struct list_node *new_node(size_t value) { 

  struct list_node *node = malloc(sizeof(struct list_node));

  if (node == NULL) {

    return NULL;

  }

  node->value = value;

  node->next = NULL;

  return node; 

}


void insert_at_head(struct linked_list *list, size_t value) {

  

  struct list_node *temp = new_node(value);

  if(temp == NULL) {

    return;

  }

  temp->next = list->head;

  list->head = temp;

}


void insert_at_tail(struct linked_list *list, size_t value) {

  struct list_node *temp = new_node(value);

  if (temp == NULL) {

    return;

  }

  if (list->head == NULL) {

    list->head = temp;

    return;

  }

  struct list_node *tail = list->head;

  while (tail->next != NULL) {

    tail = tail->next;

  }

  tail->next = temp;

}


size_t remove_from_head(struct linked_list *list) { 

  if (list->head == NULL) {

    return 0;

  }

  struct list_node *temp = list->head;

  size_t value = temp->value;

  list->head = list->head->next;

  free(temp);

  return value;

}


size_t remove_from_tail(struct linked_list *list) { 

  if (list->head == NULL) {

    return 0; 

  }

  if (list->head->next == NULL) {

    size_t value = list->head->value;

    free(list->head);

    list->head = NULL;

    return value;

  }


  struct list_node *prev = NULL;

  struct list_node *curr = list->head;

  while (curr->next != NULL) {

    prev = curr;

    curr = curr->next;

  }

  prev->next = NULL;

  size_t value = curr->value;

  free(curr);

  return value;

}


void free_list(struct linked_list list) {

  struct list_node *curr = list.head;

  while (curr != NULL) {

    struct list_node *next = curr->next;

    free(curr);

    curr = next;

  }

  list.head = NULL;

}


// Utility function to help you debugging, do not modify

void dump_list(FILE *fp, struct linked_list list) {

  fprintf(fp, "[ ");

  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {

    fprintf(fp, "%zu ", cur->value);

  }

  fprintf(fp, "]\n");

}
