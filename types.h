#ifndef _TYPES_H
#define _TYPES_H

typedef enum
{
	DIR_LEFT,
	DIR_DOWN,
	DIR_RIGHT
} dir_t;

typedef struct
{
	int pair;
	int len;
	int attr;
} colour_t;

typedef struct
{
	int x;
	int y;
	char ch;
	dir_t dir;
	colour_t col;
} sprite_t;

#endif
