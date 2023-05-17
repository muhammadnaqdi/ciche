#ifndef CICHE_DS_H
#define CICHE_DS_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

struct ciche_doubly_node {
  void *obj;
  struct ciche_doubly_node *next;
  struct ciche_doubly_node *prev;
};

struct ciche_doubly {
  size_t size;
  struct ciche_doubly_node *head;
  struct ciche_doubly_node *tail;
};

bool ciche_doubly_node_init(struct ciche_doubly_node *node) {
  if (node == NULL)
    return false;
  
  node->obj = NULL;
  node->next = NULL;
  node->prev = NULL;

  return true;
}

bool ciche_doubly_init(struct ciche_doubly *doubly) {
  if (doubly == NULL)
    return false;
  
  doubly->size = 0;
  doubly->head = NULL;
  doubly->tail = NULL;
  
  return true;
}

bool ciche_doubly_node_free(struct ciche_doubly_node *node, void **obj) {
  if (node == NULL)
    return false;
  
  *obj = node->obj;
  
  free(node);

  return true;
}

bool ciche_doubly_free(struct ciche_doubly *doubly) {
  if (doubly == NULL)
    return false;
  
  free(doubly);
  
  return true;
}

bool ciche_doubly_node_deep_free(struct ciche_doubly_node *node, bool (*obj_free)(void *)) {
  if (node == NULL || obj_free == NULL)
    return false;

  bool result = obj_free(node->obj);
  
  free(node);

  return result;
}

bool ciche_doubly_deep_free(struct ciche_doubly *doubly,  bool (*obj_free)(void *)) {
  if (doubly == NULL || obj_free == NULL)
    return false;

  bool result = true;

  if (doubly->size > 0) {
    struct ciche_doubly_node *tmp = NULL;
    for (int i = 1; i < doubly->size; ++i) {
      tmp = doubly->head;
      doubly->head = doubly->head->next;

      result &= ciche_doubly_node_deep_free(tmp, obj_free);
    }
    
    result &= ciche_doubly_node_deep_free(doubly->head, obj_free);
  }

  free(doubly);
  
  return result;
}

bool ciche_doubly_insert_at_head(struct ciche_doubly *doubly, void *obj) {
  if (doubly == NULL || obj == NULL)
    return false;

  struct ciche_doubly_node *node = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!ciche_doubly_node_init(node))
    return false;
  
  node->obj = obj;

  if (doubly->size == 0) {
    doubly->head = doubly->tail = node;
  } else {
    node->next = doubly->head;
    doubly->head->prev = node;
    doubly->head = node;
  }

  doubly->size ++;
  
  return true;
}

bool ciche_doubly_insert_at_tail(struct ciche_doubly *doubly, void *obj) {
  if (doubly == NULL || obj == NULL)
    return false;

  struct ciche_doubly_node *node = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!ciche_doubly_node_init(node))
    return false;

  node->obj = obj;

  if (doubly->tail == NULL) {
    doubly->head = doubly->tail = node;
  } else {
    node->prev = doubly->tail;
    doubly->tail->next = node;
    doubly->tail = node;
  }

  doubly->size ++;
  
  return true;
}

bool ciche_doubly_remove_head(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->size == 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (doubly->size > 1) {
    doubly->head = doubly->head->next;
    doubly->head->prev = NULL;
  } else {
    doubly->head = NULL;
    doubly->tail = NULL;
  }

  doubly->size --;

  ciche_doubly_node_free(tmp, obj);
  
  return true;
}


bool ciche_doubly_remove_tail(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->size == 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->tail;

  if (doubly->size > 1) {
    doubly->tail = doubly->tail->prev;
    doubly->tail->next = NULL;
  } else {
    doubly->head = NULL;
    doubly->tail = NULL;
  }

  doubly->size --;

  ciche_doubly_node_free(tmp, obj);
  
  return true;
}

bool ciche_doubly_remove_and_free_head(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size == 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (doubly->size > 1) {
    doubly->head = doubly->head->next;
    doubly->head->prev = NULL;
  } else {
    doubly->head = NULL;
    doubly->tail = NULL;
  }

  doubly->size --;

  ciche_doubly_node_deep_free(tmp, obj_free);
  
  return true;
}


bool ciche_doubly_remove_and_free_tail(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size == 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->tail;

  if (doubly->size > 1) {
    doubly->tail = doubly->tail->prev;
    doubly->tail->next = NULL;
  } else {
    doubly->head = NULL;
    doubly->tail = NULL;
  }

  doubly->size --;

  ciche_doubly_node_deep_free(tmp, obj_free);
  
  return true;
}

bool ciche_doubly_pick_head(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (doubly == NULL || doubly->head == NULL)
    return false;

  *node = doubly->head;

  return true;
}


bool ciche_doubly_pick_tail(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (doubly == NULL || doubly->tail == NULL)
    return false;

  *node = doubly->tail;

  return true;
}

bool ciche_doubly_pick_head_obj(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->head == NULL)
    return false;

  *obj = doubly->head->obj;

  return true;
}


bool ciche_doubly_pick_tail_obj(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->tail == NULL)
    return false;

  *obj = doubly->tail->obj;

  return true;
}

#endif /* CICHE_DS_H */
