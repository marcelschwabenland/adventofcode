#include <stdio.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\06\\input.txt"
#define BUFFERSZ 14

int isUnique(char *a, int size) {
  for(int i = 0; i < size; i++) {
    for(int j = i + 1; j < size; j++) {
      if(a[i] == a[j] || (a[i] == '\000' || a[j] == '\000')) {
        return 0;
      }
    }
  }
  return 1;
}

void push(char *a, char c, int size) {
  for(int i = 0; i < size; i++) {
    a[i] = a[i+1];
  }
  a[size - 1] = c;
}

int main(int argc, char const *argv[])
{
  FILE *fptr = fopen(FILEPATH, "r");
  int position = 0;
  char c;
  char buffer[BUFFERSZ] = {'\000'};

  while(c != EOF && isUnique(buffer, BUFFERSZ) == 0) {
    c = fgetc(fptr);

    if(position < BUFFERSZ) {
      buffer[position] = c;
    } else {
      push(buffer, c, BUFFERSZ);
    }
    position++;
  }

  printf("start-of-packet marker starts after: %d", (position));
  return 0;
}
