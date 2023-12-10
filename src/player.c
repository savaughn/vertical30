#include <math.h>
#include "player.h"

void draw_player(int x, int y, bool draw_debug)
{
    // DrawTriangle((Vector2){x, y - 20}, (Vector2){x - 20, y + 20}, (Vector2){x + 20, y + 20}, LIGHTGRAY);
    DrawTriangleLines((Vector2){x, y - 20}, (Vector2){x - 20, y + 20}, (Vector2){x + 20, y + 20}, LIME);
    if (draw_debug)
    {
        DrawCircleLines(x, y, 12, RED);
    }
}

void update_player_action(struct player *player)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        player->action = SHOOT;
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
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        velocity->y -= acceleration * delta_time;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        velocity->x -= acceleration * delta_time;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        velocity->y += acceleration * delta_time;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        velocity->x += acceleration * delta_time;
    }

    // Deceleration
    if (!IsKeyDown(KEY_W) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT) &&
        !IsKeyDown(KEY_S) && !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT))
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
