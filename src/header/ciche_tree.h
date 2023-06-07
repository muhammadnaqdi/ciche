#ifndef CICHE_TREE_H
#define CICHE_TREE_H

#include "ciche_doubly.h"
#include "ciche_stack.h"
#include "ciche_queue.h"

struct ciche_tree_node {
  void *obj;
  struct ciche_tree_node *parrent;
  struct ciche_doubly *children;
};

struct ciche_tree {
  struct ciche_tree_node *root;
};

bool ciche_tree_init(struct ciche_tree *tree, struct ciche_tree_node *root) {
  if (!tree || !root)
    return false;

  tree->root = root;

  return true;
}

bool ciche_tree_node_init(struct ciche_tree_node *node) {
  if (!node)
    return false;
  
  node->obj = NULL;
  node->parrent = NULL;
  node->children = NULL;

  return true;
}

bool ciche_tree_add(struct ciche_tree_node *node, void *obj) {
  if (!node)
    false;
  
  if (!node->children) {
    if (!(node->children = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly))))
      return false;

    if (!ciche_doubly_init(node->children))
      return false;
  }

  struct ciche_tree_node *new = malloc(sizeof(struct ciche_tree_node *));
  if (!new)
    return false;
  if (!ciche_tree_node_init(new))
    return false;
  new->obj = obj;
  new->parrent = node;
  
  return ciche_doubly_insert_at_tail(node->children, new);
}

bool ciche_tree_append(struct ciche_tree_node *dest, struct ciche_tree_node *src) {
  if (!dest || !src)
    return false;
  
  if (!dest->children) {
    if (!(dest->children = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly))))
      return false;

    if (!ciche_doubly_init(dest->children))
      return false;
  }

  src->parrent = dest;
  
  return ciche_doubly_insert_at_tail(dest->children, src);
}

bool ciche_tree_dfs(struct ciche_tree_node *node, struct ciche_doubly *visit) {
  if (!node || !visit)
    return false;

  struct ciche_doubly *stack = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  if (!ciche_doubly_init(stack))
    return false;

  ciche_stack_push(stack, node);

  struct ciche_doubly_node *tmp = NULL;
  while (stack->size > 0) {
    ciche_stack_pop_and_free(stack, (void **) &node);
    ciche_stack_push(visit, node);

    if (!node->children)
      continue;
    
    tmp = node->children->head;
    while (tmp) {
      ciche_stack_push(stack, tmp->obj);
      tmp = tmp->next;
    }
  }

  ciche_doubly_free(stack);
  
  return true;
}

bool ciche_tree_bfs(struct ciche_tree_node *node, struct ciche_doubly *visit) {
  if (!node || !visit)
    return false;

  struct ciche_doubly *queue = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  if (!ciche_doubly_init(queue))
    return false;

  ciche_queue_add(queue, node);
  
  while (queue->size > 0) {
    ciche_queue_remove_and_free(queue, (void **) &node);
    ciche_queue_add(visit, node);

    if (!node->children)
      continue;
    
    struct ciche_doubly_node *tmp = node->children->head;
    while (tmp) {
      ciche_queue_add(queue, tmp->obj);
      tmp = tmp->next;
    }
  }

  ciche_doubly_free(queue);
  
  return true;
}

bool ciche_tree_remove(struct ciche_tree_node *node, bool (*node_equals)(void *, void *)) {
  struct ciche_tree_node *p = node->parrent;
  if (!p)
    return true;

  node->parrent = NULL;
  
  return ciche_doubly_find_and_remove_and_free(p->children, node, node_equals);
}

bool ciche_tree_remove_deep_free(struct ciche_tree_node *node, bool (*node_equals)(void *, void *), bool (*node_free)(void *)) {
  struct ciche_tree_node *p = node->parrent;
  
  if (p)
    if(!ciche_doubly_find_and_remove_and_free(p->children, node, node_equals))
      return false;

  struct ciche_doubly *visit = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  if (!visit)
    return false;
  if (!ciche_doubly_init(visit))
      return false;

  if (!ciche_tree_dfs(node, visit))
    return false;

  if (!ciche_doubly_clear_and_deep_free(visit, node_free))
    return false;

  ciche_doubly_free(visit);
  
  return true;
}

#endif /* CICHE_TREE_H */
