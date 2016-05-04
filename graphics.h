#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "types.h"

void init_graphics();
void end_graphics();
void render(const sprite_t*, const colour_spec_t*);

#endif
