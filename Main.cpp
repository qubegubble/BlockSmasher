#include <SDL.h>
#include <iostream>
#include "Player.h"
#include "Wall.h"
#include "ScreenSettings.h"

using namespace std;
using namespace util;

int main(int argc, char* argv[]) {
    int horizontal;
    int vertical;
    Screensize::GetDesktopResolution(horizontal, vertical);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("BlockSmasher", 0, 0, horizontal, vertical, SDL_WINDOW_FULLSCREEN);
    if (window == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    Player::Movement player;
    SDL_Rect playerRect;
    playerRect.w = 50;
    playerRect.h = 50;
    playerRect.x = player.GetPlayerX();
    playerRect.y = player.GetPlayerY();

    bool quit = false;
    SDL_Event event;

    // Define colors
    SDL_Color blue = { 0, 0, 255, 255 };   // Blue
    SDL_Color red = { 255, 0, 0, 255 };    // Red

    // Create Platform objects with initial colors
    std::vector<Wall> platforms = {
        Wall(200, 300, 200, 20, blue), // Blue platform
        Wall(500, 400, 150, 20, red)   // Red platform
    };

    // Main game loop
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            player.HandleEvent(event);
        }

        player.Update(platforms);

        // Example: Change the color of the first platform to green
        SDL_Color green = { 0, 255, 0, 255 };
        platforms[0].SetColor(green);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Render platforms
        for (const auto& platform : platforms) {
            platform.Render(renderer);
        }

        // Render the player (block)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black block
        playerRect.x = player.GetPlayerX();
        playerRect.y = player.GetPlayerY();
        SDL_RenderFillRect(renderer, &playerRect);

        SDL_RenderPresent(renderer);

        SDL_Delay(16); // Roughly 60 FPS
    }


    // Clean up SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
