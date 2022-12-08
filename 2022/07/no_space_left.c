#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\07\\input.txt"
#define BUFFERSZ 128

struct node {
  int size;
  int num_children;
  char name[BUFFERSZ];
  struct node *children;
};

void generate_directory(FILE *fptr, fpos_t *fpos, char *buffer, char *cmp, struct node *directory_node) {
  int sub_directory_count = 0;
  // search for "$ cd dirname"
  while (strcmp(buffer, cmp) != 0) {
    fgets(buffer, BUFFERSZ, fptr);
  }
  // skip to first element of directory
  fgets(buffer, BUFFERSZ, fptr); // read next line which should be "$ ls"
  fgets(buffer, BUFFERSZ, fptr); // first item in directory
  // iterate through items of directory and handle files and sub-directories
  while (buffer[0] != '$') {
    // handle directories and files
    if (buffer[0] > '0' && buffer[0] <= '9') {
      // found a file, add size to directory size
      directory_node->size += atoi(buffer);
    } else if (buffer[0] == 'd') {
      // found a sub-directory, create new directory node
      // and call generate_directory to work on sub-directory
      fpos_t *new_fpos = malloc(sizeof(fpos_t));
      char command[BUFFERSZ] = {'$', ' ', 'c', 'd', ' ', '\0'};
      char *new_cmp = strcat(command, buffer + 4);
      struct node *new_directory = malloc(sizeof(struct node));
      // prepare new directory node
      strcpy(new_directory->name, buffer + 4);
      new_directory->size = 0;
      new_directory->num_children = 0;
      new_directory->children = malloc(sizeof(struct node));
      // remember position in file to reset to
      fgetpos(fptr, new_fpos);
      // work on sub-directory
      generate_directory(fptr, new_fpos, buffer, new_cmp, new_directory);
      // add sub-directory size to current directory
      directory_node->size += new_directory->size;
      // add sub-directory to list of children
      sub_directory_count++;
      // reallocate memory for new list of children
      directory_node->children = realloc(directory_node->children, (sizeof(struct node) * sub_directory_count));
      directory_node->children[sub_directory_count - 1] = *new_directory;
      // file position pointer was only need in the generate_directory call
      free(new_fpos);
    }
    if(feof(fptr) != 0) {
      break;
    }
    fgets(buffer, BUFFERSZ, fptr); // next item in directory
  }
  // free memory for list of children if non exist
  if(sub_directory_count == 0) {
    free(directory_node->children);
    directory_node->children = NULL;
  } else {
    directory_node->num_children = sub_directory_count;
  }
  // reset position in file
  fsetpos(fptr, fpos);
  return;
}

void calculate_total_size_of_directories(struct node *root, int *total_size) {
  struct node *curr = root;
  if (curr->size <= 100000) {
    *total_size += curr->size;
  }
  for (int i = 0; i < curr->num_children; i++) {
    calculate_total_size_of_directories(&curr->children[i], total_size);
  }
}

void print_directory_tree(struct node *root, int indent) {
  struct node *curr = root;

  for (int i = 0; i < indent; i++) {
    printf("-");
  }
  printf(" %d %s", curr->size, curr->name);
  for (int i = 0; i < curr->num_children; i++) {
    print_directory_tree(&curr->children[i], indent + 1);
  }
}

int main(int argc, char const *argv[]) {
  int sum = 0;
  fpos_t *fpos = malloc(sizeof(fpos_t));
  FILE *fptr = fopen(FILEPATH, "r");
  struct node *root = malloc(sizeof(struct node));
  char buffer[BUFFERSZ] = {'\0'};
  if (fptr == NULL) {
    return -1;
  }

  // prepare root node
  fgets(buffer, BUFFERSZ, fptr); // read first line $ cd /
  strcpy(root->name, buffer + 5);
  root->size = 0;
  root->num_children = 0;
  root->children = malloc(sizeof(struct node*));

  // remember start position
  fgetpos(fptr, fpos);

  generate_directory(fptr, fpos, buffer, buffer, root);
  print_directory_tree(root, 0);
  printf("\n");
  calculate_total_size_of_directories(root, &sum);

  printf("Sum: %d", sum);

  free(root);
  free(fpos);
  fclose(fptr);
  return 0;
}
