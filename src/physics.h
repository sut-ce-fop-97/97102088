#include "structs.h"
#ifndef FOP_PROJECT_PHYSICS_H
#define FOP_PROJECT_PHYSICS_H

void locate_tanks(Map * map);
void move_tank(char key, Tank * tank, Map * map);
void turn_tank(char key, Tank * tank);
void move_bullet(Bullet * bullet, Map * map);
void locate_mine(Mine * mine, Map * map);
void pick_mine(Tank * tank, Map * map);
void plant_mine(Tank * tank, Map * map);
void explode_mine(Mine * mine, Map *map);
int fire(Tank * tank);

#endif