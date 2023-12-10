#include "game.h"
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "pause.h"

static Texture2D background_texture;
static Texture2D player_texture;
static Camera2D camera;
static struct player player;
static struct bullet player_bullets[MAX_BULLETS];
static struct enemy enemies[MAX_ENEMIES];
static int player_bullet_count = 0;

static bool is_level_initialized = false;

void unload_game_screen(void)
{
    UnloadTexture(background_texture);
    UnloadTexture(player_texture);
}

void init_renderer(RenderTexture2D *target, Shader *shader, float *resize_scale)
{
    load_shaders_and_textures(target, shader, &background_texture, &player_texture, resize_scale);
    camera = (Camera2D){.offset = {0, 0}, .target = {0, 0}, .rotation = 0.0f, .zoom = 1.0f};
}

void draw_game_screen(struct opts *opts, int *selectedWidth, int *selectedHeight, enum screen *current_screen, RenderTexture2D *target, Shader *shader)
{
    if (!is_level_initialized)
    {
        init_game(&player, player_bullets, enemies);
        is_level_initialized = true;
    }

    // Measure delta time
    float delta_time = GetFrameTime();

    // Update
    update_player_position(&player.position, &player.velocity, delta_time);
    update_player_action(&player);

    if (player.action == SHOOT)
    {
        struct bullet bullet = {
            .position = {player.position.x, player.position.y},
            .speed = 800.0f, // Adjusted bullet speed for smooth movement
            .active = true,
            .player = &player};

        player_bullets[player_bullet_count] = bullet;
        player_bullet_count++;
        player_bullet_count %= MAX_BULLETS;
    }

    // Draw
    BeginDrawing();
    ClearBackground(BLACK);

    BeginTextureMode(*target);
    BeginMode2D(camera);
    ClearBackground(DARKGRAY);

    // Draw Background
    DrawTexture(background_texture, -1, -1, WHITE);

    // Update and draw player bullets
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (player_bullets[i].active)
        {
            update_bullet_position(&player_bullets[i].position, player_bullets[i].speed, delta_time);
            for (int j = 0; j < MAX_ENEMIES; j++)
            {
                if (enemies[j].active)
                {
                    check_bullet_collision(&player_bullets[i], &enemies[j]);
                }
            }
            if (player_bullets[i].position.y < 0)
            {
                player_bullets[i].active = false;
            }
            draw_bullet(player_bullets[i].position.x, player_bullets[i].position.y, opts->draw_debug);
        }
    }

    draw_player(&player_texture, player.position.x, player.position.y, opts->draw_debug);

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        // if active
        if (enemies[i].active)
        {
            update_enemy_position(&enemies[i].position, enemies[i].speed, delta_time);
            if (enemies[i].position.y > 750)
            {
                enemies[i].active = false;
            }
            draw_enemy(enemies[i].position.x, enemies[i].position.y, enemies[i].hit, opts->draw_debug);
            if (CheckCollisionCircles(player.position, 12, enemies[i].position, 24))
            {
                enemies[i].active = false;
                player.position.y += 10;
            }
            if (enemies[i].hit)
                enemies[i].position.y += 3;
        }
        else
        {
            enemies[i].position.y = -1000;
            enemies[i].active = true;
            enemies[i].health = 3;
            enemies[i].hit = false;
            enemies[i].speed = 12.0f * 8;
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
}
