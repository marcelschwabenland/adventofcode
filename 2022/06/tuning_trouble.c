#include <stdio.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\06\\input.txt"
#define BUFFERSZ 64

int unique(char a, char b, char c, char d) {
  if(a != b && 
  a != c && 
  a != d &&
  b != c && 
  b != d &&
  c != d) {
    return 1;
  }
  return 0;
}

int main(int argc, char const *argv[])
{
  FILE *fptr = fopen(FILEPATH, "r");
  int iterator = 0;
  char c, first, second, third, fourth;

  while(c != EOF && (iterator < 4 || unique(first, second, third, fourth) == 0)) {
    c = fgetc(fptr);
    if(iterator < 4) {
      switch (iterator % 4) {
      case 0:
        first = c;
        break;
      case 1:
        second = c;
        break;
      case 2:
        third = c;
        break;
      case 3:
        fourth = c;
        break;
      default:
        break;
      }
    } else {
      first = second;
      second = third;
      third = fourth;
      fourth = c;
    }    
    iterator++;
  }

  printf("start-of-packet marker starts after: %d", iterator);
  return 0;
}
