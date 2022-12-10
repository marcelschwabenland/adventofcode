#include <stdio.h>
#include <stdlib.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\10\\input.txt"
#define BUFFERSZ 128

int check_signal_strength(int cycle, int x) {
  int target[6] = {20, 60, 100, 140, 180, 220};

  for (int i = 0; i < 6; i++) {
    if (cycle == target[i]) {
      printf("During the %dth cycle, register X has the value %d, so the signal strength is %d * %d = %d\n", cycle, x, cycle, x, cycle * x);
      return cycle * x;
    }
  }

  return 0;
}

int main() {
  FILE *fptr = fopen(FILEPATH, "r");
  if (fptr == NULL) {
    return -1;
  }
  char buffer[BUFFERSZ] = {'\0'};
  int cycle = 1;
  int x = 1;
  int sum = 0;

  while (feof(fptr) == 0) {
    fgets(buffer, BUFFERSZ, fptr);

    if(buffer[0] == 'a') {
      for (int i = 0; i < 2; i++) {
        sum += check_signal_strength(cycle, x);
        cycle++;
      }
      int number = atoi(buffer + 5);
      x += number;
    } else {
      // do nothing
      sum += check_signal_strength(cycle, x);
      cycle++;
    }
  }

  printf("sum of the signal strengths: %d", sum);

  fclose(fptr);
  return 0;
}