#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

void draw_enemy(int x, int y, bool hit, bool draw_debug);
void update_enemy_position(Vector2 *pos, const float speed, const float delta_time);

#endif // ENEMY_H
