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

const double tank_speed = 4.0, bullet_speed = 6.0;
const double pi = 3.14159265;
const double rotation_rate = 3.0;

void locate_tanks(Map * map){
    double decimal_rand;
    int tanks_starting_positions[4][2]
            ={30, 30, map->width - 30, 30, 30, map->height - 30, map->width - 30, map->height - 30};
    int tanks_rand[2];
    tanks_rand[0] = correct_mod(rand(), 4);
    do{
        tanks_rand[1] = correct_mod(rand(), 4);
    } while(tanks_rand[0] == tanks_rand[1]);
    for (int i=0; i<=1; i++){
        map->tanks[i].x = tanks_starting_positions[tanks_rand[i]][0];
        map->tanks[i].y = tanks_starting_positions[tanks_rand[i]][1];
        decimal_rand = correct_mod(rand(), (int) pow(10, 6)) * pow(10, -6);
        map->tanks[i].angle = correct_mod(rand(), 360) + decimal_rand;
    }
}

void move_tank(char key, Tank * tank, Map * map){
    switch (key) {
        case 'U':
            if (tank->angle == 270.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= correct_int_casting(tank_speed);
            else {
                tank->x += correct_int_casting(tank_speed * cos((tank->angle) / 180.0*pi));
                tank->y += correct_int_casting(tank_speed * sin((tank->angle) / 180.0*pi));
            }
            break;
        case 'D':
            if (tank->angle == 90.0) //An exceptional case because of a bug in trigonometric calculations of SDL functions
                tank->y -= correct_int_casting(tank_speed);
            else if (tank->angle == 180.0)
                tank->x += correct_int_casting(tank_speed); //An exceptional case because of a bug in trigonometric calculations of SDL functions
            else {
                tank->x -= correct_int_casting(tank_speed * cos((tank->angle) / 180.0*pi));
                tank->y -= correct_int_casting(tank_speed * sin((tank->angle) / 180.0*pi));
            }
    }
    pick_mine(tank, map);
}

void turn_tank(char key, Tank * tank){
    double decimal_part;
    switch (key) {
        case 'R':
            tank->angle += rotation_rate;
            break;
        case 'L':
            tank->angle -= rotation_rate;
    }
    decimal_part = tank->angle - correct_int_casting(tank->angle);
    tank->angle = correct_mod(correct_int_casting(tank->angle), 360) + decimal_part;
}

void move_bullet(Bullet * bullet, Map * map){
    if (bullet_tank_collision(bullet, map) != collision) {
        bullet_wall_collision(bullet, map);
        bullet->x += correct_int_casting(bullet_speed * cos((bullet->angle) / 180.0 * pi));
        bullet->y += correct_int_casting(bullet_speed * sin((bullet->angle) / 180.0 * pi));
        bullet->lifetime--;
    }
}

void locate_mine(Mine * mine, Map * map){
    mine->x = correct_mod(rand(), map->width - (int)mine->radius) + (int)mine->radius;
    mine->y = correct_mod(rand(), map->height - (int)mine->radius) + (int)mine->radius;
}

void pick_mine(Tank * tank, Map * map){
    double distance_tank_and_mine;
    if (tank->mine_index == -1) {
        for (int i = 0; i < no_of_allowed_mines; i++) {
            if (map->mines[i].index != -1 && map->mines[i].picker_tank == -1)
                distance_tank_and_mine = sqrt(pow(tank->x - map->mines[i].x, 2) + pow(tank->y - map->mines[i].y, 2));
            if (map->mines[i].interval_between_appear_and_pick > 0 && distance_tank_and_mine <= map->mines[i].radius + tank->radius) {
                map->mines[i].picker_tank = tank->index;
                tank->mine_index = i;
                index_of_last_assigned_mine++;
                if (index_of_last_assigned_mine < no_of_allowed_mines)
                    init_mine(index_of_last_assigned_mine, map);
            }
        }
    }
}

void plant_mine(Tank * tank, Map * map){
    map->mines[tank->mine_index].x = tank->x;
    map->mines[tank->mine_index].y = tank->y;
    map->mines[tank->mine_index].is_planted = 1;
    map->mines[tank->mine_index].lifetime_after_plant = mine_lifetime_after_plant;
    tank->mine_index = -1;
}

// Probably next function should be called in draw_mine with or without(?) loop on all the mines.
void explode_mine(Mine * mine, Map *map){
    double distance_tank_and_mine, threshold_distance;
    if (mine->is_planted == 1) {
        distance_tank_and_mine = sqrt( pow(map->tanks[1 - mine->picker_tank].x - mine->x, 2) + pow(map->tanks[1 - mine->picker_tank].y - mine->y, 2) );
        threshold_distance = mine->radius + map->tanks[1 - mine->picker_tank].radius + 2.0;
        if (distance_tank_and_mine <= threshold_distance) {
            if (mine->is_planted == 1 && mine->lifetime_after_plant > 0 && mine->explosion_countdown == inactive_mine)
                mine->explosion_countdown = explosion_delay;
            else if (mine->explosion_countdown == 0) {
                map->tanks[mine->picker_tank].score ++;
                locate_tanks(map);
            }
        }
    }
}


int fire(Tank * tank) {
    if (tank->remaining_bullets > 0) {
        tank->bullets [Primary_Bullets - tank->remaining_bullets].lifetime = Bullet_Primary_Lifetime;
        tank->bullets [Primary_Bullets - tank->remaining_bullets].x = tank->x + (bullet_radius + tank->radius + 1) * cos((tank->angle) / 180.0*pi);
        tank->bullets [Primary_Bullets - tank->remaining_bullets].y = tank->y + (bullet_radius + tank->radius + 1) * sin((tank->angle) / 180.0*pi);
        tank->bullets [Primary_Bullets - tank->remaining_bullets].angle = tank->angle;
        tank->bullets [Primary_Bullets - tank->remaining_bullets].radius = bullet_radius;
        tank->bullets [Primary_Bullets - tank->remaining_bullets].previous_collided_wall_index = -1;
        //About previous line: Previous collided wall is meaningless just after firing a bullet.
        tank->remaining_bullets -= 1;
        return 1;
    }
    return 0;
}