#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"

void init_enemy(struct enemy *enemy);
void draw_enemy(int x, int y, bool hit, bool draw_debug, enum enemy_type type);
void update_enemy_position(struct enemy *enemy, const float delta_time);

#endif // ENEMY_H
