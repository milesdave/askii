#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>
#include "config.h"
#include "types.h"

int termw, termh;
int dist, updates, fps;
bool quit;
sprite_t player;
list_head_t *trees;
int trees_size;

void setup(void);
void loop(void);
void update(void);
void render(void);
void end(void);

#endif
