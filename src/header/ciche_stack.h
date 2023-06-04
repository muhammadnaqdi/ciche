#ifndef CICHE_STACK_H
#define CICHE_STACK_H

#include "ciche_doubly.h"

typedef struct ciche_doubly ciche_stack;

bool ciche_stack_push(struct ciche_doubly *stack, void *obj) {
  return ciche_doubly_insert_at_head(stack, obj);
}

bool ciche_stack_pop(struct ciche_doubly *stack, struct ciche_doubly_node **node) {
  return ciche_doubly_remove_head(stack, node);
}

bool ciche_stack_pop_and_free(struct ciche_doubly *stack,  void **obj) {
  return ciche_doubly_remove_and_free_head(stack, obj);
}

bool ciche_stack_pop_and_deep_free(struct ciche_doubly *stack, bool (*obj_free)(void *)) {
  return ciche_doubly_remove_and_deep_free_head(stack, obj_free);
}

bool ciche_stack_pick(struct ciche_doubly *stack,  struct ciche_doubly_node **node) {
  return ciche_doubly_pick_head(stack, node);
}

bool ciche_stack_pick_obj(struct ciche_doubly *stack, void **obj) {
  return ciche_doubly_pick_head_obj(stack, obj);
}

#endif /* CICHE_STACK_H */
