#ifndef _LIST_H
#define _LIST_H

#include "types.h"

void list_free(node_t**);
void list_loop(node_t**, action);
int list_add(node_t**, sprite_t*);
void list_remove(node_t**, const int);
sprite_t* list_get(node_t**, const int);

#endif
