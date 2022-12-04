#include <stdio.h>

#define FILEPATH "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\04\\input.txt"

int main(int argc, char const *argv[]) {
  FILE * fptr;

  int section_start_a, section_end_a, section_start_b, section_end_b;
  int overlapping;

  fptr = fopen(FILEPATH, "r");
  if(fptr == NULL) {
    return 1;
  }

  while (feof(fptr) == 0) {
    // make sure format is matched
    if(fscanf(fptr, "%d-%d,%d-%d", &section_start_a, &section_end_a, &section_start_b, &section_end_b) > 0) {
      if(section_start_a <= section_start_b && section_end_a >= section_end_b) {
        overlapping++;
      } else if (section_start_a >= section_start_b && section_end_a <= section_end_b) {
        overlapping++;
      }
    }    
  }
  
  printf("%d sections are fully overlapping.", overlapping);
  return 0;
}
