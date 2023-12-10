#include "common.h"
#include "pause.h"
#include "utils.h"
#include "game.h"

int main(void)
{
    static RenderTexture2D target;
    static Shader shader;
    struct opts opts = {.is_paused = false, .draw_debug = false, .show_shader = true, .show_device_scale = false};
    static float resize_scale;

    int selectedWidth = 720;
    int selectedHeight = 720;
    enum screen current_screen = GAME;

    InitWindow(RENDER_WIDTH, RENDER_HEIGHT, "Vertical");
    SetTargetFPS(MAX_FPS);

    init_renderer(&target, &shader, &resize_scale);

    while (!WindowShouldClose())
    {
        handle_opts_input(&selectedWidth, &selectedHeight, &resize_scale, &shader, &opts, &current_screen);

        switch (current_screen)
        {
        case PAUSE:
            draw_pause_screen(selectedWidth, selectedHeight);
            break;
        case GAME:
        {
            draw_game_screen(&opts, &selectedWidth, &selectedHeight, &current_screen, &target, &shader);
            break;
        }
        default:
            break;
        }
    }
    UnloadRenderTexture(target);
    UnloadShader(shader);
    CloseWindow();

    return 0;
}
