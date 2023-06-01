#ifndef CICHE_STACK_H
#define CICHE_STACK_H

#include "ciche_doubly.h"

typedef struct ciche_doubly ciche_stack;

bool ciche_stack_push(struct ciche_doubly *stack, void *frame) {
  return ciche_doubly_insert_at_tail(stack, frame);
}

bool ciche_stack_pop(struct ciche_doubly *stack, struct ciche_doubly_node **node) {
  return ciche_doubly_remove_tail(stack, node);
}

bool ciche_stack_pop_and_free(struct ciche_doubly *stack,  void **frame) {
  return ciche_doubly_remove_and_free_tail(stack, frame);
}

bool ciche_stack_pop_and_deep_free(struct ciche_doubly *stack, bool (*obj_free)(void *)) {
  return ciche_doubly_remove_and_deep_free_tail(stack, obj_free);
}

bool ciche_stack_pick_top(struct ciche_doubly *stack,  struct ciche_doubly_node **node) {
  return ciche_doubly_pick_tail(stack, node);
}

bool ciche_stack_pick_top_frame(struct ciche_doubly *stack, void **frame) {
  return ciche_doubly_pick_tail_obj(stack, frame);
}

#endif /* CICHE_STACK_H */
