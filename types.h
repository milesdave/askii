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

typedef struct node_t node_t;
typedef struct node_t list_head_t;
struct node_t
{
	sprite_t data;
	node_t *next;
};

typedef void (*action)(const sprite_t*);

#endif
