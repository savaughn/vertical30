#ifndef BULLET_H
#define BULLET_H

#include "common.h"

void draw_bullet(int x, int y, bool draw_debug);
void update_bullet_position(Vector2 *pos, const float speed, const float delta_time);
void check_bullet_collision(struct bullet *bullet, struct enemy *enemy);

#endif // BULLET_H
