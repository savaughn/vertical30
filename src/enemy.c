#include "enemy.h"

void draw_enemy(int x, int y, bool hit, bool draw_debug)
{
    DrawRectangle(x - 20, y - 20, 40, 40, hit ? RED : BLUE);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 24, LIME);
    }
}

void update_enemy_position(Vector2 *pos, const float speed, const float delta_time)
{
    pos->y += speed * delta_time;
}
