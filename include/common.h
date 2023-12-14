#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"

#define RENDER_WIDTH 720
#define RENDER_HEIGHT 720
#define DEVICE_WIDTH 379
#define DEVICE_HEIGHT 379
#define MAX_FPS 60

#define MAX_BULLETS 10
#define MAX_ENEMIES 10

#define MAX_FRAMES_LEVEL1 200

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
    u_int8_t health;
    bool hit;
    enum enemy_type type;
    u_int8_t hitbox_r;
};

static struct enemy basic_enemy = {
    .position = (Vector2){0, 0},
    .speed = 96.0f,
    .active = false,
    .health = 1,
    .type = BASIC,
    .hitbox_r = 24,
};

struct bullet
{
    Vector2 position;
    float speed;
    bool active;
    int hitbox_r;
};

struct player
{
    Vector2 position;
    float speed;
    enum player_action action;
    int score;
    Vector2 velocity;
    int bullet_count;
    struct bullet bullets[MAX_BULLETS];
    u_int8_t hitbox_r;
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

struct enemy_spawn_info
{
    Vector2 spawn_position;
    enum enemy_type type;
};

static struct enemy *level1SpawnScript[MAX_FRAMES_LEVEL1] = {
    [0 ... 199] = &(struct enemy){.active = false},
    [60] = &(struct enemy){.position = (Vector2){100, -100}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1},
    [120] = &(struct enemy){.position = (Vector2){200, -200}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1},
    [180] = &(struct enemy){.position = (Vector2){300, -300}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1},
};

static struct bullet common_bullet = {
    .position = (Vector2){0, 0},
    .speed = 800.0f,
    .active = false,
    .hitbox_r = 12,
};

#endif // COMMON_H
