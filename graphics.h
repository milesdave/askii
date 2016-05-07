#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include <ncurses.h>
#include "types.h"

void init_graphics(void);
void end_graphics(void);
void render_sprite(const sprite_t*);
WINDOW* create_win(int, int, int, int, int);
void del_win(WINDOW*);

#endif
