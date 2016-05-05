#include <stdlib.h>
#include <ncurses.h>
#include "config.h"
#include "graphics.h"

void init_graphics(void)
{
	initscr();
	start_color();
	use_default_colors();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();

	init_pair(COLOUR_PLAYER_ID, COLOUR_PLAYER, -1);
	init_pair(COLOUR_TREE_ID, COLOUR_TREE, -1);
}


void end_graphics(void)
{
	endwin();
}

void render_sprite(sprite_t *s)
{
	if(s->col.len == 1)
		mvprintw(s->y, s->x, "%c", s->ch);			// tree
	else
		mvprintw(s->y, s->x, "%c%1$c", s->ch);		// player

	mvchgat(s->y, s->x, s->col.len, s->col.attr, s->col.pair, NULL);
}
