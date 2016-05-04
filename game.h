#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>
#include "config.h"
#include "types.h"

int termw, termh;
int updates, distance;
bool quit;
sprite_t player;
sprite_t trees[MAX_TREES];	// TODO going to need a list
int num_trees;

void setup(void);
void loop(void);
void update(void);
void render(void);
void end(void);

#endif
