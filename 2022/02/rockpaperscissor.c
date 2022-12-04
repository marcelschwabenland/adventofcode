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
   * X +1 Rock
   * Y +2 Paper
   * Z +3 Scissors
   * 
   * l =0
   * d =3
   * w =6
   */
  while(fgets(buffer, BUFFER_SIZE, fptr)) {
    opponent = buffer[0];
    self = buffer[2];
    if(opponent == 'A') {
      switch (self) {
      case 'X':
        points += 4;
        break;
      case 'Y':
        points += 8;
        break;
      case 'Z':
        points += 3;
        break;
      default:
        break;
      }
    } else if (opponent == 'B') {
      switch (self) {
      case 'X':
        points += 1;
        break;
      case 'Y':
        points += 5;
        break;
      case 'Z':
        points += 9;
        break;
      default:
        break;
      }
    } else if (opponent == 'C') {
      switch (self) {
      case 'X':
        points += 7;
        break;
      case 'Y':
        points += 2;
        break;
      case 'Z':
        points += 6;
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
