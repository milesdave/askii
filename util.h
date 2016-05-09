#ifndef _UTIL_H
#define _UTIL_H

#include "types.h"

long get_time(void);
void set_dir(sprite_t*, const dir_t);
int any_key(void);
int map_score(int**);
void close_score(int, int*);
int intlen(int);

#endif
