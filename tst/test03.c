#include "../src/header/ciche_tree.h"
#include "ciche_test.h" 

struct ciche_tree *create_tree();
void print_tree(struct ciche_tree *t);
void print_doubly(struct ciche_doubly *d);
bool node_free(void *o);
bool node_equals(void *o1, void *o2);

int main(int argc, char *argv[]) {
  struct ciche_tree *t1 = create_tree();
  print_tree(t1);
  
  struct ciche_doubly *v = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  ciche_doubly_init(v);
  
  ciche_tree_add(t1->root->children->head->next->obj, coord_create());

  ciche_tree_remove(t1->root->children->head->obj, &node_equals);
  
  print_tree(t1);

  ciche_tree_remove_deep_free(t1->root->children->head->next->obj, &node_equals, &node_free);

  print_tree(t1);

  struct ciche_tree *t2 = create_tree();
  print_tree(t2);

  ciche_tree_append(t1->root, t2->root);

  print_tree(t1);

  ciche_tree_remove_deep_free(t2->root, &node_equals, &node_free);

  print_tree(t1);
  
  ciche_tree_bfs(t1->root, v);

  print_doubly(v);

  ciche_doubly_clear(v);

  ciche_tree_dfs(t1->root, v);

  print_doubly(v);
  
  return EXIT_SUCCESS;
}

void recursive_create(struct ciche_tree_node *node, int count, int level, int limit) {
  if (level == limit) {
    node->obj = (void *) coord_create();

    return;
  }

  for (int i = 0; i < count; ++i) {
    struct ciche_tree_node *new = (struct ciche_tree_node *) malloc(sizeof(struct ciche_tree_node));
    ciche_tree_node_init(new);
    
    ciche_tree_append(node, new);
  }

  struct ciche_doubly_node *tmp = node->children->head;
  while (tmp) {
    recursive_create(tmp->obj, count, level+1, limit);
    tmp = tmp->next;
  }

  node->obj = (void *) coord_create();

  return;
}

void recursive_print(struct ciche_tree_node *node) {
  if (node->children) {
    struct ciche_doubly_node *tmp = node->children->head;
    while (tmp) {
      recursive_print(tmp->obj);
      tmp = tmp->next;
    }
  }

  if (node->parrent)
    printf("(parent:%d)\t", ((struct coord *) node->parrent->obj)->id);
  coord_print((struct coord *) node->obj);

  return;
}

struct ciche_tree *create_tree() {
  struct ciche_tree_node *new = (struct ciche_tree_node *) malloc(sizeof(struct ciche_tree_node));
  ciche_tree_node_init(new);
  
  struct ciche_tree *t = (struct ciche_tree *) malloc(sizeof(struct ciche_tree));
  ciche_tree_init(t, new);

  recursive_create(new, 3, 0, 2);

  return t;
}

void print_doubly(struct ciche_doubly *d) {
  struct ciche_doubly_node *tmp = d->head;

  puts("VISIT ********");
  while(tmp) {
    coord_print((struct coord *) ((struct ciche_tree_node *) tmp->obj)->obj);
    tmp = tmp->next;
  }
  puts("********");
  puts("");
  
  return;
}

void print_tree(struct ciche_tree *t) {
  puts("********");
  recursive_print(t->root);
  puts("********");
  puts("");
}

bool node_free(void *o) {
  struct ciche_tree_node *n = (struct ciche_tree_node *) o;

  if (n->obj)
    coord_free(n->obj);

  free(n);
  
  return true;
}

bool node_equals(void *o1, void *o2) {
  struct ciche_tree_node *n1 = (struct ciche_tree_node *) o1;
  struct ciche_tree_node *n2 = (struct ciche_tree_node *) o2;

  return coord_equals(n1->obj, n2->obj);
}
