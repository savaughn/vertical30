#include "bullet.h"

void draw_bullet(int x, int y, bool draw_debug)
{
    DrawCircle(x, y, 4, RED);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 5, LIME);
    }
}

void update_bullet_position(struct bullet *bullet, const float delta_time)
{
    bullet->position.y -= bullet->speed * delta_time;
    if (bullet->position.y < 0)
    {
        bullet->active = false;
    }
}
