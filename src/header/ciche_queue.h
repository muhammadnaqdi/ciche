#ifndef CICHE_QUEUE_H
#define CICHE_QUEUE_H

#include "ciche_doubly.h"

typedef struct ciche_doubly ciche_queue;

bool ciche_queue_add(struct ciche_doubly *queue, void *obj) {
  return ciche_doubly_insert_at_tail(queue, obj);
}

bool ciche_queue_remove(struct ciche_doubly *queue, struct ciche_doubly_node **node) {
  return ciche_doubly_remove_head(queue, node);
}

bool ciche_queue_remove_and_free(struct ciche_doubly *queue,  void **obj) {
  return ciche_doubly_remove_and_free_head(queue, obj);
}

bool ciche_queue_remove_and_deep_free(struct ciche_doubly *queue, bool (*obj_free)(void *)) {
  return ciche_doubly_remove_and_deep_free_head(queue, obj_free);
}

bool ciche_queue_pick(struct ciche_doubly *queue,  struct ciche_doubly_node **node) {
  return ciche_doubly_pick_head(queue, node);
}

bool ciche_queue_pick_obj(struct ciche_doubly *queue, void **obj) {
  return ciche_doubly_pick_head_obj(queue, obj);
}

#endif /* CICHE_QUEUE_H */
