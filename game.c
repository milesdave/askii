#define _DEFAULT_SOURCE
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "game.h"
#include "graphics.h"
#include "list.h"
#include "util.h"

#define MS_PER_FRAME (1000 / fps)

void setup(void)
{
	init_graphics();

	getmaxyx(stdscr, termh, termw);
	updates = dist = 0;
	fps = SPEED_INIT;
	quit = false;
	trees = NULL;

	player.x = termw / 2;
	player.y = termh / 3;
	player.ch = CHAR_PLAYER_DOWN;
	player.dir = DIR_DOWN;
	player.col.pair = COLOUR_PLAYER_ID;
	player.col.len = 2;
	player.col.attr = A_BOLD;

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
	dist++;

	// move/delete existing trees
	for(int i = 0; i < trees_size; i++)
	{
		sprite_t *tree = list_get(&trees, i);

		/* TODO delete
		if(tree->y < 0)
		{
			list_remove(trees, i);
			trees_size--;
		}*/

		// repaint/move
		mvprintw(tree->y, tree->x, " ");
		if(player.dir == DIR_LEFT)
			tree->x++;
		else if(player.dir == DIR_RIGHT)
			tree->x--;
		tree->y--;
	}

	// spawn trees
	if(updates == SPAWN_INTERVAL)
	{
		int min, max, x;
		double _rand;

		min = -(termw / 2);
		max = termw + (termw / 2);
		_rand = (double)rand() / RAND_MAX;
		x = (max - min + 1) * _rand + min;

		sprite_t tree = {x, termh, CHAR_TREE, DIR_DOWN, {COLOUR_TREE_ID, 1, A_BOLD}};
		trees_size = list_add(&trees, &tree);

		mvprintw(0, 0, "Trees: %d", trees_size);

		updates = 0;
	} else { updates++; }

	// update speed
	if(fps < SPEED_MAX && dist % SPEED_UPDATE == 0)
		fps += SPEED_INCREASE;

	// TODO check collisions
}

void render(void)
{
	list_loop(&trees, render_sprite);
	render_sprite(&player);

	// render score
	int len = (dist == 0 ? 1 : (int)(log10(dist) + 1));
	mvprintw(0, termw - 11, "%10dC", dist);
	mvchgat(0, termw - (len + 1), 10, A_BOLD, COLOUR_SCORE_ID, NULL);
	mvchgat(0, termw - 1, 1, A_NORMAL, COLOUR_SCORE_ID, NULL);

	refresh();
}

void end(void)
{
	list_free(&trees);
	end_graphics();
}
