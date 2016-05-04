#include <stdlib.h>
#include <ncurses.h>
#include "config.h"
#include "graphics.h"

// ncurses setup
void init_graphics()
{
	initscr();
	start_color();
	use_default_colors();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();

	// colour pairs
	init_pair(COLOUR_PLAYER_ID, COLOUR_PLAYER, -1);
	init_pair(COLOUR_TREE_ID, COLOUR_TREE, -1);
}


// ncurses clean-up
void end_graphics()
{
	endwin();
}

// renders a sprite with the specified colour spec
void render(const sprite_t *s, const colour_spec_t *c)
{
	if(c->len == 1)
		mvprintw(s->y, s->x, "%c", s->c);
	else
		mvprintw(s->y, s->x, "%c%1$c", s->c);

	mvchgat(s->y, s->x, c->len, c->attr, c->pair, NULL);
}
