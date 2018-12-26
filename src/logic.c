#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "physics.h"
#include "view.h"
#include "logic.h"

int correct_mod(int a, int b){
    if (a>=0)
        return a%b;
    a *= -1;
    return b-(a%b);
}

int movement_collides_walls(Tank * tank, Map * map){
    const int collision = 2, no_collision = 1;
    const double pi = 3.14159265;
    double angle_of_connecting_line, distance_tank_wall;
    //printf("ans: %f", atan(-1));
    for (int i=0; i<map->number_of_walls; i++){
        if (map->walls[i].x1 == map->walls[i].x2){
            //printf("index: %d\n", i);
            for (int y=map->walls[i].y1; y<=map->walls[i].y2; y++){
                angle_of_connecting_line = atan( (double)(y - tank->y)/(map->walls[i].x1 - tank->x) ) * 180/pi;
                distance_tank_wall = sqrt( pow( (map->walls[i].x1 - tank->x), 2) + pow( (y - tank->y), 2) );
                //if (angle_of_connecting_line < 0)
                    //angle_of_connecting_line += 360;
                 if (angle_of_connecting_line == -0.000000)
                    angle_of_connecting_line = 0.000000;
                printf("index: %d ang: %f dis %f\n", i, angle_of_connecting_line, distance_tank_wall);
                if (angle_of_connecting_line < tank->angle + tank->thickness
                && angle_of_connecting_line > tank->angle
                && distance_tank_wall < (double)tank->length){
                    return collision;
                }
            }
        }
    }
    printf("/////////////////////////////////////\n");
    return no_collision;
}