#include "bullet.h"

void draw_bullet(int x, int y, bool draw_debug)
{
    DrawCircle(x, y, 4, RED);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 5, LIME);
    }
}

void update_bullet_position(Vector2 *pos, const float speed, const float delta_time)
{
    pos->y -= speed * delta_time;
}

void check_bullet_collision(struct bullet *bullet, struct enemy *enemy)
{
    if (CheckCollisionCircles(bullet->position, 5, enemy->position, 24))
    {
        if (enemy->health > 0)
        {
            enemy->health--;
        }
        if (enemy->health == 0)
        {
            enemy->active = false;
            bullet->player->score += 100;
        }
        enemy->hit = true;
        enemy->position.y -= 5;
        enemy->speed *= 0.9;
        bullet->active = false;
    }
}
