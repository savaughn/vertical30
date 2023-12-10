#ifndef GAME_H
#define GAME_H

#include "common.h"

void init_renderer(RenderTexture2D *target, Shader *shader, float *resize_scale);
void draw_game_screen(struct opts *opts, int *selectedWidth, int *selectedHeight, enum screen *current_screen, RenderTexture2D *target, Shader *shader);

#endif // GAME_H
