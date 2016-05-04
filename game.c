#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "game.h"
#include "graphics.h"
#include "util.h"

#define MS_PER_FRAME (1000 / 60)

void setup(void)
{
	init_graphics();

	quit = false;

	player.x = 0;
	player.y = 0;
	player.ch = CHAR_PLAYER_DOWN;
	player.dir = DIR_DOWN;
	player.col.pair = COLOUR_PLAYER_ID;
	player.col.len = 2;
	player.col.attr = A_BOLD;

	// change to non-blocking i/o
	nodelay(stdscr, true);
}

void loop(void)
{
	while(!quit)
	{
		long start = get_time();
		int in = getch();

		switch(in)
		{
		case KEY_QUIT:
			quit = true;
			break;
		case KEY_LEFT:
			set_dir(&player, DIR_LEFT);
			break;
		case KEY_DOWN:
			set_dir(&player, DIR_DOWN);
			break;
		case KEY_RIGHT:
			set_dir(&player, DIR_RIGHT);
			break;
		default:
			break;
		}

		render();
		usleep((start + MS_PER_FRAME - get_time()) * 1000);
	}
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
