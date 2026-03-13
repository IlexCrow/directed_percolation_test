#include <iostream>
#include <random>
#include <unistd.h>
#include <SDL2/SDL.h>
#define scale 36
const int screen_width = 500;
const int screen_height = 500;
bool running = true;
bool paused = false;
int generation = 0;
SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
bool board[screen_width][screen_height]; // God it has been quite a while since I've done any programming hasn't it.

const int random_numbers_number = 100000000;
float random_numbers[random_numbers_number]; // Psudo random numbers so it's not super slow
int random_number_index = 0;

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);;

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

bool check_random(float probability) {
    random_number_index++;
    if (random_number_index >= random_numbers_number) random_number_index = 0;
    return (random_numbers[random_number_index] > probability);
}

void process() {
    for (int i = 0; i <= generation; i++) { // Run diagonally accross x+y = generation. O(n^2) but again; quick and dirty.
        if (generation-i >= screen_height || i >= screen_width) continue; // i.e. don't try and do stuff off the screen.
        if (board[i][generation-i]) {
            board[i][generation-i+1] = check_random(0.3);
            board[i+1][generation-i] = check_random(0.3);
        }
    }
    if (generation > screen_width+screen_height)paused = true; // Should probably lock it rather than just pausing.
    generation++;
}

int main() {
    srand(time(0));

    for (int i = 0; i < random_numbers_number; i++) { // Generate array of psudo random numbers.
        // random_numbers[i] = 1;
        random_numbers[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // I will make this more random later.
    }

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(screen_width*2, screen_height*2, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, 2, 2);
    SDL_SetWindowTitle(window, "Directed Percolation");
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
