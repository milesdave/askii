#include <ncurses.h>
#include "graphics.h"

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
}

void end_graphics()
{
	endwin();
}
