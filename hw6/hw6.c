#include <stdio.h>
#include <string.h>
#define max(a, b) ((a > b) ? a : b)
typedef struct node {
  char *name;
  char *no;
  int h; // height
  struct node *left;
  struct node *right;
} node_t;
int height(node_t *node) {
  if (!node)
    return 0;
  return node->h;
}
node_t *turn_right(node_t *node) {
  node_t *root = node->left;
  node_t *subtree = root->right;

  root->right = node;
  node->left = subtree;

  node->h = 1 + max(height(node->left), height(node->right));
  root->h = 1 + max(height(root->left), height(root->right));

  return root;
}
node_t *turn_left(node_t *node) {
  node_t *root = node->right;
  node_t *subtree = root->left;

  root->left = node;
  node->right = subtree;

  node->h = 1 + max(height(node->left), height(node->right));
  root->h = 1 + max(height(root->left), height(root->right));

  return root;
}
node_t *insert(node_t *node, char *name, char *no) {
  if (!node) {
    // insert new node
    node_t *new = malloc(sizeof(node_t));
    new->name = malloc(strlen(name));
    strcpy(new->name, name);
    new->no = malloc(strlen(no));
    strcpy(new->no, no);
    new->h = 1;
    return new;
  }
  if (strcmp(node->name, name) > 0)
    node->left = insert(node->left, name, no);
  else
    node->right = insert(node->right, name, no);

  // Update height
  node->h = 1 + max(height(node->left), height(node->right));
  int bf = height(node->left) - height(node->right);
  // LL
  if ((bf >= 2) && (strcmp(node->left->name, name) > 0)) {
    return turn_right(node);
  }
  // LR
  else if ((bf >= 2) && (strcmp(node->left->name, name) < 0)) {
    node->left = turn_left(node->left);
    return turn_right(node);
  }
  // RR
  if ((bf <= -2) && (strcmp(node->right->name, name) < 0)) {
    return turn_left(node);
  }

  // RL
  else if ((bf <= -2) && (strcmp(node->right->name, name) > 0)) {
    node->right = turn_right(node->right);
    return turn_left(node);
  }
  return node;
}
char *find_no(node_t *root, char *name) {
  if (!root)
    return "null";
  if (strcmp(root->name, name) == 0)
    return root->no;
  else if (strcmp(root->name, name) > 0)
    return find_no(root->left, name);
  else if (strcmp(root->name, name) < 0)
    return find_no(root->right, name);
}
void print_preorder(node_t *root) {
  if (!root)
    return;
  printf(" %s", root->name);
  print_preorder(root->left);
  print_preorder(root->right);
}
int main(int argc, char *argv[]) {
  char input_line[10000];
  node_t *root = NULL;
  int S_flag = 0;
  while (scanf("%s", input_line) != EOF) {
    if (strcmp(input_line, "E") == 0)
      break;

    else if (strcmp(input_line, "D") == 0) {
      char *name;
      char *no;
      int scanf_count = 0;
      while (scanf("%s", input_line) != EOF) {
        scanf_count++;
        if (strcmp(input_line, "S") == 0) {
          printf("%s", root->name);
          print_preorder(root->left);
          print_preorder(root->right);
          S_flag = 1;
          break;
        }
        // char *name = strtok(input_line," ");  //name
        // char *no = strtok(NULL," ");  //phone no.
        if (scanf_count % 2 == 1) {
          name = malloc(strlen(input_line));
          strcpy(name, input_line);
        }

        else if (scanf_count % 2 == 0) {
          no = malloc(strlen(input_line));
          strcpy(no, input_line);
          root = insert(root, name, no);
        }
      }
    } else if (S_flag) {
      printf("\n%s %s", input_line, find_no(root, input_line));
    }
  }
  return 0;
}
