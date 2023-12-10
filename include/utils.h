#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void init_game(struct player *player, struct bullet *bullets, struct enemy *enemies);
void load_shaders_and_textures(RenderTexture2D *target, Shader *shader, Texture2D *background_texture, Texture2D *player_texture, float *resize_scale);
void handle_opts_input(int *selectedWidth, int *selectedHeight, float *resize, Shader *shader, struct opts *opts, enum screen *current_screen);

#endif // UTILS_H
