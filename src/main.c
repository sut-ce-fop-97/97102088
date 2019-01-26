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

void move_and_rotate_tank_calling(int arrow_keys[2][4], Tank * tank, Map * map){
    if (arrow_keys[tank->index][0] == 1 && movement_collides_walls(tank, map, 'F') == no_collision)
        move_tank('U', tank, map);
    if (arrow_keys[tank->index][1] == 1 && movement_collides_walls(tank, map, 'B') == no_collision)
        move_tank('D', tank, map);
    if (arrow_keys[tank->index][2] == 1)
        turn_tank('L', tank);
    if (arrow_keys[tank->index][3] == 1)
        turn_tank('R', tank);
}

int main(){
    int arrow_keys[2][4] = {0}; // Each of two rows of the array belongs to one of the tanks. In each row, columns' indexes are encoded as this -> Up:0 Down:1 Left:2 Right:3
    int output_of_handle_events;
    int winning_score = 5;
    index_of_last_assigned_mine = 0;
    srand(0);
    Map * map_1 = malloc(sizeof(Map));
    read_map_and_init_mapsize(map_1,
                              "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\3rd_map.txt", &map_1->width, &map_1->height);
    map_1->tanks = malloc(sizeof(Tank) * 2);
    init_tanks(map_1);
    // Next initializations can't be added to init_tanks function; because it should be run only at the first of game.


    map_1->mines = malloc(sizeof(Mine) * no_of_allowed_mines);
    for (int i=0; i<no_of_allowed_mines; i++)
        map_1->mines[i].index = -1;
    init_mine(index_of_last_assigned_mine ,map_1);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 30, 30, map_1->width, map_1->height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (menu(window, renderer, 'm', map_1) == new_game_in_start_menu) {
        int beginning_of_time = SDL_GetTicks();
        while (map_1->tanks[0].score < winning_score && map_1->tanks[1].score < winning_score) {
            //int current_time = SDL_GetTicks();
            init_window(renderer);
            SDL_RenderClear(renderer);
            draw_walls(renderer, map_1->walls, map_1->number_of_walls);
            draw_tank(renderer, &map_1->tanks[0]);
            char *buffer = malloc(sizeof(char) * 10);
            sprintf(buffer, "%f", map_1->tanks[0].angle);
            stringRGBA(renderer, 50, 50, buffer, 0,0,0,255);
            draw_tank(renderer, &map_1->tanks[1]);

            move_and_rotate_tank_calling(arrow_keys, &map_1->tanks[0], map_1);
            move_and_rotate_tank_calling(arrow_keys, &map_1->tanks[1], map_1);

            output_of_handle_events = handle_events(window, renderer, map_1, arrow_keys);
            if (output_of_handle_events == Exit)
                break;
            else if (output_of_handle_events == new_game_in_pause_menu){
                read_map_and_init_mapsize(map_1,
                                          "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\3rd_map.txt", &map_1->width, &map_1->height);
                init_tanks(map_1);
                index_of_last_assigned_mine = 0;
                init_mine(index_of_last_assigned_mine, map_1);
            }

            for (int k=0; k<=1; k++) {
                for (int i=0; i<Primary_Bullets; i++) {
                    if (map_1->tanks[k].bullets[i].lifetime > 0) {
                        draw_bullet(renderer, &map_1->tanks[k].bullets[i], map_1);
                        char *buffer = malloc(sizeof(char) * 10);
                        sprintf(buffer, "%d", map_1->tanks[k].bullets[i].previous_collided_wall_index);
                        stringRGBA(renderer, 10, 10, buffer, 0,0,0,255);
                    }
                }
            }

            for (int i=0; i<no_of_allowed_mines; i++) {
                draw_mine(renderer, &map_1->mines[i], map_1);
                if (map_1->mines[i].lifetime_after_plant > 0)
                    map_1->mines[i].lifetime_after_plant --;
            }



            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / FPS);
        }
        if (output_of_handle_events != Exit)
            game_over(renderer, map_1, beginning_of_time);
        quit_window(window, renderer);
    }
    return 0;
}