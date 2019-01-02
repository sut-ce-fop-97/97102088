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
const int no_collision = 1;
const int Primary_Bullets = 5;

int string_to_int(char * str){
    int converter_index = 0, ans = 0;
    while (str[converter_index] != '\0'){
        ans *= 10;
        ans += str[converter_index] - '0';
        converter_index++;
    }
    return ans;
}

// Map of the game can be changed by modifying the destination of file containing desired map
// in the second argument when calling function of "read_map_and_init_mapsize" in the function of "main".
void read_map_and_init_mapsize(Map * map, char * file_path, int * map_width, int * map_height){
    char * temp = malloc(sizeof(char) * 10);
    int max_height = 0, max_width = 0;
    FILE * map_file_pointer = fopen(file_path, "r");
    fscanf(map_file_pointer, "%s", temp);
    map->number_of_walls = string_to_int(temp);
    map->walls = malloc(sizeof(Wall) * map->number_of_walls);
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
    }
    *map_width = max_width + 1;
    *map_height = max_height + 1;
    fclose(map_file_pointer);
    free(temp);
}

void init_tank(Map * map, Tank * tank, int map_width, int map_height){
    double decimal_rand;
    srand(0);
    /*
    do {
        tank->x = correct_mod(rand(), map_width);
        tank->y = correct_mod(rand(), map_height);
    } while (movement_collides_walls(tank, map, 'F') != no_collision);
    */
    tank->x = 30;
    tank->y = 30;
    decimal_rand = correct_mod(rand(), (int)pow(10, 6)) * pow(10, -6);
    tank->angle = correct_mod(rand(), 360) + decimal_rand;
    tank->radius = 18;
    tank->thickness = 40.0;
    tank->bullets = malloc(sizeof(Bullet) * Primary_Bullets);
    tank->remaining_bullets = Primary_Bullets;
    for (int i=0; i<Primary_Bullets; i++)
        tank->bullets[i].lifetime = -1;

}

void move_and_rotate_tank_calling(int * arrow_keys, Tank * tank, Map * map){
    if (arrow_keys[0] == 1 && movement_collides_walls(tank, map, 'F') == no_collision)
        move_tank('U', tank);
    if (arrow_keys[1] == 1 && movement_collides_walls(tank, map, 'B') == no_collision)
        move_tank('D', tank);
    if (arrow_keys[2] == 1)
        turn_tank('L', tank);
    if (arrow_keys[3] == 1)
        turn_tank('R', tank);
}

int main(){
    int arrow_keys[4] = {0}; // Up:0 Down:1 Left:2 Right:3
    const double FPS = 30;
    int map_width, map_height;
    Map * map_1 = malloc(sizeof(Map));
    read_map_and_init_mapsize(map_1,
                              "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\3rd_map.txt", &map_width, &map_height);
    map_1->tanks = malloc(sizeof(Tank) * 1);
    init_tank(map_1, &map_1->tanks[0], map_width, map_height);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 30, 30, map_width, map_height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (1){
        init_window(renderer);
        SDL_RenderClear(renderer);
        draw_tank(renderer, map_1->tanks);
        draw_walls(renderer, map_1->walls, map_1->number_of_walls);
        if (handle_events(map_1, arrow_keys) == 2)
            break;
        for (int i=0; i<Primary_Bullets; i++) {
            if (map_1->tanks->bullets[i].lifetime > 0)
                draw_bullet(renderer, &map_1->tanks->bullets[i]);
        }
        move_and_rotate_tank_calling(arrow_keys, map_1->tanks, map_1);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/FPS);
    }
    quit_window(window, renderer);
    return 0;
}