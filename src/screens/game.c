#include "game.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "pause.h"

#include <stdio.h>

static struct player player = {
    .position = (Vector2){360, 650},
    .speed = 300.0f,
    .action = NONE,
    .score = 0,
    .velocity = (Vector2){0, 0},
    .bullet_count = 0,
    .hitbox_r = 12,
};
static struct enemy enemies[200];
static int enemy_count = 0;
static bool is_level_initialized = false;
static int frame_count = 0;

static struct enemy *level1SpawnScript[MAX_FRAMES_LEVEL1];

void init_game(void)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        player.bullets[i] = (struct bullet){
            .active = false,
            .speed = 800.0f,
            .position = (Vector2){0, 0},
            .hitbox_r = 12};
    }
    for (int i = 0; i < MAX_FRAMES_LEVEL1; i++)
    {
        level1SpawnScript[i] = &(struct enemy){.active = false};
        if (i == 60)
        {
            level1SpawnScript[i] = &(struct enemy){.position = (Vector2){100, -100}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1};
        }
        if (i == 120)
        {
            level1SpawnScript[i] = &(struct enemy){.position = (Vector2){200, -200}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1};
        }
        if (i == 180)
        {
            level1SpawnScript[i] = &(struct enemy){.position = (Vector2){300, -300}, .type = BASIC, .speed = 96.0f, .active = true, .health = 1};
        }
    }
}

void draw_game_screen(const struct opts *opts, const int *selectedWidth, const int *selectedHeight, const RenderTexture2D *target, const Shader *shader, const Camera2D *camera)
{
    if (!is_level_initialized)
    {
        init_game();
        is_level_initialized = true;
    }

    // Measure delta time
    float delta_time = GetFrameTime();

    // Update
    update_player_position(&player.position, &player.velocity, delta_time);
    update_player_action(&player);

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    BeginTextureMode(*target);
    BeginMode2D(*camera);
    ClearBackground(BLACK);

    int active_bullet_count = 0;
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (player.bullets[i].active)
        {
            update_bullet_position(&player.bullets[i], delta_time);
            draw_bullet(player.bullets[i].position.x, player.bullets[i].position.y, opts->draw_debug);
            active_bullet_count++;
        }
    }

    draw_player(player.position.x, player.position.y, opts->draw_debug);

    for (int i = 0; i < enemy_count; i++)
    {
        // if active
        if (enemies[i].active)
        {
            update_enemy_position(&enemies[i], delta_time);
            if (enemies[i].position.y > 750)
            {
                enemies[i].active = false;
            }
            draw_enemy(enemies[i].position.x, enemies[i].position.y, enemies[i].hit, opts->draw_debug, enemies[i].type);
            check_collisions(&player, &enemies[i], camera);
        }

        enemies[i].hit = false;
    }

    static int display_score = 0;
    if (display_score <= player.score)
    {
        display_score += 4;
        if (display_score > player.score)
        {
            display_score = player.score;
        }
    }
    EndMode2D();

    // draw score top left
    DrawText(TextFormat("%i", display_score), 20, 20, 50, RAYWHITE);

    EndTextureMode();

    if (opts->show_shader)
    {
        BeginShaderMode(*shader);
    }
    DrawTexturePro(target->texture,
                   (Rectangle){0.0f, 0.0f, (float)target->texture.width, (float)-target->texture.height},
                   (Rectangle){RENDER_WIDTH / 2 - *selectedWidth / 2, RENDER_HEIGHT / 2 - *selectedHeight / 2, (float)*selectedWidth, (float)*selectedHeight},
                   (Vector2){0.0f, 0.0f},
                   0.0f,
                   WHITE);
    if (opts->show_shader)
    {
        EndShaderMode();
    }

    EndDrawing();

    if (frame_count < MAX_FRAMES_LEVEL1)
    {
        struct enemy *enemy_spawn = level1SpawnScript[frame_count];
        if (enemy_spawn->active)
        {
            enemies[enemy_count] = *enemy_spawn;
            enemies[enemy_count].active = true;
            enemy_count++;
        }
        frame_count++;
        // frame_count %= MAX_FRAMES_LEVEL1;
    }
}
