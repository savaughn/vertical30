#ifndef GAME_H
#define GAME_H

#include "common.h"

void init_game(void);
void draw_game_screen(const struct opts *opts, const int *selectedWidth, const int *selectedHeight, const RenderTexture2D *target, const Shader *shader, const Camera2D *camera);

#endif // GAME_H
