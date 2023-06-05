#include "../src/header/ciche_hash_map.h"
#include "ciche_test.h"

#define print   puts("*********");					\
                for (int i = 0; i < HASH_MAP_SIZE; ++i) {		\
                  if (!hm->map[i]) {				       	\
		    continue;						\
		  }							\
									\
		  d = hm->map[i];					\
		  n = d->head;						\
									\
		  while (n) {						\
		    coord_print((struct coord *) n->obj);		\
		    n = n->next;					\
		  }							\
                }						      	\
                puts("*********");

int main(int argc, char *argv[]) {
  struct ciche_hash_map *hm = (struct ciche_hash_map *) malloc(sizeof(struct ciche_hash_map));
  ciche_hash_map_init(hm);

  struct coord *coords[HASH_MAP_SIZE];
  struct ciche_doubly *d = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  struct ciche_doubly_node *n = (struct ciche_doubly_node *) malloc(sizeof(struct ciche_doubly_node));
  struct coord *c = (struct coord *) malloc(sizeof(struct coord));
  
  for (int i = 0; i < 16; ++i) {
    coords[i] = coord_create();
    ciche_hash_map_add(hm, coords[i], &coord_hash);
  }

  for (int i = 0; i < HASH_MAP_SIZE; ++i) {
    printf("%d", hm->map[i] ? 1 : 0);
  }
  puts("");
  puts("");

  print;

  ciche_hash_map_find(hm, coords[5], &coord_hash, &coord_equals, &n);
  coord_print((struct coord *) n->obj);

  ciche_hash_map_find_obj(hm, coords[12], &coord_hash, &coord_equals, (void **) &c);
  coord_print(c);

  ciche_hash_map_remove(hm, coords[5], &coord_hash, &coord_equals, &n);
  coord_print((struct coord *) n->obj);

  print;

  ciche_hash_map_remove_and_free(hm, coords[10], &coord_hash, &coord_equals);

  print;

  ciche_hash_map_remove_and_deep_free(hm, coords[0], &coord_hash, &coord_equals, &coord_free);

  print;
  
  return EXIT_SUCCESS;
}
