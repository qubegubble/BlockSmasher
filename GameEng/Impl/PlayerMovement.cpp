#include "Player.h"
#include "Wall.h"
#include <SDL.h>
#include <vector>

using namespace Player;
using namespace std;

Movement::Movement()
    : playerX(100), playerY(100), speed(5),
    movingLeft(false), movingRight(false), movingDown(false), movingUp(false),
    isInteracting(false), playerAttacking(false), playerGuarding(false) {}

int Movement::GetPlayerX() const {
    return playerX;
}

int Movement::GetPlayerY() const {
    return playerY;
}

void Movement::HandleEvent(const SDL_Event& event) {
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_a:
            movingLeft = true;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            movingRight = true;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            movingDown = true;
            break;
        case SDLK_UP:
        case SDLK_w:
            movingUp = true;
            break;
        case SDLK_SPACE:
            isInteracting = true;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_a:
            movingLeft = false;
            break;
        case SDLK_RIGHT:
        case SDLK_d:
            movingRight = false;
            break;
        case SDLK_DOWN:
        case SDLK_s:
            movingDown = false;
            break;
        case SDLK_UP:
        case SDLK_w:
            movingUp = false;
            break;
        case SDLK_SPACE:
            isInteracting = false;
            break;
        default:
            break;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            playerAttacking = true;
            break;
        case SDL_BUTTON_RIGHT:
            playerGuarding = true;
            break;
        default:
            break;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
        switch (event.button.button) {
            case SDL_BUTTON_LEFT:
            playerAttacking = false;
            break;
        case SDL_BUTTON_RIGHT:
            playerGuarding = false;
            break;
        default:
            break;
        }
    }

}

void Movement::Update(const std::vector<Wall>& platforms) {
    int previousX = playerX;
    int previousY = playerY;

    if (movingLeft) {
        playerX -= speed;
    }
    if (movingRight) {
        playerX += speed;
    }
    if (movingDown) {
        playerY += speed;
    }
    if (movingUp) {
        playerY -= speed;
    }
    if (playerAttacking) {
        AttackPlayer();
    }
    if (playerGuarding) {
        GuardPlayer();
    }

    SDL_Rect playerRect = { playerX, playerY, 50, 50 };

    for (const auto& platform : platforms) {
        if (CheckCollision(playerRect, platform.GetRect())) {
            playerX = previousX; // reset to previous position on collision
            playerY = previousY;
            break;
        }
    }
}

bool Movement::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

void Movement::AttackPlayer() {
    playerX += speed;
}

void Movement::GuardPlayer() {
    playerY -= speed;
}
