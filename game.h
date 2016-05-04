#ifndef _GAME_H
#define _GAME_H

#include <stdbool.h>
#include "config.h"
#include "types.h"

bool quit;
sprite_t player;
sprite_t trees[MAX_TREES];

void setup(void);
void loop(void);
void render(void);
void end(void);

#endif
