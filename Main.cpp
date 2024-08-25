#include <SDL.h>
#include <iostream>
#include "Player.h" // including Player header file.

using namespace std;

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("2D Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
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
    playerRect.x = player.getPlayerX();
    playerRect.y = player.getPlayerY();

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            player.HandleEvent(event);
        }

        player.Update();

        playerRect.x = player.getPlayerX();
        playerRect.y = player.getPlayerY();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);

        // Draw the player (block)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black block
        SDL_RenderFillRect(renderer, &playerRect);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Cap the frame rate (optional)
        SDL_Delay(16); // Roughly 60 FPS
    }

    // Clean up SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
