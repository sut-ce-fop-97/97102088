#include "structs.h"
#ifndef FOP_PROJECT_PHYSICS_H
#define FOP_PROJECT_PHYSICS_H

void move_tank(char key, Tank * tank);
void turn_tank(char key, Tank * tank);
void move_bullet(Bullet * bullet);
int fire(Tank * tank);

#endif