#ifndef _LIST_H
#define _LIST_H

#include "types.h"

node_t* list_init(sprite_t*);
void list_free(node_t*);
void list_loop(node_t*, action);
int list_push(node_t*, sprite_t*);

#endif
