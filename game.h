#ifndef _GAME_H
#define _GAME_H

#include <ncurses.h>
#include <stdbool.h>
#include "config.h"
#include "types.h"

static bool quit = false;
static sprite_t player;
static sprite_t trees[MAX_TREES];

void setup(void);
void render(void);
void end(void);

#endif
