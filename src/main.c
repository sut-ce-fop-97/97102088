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

#ifdef main
#undef main
#endif

const int map_scale = 80;

int string_to_int(char * str){
    int converter_index = 0, ans = 0;
    while (str[converter_index] != '\0'){
        ans *= 10;
        ans += str[converter_index] - '0';
        converter_index++;
    }
    return ans;
}

void read_map_and_init_mapsize(Map * map, char * file_path, int * map_height, int * map_width){
    char * temp = malloc(sizeof(char) * 10);
    int max_height = 0, max_width = 0;
    FILE * map_file_pointer = fopen(file_path, "r");
    fscanf(map_file_pointer, "%s", temp);
    map->number_of_walls = string_to_int(temp);
    map->walls = malloc(sizeof(Wall) * map->number_of_walls);
    //printf("num of walls: %d \n", map->number_of_walls);
    for (int i=0; i<map->number_of_walls; i++){
        fscanf(map_file_pointer, "%s", temp);
            map->walls[i].x1 = string_to_int(temp) * map_scale;
        fscanf(map_file_pointer, "%s", temp);
            map->walls[i].y1 = string_to_int(temp) * map_scale;
        fscanf(map_file_pointer, "%s", temp);
            map->walls[i].x2 = string_to_int(temp) * map_scale;
            if (map->walls[i].x2 > max_width)
                max_width = map->walls[i].x2;
        fscanf(map_file_pointer, "%s", temp);
            map->walls[i].y2 = string_to_int(temp) * map_scale;
            if (map->walls[i].y2 > max_height)
                max_height = map->walls[i].y2;
        printf("index: %d | %d %d %d %d\n", i, map->walls[i].x1, map->walls[i].y1, map->walls[i].x2, map->walls[i].y2);
    }
    printf("\n\n");
    *map_height = max_height + 1;
    *map_width = max_width + 1;
    //printf("wid: %d hei: %d", *map_width, *map_height);
    fclose(map_file_pointer);
    free(temp);
}

int main(){
    //printf("%f", 4 * atan(1));

    srand(2);
    const double FPS = 30;
    double decimal_rand;
    //const int number_of_seconds = 30;
    //const int Primary_Lifetime = number_of_seconds * FPS;
    const int Primary_Bullets = 5;
    //int number_of_walls;
    int map_height, map_width;

    Map * map_1 = malloc(sizeof(Map));
    Tank * tank_1 = malloc(sizeof(Tank));
    read_map_and_init_mapsize(map_1,
            "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\3rd_map.txt", &map_height, &map_width);
    tank_1->bullets = malloc(sizeof(Bullet) * Primary_Bullets);
    map_1->tanks = tank_1;
    //tank_1->x = correct_mod(rand(), map_width);
    //tank_1->y = correct_mod(rand(), map_height);
    tank_1->x = 30;
    tank_1->y = 530;
    decimal_rand = correct_mod(rand(), (int)pow(10, 6)) * pow(10, -6);
    //tank_1->angle = correct_mod(rand(), 360) + decimal_rand;
    tank_1->angle = 330.0;
    //printf("%f %f", tank_1->angle, decimal_rand);
    for (int i=0; i<Primary_Bullets; i++)
        tank_1->bullets[i].lifetime = -1;
    tank_1->length = 40;
    tank_1->thickness = 40.0;
    tank_1->remaining_bullets = Primary_Bullets;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 30, 30, map_width, map_height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (1){

        init_window(renderer);
        SDL_RenderClear(renderer);
            draw_tank(renderer, tank_1);
            draw_walls(renderer, map_1->walls, map_1->number_of_walls);
            if (handle_events(map_1) == 2)
                break;
            for (int i=0; i<Primary_Bullets; i++) {
                if (tank_1->bullets[i].lifetime > 0)
                    draw_bullet(renderer, &tank_1->bullets[i]);
            }
/*
            char* buffer = malloc(sizeof(char) * 20);
            sprintf(buffer, "angle: %f", tank_1->angle);
            printf("%s", buffer);
            stringRGBA(renderer, 5, 5, buffer, 0, 0, 0, 255);
*/
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }
    quit_window(window, renderer);

    return 0;
}