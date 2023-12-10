#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

void draw_player(Texture2D *texture, int x, int y, bool draw_debug);
void update_player_action(struct player *player);
void update_player_position(Vector2 *pos, Vector2 *velocity, const float delta_time);

#endif // PLAYER_H
