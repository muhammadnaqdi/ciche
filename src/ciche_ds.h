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

bool ciche_doubly_node_init(struct ciche_doubly_node *node) {
  if (node == NULL)
    return false;
  
  node->obj = NULL;
  node->next = NULL;
  node->prev = NULL;

  return true;
}

bool ciche_doubly_node_free(struct ciche_doubly_node *node, void **obj) {
  if (node == NULL)
    return false;
  
  *obj = node->obj;
  
  free(node);

  return true;
}

bool ciche_doubly_node_deep_free(struct ciche_doubly_node *node, bool (*obj_free)(void *)) {
  if (node == NULL)
    return false;

  bool result = true;
  if (obj_free != NULL)
    result = obj_free(node->obj);
  
  free(node);

  return result;
}

struct ciche_doubly {
  size_t size;
  struct ciche_doubly_node *head;
  struct ciche_doubly_node *tail;
};

bool ciche_doubly_init(struct ciche_doubly *doubly) {
  if (doubly == NULL)
    return false;
  
  doubly->size = 0;
  doubly->head = NULL;
  doubly->tail = NULL;
  
  return true;
}

bool ciche_doubly_insert_at_head(struct ciche_doubly *doubly, void *obj) {
  if (doubly == NULL || doubly->size < 0)
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
  if (doubly == NULL || doubly->size < 0)
    return false;

  struct ciche_doubly_node *node = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!ciche_doubly_node_init(node))
    return false;
  node->obj = obj;

  if (doubly->size == 0) {
    doubly->head = doubly->tail = node;
  } else {
    node->prev = doubly->tail;
    doubly->tail->next = node;
    doubly->tail = node;
  }

  doubly->size ++;
  
  return true;
}

bool ciche_doubly_insert_before(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void *obj) {
  if (doubly == NULL || node == NULL)
    return false;

  struct ciche_doubly_node *tmp = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!ciche_doubly_node_init(tmp))
    return false;
  tmp->obj = obj;

  struct ciche_doubly_node *p = node->prev;
  
  if (p == NULL) {
    ciche_doubly_insert_at_head(doubly, obj);
  } else {
    node->prev = tmp;
    tmp->next = node;
    tmp->prev = p;
    p->next = tmp;
  }

  doubly->size ++;
  return true;
}

bool ciche_doubly_insert_after(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void *obj) {
  if (doubly == NULL || node == NULL)
    return false;

  struct ciche_doubly_node *tmp = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  if (!ciche_doubly_node_init(tmp))
    return false;
  tmp->obj = obj;

  struct ciche_doubly_node *n = node->prev;
  
  if (n == NULL) {
    ciche_doubly_insert_at_tail(doubly, obj);
  } else {
    node->next = tmp;
    tmp->prev = node;
    tmp->next = n;
    n->prev = tmp;
  }

  doubly->size ++;
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

bool ciche_doubly_remove_head(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (doubly->size == 1) {
    doubly->head = NULL;
    doubly->tail = NULL;		  
  } else {
    doubly->head = doubly->head->next;
    doubly->head->prev = NULL;
  }

  doubly->size --;

  ciche_doubly_node_free(tmp, obj);
  
  return true;
}


bool ciche_doubly_remove_tail(struct ciche_doubly *doubly, void **obj) {
  if (doubly == NULL || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->tail;

  if (doubly->size == 1) {
    doubly->head = NULL;
    doubly->tail = NULL;
  } else {
    doubly->tail = doubly->tail->prev;
    doubly->tail->next = NULL;
  }

  doubly->size --;

  ciche_doubly_node_free(tmp, obj);
  
  return true;
}

bool ciche_doubly_remove_and_free_head(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (doubly->size == 1) {
    doubly->head = NULL;
    doubly->tail = NULL;
  } else {
    doubly->head = doubly->head->next;
    doubly->head->prev = NULL;
  }

  doubly->size --;

  ciche_doubly_node_deep_free(tmp, obj_free);
  
  return true;
}


bool ciche_doubly_remove_and_free_tail(struct ciche_doubly *doubly, bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size <= 0)
    return false;

  struct ciche_doubly_node *tmp = doubly->tail;

  if (doubly->size == 1) {
    doubly->head = NULL;
    doubly->tail = NULL;
  } else {
    doubly->tail = doubly->tail->prev;
    doubly->tail->next = NULL;
  }

  doubly->size --;

  ciche_doubly_node_deep_free(tmp, obj_free);
  
  return true;
}

bool ciche_doubly_remove_node(struct ciche_doubly *doubly, struct ciche_doubly_node *node, void **obj) {
  if (doubly == NULL || node == NULL)
    return false;

  struct ciche_doubly_node *p, *n;
  p = node->prev;
  n = node->next;

  if (p == NULL && n == NULL)
    return ciche_doubly_remove_head(doubly, obj);

  if (p == NULL)
    return ciche_doubly_remove_head(doubly, obj);

  if (n == NULL)
    return ciche_doubly_remove_tail(doubly, obj);

  p->next = n;
  n->prev = p;
  ciche_doubly_node_free(node, obj);

  return true;
}

bool ciche_doubly_remove_node_and_free(struct ciche_doubly *doubly, struct ciche_doubly_node *node, bool (*obj_free)(void *obj)) {
  if (doubly == NULL || node == NULL)
    return false;

  struct ciche_doubly_node *p, *n;
  p = node->prev;
  n = node->next;

  if (p == NULL && n == NULL)
    return ciche_doubly_remove_and_free_head(doubly, obj_free);

  if (p == NULL)
    return ciche_doubly_remove_and_free_head(doubly, obj_free);

  if (n == NULL)
    return ciche_doubly_remove_and_free_tail(doubly, obj_free);

  p->next = n;
  n->prev = p;
  ciche_doubly_node_deep_free(node, obj_free);

  return true;
}

bool ciche_doubly_find(struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), struct ciche_doubly_node **node) {
  if (doubly == NULL)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (obj_equals != NULL) {
    while (tmp != NULL) {
      if (obj_equals(tmp->obj, obj)) {
	*node = tmp;
	return true;
      }

      tmp = tmp->next;
    }
  } else {
    while (tmp != NULL) {
      if (tmp->obj == obj) {
	*node = tmp;
	return true;
      }

      tmp = tmp->next;
    }
  }

  return false;
}

/* This one is kind of tricky. Shude be used on one list at a time. I have no intention to test it.*/
bool ciche_doubly_find_next(bool reset, struct ciche_doubly *doubly, void *obj, bool (*obj_equals)(void *, void *), struct ciche_doubly_node **node) {
  static size_t found = 0;
  if (reset)
    found = 0;
  int c = 0;

  if (doubly == NULL)
    return false;

  struct ciche_doubly_node *tmp = doubly->head;

  if (obj_equals != NULL) {
    while (tmp != NULL) {
      if (obj_equals(tmp->obj, obj)) {
	if (c < found) {
	  c ++;
	} else {
	  found ++;
	  *node = tmp;
	  return true;
	}
      }

      tmp = tmp->next;
    }
  } else {
    while (tmp != NULL) {
      if (tmp->obj == obj) {
	if (c < found) {
	  c ++;
	} else {
	  found ++;
	  *node = tmp;
	  return true;
	}
      }

      tmp = tmp->next;
    }
  }

  return false;
}

bool ciche_doubly_free(struct ciche_doubly *doubly) {
  free(doubly);
  
  return true;
}

bool ciche_doubly_clean(struct ciche_doubly *doubly,  bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size < 0)
    return false;

  bool result = true;

   while (doubly->size > 0) {
     result &= ciche_doubly_remove_and_free_tail(doubly, obj_free);
   }
  
   return result;
}

bool ciche_doubly_clean_optimized(struct ciche_doubly *doubly,  bool (*obj_free)(void *)) {
  if (doubly == NULL || doubly->size < 0)
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

#endif /* CICHE_DS_H */
