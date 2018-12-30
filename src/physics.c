#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"
#include "logic.h"
#include "structs.h"

//const int YES_SHOT = 1;
//const int NO_SHOT = -1;
//const int bullet_lifetime = 10000;

//FPS = 30;
//number_of_seconds = 30;
const int Primary_Lifetime = 30 * 2;
const double step = 4.0, bullet_speed = 6.0;
const double pi = 3.14159265;
const double rotation_rate = 4.0;
void move_tank(char key, Tank * tank){
    switch (key) {
        case 'U':
            if (tank->angle == 270.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= step;
            else {
                tank->x += step * cos((tank->angle) / 180.0*pi);
                tank->y += step * sin((tank->angle) / 180.0*pi);
            }
            //printf("\n cos: %f sin: %f\n", cos((tank->angle) * pi/180.0), sin((tank->angle) * pi/180.0) );
            break;
        case 'D':
            if (tank->angle == 90.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= step;
            else if (tank->angle == 180.0)
                tank->x += step; //An exceptional case because of a bug in trigonometric calculations of SDL functions
            else {
                tank->x -= step * cos((tank->angle) / 180.0*pi);
                tank->y -= step * sin((tank->angle) / 180.0*pi);
            }
            //printf("\n cos: %f sin: %f\n", cos((tank->angle) * pi/180.0), sin((tank->angle) * pi/180.0) );
    }
}

void turn_tank(char key, Tank * tank){
    double decimal_part;
    switch (key) {
        case 'R':
            tank->angle += rotation_rate;
            decimal_part = tank->angle - (int)tank->angle;
            tank->angle = correct_mod((int)tank->angle, 360) + decimal_part;
            break;
        case 'L':
            tank->angle -= rotation_rate;
            decimal_part = tank->angle - (int)tank->angle;
            tank->angle = correct_mod((int)tank->angle, 360) + decimal_part;
    }
}

void move_bullet(Bullet * bullet){
    bullet->x += bullet_speed * cos((bullet->angle) * pi/180.0);
    bullet->y += bullet_speed * sin((bullet->angle) * pi/180.0);
    bullet->lifetime -= 1;
}

int fire(Tank * tank) {
    if (tank->remaining_bullets > 0) {
        tank->bullets [5 - tank->remaining_bullets].lifetime = Primary_Lifetime;
        tank->bullets [5 - tank->remaining_bullets].x = tank->x;
        tank->bullets [5 - tank->remaining_bullets].y = tank->y;
        tank->bullets [5 - tank->remaining_bullets].angle = tank->angle;
        tank->remaining_bullets -= 1;
        return 1;
    }
    return 0;
}