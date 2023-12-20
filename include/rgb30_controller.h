#ifndef RGB30_CONTROLLER_H
#define RGB30_CONTROLLER_H

#include "common.h"

static int prev_button_state[RGB30_BUTTON_COUNT] = {0};
static int button_state[RGB30_BUTTON_COUNT] = {0};

bool is_button_pressed(int button);
void update_button_state(void);
void refresh_button_state(void);

#endif // RGB30_CONTROLLER_H
