#include "enemy.h"

void init_enemy(struct enemy *enemy)
{
    *enemy = basic_enemy;
    enemy->position = (Vector2){20+GetRandomValue(20, 680), -GetRandomValue(80,3000)};
    enemy->active = true;
}

void draw_basic_enemy(int x, int y, bool hit, bool draw_debug)
{
    DrawRectangle(x - 20, y - 20, 40, 40, BLACK);
    DrawRectangleLines(x - 20, y - 20, 40, 40, hit ? RED : BLUE);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 24, LIME);
    }
}

void draw_enemy(int x, int y, bool hit, bool draw_debug, enum enemy_type type)
{
    switch (type)
    {
    case BASIC:
        draw_basic_enemy(x, y, hit, draw_debug);
        break;
    default:
        break;
    }
}

void update_enemy_position(struct enemy *enemy, const float delta_time)
{
    enemy->position.y += enemy->speed * delta_time;
    if (enemy->hit)
    {
        enemy->position.y += 3;
    }
}
