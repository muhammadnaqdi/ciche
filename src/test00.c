#include "test.h"
#include "ciche_tree.h"

void make_tree(struct ciche_tree_node *root, int l, int ml) {
  if (l > ml)
    return;

  int c = rand() % 4;

  if (c <= 0)
    return;

  struct ciche_doubly_node *n;
  ciche_tree_add_child(root, coord_create());
  n = root->children->head;
  
  for (int i = 1; i < c; ++i) {
    make_tree(n->obj, ++l, ml);
    ciche_tree_add_child(root, coord_create());
    n = n->next;
  }

  make_tree(n->obj, ++l, ml);

  return;
}

int main() {
  struct ciche_tree_node *root = (struct ciche_tree_node *) malloc(sizeof(struct ciche_tree_node)); 
  ciche_tree_node_init(root);
  root->obj = (void *) coord_create();
  
  make_tree(root, 0, 3);

  struct ciche_doubly visit;
  ciche_doubly_init(&visit);
  
  ciche_tree_bfs(root, &visit);

  struct ciche_doubly_node *tmp = visit.head;

  while (tmp) {
    printf("%ld\n", (long) ((struct ciche_tree_node *) tmp->obj)->parrent);
    coord_print((struct coord *) ((struct ciche_tree_node *) tmp->obj)->obj);
    tmp = tmp->next;
  }
  
  return 0;
}
