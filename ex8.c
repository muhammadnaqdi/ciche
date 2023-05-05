/*
@author Muhammad Naqdi
*/

#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>

#include "ciche_ds.h"

struct scanner {
  const char *input;
  size_t head;
};

struct production_rule {
  struct ciche_doubly *rules;
  char tag;
};

struct stack_obj {
  struct production_rule *prule;
  struct ciche_doubly_node *current_rule;
  size_t symbol_index;
  size_t start_head;
};

struct scanner *scanner_create(const char *input) {
  struct scanner *scanner = (struct scanner *) malloc(sizeof(scanner));

  scanner->input = input;
  scanner->head = 0;
  
  return scanner;
}

char scanner_token(struct scanner *scanner) {
  char token = scanner->input[scanner->head];

  scanner->head ++;

  return token;
}

struct production_rule *production_rule_create(char tag, size_t n, ...) {
  struct production_rule *prule = (struct production_rule *) malloc(sizeof(struct production_rule));

  prule->tag = tag;
  
  va_list ptr;
  va_start(ptr, n);

  prule->rules = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly));
  ciche_doubly_init(prule->rules);

  for (int i = 0; i < n; ++i) {
    ciche_doubly_insert_at_tail(prule->rules, (void *) va_arg(ptr, const char *));
  }
  
  va_end(ptr);

  return prule;
}

struct stack_obj *stack_obj_create(struct production_rule *pr, struct scanner *sc) {
  struct stack_obj *obj = (struct stack_obj *) malloc(sizeof(struct stack_obj));

  obj->prule = pr;
  obj->start_head = sc->head;
  ciche_doubly_pick_head(pr->rules, &obj->current_rule);
  obj->symbol_index = -1;
    
  return obj;
}

bool stack_obj_free(void *obj) {
  struct stack_obj *sobj = (struct stack_obj *) obj;

  free(sobj);
  
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2)
  return EXIT_FAILURE;

  const size_t PRULES_SIZE = 91;
  struct production_rule *prules[PRULES_SIZE];
  prules['S'] = production_rule_create('S', 2, "Ede", "Fpb");
  prules['E'] = production_rule_create('E', 2, "aX", "Cd");
  prules['C'] = production_rule_create('C', 2, "awz", "Fb");
  prules['X'] = production_rule_create('X', 2, "wz", "wp");
  prules['F'] = production_rule_create('F', 1, "aw");

  struct scanner *scan = scanner_create(argv[1]);

  struct ciche_doubly *stack = (struct ciche_doubly *) malloc(sizeof(struct ciche_doubly)); 
  ciche_doubly_init(stack);
  ciche_doubly_insert_at_tail(stack, stack_obj_create(prules['S'], scan));

  struct stack_obj *sobj;
  struct production_rule *prule;
  char *string;
  char symbol;
  bool backtrack = false;

#define PRINTREST(action)					                        	\
  printf("ACTION:  %s\n", action);			                        		\
  printf("STACK:  |%c|%d|%d|\n", prule->tag, (int) sobj->symbol_index, (int) sobj->start_head); \
  
  while (stack->size > 0) {
    puts("------------------------------------------");
    ciche_doubly_pick_tail_obj(stack, (void **) &sobj);
    prule = sobj->prule;
    if (backtrack) {
      if (sobj->current_rule->next != NULL) {
	sobj->symbol_index = -1;
	scan->head = sobj->start_head;
	sobj->current_rule = sobj->current_rule->next;
	backtrack = false;
      } else {
	ciche_doubly_remove_and_free_tail(stack, &stack_obj_free);
	continue;
      }
    }
    sobj->symbol_index ++;
    symbol = ((char *)sobj->current_rule->obj)[sobj->symbol_index];

    printf("PRODUCTION RULE:  %c\nCURRENT SYMBOL:  %c\n", prule->tag, symbol == '\0' ? '-' : symbol);
    
    if (symbol == '\0') {
      PRINTREST("POP")
      ciche_doubly_remove_and_free_tail(stack, &stack_obj_free);
      continue;
    } else {
      if (symbol > 90) {
	if (symbol == scanner_token(scan)) {
	  PRINTREST("ADVANCE")
	  continue;
	} else {
	  if (sobj->current_rule->next != NULL) {
	    PRINTREST("BACKTRACK")
	    sobj->symbol_index = -1;
	    scan->head = sobj->start_head;
	    sobj->current_rule = sobj->current_rule->next;
	    continue;
	  } else {
	    PRINTREST("BACKTRACK & POP")
	    ciche_doubly_remove_and_free_tail(stack, &stack_obj_free);
	    backtrack = true;
	    continue;
	  }
	}
      } else {
	PRINTREST("PUSH")
	ciche_doubly_insert_at_tail(stack, (void *) stack_obj_create(prules[symbol], scan));
	continue;
      }
    }
  }

  puts(scan->input[scan->head] == '\0' ? "SUCCESS" : "FAILURE");
  
  return EXIT_SUCCESS;
}
