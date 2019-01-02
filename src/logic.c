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

int movement_collides_walls(Tank * tank, Map * map, char direction){
    // Primary condition in order to set the function for reverse driving state
    double copied_tank_angle = tank->angle;
    if (direction == 'B'){
        if (copied_tank_angle >= 180.0 && copied_tank_angle <360.0)
            copied_tank_angle -= 180.0;
        else if (copied_tank_angle >= 0.0 && copied_tank_angle < 180.0)
            copied_tank_angle += 180.0;
    }
    // There are some comments with "printf" components which were used to verify
    // if collision cases' codes work properly. These are remaining deliberately
    // because rewriting them for probable use in future consumes a lot of time.
    const int collision = 2, no_collision = 1;
    const double threshold_distance = 2.0, threshold_angle = 75.0;
    const double pi = 3.14159265;
    double distance_tank_and_wall;
    double distance_tank_and_edge_of_wall[4];//0: Up 1: Down 2: Left 3: Right
    double angle_tank_and_edge_of_wall;
    for (int i=0; i < map->number_of_walls; i++){
        //the case of vertical wall
        if (map->walls[i].x1 == map->walls[i].x2){
            distance_tank_and_edge_of_wall[0] = sqrt( pow(tank->x - map->walls[i].x1, 2) + pow(tank->y - map->walls[i].y1, 2));
            distance_tank_and_edge_of_wall[1] = sqrt( pow(tank->x - map->walls[i].x1, 2) + pow(tank->y - map->walls[i].y2, 2));
            //tape case
            if (tank->y <= map->walls[i].y2 && tank->y >= map->walls[i].y1){
                distance_tank_and_wall = abs(map->walls[i].x1 - tank->x);
                //printf("\n wall no. %d distance from wall: %f\n", i, distance_tank_and_wall);
                if (distance_tank_and_wall <= tank->radius + threshold_distance) {
                    if (tank->x < map->walls[i].x1){
                        if ( (copied_tank_angle < 360.0 && copied_tank_angle > 270.0) ||
                        (copied_tank_angle < 90.0 && copied_tank_angle >= 0.0)) {
                            //printf("\n wall no. %d tape ver wall \n", i);
                            return collision;
                        }
                    }
                    else {
                        if (copied_tank_angle < 270.0 && copied_tank_angle > 90.0) {
                            //printf("\n wall no. %d up and up left ver wall \n", i);
                            return collision;
                        }
                    }
                }
            }
            //upper edge case
            else if ( distance_tank_and_edge_of_wall[0] <= tank->radius + threshold_distance){
                if (tank->x == map->walls[i].x1)
                    angle_tank_and_edge_of_wall = 90.0;
                else
                    angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y1)/(tank->x - map->walls[i].x1) ) * 180.0/pi;
                //up_right
                if (angle_tank_and_edge_of_wall < 0.0) {
                    angle_tank_and_edge_of_wall += 180.0;
                    if (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle) {
                        //printf("\n wall no. %d up right ver wall \n", i);
                        return collision;
                    }
                }
                //up_left and up
                else {
                    if ( (copied_tank_angle < 360.0 && copied_tank_angle > 360.0 + angle_tank_and_edge_of_wall - threshold_angle)
                    || (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > 90.0 - threshold_angle) ) {
                        //printf("\n wall no. %d up and up left ver wall \n", i);
                        return collision;
                    }
                }
            }
            //lower edge case
            else if ( distance_tank_and_edge_of_wall[1] <= tank->radius + threshold_distance){
                if (tank->x == map->walls[i].x1)
                    angle_tank_and_edge_of_wall = 90.0;
                else
                    angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y2)/(tank->x - map->walls[i].x1) ) * 180.0/pi;
                //down_left
                if (angle_tank_and_edge_of_wall < 0.0) {
                    angle_tank_and_edge_of_wall += 360.0;
                    if ( (copied_tank_angle < 360.0 && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                    || (copied_tank_angle >=0 && copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle - 360.0) ) {
                        //printf("\n wall no. %d down left ver wall angle: %f \n", i, angle_tank_and_edge_of_wall);
                        return collision;
                    }
                }
                //down_right and down
                else {
                    angle_tank_and_edge_of_wall += 180.0;
                    if ( copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle) {
                        //printf("\n wall no. %d down and down right ver wall \n", i);
                        return collision;
                    }
                }
            }
        }

        //the case of horizontal wall
        else if (map->walls[i].y1 == map->walls[i].y2) {
            distance_tank_and_edge_of_wall[2] = sqrt( pow(tank->x - map->walls[i].x1, 2) + pow(tank->y - map->walls[i].y1, 2));
            distance_tank_and_edge_of_wall[3] = sqrt( pow(tank->x - map->walls[i].x2, 2) + pow(tank->y - map->walls[i].y1, 2));
            //tape case
            if (tank->x <= map->walls[i].x2 && tank->x >= map->walls[i].x1){
                distance_tank_and_wall = abs(map->walls[i].y1 - tank->y);
                if (distance_tank_and_wall <= tank->radius + threshold_distance) {
                    if (tank->y < map->walls[i].y1){
                        if (copied_tank_angle < 180.0 && copied_tank_angle > 0.0) {
                            //printf("\n wall no. %d tape hor wall \n", i);
                            return collision;
                        }
                    }
                    else {
                        if (copied_tank_angle < 360.0 && copied_tank_angle > 180.0) {
                            //printf("\n wall no. %d tape hor wall \n", i);
                            return collision;
                        }
                    }
                }
            }
            //left edge case
            else if ( distance_tank_and_edge_of_wall[2] <= tank->radius + threshold_distance){
                angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y1)/(tank->x - map->walls[i].x1) ) * 180.0/pi;
                //left_down
                if (angle_tank_and_edge_of_wall < 0.0) {
                    angle_tank_and_edge_of_wall += 360.0;
                    if ( (copied_tank_angle < 360.0 && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                    || (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle - 360.0 && copied_tank_angle >= 0.0) ) {
                        //printf("\n wall no. %d left down hor wall \n", i);
                        return collision;
                    }
                }
                //left_up and left
                else {
                    if ( (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle >= 0.0)
                         || (copied_tank_angle < 360.0 && copied_tank_angle > 360.0 + angle_tank_and_edge_of_wall - threshold_angle) ) {
                        //printf("\n wall no. %d left up and left hor wall \n", i);
                        return collision;
                    }
                }
            }
            //right edge case
            else if ( distance_tank_and_edge_of_wall[3] <= tank->radius + threshold_distance){
                angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y2)/(tank->x - map->walls[i].x2) ) * 180.0/pi;
                //right_up and right_down and right
                angle_tank_and_edge_of_wall += 180.0;
                if (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle) {
                    //printf("\n wall no. %d right and right up and right down hor wall \n", i);
                    return collision;
                }
            }
        }
    }
    return no_collision;
}