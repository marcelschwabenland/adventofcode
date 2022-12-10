#include <stdio.h>
#include <stdlib.h>

#define FILEPATH  "C:\\Users\\schwa\\Projekte\\adventofcode\\2022\\10\\example.txt"
#define BUFFERSZ  16

#define CLOCK_OFS 20
#define CLOCK_MOD 40
#define VERT       6
#define HORZ      40

static int cycle = CLOCK_OFS, regX = 1, sigsum = 0, pixel = 0;

static void tick(void)
{
    if (!(++cycle % CLOCK_MOD))
        sigsum += (cycle - CLOCK_OFS) * regX;  // clock = 20,60,100,140,180,220
    int beam = pixel++ % HORZ;
    if (!beam)
        printf("\n");
    printf("%c", abs(beam - regX) <= 1 ? '#' : '.');
}

int main(void)
{
  int add;
  char buf[5];  // opcodes are length 4 + 1 string terminator \0
  FILE *f = fopen("input.txt", "r");  // or: example10.txt
  while (pixel < VERT * HORZ && !feof(f))
      if (fscanf(f, "%4s ", buf) == 1) {  // 4 chars, space or newline
          tick();  // 1 cycle for every instruction
          if (buf[0] == 'a' && fscanf(f, "%d ", &add) == 1) {
              tick();  // 1 more cycle for addx
              regX += add;  // only update after complete instruction cycle
          }
      }
  fclose(f);
  printf("\n\nPart 1: %d\n", sigsum);  // ex=13140, inp=15020, Part 2: EFUGLPAP
  return 0;
}