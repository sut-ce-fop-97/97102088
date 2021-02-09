#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "view.h"
#include "physics.h"
#include "logic.h"

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
    int winning_score = 5, is_consumed_all_bullets = 0, is_consumed_all_mines = 0;
    int map_index;
    char map_address[60];
    printf("Please enter an number from 1 to 3 to choose a map:\n");
    scanf("%d", &map_index);

    switch (map_index) {
        case 1:
            strcpy(map_address, "../src/1st_map.txt");
            break;
        case 2:
            strcpy(map_address, "../src/2nd_map.txt");
            break;
        case 3:
            strcpy(map_address, "../src/3rd_map.txt");
            break;
        default:
            printf("%s", "Entered map index is not valid.");
    }
    srand(0);

    Map * map_1 = malloc(sizeof(Map));
    read_map_and_init_mapsize(map_1, map_address, &map_1->width, &map_1->height);
    map_1->tanks = malloc(sizeof(Tank) * 2);
    init_tanks(map_1);
    map_1->mines = malloc(sizeof(Mine) * no_of_allowed_mines);
    for (int i=0; i<no_of_allowed_mines; i++) {
        map_1->mines[i].index = -1;
        map_1->mines[i].lifetime_after_plant = -1;
    }
    map_1->index_of_last_assigned_mine = 0;
    make_mine(map_1);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("FoP_Project", 0, 25, window_width, window_height, SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    output_of_menu = menu(renderer, 'm', map_1);
    if (output_of_menu == new_game_in_start_menu || output_of_menu == load_game_in_menu) {
        if (output_of_menu == load_game_in_menu)
            load_game(map_1, "../src/saved_game.txt");
        int beginning_of_time = SDL_GetTicks();
        while (map_1->tanks[0].score < winning_score && map_1->tanks[1].score < winning_score
        && (is_consumed_all_bullets == 0 || is_consumed_all_mines == 0) ) {
            is_consumed_all_bullets = 1;
            is_consumed_all_mines = 1;
            init_window(renderer);
            SDL_RenderClear(renderer);

            output_of_handle_events = handle_events(renderer, map_1, arrow_keys);
            if (output_of_handle_events == Exit)
                break;
            else if (output_of_handle_events == new_game_in_pause_menu){
                read_map_and_init_mapsize(map_1, map_address, &map_1->width, &map_1->height);
                init_tanks(map_1);
                map_1->index_of_last_assigned_mine = 0;
            }
            else if (output_of_handle_events == load_game_in_menu)
                load_game(map_1, "../src/saved_game.txt");

            draw_walls(renderer, map_1->walls, map_1->number_of_walls);
            for (int i=0; i<=1; i++)
                draw_tank(renderer, &map_1->tanks[i]);

            move_and_rotate_tank_calling(arrow_keys, &map_1->tanks[0], map_1);
            move_and_rotate_tank_calling(arrow_keys, &map_1->tanks[1], map_1);

            for (int k=0; k<=1; k++) {
                for (int i=0; i<Primary_Bullets; i++) {
                    if (map_1->tanks[k].bullets[i].lifetime > 0) {
                        is_consumed_all_bullets = 0;
                        draw_bullet(renderer, &map_1->tanks[k].bullets[i], map_1);
                    }
                    else if (map_1->tanks[k].bullets[i].lifetime == -1)
                        is_consumed_all_bullets = 0;
                }
            }

            for (int i=0; i<no_of_allowed_mines; i++) {
                draw_mine(renderer, &map_1->mines[i], map_1);
                if (map_1->mines[i].lifetime_after_plant > 0) {
                    is_consumed_all_mines = 0;
                    map_1->mines[i].lifetime_after_plant--;
                }
                else if (map_1->mines[i].lifetime_after_plant == -1)
                    is_consumed_all_mines = 0;
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(1000 / FPS);
        }
        if (output_of_handle_events != Exit)
            game_over(renderer, map_1, beginning_of_time);
    }
    quit_window(window, renderer);
    return 0;
}