#include <stdio.h>
#include <string.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\03\\input.txt"
#define BUFFER_SIZE 4096

int main(int argc, char const *argv[]) {
  FILE *fptr;
  char buffer[BUFFER_SIZE];

  int compartment1[52] = {0};
  int compartment2[52] = {0};
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

    for(int i = 0; i < (len/2); i++) {
      if(buffer[i] - 'A' > 25) {
        compartment1[buffer[i] - 'A' - 32]++;
      } else {
        compartment1[buffer[i] - 'A' + 26]++;
      }      
    }

    for(int i = len/2; i < len; i++) {
      if(buffer[i] - 'A' > 25) {
        compartment2[buffer[i] - 'A' - 32]++;
      } else {
        compartment2[buffer[i] - 'A' + 26]++;
      }
    }

    for(int i = 0; i < 52; i++) {
      if(compartment1[i] > 0 && compartment2[i] > 0) {
        sum += (i+1);
      }
      compartment1[i] = 0;
      compartment2[i] = 0;
    }
  }

  fclose(fptr);
  printf("result: %d", sum);

  return 0;
}
