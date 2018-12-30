#include "structs.h"
#ifndef FOP_PROJECT_VIEW_H
#define FOP_PROJECT_VIEW_H

void init_window(SDL_Renderer *);
int handle_events(Map * map, int * arrow_keys);
void draw_tank(SDL_Renderer * renderer, Tank * tank);
void draw_bullet(SDL_Renderer * renderer, Bullet * bullet);
void draw_walls(SDL_Renderer * renderer, Wall * walls, int number_of_walls);
void quit_window(SDL_Window *, SDL_Renderer *);

#endif