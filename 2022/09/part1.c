#include <stdio.h>
#include <stdlib.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\09\\input.txt"
#define BUFFERSZ 10

void print_matric(int **matric, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", matric[i][j]);
    }
    printf("\n");
  }
}

int get_max_row(FILE *fptr) {
  char instruction[BUFFERSZ] = {'\0'};
  int n = 0, movement = 0;
  while (feof(fptr) == 0) {
    fgets(instruction, BUFFERSZ, fptr);
    if (instruction[0] == 'U' || instruction[0] == 'D') {
      n += atoi(instruction + 2);
    }
  }
  rewind(fptr);
  return n;
}

int get_max_col(FILE *fptr) {
  char instruction[BUFFERSZ] = {'\0'};
  int m = 0, movement = 0;
  while (feof(fptr) == 0) {
    fgets(instruction, BUFFERSZ, fptr);
    if (instruction[0] == 'L' || instruction[0] == 'R') {
      m += atoi(instruction + 2);
    }
  }
  rewind(fptr);
  return m;
}

int get_start_row(FILE *fptr, int n) {
  char instruction[BUFFERSZ] = {'\0'};

  while (instruction[0] != 'U' && instruction[0] != 'D') {
    fgets(instruction, BUFFERSZ, fptr);
  }
  if (instruction[0] == 'U') {
    rewind(fptr);
    return n - 1;
  }

  rewind(fptr);
  return 0;
}

int get_start_col(FILE *fptr, int m) {
  char instruction[BUFFERSZ] = {'\0'};

  while (instruction[0] != 'L' && instruction[0] != 'R') {
    fgets(instruction, BUFFERSZ, fptr);
  }
  if (instruction[0] == 'L') {
    rewind(fptr);
    return m - 1;
  }
  
  rewind(fptr);
  return 0;
}

int **malloc_matric(int n, int m) {
  int **matric = malloc(sizeof(int *) * n);
  for (int row = 0; row < n; row++) {
    matric[row] = malloc(sizeof(int) * m);
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < m; col++) {
      matric[row][col] = 0;
    }
  }
  return matric;
}

int calculate_visited_positions(int **matric, int n, int m) {
  int visited_positions = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (matric[i][j] > 0) {
        visited_positions++;
      }
    }
  }
  return visited_positions;
}

int is_tail_out_of_bound_y_axis(int head_pos_i, int tail_pos_i) {
  int diff = head_pos_i - tail_pos_i;

  if (diff > 1) {
    return (diff - 1);
  } else if (diff < -1) {
    return ((diff * -1) - 1);
  }
  return 0;
}

int is_tail_out_of_bound_x_axis(int head_pos_j, int tail_pos_j) {
  int diff = head_pos_j - tail_pos_j;

  if (diff > 1) {
    return (diff - 1);
  } else if (diff < -1) {
    return ((diff * -1) - 1);
  }
  return 0;
}

void simulate(FILE *fptr, int **matric, int n, int m) {
  char instruction[BUFFERSZ] = {'\0'};
  int head_pos_i = n/2, head_pos_j = m/2;
  int tail_pos_i = head_pos_i, tail_pos_j = head_pos_j;
  
  matric[tail_pos_i][tail_pos_j]++;
  while (feof(fptr) == 0) {
    fgets(instruction, BUFFERSZ, fptr);
    char direction = instruction[0];
    int step = 0, steps = atoi(instruction + 2);

    switch (direction) {
      case 'U': 
        for (step = 0; step < steps; step++) {
          head_pos_i--;
          int diff = is_tail_out_of_bound_y_axis(head_pos_i, tail_pos_i);
          if(diff != 0) {
            tail_pos_j = head_pos_j;
            tail_pos_i -= diff;
          }
          matric[tail_pos_i][tail_pos_j]++;
        }
        break;
      case 'D': 
        for (step = 0; step < steps; step++) {
          head_pos_i++;
          int diff = is_tail_out_of_bound_y_axis(head_pos_i, tail_pos_i);
          if(diff != 0) {
            tail_pos_j = head_pos_j;
            tail_pos_i += diff;
          }
          matric[tail_pos_i][tail_pos_j]++;
        }
        break;
      case 'L': 
        for (step = 0; step < steps; step++) {
          head_pos_j--;
          int diff = is_tail_out_of_bound_x_axis(head_pos_j, tail_pos_j);
          if(diff != 0) {
            tail_pos_i = head_pos_i;
            tail_pos_j -= diff;
          }
          matric[tail_pos_i][tail_pos_j]++;
        }
        break;
      case 'R': 
        for (step = 0; step < steps; step++) {
          head_pos_j++;
          int diff = is_tail_out_of_bound_x_axis(head_pos_j, tail_pos_j);
          if(diff != 0) {
            tail_pos_i = head_pos_i;
            tail_pos_j += diff;
          }
          matric[tail_pos_i][tail_pos_j]++;
        }
        break;
      default: break;
    }
  }
}

int main() {
  FILE *fptr = fopen(FILEPATH, "r");
  int **matric = NULL;
  if (fptr == NULL) {
    return -1;
  }
  int n = 1000, m = 1000, visited_positions = 0;

  matric = malloc_matric(n, m);
  simulate(fptr, matric, n, m);
  visited_positions = calculate_visited_positions(matric, n, m);
  printf("sum of visited positions: %d", visited_positions);
  // Part I 6367

  free(matric);
  fclose(fptr);
  return 0;
}