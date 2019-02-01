#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "physics.h"
#include "view.h"
#include "logic.h"

int correct_int_casting(double inp){
    if (inp >= 0.0 || (int)inp == inp)
        return (int)inp;
    return (int)inp - 1;
}

int correct_mod(int a, int b){
    if (a >= 0)
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
        else
            copied_tank_angle += 180.0;
    }
    const double threshold_distance = 2.0, threshold_angle = 75.0;
    const double pi = 3.14159265;
    double distance_tank_and_wall;
    double distance_tank_and_edge_of_wall[4];// 0: Up 1: Down 2: Left 3: Right
    double angle_tank_and_edge_of_wall;
    for (int i=0; i < map->number_of_walls; i++){
        //the case of vertical wall
        if (map->walls[i].x1 == map->walls[i].x2){
            distance_tank_and_edge_of_wall[0] = sqrt( pow(tank->x - map->walls[i].x1, 2) + pow(tank->y - map->walls[i].y1, 2));
            distance_tank_and_edge_of_wall[1] = sqrt( pow(tank->x - map->walls[i].x1, 2) + pow(tank->y - map->walls[i].y2, 2));
            //tape case
            if (tank->y <= map->walls[i].y2 && tank->y >= map->walls[i].y1){
                distance_tank_and_wall = abs(map->walls[i].x1 - tank->x);
                if (distance_tank_and_wall <= tank->radius + threshold_distance) {
                    if (tank->x < map->walls[i].x1){
                        if ( (copied_tank_angle < 360.0 && copied_tank_angle > 270.0) ||
                        (copied_tank_angle < 90.0 && copied_tank_angle >= 0.0))
                            return collision;
                    }
                    else {
                        if (copied_tank_angle < 270.0 && copied_tank_angle > 90.0)
                            return collision;
                    }
                }
            }
            //up edge case
            else if ( distance_tank_and_edge_of_wall[0] <= tank->radius + threshold_distance){
                if (tank->x == map->walls[i].x1)
                    angle_tank_and_edge_of_wall = 90.0;
                else
                    angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y1)/(tank->x - map->walls[i].x1) ) * 180.0/pi;
                //up_right
                if (angle_tank_and_edge_of_wall < 0.0) {
                    angle_tank_and_edge_of_wall += 180.0;
                    if (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                        return collision;
                }
                //up_left and up
                else {
                    if ( (copied_tank_angle < 360.0 && copied_tank_angle > 360.0 + angle_tank_and_edge_of_wall - threshold_angle)
                    || (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle >= 0.0) )
                        return collision;
                }
            }
            //down edge case
            else if ( distance_tank_and_edge_of_wall[1] <= tank->radius + threshold_distance){
                if (tank->x == map->walls[i].x1)
                    angle_tank_and_edge_of_wall = 90.0;
                else
                    angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y2)/(tank->x - map->walls[i].x1) ) * 180.0/pi;
                //down_left
                if (angle_tank_and_edge_of_wall < 0.0) {
                    angle_tank_and_edge_of_wall += 360.0;
                    if ( (copied_tank_angle < 360.0 && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                    || (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle - 360.0 && copied_tank_angle >= 0.0) )
                        return collision;
                }
                //down_right and down
                else {
                    angle_tank_and_edge_of_wall += 180.0;
                    if ( copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                        return collision;
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
                        if (copied_tank_angle < 180.0 && copied_tank_angle > 0.0)
                            return collision;
                    }
                    else {
                        if (copied_tank_angle < 360.0 && copied_tank_angle > 180.0)
                            return collision;
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
                    || (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle - 360.0 && copied_tank_angle >= 0.0) )
                        return collision;
                }
                //left_up and left
                else {
                    if ( (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle >= 0.0)
                         || (copied_tank_angle < 360.0 && copied_tank_angle > 360.0 + angle_tank_and_edge_of_wall - threshold_angle) )
                        return collision;
                }
            }
            //right edge case
            else if ( distance_tank_and_edge_of_wall[3] <= tank->radius + threshold_distance){
                angle_tank_and_edge_of_wall = atan( (double)(tank->y - map->walls[i].y2)/(tank->x - map->walls[i].x2) ) * 180.0/pi;
                //right_up and right_down and right
                angle_tank_and_edge_of_wall += 180.0;
                if (copied_tank_angle < angle_tank_and_edge_of_wall + threshold_angle && copied_tank_angle > angle_tank_and_edge_of_wall - threshold_angle)
                    return collision;
            }
        }
    }
    return no_collision;
}

void bullet_wall_collision(Bullet * bullet, Map * map){
    int i;
    const double threshold_distance = bullet->radius;
    double distance_bullet_and_wall;
    double distance_bullet_and_edge_of_wall[4];// 0: Up 1: Down 2: Left 3: Right
    for (i = 0; i < map->number_of_walls; i++){
        if (i == bullet->previous_collided_wall_index)
            continue;
        // the case of vertical wall
        if (map->walls[i].x1 == map->walls[i].x2) {
            distance_bullet_and_edge_of_wall[0] = sqrt( pow(bullet->x - map->walls[i].x1, 2) + pow(bullet->y - map->walls[i].y1, 2));
            distance_bullet_and_edge_of_wall[1] = sqrt( pow(bullet->x - map->walls[i].x1, 2) + pow(bullet->y - map->walls[i].y2, 2));
            // tape case
            if (bullet->y <= map->walls[i].y2 && bullet->y >= map->walls[i].y1) {
                distance_bullet_and_wall = abs(map->walls[i].x1 - bullet->x);
                if (distance_bullet_and_wall <= threshold_distance) {
                    if (bullet->angle <= 180.0 && bullet->angle >= 0.0) {
                        bullet->angle = 180.0 - bullet->angle;
                        bullet->previous_collided_wall_index = i;
                        return;
                    } else {
                        bullet->angle = 540.0 - bullet->angle;
                        bullet->previous_collided_wall_index = i;
                        return;
                    }
                }
            }
            // up edge case
            else if (distance_bullet_and_edge_of_wall[0] <= threshold_distance){
                if (bullet->angle == 180.0)
                    bullet->angle = 0;
                else if (bullet->angle < 180.0)
                    bullet->angle += 180.0;
                bullet->previous_collided_wall_index = i;
                return;
            }
            // down edge case
            else if (distance_bullet_and_edge_of_wall[1] <= threshold_distance){
                if (bullet->angle == 0.0)
                    bullet->angle = 180.0;
                else if (bullet->angle >= 180.0)
                    bullet->angle -= 180.0;
                bullet->previous_collided_wall_index = i;
                return;
            }
        }
        // the case of horizontal wall
        else if (map->walls[i].y1 == map->walls[i].y2) {
            distance_bullet_and_edge_of_wall[2] = sqrt( pow(bullet->x - map->walls[i].x1, 2) + pow(bullet->y - map->walls[i].y1, 2));
            distance_bullet_and_edge_of_wall[3] = sqrt( pow(bullet->x - map->walls[i].x2, 2) + pow(bullet->y - map->walls[i].y1, 2));
            // tape case
            if (bullet->x <= map->walls[i].x2 && bullet->x >= map->walls[i].x1) {
                distance_bullet_and_wall = abs(map->walls[i].y1 - bullet->y);
                if (distance_bullet_and_wall <= threshold_distance) {
                    bullet->angle = 360.0 - bullet->angle;
                    bullet->previous_collided_wall_index = i;
                    return;
                }
            }
            // left edge case
            else if (distance_bullet_and_edge_of_wall[2] <= threshold_distance){
                if (bullet->angle <= 90.0)
                    bullet->angle += 180.0;
                else if (bullet->angle >= 270.0)
                    bullet->angle -= 180.0;
                bullet->previous_collided_wall_index = i;
                return;
            }
            // right edge case
            else if (distance_bullet_and_edge_of_wall[3] <= threshold_distance){
                if (bullet->angle < 180.0 && bullet->angle >= 90.0)
                    bullet->angle += 180.0;
                else if (bullet->angle <= 270.0 && bullet->angle >= 180.0)
                    bullet->angle -= 180.0;
                bullet->previous_collided_wall_index = i;
                return;
            }
        }
    }
}

int bullet_tank_collision(Bullet * bullet, Map * map){
    double distance_bullet_tank;
    int duration_of_bullet_existence = Bullet_Primary_Lifetime - bullet->lifetime;
    if (duration_of_bullet_existence > 0) {
        for (int i = 0; i <= 1; i++) {
            distance_bullet_tank = sqrt(pow(map->tanks[i].x - bullet->x, 2) + pow(map->tanks[i].y - bullet->y, 2));
            if (distance_bullet_tank <= map->tanks[i].radius + bullet->radius) {
                bullet->lifetime = 0;
                map->tanks[1 - i].score++;
                locate_tanks(map);
                return collision;
            }
        }
    }
    return no_collision;
}


void save_game(Map * map, char * file_path){
    FILE * save_info = fopen(file_path, "w");
    // Walls' coordinates
    fprintf(save_info, "%d\n", map->number_of_walls);
    for (int i=0; i<map->number_of_walls; i++)
        fprintf(save_info, "%d %d %d %d\n", map->walls[i].x1 / map_scale, map->walls[i].y1 / map_scale, map->walls[i].x2 / map_scale, map->walls[i].y2 / map_scale);
    for (int i=0; i<=1; i++) {
        // Tanks' info
        fprintf(save_info, "%d %d %lf %d ", map->tanks[i].x, map->tanks[i].y, map->tanks[i].angle, map->tanks[i].score);
        fprintf(save_info, "%d %d %lf %lf %d\n", map->tanks[i].remaining_bullets, map->tanks[i].index, map->tanks[i].radius, map->tanks[i].thickness, map->tanks[i].mine_index);
        // One tank's bullets
        for (int j = 0; j < Primary_Bullets; j++) {
            fprintf(save_info, "%d %d %d ", map->tanks[i].bullets[j].lifetime, map->tanks[i].bullets[j].x, map->tanks[i].bullets[j].y);
            fprintf(save_info, "%lf %lf %d\n", map->tanks[i].bullets[j].angle, map->tanks[i].bullets[j].radius, map->tanks[i].bullets[j].previous_collided_wall_index);
        }
    }
    // Mines' info
    fprintf(save_info, "%d\n", map->index_of_last_assigned_mine);
    for (int i = 0; i < no_of_allowed_mines; i++){
        fprintf(save_info, "%d %d %d ", map->mines[i].index, map->mines[i].x, map->mines[i].y);
        fprintf(save_info, "%lf %d %d ", map->mines[i].radius, map->mines[i].interval_between_appear_and_pick, map->mines[i].countdown_before_next_mine);
        fprintf(save_info, "%d %d %d %d\n", map->mines[i].picker_tank, map->mines[i].is_planted, map->mines[i].lifetime_after_plant, map->mines[i].explosion_countdown);
    }
    fclose(save_info);
}

void load_game(Map * map, char * file_path){
    int cursor_set;
    FILE * load_info = fopen(file_path, "r");
    read_map_and_init_mapsize(map, file_path, &map->width, &map->height);
    // Next line is only written to move cursor of scanning info to proper location in the file of saved game.
    for (int i = 1; i <= 4 * map->number_of_walls + 1; i++)
        fscanf(load_info, "%d", &cursor_set);
    for (int i=0; i<=1; i++) {
        // Tanks' info
        fscanf(load_info, "%d %d %lf %d ", &map->tanks[i].x, &map->tanks[i].y, &map->tanks[i].angle, &map->tanks[i].score);
        fscanf(load_info, "%d %d %lf %lf %d\n", &map->tanks[i].remaining_bullets, &map->tanks[i].index, &map->tanks[i].radius, &map->tanks[i].thickness, &map->tanks[i].mine_index);
        // One Tank's bullets
        for (int j = 0; j < Primary_Bullets; j++) {
            fscanf(load_info, "%d %d %d ", &map->tanks[i].bullets[j].lifetime, &map->tanks[i].bullets[j].x, &map->tanks[i].bullets[j].y);
            fscanf(load_info, "%lf %lf %d\n", &map->tanks[i].bullets[j].angle, &map->tanks[i].bullets[j].radius, &map->tanks[i].bullets[j].previous_collided_wall_index);
        }
    }
    // Mines' info
    fscanf(load_info, "%d\n", &map->index_of_last_assigned_mine);
    for (int i = 0; i < no_of_allowed_mines; i++){
        fscanf(load_info, "%d %d %d ", &map->mines[i].index, &map->mines[i].x, &map->mines[i].y);
        fscanf(load_info, "%lf %d %d ", &map->mines[i].radius, &map->mines[i].interval_between_appear_and_pick, &map->mines[i].countdown_before_next_mine);
        fscanf(load_info, "%d %d %d %d\n", &map->mines[i].picker_tank, &map->mines[i].is_planted, &map->mines[i].lifetime_after_plant, &map->mines[i].explosion_countdown);
    }
    //make_mine(map);
    fclose(load_info);
}