#include <iostream>
#include <random>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <array>
#define scale 36
const int screen_width = 1000;
const int screen_height = 1000;
bool running = true;
bool paused = false;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;


void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);

    SDL_RenderPresent(renderer);
}




void process() {

}

int main() {


    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_SetWindowTitle(window, "Tetris++");


    while (running) {
        if (!paused) {
            process();
        }
        draw();
            SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE)(paused = !paused);

                    break;
            }
        }

    }

    return 0;
}