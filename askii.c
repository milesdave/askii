#include <ncurses.h>
#include "config.h"
#include "graphics.h"
#include "types.h"

int main(void)
{
	init_graphics();
	mvprintw(2, 5, "Hello world");
	refresh();
	getch();
	end_graphics();

	return 0;
}
