#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct coord {
  int x;
  int y;
  int z;
};

struct coord *coord_create() {
  struct coord *tmp = (struct coord *) malloc(sizeof(struct coord));

  tmp->x = rand();
  tmp->y = rand();
  tmp->z = rand();

  return tmp;
}

bool coors_free(struct coord *c) {
  free(c);

  return true;
}

bool coord_equals(void *o1, void *o2) {
  struct coord *c1 = (struct coord *) o1;
  struct coord *c2 = (struct coord *) o2;

  return c1->x == c2->x && c1->y == c2->y && c1->z == c2->z;
}

void coord_print(struct coord *c) {
  printf("x:%d\ty:%d\tz:%d\n", c->x, c->y, c->z);
}

#endif /* TEST_H */