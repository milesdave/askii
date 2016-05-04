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
	int x;
	int y;
	char c;
	dir_t d;
} sprite_t;

typedef struct
{
	int pair;
	int len;
	int attr;
} colour_spec_t;

#endif
