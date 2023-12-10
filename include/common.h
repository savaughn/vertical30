#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include "raylib.h"

#define RENDER_WIDTH 720
#define RENDER_HEIGHT 720
#define DEVICE_WIDTH 379
#define DEVICE_HEIGHT 379
#define MAX_FPS 60

#define MAX_BULLETS 100
#define MAX_ENEMIES 10

typedef unsigned char uint8;

enum player_action
{
    NONE = -1,
    SHOOT
};

enum enemy_type
{
    BASIC
};

struct enemy
{
    Vector2 position;
    float speed;
    bool active;
    uint8 health;
    bool hit;
    enum enemy_type type;
};

static struct enemy basic_enemy = {
    .position = (Vector2){0, 0},
    .speed = 96.0f,
    .active = false,
    .health = 1,
    .type = BASIC
};

struct player
{
    Vector2 position;
    float speed;
    enum player_action action;
    int score;
    Vector2 velocity;
};

struct bullet
{
    Vector2 position;
    float speed;
    bool active;
    struct player *player;
};

struct opts
{
    bool is_paused;
    bool draw_debug;
    bool show_shader;
    bool show_device_scale;
};

enum screen
{
    PAUSE,
    GAME
};

#endif // COMMON_H
