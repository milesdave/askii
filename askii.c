#define _DEFAULT_SOURCE
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "config.h"
#include "askii.h"
#include "graphics.h"
#include "list.h"
#include "types.h"
#include "util.h"

#define MS_PER_FRAME (1000 / fps)

int main(void)
{
	init_graphics();
	srand(time(NULL));
	updates = 0;
	trees = NULL;

	setup();
	loop();

	list_free(&trees);
	end_graphics();
	return 0;
}

void setup(void)
{
	getmaxyx(stdscr, termh, termw);
	dist = 0;
	fps = SPEED_INIT;
	quit = false;

	player.x = (termw / 2) - 1;
	player.y = termh / 3;
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
		case KEY_PAUSE:
			paused();
			break;
		case _KEY_LEFT:
			set_dir(&player, DIR_LEFT);
			break;
		case _KEY_DOWN:
			set_dir(&player, DIR_DOWN);
			break;
		case _KEY_RIGHT:
			set_dir(&player, DIR_RIGHT);
			break;
		default:
			break;
		}

		update();
		render();

		// make sure delay is not negative - can be after gameover()
		long delay = (start + MS_PER_FRAME - get_time()) * 1000;
		if(delay > 0) usleep(delay);
	}
}

void update(void)
{
	dist++;

	// move/delete existing trees
	for(int i = 0; i < trees_size; i++)
	{
		sprite_t *tree = list_get(&trees, i);

		// delete off screen trees
		if(tree->y < 0)
		{
			list_remove(&trees, i);
			trees_size--;
			continue;
		}

		// move/repaint
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

		updates = 0;
	} else { updates++; }

	// update speed
	if(fps < SPEED_MAX && dist % SPEED_INTERVAL == 0)
		fps += SPEED_INCREASE;

	// check collisions
	for(int i = 0; i < trees_size; i++)
	{
		sprite_t *tree = list_get(&trees, i);
		if((tree->x == player.x || tree->x == (player.x + 1)) && tree->y == player.y)
		{
			gameover();
			if(!quit) setup();
			break;
		}
	}
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

void gameover(void)
{
	// switch back to blocking i/o
	nodelay(stdscr, false);

	player.ch = CHAR_PLAYER_GAMEOVER;
	render();

	// gameover window
	WINDOW *win = create_win(WIN_GAMEOVER_W, WIN_GAMEOVER_H, WIN_GAMEOVER_X, WIN_GAMEOVER_Y, COLOUR_WINDOW_ID);
	win_text(win, TEXT_GAMEOVER_1, 1, ALIGN_CENTRE);
	win_text(win, TEXT_GAMEOVER_2, 2, ALIGN_CENTRE);
	int len = ((int)log10(dist) + 1);
	mvwprintw(win, 3, align_x(win, ALIGN_CENTRE, len), "%dC", dist);
	win_bold(win, 1, strlen(TEXT_GAMEOVER_1), ALIGN_CENTRE);
	win_bold(win, 3, len, ALIGN_CENTRE);
	wrefresh(win);

	// hide score
	for(int i = 0; i < 10; i++)
		mvprintw(0, termw - i, " ");

	// wait for any key or quit
	if(any_key() == KEY_QUIT)
		quit = true;

	del_win(win);

	// return to non-blocking
	nodelay(stdscr, true);
}

void paused(void)
{
	nodelay(stdscr, false);

	WINDOW *win = create_win(WIN_PAUSED_W, WIN_PAUSED_H, WIN_PAUSED_X, WIN_PAUSED_Y, COLOUR_WINDOW_ID);
	win_text(win, TEXT_PAUSED, 1, ALIGN_CENTRE);
	win_bold(win, 1, strlen(TEXT_PAUSED), ALIGN_CENTRE);
	wrefresh(win);

	// wait for pause to be pressed again
	int x = getch();
	while(x != KEY_PAUSE)
		x = getch();

	del_win(win);

	nodelay(stdscr, true);
}
