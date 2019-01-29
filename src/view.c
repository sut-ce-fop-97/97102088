#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "physics.h"
#include "view.h"
#include "logic.h"
#include "structs.h"

void init_window(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
}

// Map of the game can be changed by modifying the destination of file containing desired map
// in the second argument when calling function of "read_map_and_init_mapsize" in the function of "main".
void read_map_and_init_mapsize(Map * map, char * file_path, int * map_width, int * map_height){
    int max_height = 0, max_width = 0;
    FILE * map_file_pointer = fopen(file_path, "r");
    int temp;
    fscanf(map_file_pointer, "%d", &temp);
    map->number_of_walls = temp;
    map->walls = malloc(map->number_of_walls * sizeof(Wall));

    for (int i=0; i<map->number_of_walls; i++){
        fscanf(map_file_pointer, "%d", &temp);
        map->walls[i].x1 = temp * map_scale;
        fscanf(map_file_pointer, "%d", &temp);
        map->walls[i].y1 = temp * map_scale;
        fscanf(map_file_pointer, "%d", &temp);
        map->walls[i].x2 = temp * map_scale;
        if (map->walls[i].x2 > max_width)
            max_width = map->walls[i].x2;
        fscanf(map_file_pointer, "%d", &temp);
        map->walls[i].y2 = temp * map_scale;
        if (map->walls[i].y2 > max_height)
            max_height = map->walls[i].y2;
    }
    *map_width = max_width + 1;
    *map_height = max_height + 1;
    fclose(map_file_pointer);
    //free(temp);
}

void init_tanks(Map * map){
    /*
    do {
        tank->x = correct_mod(rand(), map_width);
        tank->y = correct_mod(rand(), map_height);
    } while (movement_collides_walls(tank, map, 'F') != no_collision);
    */
    locate_tanks(map);
    for (int i=0; i<=1; i++) {
        map->tanks[i].score = 0;
        map->tanks[i].remaining_bullets = Primary_Bullets;
        map->tanks[i].index = i;
        map->tanks[i].radius = 18.0;
        map->tanks[i].thickness = 40.0;
        map->tanks[i].mine_index = -1;
        map->tanks[i].bullets = malloc(sizeof(Bullet) * Primary_Bullets);
        for (int j = 0; j < Primary_Bullets; j++)
            map->tanks[i].bullets[j].lifetime = -1;
    }
}

void make_mine(Map * map){
    // Declaration of a help variable in the next line is only used to shorten the length of other lines in this function.
    int mine_index = map->index_of_last_assigned_mine;
    map->mines[mine_index].index = mine_index;
    map->mines[mine_index].x = correct_mod(rand(), map->width - 2 * (int)map->mines[mine_index].radius) + (int)map->mines[mine_index].radius;
    map->mines[mine_index].y = correct_mod(rand(), map->height - 2 * (int)map->mines[mine_index].radius) + (int)map->mines[mine_index].radius;
    map->mines[mine_index].radius = mine_radius;
    map->mines[mine_index].interval_between_appear_and_pick = 0;
    map->mines[mine_index].countdown_before_next_mine = time_between_consecutive_mines;
    map->mines[mine_index].picker_tank = -1;
    map->mines[mine_index].is_planted = 0;
    map->mines[mine_index].lifetime_after_plant = -1;
    map->mines[mine_index].explosion_countdown = not_activated_mine_yet;
}

void draw_tank(SDL_Renderer * renderer ,Tank * tank){
    int Circle_r, Circle_g, Circle_b, Pie_r, Pie_g, Pie_b;
    if (tank->index == 0){
        Circle_r = 255; Circle_g = 0; Circle_b = 0;
        Pie_r = 0; Pie_g = 255; Pie_b = 0;
    }
    else {
        Circle_r = 0; Circle_g = 0; Circle_b = 255;
        Pie_r = 255; Pie_g = 223; Pie_b = 0;
    }
    filledCircleRGBA(renderer, tank->x, tank->y, tank->radius, Circle_r, Circle_g, Circle_b, 255);
    filledPieRGBA(renderer, tank->x, tank->y, tank->radius, tank->angle - tank->thickness/2 , tank->angle + tank->thickness/2, Pie_r, Pie_g, Pie_b, 255);
}

void draw_bullet(SDL_Renderer * renderer, Bullet * bullet, Map * map){
    char * buffer = malloc(30 * sizeof(char));
    sprintf(buffer, "%d %d %lf %d", bullet->x, bullet->y, bullet->angle, bullet->previous_collided_wall_index);
    printf("%s\n", buffer);
    stringRGBA(renderer, 40, 40, buffer, 0,0,0,255);
    filledCircleRGBA(renderer, bullet->x, bullet->y, bullet->radius, 0, 0, 0, 255);
    move_bullet(bullet, map);
}

void draw_walls(SDL_Renderer * renderer, Wall * walls, int number_of_walls){
    for (int i=0; i<number_of_walls; i++)
        boxRGBA(renderer, walls[i].x1, walls[i].y1,
                walls[i].x2, walls[i].y2, 0, 0, 0, 255);
}

void draw_mine(SDL_Renderer * renderer, Mine * mine, Map * map){
    explode_mine(mine, map);
    if (mine->explosion_countdown >= 0){
        filledCircleRGBA(renderer, mine->x, mine->y, mine->radius, 255, 165, 0, 255);
        mine->explosion_countdown --;
    }
    else if (mine->interval_between_appear_and_pick > 0 && mine->picker_tank == -1) {
        filledCircleRGBA(renderer, mine->x, mine->y, mine->radius, 255, 255, 0, 255);
        stringRGBA(renderer, mine->x, mine->y, "M", 0, 0, 0, 255);
        mine->interval_between_appear_and_pick --;
        if (mine->interval_between_appear_and_pick == 0)
            mine->countdown_before_next_mine = time_between_consecutive_mines;
    }
    else if (mine->picker_tank == -1) {
        mine->countdown_before_next_mine --;
        if (mine->countdown_before_next_mine == 0) {
            mine->interval_between_appear_and_pick = time_between_appear_and_pick;
            locate_mine(mine, map);
        }
    }
}

void quit_window(SDL_Window * window, SDL_Renderer * renderer){
    SDL_Event quit;
    while (SDL_PollEvent(&quit)) {
        if (quit.type==SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    }
}

int menu(SDL_Window * window, SDL_Renderer * renderer, char call_from, Map * map){
    int buttons_width = map->width / 3, buttons_height = map->height * 2 / 10;
    Button new_game, load, quit;
    new_game.x = map->width / 2 - buttons_width / 2;    new_game.y = map->height * 1 / 10;
    load.x = map->width / 2 - buttons_width / 2;    load.y = map->height * 4 / 10;
    quit.x = map->width / 2 - buttons_width / 2;    quit.y = map->height * 7 / 10;

    SDL_Event event;
    while (1){
        SDL_SetRenderDrawColor(renderer, 10, 80, 80, 255);
        SDL_RenderClear(renderer);

        boxRGBA(renderer, new_game.x, new_game.y, new_game.x + buttons_width, new_game.y + buttons_height, 150, 50, 0, 255);
        char* first_banner = "Press G to start a new game.";
        stringRGBA(renderer, new_game.x + horizontal_margin_for_text, new_game.y + buttons_height / 2, first_banner, 0, 0, 0, 255);

        boxRGBA(renderer, load.x, load.y, load.x + buttons_width, load.y + buttons_height, 150, 50, 0, 255);
        char* second_banner = "Press L to load the last game.";
        stringRGBA(renderer, load.x + horizontal_margin_for_text, load.y + buttons_height / 2, second_banner, 0, 0, 0, 255);

        boxRGBA(renderer, quit.x, quit.y, quit.x + buttons_width, quit.y + buttons_height, 150, 50, 0, 255);
        char* third_banner = "Press Q to quit the game.";
        stringRGBA(renderer, quit.x + horizontal_margin_for_text, quit.y + buttons_height / 2, third_banner, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return Exit;
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        if (call_from == 'h')
                            return proceed_to_game;
                        break;
                    case SDLK_g:
                        if (call_from == 'm')
                            return new_game_in_start_menu;
                        else if (call_from == 'h')
                            return new_game_in_pause_menu;
                        break;
                    case SDLK_l:
                        return load_game_in_menu;
                    case SDLK_q:
                        return Exit;
                }
            }
        }
        SDL_Delay(1000 / FPS);
    }
}

int game_over(SDL_Renderer * renderer, Map * map, int beginning_of_time){
    int final_screen_width = map->width / 3, final_screen_height = map->height * 4 / 10;
    int final_screen_x = map->width / 2 - final_screen_width / 2, final_screen_y = map->height / 2 - final_screen_height / 2;
    int current_time = SDL_GetTicks();
    char banner_buffer[40];
    SDL_Event event;

    while (1){
        SDL_SetRenderDrawColor(renderer, 200, 20, 200, 255);
        SDL_RenderClear(renderer);

        boxRGBA(renderer, final_screen_x, final_screen_y, final_screen_x + final_screen_width,
                final_screen_y + final_screen_height, 0, 200, 50, 255);
        sprintf(banner_buffer, "Elapsed Time is: %d seconds", (current_time - beginning_of_time) / 1000);
        stringRGBA(renderer, final_screen_x + horizontal_margin_for_text, final_screen_y + final_screen_height / 2 - 20, banner_buffer, 0, 0, 0, 255);

        sprintf(banner_buffer, "First Player Score: %d", map->tanks[0].score);
        stringRGBA(renderer, final_screen_x + horizontal_margin_for_text, final_screen_y + final_screen_height / 2, banner_buffer, 0, 0, 0, 255);

        sprintf(banner_buffer, "Second Player Score: %d", map->tanks[1].score);
        stringRGBA(renderer, final_screen_x + horizontal_margin_for_text, final_screen_y + final_screen_height / 2 + 20, banner_buffer, 0, 0, 0, 255);

        sprintf(banner_buffer, "Press Q to quit the game.");
        stringRGBA(renderer, final_screen_x + horizontal_margin_for_text, final_screen_y + final_screen_height / 2 + 60, banner_buffer, 0, 0, 0, 255);

        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) )
                return Exit;
        }
        SDL_Delay(1000 / FPS);
    }
}

int handle_events(SDL_Window * window, SDL_Renderer * renderer, Map * map, int arrow_keys[2][4]){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return Exit;
        else if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_ESCAPE:
                    return menu(window, renderer, 'h', map);
                // Movement Keys of first tank
                case SDLK_UP:
                    arrow_keys[0][0] = 1;
                    break;
                case  SDLK_DOWN:
                    arrow_keys[0][1] = 1;
                    break;
                case SDLK_LEFT:
                    arrow_keys[0][2] = 1;
                    break;
                case SDLK_RIGHT:
                    arrow_keys[0][3] = 1;
                    break;
                // Movement Keys of second tank
                case SDLK_w:
                    arrow_keys[1][0] = 1;
                    break;
                case  SDLK_s:
                    arrow_keys[1][1] = 1;
                    break;
                case SDLK_a:
                    arrow_keys[1][2] = 1;
                    break;
                case SDLK_d:
                    arrow_keys[1][3] = 1;
                    //break;
            }
        }
        else if (event.type == SDL_KEYUP){
            switch (event.key.keysym.sym){
                // Keys of first tank movement
                case SDLK_UP:
                    arrow_keys[0][0] = 0;
                    break;
                case  SDLK_DOWN:
                    arrow_keys[0][1] = 0;
                    break;
                case SDLK_LEFT:
                    arrow_keys[0][2] = 0;
                    break;
                case SDLK_RIGHT:
                    arrow_keys[0][3] = 0;
                    break;
                // Keys of second tank movement
                case SDLK_w:
                    arrow_keys[1][0] = 0;
                    break;
                case  SDLK_s:
                    arrow_keys[1][1] = 0;
                    break;
                case SDLK_a:
                    arrow_keys[1][2] = 0;
                    break;
                case SDLK_d:
                    arrow_keys[1][3] = 0;
                    break;
                // Keys of firing bullets or planting mines
                case SDLK_SLASH:
                    if (map->tanks[0].mine_index == -1)
                        fire(&map->tanks[0]);
                    else
                        plant_mine(&map->tanks[0], map);
                    break;
                case SDLK_e:
                    if (map->tanks[1].mine_index == -1)
                        fire(&map->tanks[1]);
                    else
                        plant_mine(&map->tanks[1], map);
                    break;
                case SDLK_b:
                    save_game(map, "D:\\Amir Abbas's Documents\\FoP\\FoP_Project\\src\\saved_game.txt");
            }
        }
    }
}