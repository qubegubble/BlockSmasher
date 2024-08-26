#include "Player.h"
#include "Platform.h"
#include <SDL.h>
#include <vector>

using namespace Player;
using namespace std;

Movement::Movement()
    : playerX(100), playerY(100), speed(5), jumpSpeed(20), gravity(2),
    verticalVelocity(0), isJumping(false), isOnGround(true),
    movingLeft(false), movingRight(false), jumping(false) {}

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
        case SDLK_SPACE:
            if (isOnGround) {
                jumping = true;
            }
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
        case SDLK_SPACE:
            jumping = false;
            break;
        default:
            break;
        }
    }
}

void Movement::Update(const std::vector<Platform>& platforms) {
    int previousX = playerX;
    int previousY = playerY;

    if (movingLeft) {
        playerX -= speed;
    }
    if (movingRight) {
        playerX += speed;
    }

    SDL_Rect playerRect = { playerX, playerY, 50, 50 };

    for (const auto& platform : platforms) {
        if (CheckCollision(playerRect, platform.GetRect())) {
            playerX = previousX; // reset to previous position on collision
            break;
        }
    }

    if (jumping && isOnGround) {
        verticalVelocity = -jumpSpeed;
        isOnGround = false;
    }

    if (!isOnGround) {
        verticalVelocity += gravity;
    }

    playerY += verticalVelocity;

    isOnGround = false;
    playerRect.y = playerY;
    for (const auto& platform : platforms) {
        if (CheckCollision(playerRect, platform.GetRect())) {
            if (verticalVelocity > 0) { // falling down
                playerY = platform.GetRect().y - playerRect.h;
                isOnGround = true;
                verticalVelocity = 0;
            }
            else if (verticalVelocity < 0) { // jumping up
                playerY = platform.GetRect().y + platform.GetRect().h;
                verticalVelocity = 0;
            }
            break;
        }
    }

    // check if the player has landed on the ground (floor level check)
    if (playerY >= 500) { // assuming 500 is the ground level
        playerY = 500;
        isOnGround = true;
        verticalVelocity = 0;
    }
}

bool Movement::CheckCollision(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}
