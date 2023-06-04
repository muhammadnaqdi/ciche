#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct coord {
  int id;
  int x;
  int y;
  int z;
};

struct coord *coord_create() {
  static int counter = 0;
  
  struct coord *tmp = (struct coord *) malloc(sizeof(struct coord));

  tmp->id = counter++;
  tmp->x = rand();
  tmp->y = rand();
  tmp->z = rand();

  return tmp;
}

bool coord_free(void *o) {
  struct coord *c = (struct coord *) o;
  
  free(c);

  return true;
}

bool coord_equals(void *o1, void *o2) {
  struct coord *c1 = (struct coord *) o1;
  struct coord *c2 = (struct coord *) o2;

  return c1->id == c2->id;
}

void coord_print(struct coord *c) {
  printf("id:%d\tx:%d\ty:%d\tz:%d\n", c->id, c->x, c->y, c->z);
}

#endif /* TEST_H */
