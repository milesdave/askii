#include "game.h"
#include "graphics.h"

void setup(void)
{
	init_graphics();

	player.x = 0;
	player.y = 0;
	player.ch = CHAR_PLAYER_DOWN;
	player.dir = DIR_DOWN;
	player.col.pair = COLOUR_PLAYER_ID;
	player.col.len = 2;
	player.col.attr = A_BOLD;
}

void render(void)
{
	render_sprite(&player);
	refresh();
}

void end(void)
{
	end_graphics();
}
