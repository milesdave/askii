#include <stdlib.h>
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
	init_pair(COLOUR_SCORE_ID, COLOUR_SCORE_FG, COLOUR_SCORE_BG);
	init_pair(COLOUR_WINDOW_ID, COLOUR_SCORE_FG, COLOUR_WINDOW_BG);
}

void end_graphics(void)
{
	endwin();
}

void render_sprite(const sprite_t *s)
{
	if(s->col.len == 1)
		mvprintw(s->y, s->x, "%c", s->ch);			// tree
	else
		mvprintw(s->y, s->x, "%c%1$c", s->ch);		// player

	mvchgat(s->y, s->x, s->col.len, s->col.attr, s->col.pair, NULL);
}

WINDOW* create_win(int w, int h, int x, int y, int c)
{
	WINDOW *win = newwin(h, w, y, x);
	box(win, 0, 0);
	wbkgd(win, COLOR_PAIR(c));
	wrefresh(win);
	return win;
}

void del_win(WINDOW *w)
{
	werase(w);
	wbkgd(w, COLOR_PAIR(0));
	wrefresh(w);
	delwin(w);
}
