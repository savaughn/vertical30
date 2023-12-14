#ifndef BULLET_H
#define BULLET_H

#include "common.h"

void draw_bullet(int x, int y, bool draw_debug);
void update_bullet_position(struct bullet *bullet, const float delta_time);

#endif // BULLET_H
