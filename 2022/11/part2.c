#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFFERSZ 256
#define MAX_MONKEYS 8
#define MAX_ROUND 10000
#define MAX_ITEMS 256

struct Monkey {
  unsigned long long *items; // my worry levels
  int *number_of_items;
  int *business;
  char *operation;
  unsigned long long *test;
  int *target_on_true;
  int *target_on_false;
};

void run_monkey_operation(struct Monkey m, int item_number) {
  char operator = m.operation[0];
  unsigned long long n = m.operation[2] == 'o' ? m.items[item_number] : (unsigned long long) atoll(m.operation + 2);
  unsigned long long res = 0;
  switch (operator) {
    case '+':
      res = (unsigned long long)(m.items[item_number] + n);
      m.items[item_number] = res;
      // printf("    Worry level is increased by %d to %d.\n", n, m.items[item_number]);
      break;
    case '-':
      res = (unsigned long long)(m.items[item_number] - n);
      m.items[item_number] -= n;
      // printf("    Worry level is decreased by %d to %d.\n", n, m.items[item_number]);
      break;
    case '*':
      // 20
      res = (unsigned long long)(m.items[item_number] * n);
      m.items[item_number] *= n;
      // printf("    Worry level is multiplied by %d to %d.\n", n, m.items[item_number]);
      break;
    case '/':
      res = (unsigned long long)(m.items[item_number] / n);
      m.items[item_number] *= n;
      // printf("    Worry level is divided by %d to %d.\n", n, m.items[item_number]);
      break;
    default:
      printf("Unknown operator %c\n", operator);
      break;
  }

  return;
}

int run_monkey_test(struct Monkey m, int item_number) {
  if (m.items[item_number] % (*m.test) == 0) {
    // printf("    Current worry level is divisible by %d.\n", *m.test);
    return *m.target_on_true;
  } else {
    // printf("    Current worry level is not divisible by %d.\n", *m.test);
    return *m.target_on_false;
  }
}

void throw_item_to(int item_number, int throw_target, struct Monkey from, struct Monkey to) {
  // printf("    Item with worry level %d is thrown to monkey %d.\n", from.items[item_number], throw_target);
  to.items[++(*to.number_of_items) - 1] = from.items[item_number];
}

void monkey_turn(struct Monkey active_monkey, struct Monkey *monkeys) {
  // inspect item i
  for (int item_number = 0; item_number < (*active_monkey.number_of_items); item_number++) {
    int throw_target = 0;
    // printf("  Monkey inspects an item with a worry level of %d.\n", active_monkey.items[item_number]);
    // increase business level by 1
    (*active_monkey.business)++;
    // run operation on item's worry level
    run_monkey_operation(active_monkey, item_number);
    // divide item's worry level by 3
    // active_monkey.items[item_number] /= 3;
    // printf("    Monkey gets bored with item. Worry level is divided by 3 to %d.\n", active_monkey.items[item_number]);
    // run test to decide what to do
    throw_target = run_monkey_test(active_monkey, item_number);
    // throw item to target
    throw_item_to(item_number, throw_target, active_monkey, monkeys[throw_target]);
  }

  for (int item_number = 0; item_number < (*active_monkey.number_of_items); item_number++) {
    active_monkey.items[item_number] = 0;
  }
  (*active_monkey.number_of_items) = 0;
}

void game_round(struct Monkey *monkeys, unsigned long long mod) {
  // order of monkeys turn 0, 1, 2, 3
  // each monkey gets one turn
  for (int i = 0; i < MAX_ROUND; i++) {
    for (int monkey_number = 0; monkey_number < MAX_MONKEYS; monkey_number++) {
      // printf("Monkey %d:\n", monkey_number);
      monkey_turn(monkeys[monkey_number], monkeys);
    }

    for (int monkey_number = 0; monkey_number < MAX_MONKEYS; monkey_number++) {
      for (int item_number = 0; item_number < *monkeys[monkey_number].number_of_items; item_number++) {
        monkeys[monkey_number].items[item_number] %= mod;
      }
    }

    if (i + 1 == 1 || i + 1 == 20 || i + 1 == 1000 || i + 1 == 2000 || i + 1 == 3000 || i + 1 == 4000 || i + 1 == 5000 || i + 1 == 6000 || i + 1 == 7000 || i + 1 == 8000 || i + 1 == 9000 || i + 1 == 10000) {
      printf("\n== After round %ld ==\n", i + 1);
      for (int monkey_number = 0; monkey_number < MAX_MONKEYS; monkey_number++) {
        printf("Monkey %d inspected items %llu times.\n", monkey_number, *monkeys[monkey_number].business);
      }
    }
  }
}

int main() {
  FILE *fptr = fopen("input.txt", "r");
  char buffer[BUFFERSZ] = {'\0'};
  unsigned long long mod = 1;

  struct Monkey *monkeys = malloc(sizeof(struct Monkey) * MAX_MONKEYS);

  while (feof(fptr) == 0) {
    fgets(buffer, BUFFERSZ, fptr);

    if (buffer[0] == 'M') {
      int monkey_id = atoi(buffer + 7);
      struct Monkey *m = malloc(sizeof(struct Monkey));
      m->items = malloc(sizeof(unsigned long long) * MAX_ITEMS);
      for (int init = 0; init < MAX_ITEMS; init++) {
        m->items[init] = 0;
      }
      m->operation = malloc(sizeof(char) * 256);
      for (long init = 0; init < 256; init++) {
        m->operation[init] = '\0';
      }
      m->number_of_items = malloc(sizeof(int));
      *m->number_of_items = 0;
      m->target_on_false = malloc(sizeof(int));
      *m->target_on_false = 0;
      m->target_on_true = malloc(sizeof(int));
      *m->target_on_true = 0;
      m->business = malloc(sizeof(int));
      *m->business = 0;
      m->test = malloc(sizeof(int));
      *m->test = 0;

      fgets(buffer, BUFFERSZ, fptr);
      if (buffer[2] == 'S') {
        char *temp = buffer;
        while (temp[0] != '\0') {
          // move to first number
          while (!(temp[0] >= '1' && temp[0] <= '9')) {
            temp++;
          }
          m->items[(*m->number_of_items)++] = (unsigned long long)atoll(temp);
          while (temp[0] != ' ' && temp[0] != '\0') {
            temp++;
          }
        }
      }

      fgets(buffer, BUFFERSZ, fptr);
      if (buffer[2] == 'O') {
        for (int i = 0; buffer[i + 23] != '\0'; i++) {
          m->operation[i] = buffer[i + 23] == '\n' ? '\0' : buffer[i + 23];
        }
      }

      fgets(buffer, BUFFERSZ, fptr);
      if (buffer[2] == 'T') {
        *m->test = atoi(buffer + 21);
        fgets(buffer, BUFFERSZ, fptr);
        *m->target_on_true = atoi(buffer + 29);
        fgets(buffer, BUFFERSZ, fptr);
        *m->target_on_false = atoi(buffer + 29);
      }

      monkeys[monkey_id] = *m;
    }
  }

  for (int i = 0; i < MAX_MONKEYS; i++) {
    int divisor = *monkeys[i].test;
    mod *= divisor;
  }

  game_round(monkeys, mod);

  int highest = 0, second_highest = 0;
  printf("\n");
  for (int i = 0; i < MAX_MONKEYS; i++) {
    if (*monkeys[i].business > highest && *monkeys[i].business > second_highest) {
      second_highest = highest;
      highest = *monkeys[i].business;
    } else if (*monkeys[i].business < highest && *monkeys[i].business > second_highest) {
      second_highest = *monkeys[i].business;
    }
  }

  printf("%d * %d = %zu\n", highest, second_highest, (highest * second_highest));

  free(monkeys);
  fclose(fptr);
  return 0;
}