#include <stdio.h>
#include <stdlib.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\08\\input.txt"

void print_tree_map(int **tree_map, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", tree_map[i][j]);
    }
    printf("\n");
  }
}

int get_tree_map_rows(FILE *fptr) {
  char c = '\0';
  int n = 0;
  // calculate tree map columns
  while (c != EOF) {
    c = fgetc(fptr);
    if(c == '\n') {
      n++;
    }
  }
  rewind(fptr);
  return n;
}

int get_tree_map_columns(FILE *fptr) {
  char c = '\0';
  int m = 0;
  // calculate tree map columns
  while (c != '\n') {
    c = fgetc(fptr);
    if(c >= '0' && c <= '9') {
      m++;
    }
  }
  rewind(fptr);
  return m;
}

int **malloc_tree_map(int n, int m) {
  int **tree_map = malloc(sizeof(int *) * n);
  for (int row = 0; row < n; row++) {
    tree_map[row] = malloc(sizeof(int) * m);
  }
  return tree_map;
}

int **generate_tree_map(FILE *fptr, int **tree_map, int n, int m) {
  int i = 0, j = 0;
  char c = '\0';
  // fill tree map size with data from file
  while (c != EOF) {
    c = fgetc(fptr);
    if(c >= '0' && c <= '9') {
      tree_map[i][j] = (int)(c - '0');
      j = ((j + 1) % m);
    }
    if(c == '\n') {
      i++;
    }
  }
  return tree_map;
}

int count_visible_trees(int **tree_map, int n, int m) {
  int visible = 0;
  // go through each tree except most outer tree line
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      int tree_height_A = tree_map[i][j];
      int is_covered_n = 0, is_covered_s = 0, is_covered_e = 0, is_covered_w = 0;
      // check north of tree at tree_map[i][j]
      for (int row = i - 1; row >= 0; row--) {
        int tree_height_B = tree_map[row][j];
        if (tree_height_B >= tree_height_A) {
          is_covered_n++;
        }
      }
      // check south of tree at tree_map[i][j]
      for (int row = i + 1; row < n; row++) {
        int tree_height_B = tree_map[row][j];
        if (tree_height_B >= tree_height_A) {
          is_covered_s++;
        }
      }
      // check east of tree at tree_map[i][j]
      for (int col = j + 1; col < m; col++) {
        int tree_height_B = tree_map[i][col];
        if (tree_height_B >= tree_height_A) {
          is_covered_e++;
        }
      }
      // check west of tree at tree_map[i][j]
      for (int col = j - 1; col >= 0; col--) {
        int tree_height_B = tree_map[i][col];
        if (tree_height_B >= tree_height_A) {
          is_covered_w++;
        }
      }

      if (is_covered_n == 0 || is_covered_s == 0 || is_covered_e == 0 || is_covered_w == 0) {
        visible++;
      }
    }
  }
  return visible;
}

int highest_scenic_score(int **tree_map, int n, int m) {
  int highest_scenic_score = 0;
  // go through each tree except most outer tree line
  for (int i = 1; i < n - 1; i++) {
    for (int j = 1; j < m - 1; j++) {
      int tree_height_A = tree_map[i][j];
      int view_n = 0, view_s = 0, view_e = 0, view_w = 0;
      // count trees to the north of tree at tree_map[i][j] 
      // until higher or same height ist found
      for (int row = i - 1; row >= 0; row--) {
        int tree_height_B = tree_map[row][j];
        if (tree_height_B < tree_height_A) {
          view_n++;
        } else {
          view_n++;
          break; // found blocking tree
        }
      }
      // count trees to the south of tree at tree_map[i][j] 
      // until higher or same height ist found
      for (int row = i + 1; row < n; row++) {
        int tree_height_B = tree_map[row][j];
        if (tree_height_B < tree_height_A) {
          view_s++;
        } else {
          view_s++;
          break; // found blocking tree
        }
      }
      // count trees to the east of tree at tree_map[i][j] 
      // until higher or same height ist found
      for (int col = j + 1; col < m; col++) {
        int tree_height_B = tree_map[i][col];
        if (tree_height_B < tree_height_A) {
          view_e++;
        } else {
          view_e++;
          break; // found blocking tree
        }
      }
      // count trees to the east of tree at tree_map[i][j] 
      // until higher or same height ist found
      for (int col = j - 1; col >= 0; col--) {
        int tree_height_B = tree_map[i][col];
        if (tree_height_B < tree_height_A) {
          view_w++;
        } else {
          view_w++;
          break; // found blocking tree
        }
      }

      int scenic_score = view_n * view_s * view_e * view_w;
      if (scenic_score > highest_scenic_score) {
        highest_scenic_score = scenic_score;
      }
    }
  }
  return highest_scenic_score;
}

int main() {
  int n = 0, m = 0, visible = 0, highest_score = 0;
  int **tree_map = NULL;
  FILE *fptr = fopen(FILEPATH, "r");
  if(fptr == NULL) {
    return -1;
  }

  n = get_tree_map_rows(fptr);
  m = get_tree_map_columns(fptr);
  tree_map = malloc_tree_map(n, m);

  generate_tree_map(fptr, tree_map, n, m);
  print_tree_map(tree_map, n, m);

  visible = count_visible_trees(tree_map, n, m);
  printf("\n\nPart I\n");
  printf("visible interior trees: %d\n", visible);
  printf("trees on the edge: %d\n", (((n + m) * 2) - 4));
  printf("total visible trees: %d", (visible + (((n + m) * 2) - 4)));

  printf("\n\nPart II\n");
  highest_score = highest_scenic_score(tree_map, n, m);
  printf("highest scenic score: %d", highest_score);

  free(tree_map);
  return 0;
}