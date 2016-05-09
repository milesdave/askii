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

int score_fd;
int *score;

void setup(void);
void loop(void);
void update(void);
void render(void);
void gameover(void);
void paused(void);

#endif
