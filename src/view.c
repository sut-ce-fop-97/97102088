#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "physics.h"
#include "view.h"

//const int bullet_lifetime = 10000;

const int EXIT = 2;
const int SHOOT = 3;
//const int draw_bull = 3;
const int bullet_radius = 4;

void draw_tank(SDL_Renderer * renderer ,Tank * tank){
    filledPieRGBA(renderer, tank->x, tank->y, tank->length, tank->angle , tank->angle + tank->thickness, 255, 0, 0, 255);
}

void draw_bullet(SDL_Renderer * renderer, Bullet * bullet){
    filledCircleRGBA(renderer, bullet -> x, bullet -> y, bullet_radius, 0, 0, 0, 255);
    move_bullet(bullet);
}

void init_window(SDL_Renderer * renderer){
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
}

bool quit_window(SDL_Window * window, SDL_Renderer * renderer){
    SDL_Event quit;
    while (SDL_PollEvent(&quit)) {
        if (quit.type==SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return  true;
        }
    }
}

int handle_events(SDL_Renderer * renderer, Map * map){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EXIT;
        if (event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_UP:
                    move_tank(event.key.keysym.sym, map -> tanks);
                    break;
                case SDLK_RIGHT:
                    move_tank(event.key.keysym.sym, map -> tanks);
                    break;
                case SDLK_LEFT:
                    move_tank(event.key.keysym.sym, map -> tanks);
                    break;
                case SDLK_e:
                    fire(map -> tanks);
            }
        }
    }
}