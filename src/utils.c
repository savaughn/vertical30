#include "utils.h"
#include "scan_frag.h"
#include <stdio.h>

void init_game(struct player *player, struct bullet *bullets, struct enemy *enemies)
{
    player->position = (Vector2){360, 650};
    player->speed = 300.0f; // Adjusted speed for smooth movement
    player->action = NONE;
    player->score = 0;
    player->velocity = (Vector2){0, 0};

    // bullet array
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i] = (struct bullet){.active = false}; // initialize all bullets to inactive
    }

    // enemy array
    const uint8 pixel_width = 8;
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        enemies[i] = (struct enemy){.position = {(12 + pixel_width*i) * pixel_width, -GetRandomValue(0,400) * pixel_width}, .speed = 12.0f * pixel_width, .active = true, .health = 3};
    }
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
        printf("Paused %s\n", opts->is_paused ? "true" : "false");    }
        *current_screen = opts->is_paused ? PAUSE : GAME;
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
