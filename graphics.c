#include <stdlib.h>
#include <string.h>
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

void win_text(WINDOW *w, const char *t, int y, align_t a)
{
	mvwprintw(w, y, align_x(w, a, strlen(t)), t);
}

void win_bold(WINDOW *w, int y, int l, align_t a)
{
	mvwchgat(w, y, align_x(w, a, l), l, A_BOLD, COLOUR_WINDOW_ID, NULL);
}

int align_x(WINDOW *w, align_t a, int l)
{
	int winw, x;
	getmaxyx(w, winw, winw);

	switch(a)
	{
	case ALIGN_LEFT:
		x = 1;
		break;
	case ALIGN_RIGHT:
		x = (winw / 2) - l;
		break;
	case ALIGN_CENTRE:
		x = (winw / 2) - (l / 2);
		break;
	}

	return x;
}
