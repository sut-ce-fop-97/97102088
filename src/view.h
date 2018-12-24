#include "structs.h"
#ifndef FOP_PROJECT_VIEW_H
#define FOP_PROJECT_VIEW_H

void init_window(SDL_Renderer *);
int handle_events(SDL_Renderer * renderer, Map * map);
void draw_tank(SDL_Renderer * renderer, Tank * tank);
void draw_bullet(SDL_Renderer * renderer, Bullet * bullet);
bool quit_window(SDL_Window *, SDL_Renderer *);

#endif