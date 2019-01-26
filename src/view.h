#include "structs.h"
#ifndef FOP_PROJECT_VIEW_H
#define FOP_PROJECT_VIEW_H

void init_window(SDL_Renderer *);
void init_tanks(Map * map);
void init_mine(int mine_index, Map * map);
int handle_events(SDL_Window * window, SDL_Renderer * renderer, Map * map, int arrow_keys[][4]);
void draw_tank(SDL_Renderer * renderer, Tank * tank);
void draw_bullet(SDL_Renderer * renderer, Bullet * bullet,  Map * map);
void draw_walls(SDL_Renderer * renderer, Wall * walls, int number_of_walls);
void draw_mine(SDL_Renderer * renderer, Mine * mine, Map * map);
void quit_window(SDL_Window *, SDL_Renderer *);
int menu(SDL_Window * window, SDL_Renderer * renderer, char call_from, Map * map);
int game_over(SDL_Renderer * renderer, Map * map, int beginning_of_time);


#endif