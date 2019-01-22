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

//const int number_of_primary_bullets = 8;
//const int Primary_Lifetime = 30 * 6; // Product of FPS multiplying seconds of lifetime, respectively
//const int bullet_radius = 4;
const double step = 4.0, bullet_speed = 6.0;
const double pi = 3.14159265;
const double rotation_rate = 3.0;
void move_tank(char key, Tank * tank){
    switch (key) {
        case 'U':
            if (tank->angle == 270.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= step;
            else {
                tank->x += (int) step * cos((tank->angle) / 180.0*pi);
                tank->y += (int) step * sin((tank->angle) / 180.0*pi);
            }
            break;
        case 'D':
            if (tank->angle == 90.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= step;
            else if (tank->angle == 180.0)
                tank->x += step; //An exceptional case because of a bug in trigonometric calculations of SDL functions
            else {
                tank->x -= (int) step * cos((tank->angle) / 180.0*pi);
                tank->y -= (int) step * sin((tank->angle) / 180.0*pi);
            }
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

void move_bullet(Bullet * bullet, Map * map){
    bullet->x += (int) bullet_speed * cos((bullet->angle) /180.0*pi);
    bullet->y += (int) bullet_speed * sin((bullet->angle) /180.0*pi);
    bullet->lifetime -= 1;
}

int fire(Tank * tank) {
    if (tank->remaining_bullets > 0) {
        tank->bullets [Primary_Bullets - tank->remaining_bullets].lifetime = Primary_Lifetime;
        tank->bullets [Primary_Bullets - tank->remaining_bullets].x = tank->x + (bullet_radius + tank->radius + 1) * cos((tank->angle) / 180.0*pi);
        tank->bullets [Primary_Bullets - tank->remaining_bullets].y = tank->y + (bullet_radius + tank->radius + 1) * sin((tank->angle) / 180.0*pi);
        tank->bullets [Primary_Bullets - tank->remaining_bullets].angle = tank->angle;
        tank->bullets [Primary_Bullets - tank->remaining_bullets].radius = bullet_radius;
        tank->remaining_bullets -= 1;
        return 1;
    }
    return 0;
}