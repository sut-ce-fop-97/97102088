#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "structs.h"
#include "physics.h"

//const int YES_SHOT = 1;
//const int NO_SHOT = -1;
//const int bullet_lifetime = 10000;

//FPS = 30;
//number_of_seconds = 30;
const int Primary_Lifetime = 30 * 2;
const int step = 10, bullet_speed = 4;
const double pi = 3.14159265;
const double rotation_rate = 5;
bool move_tank(SDL_Keycode key, Tank * tank){
    switch (key) {
        case SDLK_UP:
            tank->x -= step * SDL_cos( (tank -> angle + tank -> thickness / 2) * pi / 180);
            tank->y -= step * SDL_sin( (tank -> angle + tank -> thickness / 2) * pi / 180);
            break;
        case SDLK_RIGHT:
            tank->angle += rotation_rate;
            break;
        case SDLK_LEFT:
            tank->angle -= rotation_rate;
    }
}

void move_bullet(Bullet * bullet){
    bullet -> x -= bullet_speed * SDL_cos( (bullet -> angle) * pi /180 );
    bullet -> y -= bullet_speed * SDL_sin( (bullet -> angle) * pi /180 );
    bullet -> lifetime -= 1;
}

int fire(Tank * tank) {
    if (tank -> remaining_bullets > 0) {
        tank -> bullets [5 - tank -> remaining_bullets] . lifetime = Primary_Lifetime;
        tank -> bullets [5 - tank -> remaining_bullets] . x = tank -> x;
        tank -> bullets [5 - tank -> remaining_bullets] . y = tank -> y;
        tank -> bullets [5 - tank -> remaining_bullets] . angle = tank -> angle + tank -> thickness / 2;
        tank -> remaining_bullets -= 1;
        return 1;
    }
    return 0;
}