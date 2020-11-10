#include <stdbool.h>
#include <stdio.h>
#define TABLE_SIZE 13
#define PRIME 7
typedef struct t {
  int value;
  bool flag;
} type_t;
int main(int argc, char *argv[]) {
  FILE *fin, *fout;
  fin = fopen(argv[1], "r");
  fout = fopen(argv[2], "w");
  int key, count = 0;
  type_t table[TABLE_SIZE];
  // init table
  for (int i = 0; i < TABLE_SIZE; i++) {
    table[i].flag = false;
  }
  // read every single key
  while (fscanf(fin, "%d", &key) != EOF) {
    int hash1 = key % TABLE_SIZE;
    int hash2 = PRIME - (key % PRIME);
    int h, i = 0;
    do {
      h = (hash1 + (i++) * hash2) % TABLE_SIZE;
    } while (table[h].flag);
    table[h].flag = true;
    table[h].value = key;
  }

  for (int i = 0; i < TABLE_SIZE; i++) {
    if(i==TABLE_SIZE-1)
        fprintf(fout,"%d->%d", i, table[i].value);
    else
        fprintf(fout,"%d->%d\n", i, table[i].value);
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
