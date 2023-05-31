#ifndef CICHE_HASH_MAP_H
#define CICHE_HASH_MAP_H

#include "ciche_doubly.h"

#define HASH_MAP_SIZE 8192
struct ciche_hash_map {
  struct ciche_doubly *map[HASH_MAP_SIZE];
};

bool ciche_hash_map_init(struct ciche_hash_map *hmap) {
  if (hmap == NULL)
    return false;

  for (int i = 0; i < HASH_MAP_SIZE; ++i)
    hmap->map[i] = NULL;

  return true;
}

bool ciche_hash_map_add(struct ciche_hash_map *hmap, void *obj, size_t (*obj_hash)(void *)) {
  size_t index = obj_hash(obj) % HASH_MAP_SIZE;
  struct ciche_doubly *doubly = hmap->map[index];

  if (doubly == NULL) {
    doubly = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
    if (!ciche_doubly_init(doubly))
      return false;
  }

  return ciche_doubly_insert_at_tail(doubly, obj);
}

bool ciche_hash_find(struct ciche_hash_map *hmap, void *obj, size_t (*obj_hash)(void *), bool (*obj_equals)(void *, void *), struct ciche_doubly_node **node) {
  size_t index = obj_hash(obj) % HASH_MAP_SIZE;
  struct ciche_doubly *doubly = hmap->map[index];

  if (doubly == NULL)
    return false;

  return ciche_doubly_find(doubly, obj, obj_equals, node);
}

/*bool ciche_hash_map_remove(struct ciche_hash_map *hmap, void *obj, size_t (*obj_hash)(void *), bool (*obj_equals)(void *)) {
  size_t index = obj_hash(obj) % HASH_MAP_SIZE;
  struct ciche_doubly *doubly = hmap->map[index];
  }*/

#endif /* CICHE_HASH_MAP_H */
