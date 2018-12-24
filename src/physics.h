#include "structs.h"
#ifndef FOP_PROJECT_PHYSICS_H
#define FOP_PROJECT_PHYSICS_H
bool move_tank(SDL_Keycode key, Tank * tank);
void move_bullet(Bullet * bullet);
int fire(Tank * tank);

#endif