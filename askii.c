#include <ncurses.h>
#include "game.h"

int main(void)
{
	setup();
	loop();
	end();
	return 0;
}
