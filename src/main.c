#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "view.h"
#include "physics.h"
#include "structs.h"

#ifdef main
#undef main
#endif

void read_map_file(Map * map){
    char * buffer = malloc(sizeof(char) * 8);
    int number_of_walls = 0, converter_index=0;
    FILE * map_file_pointer = fopen("D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\mapmap.txt", "r");


    while (buffer[converter_index++] != '\0'){
        number_of_walls *= 10;
        number_of_walls += (buffer[converter_index] - '0');
    }
    map -> walls = malloc(sizeof(Wall) * number_of_walls);
    //printf("number of walls: %d", number_of_walls);
    fread(map -> walls, sizeof(Wall), number_of_walls, map_file_pointer);
    fclose(map_file_pointer);
}

int main(){
    srand(1);
    const double FPS = 30;
    //const int number_of_seconds = 30;
    //const int Primary_Lifetime = number_of_seconds * FPS;
    const int Primary_Bullets = 5;
    int map_height=600, map_width=800;

    Map * map_1 = malloc(sizeof(Map));
    Tank * tank_1 = malloc(sizeof(Tank));
    tank_1 -> bullets = malloc(sizeof(Bullet) * Primary_Bullets);
    map_1 -> tanks = tank_1;
    tank_1 -> x = rand() % map_width;
    tank_1 -> y = rand() % map_height;
    tank_1 -> angle = rand() % 360;
    for (int i=0; i<Primary_Bullets; i++) {
        tank_1 -> bullets[i].lifetime = -1;
        //char* buffer = malloc(sizeof(char) * 20);
        //sprintf(buffer, "lifetime %d: %d   ", i, tank_1->bullets[i].lifetime);
        //printf("%s", buffer);
    }
    /*
    tank_1 -> bullets -> x = 100;
    tank_1 -> bullets -> y = 100;
    tank_1 -> bullets -> angle = 80;
    */
    tank_1 -> length = 40;
    tank_1 -> thickness = 60;
    tank_1 -> remaining_bullets = Primary_Bullets;
    read_map_file(map_1);
    /*
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 30, 30, map_width, map_height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while (1){
        init_window(renderer);
        SDL_RenderClear(renderer);
            draw_tank(renderer, tank_1);
            if (handle_events(renderer, map_1) == 2)
                break;
            for (int i=0; i<Primary_Bullets; i++) {
                if (tank_1 -> bullets[i] . lifetime > 0)
                    draw_bullet(renderer, &tank_1 -> bullets[i]);
            }

            char* buffer = malloc(sizeof(char) * 20);
            sprintf(buffer, "lifetime 0: %d, lifetime 1: %d, lifetime 2: %d, lifetime 3: %d, lifetime 4: %d remaining: %d",
            tank_1 -> bullets[0] . lifetime, tank_1 -> bullets[1] . lifetime, tank_1 -> bullets[2] . lifetime, tank_1 -> bullets[3] . lifetime, tank_1 -> bullets[4] . lifetime, tank_1 -> remaining_bullets);
            printf("%s", buffer);
            stringRGBA(renderer, 5, 5, buffer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }
    quit_window(window, renderer);
    */
    return 0;
}