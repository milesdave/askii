#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "graphics.h"
#include "list.h"
#include "util.h"

#define MS_PER_FRAME (1000 / 60)

void setup(void)
{
	init_graphics();

	getmaxyx(stdscr, termh, termw);
	updates = distance = 0;
	quit = false;

	player.x = termw / 2;
	player.y = termh / 3;
	player.ch = CHAR_PLAYER_DOWN;
	player.dir = DIR_DOWN;
	player.col.pair = COLOUR_PLAYER_ID;
	player.col.len = 2;
	player.col.attr = A_BOLD;

	// TODO tmp?
	sprite_t tree = {termw / 2, termh, CHAR_TREE, DIR_DOWN, {COLOUR_TREE_ID, 1, A_BOLD}};
	trees = list_init(&tree);

	srand(time(NULL));

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

		update();
		render();
		usleep((start + MS_PER_FRAME - get_time()) * 1000);
	}
}

void update(void)
{
	distance++;

	/* TODO move/delete existing trees
	for(int i = 0; i < num_trees; i++)
	{
		mvaddch(trees[i].y, trees[i].x, ' ');

		if(player.dir == DIR_LEFT)
			trees[i].x++;
		else if(player.dir == DIR_RIGHT)
			trees[i].x--;

		trees[i].y--;

		if(trees[i].y < 0)
			num_trees--;
	}*/

	/* TODO spawn trees
	if(updates == SPAWN_INTERVAL)
	{
		int min, max, x;
		double _rand;

		min = -(termw / 2);
		max = termw + (termw / 2);
		_rand = (double)rand() / RAND_MAX;
		x = (max - min + 1) * _rand + min;

		trees[num_trees].x = x;
		trees[num_trees].y = termh;
		trees[num_trees].ch = CHAR_TREE;
		trees[num_trees].dir = DIR_DOWN;
		trees[num_trees].col.pair = COLOUR_TREE_ID;
		trees[num_trees].col.len = 1;
		trees[num_trees].col.attr = A_BOLD;

		num_trees++;
		updates = 0;
	}
	else { updates++; }*/

	// TODO update speed
	// TODO check collisions
}

void render(void)
{
	list_loop(trees, render_sprite);
	render_sprite(&player);
	// TODO render score
	refresh();
}

void end(void)
{
	list_free(trees);
	end_graphics();
}
