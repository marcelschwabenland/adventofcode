#include <stdio.h>
#include <string.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\03\\input.txt"
#define BUFFER_SIZE 4096

int main(int argc, char const *argv[]) {
  FILE *fptr;
  char buffer[BUFFER_SIZE];

  int group[3][52] = {0};
  int linecount = 0;
  int sum = 0;

  fptr = fopen(FILEPATH, "r");
  if (fptr == NULL) {
    return 1;
  }
  // 6 offset
  while(fgets(buffer, BUFFER_SIZE, fptr)) {
    size_t len = strlen(buffer);
    if(len && buffer[len - 1] == '\n') {
      buffer[--len] = 0;
    }

    for(int i = 0; i < len; i++) {
      if(buffer[i] - 'A' > 25) {
        group[linecount%3][buffer[i] - 'A' - 32]++;
      } else {
        group[linecount%3][buffer[i] - 'A' + 26]++;
      }      
    }

    if((linecount + 1) % 3 == 0) {
      for(int col = 0; col < 52; col++) {
        if(group[0][col] > 0 && group[1][col] > 0 && group[2][col] > 0) {
          sum += (col + 1);
        }
        group[0][col] = group[1][col] = group[2][col] = 0;
      }
    }
    linecount++;
  }

  fclose(fptr);
  printf("result: %d", sum);

  return 0;
}
