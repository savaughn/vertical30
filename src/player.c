#include <math.h>
#include "player.h"

void draw_player(int x, int y, bool draw_debug)
{
    // DrawTriangle((Vector2){x, y - 20}, (Vector2){x - 20, y + 20}, (Vector2){x + 20, y + 20}, LIGHTGRAY);
    DrawTriangle((Vector2){x, y - 20}, (Vector2){x - 20, y + 20}, (Vector2){x + 20, y + 20}, BLACK);
    DrawTriangleLines((Vector2){x, y - 20}, (Vector2){x - 20, y + 20}, (Vector2){x + 20, y + 20}, LIME);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 12, RED);
    }
}

void update_player_action(struct player *player)
{
#ifdef __rgb30__
    if (is_button_pressed(RGB30_BUTTON_RIGHT_FACE_RIGHT))
#else
    if (IsKeyPressed(KEY_SPACE))
#endif
    {
        if (player->bullet_count >= MAX_BULLETS)
        {
            return;
        }
        player->bullets[player->bullet_count] = (struct bullet){
            .position = (Vector2){player->position.x, player->position.y},
            .active = true,
            .speed = common_bullet.speed,
            .hitbox_r = common_bullet.hitbox_r};
        player->bullet_count++;
        player->bullet_count %= MAX_BULLETS;
    }
    else
    {
        player->action = NONE;
    }
}

const float acceleration = 3000.0f;
const float deceleration = 0.9f; // Higher deceleration for quicker stops
const float max_speed = 400.0f;

void update_player_position(Vector2 *pos, Vector2 *velocity, const float delta_time)
{
    // Handle acceleration
#ifdef __rgb30__
    if (IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_UP))
#else
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
#endif
    {
        velocity->y -= acceleration * delta_time;
    }
#ifdef __rgb30__
    if (IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_LEFT))
#else
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
#endif
    {
        velocity->x -= acceleration * delta_time;
    }
#ifdef __rgb30__
    if (IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_DOWN))
#else
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
#endif
    {
        velocity->y += acceleration * delta_time;
    }
#ifdef __rgb30__
    if (IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_RIGHT))
#else
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
#endif
    {
        velocity->x += acceleration * delta_time;
    }

    // Deceleration
#ifdef __rgb30__
    if (!IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_UP) && !IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_LEFT) &&
        !IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_DOWN) && !IsGamepadButtonDown(0, RGB30_BUTTON_LEFT_FACE_RIGHT))
#else
    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT) &&
        !IsKeyDown(KEY_S) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT))
#endif
    {
        // If no keys are pressed, apply deceleration
        velocity->x *= deceleration;
        velocity->y *= deceleration;
    }

    // Update position based on velocity
    pos->x += (int)(velocity->x * delta_time);
    pos->y += (int)(velocity->y * delta_time);

    // Limit speed
    float speed = sqrt(velocity->x * velocity->x + velocity->y * velocity->y);
    if (speed > max_speed)
    {
        velocity->x = (velocity->x / speed) * max_speed;
        velocity->y = (velocity->y / speed) * max_speed;
    }

    // Bound player to screen
    if (pos->x < 0)
    {
        pos->x = 0;
        velocity->x = 0; // Stop when hitting the screen boundary
    }
    else if (pos->x > 720)
    {
        pos->x = 720;
        velocity->x = 0; // Stop when hitting the screen boundary
    }
    if (pos->y < 0)
    {
        pos->y = 0;
        velocity->y = 0; // Stop when hitting the screen boundary
    }
    else if (pos->y > 720)
    {
        pos->y = 720;
        velocity->y = 0; // Stop when hitting the screen boundary
    }
}
