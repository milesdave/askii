#include <ncurses.h>

int main(void)
{
	initscr();
	start_color();
	use_default_colors();
	curs_set(0);
	cbreak();
	keypad(stdscr, true);
	noecho();
	refresh();

	mvprintw(5, 5, "Hello world");

	getch();
	endwin();
	return 0;
}
