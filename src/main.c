#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
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

void move_and_rotate_tank_calling(int arrow_keys[2][4], Tank * tank, Map * map){
    // 'F':forward 'B':backward
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
    int output_of_handle_events, output_of_menu;
    int winning_score = 5;
    char map_1_address[60];
    strcpy(map_1_address, "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\3rd_map.txt");
    srand(0);

    Map * map_1 = malloc(sizeof(Map));
    read_map_and_init_mapsize(map_1, map_1_address, &map_1->width, &map_1->height);
    map_1->tanks = malloc(sizeof(Tank) * 2);
    init_tanks(map_1);
    map_1->mines = malloc(sizeof(Mine) * no_of_allowed_mines);
    for (int i=0; i<no_of_allowed_mines; i++)
        map_1->mines[i].index = -1;
    map_1->index_of_last_assigned_mine = 0;
    make_mine(map_1);

    /*
    Map * loaded_map = malloc(sizeof(Map));
    //read_map_and_init_mapsize(loaded_map,
    //                          "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\1st_map.txt", &loaded_map->width, &loaded_map->height);
    loaded_map->tanks = malloc(sizeof(Tank) * 2);
    //init_tanks(loaded_map);
    loaded_map->mines = malloc(sizeof(Mine) * no_of_allowed_mines);
    for (int i=0; i<no_of_allowed_mines; i++)
        loaded_map->mines[i].index = -1;
    */
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 30, 30, map_1->width, map_1->height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //output_of_menu = menu(window, renderer, 'm', map_1);

    /*
    if (menu(window, renderer, 'm', map_1) == load_game_in_menu){
        load_game(map_1, "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\saved_game.txt");
    }
    */

    output_of_menu = menu(window, renderer, 'm', map_1);
    if (output_of_menu == new_game_in_start_menu || output_of_menu == load_game_in_menu) {
        if (output_of_menu == load_game_in_menu)
            load_game(&window, &renderer, map_1, "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\saved_game.txt");
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
                SDL_DestroyWindow(window);
                read_map_and_init_mapsize(map_1, map_1_address, &map_1->width, &map_1->height);
                window = SDL_CreateWindow("FoP_Project", 30, 30, map_1->width, map_1->height, SDL_WINDOW_OPENGL);
                renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
                init_tanks(map_1);
                map_1->index_of_last_assigned_mine = 0;
                //make_mine(map_1);
            }
            else if (output_of_handle_events == load_game_in_menu)
                load_game(&window, &renderer, map_1, "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\saved_game.txt");
            for (int k=0; k<=1; k++) {
                for (int i=0; i<Primary_Bullets; i++) {
                    if (map_1->tanks[k].bullets[i].lifetime > 0) {
                        draw_bullet(renderer, &map_1->tanks[k].bullets[i], map_1);
                        /*
                        char *buffer = malloc(sizeof(char) * 10);
                        sprintf(buffer, "%d", map_1->tanks[k].bullets[i].previous_collided_wall_index);
                        stringRGBA(renderer, 10, 10, buffer, 0,0,0,255);
                        */
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
        //quit_window(window, renderer);
    }
    quit_window(window, renderer);
    return 0;
}