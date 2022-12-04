#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define PATH_TO_FILE "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\01\\input.txt"

int main(int argc, char const *argv[]) {
  FILE * file;

  char buffer[BUFFER_SIZE];

  int first = 0;
  int second = 0;
  int third = 0;
  int sum = 0;

  // open file
  file = fopen(PATH_TO_FILE, "r");

  // check if file opened
  if (file == NULL) {
    printf("file can't be opened\n");
    return 1;
  }

  while (fgets(buffer, BUFFER_SIZE, file)) {
    size_t len = strlen(buffer);

    if(len && buffer[len-1] == '\n') {
      buffer[--len] = 0;
    }

    if(len > 0) {
      sum += atoi(buffer);
    } else {
      if(first < sum) {
        third = second;
        second = first;
        first = sum;
      } else if(second < sum) {
        third = second;
        second = sum;
      } else if(third < sum) {
        third = sum;
      }
      sum = 0;
    }
  }  

  fclose(file);
  printf("First: %d\nSecond: %d\nThird: %d\nTotal: %d", first,second,third, (size_t)(first+second+third));

  return 0;
}
