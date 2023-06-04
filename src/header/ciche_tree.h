#ifndef CICHE_TREE_H
#define CICHE_TREE_H

#include "ciche_doubly.h"
#include "ciche_stack.h"
#include "ciche_queue.h"

struct ciche_tree_node {
  void **obj;
  struct ciche_tree_node *parrent;
  struct ciche_doubly *children;
};

struct ciche_tree {
  struct ciche_tree_node *root;
};

bool ciche_tree_node_init(struct ciche_tree_node *node) {
  if (!node)
    return false;
  
  node->obj = NULL;
  node->parrent = NULL;
  node->children = NULL;

  return true;
}

bool ciche_tree_add_child(struct ciche_tree_node *node, void *obj) {
  if (!node)
    false;
  
  if (!node->children) {
    if (!(node->children = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly))))
      return false;

    if (!ciche_doubly_init(node->children))
      return false;
  }

  struct ciche_tree_node *tmp = malloc(sizeof(struct ciche_tree_node *));
  if (!tmp)
    return false;
  if (!ciche_tree_node_init(tmp))
    return false;
  tmp->obj = obj;
  tmp->parrent = node;
  
  return ciche_doubly_insert_at_tail(node->children, tmp);
}

bool ciche_tree_dfs(struct ciche_tree_node *node, struct ciche_doubly *visit) {
  if (!node || !visit)
    return false;

  struct ciche_doubly stack;
  if (!ciche_doubly_init(&stack))
    return false;

  ciche_stack_push(&stack, node);
  
  while (stack.size > 0) {
    ciche_stack_pop_and_free(&stack, (void **) &node);
    ciche_stack_push(visit, node);

    if (!node->children)
      continue;
    
    struct ciche_doubly_node *tmp = node->children->tail;
    while (tmp) {
      ciche_stack_push(&stack, tmp->obj);
      tmp = tmp->prev;
    }
  }
  
  return true;
}

bool ciche_tree_bfs(struct ciche_tree_node *node, struct ciche_doubly *visit) {
  if (!node || !visit)
    return false;

  struct ciche_doubly queue;
  if (!ciche_doubly_init(&queue))
    return false;

  ciche_queue_add(&queue, node);
  
  while (queue.size > 0) {
    ciche_queue_remove_and_free(&queue, (void **) &node);
    ciche_queue_add(visit, node);

    if (!node->children)
      continue;
    
    struct ciche_doubly_node *tmp = node->children->head;
    while (tmp) {
      ciche_queue_add(&queue, tmp->obj);
      tmp = tmp->next;
    }
  }

  return true;
}

bool ciche_tree_remove(struct ciche_tree_node *node, bool (*node_equals)(void *, void *)) {
  struct ciche_tree_node *p = node->parrent;
  if (!p)
    return true;

  return ciche_doubly_find_and_remove_and_free(p->children, node, node_equals);
}

bool ciche_tree_remove_deep_free(struct ciche_tree_node *node, bool (*node_equals)(void *, void *), bool (*node_free)(void *)) {
  struct ciche_tree_node *p = node->parrent;
  if (p)
    if(!ciche_doubly_find_and_remove_and_free(p->children, node, node_equals))
      return false;

  struct ciche_doubly visit;
  if (!ciche_doubly_init(&visit))
      return false;

  if (!ciche_tree_dfs(node, &visit))
    return false;

  if (!ciche_doubly_clean_and_deep_free(&visit, node_free))
    return false;
  
  return true;
}

#endif /* CICHE_TREE_H */
