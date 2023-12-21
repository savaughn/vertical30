#include "common.h"
#include "pause.h"
#include "utils.h"
#include "game.h"
#ifdef __rgb30__
#include "rgb30_controller.h"
#endif

int main(void)
{
    static RenderTexture2D target;
    static Shader shader;
    static float resize_scale;

    struct opts opts = {.is_paused = false, .draw_debug = false, .show_shader = false, .show_device_scale = false};
    Camera2D camera;
    int selectedWidth = 720;
    int selectedHeight = 720;
    enum screen current_screen = GAME;

    InitWindow(RENDER_WIDTH, RENDER_HEIGHT, "Vertical");
    SetTargetFPS(MAX_FPS);
#ifdef __rgb30__
    SetExitKey(RGB30_BUTTON_MIDDLE_RIGHT);
#endif

    init_renderer(&target, &shader, &resize_scale, &camera);
#ifdef __rgb30__
    bool should_close = false;
    while (!should_close)
#else
    while (!WindowShouldClose())
#endif
    {
#ifdef __rgb30__
        update_button_state();
#else
        handle_opts_input(&selectedWidth, &selectedHeight, &resize_scale, &shader, &opts, &current_screen);
#endif
        switch (current_screen)
        {
        case PAUSE:
            draw_pause_screen(selectedWidth, selectedHeight);
            break;
        case GAME:
        {
            draw_game_screen(&opts, &selectedWidth, &selectedHeight, &target, &shader, &camera);
            break;
        }
        default:
            break;
        }
#ifdef __rgb30__
        if (IsGamepadButtonDown(0, RGB30_BUTTON_MIDDLE_RIGHT) && IsGamepadButtonDown(0, RGB30_BUTTON_MIDDLE_LEFT))
        {
            should_close = true;
        }
        refresh_button_state();
#endif
    }
    UnloadRenderTexture(target);
    UnloadShader(shader);
    CloseWindow();

    return 0;
}
