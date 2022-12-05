#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\05\\input.txt"
#define INSTRUCTIONS "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\05\\instructions.txt"
#define MAX_TOWERS 9
#define MAX_TOWER_HEIGHT 100
#define MAX_WHITESPACE 4
#define BUFFER_SIZE 128

int main(int argc, char const *argv[]) {
  FILE *fptr = fopen(FILEPATH, "r");
  FILE *instructions = fopen(INSTRUCTIONS, "r");
  
  if(fptr == NULL || instructions == NULL) {
    return -1;
  }

  char buffer[BUFFER_SIZE];
  char matrix[MAX_TOWERS][MAX_TOWER_HEIGHT] = {'0'};
  int tower = 0;
  int height = 7;
  int whitespace = 0;

  int move = 0;
  int from = 0;
  int to = 0;

  char c;

  do {
    c = fgetc(fptr);

    // skip these characters during parsing
    while (c == '[' || c == ']' || c == ' ' || c == '\n') {
      // count whitespaces when 4 consecutive whitespaces are read move to next tower
      while (c == ' ' && whitespace < MAX_WHITESPACE) {
        whitespace++;
        if(whitespace + 1 == MAX_WHITESPACE) {
          tower++;
        }
        c = fgetc(fptr);
      }
      whitespace = 0; // reset whitespace counter

      // a newline so we decrease the tower level by 1
      if(c == '\n') {
        height--;
        tower = 0;
        c = fgetc(fptr);
      }

      if(c == '[' || c == ']') {
        c = fgetc(fptr);
      }
    }

    if(c >= 'A' && c <= 'Z') {
      matrix[tower][height] = c;
      tower++;
    }
  } while (c != EOF && c >= 'A' && c <= 'Z');

  // parse instructions
  int line = 0;
  while (fscanf(instructions, "move %d from %d to %d\n", &move, &from, &to) != EOF) {
    // printf("[%d] move %d from %d to %d\n", line++, move, from, to);
    // determine tower height
    int fromH = 0;
    int toH = 0;
    while(matrix[from-1][fromH] != '\000' && fromH < MAX_TOWER_HEIGHT) {
      fromH++;
    }

    while(matrix[to-1][toH] != '\000' && toH < MAX_TOWER_HEIGHT) {
      toH++;
    }

    for(int i = 0; i < move; i++) {
      matrix[to - 1][toH + i] = matrix[from - 1][fromH - (move - i)];
      matrix[from - 1][fromH - (move - i)] = '\000';
    }

    // printf("From H: %d, To H: %d\n", fromH, toH);
  }
  
  for(int col = 0; col < MAX_TOWERS; col++) {
    for(int row = 0; matrix[col][row] != '\000'; row++) {
      // move to highest point of tower
      if(matrix[col][row + 1] == '\000') {
        printf("%c", matrix[col][row]);
      }
    }
  }

  fclose(fptr);
  fclose(instructions);
  return 0;
}
