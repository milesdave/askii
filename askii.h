#ifndef _GAME_H
#define _GAME_H

#include "types.h"

int termw;
int termh;
int dist;
int updates;
int fps;
bool quit;
sprite_t player;
list_head_t *trees;
int trees_size;

void setup(void);
void loop(void);
void update(void);
void render(void);
void gameover(void);

#endif
