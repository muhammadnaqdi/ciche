#ifndef CICHE_DOUBLY_H
#define CICHE_DOUBLY_H

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
  if (!node)
    return false;
  
  node->obj = NULL;
  node->next = NULL;
  node->prev = NULL;

  return true;
}

bool ciche_doubly_node_free(struct ciche_doubly_node *node, void **obj) {
  if (!node)
    return false;

  if (obj)
    *obj = node->obj;
  
  free(node);

  return true;
}

bool ciche_doubly_node_deep_free(struct ciche_doubly_node *node, bool (*obj_free)(void *)) {
  if (!node)
    return false;

  bool result = true;
  
  if (obj_free)
    result = obj_free(node->obj);
  
  free(node);

  return result;
}

bool ciche_doubly_init(struct ciche_doubly *doubly) {
  if (!doubly)
    return false;
  
  doubly->size = 0;
  doubly->head = NULL;
  doubly->tail = NULL;
  
  return true;
}

bool ciche_doubly_insert_at_head(struct ciche_doubly *doubly, void *obj) {
  if (!doubly || doubly->size < 0)
    return false;

  struct ciche_doubly_node *new = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!new)
    return false;
  
  if (!ciche_doubly_node_init(new))
    return false;
  new->obj = obj;

  if (doubly->size == 0) {
    doubly->head = doubly->tail = new;
  } else {
    new->next = doubly->head;
    doubly->head->prev = new;
    doubly->head = new;
  }

  doubly->size ++;
  
  return true;
}

bool ciche_doubly_insert_at_tail(struct ciche_doubly *doubly, void *obj) {
  if (!doubly || doubly->size < 0)
    return false;

  struct ciche_doubly_node *new = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!new)
    return false;
  
  if (!ciche_doubly_node_init(new))
    return false;
  new->obj = obj;

  if (doubly->size == 0) {
    doubly->head = doubly->tail = new;
  } else {
    new->prev = doubly->tail;
    doubly->tail->next = new;
    doubly->tail = new;
  }

  doubly->size ++;
  
  return true;
}

bool ciche_doubly_insert_before(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void *obj) {
  if (!doubly || !node)
    return false;

  struct ciche_doubly_node *new = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!new)
    return false;
  
  if (!ciche_doubly_node_init(new))
    return false;
  new->obj = obj;

  struct ciche_doubly_node *p = node->prev;
  
  if (!p) {
    ciche_doubly_insert_at_head(doubly, obj);
  } else {
    node->prev = new;
    new->next = node;
    new->prev = p;
    p->next = new;
    doubly->size ++;
  }

  return true;
}

bool ciche_doubly_insert_after(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void *obj) {
  if (!doubly || !node)
    return false;

  struct ciche_doubly_node *new = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!new)
    return false;
  
  if (!ciche_doubly_node_init(new))
    return false;
  new->obj = obj;

  struct ciche_doubly_node *n = node->next;
  
  if (!n) {
    ciche_doubly_insert_at_tail(doubly, obj);
  } else {
    node->next = new;
    new->prev = node;
    new->next = n;
    n->prev = new;
    doubly->size ++;
  }
  
  return true;
}

bool ciche_doubly_pick_head(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (!doubly || !doubly->head || !node)
    return false;

  *node = doubly->head;

  return true;
}


bool ciche_doubly_pick_tail(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (!doubly || !doubly->tail || !node)
    return false;

  *node = doubly->tail;

  return true;
}

bool ciche_doubly_pick_head_obj(struct ciche_doubly *doubly, void **obj) {
  if (!doubly || !doubly->head || !obj)
    return false;

  *obj = doubly->head->obj;

  return true;
}


bool ciche_doubly_pick_tail_obj(struct ciche_doubly *doubly, void **obj) {
  if (!doubly || !doubly->tail || !obj)
    return false;

  *obj = doubly->tail->obj;

  return true;
}

bool ciche_doubly_find(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), struct ciche_doubly_node **node) {
  if (!doubly || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (obj_equals) {
    while (tmp) {
      if (obj_equals(tmp->obj, obj)) {
	if (node)
	  *node = tmp;
	return true;
      }

      tmp = tmp->next;
    }
  } else {
    while (tmp) {
      if (tmp->obj == obj) {
	if (node)
	  *node = tmp;
	return true;
      }

      tmp = tmp->next;
    }
  }

  return false;
}

bool ciche_doubly_find_obj(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), void **fobj) {
  if (!doubly || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (obj_equals) {
    while (tmp) {
      if (obj_equals(tmp->obj, obj)) {
	*fobj = tmp->obj;
	return true;
      }

      tmp = tmp->next;
    }
  } else {
    while (tmp) {
      if (tmp->obj == obj) {
	*fobj = tmp->obj;
	return true;
      }

      tmp = tmp->next;
    }
  }

  return false;
}

bool ciche_doubly_remove(struct ciche_doubly *doubly, struct ciche_doubly_node *node) {
  if (!doubly || !node || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *p, *n;
  p = node->prev;
  n = node->next;

  if (!p && !n) {
     doubly->head = NULL;
     doubly->tail = NULL;
  }
  else if (!p) {
    doubly->head = doubly->head->next;
    doubly->head->prev = NULL;
  }
  else if (!n) {
    doubly->tail = doubly->tail->prev;
    doubly->tail->next = NULL;
  }
  else {
    p->next = n;
    n->prev = p;
  }

  node->prev = NULL;
  node->next = NULL;
  
  doubly->size --;

  return true;
}

bool ciche_doubly_remove_and_free(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void **obj) {
  bool result = true;

  result &= ciche_doubly_remove(doubly, node);
  result &= ciche_doubly_node_free(node, obj);

  return result;
}

bool ciche_doubly_remove_and_deep_free(struct ciche_doubly *doubly, struct ciche_doubly_node *node, bool (*obj_free)(void *obj)) {
  bool result = true;
  
  result &= ciche_doubly_remove(doubly, node);
  result &= ciche_doubly_node_deep_free(node, obj_free);
  
  return result;
}

bool ciche_doubly_remove_head(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (node)
    *node = doubly->head;
  
  return ciche_doubly_remove(doubly, doubly->head);
}


bool ciche_doubly_remove_tail(struct ciche_doubly *doubly, struct ciche_doubly_node **node) {
  if (node)
    *node = doubly->tail;

  return ciche_doubly_remove(doubly, doubly->tail);
}

bool ciche_doubly_remove_and_free_head(struct ciche_doubly *doubly, void **obj) {
  return ciche_doubly_remove_and_free(doubly, doubly->head, obj);
}


bool ciche_doubly_remove_and_free_tail(struct ciche_doubly *doubly, void **obj) {
  return ciche_doubly_remove_and_free(doubly, doubly->tail, obj);
}

bool ciche_doubly_remove_and_deep_free_head(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  return ciche_doubly_remove_and_deep_free(doubly, doubly->head, obj_free);
}

bool ciche_doubly_remove_and_deep_free_tail(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  return ciche_doubly_remove_and_deep_free(doubly, doubly->tail, obj_free);
}

bool ciche_doubly_find_and_remove(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), struct ciche_doubly_node **node) {
  struct ciche_doubly_node *tmp = NULL;
  
  if (!ciche_doubly_find(doubly, obj, obj_equals, &tmp))
      return false;

  if (node)
    *node = tmp;
  
  return ciche_doubly_remove(doubly, tmp);
}

bool ciche_doubly_find_and_remove_and_free(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *)) {
  struct ciche_doubly_node *tmp = NULL;
  if (!ciche_doubly_find(doubly, obj, obj_equals, &tmp))
      return false;

  return ciche_doubly_remove_and_free(doubly, tmp, NULL);
}

bool ciche_doubly_find_and_remove_and_deep_free(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), bool (*obj_free)(void *obj)) {
  struct ciche_doubly_node *tmp = NULL;
  if (!ciche_doubly_find(doubly, obj, obj_equals, &tmp))
      return false;

  return ciche_doubly_remove_and_deep_free(doubly, tmp, obj_free);
}

bool ciche_doubly_clear(struct ciche_doubly *doubly) {
  if (!doubly || doubly->size < 0)
    return false;

  bool result = true;

   while (doubly->size > 0)
     result &= ciche_doubly_remove_tail(doubly, NULL);
   
   return result;
}

bool ciche_doubly_clear_and_free(struct ciche_doubly *doubly) {
  if (!doubly || doubly->size < 0)
    return false;

  bool result = true;

   while (doubly->size > 0)
     result &= ciche_doubly_remove_and_free_tail(doubly, NULL);
   
   return result;
}

bool ciche_doubly_clear_and_deep_free(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  if (!doubly || doubly->size < 0)
    return false;

  bool result = true;

   while (doubly->size > 0)
     result &= ciche_doubly_remove_and_deep_free_tail(doubly, obj_free);
   
   return result;
}

bool ciche_doubly_clear_deep_free_optimized(struct ciche_doubly *doubly,  bool (*obj_free)(void *)) {
  if (!doubly || doubly->size < 0)
    return false;

  bool result = true;

  struct ciche_doubly_node *tmp = NULL;
  for (int i = 1; i < doubly->size; ++i) {
    tmp = doubly->head;
    doubly->head = doubly->head->next;

    result &= ciche_doubly_node_deep_free(tmp, obj_free);
  }

  result &= ciche_doubly_node_deep_free(doubly->head, obj_free);


   doubly->head = NULL;
   doubly->tail = NULL;
   doubly->size = 0;
  
   return result;
}

bool ciche_doubly_free(struct ciche_doubly *doubly) {
  free(doubly);
  
  return true;
}

#endif /* CICHE_DOUBLY_H */
