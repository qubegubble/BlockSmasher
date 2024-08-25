#include "Player.h"
#include <SDL.h>

using namespace Player;
using namespace std;

Movement::Movement()
    : playerX(100), playerY(100), speed(5), jumpSpeed(20), gravity(2),
    verticalVelocity(0), isJumping(false), isOnGround(true),
    movingLeft(false), movingRight(false), jumping(false) {}

int Movement::getPlayerX() const {
    return playerX;
}

int Movement::getPlayerY() const {
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

void Movement::Update() {
    if (movingLeft) {
        playerX -= speed;
    }
    if (movingRight) {
        playerX += speed;
    }

    if (jumping && isOnGround) {
        verticalVelocity = -jumpSpeed;
        isOnGround = false;
    }

    if (!isOnGround) {
        verticalVelocity += gravity;
        playerY += verticalVelocity;

        if (playerY >= 100) { // Ground will be implemented later.
            playerY = 100;
            isOnGround = true;
            verticalVelocity = 0;
        }
    }
}
