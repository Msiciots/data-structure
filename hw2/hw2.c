#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 256
int main(int argc, char *argv[]) {
  int queueA[size], queueB[size], stack[size], output[size];
  int stack_index = 0, queueA_font = 0, queueA_tail = 0, queueB_font = 0,queueB_tail = 0, output_index = 0;
  int pop_element;
  FILE *input;
  input = fopen("input.txt", "r");
  char line[256];
  while (fgets(line, sizeof(line), input)) {
    char *p = strtok(line, " ");
    if (!strcmp(p, "PUSH")) {
      p = strtok(NULL, "\n");
      int tmp = atoi(p);
      stack[stack_index++] = tmp;
    } else if (!strcmp(p, "POP\n")) {
      pop_element = stack[--stack_index];
    } else if (!strcmp(p, "ENQUEUE")) {
      p = strtok(NULL, "\n");
      if (!strcmp(p, "A")) {
        queueA[queueA_tail++] = pop_element;
      } else if (!strcmp(p, "B")) {
        queueB[queueB_tail++] = pop_element;
      }

    } else if (!strcmp(p, "DEQUEUE")) {
      p = strtok(NULL, "\n");
      if (!strcmp(p, "A")) {
        output[output_index++] = queueA[queueA_font++];

      } else if (!strcmp(p, "B")) {
        output[output_index++] = queueB[queueB_font++];
      }
    }
  }
  for (int i = 0; i < output_index; i++) {
    printf("%d\n", output[i]);
  }
  fclose(input);
  return 0;
}
