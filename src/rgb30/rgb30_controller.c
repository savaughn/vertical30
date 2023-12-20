#include "rgb30_controller.h"

bool is_button_pressed(int button)
{
    return button_state[button] == 1 && prev_button_state[button] == 0;
}

void update_button_state(void)
{
    for (int i = 0; i < RGB30_BUTTON_COUNT; i++)
    {
        if (IsGamepadButtonDown(0, i))
        {
            button_state[i] = 1;
        }
    }
}

void refresh_button_state(void)
{
    for (int i = 0; i < RGB30_BUTTON_COUNT; i++)
    {
        prev_button_state[i] = button_state[i];
        button_state[i] = 0;
    }
}
