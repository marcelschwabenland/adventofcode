#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE (sizeof(char) * 5)
#define PATH_TO_FILE "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\02\\input.txt"

int main(int argc, char const *argv[])
{
  FILE * fptr;
  char buffer[BUFFER_SIZE] = "";

  char opponent, self;
  int points = 0;

  fptr = fopen(PATH_TO_FILE, "r");
  if(fptr == NULL) {
    printf("could not open file.");
    return 1;
  }

  /*
   * A +1 Rock X lose
   * B +2 Paper Y draw
   * C +3 Scissors Z win
   * 
   * l =0
   * d =3
   * w =6
   */
  while(fgets(buffer, BUFFER_SIZE, fptr)) {
    opponent = buffer[0];
    self = buffer[2];
    if(self == 'X') {
      switch (opponent) {
      case 'A':
        points += 3;
        break;
      case 'B':
        points += 1;
        break;
      case 'C':
        points += 2;
        break;
      default:
        break;
      }
    } else if (self == 'Y') {
      switch (opponent) {
      case 'A':
        points += 4;
        break;
      case 'B':
        points += 5;
        break;
      case 'C':
        points += 6;
        break;
      default:
        break;
      }
    } else if (self == 'Z') {
      switch (opponent) {
      case 'A':
        points += 8;
        break;
      case 'B':
        points += 9;
        break;
      case 'C':
        points += 7;
        break;
      default:
        break;
      }
    }     
  }

  printf("Result: %d", points);
  fclose(fptr);
  return 0;
}
