#include <iostream>
#include <random>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <array>
#define scale 36
const int screen_width = 500;
const int screen_height = 500;
bool running = true;
bool paused = false;
int generation = 0;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool board[screen_width][screen_height]; // God it has been quite a while since I've done any programming hasn't it.


void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);;

    // Draw the board from the board bitmap
    // I know this isn't exactly the prettiest or fastest way of doing it,
    // but this is a quick and dirty program I thought would be cool to make.
    for (int i = 0; i < screen_width; i++) {
        for (int j = 0; j < screen_height; j++) {
            if (board[i][j]) {
                SDL_RenderDrawPoint(renderer, i, j);
            }
        }
    }
    SDL_RenderPresent(renderer);
}



void process() {
    for (int i = 0; i <= generation; i++) { // Run diagonally accross x+y = generation. O(n^2) but again; quick and dirty.
        if (generation-i >= screen_height || i >= screen_width) continue; // i.e. don't try and do stuff off the screen.
        if (board[i][generation-i]) {
            board[i][generation-i+1] = true;
            board[i+1][generation-i] = true;
        }
    }
    if (generation > screen_width+screen_height)paused = true; // Should probably lock it rather than just pausing.
    generation++;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &window, &renderer);
    // SDL_RenderSetScale(renderer, 0.5, 0.5);
    SDL_SetWindowTitle(window, "Tetris++");
    board[0][0] = true; // Initial seed.

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
