#ifndef UTILS_H
#define UTILS_H

#include "common.h"

void init_renderer(RenderTexture2D *target, Shader *shader, float *resize_scale, Camera2D *camera);
void load_shaders_and_textures(RenderTexture2D *target, Shader *shader, float *resize_scale);
void handle_opts_input(int *selectedWidth, int *selectedHeight, float *resize, Shader *shader, struct opts *opts, enum screen *current_screen);
void check_collisions(struct player *player, struct enemy *enemy, Camera2D *camera);

#endif // UTILS_H
