#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node {
  int value;
  struct node *next;
} node_t;
void read_list(node_t **head, node_t **tail, char *inputfile) {
  FILE *f = fopen(inputfile, "r");
  char line[3];
  while (fscanf(f, "%s", line) != EOF) {
    node_t *new_node = malloc(sizeof(node_t));
    // atoi(line) == 0 -> 'A', 'J', 'Q', 'K'
    // atoi(line) != 0 -> 2 ~ 10
    new_node->value = atoi(line) ? atoi(line) : line[0];
    if (!*head) { // Add first element to list
      *head = new_node;
      *tail = new_node;
    } else {
      (*tail)->next = new_node;
      (*tail) = new_node;
    }
    new_node->next = NULL;
  }
}
void print_list(node_t *head, FILE *output) {
  node_t *tmp;
  for (tmp = head; tmp; tmp = tmp->next) {

    if (tmp->value > 10)
      fprintf(output, "%c", tmp->value);
    else
      fprintf(output, "%d", tmp->value);
    if (tmp->next)
      fprintf(output, " ");
    else
      fprintf(output, "\n");
  }
}
void draw(node_t *head, node_t *tail, FILE *output) {
  int index = 13;
  while (head) {
    print_list(head, output);
    int a;
    switch (index) {
    case 1:
      a = 'A';
      break;
    case 11:
      a = 'J';
      break;
    case 12:
      a = 'Q';
      break;
    case 13:
      a = 'K';
      break;
    default:
      a = index;
      break;
    }

    if (head->value == a) { // draw out
      node_t *tmp = head;
      head = head->next;
      free(tmp);
      index--;
    } else { // move to tail
      tail = tail->next = head;
      head = head->next;
      tail->next = NULL;
    }
  }
}
int main(int argc, char *argv[]) {

  node_t *head = NULL;
  node_t *tail = NULL;
  read_list(&head, &tail, argv[1]);
  FILE *output = fopen(argv[2], "w");
  draw(head, tail, output);
  fclose(output);
  return 0;
}
