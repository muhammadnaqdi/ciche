#ifndef CICHE_TREE_H
#define CICHE_TREE_H

#include "ciche_doubly.h"

struct ciche_tree_node {
  void **obj;
  struct ciche_doubly *children;
};

struct ciche_tree {
  struct ciche_tree_node *root;
};

bool ciche_tree_node_init(struct ciche_tree_node *node) {
  if (!node)
    return false;
  
  node->obj = NULL;
  node->children = NULL;

  return true;
}



#endif /* CICHE_TREE_H */
