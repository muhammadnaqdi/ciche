#include "ciche_test.h"
#include "../src/ciche_doubly.h"

#include <stdlib.h>

#define print   i = doubly->head;		  \
                while (i) {			  \
		  coord_print(i->obj);		  \
		  i = i->next;			  \
		}				  \
		puts("");

int main(int argc, char *argv[]) {
  struct ciche_doubly *doubly = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));

  ciche_doubly_init(doubly);

  ciche_doubly_insert_at_head(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());
  
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());

  struct coord *c0 = (struct coord *) malloc(sizeof(struct coord));
  c0->id = 0;
  c0->x = 1;
  c0->y = 2;
  c0->z = 3;
  
  struct ciche_doubly_node *n = NULL;

  struct ciche_doubly_node *i = NULL;
  
  ciche_doubly_find(doubly, c0, &coord_equals, &n);

  ciche_doubly_insert_after(doubly, n, coord_create());
  ciche_doubly_insert_before(doubly, n, coord_create());

  print

  ciche_doubly_pick_head(doubly, &n);
  coord_print((struct coord *) n->obj);
  ciche_doubly_pick_tail(doubly, &n);
  coord_print((struct coord *) n->obj);
  puts("");

  struct coord *c = NULL;
  ciche_doubly_pick_head_obj(doubly, (void **) &c);
  coord_print(c);
  ciche_doubly_pick_tail_obj(doubly, (void **) &c);
  coord_print(c);
  puts("");

  ciche_doubly_find_obj(doubly, c0, &coord_equals, (void **) &c);
  coord_print(c);
  puts("");

  ciche_doubly_find(doubly, c0, &coord_equals, &n);
  ciche_doubly_remove(doubly, n);

  print

  ciche_doubly_insert_at_tail(doubly, c0);

  print
    
  ciche_doubly_find(doubly, c0, &coord_equals, &n);
  ciche_doubly_remove_and_free(doubly, n, (void **) &c);
  coord_print((struct coord *) c);
  puts("");

  print

  ciche_doubly_insert_at_head(doubly, c0);

  print

  ciche_doubly_find(doubly, c0, &coord_equals, &n);
  ciche_doubly_remove_and_deep_free(doubly, n, &coord_free);

  print

  ciche_doubly_remove_and_deep_free_head(doubly, &coord_free);
  ciche_doubly_remove_and_deep_free_tail(doubly, &coord_free);

  print

  c0 = (struct coord *) malloc(sizeof(struct coord));
  c0->id = 0;
  c0->x = 1;
  c0->y = 2;
  c0->z = 3;
    
  ciche_doubly_insert_at_tail(doubly, c0);
  ciche_doubly_insert_at_tail(doubly, c0);
  ciche_doubly_insert_at_tail(doubly, c0);
  //ciche_doubly_insert_at_tail(doubly, c0);

  puts("HEY!");
  print

  ciche_doubly_remove_head(doubly, &n);
  coord_print((struct coord *) n->obj);
  puts("");

  print

  ciche_doubly_remove_and_free_head(doubly, (void **) &c);
  coord_print((struct coord *) c);
  puts("");

  print

  ciche_doubly_remove_and_deep_free_head(doubly, &coord_free);

  print
  
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());

  print

  ciche_doubly_remove_tail(doubly, &n);
  coord_print((struct coord *) n->obj);
  puts("");

  print

  ciche_doubly_remove_and_free_tail(doubly, (void **) &c);
  coord_print((struct coord *) c);
  puts("");

  print

  ciche_doubly_remove_and_deep_free_tail(doubly, &coord_free);

  print

  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());

  print

  ciche_doubly_find_and_remove(doubly, c0, &coord_equals, &n);
  coord_print((struct coord *) n->obj);
  puts("");

  print

  ciche_doubly_find_and_remove_and_free(doubly, c0, &coord_equals);

  print

  ciche_doubly_find_and_remove_and_deep_free(doubly, c0, &coord_equals, &coord_free);

  print

  ciche_doubly_clear_and_deep_free(doubly, &coord_free);

  puts("HEY!");
  print

  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_tail(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());
  ciche_doubly_insert_at_head(doubly, coord_create());

  print

  ciche_doubly_clear_deep_free_optimized(doubly, &coord_free);

  puts("HEY!");
  print
    
  return EXIT_SUCCESS;
}
