#include <stdlib.h>
#include <ncurses.h>
#include "config.h"
#include "graphics.h"
#include "types.h"

int main(void)
{
	init_graphics();

	colour_spec_t player_c = {COLOUR_PLAYER_ID, 2, A_BOLD};
	colour_spec_t tree_c = {COLOUR_TREE_ID, 1, A_BOLD};

	sprite_t player = {2, 5, CHAR_PLAYER_DOWN, DIR_DOWN};
	sprite_t tree = {5, 7, CHAR_TREE, DIR_DOWN};

	render(&player, &player_c);
	render(&tree, &tree_c);

	refresh();
	getch();

	end_graphics();
	return 0;
}
