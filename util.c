#include <stdlib.h>
#include <sys/time.h>
#include "config.h"
#include "util.h"

long get_time(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (long)(t.tv_sec * 1000 + t.tv_sec / 1000);
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
