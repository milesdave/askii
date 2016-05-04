#include <ncurses.h>
#include "game.h"

int main(void)
{
	setup();

	render();

	getch();
	end();
	return 0;
}
