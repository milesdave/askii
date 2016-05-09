#define _DEFAULT_SOURCE
#include <fcntl.h>
#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <unistd.h>
#include "config.h"
#include "util.h"

long get_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (long)((t.tv_sec * 1000) + (t.tv_sec / 1000));
}

void set_dir(sprite_t *s, const dir_t d)
{
	switch(s->dir)
	{
	// currently left
	case DIR_LEFT:
		// change to down
		if(d == DIR_DOWN || d == DIR_RIGHT)
		{
			s->dir = DIR_DOWN;
			s->ch = CHAR_PLAYER_DOWN;
		}
		break;
	// currently down
	case DIR_DOWN:
		// change to left
		if(d == DIR_LEFT)
		{
			s->dir = DIR_LEFT;
			s->ch = CHAR_PLAYER_LEFT;
		}
		// change to right
		else if(d == DIR_RIGHT)
		{
			s->dir = DIR_RIGHT;
			s->ch = CHAR_PLAYER_RIGHT;
		}
		break;
	// currently right
	case DIR_RIGHT:
		// change to down
		if(d == DIR_DOWN || d == DIR_LEFT)
		{
			s->dir = DIR_DOWN;
			s->ch = CHAR_PLAYER_DOWN;
		}
		break;
	}
}

int any_key(void)
{
	int x = getch();

	// any key besides arrows - could accidently skip gameover
	while(x == _KEY_LEFT || x == _KEY_DOWN || x == _KEY_RIGHT)
		x = getch();

	return x;
}

int map_score(int **m)
{
	// open file descriptor
	int fd, *score;
	if((fd = open(FILE_SCORE, O_RDWR | O_CREAT, 0644)) < 0)
		return -1;

	// set file size (need if file is empty)
	if(ftruncate(fd, sizeof(*score)) != 0)
		return -1;

	// get pointer to mapped file
	*m = mmap(0, sizeof(**m), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(*m == MAP_FAILED)
		return -1;

	return fd;
}

void close_score(int f, int *m)
{
	if(f < 0) return;
	munmap(m, sizeof(*m));
	close(f);
}

int intlen(int x)
{
	return x == 0 ? 1 : (int)(log10(abs(x)) + 1);
}
