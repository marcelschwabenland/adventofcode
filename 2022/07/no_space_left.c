#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\07\\input.txt"
#define BUFFERSZ 128

struct node {
  int value;
  char name[BUFFERSZ];
  struct node *pred;
  struct node *succ;
  struct node *parent;
  struct node *firstchild;
};

void print_directory_tree(struct node *tree) {
  int indent = 0;
  struct node *curr = tree;
  char out[4096] = {'\0'};
  
  while (curr->firstchild != NULL || curr->succ != NULL) {
    if(curr->firstchild != NULL && curr->succ != NULL) {
      printf("d %s", curr->name);
      struct node *child = curr->firstchild;
      while(child->succ != NULL) {
        for(int i = 0; i < indent; i++) {
          printf(" ");
        }
        printf("%s", child->name);
        child = child->succ;
      }
    }
  }
}

int build_directory_tree(FILE *fptr, struct node *subtree) {
  int subsum = 0;
  char buffer[BUFFERSZ] = {'\0'};
  
  int depth = 0;
  
  while (feof(fptr) == 0) {
    if(buffer[0] != '$' || buffer[5] == '/') {
      fgets(buffer, BUFFERSZ, fptr);
    }
    printf("%s", buffer);
    if(buffer[0] == '$' && buffer[2] == 'c' && buffer[3] == 'd' && buffer[5] != '.' && buffer[5] != '/') {
      // increase depth
      // go to next line
      subtree = subtree->firstchild;
      while(subtree->succ != NULL && strcmp(subtree->name, buffer + 5) != 0) {
        subtree = subtree->succ;
      }
      printf("%s\n", subtree->name);
      fgets(buffer, BUFFERSZ, fptr);
      // depth++;
    } else if (buffer[0] == '$' && buffer[2] == 'c' && buffer[3] == 'd' && buffer[5] == '.') {
      // decrease depth
      // go to next line
      subtree = subtree->parent;
      fgets(buffer, BUFFERSZ, fptr);
      // depth--;
    } else if (buffer[0] == '$' && buffer[2] == 'l') {
      // go to next line
      fgets(buffer, BUFFERSZ, fptr);
      printf("%s", buffer);
      // loop to next command symbol
      while (buffer[0] != '$') {
        if(buffer[0] > '0' && buffer[0] <= '9') {
          // file size add to directory value
          subtree->value += atoi(buffer);
        } else if (buffer[0] == 'd' && subtree->firstchild == NULL) {
          // remember file position
          // fpos_t *directory_pos = malloc(sizeof(fpos_t));
          // fgetpos(fptr, directory_pos);
          // create new directory
          struct node *firstchild = malloc(sizeof(struct node));
          strcpy(firstchild->name, buffer + 4);
          firstchild->value = 0;
          firstchild->parent = subtree;
          firstchild->pred = firstchild->succ = firstchild->firstchild = NULL;
          // append new directory to parent
          subtree->firstchild = firstchild;
          // build subtree of firstchild
          // recursive call here
          // clean up
          // fsetpos(fptr, directory_pos);
          // free(directory_pos);
        } else if (buffer[0] == 'd' && subtree->firstchild != NULL) {
          // remember file position
          // fpos_t *directory_pos = malloc(sizeof(fpos_t));
          // fgetpos(fptr, directory_pos);
          // find last child node
          struct node *pred = subtree->firstchild;
          while (pred->succ != NULL) {
            pred = pred->succ;
          }
          // create new directory
          struct node *succ = malloc(sizeof(struct node));
          strcpy(succ->name, buffer + 4);
          succ->value = 0;
          succ->parent = subtree;
          succ->pred = pred;
          succ->succ = succ->firstchild = NULL;
          // append new directory to pred
          pred->succ = succ;
          // build subtree of succ
          // recursive call here
          // clean up
          // fsetpos(fptr, directory_pos);
          // free(directory_pos);
        }
        // go to next line
        fgets(buffer, BUFFERSZ, fptr);
        printf("%s", buffer);
      }
    }
  }

  return 0;
}

int main(int argc, char const *argv[]) {
  FILE *fptr = fopen(FILEPATH, "r");
  struct node *root = malloc(sizeof(struct node));
  if (fptr == NULL) {
    return -1;
  }

  strcpy(root->name, (char *)"/\0");
  root->value = 0;
  root->pred = root->succ = root->parent = root->firstchild = NULL;

  fpos_t *start = malloc(sizeof(fpos_t));
  fgetpos(fptr, start);

  build_directory_tree(fptr, root);
  print_directory_tree(root);
  // free_directory_tree(root);
  // clean_up_tree(root);
  free(root);

  fsetpos(fptr, start);
  
  free(start);
  fclose(fptr);
  return 0;
}
