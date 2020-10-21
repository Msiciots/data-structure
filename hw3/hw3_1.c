#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// node in queue
typedef struct nodeq {
    int value;
    struct nodeq *next;
} node_q;
// node in stack
typedef struct nodes {
    int value;
    struct nodes *next;
    struct nodes *pre;
} node_s;
int main(int argc, char *argv[]) {
  
  node_q *head_qA = NULL;
  node_q *tail_qA = NULL;
  node_q *head_qB = NULL;
  node_q *tail_qB = NULL;
  node_s *tail_s = NULL;
  node_q *head_output = NULL;
  node_q *tail_output = NULL;

  int pop_element;
  FILE *input;
  input = fopen(argv[1], "r");
  char line[256];
  int count = 1;
  while (fgets(line, sizeof(line), input)) {
      getchar();
    printf("%d %s\n",count++, line);
    char *p = strtok(line, " ");
    if (!strcmp(p, "PUSH")) {
      p = strtok(NULL, "\n");
      node_s *tmp = malloc(sizeof(node_s));
      tmp->value = atoi(p);
      if(tail_s){
          tmp->pre = tail_s;
          tail_s = tail_s->next = tmp;
      }
      else {           // first element in stack
          tmp->pre = NULL;
          tail_s = tmp;
      }
      tmp->next = NULL;
      
    } else if (!strcmp(p, "POP\n")) {
      pop_element = tail_s->value;
      tail_s = tail_s->pre;
      free(tail_s->next);
      tail_s->next = NULL;
      printf("pop:%d\n",pop_element);
      printf("tail_s:%d\n",tail_s->value);

    } else if (!strcmp(p, "ENQUEUE")) {
      p = strtok(NULL, "\n");
        node_q *tmp = malloc(sizeof(node_q));
        tmp->value = pop_element;
        tmp->next = NULL;
      if (!strcmp(p, "A")) {
          if(head_qA)
              tail_qA = tail_qA->next = tmp; 
          else
              head_qA = tail_qA = tmp;
      } else if (!strcmp(p, "B")) {
          if(head_qB)
              tail_qB = tail_qB->next = tmp; 
          else
              head_qB = tail_qB = tmp;
      }

    } else if (!strcmp(p, "DEQUEUE")) {
      p = strtok(NULL, "\n");
      node_q *tmp;
      if (!strcmp(p, "A")) {
            tmp = head_qA;
          if (head_qA->next){ // if not only one element
            head_qA = head_qA->next;
          }
          else{
            head_qA = tail_qB = NULL;
          }
      } else if (!strcmp(p, "B")) {
            tmp = head_qB;
          if (head_qB->next){ // if not only one element
            head_qB = head_qB->next;
          }
          else{
            head_qB = tail_qB = NULL;
          }
      }
      if(head_output){
        tail_output = tail_output->next = tmp;
      }
      else{ // first element in output list
        head_output = tail_output = tmp;
        printf("head:%d tail:%d\n",head_output->value,tail_output->value);
      }
      free(tmp);
    }
  }
  for (node_q *p = head_output; p; p = p->next) {
    
    printf("%d\n", p->value);
  }
  fclose(input);
  return 0;
}
