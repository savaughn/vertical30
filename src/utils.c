#include "utils.h"
#include "scan_frag.h"

void init_renderer(RenderTexture2D *target, Shader *shader, float *resize_scale, Camera2D *camera)
{
    load_shaders_and_textures(target, shader, resize_scale);
    *camera = (Camera2D){.offset = {0, 0}, .target = {0, 0}, .rotation = 0.0f, .zoom = 1.0f};
}


void load_shaders_and_textures(RenderTexture2D *target, Shader *shader, float *resize)
{
    *target = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);
    SetTextureFilter(target->texture, TEXTURE_FILTER_ANISOTROPIC_16X);
    
    *shader = LoadShaderFromMemory(NULL, (const char*)scan_frag);
    *resize = 1.3f;
    SetShaderValue(*shader, GetShaderLocation(*shader, "resize"), resize, SHADER_UNIFORM_FLOAT);
    float resf = (float)RENDER_WIDTH;
    SetShaderValue(*shader, GetShaderLocation(*shader, "resolution"), &resf, SHADER_UNIFORM_FLOAT);
}

void handle_opts_input(int *selectedWidth, int *selectedHeight, float *resize, Shader *shader, struct opts *opts, enum screen *current_screen)
{
    if (IsKeyPressed(KEY_ONE))
    {
        opts->is_paused = !opts->is_paused;
        *current_screen = opts->is_paused ? PAUSE : GAME;
    }
    if (IsKeyPressed(KEY_TWO))
    {
        opts->show_shader = !opts->show_shader;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        opts->show_device_scale = !opts->show_device_scale;
        *selectedWidth = opts->show_device_scale ? DEVICE_WIDTH : RENDER_WIDTH;
        *selectedHeight = opts->show_device_scale ? DEVICE_HEIGHT : RENDER_HEIGHT;
        *resize = opts->show_device_scale ? 1.1f : 1.3f;
        SetShaderValue(*shader, GetShaderLocation(*shader, "resize"), resize, SHADER_UNIFORM_FLOAT);
        SetShaderValue(*shader, GetShaderLocation(*shader, "resolution"), selectedHeight, SHADER_UNIFORM_INT);
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        opts->draw_debug = !opts->draw_debug;
    }
}

void check_collisions(struct player *player, struct enemy *enemy, Camera2D *camera)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (player->bullets[i].active)
        {
            if (CheckCollisionCircles(player->bullets[i].position, 12, enemy->position, 24))
            {
                enemy->health--;
                if (enemy->health <= 0)
                {
                    enemy->active = false;
                    player->score += 100;
                }
                player->bullets[i].active = false;
            }
        }
    }
    if (CheckCollisionCircles(player->position, player->hitbox_r, enemy->position, enemy->hitbox_r))
    {
        player->position.y += 10;
    }
}
